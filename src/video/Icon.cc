// $Id$
/* GIMP RGBA C-Source image dump (openMSX_32.c) */
// ...but a little bit modified to fit into openMSX nicely :)

// To replace it:
// - save your image from GIMP with a .c extension, with all options off,
//   except RGBA
// - rename it to Icon.hh
// - add the namespace stuff
// - remove the const
// - rename gimp_image to openMSX_icon
// - add these comments

#include "Icon.hh"

namespace openmsx {

OpenMSX_Icon openMSX_icon = {
  32, 32, 4,
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\207\26\0\0\206V\0\0\204d\0\0\201Q\0"
  "\0\200\17\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\207"
  "\5\37\37\225\17788\240\366\4\4\205\377\0\0\201\377\24\24\211\377\20\20\205"
  "\357\0\0zj\0\0x\1\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\206\1AA\245\240\352"
  "\352\365\377\377\377\377\377\312\312\345\377\230\230\313\377\375\375\376"
  "\377\361\361\370\37788\224\377\0\0u\215\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\204N\251\251\325\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\266\266\327\377\0\0q\376\0\0"
  "oN\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\202\275\331\331\354\377\335\335\335\377\324"
  "\324\324\377\370\370\367\377\367\367\367\377\302\302\302\377\377\377\377"
  "\377\362\362\370\377\0\0n\377\0\0l\240\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\200\2\0\0\177"
  "\365\304\304\341\377\335\335\335\377[ZG\377\331\320H\377\312\304k\377ZZZ"
  "\377\377\377\377\377\342\342\356\377\0\0k\377\0\0i\332\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0{\355]]\252\377\376\376\376\377\334\327\223\377\337\326J\377\343"
  "\326\12\377\352\352\343\377\377\377\377\377ll\250\377\0\0g\377\0\0f\344\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\25\24i\340\217\213Y\377\327\3150\377\366\360\225\377"
  "\331\316'\377\356\340\4\377\312\302?\377\255\247A\377=::\377\0\0d\377\0\0"
  "c\342\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0'%U\345\224\213\7\377\260\245\3\377\352\336\40"
  "\377\334\320\24\377\341\323\4\377\266\254\5\377sl\3\377VQ3\377\0\0a\377\0"
  "\0_\343\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0u\3\0\0r\37263J\377@<\1\377\34\14\0\377u?\3\377"
  ")\1\1\377\6\5\0\377\177y7\377\10\10d\377\0\0]\377\0\0[\376\0\0[0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0[=\0\0n\377\10\10q\377\236\231n\377\254V\5\377\323\10\2\377\313\33\2"
  "\377\234\220=\377\366\365\356\377\362\362\367\377\243\243\304\377**s\377"
  "\0\0W\262\0\0S\1\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\20\24\0\0S\32411\203\377\326\326\347\377\376\376\376\377\344"
  "\343\307\377\306\274f\377\313\310\225\377\370\370\370\377\376\376\376\377"
  "\376\376\376\377\376\376\376\377\370\370\372\37711\200\377\0\0^\315\0\0\\"
  "E\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0A>\0\0c\311\0\0e\36566p\377\360"
  "\360\366\377\376\376\376\377\376\376\376\377\376\376\376\377\376\376\376"
  "\377\376\376\376\377\376\376\376\377\376\376\376\377\376\376\376\377\376"
  "\376\376\377\376\376\376\377{{\247\377\0\0n\377\0\0e\367\0\0P:\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0I4\0\0z\366\0\0o\377\26\26U\377\346\346\357\377\376\376"
  "\376\377\376\376\376\377\376\376\376\377\376\376\376\377\376\376\376\377"
  "\376\376\376\377\376\376\376\377\376\376\376\377\376\376\376\377\376\376"
  "\376\377\376\376\376\377jj\236\377\0\0j\377\0\0d\377\0\0X\331\0\0""0\14\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0i\252\0\0x\377\0\0^\377\245\245\274\377\376\376\376\377"
  "\376\376\376\377\376\376\376\377\376\376\376\377\376\376\376\377\376\376"
  "\376\377\376\376\376\377\376\376\376\377\376\376\376\377\376\376\376\377"
  "\376\376\376\377\337\337\345\377\20\20n\377\0\0e\377\0\0`\377\0\0\\\377\0"
  "\0G\203\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0d\266\0\0m\377,,e\377\374\374\375\377\376\376\376"
  "\377\376\376\376\377\376\376\376\377\376\376\376\377\376\376\376\377\376"
  "\376\376\377\371\371\371\377gg\240\377((\177\377\227\227\266\377\303\303"
  "\321\377!!w\377\0\0g\377\0\0b\377\0\0\\\377\0\0W\377\0\0N\355\0\0)\15\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0""7a\0\0W\377\223\223\253\377\376\376\376\377\376\376\376\377\375"
  "\375\375\377\376\376\376\377\376\376\376\377\376\376\376\377\376\376\376"
  "\377\222\222\271\377\0\0\177\377\0\0y\377\1\1i\377\2\2m\377\0\0i\377\0\0"
  "c\377\0\0^\377\0\0X\377\0\0S\377\0\0M\377\0\0@Z\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\40\201"
  "\341\341\354\377\376\376\376\377\376\376\376\377\376\376\376\377\376\376"
  "\376\377\376\376\376\377\376\376\376\377\376\376\376\377II\221\377\0\0{\377"
  "\0\0u\377\0\0p\377\0\0j\377\0\0e\377\0\0_\377\0\0Z\377\0\0T\377\0\0O\377"
  "\0\0I\377\0\0/e\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0""99c\213\376\376\376\377\376\376\376\377\376"
  "\376\376\377\376\376\376\377\376\376\376\377\376\376\376\377\376\376\376"
  "\377\376\376\376\377PP\224\377\0\0w\377\0\0q\377\0\0l\377\0\0f\377\0\0a\377"
  "\0\0[\377\0\0V\377\0\0P\377\0\0K\377\0\0>\377\0\0$\40\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0+(\1\37\227\214\2x\236"
  "\224%\333\303\274u\377\343\342\335\377\376\376\376\377\376\376\376\377\376"
  "\376\376\377\376\376\376\377\376\376\376\377\376\376\376\377\241\241\274"
  "\377\0\0r\377\0\0m\377\0\0h\377\0\0b\377\0\0]\377\0\0W\377\0\0R\377\0\0M"
  "\377\33\33Y\377--^\377\0\0""6F\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\265\250\3\317\326\305\3\377\310\270\3\377"
  "\301\260\3\377\274\254\13\377\303\277\236\377\376\376\376\377\376\376\376"
  "\377\376\376\376\377\376\376\376\377\376\376\376\377\375\375\375\377\212"
  "\212\256\377QQ\221\377PP\212\377##j\377\0\0O\377\12\12P\37766l\377\205\205"
  "\240\377\356\356\360\377\223\223\253\377\0\0""1c\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\"\37\0\36\340\316\4\376\354\327"
  "\4\377\353\326\4\377\353\324\4\377\312\266\3\377\266\243\5\377\310\306\265"
  "\377\375\375\375\377\375\375\375\377\375\375\375\377\375\375\375\377\375"
  "\375\375\377\375\375\375\377\375\375\375\377\375\375\375\377\375\375\375"
  "\377\375\375\375\377\375\375\375\377\375\375\375\377\375\375\375\377\375"
  "\375\375\377\236\236\255\377\0\0+c\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0rh\2R\354\326\4\377\353\325\4\377\353\323\4\377"
  "\352\322\4\377\352\320\4\377\312\263\3\377\242\222\36\377\353\353\353\377"
  "\375\375\375\377\375\375\375\377\375\375\375\377\375\375\375\377\375\375"
  "\375\377\375\375\375\377\375\375\375\377\375\375\375\377\375\375\375\377"
  "\375\375\375\377\375\375\375\377\375\375\375\377\375\375\375\377\213\213"
  "\232\377\0\0\40\330\0\0\37^\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0*&\0\40\327\302\3\373\352\322\4\377\352\321\4\377\352\317\4\377"
  "\351\316\4\377\351\314\4\377\323\270\3\377\265\261\230\377\357\357\357\377"
  "\334\334\334\377\375\375\375\377\375\375\375\377\375\375\375\377\375\375"
  "\375\377\375\375\375\377\375\375\375\377\375\375\375\377\375\375\375\377"
  "\375\375\375\377\375\375\375\377\377\377\377\377>>T\377\0\0\36\377\0\0\37"
  "M\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\241\220"
  "\3\225\352\320\4\377\351\316\4\377\351\315\4\377\351\313\4\377\350\312\4"
  "\377\350\310\4\377\267\250L\377\336\336\336\377ddd\377\376\376\376\377\375"
  "\375\375\377\375\375\375\377\375\375\375\377\375\375\375\377\375\375\375"
  "\377\375\375\375\377\375\375\375\377\375\375\375\377\376\376\376\377\377"
  "\377\377\377VVj\377\0\0\36\321\0\0\37\3\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\17\15\0\14\302\252\3\320\351\314\4\377\350"
  "\312\4\377\350\310\4\377\350\307\4\377\347\306\4\377\271\240\26\377\375\375"
  "\375\377\326\326\326\377\323\323\323\377\374\374\374\377\375\375\375\377"
  "\375\375\375\377\375\375\375\377\375\375\375\377\375\375\375\377\375\375"
  "\375\377\375\375\375\377\377\377\377\377\377\377\377\377\273\273\277\375"
  "\4\3\31:\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0OE\1\30\277\246\3\312\350\307\4\377\347\306\4\377\347\304"
  "\4\377\347\303\4\377\316\267;\377\375\375\375\377\375\375\375\377\364\364"
  "\364\377\300\300\300\377\375\375\375\377\375\375\375\377\375\375\375\377"
  "\375\375\375\377\375\375\375\377\376\376\376\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\315\302\250\377\242v\2\3479)\1""5\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\0"
  "\10\265\247W\273\314\260\22\376\346\302\4\377\314\254\7\377\326\320\263\377"
  "\375\375\375\377\375\375\375\377\375\375\375\377\374\374\374\377\375\375"
  "\375\377\376\376\376\377\376\376\376\377\376\376\376\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\364\364\364\377\255\213"
  "1\377\336\257\3\377\236s\2\314\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\2\224\224\223N\210\201"
  "`\223\244\241\224\233\237\236\234o\223\223\247\212\272\272\306\324\322\322"
  "\331\374\370\370\371\377\366\366\366\377\275\275\277\377\372\372\372\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\312\310"
  "\302\377\243\2042\377\334\265\3\377\330\262\2\377\231p\2\276\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0+\7\0\0&"
  "\34\0\0#\40\0\0\36\40>>>I\177zk\253\256\230`\377\254\223R\377\323\260\13"
  "\377\325\251\4\377\330\262\2\377\342\271\3\376\316\226\3\366E2\1^\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1gK\1Y\233q\2|\240u\2\365\322\247"
  "\3\377\333\255\3\377\232p\2\365yX\2x\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\26\22\15\0""8O:\1@.!\0!\0\0\0"
  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
};

} // namespace openmsx
