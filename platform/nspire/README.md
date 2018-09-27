PicoDrive for Ti Nspire CX.
=======================
Port to TI Nspire CX by gameblabla.

Right now, it's pretty much hacked up...
I had to make several modifications to make it work on Ti Nspire CX.

Basically, what i did :
- Removed Sega CD emulation. (Pointless, considering the TI Nspire CX's Nand of 100Mb)
- Removed sound emulation. (YM chip, SN chip etc...)
- Tried not to rely on Malloc, which suffers from memory leak on TI Nspire CX.

Picodrive is under a non-commercial clause because the copyright holders are being real assholes about it, ROFL.
There's nothing i can do, see COPYRIGHT.

It runs fullspeed on a non-overclocked TI Nspire CX with a frameskip of 2.
There's no point of overclocking because a overclocking of 266Mhz is not even fast
enough for a frameskip of 1 for most games.

6 Buttons games are not properly supported yet.
The buttons are mapped as follow :
Touchpad = Dpad
Ctrl = A
Shift = B
Var = C
