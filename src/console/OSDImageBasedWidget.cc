// $Id$

#include "OSDImageBasedWidget.hh"
#include "OSDGUI.hh"
#include "BaseImage.hh"
#include "OutputSurface.hh"
#include "Display.hh"
#include "CliComm.hh"
#include "TclObject.hh"
#include "CommandException.hh"
#include "Timer.hh"
#include <cassert>

using std::string;
using std::set;

namespace openmsx {

OSDImageBasedWidget::OSDImageBasedWidget(const OSDGUI& gui_, const string& name)
	: OSDWidget(name)
	, gui(gui_)
	, startFadeTime(0)
	, fadePeriod(0.0)
	, fadeTarget(1.0)
	, startFadeValue(1.0)
	, error(false)
{
	for (int i = 0; i < 4; ++i) {
		rgba[i] = 0x000000ff;
	}
}

OSDImageBasedWidget::~OSDImageBasedWidget()
{
}

void OSDImageBasedWidget::getProperties(set<string>& result) const
{
	result.insert("-rgba");
	result.insert("-rgb");
	result.insert("-alpha");
	result.insert("-fadePeriod");
	result.insert("-fadeTarget");
	result.insert("-fadeCurrent");
	OSDWidget::getProperties(result);
}

static void get4(const TclObject& value, unsigned* result)
{
	unsigned len = value.getListLength();
	if (len == 4) {
		for (unsigned i = 0; i < 4; ++i) {
			result[i] = value.getListIndex(i).getInt();
		}
	} else if (len == 1) {
		unsigned val = value.getInt();
		for (unsigned i = 0; i < 4; ++i) {
			result[i] = val;
		}
	} else {
		throw CommandException("Expected either 1 or 4 values.");
	}
}
static bool constantAlpha(const unsigned rgba[4])
{
	return ((rgba[0] & 0xff) == (rgba[1] & 0xff)) &&
	       ((rgba[0] & 0xff) == (rgba[2] & 0xff)) &&
	       ((rgba[0] & 0xff) == (rgba[3] & 0xff));
}
static bool sameRGB(const unsigned rgba_1[4], const unsigned rgba_2[4])
{
	return ((rgba_1[0] & 0xffffff00) == (rgba_2[0] & 0xffffff00)) &&
	       ((rgba_1[1] & 0xffffff00) == (rgba_2[1] & 0xffffff00)) &&
	       ((rgba_1[2] & 0xffffff00) == (rgba_2[2] & 0xffffff00)) &&
	       ((rgba_1[3] & 0xffffff00) == (rgba_2[3] & 0xffffff00));
}
void OSDImageBasedWidget::setProperty(const string& name, const TclObject& value)
{
	if (name == "-rgba") {
		unsigned newRGBA[4];
		get4(value, newRGBA);
		if (!constantAlpha(newRGBA) || !constantAlpha(rgba) ||
		    !sameRGB(newRGBA, rgba)) {
			invalidateLocal();
		}
		for (unsigned i = 0; i < 4; ++i) {
			rgba[i] = newRGBA[i];
		}
	} else if (name == "-rgb") {
		unsigned newRGB[4];
		get4(value, newRGB);
		if (!constantAlpha(rgba) || !sameRGB(newRGB, rgba)) {
			invalidateLocal();
		}
		for (unsigned i = 0; i < 4; ++i) {
			rgba[i] = (rgba[i]          & 0x000000ff) |
			          ((newRGB[i] << 8) & 0xffffff00);
		}
	} else if (name == "-alpha") {
		unsigned newAlpha[4];
		get4(value, newAlpha);
		if (!constantAlpha(rgba) || !constantAlpha(newAlpha)) {
			invalidateLocal();
		}
		for (unsigned i = 0; i < 4; ++i) {
			rgba[i] = (rgba[i]     & 0xffffff00) |
			          (newAlpha[i] & 0x000000ff);
		}
	} else if (name == "-fadePeriod") {
		updateCurrentFadeValue();
		fadePeriod = value.getDouble();
	} else if (name == "-fadeTarget") {
		updateCurrentFadeValue();
		fadeTarget = std::max(0.0, std::min(1.0 , value.getDouble()));
	} else if (name == "-fadeCurrent") {
		startFadeValue = std::max(0.0, std::min(1.0, value.getDouble()));
		startFadeTime = Timer::getTime();
	} else {
		OSDWidget::setProperty(name, value);
	}
}

static void set4(const unsigned rgba[4], unsigned mask, unsigned shift, TclObject& result)
{
	if ((rgba[0] == rgba[1]) && (rgba[0] == rgba[2]) && (rgba[0] == rgba[3])) {
		result.setInt((rgba[0] & mask) >> shift);
	} else {

		for (unsigned i = 0; i < 4; ++i) {
			result.addListElement(int((rgba[i] & mask) >> shift));
		}
	}
}
void OSDImageBasedWidget::getProperty(const string& name, TclObject& result) const
{
	if (name == "-rgba") {
		set4(rgba, 0xffffffff, 0, result);
	} else if (name == "-rgb") {
		set4(rgba, 0xffffff00, 8, result);
	} else if (name == "-alpha") {
		set4(rgba, 0x000000ff, 0, result);
	} else if (name == "-fadePeriod") {
		result.setDouble(fadePeriod);
	} else if (name == "-fadeTarget") {
		result.setDouble(fadeTarget);
	} else if (name == "-fadeCurrent") {
		result.setDouble(getCurrentFadeValue());
	} else {
		OSDWidget::getProperty(name, result);
	}
}

bool OSDImageBasedWidget::hasConstantAlpha() const
{
	return constantAlpha(rgba);
}
bool OSDImageBasedWidget::hasConstantRGBA() const
{
	return (rgba[0] == rgba[1]) && (rgba[0] == rgba[2]) && (rgba[0] == rgba[3]);
}

byte OSDImageBasedWidget::getFadedAlpha() const
{
	unsigned alpha = constantAlpha(rgba) ? (rgba[0] & 0xff): 255;
	return byte(alpha * getRecursiveFadeValue());
}

double OSDImageBasedWidget::getRecursiveFadeValue() const
{
	return getParent()->getRecursiveFadeValue() * getCurrentFadeValue();
}

bool OSDImageBasedWidget::isFading() const
{
	return (startFadeValue != fadeTarget) && (fadePeriod != 0.0);
}

double OSDImageBasedWidget::getCurrentFadeValue() const
{
	if (!isFading()) {
		return startFadeValue;
	}
	return getCurrentFadeValue(Timer::getTime());
}

double OSDImageBasedWidget::getCurrentFadeValue(unsigned long long now) const
{
	assert(now >= startFadeTime);

	int diff = int(now - startFadeTime); // int should be big enough
	assert(fadePeriod != 0.0);
	double delta = diff / (1000000.0 * fadePeriod);
	if (startFadeValue < fadeTarget) {
		double tmp = startFadeValue + delta;
		if (tmp >= fadeTarget) {
			startFadeValue = fadeTarget;
			return startFadeValue;
		}
		return tmp;
	} else {
		double tmp = startFadeValue - delta;
		if (tmp <= fadeTarget) {
			startFadeValue = fadeTarget;
			return startFadeValue;
		}
		return tmp;
	}
}

void OSDImageBasedWidget::updateCurrentFadeValue()
{
	unsigned long long now = Timer::getTime();
	if (isFading()) {
		startFadeValue = getCurrentFadeValue(now);
	}
	startFadeTime = now;
}

void OSDImageBasedWidget::invalidateLocal()
{
	error = false;
	image.reset();
}

void OSDImageBasedWidget::getTransformedXY(const OutputSurface& output,
                                           double& outx, double& outy) const
{
	const OSDWidget* parent = getParent();
	assert(parent);
	int factor = getScaleFactor(output);
	double x = factor * getX();
	double y = factor * getY();
	parent->transformXY(output, x, y, getRelX(), getRelY(), outx, outy);
}

void OSDImageBasedWidget::setError(const string& message)
{
	error = true;
	gui.getDisplay().getCliComm().printWarning(message);
}

void OSDImageBasedWidget::paintSDL(OutputSurface& output)
{
	paint(output, false);
}

void OSDImageBasedWidget::paintGL(OutputSurface& output)
{
	paint(output, true);
}

void OSDImageBasedWidget::paint(OutputSurface& output, bool openGL)
{
	// Note: Even when alpha == 0 we still create the image:
	//    It may be needed to get the dimensions to be able to position
	//    child widgets.
	if (!image.get() && !hasError()) {
		try {
			if (openGL) {
				image.reset(createGL(output));
			} else {
				image.reset(createSDL(output));
			}
		} catch (MSXException& e) {
			setError(e.getMessage());
		}
	}
	byte fadedAlpha = getFadedAlpha();
	if ((fadedAlpha != 0) && image.get()) {
		double x, y;
		getTransformedXY(output, x, y);
		image->draw(output, int(x + 0.5), int(y + 0.5), fadedAlpha);
	}
	if (isFading()) {
		gui.refresh();
	}
}

} // namespace openmsx
