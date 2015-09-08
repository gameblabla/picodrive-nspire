/*
	main.c - based on platform/gp2x/main.c

	(c) Copyright 2006 notaz, All rights reserved.
	Free for non-commercial use.

	For commercial use, separate licencing terms must be obtained.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "sdlemu.h"
#include "menu.h"
#include "../common/menu.h"
#include "../common/emu.h"
#include "emu.h"
#include "version.h"

char *ext_menu, *ext_state;
extern int select_exits;
extern char PicoConfigFile[128];

int pico_load(char* romname)
{
	/*g_argv = argv;*/

	emu_ReadConfig(0, 0);
	sdl_init();

	emu_Init();
	menu_init();

	engineState = PGS_Menu;
	
	/*sprintf(argv[0], "/documents/flicky.md.tns");*/

	strncpy(romFileName, romname, PATH_MAX);
	romFileName[PATH_MAX-1] = 0;
	FILE *f = fopen(romFileName, "rb");
	if (f) fclose(f); 
	f = NULL;
	
	engineState = PGS_ReloadRom;

	/*if (argc > 1)*/
	/*parse_cmd_line(argc, argv);*/

	for (;;)
	{
		switch (engineState)
		{
			case PGS_Menu:
				menu_loop();
				break;

			case PGS_ReloadRom:
				if (emu_ReloadRom())
					engineState = PGS_Running;
				else {
					printf("PGS_ReloadRom == 0\n");
					engineState = PGS_Menu;
				}
				break;

			case PGS_RestartRun:
				engineState = PGS_Running;

			case PGS_Running:
				emu_Loop();
				break;

			case PGS_Quit:
				goto endloop;

			default:
				printf("engine got into unknown state (%i), exitting\n", engineState);
				goto endloop;
		}
	}

	endloop:

	emu_Deinit();
	sdl_deinit();

	return 0;
}
