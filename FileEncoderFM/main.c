#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include "utils.h"
#define bufferLength		32768
#define headerLength		4096
#define fileBlockSize		255
#define StartMsg			"v0.0.2 build 11\n"
#define codePageInfo 		"Задана кодовая таблица приложения OEM CP-866\n"
char fileBuffer[256];
char fileName[128];
char tempName[9]="generated";
char headerNameSuffix[11]="_header.dat";
char headerBodySuffix[9]="_body.dat";
char headerConvSuffix[12]="_conv_FM.wav";
char metadataTag[15]="FM>METADATA_MT>";
char fileprop[15]="FM>FILEPROP_FP>";
char fileSign[4]="FIL>";
char codeMethod[3]="FM>";
char filepropFileName[12]="FP>FILENAME>";
char filepropFileSize[12]="FP>FILESIZE>";
char filepropFileExtn[12]="FP>FILEEXTN>";
char filepropFileCrcs[12]="FP>CHECKSUM>";
char metadataFileEnds[12]="FM>ENDOFFIL>";
char metadataBlckCont[12]="MT>BLCKCONT>";
char metadataBckSzDec[12]="MT>BCKSZDEC>";
char metadataBlckLstS[12]="MT>BCKLSTSZ>";
char binfdataBckSzEnc[8]="BI>BSCN>";
char binfdataBlckCr16[8]="BI>CR16>";
char binfdataBlckCr32[8]="BI>CR32>";
char binfdataBlckBlck[8]="BI>BLCK>";
char fileNameHdrDat[64];
char fileNameBodDat[64];
char fileNameTgtDat[64];
char valBuffer[4];
char *wordFilenameSource="FSRC";
char *wordFilenameBody="FBOD";
char *wordFilename="FNAM";
char *wordFilenameTarget="FTGT";
char *wordSrcFilenameEnd=">FSND";
char *wordNameFilenameEnd=">FNND";
char *wordBodyFilenameEnd=">FBND";
char *wordTargFilenameEnd=">FTND";
FILE* FIn;
FILE* FSet;
FILE* FOut;
float modOfDiv;
uint8_t SoundChannels;
uint8_t BitDepth;
uint8_t nullTerminator=0x46;
uint16_t carrierFreq=12000;
uint16_t wavSampleRate=48000;
uint32_t summaryPacketLength;
uint32_t roundedVal=0;
uint32_t numberOfIterations;
bool binArr[8];
uint8_t outArr[256];
uint8_t dummyArr[2]={0x00,0x00};
void createInputArr(bool *appPtr, uint8_t sizeArr, uint8_t inputByte);
void storeStructToFile(void);
uint8_t createDataPacket(bool *arrIn, uint8_t *arrOut, uint8_t packetNumber, uint8_t analogLevel);
uint16_t createBit(uint8_t *inputMas, uint16_t startAdr, uint16_t endAdr, uint8_t charToFill, uint8_t bitPauseRange);
uint16_t writeCalibrate(bool overrideStruct, uint8_t lengthDetector, uint8_t lengthX, uint8_t lengthNotX);
uint32_t appendArray(uint8_t *arrToAppend, uint32_t stopAddr, uint32_t startAddr, char *collectStr);
uint8_t *bufferMas;
uint8_t *headerBlk;
uint8_t *lasstBufferMas;
struct pulseTimings{
	uint8_t bitSeparatorTiming;
	uint8_t pkgSeparatorTiming;
	uint8_t logTrueTiming;
	uint8_t logElseTiming;
	uint8_t tSP;
	uint8_t tTR;
	uint8_t tFL;
	uint8_t tSB;
} pulsTim;
struct CRCBitDepthKit{
	uint8_t CRC8Summ;
	uint16_t CRC16Summ;
	uint32_t CRC32Summ;
	uint64_t CRC64Summ;
} CRCKit;
struct analogLvl{
	uint8_t signalLevel;
	uint8_t silenceLevel;
} aLvl;
struct calibrationArea{
	uint8_t DetectorPulseRange;
	uint8_t logXPulseRange;
	uint8_t logNotXPulseRange;
} cArea;
struct fileDetails{
	uint8_t tableVer;
	uint8_t fileSrc[255];
	uint8_t fileName[247];
	uint8_t fileExt[8];
	uint32_t srcFileSize;
} fInf;
struct fileBlockInfo{
	uint16_t packetDSize;
	uint16_t lastBlockSize;
	uint32_t blocksCnt;
} bInf;
struct blockHead{
	uint16_t blockCRC16;
	uint32_t blockCRC32;
	uint32_t blockSize;
} bHed;
int main(int argc, char* argv[])
{
	unsigned int codePageNum;
	char temp;
	char temp2[247];
	char temp3[56];
	char temp4[56];
	char fileInfo[333];
	char fileMeta[59];
	char blockInfo[24];
	memset(fileMeta,0x00,sizeof(fileMeta));
	memset(blockInfo,0x00,sizeof(blockInfo));
	uint8_t pRange=0;
	uint32_t writeIterations=0;
	uint32_t transferIndex=0;
	uint32_t arrIndex=0;
	uint32_t iterations=0;
	uint32_t stopIteration;
	uint32_t fileSize=0;
	uint32_t inputFileReadIndex=0;
	bool setOutCodePageStatus;
	bool setInCodePageStatus;
	fInf.tableVer=0x01;
	CRCKit.CRC8Summ=0xFF;
	CRCKit.CRC16Summ=0xFFFF;
	CRCKit.CRC32Summ=0xFFFFFFFF;
	CRCKit.CRC64Summ=0xFFFFFFFFFFFFFFFF;
	bHed.blockCRC16=0xFFFF;
	pulsTim.bitSeparatorTiming=1;
	pulsTim.pkgSeparatorTiming=4;
	pulsTim.logTrueTiming=1;
	pulsTim.logElseTiming=2;
	aLvl.signalLevel=0xFF;
	cArea.DetectorPulseRange=0x07;
	cArea.logXPulseRange=0x07;
	cArea.logNotXPulseRange=0x07;
	SoundChannels=1;
	BitDepth=8;
	headerBlk = malloc(headerLength);	
	bufferMas = malloc(bufferLength);				//буфер под пачку семплов генерируемых из 256 байт данных. Должно хватить
	memset(bufferMas,0x00,sizeof(bufferMas));
	codePageNum = GetConsoleOutputCP();
	printf("Current console output codepage: %d\n",codePageNum);
	codePageNum = GetConsoleCP();
	printf("Current console input codepage: %d\n",codePageNum);
	if(codePageNum!=866){
		setOutCodePageStatus=SetConsoleOutputCP(866);
		setInCodePageStatus=SetConsoleCP(866);
		if(setOutCodePageStatus&&setInCodePageStatus != 0)
		{printf(codePageInfo);}}
	else{printf("Переключение кодовой страницы не требуется\n");}
	printf("Преобразователь форматов BIN->WAV(дискретная FM модуляция) \n");
	printf(StartMsg);
	printf("Ну чо пацаны, я слетел с шараги так что теперь прога быстрее будет писаться. \nВсем гулям ку остальным соболезную\n");
	FIn=fopen(argv[1],"rb");
	if(!FIn&&argc<3){
		printf("Не найден файл %s, или не указаны аргументы\n",argv[1]);
		exit(1);}
	transformFileName(tempName, sizeof(tempName), headerNameSuffix, sizeof(headerNameSuffix), fileNameHdrDat);
	transformFileName(tempName, sizeof(tempName), headerBodySuffix, sizeof(headerBodySuffix), fileNameBodDat);
	transformFileName(tempName, sizeof(tempName), headerConvSuffix, sizeof(headerConvSuffix), fileNameTgtDat);
	FOut=fopen(fileNameBodDat, "wb");
	fseek(FIn,0,SEEK_END);
	fileSize=ftell(FIn);
	//printf("Размер входного файла: %d байт\n",fileSize);
	pulsTim.tSP=(wavSampleRate/carrierFreq)*pulsTim.pkgSeparatorTiming;
	pulsTim.tTR=(wavSampleRate/carrierFreq)*pulsTim.logTrueTiming;
	pulsTim.tFL=(wavSampleRate/carrierFreq)*pulsTim.logElseTiming;
	pulsTim.tSB=(wavSampleRate/carrierFreq)*pulsTim.bitSeparatorTiming;
	printf("Тайминг стоп-бита: %d\nТайминг лог.0: %d\nТайминг лог.1: %d\nТайминг паузы между отправкой битов: %d\n",pulsTim.tSP,pulsTim.tFL,pulsTim.tTR,pulsTim.tSB);
	printf("f(дискр)=%d\nf(несущ)=%d\n",wavSampleRate,carrierFreq);
	modOfDiv=fmod(fileSize, sizeof(fileBuffer));
	//printf("Остаточный пакет байтов: %f\n",modOfDiv);
	roundedVal=round(modOfDiv);
	//printf("Округленное значение: %d\n", roundedVal);
	numberOfIterations=(fileSize-modOfDiv)/sizeof(fileBuffer);
	printf("Суммарное количество блоков размером %d байт на запись: %d\n",sizeof(fileBuffer),numberOfIterations);
	lasstBufferMas=malloc(roundedVal);
	if(lasstBufferMas!=NULL)
	{printf("Задан размер буфера под остаток в %d байт\n",roundedVal+1);}
	stopIteration=sizeof(fileBuffer);
	fseek(FOut,0,SEEK_SET);
	transferIndex=writeCalibrate(1,31,31,31);
	fwrite(bufferMas,1,transferIndex,FOut);
	GetFileName(argv[1],fInf.fileSrc);
	splitFileName(fInf.fileSrc, fInf.fileName, fInf.fileExt);
	fseek(FOut,transferIndex,SEEK_SET);
	transferIndex=transferIndex+sizeof(fileInfo);
	transferIndex=0;
	memset(fileInfo,0x00,sizeof(fileInfo));
	arrcop(fileSign,0,fileInfo,4);
	fileInfo[4]=fInf.tableVer;
	arrcop(codeMethod,5,fileInfo,3);
	arrcop(fileprop,8,fileInfo,15);
	arrcop(filepropFileName,23,fileInfo,12);
	arrcop(fInf.fileSrc,35,fileInfo,247);
	intmas(fileSize,4,valBuffer);
	arrcop(filepropFileSize,281,fileInfo,12);
	arrcop(valBuffer,293,fileInfo,4);
	arrcop(filepropFileExtn,297,fileInfo,12);
	arrcop(fInf.fileExt,309,fileInfo,8);
	arrcop(filepropFileCrcs,317,fileInfo,12);
	intmas(CRCKit.CRC32Summ,4,valBuffer);
	arrcop(valBuffer,329,fileInfo,332);
	arrcop(metadataTag,0,fileMeta,15);
	arrcop(metadataBlckCont,15,fileMeta,12);
	intmas(numberOfIterations+1,4,valBuffer);
	arrcop(valBuffer,27,fileMeta,4);
	arrcop(metadataBckSzDec,31,fileMeta,12);
	intmas(fileBlockSize,2,valBuffer);
	arrcop(valBuffer,43,fileMeta,2);
	arrcop(metadataBlckLstS,45,fileMeta,12);
	memset(valBuffer,0x00,sizeof(valBuffer));
	intmas(roundedVal,2,valBuffer);
	arrcop(valBuffer,57,fileMeta,2);
	memset(bufferMas,0x00,sizeof(bufferMas));
	arrcop(fileInfo,0,fileBuffer,0xFF);
	for(uint8_t i=0;i<0xFF;++i){
		createInputArr(binArr, sizeof(binArr), fileBuffer[i]);
		pRange=createDataPacket(binArr, outArr, i,aLvl.signalLevel);
		summaryPacketLength=summaryPacketLength+pRange;
		transferIndex=appendArray(outArr, summaryPacketLength, transferIndex, bufferMas);}
	fwrite(bufferMas, 1, transferIndex, FOut);
	transferIndex=0;
	pRange=0;
	memset(fileBuffer,0x00,sizeof(fileBuffer));
	for(uint16_t i=0x00FF;i<392;++i){
		if(pRange<=0x4D){fileBuffer[pRange]=fileInfo[i];}
		if(pRange>0x4D){fileBuffer[pRange]=fileMeta[transferIndex];
			transferIndex++;}
		if(pRange==0x88){break;}++pRange;}
	transferIndex=0;
	pRange=0;
	for(uint8_t i=0;i<=0x88;++i){
		createInputArr(binArr, sizeof(binArr), fileBuffer[i]);
		pRange=createDataPacket(binArr, outArr, i,aLvl.signalLevel);
		summaryPacketLength=summaryPacketLength+pRange;
		transferIndex=appendArray(outArr, summaryPacketLength, transferIndex, bufferMas);}
	fwrite(bufferMas, 1, transferIndex, FOut);
	summaryPacketLength=0;
	transferIndex=0;
	pRange=0;
	while(writeIterations<numberOfIterations+1){
		writeIterations++;
		if(writeIterations>numberOfIterations){
			printf("Запись остаточного блока №%d размером в %d байт\n",writeIterations,roundedVal);
			stopIteration=roundedVal;}
		memset(bufferMas,0x00,sizeof(bufferMas));
		fseek(FIn,inputFileReadIndex,SEEK_SET);
		fread(fileBuffer,1,sizeof(fileBuffer),FIn);
		while(iterations<stopIteration){
			createInputArr(binArr, sizeof(binArr), fileBuffer[iterations]);
			pRange=createDataPacket(binArr, outArr, iterations,aLvl.signalLevel);
			summaryPacketLength=summaryPacketLength+pRange;
			transferIndex=appendArray(outArr, summaryPacketLength, transferIndex, bufferMas);
			iterations++;}
		arrcop(binfdataBckSzEnc,0,blockInfo,8);
		intmas(transferIndex,4,valBuffer);
		arrcop(valBuffer,8,blockInfo,4);
		intmas(transferIndex,4,valBuffer);
		arrcop(binfdataBlckCr16,12,blockInfo,8);
		intmas(bHed.blockCRC16,2,valBuffer);
		arrcop(valBuffer,20,blockInfo,2);
		arrcop(dummyArr,22,blockInfo,2);
		dataStack(1,transferIndex);
		transferIndex=0;
		for(uint8_t i=0;i<24;++i){
			createInputArr(binArr, sizeof(binArr), blockInfo[i]);
			pRange=createDataPacket(binArr, outArr, iterations,aLvl.signalLevel);
			summaryPacketLength=summaryPacketLength+pRange;
			transferIndex=appendArray(outArr, summaryPacketLength, transferIndex, headerBlk);}
		fwrite(headerBlk, 1, transferIndex, FOut);
		transferIndex=dataStack(0,0);
		inputFileReadIndex=inputFileReadIndex+iterations;
		iterations=0;
		arrIndex=arrIndex+transferIndex;
		fwrite(bufferMas, 1, transferIndex, FOut);
		transferIndex=0;}
	summaryPacketLength=ftell(FOut);
	transferIndex=ftell(FOut);
	printf("Суммарный размер записанного файла: %d байт\n",transferIndex);
	printf("Файл настроек convertParams.ini успешно создан\nТеперь необходимо запустить WAVBIND.EXE, чтобы сформировать WAV файл\n");
	free(bufferMas);
	fclose(FIn);
	fclose(FOut);
	storeStructToFile();
	return 0;
}
uint16_t writeCalibrate(bool overrideStruct, uint8_t lengthDetector, uint8_t lengthX, uint8_t lengthNotX)
{
	uint8_t pulseRng=0;
	uint8_t xPulse=0;
	uint8_t notXPulse=0;
	uint8_t steps=0;
	uint16_t calibratPosStart=ftell(FOut);
	uint16_t calibratPosEnd;
	uint16_t writeStart=0;
	uint16_t writeEnd=0;
	if(overrideStruct==TRUE){
		if((lengthDetector>250)||(lengthX>250)||(lengthNotX>250))
			{return 0;}
		pulseRng=cArea.DetectorPulseRange;
		xPulse=cArea.logXPulseRange;
		notXPulse=cArea.logNotXPulseRange;
		cArea.DetectorPulseRange=lengthDetector;
		cArea.logXPulseRange=lengthX;
		cArea.logNotXPulseRange=lengthNotX;}
	for(uint8_t div8=0;div8<=cArea.DetectorPulseRange;div8=div8+4){while(steps<4){
			calibratPosEnd=createBit(outArr, calibratPosStart, calibratPosStart+pulsTim.tSP, aLvl.signalLevel, pulsTim.tSB);
			calibratPosStart=calibratPosEnd;
			steps++;}calibratPosStart=0;
		writeEnd=writeEnd+calibratPosEnd;
		writeStart=appendArray(bufferMas, writeEnd, writeStart, bufferMas);
		steps=0;}
	for(uint8_t div8=0;div8<=cArea.logXPulseRange;div8=div8+4){while(steps<4){
			calibratPosEnd=createBit(outArr, calibratPosStart, calibratPosStart+pulsTim.tTR, aLvl.signalLevel, pulsTim.tSB);
			calibratPosStart=calibratPosEnd;
			steps++;}calibratPosStart=0;
		writeEnd=writeEnd+calibratPosEnd;
		writeStart=appendArray(bufferMas, writeEnd, writeStart, bufferMas);
		steps=0;}
	for(uint8_t div8=0;div8<=cArea.logNotXPulseRange;div8=div8+4){while(steps<4){
			calibratPosEnd=createBit(outArr, calibratPosStart, calibratPosStart+pulsTim.tFL, aLvl.signalLevel, pulsTim.tSB);
			calibratPosStart=calibratPosEnd;
			steps++;}calibratPosStart=0;
		writeEnd=writeEnd+calibratPosEnd;
		writeStart=appendArray(bufferMas, writeEnd, writeStart, bufferMas);
		steps=0;}
	cArea.DetectorPulseRange=pulseRng;
	cArea.logXPulseRange=xPulse;
	cArea.logNotXPulseRange=notXPulse;
	return writeEnd;
}
void createInputArr(bool *appPtr, uint8_t sizeArr, uint8_t inputByte)
{
	uint8_t bitMask=0x01;
	uint8_t bitMoveChar=inputByte;
	uint8_t bitShift=0;
	uint8_t bitShift2=0;
	bool testBit=0;
	for(uint8_t i=0;i<8;i++){
		bitShift2=bitMask<<bitShift;
		bitMoveChar=bitMoveChar&bitShift2;
		testBit=bitMoveChar>>bitShift;
		appPtr[i]=testBit;
		bitShift++;
		bitMoveChar=inputByte;
		testBit=0;}
}
uint8_t createDataPacket(bool *arrIn, uint8_t *arrOut, uint8_t packetNumber, uint8_t analogLevel)
{
	uint8_t arrPos=0;
	uint8_t packetRange=0;
	arrPos=arrPos=createBit(outArr, arrPos, pulsTim.tSP, analogLevel, pulsTim.tSB);
	packetRange=arrPos;
	for(int i=0;i<8;i++){if(arrIn[i]==0){packetRange=packetRange+pulsTim.tFL+pulsTim.tSB;
			arrPos=createBit(outArr, arrPos, arrPos+pulsTim.tFL, analogLevel, pulsTim.tSB);}
		else{packetRange=packetRange+pulsTim.tTR+pulsTim.tSB;
			arrPos=createBit(outArr, arrPos, arrPos+pulsTim.tTR, analogLevel, pulsTim.tSB);}}
	arrPos=createBit(outArr, arrPos, arrPos+1, nullTerminator, 0);
	return arrPos-1;
}
inline uint16_t createBit(uint8_t *inputMas, uint16_t startAdr, uint16_t endAdr, uint8_t charToFill, uint8_t bitPauseRange)
{
	uint8_t pauseChar;
	while(startAdr<endAdr){inputMas[startAdr]=charToFill;
		startAdr++;}if(bitPauseRange==0){return startAdr;}
	endAdr=endAdr+bitPauseRange;
	pauseChar=~charToFill;
	while(startAdr<endAdr){inputMas[startAdr]=pauseChar;
		startAdr++;}return startAdr;
}
uint32_t appendArray(uint8_t *arrToAppend, uint32_t stopAddr, uint32_t startAddr, char *collectStr)
{
	uint8_t inputArrIndexStart=0;
	char temp;
	while(startAddr<stopAddr){
		collectStr[startAddr]=outArr[inputArrIndexStart];
		inputArrIndexStart++;
		startAddr++;
		temp=outArr[inputArrIndexStart];
		if(temp==nullTerminator){return startAddr;}}
	return startAddr;
}
void storeStructToFile(void)
{
	uint8_t crlfSign[2]={0x0D, 0x0A};
	bool WordConverted=1;
	char *FnameSrc="FSRC>";
	char *FnameBod="FBOD>";
	char *Fnametgt="FTGT>";
	char *Fname="FNAM>";
	char *WordConvert="Convert=";
	char *WordSampleRate="SampleRate=";
	char *WordChannels="Channels=";
	char *WordBitsPerSample="BitsPerSample=";
	char *WordCountOfSamples="SamplesInChannel=";
	FSet=fopen("convertParams.ini", "wb");
	fseek(FSet, 0, SEEK_SET);
	fprintf(FSet, "%s", FnameSrc);
	fprintf(FSet, "%s", tempName);
	fprintf(FSet, "%s", wordSrcFilenameEnd);
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);
	fprintf(FSet, "%s", Fname);
	fprintf(FSet, "%s", fileNameHdrDat);
	fprintf(FSet, "%s", wordNameFilenameEnd);
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);
	fprintf(FSet, "%s", FnameBod);
	fprintf(FSet, "%s", fileNameBodDat);
	fprintf(FSet, "%s", wordBodyFilenameEnd);
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);
	fprintf(FSet, "%s", Fnametgt);
	fprintf(FSet, "%s", fileNameTgtDat);
	fprintf(FSet, "%s", wordTargFilenameEnd);
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);
	fprintf(FSet, "%s", WordConvert);
	fprintf(FSet, "%d", WordConverted);
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);
	fprintf(FSet, "%s", WordSampleRate);
	fprintf(FSet, "%d", wavSampleRate);
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);
	fprintf(FSet, "%s", WordChannels);
	fprintf(FSet, "%d", SoundChannels);
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);
	fprintf(FSet, "%s", WordBitsPerSample);
	fprintf(FSet, "%d", BitDepth);
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);
	fprintf(FSet, "%s", WordCountOfSamples);
	fprintf(FSet, "%d", summaryPacketLength);
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);
	fclose(FSet);
}