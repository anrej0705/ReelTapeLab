#include<locale.h>																																//Áèáëèîòåêà ëîêàëèçàöé, íóæíà äëÿ ğóññêîãî ÿçûêà â êîíñîëè
#include<stdbool.h>																																//Áèáëèîòåêà äëÿ ğàáîòû ñ äâîè÷íûìè ÷èñëàì, C99
#include<stdint.h>																																//Áèáèëîòåêà äëÿ ğàáîòû ñ íåñòàíäàğòíûìè ÷èñëàìè uint8_t, uint16_t, uint32_t
#include<stdio.h>																																//Áèáëèîòåêà äëÿ ğàáîòû ñ êîíñîëüş, âûâîä â êîíñîëü è ñ÷èòûâàíèå ñ íåå
#include<conio.h>																																//Áèáèëîòåêà
#include<stdlib.h>																																//Áèáèëîòåêà
#include<string.h>																																//Áèáëèîòåêà
#include<math.h>																																//Áèáëèîòåêà ñ ìàòåìàòè÷åñêèìè ôóíêöèÿìè
#define RusLang							setlocale(LC_ALL, "Rus")
#define buildVersion					" v0.0.1\n"																								//âåğñèÿ áèëäà. Â äàííûé ìîìåíò èäåò àëüôà òåñò
FILE* FSt;																																		//äëÿ ğàáîòû ñ ôàéëîì convertParams.ini
FILE* FHd;																																		//äëÿ ğàáîòû ñ ôàéëîì çàãîëîâêà
FILE* FBd;																																		//äëÿ ğàáîòû ñ ôàéëîì òåëà
FILE* FTg;																																		//äëÿ ğàáîòû ñ ğåçóëüòàòîì
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
	printf(" Óñòàíîâëåí ğàçìåğ áóôåğà ÷òåíèÿ-çàïèñè: %d Áàéò\n",sizeof(fileMainBuffer));
	printDebugMsg(0,0,0);
	printf(" Óñòàíîâëåí ğàçìåğ ñáîğî÷íîãî áóôåğà: %d Áàéò\n",sizeof(fileInitialBuffer));
	
	
	printDebugMsg(0,0,0);
	printf(" Îòêğûâàş ôàéë íàñòğîåê convertParams.ini... ");
	FSt=fopen("convertParams.ini","rb");
	if(FSt != 0)
	{
		printf("Óñïåõ!\n");
	}
	else
	{
		printf("Ôàéë convertParams.ini íå íàéäåí èëè íåäîñòóïåí äëÿ îòêğûòèÿ. Âûõîä...\n");
		exit(1);
	}
	fread(FSetBuffer, 1, sizeof(FSetBuffer), FSt);
	
	printDebugMsg(0,0,0);
	printDebugMsg(4,0,0);
	printf(" Èùó ñëîâî: %s...",TagFileHeaderStart);
	startPos=strstr(FSetBuffer,TagFileHeaderStart);
	TagFileHeaderStartPos=startPos-FSetBuffer;
	printf(" Íàéäåíî, ñìåùåíèå íà %d Áàéò\n",TagFileHeaderStartPos);
	printDebugMsg(0,0,0);
	printDebugMsg(4,0,0);
	printf(" Èùó ñëîâî: %s...",TagFileHeaderEnd);
	startPos=strstr(FSetBuffer,TagFileHeaderEnd);
	TagFileHeaderEndPos=startPos-FSetBuffer;
	printf(" Íàéäåíî, ñìåùåíèå íà %d Áàéò\n",TagFileHeaderEndPos);
	printDebugMsg(0,0,0);
	printDebugMsg(4,0,0);
	printf(" Èùó ñëîâî: %s...",TagFileBodyStart);
	startPos=strstr(FSetBuffer,TagFileBodyStart);
	TagFileBodyStartPos=startPos-FSetBuffer;
	printf(" Íàéäåíî, ñìåùåíèå íà %d Áàéò\n",TagFileBodyStartPos);
	printDebugMsg(0,0,0);
	printDebugMsg(4,0,0);
	printf(" Èùó ñëîâî: %s...",TagFileBodyEnd);
	startPos=strstr(FSetBuffer,TagFileBodyEnd);
	TagFileBodyEndPos=startPos-FSetBuffer;
	printf(" Íàéäåíî, ñìåùåíèå íà %d Áàéò\n",TagFileBodyEndPos);
	printDebugMsg(0,0,0);
	printDebugMsg(4,0,0);
	printf(" Èùó ñëîâî: %s...",TagFileTargetStart);
	startPos=strstr(FSetBuffer,TagFileTargetStart);
	TagFileTargetStartPos=startPos-FSetBuffer;
	printf(" Íàéäåíî, ñìåùåíèå íà %d Áàéò\n",TagFileTargetStartPos);
	printDebugMsg(0,0,0);
	printDebugMsg(4,0,0);
	printf(" Èùó ñëîâî: %s...",TagFileTargetEnd);
	startPos=strstr(FSetBuffer,TagFileTargetEnd);
	TagFileTargetEndPos=startPos-FSetBuffer;
	printf(" Íàéäåíî, ñìåùåíèå íà %d Áàéò\n",TagFileTargetEndPos);
	printDebugMsg(0,0,0);
	printDebugMsg(4,0,0);
	printf(" Èùó ñëîâî: %s...",TagSamplesInChannel);
	startPos=strstr(FSetBuffer,TagSamplesInChannel);
	TagSamplesInChannelPos=startPos-FSetBuffer;
	printf(" Íàéäåíî, ñìåùåíèå íà %d Áàéò\n",TagSamplesInChannelPos);
	printDebugMsg(0,0,0);
	printDebugMsg(4,0,0);
	printf(" Ñêàíèğîâàíèå òåãîâ çàâåğøåíî\n");
	
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
	printf(" Çàäàííîå èìÿ ôàéëà ñ çàãîëîâêîì: %s\n",fileHeaderName);
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
	printf(" Çàäàííîå èìÿ ôàéëà ñ òåëîì: %s\n",fileBodyName);
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
	printf(" Çàäàííîå êîíå÷íîå èìÿ ôàéëà: %s\n",fileTargetName);
	scanStartPos=TagSamplesInChannelPos+wordSamplesValueShift;
	fseek(FSt,scanStartPos,SEEK_SET);
	fscanf(FSt,"%d",&SamplesInChannel);
	printDebugMsg(0,0,0);
	printDebugMsg(5,0,0);
	printf(" Êîëè÷åñòâî ñåìïëîâ â ôàéëå: %d\n",SamplesInChannel);
	modOfDiv=fmod(SamplesInChannel, sizeof(fileMainBuffer));
	printDebugMsg(0,0,0);
	printf(" Îñòàòî÷íûé ïàêåò áàéòîâ: %f\n",modOfDiv);
	roundedVal=round(modOfDiv);
	printDebugMsg(0,0,0);
	printf(" Îêğóãëåííîå çíà÷åíèå: %d\n", roundedVal);
	numberOfIterations=(SamplesInChannel-modOfDiv)/sizeof(fileMainBuffer);
	printDebugMsg(0,0,0);
	printf(" Ñóììàğíîå êîëè÷åñòâî áëîêîâ ğàçìåğîì %d áàéò íà çàïèñü: %d\n",sizeof(fileMainBuffer),numberOfIterations);
	
	printDebugMsg(0,0,0);
	printf(" Îòêğûâàş ôàéë çàãîëîâêà %s... ",fileHeaderName);
	FHd=fopen(fileHeaderName, "rb");
	if(FHd != 0)
	{
		printf("Óñïåõ!\n");
	}
	else
	{
		printf("Ôàéë %s íå íàéäåí èëè íåäîñòóïåí äëÿ îòêğûòèÿ. Âûõîä...\n",fileHeaderName);
		exit(1);
	}
	fseek(FHd, 0, SEEK_SET);
	fread(fileHeader, 1, sizeof(fileHeader), FHd);
	printDebugMsg(0,0,0);
	printf(" Çàãîëîâîê ïğî÷èòàí â áóôåğ\n");
	fclose(FHd);
	
	printDebugMsg(0,0,0);
	printf(" Îòêğûâàş ôàéë òåëà %s... ",fileBodyName);
	FBd=fopen(fileBodyName, "rb");
	if(FBd != 0)
	{
		printf("Óñïåõ!\n");
	}
	else
	{
		printf("Ôàéë %s íå íàéäåí èëè íåäîñòóïåí äëÿ îòêğûòèÿ. Âûõîä...\n",fileBodyName);
		exit(1);
	}
	fseek(FBd, 0, SEEK_SET);
	printDebugMsg(0,0,0);
	printDebugMsg(6,0,0);
	printf(" ×èòàş ïåğâûå 2004 áàéò ôàéëà-òåëà\n");
	fseek(FBd, 0, SEEK_SET);
	fread(fileInitialBuffer, 1, sizeof(fileInitialBuffer), FBd);
	printDebugMsg(0,0,0);
	printf(" Êîïèğîâàíèå çàãîëîâêà â ñáîğî÷íûé áóôåğ\n");
	for(int i=0;i<44;i++)
	{
		fileMainBuffer[i]=(uint8_t)fileHeader[i];
		printDebugMsg(0,0,0);
		printf(" ADDR>>0x%02X DATA>>0x%02X [%c]\n",i,fileMainBuffer[i],fileMainBuffer[i]);
	}
	printDebugMsg(0,0,0);
	printf(" Êîïèğîâàíèå ïàêåòà äàííûõ â ñáîğî÷íûé áóôåğ\n");
	for(int i=44;i<2048;i++)
	{
		fileMainBuffer[i]=fileInitialBuffer[i-44];
	}
	printDebugMsg(0,0,0);
	printDebugMsg(7,0,0);
	printf(" Îòêğûâàş ñîçäàş ôàéë %s è èíèöèàëèçèğóş çàïèñü ïåğâûõ 2048 áàéò... ",fileTargetName);
	FTg=fopen(fileTargetName, "wb");
	if(FTg != 0)
	{
		printf("Óñïåõ!\n");
	}
	else
	{
		printf("Ôàéë %s íå íàéäåí èëè íåäîñòóïåí äëÿ îòêğûòèÿ. Âûõîä...\n",fileTargetName);
		exit(1);
	}
	fseek(FTg, 0, SEEK_SET);
	fwrite(fileMainBuffer, 1, sizeof(fileMainBuffer), FTg);
	printDebugMsg(0,0,0);
	printDebugMsg(7,0,0);
	printf(" Èíèöèèğóş öèêëè÷åñêóş çàïèñü áëîêàìè ïî %d Áàéò\n",sizeof(fileMainBuffer));
	numberOfIterations=(SamplesInChannel-modOfDiv-2004)/sizeof(fileMainBuffer);
	printDebugMsg(0,0,0);
	printf(" Ñóììàğíîå êîëè÷åñòâî áëîêîâ ğàçìåğîì %d áàéò íà çàïèñü: %d\n",sizeof(fileMainBuffer),numberOfIterations);
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
	//printDebugMsg(0,0,0);		//ÊÎÑÒÛËÜ ÍÀ ÀÂÒÎÌÀÒÈÇÀÖÈŞ
	//printDebugMsg(3,0,0);
	return 0;
}
void printDebugMsg(uint8_t msgCode, uint8_t codeParameter, char charParameter)
{
	switch(msgCode)
	{
		case 0:
			printf("[ÎÒËÀÄÊÀ]");
			break;
		case 1:
			printf(" Íà÷àëî ğàáîòû ïğîãğàììû-ñøèâàòåëÿ\n");
			break;
		case 2:
			printf(" Ğàáîòà çàâåğøåíà! Ïîëó÷åííûé ôàéë ãîòîâ ê ïğåîáğàçîâàíèş â äâîè÷íûé êîä\n");
			break;
		case 3:
			printf(" Íàæìèòå Enter äëÿ âûõîäà èç ïğîãğàììû\n");
			getchar();
			exit(1);
			break;
		case 4:
			printf("[ÑÊÀÍÈĞÎÂÀÍÈÅ ÑÒĞÓÊÒÓĞÛ]");
			break;
		case 5:
			printf("[ÇÀÃĞÓÇÊÀ ÏÀĞÀÌÅÒĞÎÂ]");
			break;
		case 6:
			printf("[×ÒÅÍÈÅ]");
			break;
		case 7:
			printf("[ÇÀÏÈÑÜ]");
			break;
	}
}
