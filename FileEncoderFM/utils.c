#include<stdint.h>
#include<stdio.h>
#include "utils.h"
inline uint32_t masrng(char* inputArr){
	for(uint32_t i=0;i<0xFFFFFFFF;i++)
	{if(inputArr[i]==EOF){return i;}}}
