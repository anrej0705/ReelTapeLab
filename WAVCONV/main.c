#include<locale.h>																																//Áèáëèîòåêà ëîêàëèçàöé, íóæíà äëÿ ðóññêîãî ÿçûêà â êîíñîëè
#include<stdbool.h>																																//Áèáëèîòåêà äëÿ ðàáîòû ñ äâîè÷íûìè ÷èñëàì, C99
#include<stdint.h>																																//Áèáèëîòåêà äëÿ ðàáîòû ñ íåñòàíäàðòíûìè ÷èñëàìè uint8_t, uint16_t, uint32_t
#include<stdio.h>																																//Áèáëèîòåêà äëÿ ðàáîòû ñ êîíñîëüþ, âûâîä â êîíñîëü è ñ÷èòûâàíèå ñ íåå
#include<conio.h>																																//Áèáèëîòåêà
#include<stdlib.h>																																//Áèáèëîòåêà
#include<string.h>																																//Áèáëèîòåêà
#include<math.h>																																//Áèáëèîòåêà ñ ìàòåìàòè÷åñêèìè ôóíêöèÿìè
//#include<windows.h>
#define RusLang							setlocale(LC_ALL, "Rus")
#define buildVersion					" v0.0.2\n"																								//âåðñèÿ áèëäà. Â äàííûé ìîìåíò èäåò àëüôà òåñò
#define writeBufferSize					2048																									//êîíñòàíòà ðàçìåðà ìàññèâîâ ÷òåíèÿ è çàïèñè â ôàéëû. Ìåíÿòü òîëüêî å¸
#define inputBufferSize					writeBufferSize*4
FILE* FRd;
FILE* FIn;
FILE* FOut;
int wordSearch(char* wordToSearch);
float modOfDiv;
bool readConfig(void);
bool writeChunk(uint32_t *ptrParamMas, uint16_t ptrRange);
uint8_t bitShorter(uint8_t inputFormat, uint32_t inputWord);
uint8_t writeFile(uint8_t *ptrToWrite, uint16_t ptrRange, uint32_t writePointer);
uint8_t stereoToMonoMixer(uint8_t firstChannel, uint8_t secondChannel);
//uint8_t threeChToMonoMixer(uint8_t firstChannel, uint8_t secondChannel, uint8_t threeChannel);
//uint8_t quadroToMonoMixer(uint8_t firstChannel, uint8_t secondChannel, uint8_t threeChannel, uint8_t fourChannel);
//uint8_t OneByteSampleReader(char* filesStream, uint32_t posCursor);
uint16_t TwoBytesSampleReader(uint16_t posCursor);
//uint32_t ThreeByteSampleReader(char* filesStream, uint32_t posCursor);
//uint32_t FourByteSampleReader(char* filesStream, uint32_t posCursor);
void fileOpen(int openParam, char* fileName);
void fileClose(void);
void fileWrite(void);
void printDebugMsg(uint8_t msgCode, uint8_t codeParameter, char charParameter);
uint8_t crlfSign[2]={0x0D, 0x0A};																												//ìåòêà CR LF(ïåðåíîñ êàðåòêè íà íîâóþ ñòðîêó)	
uint8_t resultToWrite[writeBufferSize];																											//ìàññèâ, ñîäåðæàùèé â ñåáå ïîäãîòîâëåííóþ ê çàïèñè èíôîðìàöèþ
char SearchWord[100];
uint8_t fileMassive[inputBufferSize];																											//ìàññèâ â êîòîðûé ÷èòàåòñÿ ñîäåðæèìîå ôàéëà convertParams.ini
char fileBuffer[inputBufferSize];																												//ìàññèâ, â êîòîðûé áóäåò ïðîèçâîäèòüñÿ ÷òåíèå ñûðûõ äàííûõ
char fileSrcBuffer[64];
char fileNameBuffer[64];
char fileBodyBuffer[64];
char symbol;
char *wordSrcFilenameStart="FSRC";
char *wordFilenameStart="FNAM";
char *wordFilenameBody="FBOD";
char *wordSrcFilenameEnd="FSND";
char *wordNamFilenameEnd="FNND";
char *wordBodyFilenameEnd="FBND";
char *wordConvert="Convert";
char *wordSampleRate="SampleRate";
char *wordChannels="Channels";
char *wordBitsPerSample="BitsPerSample";
char *WordCountOfSamples="SamplesInChannel";																									//îáðàçåö òåãà SamplesInChannel
char *cursorSymbol;
const uint8_t HeaderSize=44;
const uint8_t wordTagRange=4;
const uint8_t wordTagStepBack=1;
const uint8_t wordConvertShift=8;
const uint8_t wordSampleRateShift=11;
const uint8_t wordChannelsShift=9;
const uint8_t wordBitsPerSampleShift=14;
const uint8_t wordSamplesValueShift=17;
bool checkIntegrity=0;
bool ConvertStat;
bool fileOpenFlag=0;
bool writeStat=0;
bool arrPrepared=0;
uint8_t byteShortCode=0;
uint8_t channelsValue;
uint8_t BitsPerSampleValue;
//uint8_t OneByteSample;
uint16_t fsrcPos;
uint16_t fnamPos;
uint16_t fbodPos;
uint16_t fsendPos;
uint16_t fnendPos;
uint16_t fbendPos;
uint16_t TwoByteSample;
uint32_t numberOfIterations;
//uint32_t ThreeByteSample;
//uint32_t FourByteSample;
uint32_t SampleRateValue;
uint32_t cursorPos;
uint32_t cursorPos2;
uint32_t wordConvertPos;
uint32_t wordSampleRatePos;
uint32_t wordChannelsPos;
uint32_t wordBitsPerSamplePos;
uint32_t wordSamplesValue;
uint32_t writeParameters[2]={0x00000000,0x00000000};
uint8_t oneByte=0x8D;
uint16_t twoByte=0x4E28;
uint32_t threeByte=0x0076BB81;
uint32_t fourByte=0xB1C39FB6;
uint32_t roundedVal=0;
uint32_t prepareArray(uint32_t startPos);
uint16_t returnedValue;
uint16_t firstChannel;
uint16_t secondChannel;
uint16_t threeChannel;
uint16_t fourChannel;
uint16_t j=0;
uint32_t samplesValue;																															//ñþäà áóäåò ïèñàòüñÿ êîëè÷åñòâî âûáîðîê â 1 êàíàëå ôàéëà
int main(void)
{
	setlocale(LC_ALL, "Rus");
	printDebugMsg(0,0,0);
	printf(" Ïðîãðàììà äëÿ ïîèñêà ãîâíîêîäà\n");
	printDebugMsg(0,0,0);
	printf(buildVersion);
	fileOpen(2, "convertParams.ini");
	if(!fileOpenFlag)
	{
		printDebugMsg(0,0,0);
		printDebugMsg(13,0,0);
		printf(" Ôàéë convertParams.ini íàéäåí è îòêðûò\n");
	}
	else
	{
		printf("ôàéë convertParams.ini íå íàéäåí, áóäåò ñîçäàí ôàéë ïî ïàðàìåòðàì\n");
		fileWrite();
		fileClose();
	}
	fileOpen(2, "convertParams.ini");
	fseek(FRd, 0, SEEK_SET);
	fread(fileMassive, 1, sizeof(fileMassive), FRd);
	for(int i=0;i<sizeof(fileMassive);i++)
	{
		fileBuffer[i]=fileMassive[i];
		//printf("%c",fileBuffer[i]);
	}
	checkIntegrity=readConfig();
	if(!checkIntegrity==0)
	{
		printDebugMsg(0,0,0);
		printf(" Ïðîâåðêà öåëîñòíîñòè ôàéëà ïàðàìåòðîâ âûïîëíåíà. Ïàðàìåòðû çàãðóæåíû â êîíâåðòåð\n");
	}
	printDebugMsg(0,0,0);
	printDebugMsg(13,0,0);
	printf(" Ïîïûòêà îòêðûòü ôàéë %s äëÿ ÷òåíèÿ... ",fileSrcBuffer);
	FIn=fopen(fileSrcBuffer, "rb");
	if(FIn != NULL)
	{
		printf("Óñïåõ\n");
	}
	printDebugMsg(0,0,0);
	printf(" Óñòàíîâëåí ðàçìåð áóôåðà ÷òåíèÿ â %d áàéò\n",sizeof(fileBuffer));
	printDebugMsg(0,0,0);
	printf(" Óñòàíîâëåí ðàçìåð áóôåðà çàïèñè â %d áàéò\n",sizeof(resultToWrite));
	byteShortCode=BitsPerSampleValue/8;
	printDebugMsg(0,0,0);
	printf(" Êîä âûçîâà ôóíêöèè byteShorter: %d\n",byteShortCode);
	printDebugMsg(0,0,0);
	printDebugMsg(14,0,0);
	printf(" Ñîçäàþ ôàéë íà çàïèñü ñ èìåíåì èç convertParams.ini: %s",fileBodyBuffer);
	FOut=fopen(fileBodyBuffer, "wb");
	//FOut=fopen("result.wav", "wb");
	if(FOut != NULL)
	{
		printf(" Óñïåõ!\n");
	}
	else
	{
		printf(" Ïðîèçîøëà îøèáêà, âûõîä...\n");
		exit(0);
	}
	modOfDiv=fmod(samplesValue, sizeof(resultToWrite));
	printDebugMsg(0,0,0);
	printf(" Îñòàòî÷íûé ïàêåò áàéòîâ: %f\n",modOfDiv);
	roundedVal=round(modOfDiv);
	printDebugMsg(0,0,0);
	printf(" Îêðóãëåííîå çíà÷åíèå: %d\n", roundedVal);
	numberOfIterations=(samplesValue-modOfDiv)/sizeof(resultToWrite);
	printDebugMsg(0,0,0);
	printf(" Ñóììàðíîå êîëè÷åñòâî áëîêîâ ðàçìåðîì %d áàéò íà çàïèñü: %d\n",sizeof(resultToWrite),numberOfIterations);
	cursorPos2=HeaderSize;
	writeParameters[0]=cursorPos2;
	
	for(uint32_t i=0;i<numberOfIterations;i++)
	{	
		//printf("×àíê ¹%d\n",i);
		cursorPos2=prepareArray(cursorPos2);
		writeStat=writeChunk(writeParameters,sizeof(resultToWrite));
		if(writeStat==0)
		{
			//printf("×àíê ¹%d â %d áàéò óñïåøíî çàïèñàí\n",i,sizeof(resultToWrite));
		}
	}
	fseek(FRd, 0, SEEK_SET);
	fread(fileMassive, 1, sizeof(fileMassive), FRd);
	for(int i=0;i<sizeof(fileMassive);i++)
	{
		fileBuffer[i]=fileMassive[i];
		//printf("%c",fileBuffer[i]);
	}
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Èùó ñëîâî: %s\n", wordConvert);
	cursorSymbol=strstr(fileBuffer, wordConvert);
	wordConvertPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Íà÷àëî ñëîâà íà: %d Áàéò\n", wordConvertPos);
	cursorPos=wordConvertPos+wordConvertShift;
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &ConvertStat);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Ôëàã êîíâåðòàöèè: %d\n", ConvertStat);
	printDebugMsg(0,0,0);
	printDebugMsg(16,0,0);
	printf("Îáíîâëÿþ ôëàã êîíâåðòàöèè...\n");
	fclose(FRd);
	fileOpen(4, "convertParams.ini");
	fseek(FRd, cursorPos, SEEK_SET);
	fprintf(FRd, "1");
	fclose(FRd);
	fileOpen(2, "convertParams.ini");
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &ConvertStat);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Ôëàã êîíâåðòàöèè: %d\n", ConvertStat);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Íà÷àëî ñëîâà íà: %d Áàéò\n", wordChannelsPos);
	cursorPos=wordChannelsPos+wordChannelsShift;
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &channelsValue);
	printDebugMsg(0,0,0);
	printDebugMsg(16,0,0);
	printf("Îáíîâëÿþ êîëè÷åñòâî êàíàëîâ...\n");
	fclose(FRd);
	fileOpen(4, "convertParams.ini");
	fseek(FRd, cursorPos, SEEK_SET);
	fprintf(FRd, "1");
	fclose(FRd);
	fileOpen(2, "convertParams.ini");
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &ConvertStat);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Êîëè÷åñòâî êàíàëîâ: %d\n", channelsValue);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Íà÷àëî ñëîâà íà: %d Áàéò\n", wordBitsPerSamplePos);
	cursorPos=wordBitsPerSamplePos+wordBitsPerSampleShift;
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &BitsPerSampleValue);
	printDebugMsg(0,0,0);
	printDebugMsg(16,0,0);
	printf("Îáíîâëÿþ çíà÷åíèå ãëóáèíû âûáîðêè...\n");
	fclose(FRd);
	fileOpen(4, "convertParams.ini");
	fseek(FRd, cursorPos, SEEK_SET);
	fprintf(FRd, "8 ");
	fclose(FRd);
	fileOpen(2, "convertParams.ini");
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &ConvertStat);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Ãëóáèíà âûáîðêè: %d áèò\n", BitsPerSampleValue);
	fclose(FRd);
	
	fclose(FOut);
	fclose(FIn);
	fileClose();
	printDebugMsg(0,0,0);
	printDebugMsg(17,0,0);
	//printDebugMsg(0,0,0);				//ÊÎÑÒÛËÜ ÍÀ ÀÂÒÎÌÀÒÈÇÀÖÈÞ
	//printDebugMsg(15,0,0);
	//getchar();
	return 0;
}
void fileOpen(int openParam, char* fileName)
{
	switch(openParam)
	{
		case 0:
			FRd=fopen(fileName, "r");
			break;
		case 1:
			FRd=fopen(fileName, "w");
			break;
		case 2:
			FRd=fopen(fileName, "rb");
			break;
		case 3:
			FRd=fopen(fileName, "wb");
			break;
		case 4:
			FRd=fopen(fileName, "rb+");
			break;
		case 5:
			FRd=fopen(fileName, "wb+");
			break;
	}
	if(!FRd)
	{
		fileOpenFlag=1;
	}
	else
	{
		fileOpenFlag=0;
	}
}
void fileWrite(void)
{
	char *WordConvert="Convert=";
	char *WordSamples="SampleRate=";
	char *WordChannels="Channels=";
	char *WordBits="BitsPerSample=";
	char *WordCountOfSamples="SamplesInChannel=";																								//îáðàçåö òåãà SamplesInChannel
	int smprt=192000;
	int chnls=2;
	int cnvrt=1;
	int bits=24;
	uint8_t crlfSign[2]={0x0D, 0x0A};
	printf("Íàïèøèòå ÷àñòîòó äèñêðåòèçàöèè â Ãö: ");
	scanf("%d", &smprt);
	printf("Íàïèøèòå êîëè÷åñòâî êàíàëîâ, íå áîëüøå 4: ");
	scanf("%d", &chnls);
	printf("Óêàæèòå ðàçðÿäíîñòü, â áèòàõ: ");
	scanf("%d", &bits);
	fileOpen(3, "convertParams.ini");
	fseek(FRd, 0, SEEK_SET);
	fprintf(FRd, "%s", WordConvert);
	fprintf(FRd, "%d", cnvrt);
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FRd);
	fprintf(FRd, "%s", WordSamples);
	fprintf(FRd, "%d", smprt);
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FRd);
	fprintf(FRd, "%s", WordChannels);
	fprintf(FRd, "%d", chnls);
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FRd);
	fprintf(FRd, "%s", WordBits);
	fprintf(FRd, "%d", bits);
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FRd);
}
void fileClose(void)
{
	fclose(FRd);
}
bool readConfig(void)
{
	bool checkFileIntegrity=0;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Èùó ñëîâî: %s (òåã FSRC)\n", wordSrcFilenameStart);
	cursorSymbol=strstr(fileBuffer, wordSrcFilenameStart);
	fsrcPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Íà÷àëî ñëîâà íà: %d Áàéò\n", fsrcPos);
	fseek(FRd, fsrcPos+wordTagRange, SEEK_SET);
	fsrcPos=ftell(FRd);
	symbol=fgetc(FRd);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Ïðîâåðêà íàëè÷èÿ óêàçàòåëÿ íà÷àëà èìåíè ôàéëà... ");
	if(symbol==0x3E)
	{
		printf("Óêàçàòåëü íàéäåí");
		fsrcPos++;
		checkFileIntegrity=1;
	}
	printf("(%d)\n",fsrcPos);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Èùó ñëîâî: %s (òåã FSND)\n", wordSrcFilenameEnd);
	cursorSymbol=strstr(fileBuffer, wordSrcFilenameEnd);
	fsendPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Íà÷àëî ñëîâà íà: %d Áàéò\n", fsendPos);
	fseek(FRd, fsendPos-wordTagStepBack, SEEK_SET);
	fsendPos=ftell(FRd);
	symbol=fgetc(FRd);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Ïðîâåðêà íàëè÷èÿ óêàçàòåëÿ êîíöà èìåíè ôàéëà... ");
	if(symbol==0x3E)
	{
		printf("Óêàçàòåëü íàéäåí");
		checkFileIntegrity=1;
	}
	printf("(%d)\n",fsendPos);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Èùó ñëîâî: %s (òåã FNAM)\n", wordFilenameStart);
	cursorSymbol=strstr(fileBuffer, wordFilenameStart);
	fnamPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Íà÷àëî ñëîâà íà: %d Áàéò\n", fnamPos);
	fseek(FRd, fnamPos+wordTagRange, SEEK_SET);
	fnamPos=ftell(FRd);
	symbol=fgetc(FRd);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Ïðîâåðêà íàëè÷èÿ óêàçàòåëÿ íà÷àëà èìåíè ôàéëà... ");
	if(symbol==0x3E)
	{
		printf("Óêàçàòåëü íàéäåí");
		fnamPos++;
		checkFileIntegrity=1;
	}
	printf("(%d)\n",fnamPos);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Èùó ñëîâî: %s (òåã FNND)\n", wordNamFilenameEnd);
	cursorSymbol=strstr(fileBuffer, wordNamFilenameEnd);
	fnendPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Íà÷àëî ñëîâà íà: %d Áàéò\n", fnendPos);
	fseek(FRd, fnendPos-wordTagStepBack, SEEK_SET);
	fnendPos=ftell(FRd);
	symbol=fgetc(FRd);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Ïðîâåðêà íàëè÷èÿ óêàçàòåëÿ êîíöà èìåíè ôàéëà... ");
	if(symbol==0x3E)
	{
		printf("Óêàçàòåëü íàéäåí");
		checkFileIntegrity=1;
	}
	printf("(%d)\n",fnendPos);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Èùó ñëîâî: %s (òåã FBOD)\n", wordFilenameBody);
	cursorSymbol=strstr(fileBuffer, wordFilenameBody);
	fbodPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Íà÷àëî ñëîâà íà: %d Áàéò\n", fbodPos);
	fseek(FRd, fbodPos+wordTagRange, SEEK_SET);
	fbodPos=ftell(FRd);
	symbol=fgetc(FRd);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Ïðîâåðêà íàëè÷èÿ óêàçàòåëÿ êîíöà èìåíè ôàéëà... ");
	if(symbol==0x3E)
	{
		printf("Óêàçàòåëü íàéäåí");
		checkFileIntegrity=1;
	}
	printf("(%d)\n",fbodPos);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Èùó ñëîâî: %s (òåã FBND)\n", wordBodyFilenameEnd);
	cursorSymbol=strstr(fileBuffer, wordBodyFilenameEnd);
	fbendPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Íà÷àëî ñëîâà íà: %d Áàéò\n", fbendPos);
	fseek(FRd, fbendPos-wordTagStepBack, SEEK_SET);
	fbendPos=ftell(FRd);
	symbol=fgetc(FRd);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Ïðîâåðêà íàëè÷èÿ óêàçàòåëÿ êîíöà èìåíè ôàéëà... ");
	if(symbol==0x3E)
	{
		printf("Óêàçàòåëü íàéäåí");
		checkFileIntegrity=1;
	}
	printf("(%d)\n",fbendPos);
	memset(fileSrcBuffer,0x00,sizeof(fileSrcBuffer));
	memset(fileNameBuffer,0x00,sizeof(fileNameBuffer));
	cursorPos=0;
	cursorPos2=fsrcPos;
	while(cursorPos2<fsendPos)
	{
		fileSrcBuffer[cursorPos]=fileBuffer[cursorPos2];
		//printf("%c",fileSrcBuffer[cursorPos]);
		//printf("%d>%d ",cursorPos2,cursorPos);
		cursorPos2++;
		cursorPos++;
	}
	cursorPos=0;
	cursorPos2=fnamPos;
	while(cursorPos2<fnendPos)
	{
		fileNameBuffer[cursorPos]=fileBuffer[cursorPos2];
		//printf("%c",fileNameBuffer[cursorPos]);
		//printf("%d>%d ",cursorPos2,cursorPos);
		cursorPos2++;
		cursorPos++;
	}
	cursorPos=0;
	cursorPos2=fbodPos+1;																														//êîñòûëü
	while(cursorPos2<fbendPos)
	{
		fileBodyBuffer[cursorPos]=fileBuffer[cursorPos2];
		//printf("%c",fileBodyBuffer[cursorPos]);
		//printf("%d>%d ",cursorPos2,cursorPos);
		cursorPos2++;
		cursorPos++;
	}
	cursorPos=0;
	cursorPos2=0;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Äèàïàçîí èìåíè èñõîäíîãî ôàéëà %d...%d(%s)\n",fsrcPos,fsendPos,fileSrcBuffer);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Äèàïàçîí èìåíè çàãîëîâî÷íîãî ôàéëà %d...%d(%s)\n",fnamPos,fnendPos,fileNameBuffer);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Äèàïàçîí èìåíè ôàéëà-êîíòåéíåðà òåëà %d...%d(%s)\n",fbodPos,fbendPos,fileBodyBuffer);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Èùó ñëîâî: %s\n", wordConvert);
	cursorSymbol=strstr(fileBuffer, wordConvert);
	wordConvertPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Íà÷àëî ñëîâà íà: %d Áàéò\n", wordConvertPos);
	cursorPos=wordConvertPos+wordConvertShift;
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &ConvertStat);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Ôëàã êîíâåðòàöèè: %d", ConvertStat);
	if(ConvertStat==0)
	{
		printf(", íåîáõîäèìà êîíâåðòàöèÿ\n");
	}
	else
	{
		printf(", êîíâåðòàöèÿ óæå áûëà ïðîâåäåíà. Íåîáõîäèìî ñêëåèòü çàãîëîâîê è òåëî\n");
	}
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Èùó ñëîâî: %s\n", wordSampleRate);
	cursorSymbol=strstr(fileBuffer, wordSampleRate);
	wordSampleRatePos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Íà÷àëî ñëîâà íà: %d Áàéò\n", wordSampleRatePos);
	cursorPos=wordSampleRatePos+wordSampleRateShift;
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &SampleRateValue);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("×àñòîòà äèñêðåòèçàöèè: %d Ãö\n", SampleRateValue);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Èùó ñëîâî: %s\n", wordChannels);
	cursorSymbol=strstr(fileBuffer, wordChannels);
	wordChannelsPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Íà÷àëî ñëîâà íà: %d Áàéò\n", wordChannelsPos);
	cursorPos=wordChannelsPos+wordChannelsShift;
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &channelsValue);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Êîëè÷åñòâî êàíàëîâ: %d, ", channelsValue);
	switch(channelsValue)
	{
		case 1:
			printf("ìîíî\n");
			break;
		case 2:
			printf("ñòåðåî\n");
			break;
		case 4:
			printf("êâàäðî\n");
			break;
	}
	
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);	
	printf("Èùó ñëîâî: %s\n", wordBitsPerSample);
	cursorSymbol=strstr(fileBuffer, wordBitsPerSample);
	wordBitsPerSamplePos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Íà÷àëî ñëîâà íà: %d Áàéò\n", wordBitsPerSamplePos);
	cursorPos=wordBitsPerSamplePos+wordBitsPerSampleShift;
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &BitsPerSampleValue);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Ãëóáèíà âûáîðêè: %d áèò\n", BitsPerSampleValue);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);	
	printf("Èùó ñëîâî: %s\n", WordCountOfSamples);
	cursorSymbol=strstr(fileBuffer, WordCountOfSamples);
	wordSamplesValue=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Íà÷àëî ñëîâà íà: %d Áàéò\n", wordSamplesValue);
	cursorPos=wordSamplesValue+wordSamplesValueShift;
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &samplesValue);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("Ñóììàðíîå êîëè÷åñòâî âûáîðîê â îäíîì êàíàëå: %d\n", samplesValue);
	return checkFileIntegrity;
}
uint8_t bitShorter(uint8_t inputFormat, uint32_t inputWord)
{
	switch(inputFormat)
	{
		case 0:
			printf("Òàêîãî ôîðìàòà äàííûõ íå áûâàåò!");
			break;
		case 1:
			return inputWord;
			break;
		case 2:
			inputWord=inputWord>>8;
			return inputWord;
			break;
		case 3:
			inputWord=inputWord>>16;
			return inputWord;
			break;
		case 4:
			inputWord=inputWord>>24;
			return inputWord;
			break;
	}
}
uint32_t prepareArray(uint32_t startPos)
{
	uint16_t scanCursor;
	fseek(FIn, startPos, SEEK_SET);
	fread(fileMassive, 1, sizeof(fileMassive), FIn);
	for(uint16_t i=0;i<sizeof(fileBuffer);i++)
	{
		fileBuffer[i]=(uint8_t)fileMassive[i];
	}
	startPos=startPos+sizeof(fileBuffer);
	arrPrepared=1;
	return startPos;
}
/*uint8_t OneByteSampleReader(char* filesStream, uint32_t posCursor)
{
	
}*/
uint16_t TwoBytesSampleReader(uint16_t posCursor)
{
	//printf("Íà÷àëî ðàáîòû ôóíêöèè ñ÷èòûâàíèÿ 16 ðàçðÿäíûõ ñåìïëîâ...\n");
	uint16_t tempVal;
	uint8_t tempVal8;
	uint8_t oneByte[2];
	memset(oneByte, 0x00, sizeof(oneByte));
	//printf("Ïîçèöèÿ êóðñîðà â ôàéëå: %d\n",posCursor);
	//fseek(FIn, posCursor, SEEK_SET);
	//fread(oneByte, 2, sizeof(oneByte), FIn);
	oneByte[0]=fileMassive[posCursor];
	oneByte[1]=fileMassive[posCursor+1];
	tempVal8=oneByte[0];
	//printf("Ñòàðøèé áàéò: 0x%02X\n", tempVal8);
	tempVal8=oneByte[1];
	//printf("Ìëàäøèé áàéò: 0x%02X\n", tempVal8);
	tempVal=oneByte[0];
	tempVal=tempVal|oneByte[1]<<8;
	//printf("Ïîëó÷åííûé 16 áèòíûé ñåìïë: 0x%04X\n",tempVal);
	return tempVal;
}
/*uint32_t ThreeByteSampleReader(char* filesStream, uint32_t posCursor)
{
	
}*/
/*uint32_t FourByteSampleReader(char* filesStream, uint32_t posCursor)
{
	
}*/
uint8_t stereoToMonoMixer(uint8_t firstChannel, uint8_t secondChannel)
{
	uint8_t valueToReturn;
	uint16_t scrapValue;
	//printf("íà÷àëî ðàáîòû ìèêøåðà êàíàëîâ...\n");
	scrapValue = firstChannel+secondChannel;
	//printf("Ïðîìåæóòî÷íàÿ ïåðåìåííàÿ(16 áèò): 0x%04X\n",scrapValue);
	valueToReturn = scrapValue/2;
	//printf("Ïåðåìåííàÿ íà âûäà÷ó: 0x%02X\n",valueToReturn);
	return valueToReturn;
}
/*uint8_t threeChToMonoMixer(uint8_t firstChannel, uint8_t secondChannel, uint8_t threeChannel);
{
	
}*/
/*uint8_t quadroToMonoMixer(uint8_t firstChannel, uint8_t secondChannel, uint8_t threeChannel, uint8_t fourChannel);
{
	
}*/
uint8_t writeFile(uint8_t *ptrToWrite, uint16_t ptrRange, uint32_t writePointer)
{
	uint16_t scanCursor=0;
	uint8_t returnValue;
	fseek(FOut,writePointer,SEEK_SET);
	returnValue=fwrite(ptrToWrite, 1, ptrRange, FOut);
	return returnValue;
}
bool writeChunk(uint32_t *ptrParamMas, uint16_t ptrRange)
{
	uint8_t tempArr[2];
	uint16_t indexOne=0;
	uint16_t writeResult;
	uint32_t fOutWriteCursor=ptrParamMas[1];
	//printf("Óêàçàòåëü íà ïîçèöèþ â ïîòîêå FOut: %d\n",fOutWriteCursor);
	for(int i=0;i<sizeof(fileBuffer);i=i+4)
	{
		TwoByteSample=TwoBytesSampleReader(i);
		firstChannel=bitShorter(byteShortCode,TwoByteSample);
		firstChannel=firstChannel-128;
		//printf("bitShorter âåðíóë çíà÷åíèå(1 êàíàë): 0x%02X\n", firstChannel);
		TwoByteSample=TwoBytesSampleReader(i+2);
		secondChannel=bitShorter(byteShortCode,TwoByteSample);
		secondChannel=secondChannel-128;
		//printf("bitShorter âåðíóë çíà÷åíèå(2 êàíàë): 0x%02X\n", secondChannel);
		returnedValue=stereoToMonoMixer(firstChannel,secondChannel);
		//printf("Ñðåäíåå äâóõ êàíàëîâ: 0x%02X\n", returnedValue);
		resultToWrite[indexOne]=returnedValue;
		indexOne++;
		//printf("Èíäåêñ ìàññèâà: %d\n", indexOne);
	}
	writeResult = writeFile(resultToWrite, ptrRange, fOutWriteCursor);
	fOutWriteCursor=fOutWriteCursor+sizeof(resultToWrite);
	memset(resultToWrite, 0x00, sizeof(resultToWrite));
	arrPrepared=0;
	writeParameters[1]=fOutWriteCursor;
	return writeResult;
	
}
void printDebugMsg(uint8_t msgCode, uint8_t codeParameter, char charParameter)
{
	switch(msgCode)
	{
		case 0:
			printf("[ÎÒËÀÄÊÀ]");
			break;
		case 1:
			printf("[ÇÀÃÐÓÇÊÀ ÏÀÐÀÌÅÒÐÎÂ] ");
			break;
		case 2:
			printf("Íå íàéäåí ");
			break;
		case 3:
			printf("òåã FSRC\n");
			break;
		case 4:
			printf("òåã FNAM\n");
			break;
		case 5:
			printf("òåã FSND\n");
			break;
		case 6:
			printf("òåã FNND\n");
			break;
		case 7:
			printf("Âûõîä...");
			exit(1);
			break;
		case 8:
			printf("óêàçàòåëü íà÷àëà ");
			break;
		case 9:
			printf("óêàçàòåëü êîíöà ");
			break;
		case 10:
			printf("èñõîäíîãî ");
			break;
		case 11:
			printf("ñãåíåðèðîâàííîãî ");
			break;
		case 12:
			printf("èìåíè ôàéëà\n");
			break;
		case 13:
			printf("[×ÒÅÍÈÅ]");
			break;
		case 14:
			printf("[ÇÀÏÈÑÜ]");
			break;
		case 15:
			printf(" Ðàáîòà çàâåðøåíà. Íàæìèòå Enter äëÿ âûõîäà èç ïðîãðàììû...");
			break;
		case 16:
			printf("[ÇÀÏÈÑÜ ÏÀÐÀÌÅÒÐÎÂ] ");
			break;
		case 17:
			printf(" Ðàáîòà çàâåðøåíà. Òåïåðü íåîáõîäèìî ïîâòîðíî çàïóñòèòü Exheader äëÿ ôîðìèðîâàíèÿ\n	  ôàéëà çàãîëîâêà èç çàïèñàííûõ ïîñëå êîíâåðòàöèè ïàðàìåòðîâ\n");
			break;
	}
}
