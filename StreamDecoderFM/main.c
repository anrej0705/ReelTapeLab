#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include "utils.h"
#define scanSignalCorrect	4
#define bufferLength		131072
#define skipsBeforeTrig		2
#define StartMsg			"v0.0.3 build 4\n"
#define codePageInfo 		"������ ������� ⠡��� �ਫ������ OEM CP-866\n"
FILE* FIn;
FILE* FOut;
FILE* FTest;
char fileTypeJPGcaps[3]="JPG";
char fileTypeJPGnocp[3]="jpg";
char fileTypeJPEGcaps[4]="JPEG";
char fileTypeJPEGnocp[4]="jpeg";
char fileTypeJPG[25]="���⭮� JPEG ����ࠦ����\0";
char fileTypePNGcaps[3]="PNG";
char fileTypePNGnocp[3]="png";
char fileTypePNG[34]="���⮥ ��� ����� PNG ����ࠦ����\0";
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
char valBuffer[4];
char extensionBuffer[8];
char blockInfo[24];
uint16_t chuksEnum[32];
uint16_t hdrTagList[13]={0,5,8,23,35,281,297,309,317,333,348,364,378};
uint8_t hdrSizeList[5]={1,247,4,8,4};
uint8_t infoTagList[4]={0,8,12,20};
uint8_t decodedFileName[255];
bool headerReady=0;
bool bodyReady=0;
bool jpgExtn=0;
bool jpegExtn=0;
bool crcWide=0;
uint8_t transferSteps=0;
uint8_t decodeBuffer[256];
uint8_t procBuf[768];
uint8_t nullTerminator=0x46;
uint8_t zeroAmplitude=0x80;
uint8_t dataAmplitudeHi=0xFF;
uint8_t separatorAmpHi=0xFF;
uint8_t bitSeparatorTiming=1;
uint8_t pkgSeparatorTiming=4;
uint8_t logTrueTiming=1;
uint8_t logElseTiming=2;
uint8_t pulseDeviation=1;
uint8_t pulseDeviationPlus=1;
uint8_t pulseDeviationMinus=1;
uint8_t chunksSum;
uint8_t resultByte=0x00;
uint16_t transferPos[3]={0,256,512};
uint16_t carrierFreq=12000;
uint16_t wavSampleRate=48000;
uint16_t decFileCRC16=0;
uint16_t decFileDecSz=0;
uint16_t decFileDecLtSz=0;
uint32_t decBlockNumber=0;
uint32_t decFileSize=0;
uint32_t decFileCRC32=0;
uint32_t decFileBlks=0;
uint8_t *inputBuffer;
uint8_t *lasstBufferMas;
uint32_t packetConverter(uint8_t *sourceArray, uint32_t arrPos, uint32_t bufferSize);
uint32_t measurePulse(uint8_t *samplesArr);
void proceedHeader(char *inputArr);
struct computedTimings{
	uint8_t tSPlow;
	uint8_t tSPhigh;
	uint8_t tSPavg;
	uint8_t tTRlow;
	uint8_t tTRhigh;
	uint8_t tTRavg;
	uint8_t tFLlow;
	uint8_t tFLhigh;
	uint8_t tFLavg;
	uint8_t tSBlow;
	uint8_t tSBhigh;
	uint8_t tSBavg;
	uint8_t tSPDiffMinus;
	uint8_t tSPDiffPlus;
	uint8_t tTRDiffMinus;
	uint8_t tTRDiffPlus;
	uint8_t tFLDiffMinus;
	uint8_t tFLDiffPlus;
	uint8_t tSBDiffMinus;
	uint8_t tSBDiffPlus;
} compTim;
int main(int argc, char* argv[])
{
	unsigned int codePageNum;
	float modOfDiv;
	bool setOutCodePageStatus;
	bool setInCodePageStatus;
	bool saveAddr=0;
	bool startLock=0;
	bool endLock=1;
	bool transferHeaderLock=1;
	uint8_t decodeByte=0x00;
	uint8_t stopRead=0xFF;
	uint8_t lastChunkSize=0;
	uint8_t srchWrd=0;
	uint8_t ihp=0;
	uint16_t stopProc=0x01FF;
	uint32_t decodeBufIndx=0;
	uint32_t fileWriteIndex=0;
	uint32_t bufferPos=0;
	uint32_t cacheBufferPos=0;
	uint32_t fileSize=0;
	uint32_t roundedVal=0;
	uint32_t numberOfIterations;
	uint32_t fileIndex=0;
	uint32_t fileOffset=0;
	SetConsoleTitle("FM Decoder v0.0.3 build 4 by Anrej0705");
	inputBuffer=malloc(bufferLength);
	codePageNum = GetConsoleOutputCP();
	printf("Current console output codepage: %d\n",codePageNum);
	codePageNum = GetConsoleCP();
	printf("Current console input codepage: %d\n",codePageNum);
	if(codePageNum!=866)
	{
		setOutCodePageStatus=SetConsoleOutputCP(866);
		setInCodePageStatus=SetConsoleCP(866);
		if(setOutCodePageStatus&&setInCodePageStatus != 0)
		{
			printf(codePageInfo);
		}
	}
	else
	{
		printf("��४��祭�� ������� ��࠭��� �� �ॡ����\n");
	}
	printf("WAV(����⭠� FM �������)->�८�ࠧ���⥫� �ଠ⮢ BIN \n");
	printf(StartMsg);
	FIn=fopen(argv[1],"rb");
	if(!FIn)
	{
		printf("�� ������ 䠩� %s, ��� �� 㪠���� ��㬥���\n",argv[1]);
		exit(1);
	}
	fseek(FIn,0,SEEK_SET);
	fread(inputBuffer,1,bufferLength,FIn);
	fileIndex=measurePulse(inputBuffer);
	printf("������� �⮯-���: %d...%d(�।��� %d)(�⪫������ �� �।���� +%d...-%d)\n������� ���.0: %d...%d(�।��� %d)(�⪫������ �� �।���� +%d...-%d)\n������� ���.1: %d...%d(�।��� %d)(�⪫������ �� �।���� +%d...-%d)\n������� ����: %d...%d(�।��� %d)(�⪫������ �� �।���� +%d...-%d)\n",compTim.tSPlow,compTim.tSPhigh,compTim.tSPavg,compTim.tSPDiffPlus,compTim.tSPDiffMinus,compTim.tFLlow,compTim.tFLhigh,compTim.tFLavg,compTim.tFLDiffPlus,compTim.tFLDiffMinus,compTim.tTRlow,compTim.tTRhigh,compTim.tTRavg,compTim.tTRDiffPlus,compTim.tTRDiffMinus,compTim.tSBlow,compTim.tSBhigh,compTim.tSBavg,compTim.tSBDiffPlus,compTim.tSBDiffMinus);
	
	fseek(FIn,fileIndex,SEEK_SET);
	fread(inputBuffer,1,bufferLength,FIn);
	
	//fileIndex=fileIndex+43;
	for(uint8_t i=0;i<3;i++)
	{
		//printf("iteration %d\n",i);
		memset(decodeBuffer,0x00,sizeof(decodeBuffer));
		memset(inputBuffer,0x00,bufferLength);
		fseek(FIn,fileIndex,SEEK_SET);
		fread(inputBuffer,1,bufferLength,FIn);
		bufferPos=1;
		while(1)
		{	
			bufferPos=packetConverter(inputBuffer, bufferPos, bufferLength);
			decodeBuffer[decodeBufIndx]=resultByte;
			if(decodeBufIndx==stopRead)
				break;	
			decodeBufIndx++;
		}
		arrcop(decodeBuffer, transferPos[transferSteps], procBuf, sizeof(decodeBuffer));
		transferSteps++;
		if((i%2==1)&&(headerReady==0))
		{
			proceedHeader(procBuf);
			headerReady=1;
		}
		decodeBufIndx=0;
		if((bodyReady==0)&&(i==0))
		{
			bodyReady=1;
			//dataStack(1,bufferPos);
			//printf("trig\n");
		}
		fileIndex=fileIndex+bufferPos-1;
		fileWriteIndex=fileWriteIndex+sizeof(decodeBuffer);
		//printf("done\n");
	}
	transferSteps=0;
	numberOfIterations=decFileBlks;
	printf("�㬬�୮� ������⢮ ������: %d\n",numberOfIterations);
	FOut=fopen(decodedFileName,"wb");
	fseek(FOut,0,SEEK_SET);
	
	fileIndex=0;
	bufferPos=0;
	fseek(FIn,0,SEEK_SET);
	
	for(uint16_t steps=0;steps<numberOfIterations;steps++)
	{
		dataStack(1,bufferPos);
		bufferPos=0;
		fseek(FIn,fileIndex,SEEK_SET);
		fread(inputBuffer,1,bufferLength,FIn);
		while(1)
		{
			if(startLock==0)
			{
				cacheBufferPos=bufferPos;
			}
			bufferPos=packetConverter(inputBuffer, bufferPos, bufferLength);
			procBuf[decodeBufIndx]=resultByte;
			if(procBuf[decodeBufIndx]==binfdataBckSzEnc[srchWrd])
			{
				srchWrd++;
				if(startLock==0)
				{
					startLock=1;
				}
				if(srchWrd==sizeof(binfdataBckSzEnc)-1)
				{
					break;
				}
			}
			else
			{
				startLock=0;
				srchWrd=0;
			}
			if(decodeBufIndx==768)
			{
				break;
			}
			decodeBufIndx++;
		}
		decodeBufIndx=0;
		//printf("��砫� ��������� %d\n",cacheBufferPos);
		bufferPos=cacheBufferPos;
		for(uint8_t i=0;i<sizeof(blockInfo);i++)
		{
			bufferPos=packetConverter(inputBuffer, bufferPos, bufferLength);
			blockInfo[i]=resultByte;
		}
		if((ihp=strarcmp(blockInfo,infoTagList[0],binfdataBckSzEnc,sizeof(binfdataBckSzEnc)))!=0)
		{/*printf("BSCN ⥣ ������ � �� �� ����\n");*/}
		for(uint8_t i=0;i<sizeof(valBuffer);i++){valBuffer[i]=blockInfo[ihp];ihp++;}
		decBlockNumber=masint(valBuffer,0,4);
		//printf("����� �����: %d\n",decBlockNumber);
		memset(valBuffer,0x00,sizeof(valBuffer));
		if((ihp=strarcmp(blockInfo,infoTagList[2],binfdataBlckCr16,sizeof(binfdataBlckCr16)))!=0)
		{/*printf("CR16 ⥣ ������ � �� �� ����\n");*/}
		for(uint8_t i=0;i<sizeof(valBuffer);i++){valBuffer[i]=blockInfo[ihp];ihp++;}
		decFileCRC16=masint(valBuffer,0,2);
		//printf("����஫쭠� �㬬� CRC-16 �����: 0x%04X\n",decFileCRC16);
		memset(valBuffer,0x00,sizeof(valBuffer));
		printf("������஢����... ��室 %d, ��室�� 砭� %d(ࠧ��� 砭�� %d), ������ 砭� %d, CRC-16: 0x%04X\n",steps+1,fileIndex,dataStack(0,0),fileWriteIndex,decFileCRC16);
		if(steps==numberOfIterations-1)
		{
			printf("������ ���⪠ ࠧ��஬ %d ����... ",decFileDecLtSz+1);
			stopRead=decFileDecLtSz;
			
		}
		while(1)
		{
			bufferPos=packetConverter(inputBuffer, bufferPos, bufferLength);
			decodeBuffer[decodeBufIndx]=resultByte;
			if(decodeBufIndx==stopRead-2)
			{
				cacheBufferPos=bufferPos;
			}
			if(decodeBufIndx==stopRead)
			{
				break;
			}
			decodeBufIndx++;
		}
		//printf("\n");
		bufferPos=cacheBufferPos;
		//printf("����� ���� ᯠ�� ������...");
		for(uint8_t i=0;i<32;i++)
		{
			if(inputBuffer[bufferPos-i]==0)
			{
				//printf(" ������� -> %d\n",bufferPos-i);
				bufferPos=bufferPos-i;
				break;
			}
		}
		fileIndex=fileIndex+bufferPos-1;
		if(steps==numberOfIterations-1)
		{
			stopRead=decFileDecLtSz;
			fwrite(decodeBuffer,1,decFileDecLtSz,FOut);
			break;
		}
		fwrite(decodeBuffer,1,sizeof(decodeBuffer),FOut);
		memset(procBuf,0x00,sizeof(procBuf));
		fileWriteIndex=fileWriteIndex+sizeof(decodeBuffer);
	}
	printf("��⮢�!\n");
	fclose(FIn);
	fclose(FOut);
}
void proceedHeader(char *inputArr)
{
	uint16_t hp=0;
	memset(decodedFileName,0x00,sizeof(decodedFileName));
	if((hp=strarcmp(inputArr,hdrTagList[0],fileSign,sizeof(fileSign)))!=0)
	{printf("FILE ⥣ ������ � �� �� ����\n");}
	printf("����� ⠡���� %d\n",procBuf[hp]);
	if((hp=strarcmp(inputArr,hdrTagList[1],codeMethod,sizeof(codeMethod)))!=0)
	{printf("��⮤ ����஢����: FM\n");}
	if((hp=strarcmp(inputArr,hdrTagList[2],fileprop,sizeof(fileprop)))!=0)
	{printf("FILEPROP ⥣ ������ � �� �� ����\n");}
	if((hp=strarcmp(inputArr,hdrTagList[3],filepropFileName,sizeof(filepropFileName)))!=0)
	{printf("FILENAME ⥣ ������ � �� �� ����\n");}
	dataStack(1,hp);
	hp=0;
	while(inputArr[hp+hdrTagList[4]]!=0x00){decodedFileName[hp]=inputArr[hp+hdrTagList[4]];hp++;}
	printf("������஢����� ��� 䠩��: %s\n",decodedFileName);
	hp=dataStack(0,0);
	if((hp=strarcmp(inputArr,hdrTagList[5],filepropFileSize,sizeof(filepropFileSize)))!=0)
	{printf("FILESIZE ⥣ ������ � �� �� ����\n");}
	for(uint8_t i=0;i<sizeof(valBuffer);i++){valBuffer[i]=inputArr[hp];hp++;}
	decFileSize=masint(valBuffer,0,4);
	printf("������ ࠧ��� �������㥬��� 䠩��: %d ����\n",decFileSize);
	memset(valBuffer,0x00,sizeof(valBuffer));
	if((hp=strarcmp(inputArr,hdrTagList[6],filepropFileExtn,sizeof(filepropFileExtn)))!=0)
	{printf("FILESIZE ⥣ ������ � �� �� ����\n");}
	dataStack(1,hp);
	hp=0;
	printf("��� 䠩��: ");
	while(inputArr[hp+hdrTagList[7]]!=0x00){extensionBuffer[hp]=inputArr[hp+hdrTagList[7]];hp++;}
	if(hp==3||hp==4)
	{
		for(uint8_t i=0;i<hp;i++)
		{
			if((extensionBuffer[i]==fileTypeJPGcaps[i])||(extensionBuffer[i]==fileTypeJPGnocp[i]))
			{
				if((i==2)||(i==3))
				{
					printf("%s\n",fileTypeJPG);
				}
			}
			else if((extensionBuffer[i]==fileTypePNGcaps[i])||(extensionBuffer[i]==fileTypePNGnocp[i]))
			{
				if(i==2)
				{
					printf("%s\n",fileTypePNG);
				}
			}
			else
			{
				break;
			}
		}
	}
	if((hp=strarcmp(inputArr,hdrTagList[8],filepropFileCrcs,sizeof(filepropFileCrcs)))!=0)
	{printf("CHECKSUM ⥣ ������ � �� �� ����\n");}
	for(uint8_t i=0;i<sizeof(valBuffer);i++){valBuffer[i]=inputArr[hp];hp++;}
	decFileCRC32=masint(valBuffer,0,4);
	printf("����஫쭠� �㬬� CRC32: 0x%08X\n",decFileCRC32);
	memset(valBuffer,0x00,sizeof(valBuffer));
	if((hp=strarcmp(inputArr,hdrTagList[9],metadataTag,sizeof(metadataTag)))!=0)
	{printf("METADATA_MT ⥣ ������ � �� �� ����\n");}
	if((hp=strarcmp(inputArr,hdrTagList[10],metadataBlckCont,sizeof(metadataBlckCont)))!=0)
	{printf("BLCKCONT ⥣ ������ � �� �� ����\n");}
	for(uint8_t i=0;i<sizeof(valBuffer);i++){valBuffer[i]=inputArr[hp];hp++;}
	decFileBlks=masint(valBuffer,0,4);
	printf("������⢮ ����஢����� ������: %d\n",decFileBlks);
	memset(valBuffer,0x00,sizeof(valBuffer));
	if((hp=strarcmp(inputArr,hdrTagList[11],metadataBckSzDec,sizeof(metadataBckSzDec)))!=0)
	{printf("BCKSZDEC ⥣ ������ � �� �� ����\n");}
	for(uint8_t i=0;i<2;i++){valBuffer[i]=inputArr[hp];hp++;}
	decFileDecSz=masint(valBuffer,0,2);
	printf("������ ������஢������ �����: %d ����\n",decFileDecSz+1);
	memset(valBuffer,0x00,sizeof(valBuffer));
	if((hp=strarcmp(inputArr,hdrTagList[12],metadataBlckLstS,sizeof(metadataBlckLstS)))!=0)
	{printf("BCKLSTSZ ⥣ ������ � �� �� ����\n");}
	for(uint8_t i=0;i<2;i++){valBuffer[i]=inputArr[hp];hp++;}
	decFileDecLtSz=masint(valBuffer,0,2);
	printf("������ ����筮��: %d ����\n",decFileDecLtSz+1);
	memset(valBuffer,0x00,sizeof(valBuffer));
	
}
uint32_t measurePulse(uint8_t *samplesArr)
{
	float divl=0;
	uint16_t _ovct=0;
	uint16_t _j=0;
	uint16_t _i=0;
	uint16_t _p=0;
	uint16_t _k=44;
	uint8_t dMin;
	uint8_t dMax;
	uint8_t tMin;
	uint8_t tMax;
	uint8_t fMin;
	uint8_t fMax;
	uint8_t pMin;
	uint8_t pMax;
	uint8_t mFlags=0x00;			//mFlags b0 b1 b2 b3 b4 b5 b6 b7
									//b0 - dMin
									//b1 - dMax
									//b2 - tMin
									//b3 - tMax
									//b4 - fMin
									//b5 - fMax
									//b6 - eCal
									//b7 - nCal
	uint8_t wideTable[255];
	uint8_t pauseTable[255];
	uint8_t pulseCnt=0;
	uint8_t pauseCnt=0;
	uint8_t trigKey=0;
	uint8_t trigPause=0;
	bool pauseTrig=0;
	bool signalTrig=1;
	memset(wideTable,0x00,sizeof(wideTable));
	memset(pauseTable,0x00,sizeof(pauseTable));
	printf("�믮���� ����७�� ���� �����ᮢ...\n");
	if(((mFlags&0x80)==0)&&(mFlags&0x40)==0){if(samplesArr[_k]>0xF0){
			while(1){if(samplesArr[_k]>=0xF0){++_k;++_j;}else{break;}}
			dMin=dMax=wideTable[pulseCnt]=_j;
			++pulseCnt;dataStack(1,_k);
			_i=_j;_j=0;pauseTrig=1;}
		while(1){if(samplesArr[_k]<=0x0F){++_k;++_j;}else{break;}}
		pMin=pMax=pauseTable[pauseCnt]=_j;++pauseCnt;_i=_j;_j=0;
		if(pauseTrig==0){while(1){if(samplesArr[_k]>=0xF0){++_k;++_j;}else{break;}}
			dMin=dMax=wideTable[pulseCnt]=_j;
			++pulseCnt;_i=_j;_j=0;}
		else{_k=dataStack(0,0);}pauseTrig=0;
		for(uint32_t i=_k;i<bufferLength;++i){
			if((samplesArr[i]>0xF0)&&(_j>_p)&&(pauseTrig==0)&&(signalTrig==1)){
				if(_j<pMin){pMin=_j;}else if(_j>pMax){pMax=_j;}
				pauseTrig=1;signalTrig=0;
				pauseTable[pauseCnt]=_j;
				++pauseCnt;trigPause=0;
				_p=_j;_j=0;}
			else if((samplesArr[i]>0xF0)&&(_j<_p)&&(pauseTrig==0)&&(signalTrig==1)){
				if(_j<pMin){pMin=_j;}else if(_j>pMax){pMax=_j;}
				pauseTrig=1;signalTrig=0;
				pauseTable[pauseCnt]=_j;
				++pauseCnt;trigPause=0;
				_p=_j;_j=0;}
			else if((samplesArr[i]>0xF0)&&(_j==_p)&&(pauseTrig==0)&&(signalTrig==1)){
				if(_j<pMin){pMin=_j;}else if(_j>pMax){pMax=_j;}
				pauseTrig=1;signalTrig=0;
				pauseTable[pauseCnt]=_j;
				++pauseCnt;trigPause=0;
				_p=_j;_j=0;}
			if((samplesArr[i]<0x0F)&&(_j>dMin-(dMin/4))&&(_j>_i)&&(pauseTrig==1)&&(signalTrig==0)){
				if(_j<dMin){dMin=_j;}else if(_j>dMax){dMax=_j;}
				pauseTrig=0;signalTrig=1;
				wideTable[pulseCnt]=_j;
				++pulseCnt;_i=_j;_j=0;}
			else if((samplesArr[i]<0x0F)&&(_j>dMin-(dMin/4))&&(_j<_i)&&(pauseTrig==1)&&(signalTrig==0)){
				if(_j<dMin){dMin=_j;}else if(_j>dMax){dMax=_j;}
				pauseTrig=0;signalTrig=1;
				wideTable[pulseCnt]=_j;
				++pulseCnt;_i=_j;_j=0;}
			else if((samplesArr[i]<0x0F)&&(_j>=dMin-(dMin/4))&&(_j==_i)&&(pauseTrig==1)&&(signalTrig==0)){
				if(samplesArr[i]<0x0F)
				pauseTrig=0;signalTrig=1;
				wideTable[pulseCnt]=_j;
				++pulseCnt;_i=_j;_j=0;}
			if((samplesArr[i]>0xF0)&&(_j>dMax)&&(pauseTrig==1)&&(signalTrig==0)){trigPause++;}
			else if(trigPause>2){
				_k=i-_j-skipsBeforeTrig;_ovct=_j;
				mFlags=mFlags|0xC0;break;}
			if((samplesArr[i]>0xF0)&&(trigKey==0x00)){trigKey=0xFF;}
			if((samplesArr[i]>0xF0)&&(trigKey==0xFF)){trigKey=0x00;}
			else if((pauseTrig==1)&&(trigPause>skipsBeforeTrig)){
				trigPause=0;_k=i;_ovct=_i-_p;
				mFlags=mFlags|0xC0;break;}
			else if(pauseTrig==1){trigPause++;}
			if((samplesArr[i]>0xF0)&&(pauseTrig==1)&&(signalTrig==0)){++_j;}
			if((samplesArr[i]<0x0F)&&(pauseTrig==0)&&(signalTrig==1)){++_j;}}_k=_k-_ovct;
		for(uint8_t i=0;i<pulseCnt;i++){divl=divl+wideTable[i];}
		divl=divl/pulseCnt;compTim.tSPavg=round(divl);}
	memset(wideTable,0x00,sizeof(wideTable));
	for(uint32_t i=_k;_k>0;--_k){if(samplesArr[_k]>0xF0){_k=i;--_k;break;}}
	divl=0;pauseTrig=0;signalTrig=1;pulseCnt=0;trigPause=0;
	if(((mFlags&0x20)==0)&&(mFlags&0x10)==0){_j=0;
		while(1){if(samplesArr[_k]<=0x0F){++_k;++_j;}else{break;}}
		pMin=pMax=pauseTable[pauseCnt]=_j;++pauseCnt;_i=_j;_j=0;
		while(1){if(samplesArr[_k]>=0xF0){++_k;++_j;}else{break;}}
		tMin=tMax=wideTable[pulseCnt]=_j;
		--tMin;++tMax;++pulseCnt;_i=_j;_j=0;
		for(uint16_t i=_k;i<bufferLength;++i){
			if((samplesArr[i]>0xF0)&&(_j>_p)&&(pauseTrig==0)&&(signalTrig==1)){if(_j<pMin){pMin=_j;}else if(_j>pMax){pMax=_j;}
				pauseTrig=1;signalTrig=0;
				pauseTable[pauseCnt]=_j;
				++pauseCnt;trigPause=0;
				_p=_j;_j=0;}
			else if((samplesArr[i]>0xF0)&&(_j<_p)&&(pauseTrig==0)&&(signalTrig==1)){if(_j<pMin){pMin=_j;}else if(_j>pMax){pMax=_j;}
				pauseTrig=1;signalTrig=0;
				pauseTable[pauseCnt]=_j;
				++pauseCnt;trigPause=0;
				_p=_j;_j=0;}
			else if((samplesArr[i]>0xF0)&&(_j==_p)&&(pauseTrig==0)&&(signalTrig==1)){pauseTrig=1;signalTrig=0;
				pauseTable[pauseCnt]=_j;
				++pauseCnt;trigPause=0;
				_p=_j;_j=0;}
			if((samplesArr[i]<0x0F)&&(_j>tMin-(tMin/4))&&(_j<tMax+(tMax/2))&&(_j>_i)&&(pauseTrig==1)&&(signalTrig==0)){
				if(_j<tMin){tMin=_j;}else if(_j>tMax){tMax=_j;}
				pauseTrig=0;signalTrig=1;
				wideTable[pulseCnt]=_j;
				++pulseCnt;_i=_j;_j=0;}
			else if((samplesArr[i]<0x0F)&&(_j>tMin-(tMin/4))&&(_j<tMax+(tMax/2))&&(_j<_i)&&(pauseTrig==1)&&(signalTrig==0)){
				if(_j<tMin){tMin=_j;}else if(_j>tMax){tMax=_j;}
				pauseTrig=0;signalTrig=1;
				wideTable[pulseCnt]=_j;
				++pulseCnt;_i=_j;_j=0;}
			else if((samplesArr[i]<0x0F)&&(_j>tMin-(tMin/4))&&(_j<tMax+(tMax/2))&&(_j==_i)&&(pauseTrig==1)&&(signalTrig==0)){
				if(samplesArr[i]<0x0F)
				pauseTrig=0;signalTrig=1;
				wideTable[pulseCnt]=_j;
				++pulseCnt;_i=_j;_j=0;}
			if((samplesArr[i]>0xF0)&&(_j>tMax)&&(pauseTrig==1)&&(signalTrig==0)){trigPause++;}
			else if(trigPause>2){
				_k=i;_ovct=_j+1;
				mFlags=mFlags|0x30;break;}
			if((samplesArr[i]>0xF0)&&(trigKey==0x00)){trigKey=0xFF;}
			if((samplesArr[i]>0xF0)&&(trigKey==0xFF)){trigKey=0x00;}
			else if((pauseTrig==1)&&(trigPause>skipsBeforeTrig)){
				trigPause=0;_k=i;_ovct=_i-_p;
				mFlags=mFlags|0x30;break;}
			else if(pauseTrig==1){trigPause++;}
			if((samplesArr[i]<0x0F)&&(pauseTrig==0)&&(signalTrig==1)){++_j;}
			if((samplesArr[i]>0xF0)&&(pauseTrig==1)&&(signalTrig==0)){++_j;}}_k=_k-_ovct-_p;
		for(uint8_t i=0;i<pulseCnt;i++){divl=divl+wideTable[i];}
		divl=divl/pulseCnt;compTim.tTRavg=round(divl);}
	memset(wideTable,0x00,sizeof(wideTable));
	memset(wideTable,0x00,sizeof(wideTable));
	for(uint32_t i=_k;_k>0;--_k){if(samplesArr[_k]>0xF0){_k=i;++_k;break;}}
	divl=0;pauseTrig=0;signalTrig=1;pulseCnt=0;trigPause=0;
	if(((mFlags&0x08)==0)&&(mFlags&0x04)==0){_j=0;
		while(1){if(samplesArr[_k]<=0x0F){++_k;++_j;}else{break;}}
		pMin=pMax=pauseTable[pauseCnt]=_j;++pauseCnt;_i=_j;_j=0;
		while(1){if(samplesArr[_k]>=0xF0){++_k;++_j;}else{break;}}
		fMin=fMax=wideTable[pulseCnt]=_j;++pulseCnt;_i=_j;_j=0;
		for(uint32_t i=_k;i<bufferLength;++i){
			if((samplesArr[i]>0xF0)&&(_j>_p)&&(pauseTrig==0)&&(signalTrig==1)){if(_j<pMin){pMin=_j;}else if(_j>pMax){pMax=_j;}
				pauseTrig=1;signalTrig=0;
				pauseTable[pauseCnt]=_j;
				++pauseCnt;trigPause=0;
				_p=_j;_j=0;}
			else if((samplesArr[i]>0xF0)&&(_j<_p)&&(pauseTrig==0)&&(signalTrig==1)){if(_j<pMin){pMin=_j;}else if(_j>pMax){pMax=_j;}
				pauseTrig=1;signalTrig=0;
				pauseTable[pauseCnt]=_j;
				++pauseCnt;trigPause=0;
				_p=_j;_j=0;}
			else if((samplesArr[i]>0xF0)&&(_j==_p)&&(pauseTrig==0)&&(signalTrig==1)){if(_j<pMin){pMin=_j;}else if(_j>pMax){pMax=_j;}
				pauseTrig=1;signalTrig=0;
				pauseTable[pauseCnt]=_j;
				++pauseCnt;trigPause=0;
				_p=_j;_j=0;}
			if((samplesArr[i]<0x0F)&&(_j>fMin-(fMin/4))&&(_j<fMax+(fMax/2))&&(_j>_i)&&(pauseTrig==1)&&(signalTrig==0)){
				if(_j<fMin){fMin=_j;}else if(_j>fMax){fMax=_j;}
				pauseTrig=0;signalTrig=1;
				wideTable[pulseCnt]=_j;
				++pulseCnt;_i=_j;_j=0;}
			else if((samplesArr[i]<0x0F)&&(_j>fMin-(fMin/4))&&(_j<fMax+(fMax/2))&&(_j<_i)&&(pauseTrig==1)&&(signalTrig==0)){
				if(_j<fMin){fMin=_j;}else if(_j>fMax){fMax=_j;}
				pauseTrig=0;signalTrig=1;
				wideTable[pulseCnt]=_j;
				++pulseCnt;_i=_j;_j=0;}
			else if((samplesArr[i]<0x0F)&&(_j>fMin-(fMin/4))&&(_j<fMax+(fMax/2))&&(_j==_i)&&(pauseTrig==1)&&(signalTrig==0)){
				if(_j<fMin){fMin=_j;}else if(_j>fMax){fMax=_j;}if(samplesArr[i]<0x0F)
				pauseTrig=0;signalTrig=1;
				wideTable[pulseCnt]=_j;
				++pulseCnt;_i=_j;_j=0;}
			if((samplesArr[i]>0xF0)&&(_j>fMax)&&(pauseTrig==1)&&(signalTrig==0)){trigPause++;}else if(trigPause>2){_k=i;_ovct=_j+1;
				mFlags=mFlags|0x30;break;}
			if((samplesArr[i]>0xF0)&&(trigKey==0x00)){trigKey=0xFF;}
			if((samplesArr[i]>0xF0)&&(trigKey==0xFF)){trigKey=0x00;}
			else if((pauseTrig==1)&&(trigPause>skipsBeforeTrig)){trigPause=0;
				_k=i;_ovct=_i-_p;
				mFlags=mFlags|0x30;
				break;}
			else if(pauseTrig==1){trigPause++;}
			if((samplesArr[i]<0x0F)&&(pauseTrig==0)&&(signalTrig==1)){++_j;}
			if((samplesArr[i]>0xF0)&&(pauseTrig==1)&&(signalTrig==0)){++_j;}}_k=_k-_ovct-_p;
		for(uint8_t i=0;i<pulseCnt;i++){divl=divl+wideTable[i];}divl=divl/pulseCnt;
		compTim.tFLavg=round(divl);}memset(wideTable,0x00,sizeof(wideTable));
	pauseTrig=0;signalTrig=1;pulseCnt=0;
	for(uint8_t i=0;i<pauseCnt;i++){divl=divl+pauseTable[i];
		if(pMin>=pauseTable[i]){pMin=pauseTable[i];}
		else if(pMax<=pauseTable[i]){pMax=pauseTable[i];}}
	divl=divl/pauseCnt;
	compTim.tSBavg=round(divl);
	_k=_k+_p;
	--dMin;
	++dMax;
	--fMin;
	++fMax;
	--fMin;
	++fMax;
	--pMin;
	++pMax;
	compTim.tTRlow=tMin;
	compTim.tTRhigh=tMax;
	compTim.tFLlow=fMin;
	compTim.tFLhigh=fMax;
	compTim.tSPlow=dMin;
	compTim.tSPhigh=dMax+2;
	compTim.tSBlow=pMin;
	compTim.tSBhigh=pMax;
	compTim.tSPDiffMinus=compTim.tSPhigh-compTim.tSPavg;
	compTim.tSPDiffPlus=compTim.tSPavg-compTim.tSPlow;
	compTim.tTRDiffMinus=compTim.tTRhigh-compTim.tTRavg;
	compTim.tTRDiffPlus=compTim.tTRavg-compTim.tTRlow;
	compTim.tFLDiffMinus=compTim.tFLhigh-compTim.tFLavg;
	compTim.tFLDiffPlus=compTim.tFLavg-compTim.tFLlow;
	compTim.tSBDiffMinus=compTim.tSBhigh-compTim.tSBavg;
	compTim.tSBDiffPlus=compTim.tSBavg-compTim.tSBlow;
	printf("������ �����஢�筮�� ����: %d\n",_k-44);
	return _k;
}
uint32_t packetConverter(uint8_t *sourceArray, uint32_t arrPos, uint32_t bufferSize)
{
	for(uint32_t i=arrPos;i<arrPos+bufferSize;++i){if(sourceArray[i]==0xFF){arrPos=i;break;}}
	bool ifPulseDetector=0;
	bool ifPulsePause=0;
	bool bitTrig=0;
	bool lowLimTrig=0;
	bool higLimTrig=0;
	int8_t bitProceed=7;
	uint8_t bitArr[8];
	uint8_t pulseCounter=0;
	uint8_t byteCount=0;
	uint8_t byteInvert=0;
	memset(bitArr,0,sizeof(bitArr));
	byteInvert=~dataAmplitudeHi;
	for(uint32_t i=arrPos-pulseDeviation;i<arrPos+compTim.tSPhigh;i++){
		if(sourceArray[i]==dataAmplitudeHi){if((byteCount>=compTim.tSPlow)&&(lowLimTrig!=1)){lowLimTrig=1;}}
		else if((sourceArray[i]==byteInvert)&&(lowLimTrig==1)){
			if((byteCount<=compTim.tSPhigh)&&(sourceArray[i]==byteInvert)&&(higLimTrig!=1)){byteCount--;higLimTrig=1;}}
		if((lowLimTrig&&higLimTrig)==1){arrPos=i+1;break;}byteCount++;}
	lowLimTrig=0;higLimTrig=0;byteCount=0;
	for(uint32_t i=arrPos-pulseDeviation;i<arrPos+compTim.tSBhigh;i++){
		if(sourceArray[i]==byteInvert){if((byteCount>=compTim.tSBlow)&&(lowLimTrig!=1)){lowLimTrig=1;}}
		else if(sourceArray[i]==dataAmplitudeHi){
			if((byteCount<=compTim.tSBhigh)&&(sourceArray[i]==dataAmplitudeHi)&&(higLimTrig!=1)){byteCount--;higLimTrig=1;}}
		if((lowLimTrig&&higLimTrig)==1){arrPos=i;break;}byteCount++;}lowLimTrig=0;higLimTrig=0;byteCount=0;
	while(bitProceed>-1){for(uint32_t i=arrPos-pulseDeviation;i<arrPos+compTim.tFLhigh+pulseDeviation;i++){
			if((sourceArray[i]==dataAmplitudeHi)&&(lowLimTrig!=1)){bitTrig++;lowLimTrig=1;}
			else if((sourceArray[i]==byteInvert)&&(lowLimTrig==1)&&(higLimTrig==0)){higLimTrig=1;bitTrig--;}
			if(bitTrig==1){pulseCounter++;}
			if((higLimTrig==1)&&(lowLimTrig==1)){arrPos=i+1;break;}byteCount++;}
		if((pulseCounter>compTim.tTRlow)&&(pulseCounter<compTim.tTRhigh)){bitArr[bitProceed]=1;}
		if((pulseCounter>compTim.tFLlow)&&(pulseCounter<compTim.tFLhigh)){bitArr[bitProceed]=0;}
		lowLimTrig=0;higLimTrig=0;byteCount=0;pulseCounter=0;bitProceed--;
		for(uint32_t i=arrPos-pulseDeviation;i<arrPos+compTim.tSBhigh;i++){byteCount++;
			if(sourceArray[i]==byteInvert){
				if((byteCount>=compTim.tSBlow)&&(lowLimTrig!=1)){lowLimTrig=1;}}
			else if(sourceArray[i]==dataAmplitudeHi){
				if((byteCount<=compTim.tSBhigh)&&(sourceArray[i]==dataAmplitudeHi)&&(higLimTrig!=1)){byteCount--;
					higLimTrig=1;}}if((lowLimTrig&&higLimTrig)==1){arrPos=i+1;break;}}
		lowLimTrig=0;higLimTrig=0;byteCount=0;}
	if(resultByte!=0)
		resultByte=0x00;
	for(uint8_t i=0;i<8;i++)
	{resultByte=resultByte|bitArr[7-i]<<i;}
	return arrPos;
}
