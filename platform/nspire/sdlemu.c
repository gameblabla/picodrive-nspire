/*
	sdlemu.c - based on platform/linux/gp2x.c

	(c) Copyright 2006 notaz, All rights reserved.
	Free for non-commercial use.

	For commercial use, separate licencing terms must be obtained.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "n2DLib.h"

#include "../common/emu.h"

#include "sdlemu.h"

void *sdl_screen; // working buffer 320*230*2 + 320*2
static int current_bpp = 16;

void sdl_video_flip_320(void);

void sdl_init(void)
{
	struct {
		int x;
		int y;
		void (*p)(void);
	} vm[1] = {
			{320, 240, sdl_video_flip_320},
	};

	initBuffering();
	clearBufferB();
	updateScreen();

	/*screen = SDL_SetVideoMode(surfacewidth, surfaceheight, 16, SDL_SWSURFACE);*/
	/*menu_screen = SDL_CreateRGBSurfaceFrom(sdl_screen, 320, 240, 16, 640, 0xF800, 0x7E0, 0x1F, 0);*/
	sdl_screen = malloc((320*240*2 + 320*2));
	memset(sdl_screen, 0, (320*240*2 + 320*2));
}

void sdl_deinit(void)
{
	deinitBuffering();
	if (sdl_screen) free(sdl_screen);
}

/* video */
void sdl_video_flip_320(void)
{
	int i;
	unsigned short *fbp = (unsigned short *)BUFF_BASE_ADDRESS;
	unsigned short *pixels = sdl_screen;

	for (i =(320*240); i--;) 
	{
		*fbp++ = *pixels++;
	}
}

void sdl_video_flip(void)
{
	sdl_video_flip_320();
	updateScreen();
}

void sdl_menu_flip(void)
{
	updateScreen();
}

void sdl_clear_screen(void)
{
	clearBufferB();
}

void sdl_video_changemode(int bpp)
{
	current_bpp = 16;
}

void sdl_memcpy_buffers(int buffers, void *data, int offset, int len)
{
	if ((char *)sdl_screen + offset != data)
		memcpy((char *)sdl_screen + offset, data, len);
}

void sdl_memcpy_all_buffers(void *data, int offset, int len)
{
	memcpy((char *)sdl_screen + offset, data, len);
}


void sdl_memset_all_buffers(int offset, int byte, int len)
{
	memset((char *)sdl_screen + offset, byte, len);
}

void sdl_pd_clone_buffer2(void)
{
	memset(sdl_screen, 0, 320*240*2);
}

