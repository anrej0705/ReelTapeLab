@ECHO OFF
gcc -m32 BIN2FM\main.c BIN2FM\utils.c -o BIN2FM.EXE
gcc -m32 FM2BIN\main.c FM2BIN\utils.c -o FM2BIN.EXE
gcc -m32 WAVCONV\main.c -o WAVCONV.EXE
gcc -m32 WAVHEAD\main.c  WAVHEAD\debug.c -o WAVHEAD.EXE
gcc -m32 WAVBIND\main.c -o WAVBIND.EXE