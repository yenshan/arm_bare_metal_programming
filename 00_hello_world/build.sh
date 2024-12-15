#!/bin/sh

CROSS_PATH=/opt/homebrew/bin/arm-none-eabi

$CROSS_PATH-as -mcpu=arm926ej-s -g startup.s -o startup.o
$CROSS_PATH-gcc -c -mcpu=arm926ej-s -g test.c -o test.o
$CROSS_PATH-gcc -c -mcpu=arm926ej-s -g serial.c -o serial.o
$CROSS_PATH-ld -T ld.scr test.o startup.o serial.o -o test.elf
$CROSS_PATH-objcopy -O binary test.elf test.bin
