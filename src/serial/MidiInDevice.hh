#ifndef MIDIINDEVICE_HH
#define MIDIINDEVICE_HH

#include "Pluggable.hh"

namespace openmsx {

class MidiInDevice : public Pluggable
{
public:
	// Pluggable (part)
	string_ref getClass() const final override;

	virtual void signal(EmuTime::param time) = 0;
};

} // namespace openmsx

#endif
