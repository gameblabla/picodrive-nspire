/*
    Platform dependant defines
*/

#if      defined(_TINSPIRE)
    #include "../nspire/sdlemu.h"
    #include "../nspire/emu.h"
    #include "../nspire/menu.h"
    #define SCREEN_WIDTH 320
    #define SCREEN_BUFFER sdl_screen

#elif      defined(__SDL__)
    #include "../sdl/sdlemu.h"
    #define SCREEN_WIDTH 320
    #define SCREEN_BUFFER sdl_screen
#elif   defined(__GP2X__)
    #include "../gp2x/gp2x.h"
    #define SCREEN_WIDTH 320
    #define SCREEN_BUFFER gp2x_screen
#elif defined(__GIZ__)
    #include "../gizmondo/giz.h"
    #define SCREEN_WIDTH 321
    #define SCREEN_BUFFER giz_screen
#elif defined(PSP)
    #include "../psp/psp.h"
    #define SCREEN_WIDTH 512
    #define SCREEN_BUFFER psp_screen
#endif