static unsigned long button_states = 0;
unsigned long sdl_joystick_read(int allow_usb_joy)
{
	static unsigned char button_state[12], button_time[12];
	
	int i;
	int pad;
	for(i=0;i<sizeof(button_state);i++)
	{
		switch (i)
		{
			case 0:
			pad = isKeyPressed(KEY_NSPIRE_UP);
			break;
			case 1:
			pad = isKeyPressed(KEY_NSPIRE_DOWN);
			break;
			case 2:
			pad = isKeyPressed(KEY_NSPIRE_LEFT);
			break;
			case 3:
			pad = isKeyPressed(KEY_NSPIRE_RIGHT);
			break;
			case 4:
			pad = isKeyPressed(KEY_NSPIRE_CTRL);
			break;
			case 5:
			pad = isKeyPressed(KEY_NSPIRE_SHIFT);
			break;
			case 6:
			pad = isKeyPressed(KEY_NSPIRE_VAR);
			break;
			case 7:
			pad = isKeyPressed(KEY_NSPIRE_DEL);
			break;
			case 8:
			pad = isKeyPressed(KEY_NSPIRE_TAB);
			break;
			case 9:
			pad = isKeyPressed(KEY_NSPIRE_MENU);
			break;
			case 10:
			pad = isKeyPressed(KEY_NSPIRE_ENTER);
			break;
			case 11:
			pad = isKeyPressed(KEY_NSPIRE_ESC);
			break;
		}
		
		switch (button_state[i])
		{
			case 0:
				if (pad)
				{
					button_state[i] = 1;
					button_time[i] = 0;
				}
			break;
			
			case 1:
				button_time[i] = button_time[i] + 1;
				
				if (button_time[i] > 0)
				{
					button_state[i] = 2;
					button_time[i] = 0;
				}
			break;
			
			case 2:
				if (!(pad))
				{
					button_state[i] = 3;
					button_time[i] = 0;
				}
			break;
			
			case 3:
				button_time[i] = button_time[i] + 1;
				
				if (button_time[i] > 1)
				{
					button_state[i] = 0;
					button_time[i] = 0;
				}
			break;
		}
		
	}
	
	if (button_state[0] == 3)
	{
		button_states &= ~(GP2X_UP);
	}
	else if (button_state[0] > 0)
	{
		button_states &= ~(GP2X_UP);
		button_states |= (GP2X_UP);
	}
	
	if (button_state[1] == 3)
	{
		button_states &= ~(GP2X_DOWN);
	}
	else if (button_state[1] > 0)
	{
		button_states &= ~(GP2X_DOWN);
		button_states |= (GP2X_DOWN);
	}
	
	if (button_state[2] == 3)
	{
		button_states &= ~(GP2X_LEFT);
	}
	else if (button_state[2] > 0)
	{
		button_states &= ~(GP2X_LEFT);
		button_states |= (GP2X_LEFT);
	}
	
	if (button_state[3] == 3)
	{
		button_states &= ~(GP2X_RIGHT);
	}
	else if (button_state[3] > 0)
	{
		button_states &= ~(GP2X_RIGHT);
		button_states |= (GP2X_RIGHT);
	}
		
	if (button_state[4] == 3)
	{
		button_states &= ~(GP2X_B);
	}
	else if (button_state[4] > 0)
	{
		button_states &= ~(GP2X_B);
		button_states |= (GP2X_B);
	}
	
	if (button_state[5] == 3)
	{
		button_states &= ~(GP2X_X);
	}
	else if (button_state[5] > 0)
	{
		button_states &= ~(GP2X_X);
		button_states |= (GP2X_X);
	}
	
	if (button_state[6] == 3)
	{
		button_states &= ~(GP2X_Y);
	}
	else if (button_state[6] > 0)
	{
		button_states &= ~(GP2X_Y);
		button_states |= (GP2X_Y);
	}
	
	if (button_state[7] == 3)
	{
		button_states &= ~(GP2X_A);
	}
	else if (button_state[7] > 0)
	{
		button_states &= ~(GP2X_A);
		button_states |= (GP2X_A);
	}
	
	/*if (button_state[8] == 3)
	{
		button_states &= ~(GP2X_L);
	}
	else if (button_state[8] == 1)
	{
		button_states &= ~(GP2X_L);
		button_states |= (GP2X_L);
	}
	
	if (button_state[9] == 3)
	{
		button_states &= ~(GP2X_R);
	}
	else if (button_state[9] == 1)
	{
		button_states &= ~(GP2X_R);
		button_states |= (GP2X_R);
	}*/
	
	if (button_state[10] == 3)
	{
		button_states &= ~(GP2X_START);
	}
	else if (button_state[10] > 0)
	{
		button_states &= ~(GP2X_START);
		button_states |= (GP2X_START);
	}
	
	if (button_state[11] == 3)
	{
		button_states &= ~(GP2X_SELECT);
	}
	else if (button_state[11] > 0)
	{
		button_states &= ~(GP2X_SELECT);
		button_states |= (GP2X_SELECT);
	}
	 

	/*SDL_Event event;

	if(SDL_PollEvent(&event)) {
		if(event.type == SDL_KEYUP || event.type == SDL_KEYDOWN) {
			SETKEY(SDLK_UP, GP2X_UP);
			SETKEY(SDLK_DOWN, GP2X_DOWN);
			SETKEY(SDLK_LEFT, GP2X_LEFT);
			SETKEY(SDLK_RIGHT, GP2X_RIGHT);
			SETKEY(SDLK_LCTRL, GP2X_B); // dingoo A
			SETKEY(SDLK_LSHIFT, GP2X_X); // dingoo B
			SETKEY(SDLK_SPACE, GP2X_Y); // dingoo X
			SETKEY(SDLK_BACKSPACE, GP2X_A); // dingoo Y
			SETKEY(SDLK_TAB, GP2X_L);
			SETKEY(SDLK_MENU, GP2X_R);
			SETKEY(SDLK_ESCAPE, GP2X_SELECT);
			SETKEY(SDLK_RETURN, GP2X_START);
		}
	}*/

	return button_states;
}


/* misc */
void spend_cycles(int c)
{
	/*usleep(c/200);*/
}

/* lprintf stub */
void lprintf(const char *fmt, ...)
{
	va_list vl;

	va_start(vl, fmt);
	vprintf(fmt, vl);
	va_end(vl);
}
