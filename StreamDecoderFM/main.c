#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include "utils.h"
#define scanSignalCorrect	4
#define bufferLength		160000
#define skipsBeforeTrig		2
#define StartMsg			"v0.0.2 build 2\n"
#define codePageInfo 		"Задана кодовая таблица приложения OEM CP-866\n"
FILE* FIn;
FILE* FOut;
char metadataTag[14]="FM>METADATA_MT";
char metadataEnd[7]="FM>FILE";
char metadataFileName[11]="MT>FILENAME";
char metedataFileSize[11]="MT>FILESIZE";
char metadataFileExtn[11]="MT>FILEEXTN";
char metadataFileCrcs[11]="MT>CHECKSUM";
char metadataFileEnds[11]="MT>ENDOFFIL";
char metadataChnkSumr[11]="MT>CHNKSUMR";
char metadataChnkIndx[11]="MT>CHNKINDX";
char metadataChnkSize[11]="MT>CHNKSIZE";
uint16_t chuksEnum[32];
uint8_t decodeBuffer[256];
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
uint8_t tSP;		//Длина импульса-детектора пакета
uint8_t tTR;		//Длина импульса лог.1
uint8_t tFL;		//Длина импульса лог.0
uint8_t tSB;		//Длина паузы между отправкой битов
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
uint8_t chunksSum;
uint8_t resultByte=0x00;
uint16_t carrierFreq=12000;
uint16_t wavSampleRate=48000;
uint8_t *inputBuffer;
uint8_t *lasstBufferMas;
uint32_t packetConverter(uint8_t *sourceArray, uint32_t arrPos, uint32_t bufferSize);
uint32_t measurePulse(uint8_t *samplesArr);
int main(int argc, char* argv[])
{
	unsigned int codePageNum;
	float modOfDiv;
	bool setOutCodePageStatus;
	bool setInCodePageStatus;
	uint8_t decodeByte=0x00;
	uint8_t decodeBufIndx=0;
	uint8_t stopRead=0xFF;
	uint8_t lastChunkSize=0;
	uint32_t fileWriteIndex=0;
	uint32_t bufferPos=0;
	uint32_t fileSize=0;
	uint32_t roundedVal=0;
	uint32_t numberOfIterations;
	uint32_t fileIndex=0;
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
		printf("Переключение кодовой страницы не требуется\n");
	}
	printf("WAV(дискретная FM модуляция)->Преобразователь форматов BIN \n");
	printf(StartMsg);
	printf("Ну чо пацаны, я слетел с шараги так что теперь прога быстрее будет писаться. \nВсем гулям ку остальным соболезную\n");
	//FIn=fopen("test.wav","rb");
	//if(!FIn&&argc<2)
	//{
	//	printf("Не найден файл %s, или не указаны аргументы\n",argv[1]);
	//	exit(1);
	//}
	tSP=(wavSampleRate/carrierFreq)*pkgSeparatorTiming;
	tTR=(wavSampleRate/carrierFreq)*logTrueTiming;
	tFL=(wavSampleRate/carrierFreq)*logElseTiming;
	tSB=(wavSampleRate/carrierFreq)*bitSeparatorTiming;
	printf("Тайминг стоп-бита: %d\nТайминг лог.0: %d\nТайминг лог.1: %d\nТайминг паузы между отправкой битов: %d\n",tSP,tFL,tTR,tSB);
	printf("f(дискр)=%d\nf(несущ)=%d\n",wavSampleRate,carrierFreq);
	printf("Диапазон разброса длины импульсов %d tau\n",pulseDeviation*2);
	//tSPlow=tSP-pulseDeviationMinus;
	//tSPhigh=tSP+pulseDeviationPlus;
	//tTRlow=tTR-pulseDeviationMinus;
	//tTRhigh=tTR+pulseDeviationPlus;
	//tFLlow=tFL-pulseDeviationMinus;
	//tFLhigh=tFL+pulseDeviationPlus;
	//tSBlow=tSB-pulseDeviationMinus;
	//tSBhigh=tSB+pulseDeviationPlus;
	//printf("Тайминг стоп-бита: %d...%d\nТайминг лог.0: %d...%d\nТайминг лог.1: %d...%d\nТайминг паузы: %d...%d\n",tSPlow,tSPhigh,tFLlow,tFLhigh,tTRlow,tTRhigh,tSBlow,tSBhigh);
	FIn=fopen(argv[1],"rb");
	if(!FIn)
	{
		printf("Не найден файл %s, или не указаны аргументы\n",argv[1]);
		exit(1);
	}
	fseek(FIn,0,SEEK_END);
	fileSize=ftell(FIn);
	modOfDiv=fmod(fileSize, bufferLength);
	printf("Остаточный пакет байтов(RAW): %f\n",modOfDiv);
	roundedVal=round(modOfDiv);
	printf("Остаточный пакет байтов: %d\n", roundedVal);
	numberOfIterations=(fileSize-modOfDiv)/bufferLength;
	if(roundedVal!=0)
	{
		numberOfIterations++;
	}
	printf("Суммарное количество блоков: %d\n",numberOfIterations);
	lasstBufferMas=malloc(roundedVal);
	
	fseek(FIn,0,SEEK_SET);
	fread(inputBuffer,1,bufferLength,FIn);
	fileIndex=measurePulse(inputBuffer);
	printf("Тайминг стоп-бита: %d...%d(среднее %d)(отклонение от среднего +%d-%d)\nТайминг лог.0: %d...%d(среднее %d)(отклонение от среднего +%d-%d)\nТайминг лог.1: %d...%d(среднее %d)(отклонение от среднего +%d-%d)\nТайминг паузы: %d...%d(среднее %d)(отклонение от среднего +%d-%d)\n",tSPlow,tSPhigh,tSPavg,pulseDeviationPlus,pulseDeviationMinus,tFLlow,tFLhigh,tFLavg,pulseDeviationPlus,pulseDeviationMinus,tTRlow,tTRhigh,tTRavg,pulseDeviationPlus,pulseDeviationMinus,tSBlow,tSBhigh,tSBavg,pulseDeviationPlus,pulseDeviationMinus);
	
	FOut=fopen("test","wb");
	//fileIndex=fileIndex+43;
	fseek(FOut,fileWriteIndex,SEEK_SET);
	//for(uint16_t steps=0;steps<4;steps++)
	for(uint16_t steps=0;steps<numberOfIterations;steps++)
	{
		if(steps<numberOfIterations-1)
		{
			printf("Декодирование файла, проход %d, указатель чанка на входном потоке %d, указатель чанка на выходном потоке %d",steps,fileIndex,fileWriteIndex);
		}
		else
		{
			printf("Декодирование файла(остаток), проход %d, указатель чанка на входном потоке %d, указатель чанка на выходном потоке %d",steps,fileIndex,fileWriteIndex);
			stopRead=lastChunkSize;
		}
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
		printf(", размер кодированного пакета %d\n",bufferPos);
		fwrite(decodeBuffer,1,sizeof(decodeBuffer),FOut);
		decodeBufIndx=0;
		fileIndex=fileIndex+bufferPos-1;
		fileWriteIndex=fileWriteIndex+sizeof(decodeBuffer);
	}
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
	printf("Выполняю измерение длин импульсов...\n");
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
		divl=divl/pulseCnt;tSPavg=round(divl);}
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
		divl=divl/pulseCnt;tTRavg=round(divl);}
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
		tFLavg=round(divl);}memset(wideTable,0x00,sizeof(wideTable));
	pauseTrig=0;signalTrig=1;pulseCnt=0;
	for(uint8_t i=0;i<pauseCnt;i++){divl=divl+pauseTable[i];
		if(pMin>=pauseTable[i]){pMin=pauseTable[i];}
		else if(pMax<=pauseTable[i]){pMax=pauseTable[i];}}
	divl=divl/pauseCnt;
	tSBavg=round(divl);
	_k=_k+_p;
	--dMin;
	++dMax;
	--fMin;
	++fMax;
	--fMin;
	++fMax;
	--pMin;
	++pMax;
	tTRlow=tMin;
	tTRhigh=tMax;
	tFLlow=fMin;
	tFLhigh=fMax;
	tSPlow=dMin;
	tSPhigh=dMax+2;
	tSBlow=pMin;
	tSBhigh=pMax;
	printf("Размер калибровочного поля: %d\n",_k-44);
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
	for(uint32_t i=arrPos-pulseDeviation;i<arrPos+tSPhigh;i++){
		if(sourceArray[i]==dataAmplitudeHi){if((byteCount>=tSPlow)&&(lowLimTrig!=1)){lowLimTrig=1;}}
		else if((sourceArray[i]==byteInvert)&&(lowLimTrig==1)){
			if((byteCount<=tSPhigh)&&(sourceArray[i]==byteInvert)&&(higLimTrig!=1)){byteCount--;higLimTrig=1;}}
		if((lowLimTrig&&higLimTrig)==1){arrPos=i+1;break;}byteCount++;}
	lowLimTrig=0;higLimTrig=0;byteCount=0;
	for(uint32_t i=arrPos-pulseDeviation;i<arrPos+tSBhigh;i++){
		if(sourceArray[i]==byteInvert){if((byteCount>=tSBlow)&&(lowLimTrig!=1)){lowLimTrig=1;}}
		else if(sourceArray[i]==dataAmplitudeHi){
			if((byteCount<=tSBhigh)&&(sourceArray[i]==dataAmplitudeHi)&&(higLimTrig!=1)){byteCount--;higLimTrig=1;}}
		if((lowLimTrig&&higLimTrig)==1){arrPos=i;break;}byteCount++;}lowLimTrig=0;higLimTrig=0;byteCount=0;
	while(bitProceed>-1){for(uint32_t i=arrPos-pulseDeviation;i<arrPos+tFLhigh+pulseDeviation;i++){
			if((sourceArray[i]==dataAmplitudeHi)&&(lowLimTrig!=1)){bitTrig++;lowLimTrig=1;}
			else if((sourceArray[i]==byteInvert)&&(lowLimTrig==1)&&(higLimTrig==0)){higLimTrig=1;bitTrig--;}
			if(bitTrig==1){pulseCounter++;}
			if((higLimTrig==1)&&(lowLimTrig==1)){arrPos=i+1;break;}byteCount++;}
		if((pulseCounter>tTRlow)&&(pulseCounter<tTRhigh)){bitArr[bitProceed]=1;}
		if((pulseCounter>tFLlow)&&(pulseCounter<tFLhigh)){bitArr[bitProceed]=0;}
		lowLimTrig=0;higLimTrig=0;byteCount=0;pulseCounter=0;bitProceed--;
		for(uint32_t i=arrPos-pulseDeviation;i<arrPos+tSBhigh;i++){byteCount++;
			if(sourceArray[i]==byteInvert){
				if((byteCount>=tSBlow)&&(lowLimTrig!=1)){lowLimTrig=1;}}
			else if(sourceArray[i]==dataAmplitudeHi){
				if((byteCount<=tSBhigh)&&(sourceArray[i]==dataAmplitudeHi)&&(higLimTrig!=1)){byteCount--;
					higLimTrig=1;}}if((lowLimTrig&&higLimTrig)==1){arrPos=i+1;break;}}
		lowLimTrig=0;higLimTrig=0;byteCount=0;}
	if(resultByte!=0)
		resultByte=0x00;
	for(uint8_t i=0;i<8;i++)
	{resultByte=resultByte|bitArr[7-i]<<i;}
	return arrPos;
}
