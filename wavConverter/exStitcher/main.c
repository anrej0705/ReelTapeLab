#include<locale.h>																																//Библиотека локализацй, нужна для русского языка в консоли
#include<stdbool.h>																																//Библиотека для работы с двоичными числам, C99
#include<stdint.h>																																//Бибилотека для работы с нестандартными числами uint8_t, uint16_t, uint32_t
#include<stdio.h>																																//Библиотека для работы с консолью, вывод в консоль и считывание с нее
#include<conio.h>																																//Бибилотека
#include<stdlib.h>																																//Бибилотека
#include<string.h>																																//Библиотека
#include<math.h>																																//Библиотека с математическими функциями
#define RusLang							setlocale(LC_ALL, "Rus")
#define buildVersion					" v0.0.1\n"																								//версия билда. В данный момент идет альфа тест
FILE* FSt;																																		//для работы с файлом convertParams.ini
FILE* FHd;																																		//для работы с файлом заголовка
FILE* FBd;																																		//для работы с файлом тела
FILE* FTg;																																		//для работы с результатом
uint8_t fileMainBuffer[2048];
char FSetBuffer[1024];
char fileHeaderName[256];
char fileBodyName[256];
char fileTargetName[256];
char fileHeader[44];
char fileInitialBuffer[2004];
char *startPos;
char *TagFileHeaderStart="FNAM";
char *TagFileHeaderEnd="FNND";
char *TagFileBodyStart="FBOD";
char *TagFileBodyEnd="FBND";
char *TagFileTargetStart="FTGT";
char *TagFileTargetEnd="FTND";
char *TagSamplesInChannel="SamplesInChannel";
float modOfDiv;
const uint8_t shiftForward=5;
const uint8_t stepBack=1;
const uint8_t wordSamplesValueShift=17;
uint16_t TagFileHeaderStartPos;
uint16_t TagFileHeaderEndPos;
uint16_t TagFileBodyStartPos;
uint16_t TagFileBodyEndPos;
uint16_t TagFileTargetStartPos;
uint16_t TagFileTargetEndPos;
uint16_t TagSamplesInChannelPos;
uint16_t writeIterations=0;
uint32_t scanStartPos;
uint32_t scanStopPos;
uint32_t SamplesInChannel;
uint32_t roundedVal=0;
uint32_t numberOfIterations;
void printDebugMsg(uint8_t msgCode, uint8_t codeParameter, char charParameter);
int main(void)
{
	uint8_t transferIndex=0;
	setlocale(LC_ALL, "Rus");;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printDebugMsg(0,0,0);
	printf(buildVersion);
	printDebugMsg(0,0,0);
	printf(" Установлен размер буфера чтения-записи: %d Байт\n",sizeof(fileMainBuffer));
	printDebugMsg(0,0,0);
	printf(" Установлен размер сборочного буфера: %d Байт\n",sizeof(fileInitialBuffer));
	
	
	printDebugMsg(0,0,0);
	printf(" Открываю файл настроек convertParams.ini... ");
	FSt=fopen("convertParams.ini","rb");
	if(FSt != 0)
	{
		printf("Успех!\n");
	}
	else
	{
		printf("Файл convertParams.ini не найден или недоступен для открытия. Выход...\n");
		exit(1);
	}
	fread(FSetBuffer, 1, sizeof(FSetBuffer), FSt);
	
	printDebugMsg(0,0,0);
	printDebugMsg(4,0,0);
	printf(" Ищу слово: %s...",TagFileHeaderStart);
	startPos=strstr(FSetBuffer,TagFileHeaderStart);
	TagFileHeaderStartPos=startPos-FSetBuffer;
	printf(" Найдено, смещение на %d Байт\n",TagFileHeaderStartPos);
	printDebugMsg(0,0,0);
	printDebugMsg(4,0,0);
	printf(" Ищу слово: %s...",TagFileHeaderEnd);
	startPos=strstr(FSetBuffer,TagFileHeaderEnd);
	TagFileHeaderEndPos=startPos-FSetBuffer;
	printf(" Найдено, смещение на %d Байт\n",TagFileHeaderEndPos);
	printDebugMsg(0,0,0);
	printDebugMsg(4,0,0);
	printf(" Ищу слово: %s...",TagFileBodyStart);
	startPos=strstr(FSetBuffer,TagFileBodyStart);
	TagFileBodyStartPos=startPos-FSetBuffer;
	printf(" Найдено, смещение на %d Байт\n",TagFileBodyStartPos);
	printDebugMsg(0,0,0);
	printDebugMsg(4,0,0);
	printf(" Ищу слово: %s...",TagFileBodyEnd);
	startPos=strstr(FSetBuffer,TagFileBodyEnd);
	TagFileBodyEndPos=startPos-FSetBuffer;
	printf(" Найдено, смещение на %d Байт\n",TagFileBodyEndPos);
	printDebugMsg(0,0,0);
	printDebugMsg(4,0,0);
	printf(" Ищу слово: %s...",TagFileTargetStart);
	startPos=strstr(FSetBuffer,TagFileTargetStart);
	TagFileTargetStartPos=startPos-FSetBuffer;
	printf(" Найдено, смещение на %d Байт\n",TagFileTargetStartPos);
	printDebugMsg(0,0,0);
	printDebugMsg(4,0,0);
	printf(" Ищу слово: %s...",TagFileTargetEnd);
	startPos=strstr(FSetBuffer,TagFileTargetEnd);
	TagFileTargetEndPos=startPos-FSetBuffer;
	printf(" Найдено, смещение на %d Байт\n",TagFileTargetEndPos);
	printDebugMsg(0,0,0);
	printDebugMsg(4,0,0);
	printf(" Ищу слово: %s...",TagSamplesInChannel);
	startPos=strstr(FSetBuffer,TagSamplesInChannel);
	TagSamplesInChannelPos=startPos-FSetBuffer;
	printf(" Найдено, смещение на %d Байт\n",TagSamplesInChannelPos);
	printDebugMsg(0,0,0);
	printDebugMsg(4,0,0);
	printf(" Сканирование тегов завершено\n");
	
	scanStartPos=TagFileHeaderStartPos+shiftForward;
	scanStopPos=TagFileHeaderEndPos-stepBack;
	while(scanStartPos<scanStopPos)
	{
		fileHeaderName[transferIndex]=FSetBuffer[scanStartPos];
		//printf("%c",fileHeaderName[transferIndex]);
		scanStartPos++;
		transferIndex++;
	}
	transferIndex=0;
	printDebugMsg(0,0,0);
	printDebugMsg(5,0,0);
	printf(" Заданное имя файла с заголовком: %s\n",fileHeaderName);
	scanStartPos=TagFileBodyStartPos+shiftForward;
	scanStopPos=TagFileBodyEndPos-stepBack;
	while(scanStartPos<scanStopPos)
	{
		fileBodyName[transferIndex]=FSetBuffer[scanStartPos];
		//printf("%c",fileBodyName[transferIndex]);
		scanStartPos++;
		transferIndex++;
	}
	transferIndex=0;
	printDebugMsg(0,0,0);
	printDebugMsg(5,0,0);
	printf(" Заданное имя файла с телом: %s\n",fileBodyName);
	scanStartPos=TagFileTargetStartPos+shiftForward;
	scanStopPos=TagFileTargetEndPos-stepBack;
	while(scanStartPos<scanStopPos)
	{
		fileTargetName[transferIndex]=FSetBuffer[scanStartPos];
		//printf("%c",fileTargetName[transferIndex]);
		scanStartPos++;
		transferIndex++;
	}
	transferIndex=0;
	printDebugMsg(0,0,0);
	printDebugMsg(5,0,0);
	printf(" Заданное конечное имя файла: %s\n",fileTargetName);
	scanStartPos=TagSamplesInChannelPos+wordSamplesValueShift;
	fseek(FSt,scanStartPos,SEEK_SET);
	fscanf(FSt,"%d",&SamplesInChannel);
	printDebugMsg(0,0,0);
	printDebugMsg(5,0,0);
	printf(" Количество семплов в файле: %d\n",SamplesInChannel);
	modOfDiv=fmod(SamplesInChannel, sizeof(fileMainBuffer));
	printDebugMsg(0,0,0);
	printf(" Остаточный пакет байтов: %f\n",modOfDiv);
	roundedVal=round(modOfDiv);
	printDebugMsg(0,0,0);
	printf(" Округленное значение: %d\n", roundedVal);
	numberOfIterations=(SamplesInChannel-modOfDiv)/sizeof(fileMainBuffer);
	printDebugMsg(0,0,0);
	printf(" Суммарное количество блоков размером %d байт на запись: %d\n",sizeof(fileMainBuffer),numberOfIterations);
	
	printDebugMsg(0,0,0);
	printf(" Открываю файл заголовка %s... ",fileHeaderName);
	FHd=fopen(fileHeaderName, "rb");
	if(FHd != 0)
	{
		printf("Успех!\n");
	}
	else
	{
		printf("Файл %s не найден или недоступен для открытия. Выход...\n",fileHeaderName);
		exit(1);
	}
	fseek(FHd, 0, SEEK_SET);
	fread(fileHeader, 1, sizeof(fileHeader), FHd);
	printDebugMsg(0,0,0);
	printf(" Заголовок прочитан в буфер\n");
	fclose(FHd);
	
	printDebugMsg(0,0,0);
	printf(" Открываю файл тела %s... ",fileBodyName);
	FBd=fopen(fileBodyName, "rb");
	if(FBd != 0)
	{
		printf("Успех!\n");
	}
	else
	{
		printf("Файл %s не найден или недоступен для открытия. Выход...\n",fileBodyName);
		exit(1);
	}
	fseek(FBd, 0, SEEK_SET);
	printDebugMsg(0,0,0);
	printDebugMsg(6,0,0);
	printf(" Читаю первые 2004 байт файла-тела\n");
	fseek(FBd, 0, SEEK_SET);
	fread(fileInitialBuffer, 1, sizeof(fileInitialBuffer), FBd);
	printDebugMsg(0,0,0);
	printf(" Копирование заголовка в сборочный буфер\n");
	for(int i=0;i<44;i++)
	{
		fileMainBuffer[i]=(uint8_t)fileHeader[i];
		printDebugMsg(0,0,0);
		printf(" ADDR>>0x%02X DATA>>0x%02X [%c]\n",i,fileMainBuffer[i],fileMainBuffer[i]);
	}
	printDebugMsg(0,0,0);
	printf(" Копирование пакета данных в сборочный буфер\n");
	for(int i=44;i<2048;i++)
	{
		fileMainBuffer[i]=fileInitialBuffer[i-44];
	}
	printDebugMsg(0,0,0);
	printDebugMsg(7,0,0);
	printf(" Открываю создаю файл %s и инициализирую запись первых 2048 байт... ",fileTargetName);
	FTg=fopen(fileTargetName, "wb");
	if(FTg != 0)
	{
		printf("Успех!\n");
	}
	else
	{
		printf("Файл %s не найден или недоступен для открытия. Выход...\n",fileTargetName);
		exit(1);
	}
	fseek(FTg, 0, SEEK_SET);
	fwrite(fileMainBuffer, 1, sizeof(fileMainBuffer), FTg);
	printDebugMsg(0,0,0);
	printDebugMsg(7,0,0);
	printf(" Инициирую циклическую запись блоками по %d Байт\n",sizeof(fileMainBuffer));
	numberOfIterations=(SamplesInChannel-modOfDiv-2004)/sizeof(fileMainBuffer);
	printDebugMsg(0,0,0);
	printf(" Суммарное количество блоков размером %d байт на запись: %d\n",sizeof(fileMainBuffer),numberOfIterations);
	scanStartPos=sizeof(fileInitialBuffer);
	while(writeIterations<numberOfIterations)
	{
		fseek(FBd,scanStartPos,SEEK_SET);
		fread(fileMainBuffer,1,sizeof(fileMainBuffer),FBd);
		fwrite(fileMainBuffer,1,sizeof(fileMainBuffer),FTg);
		scanStartPos=scanStartPos+sizeof(fileMainBuffer);
		writeIterations++;
	}
	
	
	fclose(FSt);
	fclose(FBd);
	fclose(FTg);
	
	printDebugMsg(0,0,0);
	printDebugMsg(2,0,0);
	//printDebugMsg(0,0,0);		//КОСТЫЛЬ НА АВТОМАТИЗАЦИЮ
	//printDebugMsg(3,0,0);
	return 0;
}
void printDebugMsg(uint8_t msgCode, uint8_t codeParameter, char charParameter)
{
	switch(msgCode)
	{
		case 0:
			printf("[ОТЛАДКА]");
			break;
		case 1:
			printf(" Начало работы программы-сшивателя\n");
			break;
		case 2:
			printf(" Работа завершена! Полученный файл готов к преобразованию в двоичный код\n");
			break;
		case 3:
			printf(" Нажмите Enter для выхода из программы\n");
			getchar();
			exit(1);
			break;
		case 4:
			printf("[СКАНИРОВАНИЕ СТРУКТУРЫ]");
			break;
		case 5:
			printf("[ЗАГРУЗКА ПАРАМЕТРОВ]");
			break;
		case 6:
			printf("[ЧТЕНИЕ]");
			break;
		case 7:
			printf("[ЗАПИСЬ]");
			break;
	}
}
