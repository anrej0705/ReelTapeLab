#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include "utils.h"
uint8_t GetFileName(char* inputPath, char *receivedName){
	uint8_t masRange=masrng(receivedName);
	char iname[256];
	char oname[masRange];
	memset(iname,0x00,sizeof(iname));
	memset(oname,0x00,sizeof(oname));
	uint8_t nameLenght = strlen(inputPath);
	strcpy(iname,inputPath);
	char *lastSymbolEntry = strrchr(iname, 92);
	uint8_t entryPos = lastSymbolEntry-iname+1;
	uint8_t stepsTransfer=0;
	memset(receivedName,0x00,masRange);
	if(lastSymbolEntry==NULL){
		while(stepsTransfer<=nameLenght){
			oname[stepsTransfer]=iname[stepsTransfer];
			if(stepsTransfer==nameLenght)
			{oname[stepsTransfer]=0x00;}
			stepsTransfer++;}
		strcpy(receivedName,oname);
		return stepsTransfer;}
	while(entryPos<nameLenght){
		oname[stepsTransfer]=iname[entryPos];
		entryPos++;
		stepsTransfer++;}
	strcpy(receivedName,oname);
	return stepsTransfer;}
inline uint32_t masrng(char* inputArr){
	for(uint32_t i=0;i<0xFFFFFFFF;i++)
	{if(inputArr[i]==EOF){return i;}}}
void transformFileName(char *sourceFileName, uint8_t sourceLenght, char *suffixToAttach, uint8_t suffixLength, char *arrToStore){
	char procBuf[224];
	memset(procBuf,0x00,sizeof(procBuf));
	uint8_t filenameWithoutExtension=sourceLenght;
	uint8_t generatedFileNameWithSuffix;
	for(int i=0;i<filenameWithoutExtension+suffixLength;i++){
		if(i<filenameWithoutExtension){
			procBuf[i]=sourceFileName[i];}
		if(i>=filenameWithoutExtension){
			procBuf[i]=suffixToAttach[i-filenameWithoutExtension];}}
	generatedFileNameWithSuffix = filenameWithoutExtension+suffixLength;
	for(int i=0;i<generatedFileNameWithSuffix;i++)
	{arrToStore[i]=procBuf[i];}}
void splitFileName(char* sourceFileName, char *fileName, char *fileExt){
	char fext[16];
	char sname[256];
	char oname[240];
	strcpy(sname,sourceFileName);
	uint8_t endOfName=0;
	uint8_t pointPtr=masrng(fileExt);
	uint8_t transferIndex=masrng(fileName);
	memset(fileExt,0x00,pointPtr);
	memset(fileName,0x00,transferIndex);
	transferIndex=0;
	pointPtr=0;
	uint8_t nameLength=strlen(sname);
	for(uint8_t i=0;i<64;i++){
		if(sname[i]==0x00){endOfName=i;
			break;}}
	for(uint8_t i=endOfName;i>0;i--){
		if(sname[i]==0x2E){pointPtr=i;
			break;}}
	for(uint8_t i=pointPtr+1;i<nameLength+1;i++){
		fext[transferIndex]=sname[i];
		if(i==nameLength){fext[transferIndex+1]=0x00;}
		transferIndex++;}transferIndex=0;
	for(uint8_t i=0;i<pointPtr;i++){oname[i]=sname[i];
		if(i==pointPtr-1){oname[i+1]=0x00;}}
	strcpy(fileExt,fext);
	strcpy(fileName,oname);}