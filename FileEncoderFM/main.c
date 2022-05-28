#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#define bufferLength		32768
#define StartMsg			"v0.0.2 build 3\n"
#define codePageInfo 		"Задана кодовая таблица приложения OEM CP-866\n"
char fileBuffer[256];
char fileName[128];
char tempName[9]="generated";
char headerNameSuffix[11]="_header.dat";																										//суффикс к имени преобразуемого файла
char headerBodySuffix[9]="_body.dat";																											//суффикс к имени преобразуемого файла
char headerConvSuffix[12]="_conv_FM.wav";																										//суффикс к имени преобразуемого файла
char metadataTag[14]="FM>METADATA_MT";
char metadataEnd[7]="FM>FILE";
char metadataFileName[11]="MT>FILENAME";
char metedataFileSize[11]="MT>FILESIZE";
char metadataFileExtn[11]="MT>FILEEXTN";
char metadataFileCrcs[11]="MT>CHECKSUM";
char metadataFileEnds[11]="MT>ENDOFFIL";
char fileNameHdrDat[64];																														//массив с именем заголовочного файла
char fileNameBodDat[64];																														//массив с именем заголовочного файла
char fileNameTgtDat[64];																														//массив с именем заголовочного файла
char *wordFilenameSource="FSRC";																												//Название для параметра имени файла
char *wordFilenameBody="FBOD";		   																											//Название для параметра имени файла
char *wordFilename="FNAM";																														//Название для параметра имени файла
char *wordFilenameTarget="FTGT";																												//Название для параметра имени файла
char *wordSrcFilenameEnd=">FSND";																												//Название для параметра имени файла
char *wordNameFilenameEnd=">FNND";																												//Название для параметра имени файла
char *wordBodyFilenameEnd=">FBND";																												//Название для параметра имени файла
char *wordTargFilenameEnd=">FTND";																												//Название для параметра имени файла
FILE* FIn;
FILE* FSet;
FILE* FOut;
float modOfDiv;
uint8_t SoundChannels;
uint8_t BitDepth;
uint8_t nullTerminator=0x46;
uint8_t zeroAmplitude=0x80;
uint8_t dataAmplitudeHi=0xFF;
uint8_t separatorAmpHi=0xFF;
uint8_t bitSeparatorTiming=1;
uint8_t pkgSeparatorTiming=4;
uint8_t logTrueTiming=1;
uint8_t logElseTiming=2;
uint8_t tSP;		//Длина импульса-детектора пакета
uint8_t tTR;		//Длина импульса лог.1
uint8_t tFL;		//Длина импульса лог.0
uint8_t tSB;		//Длина паузы между отправкой битов
uint16_t carrierFreq=12000;
uint16_t wavSampleRate=48000;
uint32_t summaryPacketLength;
uint32_t roundedVal=0;
uint32_t numberOfIterations;
bool binArr[8];
uint8_t outArr[256];
void createInputArr(bool *appPtr, uint8_t sizeArr, uint8_t inputByte);
void storeStructToFile(void);
uint8_t createDataPacket(bool *arrIn, uint8_t *arrOut, uint8_t packetNumber, uint8_t analogLevel);
uint16_t createBit(uint8_t *inputMas, uint16_t startAdr, uint16_t endAdr, uint8_t charToFill, uint8_t bitPauseRange);
uint16_t writeCalibrate(bool overrideStruct, uint8_t lengthDetector, uint8_t lengthX, uint8_t lengthNotX);
uint32_t appendArray(uint8_t *arrToAppend, uint32_t stopAddr, uint32_t startAddr);
void transformFileName(char *sourceFileName, uint8_t sourceLenght, char *suffixToAttach, uint8_t suffixLength, char *arrToStore);
uint8_t *bufferMas;
uint8_t *lasstBufferMas;
struct analogLvl{
	uint8_t signalLevel;
} aLvl;
struct calibrationArea{
	uint8_t DetectorPulseRange;
	uint8_t logXPulseRange;
	uint8_t logNotXPulseRange;
} cArea;
int main(int argc, char* argv[])
{
	unsigned int codePageNum;
	char temp;
	uint8_t testMas[4]={0x7E,0x9A,0x2F,0xB1};
	uint8_t pRange=0;
	uint32_t writeIterations=0;
	uint32_t transferIndex=0;
	uint32_t arrIndex=0;
	uint32_t iterations=0;
	uint32_t stopIteration=16;
	uint32_t fileSize=0;
	uint32_t inputFileReadIndex=0;
	bool setOutCodePageStatus;
	bool setInCodePageStatus;
	aLvl.signalLevel=0xFF;
	cArea.DetectorPulseRange=0x07;
	cArea.logXPulseRange=0x07;
	cArea.logNotXPulseRange=0x07;
	SoundChannels=1;
	BitDepth=8;
	bufferMas = malloc(bufferLength);					//буфер под пачку семплов генерируемых из 256 байт данных. Должно хватить
	memset(bufferMas,0x00,sizeof(bufferMas));
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
	printf("Преобразователь форматов BIN->WAV(дискретная FM модуляция) \n");
	printf(StartMsg);
	printf("Ну чо пацаны, я слетел с шараги так что теперь прога быстрее будет писаться. \nВсем гулям ку остальным соболезную\n");
	FIn=fopen(argv[1],"rb");
	if(!FIn&&argc<2)
	{
		printf("Не найден файл %s, или не указаны аргументы\n",argv[1]);
		exit(1);
	}
	transformFileName(tempName, sizeof(tempName), headerNameSuffix, sizeof(headerNameSuffix), fileNameHdrDat);
	transformFileName(tempName, sizeof(tempName), headerBodySuffix, sizeof(headerBodySuffix), fileNameBodDat);
	transformFileName(tempName, sizeof(tempName), headerConvSuffix, sizeof(headerConvSuffix), fileNameTgtDat);
	FOut=fopen(fileNameBodDat, "wb");
	fseek(FIn,0,SEEK_END);
	fileSize=ftell(FIn);
	//printf("Размер входного файла: %d байт\n",fileSize);
	tSP=(wavSampleRate/carrierFreq)*pkgSeparatorTiming;
	tTR=(wavSampleRate/carrierFreq)*logTrueTiming;
	tFL=(wavSampleRate/carrierFreq)*logElseTiming;
	tSB=(wavSampleRate/carrierFreq)*bitSeparatorTiming;
	printf("Тайминг стоп-бита: %d\nТайминг лог.0: %d\nТайминг лог.1: %d\nТайминг паузы между отправкой битов: %d\n",tSP,tFL,tTR,tSB);
	printf("f(дискр)=%d\nf(несущ)=%d\n",wavSampleRate,carrierFreq);
	modOfDiv=fmod(fileSize, sizeof(fileBuffer));
	//printf("Остаточный пакет байтов: %f\n",modOfDiv);
	roundedVal=round(modOfDiv);
	//printf("Округленное значение: %d\n", roundedVal);
	numberOfIterations=(fileSize-modOfDiv)/sizeof(fileBuffer);
	//printf("Суммарное количество блоков размером %d байт на запись: %d\n",sizeof(fileBuffer),numberOfIterations);
	lasstBufferMas=malloc(roundedVal);
	if(lasstBufferMas!=NULL)
	{
		printf("Задан размер буфера под остаток в %d байт\n",roundedVal);
	}
	stopIteration=sizeof(fileBuffer);
	
	fseek(FOut,0,SEEK_SET);
	transferIndex=writeCalibrate(1,31,31,31);
	printf("transferIndex=%d\n",transferIndex);
	fwrite(bufferMas,1,transferIndex,FOut);
	
	for(uint16_t i=1;i<transferIndex+1;i++)
	{
		printf("0x%02X ",bufferMas[i-1]);
		if(i%16==0)
			printf("\n");
	}
	
	fseek(FOut,transferIndex,SEEK_SET);
	transferIndex=0;
	
	while(writeIterations<numberOfIterations+1)
	{
		writeIterations++;
		if(writeIterations>numberOfIterations)
		{
			printf("Запись остаточного блока №%d размером в %d байт\n",writeIterations,roundedVal);
			stopIteration=roundedVal;
		}
		else
		{
			//printf("Запись блока №%d\n",writeIterations);
		}
		//printf("Начало блока исходного файла %d байт\n",inputFileReadIndex);
		//printf("Начало блока на %d байт\n",arrIndex);
		memset(bufferMas,0x00,sizeof(bufferMas));
		fseek(FIn,inputFileReadIndex,SEEK_SET);
		fread(fileBuffer,1,sizeof(fileBuffer),FIn);
		//printf("Размер буфера: %d байт\n",stopIteration);
		//for(uint8_t i=0;i<255;i++)
		//{
		//	printf("0x%02X ",(uint8_t)fileBuffer[i]);
		//	if(i%16==0)
		//	{
		//		printf("\n");
		//	}
		//}
		while(iterations<stopIteration)
		{
			createInputArr(binArr, sizeof(binArr), fileBuffer[iterations]);
			pRange=createDataPacket(binArr, outArr, iterations,aLvl.signalLevel);
			//printf("Длина пакета данных %d байт\n",pRange);
			summaryPacketLength=summaryPacketLength+pRange;
			transferIndex=appendArray(outArr, summaryPacketLength, transferIndex);
			//printf("Суммарный размер блока данных объемом %d пакетов: %d байт\n",iterations,transferIndex);
			iterations++;
		}
		//printf("Суммарный размер записанного блока: %d семлов\n",transferIndex);
		inputFileReadIndex=inputFileReadIndex+iterations;
		//fseek(FOut,arrIndex,SEEK_SET);
		fwrite(bufferMas, 1, transferIndex, FOut);
		iterations=0;
		arrIndex=arrIndex+transferIndex;
		transferIndex=0;
	}
	summaryPacketLength=ftell(FOut);
	transferIndex=ftell(FOut);
	printf("[В РАЗРАБОТКЕ] Не забудь записать количество чанков и их размеры!\n(В будущем эта функция будет автоматизирована)\n");
	printf("Суммарный размер записанного файла: %d байт\n",transferIndex);
	printf("Файл настроек convertParams.ini успешно создан\nТеперь необходимо запустить Exstitcher, чтобы сформировать WAV файл\n");
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
			calibratPosEnd=createBit(outArr, calibratPosStart, calibratPosStart+tSP, aLvl.signalLevel, tSB);
			calibratPosStart=calibratPosEnd;
			steps++;}calibratPosStart=0;
		writeEnd=writeEnd+calibratPosEnd;
		writeStart=appendArray(bufferMas, writeEnd, writeStart);
		steps=0;}
	for(uint8_t div8=0;div8<=cArea.logXPulseRange;div8=div8+4){while(steps<4){
			calibratPosEnd=createBit(outArr, calibratPosStart, calibratPosStart+tTR, aLvl.signalLevel, tSB);
			calibratPosStart=calibratPosEnd;
			steps++;}calibratPosStart=0;
		writeEnd=writeEnd+calibratPosEnd;
		writeStart=appendArray(bufferMas, writeEnd, writeStart);
		steps=0;}
	for(uint8_t div8=0;div8<=cArea.logNotXPulseRange;div8=div8+4){while(steps<4){
			calibratPosEnd=createBit(outArr, calibratPosStart, calibratPosStart+tFL, aLvl.signalLevel, tSB);
			calibratPosStart=calibratPosEnd;
			steps++;}calibratPosStart=0;
		writeEnd=writeEnd+calibratPosEnd;
		writeStart=appendArray(bufferMas, writeEnd, writeStart);
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
	uint8_t testMas[8];
	bool testBit=0;
	for(uint8_t i=0;i<8;i++)
	{
		bitShift2=bitMask<<bitShift;
		bitMoveChar=bitMoveChar&bitShift2;
		testBit=bitMoveChar>>bitShift;
		appPtr[i]=testBit;
		bitShift++;
		bitMoveChar=inputByte;
		testBit=0;
	}
}
uint8_t createDataPacket(bool *arrIn, uint8_t *arrOut, uint8_t packetNumber, uint8_t analogLevel)
{
	uint8_t arrPos=0;
	uint8_t packetRange=0;
	arrPos=arrPos=createBit(outArr, arrPos, tSP, analogLevel, tSB);
	packetRange=arrPos;
	for(int i=0;i<8;i++)
	{
		if(arrIn[i]==0)
		{
			packetRange=packetRange+tFL+tSB;
			arrPos=createBit(outArr, arrPos, arrPos+tFL, analogLevel, tSB);
		}
		else
		{
			packetRange=packetRange+tTR+tSB;
			arrPos=createBit(outArr, arrPos, arrPos+tTR, analogLevel, tSB);
		}
	}
	arrPos=createBit(outArr, arrPos, arrPos+1, nullTerminator, 0);
	return arrPos-1;
}
inline uint16_t createBit(uint8_t *inputMas, uint16_t startAdr, uint16_t endAdr, uint8_t charToFill, uint8_t bitPauseRange)
{
	uint8_t pauseChar;
	while(startAdr<endAdr)
	{
		inputMas[startAdr]=charToFill;
		startAdr++;
	}
	if(bitPauseRange==0)
	{
		return startAdr;
	}
	endAdr=endAdr+bitPauseRange;
	pauseChar=~charToFill;
	while(startAdr<endAdr)
	{
		inputMas[startAdr]=pauseChar;
		startAdr++;
	}
	return startAdr;
}
uint32_t appendArray(uint8_t *arrToAppend, uint32_t stopAddr, uint32_t startAddr)
{
	uint8_t inputArrIndexStart=0;
	char temp;
	while(startAddr<stopAddr)
	{
		bufferMas[startAddr]=outArr[inputArrIndexStart];
		inputArrIndexStart++;
		startAddr++;
		temp=outArr[inputArrIndexStart];
		if(temp==nullTerminator)
		{
			return startAddr;
		}
	}
	return startAddr;
}
void storeStructToFile(void)																													//функция записи настроек в файл
{																																				//начало функции
	uint8_t crlfSign[2]={0x0D, 0x0A};																											//метка CR LF(перенос каретки на новую строку)
	bool WordConverted=1;																														//инициализируем флаг
	char *FnameSrc="FSRC>";																														//имя исходного файла
	char *FnameBod="FBOD>";																														//имя тела файла
	char *Fnametgt="FTGT>";																														//имя файла после склеивания
	char *Fname="FNAM>";																														//имя файла
	char *WordConvert="Convert=";																												//образец тега Convert
	char *WordSampleRate="SampleRate=";																											//образец тега SampleRate
	char *WordChannels="Channels=";																												//образец тега Channels
	char *WordBitsPerSample="BitsPerSample=";																									//образец тега BitsPerSample
	char *WordCountOfSamples="SamplesInChannel=";																								//образец тега SamplesInChannel
	FSet=fopen("convertParams.ini", "wb");																										//открываем файл на запись как бинарный(зач бинарный? тут текст обычный)
	fseek(FSet, 0, SEEK_SET);																													//устанвливаем курсор на 0
	fprintf(FSet, "%s", FnameSrc);																												//пишем тег FNAM
	fprintf(FSet, "%s", tempName);																												//пишем имя файла
	fprintf(FSet, "%s", wordSrcFilenameEnd);																									//пишем тег >FSND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fprintf(FSet, "%s", Fname);																													//пишем тег FNAM
	fprintf(FSet, "%s", fileNameHdrDat);																										//пишем имя файла
	fprintf(FSet, "%s", wordNameFilenameEnd);																									//пишем тег >FNND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fprintf(FSet, "%s", FnameBod);																												//пишем тег FBOD
	fprintf(FSet, "%s", fileNameBodDat);																										//пишем имя файла
	fprintf(FSet, "%s", wordBodyFilenameEnd);																									//пишем тег >FBND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fprintf(FSet, "%s", Fnametgt);																												//пишем тег FTGT
	fprintf(FSet, "%s", fileNameTgtDat);																										//пишем имя файла
	fprintf(FSet, "%s", wordTargFilenameEnd);																									//пишем тег >FTND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fprintf(FSet, "%s", WordConvert);																											//пишем тег Convert
	fprintf(FSet, "%d", WordConverted);																											//пишем флаг состояния
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fprintf(FSet, "%s", WordSampleRate);																										//пишем тег SampleRate
	fprintf(FSet, "%d", wavSampleRate);																											//пишем частоту дискретизации числом
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fprintf(FSet, "%s", WordChannels);																											//пишем тег Channels
	fprintf(FSet, "%d", SoundChannels);																											//пишем количество каналов
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fprintf(FSet, "%s", WordBitsPerSample);																										//пишем тег BitsPerSample
	fprintf(FSet, "%d", BitDepth);																												//пишем глубину выборки
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fprintf(FSet, "%s", WordCountOfSamples);																									//пишем тег BitsPerSample
	fprintf(FSet, "%d", summaryPacketLength);																									//пишем количество выборок
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fclose(FSet);																																//закрываем файл
}																																				//конец функции
void transformFileName(char *sourceFileName, uint8_t sourceLenght, char *suffixToAttach, uint8_t suffixLength, char *arrToStore)				//функция генерирования имени файла
{																																				//начало тела функции
	char tempMas[128];																															//инициализируем временный буфер
	memset(tempMas,0x00,sizeof(tempMas));																										//и чистим его
	uint8_t filenameWithoutExtension=sourceLenght;																								//инициализация переменной длины имени файла без расширения
	uint8_t generatedFileNameWithSuffix;																										//инициализация переменной длины сгенерированного имени файла
	for(int i=0;i<filenameWithoutExtension+suffixLength;i++)																					//начало цикла генерации имени файла
	{																																			//начало тела цикла
		if(i<filenameWithoutExtension)																											//начало переноса имени файла
		{																																		//начало тела
			tempMas[i]=sourceFileName[i];																										//посимвольный перенос имени файла
		}																																		//конец тела
		if(i>=filenameWithoutExtension)																											//начало записи суффикса к имени файла
		{																																		//начало тела
			tempMas[i]=suffixToAttach[i-filenameWithoutExtension];																				//посимвольная запись суффикса к имени файла
		}																																		//конец тела
	}																																			//конец тела цикла
	generatedFileNameWithSuffix = filenameWithoutExtension+suffixLength;																		//формирование длины имени файла вместе с суффиксом
	printf("Полученное имя файла: ");																											//пишем сгенерированное имя файла
	for(int i=0;i<generatedFileNameWithSuffix;i++)																								//начало цикла переноса имени файла из временного массива
	{																																			//начало тела цикла
		fileName[i]=tempMas[i];																													//посимвольный перенос имени файла
		arrToStore[i]=tempMas[i];																												//дублируем в массив по указателю для защиты от случайного изменения в ходе работы программы т.к прога где-то багается непонятно где
		printf("%c",arrToStore[i]);																												//и сразу же вывод в консоль
	}																																			//конец тела цикла
	printf("\n");																																//перенос каретки
}
