#include<locale.h>																																//Библиотека локализацй, нужна для русского языка в консоли
#include<stdbool.h>																																//Библиотека для работы с двоичными числам, C99
#include<stdint.h>																																//Бибилотека для работы с нестандартными числами uint8_t, uint16_t, uint32_t
#include<stdio.h>																																//Библиотека для работы с консолью, вывод в консоль и считывание с нее
#include<conio.h>																																//Бибилотека
#include<stdlib.h>																																//Бибилотека
#ifndef DEBUG_H_
#define DEBUG_H_
extern void printSampleDivide(float SamplesDivide);
extern void pringDebugMsg(int debugMsgNum, uint32_t firstParameter);
extern uint8_t FileHeaderMSG[44];																												//сюда переписывается заголовок для вывода в режим отладки
#endif
