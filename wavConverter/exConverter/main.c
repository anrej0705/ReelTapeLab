#include<locale.h>																																//���������� ����������, ����� ��� �������� ����� � �������
#include<stdbool.h>																																//���������� ��� ������ � ��������� ������, C99
#include<stdint.h>																																//���������� ��� ������ � �������������� ������� uint8_t, uint16_t, uint32_t
#include<stdio.h>																																//���������� ��� ������ � ��������, ����� � ������� � ���������� � ���
#include<conio.h>																																//����������
#include<stdlib.h>																																//����������
#include<string.h>																																//����������
#include<math.h>																																//���������� � ��������������� ���������
//#include<windows.h>
#define RusLang							setlocale(LC_ALL, "Rus")
#define buildVersion					" v0.0.2\n"																								//������ �����. � ������ ������ ���� ����� ����
#define writeBufferSize					2048																									//��������� ������� �������� ������ � ������ � �����. ������ ������ �
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
uint8_t crlfSign[2]={0x0D, 0x0A};																												//����� CR LF(������� ������� �� ����� ������)	
uint8_t resultToWrite[writeBufferSize];																											//������, ���������� � ���� �������������� � ������ ����������
char SearchWord[100];
uint8_t fileMassive[inputBufferSize];																											//������ � ������� �������� ���������� ����� convertParams.ini
char fileBuffer[inputBufferSize];																												//������, � ������� ����� ������������� ������ ����� ������
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
char *WordCountOfSamples="SamplesInChannel";																									//������� ���� SamplesInChannel
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
uint32_t samplesValue;																															//���� ����� �������� ���������� ������� � 1 ������ �����
int main(void)
{
	setlocale(LC_ALL, "Rus");
	printDebugMsg(0,0,0);
	printf(" ��������� ��� ������ ���������\n");
	printDebugMsg(0,0,0);
	printf(buildVersion);
	fileOpen(2, "convertParams.ini");
	if(!fileOpenFlag)
	{
		printDebugMsg(0,0,0);
		printDebugMsg(13,0,0);
		printf(" ���� convertParams.ini ������ � ������\n");
	}
	else
	{
		printf("���� convertParams.ini �� ������, ����� ������ ���� �� ����������\n");
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
		printf(" �������� ����������� ����� ���������� ���������. ��������� ��������� � ���������\n");
	}
	printDebugMsg(0,0,0);
	printDebugMsg(13,0,0);
	printf(" ������� ������� ���� %s ��� ������... ",fileSrcBuffer);
	FIn=fopen(fileSrcBuffer, "rb");
	if(FIn != NULL)
	{
		printf("�����\n");
	}
	printDebugMsg(0,0,0);
	printf(" ���������� ������ ������ ������ � %d ����\n",sizeof(fileBuffer));
	printDebugMsg(0,0,0);
	printf(" ���������� ������ ������ ������ � %d ����\n",sizeof(resultToWrite));
	byteShortCode=BitsPerSampleValue/8;
	printDebugMsg(0,0,0);
	printf(" ��� ������ ������� byteShorter: %d\n",byteShortCode);
	printDebugMsg(0,0,0);
	printDebugMsg(14,0,0);
	printf(" ������ ���� �� ������ � ������ �� convertParams.ini: %s",fileBodyBuffer);
	FOut=fopen(fileBodyBuffer, "wb");
	//FOut=fopen("result.wav", "wb");
	if(FOut != NULL)
	{
		printf(" �����!\n");
	}
	else
	{
		printf(" ��������� ������, �����...\n");
		exit(0);
	}
	modOfDiv=fmod(samplesValue, sizeof(resultToWrite));
	printDebugMsg(0,0,0);
	printf(" ���������� ����� ������: %f\n",modOfDiv);
	roundedVal=round(modOfDiv);
	printDebugMsg(0,0,0);
	printf(" ����������� ��������: %d\n", roundedVal);
	numberOfIterations=(samplesValue-modOfDiv)/sizeof(resultToWrite);
	printDebugMsg(0,0,0);
	printf(" ��������� ���������� ������ �������� %d ���� �� ������: %d\n",sizeof(resultToWrite),numberOfIterations);
	cursorPos2=HeaderSize;
	writeParameters[0]=cursorPos2;
	
	for(uint32_t i=0;i<numberOfIterations;i++)
	{	
		//printf("���� �%d\n",i);
		cursorPos2=prepareArray(cursorPos2);
		writeStat=writeChunk(writeParameters,sizeof(resultToWrite));
		if(writeStat==0)
		{
			//printf("���� �%d � %d ���� ������� �������\n",i,sizeof(resultToWrite));
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
	printf("��� �����: %s\n", wordConvert);
	cursorSymbol=strstr(fileBuffer, wordConvert);
	wordConvertPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("������ ����� ��: %d ����\n", wordConvertPos);
	cursorPos=wordConvertPos+wordConvertShift;
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &ConvertStat);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("���� �����������: %d\n", ConvertStat);
	printDebugMsg(0,0,0);
	printDebugMsg(16,0,0);
	printf("�������� ���� �����������...\n");
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
	printf("���� �����������: %d\n", ConvertStat);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("������ ����� ��: %d ����\n", wordChannelsPos);
	cursorPos=wordChannelsPos+wordChannelsShift;
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &channelsValue);
	printDebugMsg(0,0,0);
	printDebugMsg(16,0,0);
	printf("�������� ���������� �������...\n");
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
	printf("���������� �������: %d\n", channelsValue);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("������ ����� ��: %d ����\n", wordBitsPerSamplePos);
	cursorPos=wordBitsPerSamplePos+wordBitsPerSampleShift;
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &BitsPerSampleValue);
	printDebugMsg(0,0,0);
	printDebugMsg(16,0,0);
	printf("�������� �������� ������� �������...\n");
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
	printf("������� �������: %d ���\n", BitsPerSampleValue);
	fclose(FRd);
	
	fclose(FOut);
	fclose(FIn);
	fileClose();
	printDebugMsg(0,0,0);
	printDebugMsg(17,0,0);
	//printDebugMsg(0,0,0);				//������� �� �������������
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
	char *WordCountOfSamples="SamplesInChannel=";																								//������� ���� SamplesInChannel
	int smprt=192000;
	int chnls=2;
	int cnvrt=1;
	int bits=24;
	uint8_t crlfSign[2]={0x0D, 0x0A};
	printf("�������� ������� ������������� � ��: ");
	scanf("%d", &smprt);
	printf("�������� ���������� �������, �� ������ 4: ");
	scanf("%d", &chnls);
	printf("������� �����������, � �����: ");
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
	printf("��� �����: %s (��� FSRC)\n", wordSrcFilenameStart);
	cursorSymbol=strstr(fileBuffer, wordSrcFilenameStart);
	fsrcPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("������ ����� ��: %d ����\n", fsrcPos);
	fseek(FRd, fsrcPos+wordTagRange, SEEK_SET);
	fsrcPos=ftell(FRd);
	symbol=fgetc(FRd);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("�������� ������� ��������� ������ ����� �����... ");
	if(symbol==0x3E)
	{
		printf("��������� ������");
		fsrcPos++;
		checkFileIntegrity=1;
	}
	printf("(%d)\n",fsrcPos);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("��� �����: %s (��� FSND)\n", wordSrcFilenameEnd);
	cursorSymbol=strstr(fileBuffer, wordSrcFilenameEnd);
	fsendPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("������ ����� ��: %d ����\n", fsendPos);
	fseek(FRd, fsendPos-wordTagStepBack, SEEK_SET);
	fsendPos=ftell(FRd);
	symbol=fgetc(FRd);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("�������� ������� ��������� ����� ����� �����... ");
	if(symbol==0x3E)
	{
		printf("��������� ������");
		checkFileIntegrity=1;
	}
	printf("(%d)\n",fsendPos);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("��� �����: %s (��� FNAM)\n", wordFilenameStart);
	cursorSymbol=strstr(fileBuffer, wordFilenameStart);
	fnamPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("������ ����� ��: %d ����\n", fnamPos);
	fseek(FRd, fnamPos+wordTagRange, SEEK_SET);
	fnamPos=ftell(FRd);
	symbol=fgetc(FRd);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("�������� ������� ��������� ������ ����� �����... ");
	if(symbol==0x3E)
	{
		printf("��������� ������");
		fnamPos++;
		checkFileIntegrity=1;
	}
	printf("(%d)\n",fnamPos);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("��� �����: %s (��� FNND)\n", wordNamFilenameEnd);
	cursorSymbol=strstr(fileBuffer, wordNamFilenameEnd);
	fnendPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("������ ����� ��: %d ����\n", fnendPos);
	fseek(FRd, fnendPos-wordTagStepBack, SEEK_SET);
	fnendPos=ftell(FRd);
	symbol=fgetc(FRd);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("�������� ������� ��������� ����� ����� �����... ");
	if(symbol==0x3E)
	{
		printf("��������� ������");
		checkFileIntegrity=1;
	}
	printf("(%d)\n",fnendPos);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("��� �����: %s (��� FBOD)\n", wordFilenameBody);
	cursorSymbol=strstr(fileBuffer, wordFilenameBody);
	fbodPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("������ ����� ��: %d ����\n", fbodPos);
	fseek(FRd, fbodPos+wordTagRange, SEEK_SET);
	fbodPos=ftell(FRd);
	symbol=fgetc(FRd);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("�������� ������� ��������� ����� ����� �����... ");
	if(symbol==0x3E)
	{
		printf("��������� ������");
		checkFileIntegrity=1;
	}
	printf("(%d)\n",fbodPos);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("��� �����: %s (��� FBND)\n", wordBodyFilenameEnd);
	cursorSymbol=strstr(fileBuffer, wordBodyFilenameEnd);
	fbendPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("������ ����� ��: %d ����\n", fbendPos);
	fseek(FRd, fbendPos-wordTagStepBack, SEEK_SET);
	fbendPos=ftell(FRd);
	symbol=fgetc(FRd);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("�������� ������� ��������� ����� ����� �����... ");
	if(symbol==0x3E)
	{
		printf("��������� ������");
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
	cursorPos2=fbodPos+1;																														//�������
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
	printf("�������� ����� ��������� ����� %d...%d(%s)\n",fsrcPos,fsendPos,fileSrcBuffer);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("�������� ����� ������������� ����� %d...%d(%s)\n",fnamPos,fnendPos,fileNameBuffer);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("�������� ����� �����-���������� ���� %d...%d(%s)\n",fbodPos,fbendPos,fileBodyBuffer);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("��� �����: %s\n", wordConvert);
	cursorSymbol=strstr(fileBuffer, wordConvert);
	wordConvertPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("������ ����� ��: %d ����\n", wordConvertPos);
	cursorPos=wordConvertPos+wordConvertShift;
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &ConvertStat);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("���� �����������: %d", ConvertStat);
	if(ConvertStat==0)
	{
		printf(", ���������� �����������\n");
	}
	else
	{
		printf(", ����������� ��� ���� ���������. ���������� ������� ��������� � ����\n");
	}
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("��� �����: %s\n", wordSampleRate);
	cursorSymbol=strstr(fileBuffer, wordSampleRate);
	wordSampleRatePos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("������ ����� ��: %d ����\n", wordSampleRatePos);
	cursorPos=wordSampleRatePos+wordSampleRateShift;
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &SampleRateValue);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("������� �������������: %d ��\n", SampleRateValue);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("��� �����: %s\n", wordChannels);
	cursorSymbol=strstr(fileBuffer, wordChannels);
	wordChannelsPos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("������ ����� ��: %d ����\n", wordChannelsPos);
	cursorPos=wordChannelsPos+wordChannelsShift;
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &channelsValue);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("���������� �������: %d, ", channelsValue);
	switch(channelsValue)
	{
		case 1:
			printf("����\n");
			break;
		case 2:
			printf("������\n");
			break;
		case 4:
			printf("������\n");
			break;
	}
	
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);	
	printf("��� �����: %s\n", wordBitsPerSample);
	cursorSymbol=strstr(fileBuffer, wordBitsPerSample);
	wordBitsPerSamplePos=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("������ ����� ��: %d ����\n", wordBitsPerSamplePos);
	cursorPos=wordBitsPerSamplePos+wordBitsPerSampleShift;
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &BitsPerSampleValue);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("������� �������: %d ���\n", BitsPerSampleValue);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);	
	printf("��� �����: %s\n", WordCountOfSamples);
	cursorSymbol=strstr(fileBuffer, WordCountOfSamples);
	wordSamplesValue=cursorSymbol-fileBuffer;
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("������ ����� ��: %d ����\n", wordSamplesValue);
	cursorPos=wordSamplesValue+wordSamplesValueShift;
	fseek(FRd, cursorPos, SEEK_SET);
	fscanf(FRd, "%d", &samplesValue);
	printDebugMsg(0,0,0);
	printDebugMsg(1,0,0);
	printf("��������� ���������� ������� � ����� ������: %d\n", samplesValue);
	return checkFileIntegrity;
}
uint8_t bitShorter(uint8_t inputFormat, uint32_t inputWord)
{
	switch(inputFormat)
	{
		case 0:
			printf("������ ������� ������ �� ������!");
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
	//printf("������ ������ ������� ���������� 16 ��������� �������...\n");
	uint16_t tempVal;
	uint8_t tempVal8;
	uint8_t oneByte[2];
	memset(oneByte, 0x00, sizeof(oneByte));
	//printf("������� ������� � �����: %d\n",posCursor);
	//fseek(FIn, posCursor, SEEK_SET);
	//fread(oneByte, 2, sizeof(oneByte), FIn);
	oneByte[0]=fileMassive[posCursor];
	oneByte[1]=fileMassive[posCursor+1];
	tempVal8=oneByte[0];
	//printf("������� ����: 0x%02X\n", tempVal8);
	tempVal8=oneByte[1];
	//printf("������� ����: 0x%02X\n", tempVal8);
	tempVal=oneByte[0];
	tempVal=tempVal|oneByte[1]<<8;
	//printf("���������� 16 ������ �����: 0x%04X\n",tempVal);
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
	//printf("������ ������ ������� �������...\n");
	scrapValue = firstChannel+secondChannel;
	//printf("������������� ����������(16 ���): 0x%04X\n",scrapValue);
	valueToReturn = scrapValue/2;
	//printf("���������� �� ������: 0x%02X\n",valueToReturn);
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
	//printf("��������� �� ������� � ������ FOut: %d\n",fOutWriteCursor);
	for(int i=0;i<sizeof(fileBuffer);i=i+4)
	{
		TwoByteSample=TwoBytesSampleReader(i);
		firstChannel=bitShorter(byteShortCode,TwoByteSample);
		firstChannel=firstChannel-128;
		//printf("bitShorter ������ ��������(1 �����): 0x%02X\n", firstChannel);
		TwoByteSample=TwoBytesSampleReader(i+2);
		secondChannel=bitShorter(byteShortCode,TwoByteSample);
		secondChannel=secondChannel-128;
		//printf("bitShorter ������ ��������(2 �����): 0x%02X\n", secondChannel);
		returnedValue=stereoToMonoMixer(firstChannel,secondChannel);
		//printf("������� ���� �������: 0x%02X\n", returnedValue);
		resultToWrite[indexOne]=returnedValue;
		indexOne++;
		//printf("������ �������: %d\n", indexOne);
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
			printf("[�������]");
			break;
		case 1:
			printf("[�������� ����������] ");
			break;
		case 2:
			printf("�� ������ ");
			break;
		case 3:
			printf("��� FSRC\n");
			break;
		case 4:
			printf("��� FNAM\n");
			break;
		case 5:
			printf("��� FSND\n");
			break;
		case 6:
			printf("��� FNND\n");
			break;
		case 7:
			printf("�����...");
			exit(1);
			break;
		case 8:
			printf("��������� ������ ");
			break;
		case 9:
			printf("��������� ����� ");
			break;
		case 10:
			printf("��������� ");
			break;
		case 11:
			printf("���������������� ");
			break;
		case 12:
			printf("����� �����\n");
			break;
		case 13:
			printf("[������]");
			break;
		case 14:
			printf("[������]");
			break;
		case 15:
			printf(" ������ ���������. ������� Enter ��� ������ �� ���������...");
			break;
		case 16:
			printf("[������ ����������] ");
			break;
		case 17:
			printf(" ������ ���������. ������ ���������� �������� ��������� Exheader ��� ������������\n	  ����� ��������� �� ���������� ����� ����������� ����������\n");
			break;
	}
}
