/*
	sdlemu.h - based on platform/gp2x/gp2x.h

	(c) Copyright 2006 notaz, All rights reserved.
	Free for non-commercial use.

	For commercial use, separate licencing terms must be obtained.

*/

#ifndef __SDLEMU_H__
#define __SDLEMU_H__

#include <stdint.h>

void sdl_init(void);
void sdl_deinit(void);

/* video */
void sdl_video_flip(void);
void sdl_menu_flip(void);
void sdl_clear_screen(void);
void sdl_video_changemode(int bpp);
void sdl_video_setpalette(int *pal, int len);
void sdl_video_RGB_setscaling(int ln_offs, int W, int H);
void sdl_memcpy_buffers(int buffers, void *data, int offset, int len);
void sdl_memcpy_all_buffers(void *data, int offset, int len);
void sdl_memset_all_buffers(int offset, int byte, int len);
void sdl_pd_clone_buffer2(void);

/* sound */
void sdl_start_sound(int rate, int bits, int stereo);
void sdl_sound_write(void *buff, int len);
void sdl_sound_volume(int l, int r);

/* joy */
unsigned long sdl_joystick_read(int allow_usb_joy);

extern uint16_t *sdl_screen;
extern int sdl_video_scaling;

enum  { GP2X_UP=1<<6,      GP2X_LEFT=1<<5,      GP2X_DOWN=1<<27, GP2X_RIGHT=1<<18,
        GP2X_START=1<<16,  GP2X_SELECT=1<<17,   GP2X_L=1<<14,    GP2X_R=1<<15,
        GP2X_A=1<<2,       GP2X_B=1<<0,         GP2X_X=1<<1,     GP2X_Y=1<<19,
        GP2X_VOL_UP=1<<20, GP2X_VOL_DOWN=1<<21, GP2X_PUSH=1<<29 };        

#endif
 
