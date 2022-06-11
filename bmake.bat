@ECHO OFF
gcc -m32 FileEncoderFM\main.c FileEncoderFM\utils.c -o BIN2FM.EXE
gcc -m32 StreamDecoderFM\main.c FileEncoderFM\utils.c -o FM2BIN.EXE
gcc -m32 wavConverter\exConverter\main.c -o WAVCONV.EXE
gcc -m32 wavConverter\exHeader\main.c  wavConverter\exHeader\debug.c -o WAVHEAD.EXE
gcc -m32 wavConverter\exStitcher\main.c -o WAVBIND.EXE