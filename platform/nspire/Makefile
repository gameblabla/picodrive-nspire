
# settings
#use_musashi = 1
use_fame = 1
#use_mz80 = 1

DEFINC = -I../.. -I. -D__SDL__

GCC = nspire-gcc
AS = nspire-gcc

COPT_COMMON = -Dndlib -Ofast -fomit-frame-pointer -fdata-sections -ffunction-sections -marm -march=armv5te -mtune=arm926ej-s -flto
COPT = $(COPT_COMMON) $(PROFILE)

# libraries
LDFLAGS += -lSDL -lm -lz -flto -Wl,--as-needed -Wl,--gc-sections

# frontend
OBJS += main.o menu.o emu.o sdlemu.o gui.o n2DLib.o

# common
OBJS += platform/common/emu.o platform/common/menu.o

# Pico
OBJS += Pico/Area.o Pico/Cart.o Pico/Memory.o Pico/Misc.o Pico/Pico.o Pico/Sek.o \
		Pico/VideoPort.o Pico/Draw2.o Pico/Draw.o Pico/Patch.o

# Pico - CD
#OBJS += Pico/cd/Pico.o Pico/cd/Memory.o Pico/cd/Sek.o Pico/cd/LC89510.o \
#Pico/cd/cd_sys.o Pico/cd/cd_file.o Pico/cd/gfx_cd.o \
#Pico/cd/Area.o Pico/cd/Misc.o Pico/cd/pcm.o Pico/cd/buffering.o

# zlib
OBJS += zlib/gzio.o zlib/inffast.o zlib/inflate.o zlib/inftrees.o zlib/trees.o \
zlib/deflate.o zlib/crc32.o zlib/adler32.o zlib/zutil.o zlib/compress.o zlib/uncompr.o

# unzip
OBJS += unzip/unzip.o unzip/unzip_stream.o

# CPU cores
ifeq "$(use_musashi)" "1"
DEFINC += -DEMU_M68K
OBJS += cpu/musashi/m68kops.o cpu/musashi/m68kcpu.o
endif
ifeq "$(use_fame)" "1"
DEFINC += -DEMU_F68K
OBJS += cpu/fame/famec.o
endif

# z80
ifeq "$(use_mz80)" "1"
DEFINC += -D_USE_MZ80
OBJS += cpu/mz80/mz80.o
else
DEFINC += -D_USE_CZ80
OBJS += cpu/cz80/cz80.o
endif

vpath %.c = ../..
vpath %.s = ../..

DIRS = bin platform platform/common platform/common/helix platform/common/helix/real \
	Pico Pico/cd Pico/sound zlib unzip \
	cpu cpu/musashi cpu/fame cpu/mz80 cpu/cz80

all: mkdirs PicoDrive gen zip

zip:
	zip -r picodrive-nspire.zip picodrive.tns README.md AUTHORS COPYING

gen:
	mv bin/PicoDrive ./pico
	genzehn --input pico --output pico.t --compress
	make-prg pico.t picodrive.tns
	rm pico.t
	rm pico 
	
clean: tidy
	@$(RM) bin/PicoDrive bin/PicoDrive.dge

tidy:
	$(RM) $(OBJS)
	make -C ../common/helix CROSS=nspire- X86=1 TARGET=helix_mp3.a clean
	#rm -rf $(DIRS)

PicoDrive : $(OBJS) 
	@echo ">>>" $@
	$(GCC) $(COPT) $^ -o bin/$@ $(LDFLAGS)
	#$(STRIP) bin/$@ -o bin/$@.dge

mkdirs:
	mkdir -p $(DIRS)

../../cpu/musashi/m68kops.c :
	@make -C ../../cpu/musashi

../common/helix/helix_mp3.a:
	make -C ../common/helix CROSS=nspire- X86=1 TARGET=helix_mp3.a CFLAGS="$(COPT_COMMON) -Ipub"

.c.o:
	@echo ">>>" $<
	$(GCC) $(COPT) $(DEFINC) -c $< -o $@

.s.o:
	@echo ">>>" $<
	$(AS)  $< -o $@

cpu/fame/famec.o : ../../cpu/fame/famec.c ../../cpu/fame/famec_opcodes.h
