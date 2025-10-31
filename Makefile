MCU ?= attiny88

AVRCC ?= avr-gcc
AVRCXX ?= avr-g++
AVRNM ?= avr-nm
AVROBJCOPY ?= avr-objcopy
AVROBJDUMP ?= avr-objdump

MCU_FLAGS = -mmcu=attiny88 -DF_CPU=8000000UL

SHARED_FLAGS = ${MCU_FLAGS} -I. -Os -Wall -Wextra -pedantic
SHARED_FLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
SHARED_FLAGS += -flto -mstrict-X

CFLAGS += ${SHARED_FLAGS} -std=c14
CXXFLAGS += ${SHARED_FLAGS} -std=c++14 -fno-rtti -fno-exceptions

ASFLAGS += ${MCU_FLAGS} -wA,--warn
LDFLAGS += -Wl,--gc-sections

#HEADERS  = $(wildcard src/*.h)
HEADERS =
ASFILES  = $(wildcard src/*.S)
CFILES   = $(wildcard src/*.c)
#CXXFILES = $(wildcard src/*.cpp)
CXXFILES = src/main.cpp src/HardwareDisplay.cpp src/Frame.cpp src/Coordinates.cpp src/Vector.cpp src/RocketGame.cpp
OBJECTS  = ${CFILES:src/%.c=build/%.o} ${CXXFILES:src/%.cpp=build/%.o} ${ASFILES:src/%.S=build/%.o}

all: build build/main.elf build/main.hex

build:
	mkdir -p build

build/%.hex: build/%.elf
	${AVROBJCOPY} -O binary -R .eeprom $< $@

build/%.eep: build/%.elf
	${AVROBJCOPY} -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O ihex $< $@

build/%.o: src/%.cpp #${HEADERS}
	${AVRCXX} ${CXXFLAGS} -o $@ $< -c -Wl,-Map=main.map,--cref

build/%.o: src/%.c #${HEADERS}
	${AVRCC} ${CFLAGS} -o $@ $< -c -Wl,-Map=main.map,--cref

build/main.elf: ${OBJECTS}
	${AVRCXX} ${CXXFLAGS} -o $@ $^ ${LDFLAGS}
	@echo
	@avr-size --format=avr --mcu=${MCU} $@

secsize: build/main.elf
	${AVROBJDUMP} -hw -j.text -j.bss -j.data $<

funsize: build/main.elf
	${AVRNM} --print-size --size-sort $<

clean:
	rm -rf build/

.PHONY: all secsize funsize
