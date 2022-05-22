//Exheader - ��������� ������������� ��� ���������� ��������� �� WAV ����� ��� ���������� ������ � ��� - ������������ � ������� � ����� ����
//������ ��������� ������ ���� ��������� RIFFeeeeWAVEfmt kkkkgghhrrrryyyyooqqppppzzzz
// RIFF - ����� ������� �����, DWORD 4 �����
// eeee - ������ ����� ����� � ������ DWORD 4 �����
// WAVE - ����������� ��� ���� �������� DWORD 4 �����
// fmt  - ����������� ��� ������ ����� ������ � ����� DWORD 4 �����, ��������� ������ �������������� - 0x20 WORD 2 �����
// kkkk - ��� ������� ���(PCM) DWORD 4 �����
// gg - ����� ������ �����, ������ ���(PCM) WORD 2 �����
// hh - ����� ������� ���������� ������ WORD 2 �����
// rrrr - ������� ������������� � ������ DWORD 4 �����
// yyyy - �������� �������� ������ � ������ � ������� DWORD 4 �����
// oo - ���������� ���� ��� ����� ������� ������� ��� ������ WORD 2 �����
// qq - ������� ������� � ����� WORD 2 �����
// data - ����� ������������ ��� ������ ����� ������ DWORD 4 �����
// zzzz - ������ ����� ����� ������ ��������� DWORD 4 �����
//����� ���������� ��������� ��������� ���������� ���� convertParams.ini � ������� ����������
// ���������� ������ FSRC-FSND �������� ��� �����
// ���������� ������ FBOD-FBND ��� ���������� wav ������
// ���������� ������ FHDT-FHND ��� ����� � ����������, ���������� ���� ����������
// ���������� ������ FTGT-FTND ��� ��������� �����
// ���� ��������� ����������� - 0(�� �������������), 1(�������������)
// ������� ������������� ����� � ������
// ���������� ������� � �����
// ������� �������
// ���������� ������� � ����� ������
//������ ������ ��������� ��������� ������� ����� convertParams.ini � ����
//�� ������� �� ������� �����. ����� ���� ����, ��� ��������� ��� � � ������
//������ ��������� ���� �����������. ���� 0 - ��������� ��������� ������
//���� 1 �� ��������� ������ ��������� ������, ������� ��� ����� ���������
//� ������� ���� �������� ����������� ����� ����� ���� FHDT. ����� ���������
//�� ����������� ������ ��������� ����������� ��������� � ���������� ��� � ����
#include<locale.h>																																//���������� ����������, ����� ��� �������� ����� � �������
#include<stdbool.h>																																//���������� ��� ������ � ��������� ������, C99
#include<stdint.h>																																//���������� ��� ������ � �������������� ������� uint8_t, uint16_t, uint32_t
#include<stdio.h>																																//���������� ��� ������ � ��������, ����� � ������� � ���������� � ���
#include<conio.h>																																//���������� ��� ������ � ������
#include<stdlib.h>																																//���������� ����� ����������
#include<string.h>																																//���������� ���������� ����������
#include "debug.h"																																//���������� ���������� ���������
#define StartMsg					"\nv0.2.7\n"																								//��������� ��� ������ � �������, 1 �����
#define StartMsgTwo					"������ ��������� �������� ����������� � ���� �� ���� �� ����� ������\n\n"									//��������� ��� ������ � �������, 2 �����
#define FileSizeMsg					"������ �����, ������: %d ����\n"																			//��������� ��� ������ ������� �����
#define FileSizeWoutHeaderMsg		"������ ����� ��� ����� ���������: %d ����\n"																//��������� ��� ������ ������� ����� ��� ���������
#define SampleRateMsg				"������� �������������: %d ��\n"																			//��������� ��� ������ ������� �������������
#define ByteRateMsg					"�������� �������� ������: %d ����/�\n"																		//��������� ��� ������ �������� �������� ������ � ������
#define BitDepthMsg					"������� �������: %d ���\n"																					//��������� ��� ������ ������� �������
#define ChannelsMsg					"���������� �������: %d"																					//��������� ��� ������ ���������� �������
#define BytesInSampleMsg			"���������� ���� � ����� ������� �� ���� �������: %d ����\n"												//��������� ��� ������ ���������� ���� � ������� �� ���� ������� �����
#define CodecTypeMsg				"��� ����������� �����:"																					//��������� ��� ������ ���� ����������� ����� � �����
const uint8_t wordFilenameShift=4;																												//�������� � ������ �� ������ ���������
const uint8_t wordConvertShift=7;																												//�������� � ������ �� ������ ���������
const uint8_t wordSampleRateShift=10;																											//�������� � ������ �� ������ ���������
const uint8_t wordChannelsShift=8;																												//�������� � ������ �� ������ ���������
const uint8_t wordBitsPerSampleShift=13;																										//�������� � ������ �� ������ ���������
const uint8_t wordSamplesValueShift=16;																											//�������� � ������ �� ������ ���������
const uint16_t pcmFormat=0x0001;
const uint32_t RIFFsignature=0x52494646;																										//����� RIFF, �������
const uint32_t WAVEsignature=0x57415645;																										//����� WAVE, �������
const uint32_t fmtSignature=0x666D7420;																											//����� fmt , �������
const uint32_t dataSignature=0x64617461;																										//����� data, �������
const uint32_t dataFormatLength=0x00000010;
char headerNameSuffix[11]="_header.dat";																										//������� � ����� �������������� �����
char headerBodySuffix[9]="_body.dat";																											//������� � ����� �������������� �����
char headerConvSuffix[9]="_conv.wav";																											//������� � ����� �������������� �����
char fileMassive[256];																															//������ � ������� �������� ���������� ����� convertParams.ini
char fileNameRAW[128];																															//������, � ������� �������� ��� ����� ������� ����
char fileNameSrc[64];																															//������ � ������ ��������� �����
char fileNameHdrDat[64];																														//������ � ������ ������������� �����
char fileNameBodDat[64];																														//������ � ������ ������������� �����
char fileNameTgtDat[64];																														//������ � ������ ������������� �����
char fileName[64];																																//������ � ������ �����
char *wordFilenameSource="FSRC";																												//�������� ��� ��������� ����� �����
char *wordFilenameBody="FBOD";		   																											//�������� ��� ��������� ����� �����
char *wordFilename="FNAM";																														//�������� ��� ��������� ����� �����
char *wordFilenameTarget="FTGT";																												//�������� ��� ��������� ����� �����
char *wordSrcFilenameEnd=">FSND";																												//�������� ��� ��������� ����� �����
char *wordNameFilenameEnd=">FNND";																												//�������� ��� ��������� ����� �����
char *wordBodyFilenameEnd=">FBND";																												//�������� ��� ��������� ����� �����
char *wordTargFilenameEnd=">FTND";																												//�������� ��� ��������� ����� �����
char *wordConvert="Convert";																													//�������� ��� ����� ��������� �����������
char *wordSampleRate="SampleRate";																												//�������� ��� ��������� ������� �������������
char *wordChannels="Channels";																													//�������� ��� ��������� ���������� �������
char *wordBitsPerSample="BitsPerSample";																										//�������� ��� ��������� ������������� ���������� ��� � �������
char *WordCountOfSamples="SamplesInChannel";																									//�������� ��� ��������� ������������� ���������� �������
char *cursorSymbol;																																//�������� � ������� ����� �������� ������� ������� � �������� ���������� ������� �����
uint8_t fileLength;																																//����� ���������� ��� �������� ���������� � ����� �����
uint32_t cursorPosit;																															//������� ������� �� ������ ����� ���������
uint32_t wordFsrcPos;																															//������� ���� FSRC
uint32_t wordFnamePos;																															//������� ���� FNAM
uint32_t wordConvertPos;																														//���� ������� �������, �� ������� ����� ��������� ������ ��� ������ ��������� FSetWasConverted 
uint32_t wordSampleRatePos;																														//���� ������� �������, �� ������� ����� ��������� ������ ��� ������ ��������� FSetSampleRate
uint32_t wordChannelsPos;																														//���� ������� �������, �� ������� ����� ��������� ������ ��� ������ ��������� FSetChannels
uint32_t wordBitsPerSamplePos;																													//���� ������� �������, �� ������� ����� ��������� ������ ��� ������ ��������� FSetBitDepth
uint32_t wordSamplesValuePos;																													//���� ����� �������� ���������� ������� � 1 ������ �����
bool DebugMode=1;																																//����� �������, 1 - ���, 0 - ����
bool analyzeState;																																//��������� ������� ������, 1 - ��� ������, 0 - ���-�� ��������� ������
bool convertState;																																//��������� ������� �������������� � ������ � ���������, 1 - ��� ������, 0 - ���-�� ��������� ������
bool cruzo;																																		//��������� ����������� � ����� convertParams.ini
bool ahsoka;																																	//��������� ������� �������� ������������ ������ � ���������, 1 - ��� ������, 0 - ������ � ��������� �� ��������� � ���������, ����������� �������� �� �����
bool gabella;																																	//���� 1 - ���������� � ��������� ������� ��������, ���� 0 - ��������� ���-�� ����� ��� �� ���� ��������
bool Egor;																																		//��������� ������� ������ �� ����� convertParams.ini
bool doubledoor;																																//��������� ��������� ������ � ����, ���� 1 �� ��� ������, ���� 0 �� ���� �� ��� �������
FILE* FSet;																																		//��������� �� ���� � ����������� ���������
FILE* FRd;																																		//��������� �� ���� � �������� ��� ����� ��������
FILE* FWr;																																		//��������� �� ���� � ������� ����� ���� ������, ���� � ���� �� ��������
const int HeaderSize=44;																														//�������� ����� ��������� � ������(�� 0 ����� �� ������ ����� ������ WAVE), ��������� ����� ������ ���� � �� �� �����
int headerAddrs[14]={0,4,8,12,16,20,22,24,28,32,34,36,40,44};																					//������ ������� � ��������� � ������� ����� ������ ��������� �����
int headerWordSizeOf[13]={sizeof(uint32_t),sizeof(uint32_t),sizeof(uint32_t),sizeof(uint32_t),													//������ ����� ����, �������� �� ���������(������ ������ � headerAddrs � headerWordInvert)
						sizeof(uint32_t),sizeof(uint16_t),sizeof(uint16_t),sizeof(uint32_t),													//����� � ������ ����
						sizeof(uint32_t),sizeof(uint16_t),sizeof(uint16_t),sizeof(uint32_t),
						sizeof(uint32_t)};																										//������ ������� �������� ����� ������� ��������� � �����
int headerWordInvert[13]={1,0,1,1,0,0,0,0,0,0,0,1,0};																							//������ ��� �������, ���������� ������� ������ - � ����� ��� � ������
int headerDebugPrintParameters[13]={0,0,0,0,0,1,1,0,0,1,1,0};																					//������ ����� ��������� ������ ��� ������� ������ ���������� ����������
uint8_t FileHeader[44];																															//���� �������������� ���������
uint8_t ByteBuffer[4];																															//����� �������� �������� ��������� ����� ������ ��� �� ���������� � ��������� �������
uint8_t headerReader(void);																														//������� ������ ��������� � ���������
uint8_t massiveSwap(bool swapState);																											//������� ��������� ������� ���������� ������
uint8_t sByteConverter(uint32_t wordToConvert);																									//������� ��������� �����������
uint8_t GetFileName(char* nameOfFile);																											//������� ��������� ����� �����(�� ����� ���� ��� ������ �� ��������)
uint16_t dByteConverter(uint32_t wordToConvert);																								//������� ��������� �����������(� 32 �� 16 ���)
uint32_t qByteConverter(uint32_t wordToConvert);																								//������� ��������� �����������(� 32 �� 8 ���)
uint32_t byteConverter(int startOffset, int endOffset, int ByteLenght, bool invertState);														//������� ��� �������������� ������ ����� �����������  ������� � ���� ����� � ������ �������
uint32_t structFiller(int structShift, uint32_t paramToWrite);																					//������� ������ � ���������
uint32_t writeBuffer(int startOffset, int endOffset, uint32_t paramToWrite, int wordSize, bool SwapByte);										//������� ������ ���������� ��������� � ������, ���������� � ������ � ����
void transformFileName(char *sourceFileName, uint8_t sourceLenght, char *suffixToAttach, uint8_t suffixLength, char *arrToStore);				//������� ��������� ����� ����� �� ����������� ���������
void storeStructToFile();																														//������� ��� ������ ���������� ��������� � ��������� ���� � ���� ���������
void checkStatus(uint8_t statusCode);																											//������� ��� �������� ��������� ������ �� ������ �������, ��� ����������� ������
void structAnalyzer(void);																														//������� ��� �������� ��������� � ������ �� �����������
void structModifier(void);																														//������� ��� ����������� ���������
void clearByteBuffer(void);																														//������� ������ ����� ������
void clearHeaderBuffer(void);																													//������� ������ ��������� ����� �������� ������ �����
void writeDebugHeaderBuffer(void);																												//������ ����� ���������� �������� ��������� � ���������� �����
void BufferReader(void);																														//�������-������� ��� ���������� �����
void printHelpMsg(void);																														//�������-������� � ������ ������� ������ ��� ������ �� �������� -h.-H,-help,-HELP
void generateHead(void);
int WriteSettingsFile(void);																													//������� ������������ ��������� ��������������
int ReadSettingsFile(void);																														//������� ����������� ��������� ��������������
struct WaveHeader																																//���������, � ������� ����� �������� ���������� � ��������� �����
{																																				//������ ��������� ���������
	uint32_t RiffSign;																															//����� RIFF
	uint32_t chunkSizeBytes;																													//������ ����� � ����������
	uint32_t WaveSign;																															//����� WAVE
	uint32_t fmtSign;																															//����� fmt
	uint32_t DataFormatLenght;																													//����� ������� ������
	uint16_t compressionCode;																													//��� ������
	uint16_t soundChannels;																														//���������� �������
	uint32_t sampleRate;																														//������� �������
	uint32_t byteRate;																															//�������� �������� ������, ����
	uint16_t BytesInSample;																														//���������� ���� � ����� ������� �� ���� �������
	uint16_t BitDepth;																															//������� �������������
	uint32_t dataSign;																															//����� data
	uint32_t chunkSizeWoutHeader;																												//������ ����� ��� ���������
};																																				//����� ��������� ���������
struct FilSettings																																//���������, � ������� ������� ��������� �� ����� convertParams.ini
{																																				//������ ���������
	int FSetWasConverted;																														//���� ������� ���������� - ��� �� ������������� ���� ���� ������� ����� - ������ ��������� ��� ���
	int FSetBitDepth;																															//������� �������������
	int FSetChannels;																															//���������� �������
	long FSetSampleRate;																														//������� �������
	uint32_t FSetSamplesValue;																													//���������� �������
};																																				//����� ���������
struct FilSettings FilSet;																														//��������� ����� ���������
struct WaveHeader Wave;																															//��������� ����� ���������
int main(int argc, char* argv[])																												//�������� main � ������ �������� ���������� �� ��������� ������
{																																				//������ ���� main
	memset(fileMassive,0x00,sizeof(fileMassive));																								//������ ������ fileMassive
	memset(fileNameRAW,0x00,sizeof(fileNameRAW));																								//������ ������ fileNameRAWs
	memset(fileNameSrc,0x00,sizeof(fileNameSrc));																								//������ ������ fileNameSrc
	memset(fileName,0x00,sizeof(fileName));																										//������ ������ fileName
	memset(FileHeader,0x00,sizeof(FileHeader));																									//������ ������ FileHeader
	memset(ByteBuffer,0x00,sizeof(ByteBuffer));																									//������ ������ ByteBuffer
	setlocale(LC_ALL, "Rus");																													//������� ����
	if(DebugMode==1)																															//��������, ������� �� ����� �������
	{pringDebugMsg(36,0);}																														//���� ������� �� ����� ���������
	pringDebugMsg(33,0);																														//����������� � ������ ������ �����
	pringDebugMsg(85,argc);																														//��������� � ���������� ����������, ���������� �� ��������� ������
	for(uint8_t i=0;i<64;i++)
	{
		if(!(strcmp(argv[i], "-makehead")))
		{
			pringDebugMsg(101,0);
			printf(" �������� -makehead ������\n");
			ReadSettingsFile();
			cursorSymbol=strstr(fileMassive, wordConvert);
			structModifier();
			generateHead();
			exit(0);
		}
	}
	if(argc<2)																																	//������ �������� ���������� ����������...
	{																																			//...���� ���������� ������ ����
		printf("�� ������� ��� �����\n");																										//������� ��������� � ��� ��� �� ������� ���������
		printf("����� ������� -h, -H, -help, -HELP\n\n");																						//� ���������� ������� �������
		pringDebugMsg(84,0);																													//���������� ����� �� ��������� � ����� 1(���� �� ������)
	}																																			//����� �� ���� �������� ��������
	if(argc>4)																																	//��������� ���������� ���������� - �� ������ ���� 2...4
	{																																			//���� ���������� ������ 2, ��
		printf("������� ����� ����������\n");																									//�������� �� ����
		pringDebugMsg(84,0);																													//� ������� �� ���������
	}																																			//����� �� ���� ��������
	printf(StartMsg);																															//����� ��������� �����������
	printf(StartMsgTwo);																														//����� ���������, ������ �����
	if(!(strcmp(argv[1], "-h")&&strcmp(argv[1], "-H")&&strcmp(argv[1], "-HELP")&&strcmp(argv[1], "-help")))										//��������� ������� ������� �������
	{																																			//������ ����
		printHelpMsg();																															//�������� ������� ������ �������
	}																																			//����� ����
	printf("������ �������� ����������, ��������� ���� � ������ �� ���������\n\n");																//�������
	FRd=fopen(argv[1], "rb");																													//�������� ����� ���������� � ������ ���������
	fileLength=GetFileName(argv[1]);																											//�������� ��� �����
	transformFileName(fileName,fileLength,headerNameSuffix,sizeof(headerNameSuffix),fileNameHdrDat);											//���������� ��� ����� � ���������� �� ���������
	transformFileName(fileName,fileLength,headerBodySuffix,sizeof(headerBodySuffix),fileNameBodDat);											//���������� ��� ����� � ����� �� ���������
	transformFileName(fileName,fileLength,headerConvSuffix,sizeof(headerConvSuffix),fileNameTgtDat);											//���������� ��� ����� � ����� �� ���������
	if(!FRd)																																	//�������� ������������� ����� ��(FRd)=0?
	{																																			//�����...
		pringDebugMsg(89,0);																													//�������
		pringDebugMsg(91,0);																													//��������� �� ����������� �����
		exit(1);																																//����� �� ��������� � ����� 1(���� �� ������)
	}																																			//����� ���� ��������
	fseek(FRd, 0, SEEK_SET);																													//��������� ������� �� �����(���������� ������ �������� ���� �� ����������� �����)
	pringDebugMsg(26,0);																														//�������� ���������� ��������� � ������ ������ ���������
	fread(FileHeader, 1, HeaderSize, FRd);																										//��������� ������ � ������ FileHeader, ������ ������ 44 �����(������� � HeaderSize)
	writeDebugHeaderBuffer();																													//������ ��� ������ �������, ������ � ��������� ����� �� �������� ����� ���������� �� ����� �������
	pringDebugMsg(25,0);																														//����� ����������� ������ FileHeader
	pringDebugMsg(29,0);																														//����� ��������� � ���, ��� ������ ������ ����������� ����� ������
	headerReader();																																//����� ������� ������ ���������
	fclose(FRd);																																//�������� ����� ��� ������
	checkStatus(1);																																//�������� ���� ������ ������� ������ ���������
	structAnalyzer();																															//����� ������� �������� ��������� �� ������������
	ReadSettingsFile();																															//����� ������� ������ �� ����� ����������
	WriteSettingsFile();																														//����� ������� ������ ���������� � ����
	pringDebugMsg(82,0);																														//����� ��������� ���������� ������ ���������
	//pringDebugMsg(38,0);					//������� ��� �������������																			//��������� �������� �� ��� ��� ��� ����� ����� ������� ������� Enter
	//getchar();																																//������ �� ������, ����� ������� ������� Enter
}																																				//����� ���� main
void generateHead(void)
{
	pringDebugMsg(101,0);
	printf(" ��������� ���������...\n");
	memset(FileHeader,0x00,sizeof(FileHeader));
	writeBuffer(headerAddrs[0], headerAddrs[1], RIFFsignature, headerWordSizeOf[0], headerWordInvert[0]);
	writeBuffer(headerAddrs[1], headerAddrs[2], Wave.chunkSizeBytes, headerWordSizeOf[1], headerWordInvert[1]);
	writeBuffer(headerAddrs[2], headerAddrs[3], WAVEsignature, headerWordSizeOf[2], headerWordInvert[2]);
	writeBuffer(headerAddrs[3], headerAddrs[4], fmtSignature, headerWordSizeOf[3], headerWordInvert[3]);
	writeBuffer(headerAddrs[4], headerAddrs[5], dataFormatLength, headerWordSizeOf[4], headerWordInvert[4]);
	writeBuffer(headerAddrs[5], headerAddrs[6], pcmFormat, headerWordSizeOf[5], headerWordInvert[5]);
	writeBuffer(headerAddrs[6], headerAddrs[7], Wave.soundChannels, headerWordSizeOf[6], headerWordInvert[6]);
	writeBuffer(headerAddrs[7], headerAddrs[8], Wave.sampleRate, headerWordSizeOf[7], headerWordInvert[7]);
	writeBuffer(headerAddrs[8], headerAddrs[9], Wave.byteRate, headerWordSizeOf[8], headerWordInvert[8]);
	writeBuffer(headerAddrs[9], headerAddrs[10], Wave.BytesInSample, headerWordSizeOf[9], headerWordInvert[9]);
	writeBuffer(headerAddrs[10], headerAddrs[11], Wave.BitDepth, headerWordSizeOf[10], headerWordInvert[10]);
	writeBuffer(headerAddrs[11], headerAddrs[12], dataSignature, headerWordSizeOf[11], headerWordInvert[11]);
	writeBuffer(headerAddrs[12], headerAddrs[13], Wave.chunkSizeWoutHeader, headerWordSizeOf[12], headerWordInvert[12]);
	BufferReader();
	pringDebugMsg(81,0);
	FWr=fopen(fileNameHdrDat, "wb");
	if(FWr != NULL)
	{
		printf(" �����\n");
	}
	else
	{
		printf(" �� ������� ������� ���� %s\n",fileNameHdrDat);
		exit(0);
	}
	fseek(FWr, 0, SEEK_SET);
	fwrite(FileHeader, sizeof(uint8_t), sizeof(FileHeader), FWr);
	fclose(FWr);
}
inline void printHelpMsg(void)																													//������� ������ ���������� ���������� � �������
{																																				//������ ����
	printf(StartMsg);																															//������� ������ ���������
	printf("�������������: Exheader.exe source_file output_file(���������)\n\n");																//�������, ������
	printf("- ��� ���������� ������� ���������, ���� � ���������� ��������� �\n  ���������� ������� Exheader.exe\n");							//�������, �����������
	printf("- ��������, ����� Exheader.exe C:\\foreign8.wav ������� �� �����\n  ������ ������������ ���� foreign8_header.dat\n");				//�������, �����������
	printf("  � ����� Exheader C:\\foreign8.wav C:\\aaa\\foreign8dat.wav ������� �� ���� C:\\aaa ���� foreign8dat.wav.dat\n\n");				//�������, �����������
	printf("- �������� ���� ������ ����� � ����������� .dat � ��������� � ����\n  �������������� �� convertParams.ini ���������\n");			//�������, �����������
	exit(1);																																	//����� � ����� 1
}																																				//����� ���� ���������� �������
inline void writeDebugHeaderBuffer(void)																										//�-���� ����������� ��������� � ��������� ����� ��� ������ ���������� ���������
{																																				//������ ���� �-����
	for(int j=0;j<43;j++)																														//������ ����� ����������� ��������
	{																																			//������ ���� �����
		FileHeaderMSG[j]=FileHeader[j];																											//������������ ����������� � ����������� ������ ������� ������������ ������ ��������
	}																																			//����� ���� �����
}																																				//����� ���� �������
uint8_t GetFileName(char* nameOfFile) 																											//������� ��������� ����� ����� �� ����
{																																				//������ ����
	uint8_t symbolCountInFileName;																												//���������� �������� ����� ����� �����, ������� ����������
	strcpy(fileNameRAW,nameOfFile);																												//������������ ������ � ������
	uint8_t nameLenght = strlen(nameOfFile);																									//������� ���������� �������� ��������
	char *lastSymbolEntry = strrchr(fileNameRAW, 92);																							//���������� ���������� ��������� ������� "\"
	uint8_t entryPos = lastSymbolEntry-fileNameRAW+1;																							//��������� �� ������ ���������� ��������� �������
	if(lastSymbolEntry==NULL)																													//���� ������� strrchr ���������� NULL...
	{																																			//...�� �������� ��������� ����� ��� ��������� ������ ���� � �����
		pringDebugMsg(89,0);																													//����� � �������
		pringDebugMsg(92,0);																													//����� ��������� � �������� NULL �������� strrchr
		pringDebugMsg(89,0);																													//����� � �������
		printf("����� ����� ����� = %d\n", nameLenght);																							//����� ��������� � ����� ����� ����� ������� ���� �� ����
		pringDebugMsg(89,0);																													//����� � �������
		printf("��� ������������ �����: ");																										//����� ��� ������������ �����
		for(int i=0;i<nameLenght;i++)																											//������ ����� ������ ����� �����
		{																																		//������ ���� �����
			printf("%c",fileNameRAW[i]);																										//������������ ����� ����� ����� �� �������
		}																																		//����� ���� �����
		printf("\n");																															//������� ������� �������
		pringDebugMsg(89,0);																													//����� � �������
		pringDebugMsg(93, entryPos);																											//������� ������� ���������� ���������� ������� �������
		pringDebugMsg(89,0);																													//����� � �������
		printf("��������� ��������� �������: %s\n", lastSymbolEntry);																			//����� ��������� ��������� �������
		symbolCountInFileName = strlen(fileNameRAW);																							//������������ ����� ����� �����, � ��������
		pringDebugMsg(89,0);																													//����� � �������
		pringDebugMsg(94,symbolCountInFileName);																								//����� ���������� � ���������� �������� �����
		pringDebugMsg(89,0);																													//����� � �������
		printf("���������� ��� �����: ");																										//������� ���������� ��� �����
		for(int i=0;i<symbolCountInFileName;i++)																								//������ ����� ������ �����
		{																																		//������ ���� �����
			fileNameSrc[i]=fileNameRAW[i];																										//������������ ������������� ����� ����� � ������
			fileName[i]=fileNameRAW[i];																											//��������� ��� � ������ ������ �����������
			printf("%c",fileName[i]);																											//� ������ ����������� ������� ����������� ��� � �������
		}																																		//����� ���� �����
		printf("\n");																															//��������� �������
		return symbolCountInFileName;																											//���������� ����� ����� �����
	}																																			//����� ����(������)
	else																																		//����� �������� ���� �� ����� �� ����� �����
	{																																			//������ ����
		pringDebugMsg(89,0);																													//����� � �������
		printf("����� �����, ������� ���� � ����� = %d\n", nameLenght);																			//����� ����� ����� �����
		pringDebugMsg(89,0);																													//����� � �������
		printf("��� ������������ �����: ");																										//����� ��� ������������ �����
		for(int i=0;i<nameLenght;i++)																											//������ ����� ������ ����� �����
		{																																		//������ ���� �����
			printf("%c",fileNameRAW[i]);																										//������������ ����� ����� �����
		}																																		//����� ���� �����
		printf("\n");																															//������� �������
		pringDebugMsg(89,0);																													//����� � �������
		pringDebugMsg(93, entryPos);																											//����� ������� �������, ������� ���� � ������
		pringDebugMsg(89,0);																													//����� � �������
		printf("��������� ��������� �������: %s\n", lastSymbolEntry);																			//������ � ��� ������� ��� ��� ������ �������
		symbolCountInFileName = nameLenght-entryPos;																							//������� ���������� �������� � ����� �����
		pringDebugMsg(89,0);																													//����� � �������
		pringDebugMsg(94,symbolCountInFileName);																								//����� ��������� � ���������� ���������� �����
		pringDebugMsg(89,0);																													//����� � �������
		printf("���������� ��� �����: ");																										//����� ���������� ��� �����(��� ���� ���)
		for(int i=0;i<symbolCountInFileName;i++)																								//�������� ����� ����� �����
		{																																		//������ ���� �����
			fileNameSrc[i]=fileNameRAW[i+entryPos];																								//������������ ������������� ����� ����� � ������
			fileName[i]=fileNameRAW[i+entryPos];																								//����������� ������� ��� ����� �� ��������� � ������ �����
			printf("%c",fileName[i]);																											//� ����� �� ��������, ����� �� �������
		}																																		//����� ����
		printf("\n");																															//������� �������
		return symbolCountInFileName;																											//���������� ����� ����� ����� � ����� ������ �������
	}																																			//����� ����(����)
}																																				//����� ���� �������
void transformFileName(char *sourceFileName, uint8_t sourceLenght, char *suffixToAttach, uint8_t suffixLength, char *arrToStore)				//������� ������������� ����� �����
{																																				//������ ���� �������
	char tempMas[64];																															//�������������� ��������� �����
	memset(tempMas,0x00,sizeof(tempMas));																										//� ������ ���
	uint8_t filenameWithoutExtension=sourceLenght-4;																							//������������� ���������� ����� ����� ����� ��� ����������
	uint8_t generatedFileNameWithSuffix;																										//������������� ���������� ����� ���������������� ����� �����
	pringDebugMsg(95,0);																														//����� � �������
	pringDebugMsg(96,0);																														//����� ���������� � ������ ������ �������
	for(int i=0;i<filenameWithoutExtension+suffixLength;i++)																					//������ ����� ��������� ����� �����
	{																																			//������ ���� �����
		if(i<filenameWithoutExtension)																											//������ �������� ����� �����
		{																																		//������ ����
			tempMas[i]=sourceFileName[i];																										//������������ ������� ����� �����
		}																																		//����� ����
		if(i>=filenameWithoutExtension)																											//������ ������ �������� � ����� �����
		{																																		//������ ����
			tempMas[i]=suffixToAttach[i-filenameWithoutExtension];																				//������������ ������ �������� � ����� �����
		}																																		//����� ����
	}																																			//����� ���� �����
	generatedFileNameWithSuffix = filenameWithoutExtension+suffixLength;																		//������������ ����� ����� ����� ������ � ���������
	if(strlen(tempMas)==generatedFileNameWithSuffix)																							//���������� ���������� ��� � ��������� ����� �����
	{																																			//������ ���� �����
		pringDebugMsg(95,0);																													//����� � �������
		pringDebugMsg(98,0);																													//����� ��������
	}																																			//����� ���� �����
	else																																		//� ������ ���� ����� �� ���������
	{																																			//�� ����� � ������� ��������� �� ������
		pringDebugMsg(15,0);																													//� ������� �� ���������
	}																																			//����� ���� �����
	pringDebugMsg(95,0);																														//����� � �������
	printf("���������� ��� �����: ");																											//����� ��������������� ��� �����
	for(int i=0;i<generatedFileNameWithSuffix;i++)																								//������ ����� �������� ����� ����� �� ���������� �������
	{																																			//������ ���� �����
		fileName[i]=tempMas[i];																													//������������ ������� ����� �����
		arrToStore[i]=tempMas[i];																												//��������� � ������ �� ��������� ��� ������ �� ���������� ��������� � ���� ������ ��������� �.� ����� ���-�� �������� ��������� ���
		printf("%c",arrToStore[i]);																												//� ����� �� ����� � �������
	}																																			//����� ���� �����
	printf("\n");																																//������� �������
	pringDebugMsg(95,0);																														//����� � �������
	pringDebugMsg(94,generatedFileNameWithSuffix);																								//����� ����� ���������������� �����
	pringDebugMsg(95,0);																														//����� � �������
	pringDebugMsg(97,0);																														//���������� ��� ��� ����� ��������� � ���������� �������
}																																				//����� ���� �������
uint8_t headerReader(void)																														//���������� ������� 
{																																				//������ ���� �-����
	uint32_t LongByteWord;																														//��������� ��������� 4 ������� ����������
	int hA=0,hB=0,hC=0,hD=0;																													//�������
	struct WaveHeader Wave;																														//���������� �������� ��������� � ���� �������(�����?)
	for(int i=0;i<13;i++)																														//������ ����� ������ ��������� � ���������
	{																																			//������ ���� �����
		pringDebugMsg(8,0);																														//�������� ����������� � �������, ��� �������
		pringDebugMsg(7, hB);																													//���������� ������� ������������� ���������
		LongByteWord=byteConverter(headerAddrs[hA], headerAddrs[hA+1], headerWordSizeOf[hC], headerWordInvert[hD]);								//�������� ������� ����������� ������� ������, ��� ��������� ��� ����� ����� �� �������� � ������ �����
		checkStatus(0);																															//��������� �����-������������� ������
		pringDebugMsg(headerDebugPrintParameters[hB], LongByteWord);																			//����� ���������� ���������, � ������� ����������� �������� ��������� ���������
		structFiller(hB, LongByteWord);																											//����� � ��������� ������������� ��������
		clearByteBuffer();																														//������� ����� ����� ��������� ������ � ���
		LongByteWord=0;																															//������ ���������� � ������� ������ ���������� �������(�����? ���������� ������������ ����� ������ �� �������)
		hA++;																																	//�������
		hB++;																																	//�������
		hC++;																																	//�������
		hD++;																																	//�������
	}																																			//����� ���� �����
	pringDebugMsg(8,0);																															//����� ����������� � �������, ����� ���� ��� �������
	analyzeState=1;																																//���������� ���� ��������� �������(�������-������� ���� ����� ��������)
	return analyzeState;																														//����������, ��� �� ������ ������, ��� �� ��������
}																																				//����� ���� �������
uint32_t byteConverter(int startOffset, int endOffset, int ByteLenght, bool invertState)														//������� ������������� �������� ������ �� 32 � 8,16,32 ���������
{																																				//������ ���� �������
	uint32_t quadByte;																															//��������� 4 �������� ��������� ����������
	uint16_t doubleByte;																														//��������� ������������ ��������� ����������
	uint8_t singleByte;																															//��������� ������������ ��������� ����������
	int i=0;																																	//��������� ��������� ������ ��������
	int startMarker=startOffset;																												//��������� � ������������ ����������� ��������� ��������� ������ ������ ����������
	int endMarker=endOffset;																													//��������� � ������������ ����������� ��������� ��������� ����� ������ ����������
	while(startMarker<endMarker)																												//������ ����� ������ ���������� ������
	{																																			//������ ���� �����
		ByteBuffer[i]=FileHeader[startMarker];																									//��������� ������������ � ����� ����������, ����������� �� ��������� ������
		pringDebugMsg(32,ByteBuffer[i]);																										//�������� � ������� � ������������� ������
		i++;																																	//������������� ����� ������
		startMarker++;																															//������������� ����� ������� � �������� ���� ������
	}																																			//����� ���� �����
	i=0;																																		//������ ����������(�����? ��� ����� �� �����)
	switch(ByteLenght)																															//�������� ������� ���������� ��������� � ������
	{																																			//������ ���� switch
		case 0:																																	//� ������ ���� �������� �� ����������
			pringDebugMsg(30,0);																												//����� � ������� ����������� �� ����
			convertState=0;																														//����� ���� ������
			break;																																//������� �� �����
		case 1:																																	//� ������ ���� �������� 1 �������
			pringDebugMsg(31,0);																												//����� ��������� � ������� �� ����
			singleByte=FileHeader[startMarker];																									//���������� �������� � ���������� ��� ������
			convertState=1;																														//���������� ���� �������� ��������
			return singleByte;																													//���������� ���������� �� ����� ������ �������
			break;																																//������� �� �����
		case 2:																																	//� ������ ���� ���������� 2 �������
			massiveSwap(invertState);																											//�������� ������� �������������� ���������� � �������� �� �������� � ����������� � ������������� ����������
			doubleByte=ByteBuffer[0];																											//����� ������� ����
			doubleByte=doubleByte|ByteBuffer[1]<<8;																								//����� ������� ����
			pringDebugMsg(28,doubleByte);																										//���������� � ������� ��� ����������
			convertState=1;																														//���������� ���� �������� ��������
			return doubleByte;																													//���������� ���������� �� ����� ������ �������
			break;																																//������� �� �����
		case 4:																																	//� ������ ���� ���������� 4 �������
			massiveSwap(invertState);																											//�������� ������� ��������������� ���������� � �������� �� �������� � ����������� � ������������� ����������
			quadByte=ByteBuffer[0];																												//����� ������� ����
			quadByte=quadByte|ByteBuffer[1]<<8;																									//����� ���� ��������
			quadByte=quadByte|ByteBuffer[2]<<16;																								//����� ���� ��������
			quadByte=quadByte|ByteBuffer[3]<<24;																								//����� ������� ����
			pringDebugMsg(27,quadByte);																											//� ������� ������� �� ���� � ���������� ���������
			convertState=1;																														//���������� ���� �������� ��������
			return quadByte;																													//���������� ���������� �� ����� ������
			break;																																//������� �� �����
	}																																			//����� ���� �����
	return convertState;																														//���������� ���� ���������
}																																				//����� �������
uint8_t massiveSwap(bool swapState)																												//���������� ������ �������� ��������, ������� ��� "������������ ������ �� ���������" ���������������
{																																				//������� �� ���������� �������, �� ���� �� ��������
	uint32_t tempByte;																															//��������� ��������� ����������
	uint8_t tempBuffer[4];																														//��������� ��������� ����� ��� �����
	memset(tempBuffer,0x00,sizeof(tempBuffer));																									//� ����� ������ ��� �� ���������� ������
	if(swapState==1)																															//�������������� ������?
	{																																			//���� ������, ��...
		pringDebugMsg(34,0);																													//...�������� �� ���� � �������
		tempBuffer[0]=ByteBuffer[3];																											//�������� ��������������
		tempBuffer[1]=ByteBuffer[2];																											//����� ������� ������� ���������� ������ � ������...
		tempBuffer[2]=ByteBuffer[1];																											//...� ������ ���������� ������ � �����
		tempBuffer[3]=ByteBuffer[0];																											//...�����...
		ByteBuffer[0]=tempBuffer[0];																											//...������������ ��� ��� ����� ������� ��� ������ � ������
		ByteBuffer[1]=tempBuffer[1];																											//...
		ByteBuffer[2]=tempBuffer[2];																											//...
		ByteBuffer[3]=tempBuffer[3];																											//...
	}																																			//����� ����������
	else																																		//���� �� ������, ��...
	{pringDebugMsg(35,0);}																														//...����� � ������� ��� �� ������ � ������� �� �������
}																																				//����� ���� �������
void checkStatus(uint8_t statusCode)																											//���������� �������
{																																				//������ ���� �������
	pringDebugMsg(74, statusCode);																												//�������� �� ���� � ������� � ���������� ��� ��������
	switch(statusCode)																															//������ ��������
	{																																			//������ ���� switch
		case 0:																																	//� ������ ���� ������ ��� 0(��������� �����������)
			if(convertState!=0)																													//�������� ������� ����� ������ �����������
			{pringDebugMsg(10,0);}																												//� ����� ������ ����� � ������� �� ����
			else																																//�����...
			{pringDebugMsg(20,convertState);pringDebugMsg(15,0);}																				//...���������� ���������� �����
			pringDebugMsg(20,convertState);																										//� ������� ��������� � ����� 0(������)
			break;																																//����� �� �����
		case 1:																																	//� ������ ���� ������ ��� 1(��������� �����������)
			if(analyzeState!=0)																													//��������� ��������� ���������� ���������
			{pringDebugMsg(11,0);}																												//� ������ ������ ����� �� ����
			else																																//�����...
			{pringDebugMsg(21,analyzeState);pringDebugMsg(16,0);}																				//...���������� ���������� �����
			pringDebugMsg(21,analyzeState);																										//� �������� �� ������
			break;																																//������� �� �����
		case 2:																																	//� ������ ���� ������ ��� 2(��������� ��������� ���������)
			if(ahsoka!=0)																														//��������� ��������� �����
			{pringDebugMsg(12,0);}																												//� ������ ���� ��������� ��������� ����������, ������� �� ���� � �������
			else																																//�����...
			{pringDebugMsg(22,ahsoka);pringDebugMsg(17,0);}																						//����� � ������� ����������� � ����� ���������
			pringDebugMsg(22,ahsoka);																											//� ���������� ��������� �����
			break;																																//������� �� �������
		case 3:																																	//� ������ ���� ������ ��� 3(����������� ���������)
			if(gabella!=0)																														//���� ����������� ���� �������
			{pringDebugMsg(13,0);}																												//����� �� ���� � �������
			else																																//�����...
			{pringDebugMsg(23,gabella);pringDebugMsg(18,0);}																					//...����� � ������� ������ �������� ����������� ���������
			pringDebugMsg(23,gabella);																											//���������� ���������� �����
			break;																																//������� �� �������
		case 4:																																	//� ������ ���� ������� ��� 4
			if(doubledoor!=0)																													//��������� ���������� ������ ���������
			{pringDebugMsg(14,0);}																												//����� �� ���� � �������
			else																																//�����...
			{pringDebugMsg(24,doubledoor);pringDebugMsg(19,0);}																					//...����� �� ������ � �������
			pringDebugMsg(24,doubledoor);																										//� ���������� ���������� �����
			break;																																//������� �� �������
		case 5:																																	//� ������ ���� ������� ��� 5
			if(Egor!=0)																															//��������� ����� ����������� ����������
			{pringDebugMsg(64,0);}																												//� ������ ���� ��������� �������, ����� � �������
			else																																//�����...
			{pringDebugMsg(66,Egor);pringDebugMsg(65,0);}																						//����� ��������� �� ������
			pringDebugMsg(66,Egor);																												//� ���������� ��������� �����
			break;																																//������� �� �������
		case 6:																																	//� ������ ���� ������� ��� 6
			if(cruzo!=0)																														//��������� ����� �������������� ���������
			{pringDebugMsg(72,0);}																												//���� ��� ������ �� ����� � �������
			else																																//�����...
			{pringDebugMsg(71,cruzo);pringDebugMsg(73,0);}																						//...���������� � ������� �� ������
			pringDebugMsg(71,cruzo);																											//� ���������� ��������� ����������
			break;																																//������� �� �������
	}																																			//����� ���� �����
}																																				//����� ���� �������
uint32_t structFiller(int structShift, uint32_t paramToWrite)																					//��������� �������� ������������ ���������, ������ �� ������
{																																				//������ �������
	uint32_t qWordToConvert;																													//������� ��������� 2 ������� ����������
	uint16_t dWordToConvert;																													//������� ��������� 4 ������� ����������
	switch(structShift)																															//������ ����� switch
	{																																			//������ ���� �����
		case 0:																																	//� ������ ���� ������� ������ ����� RIFF
			Wave.RiffSign=qByteConverter(paramToWrite);																							//�������� ����� � ������� ����������� �� ��������� �������
			pringDebugMsg(3,0);																													//����� � ������� ����������� � ������ � ���������
			if(Wave.RiffSign==RIFFsignature)																									//���������� � ��������
			{pringDebugMsg(41, structShift);}																									//� ������ ���� ���������� ����� ��������� � �������� ����� �� ���� �������
			else																																//�����...
			{pringDebugMsg(42, structShift);}																									//������� �� ������
			break;																																//������� �� �����
		case 1:																																	//� ������ ���� ������� ������ ����� ������� �����
			Wave.chunkSizeBytes=qByteConverter(paramToWrite);																					//������������ � 4 ������� ������
			pringDebugMsg(3,structShift);																										//����� � ������� ����������� � ������ � ���������																									
			pringDebugMsg(41, structShift);																										//�������� �� ������ � �������(���� ��� �������� �� ��������������)
			break;																																//������� �� �����
		case 2:																																	//� ������ ���� ������� ������ ����� WAVE
			Wave.WaveSign=qByteConverter(paramToWrite);																							//������������
			pringDebugMsg(3,structShift);																										//����� � ������� ����������� � ������ � ���������
			if(Wave.WaveSign==WAVEsignature)																									//���������� � ��������
			{pringDebugMsg(41, structShift);}																									//�������� �� ������ � �������(���� ��� �������� �� ��������������)
			else																																//�����...
			{pringDebugMsg(42, structShift);}																									//�������� �� ������
			break;																																//����� �� �����
		case 3:																																	//� ������ ���� ������� ������ ����� fmt
			Wave.fmtSign=qByteConverter(paramToWrite);																							//������������																							
			pringDebugMsg(3,structShift);																										//����� � ������� ����������� � ������ � ���������
			if(Wave.fmtSign==fmtSignature)																										//���������� � ��������
			{pringDebugMsg(41, structShift);}																									//�������� �� ������ � �������(���� ��� �������� �� ��������������)
			else																																//�����...
			{pringDebugMsg(42, structShift);}																									//����� �� ������
			break;																																//������� �� �����
		case 4:																																	//� ������ ���� ������� ������ ������� ������
			Wave.DataFormatLenght=qByteConverter(paramToWrite);																					//������������
			pringDebugMsg(3,structShift);																										//����� � ������� ����������� � ������ � ���������
			pringDebugMsg(41, structShift);																										//�������� �� ������ � �������(���� ��� �������� �� ��������������)
			break;																																//������� �� �����
		case 5:																																	//� ������ ���� ������� ������ ���� ������
			Wave.compressionCode=dByteConverter(paramToWrite);																					//������������
			pringDebugMsg(3,structShift);																										//����� � ������� ����������� � ������ � ���������
			pringDebugMsg(41, structShift);																										//�������� �� ������ � �������(���� ��� �������� �� ��������������)
			break;																																//������� �� �����
		case 6:																																	//� ������ ���� ������� ������ ���������� �������
			Wave.soundChannels=dByteConverter(paramToWrite);																					//������������
			pringDebugMsg(3,structShift);																										//����� � ������� ����������� � ������ � ���������
			pringDebugMsg(41, structShift);																										//�������� �� ������ � �������(���� ��� �������� �� ��������������)
			break;																																//������� �� �����
		case 7:																																	//� ������ ���� ������� ������ ������� �������������
			Wave.sampleRate=qByteConverter(paramToWrite);																						//������������
			pringDebugMsg(3,structShift);																										//����� � ������� ����������� � ������ � ���������
			pringDebugMsg(41, structShift);																										//�������� �� ������ � �������(���� ��� �������� �� ��������������)	
			break;																																//������� �� �����
		case 8:																																	//� ������ ���� ������� ������ ��������
			Wave.byteRate=qByteConverter(paramToWrite);																							//������������
			pringDebugMsg(3,structShift);																										//����� � ������� ����������� � ������ � ���������
			pringDebugMsg(41, structShift);																										//�������� �� ������ � �������(���� ��� �������� �� ��������������)
			break;																																//������� �� �����
		case 9:																																	//� ������ ���� ������� ������ ������� ������ � ������
			Wave.BytesInSample=dByteConverter(paramToWrite);																					//������������
			pringDebugMsg(3,structShift);																										//����� � ������� ����������� � ������ � ���������
			pringDebugMsg(41, structShift); 																									//�������� �� ������ � �������(���� ��� �������� �� ��������������)
			break;																																//������� �� �����
		case 10:																																//� ������ ���� ������� ������ ������� ������
			Wave.BitDepth=dByteConverter(paramToWrite);																							//������������
			pringDebugMsg(3,structShift);																										//����� � ������� ����������� � ������ � ���������
			pringDebugMsg(41, structShift);																										//�������� �� ������ � �������(���� ��� �������� �� ��������������)
			break;																																//������� �� �����
		case 11:																																//� ������ ���� ������� ������ ����� data
			Wave.dataSign=qByteConverter(paramToWrite);																							//������������
			pringDebugMsg(3,structShift);																										//����� � ������� ����������� � ������ � ���������
			if(Wave.dataSign==dataSignature)																									//���������� � ��������
			{pringDebugMsg(41, structShift);}																									//�������� �� ������ � �������(���� ��� �������� �� ��������������)
			else																																//�����...
			{pringDebugMsg(42, structShift);}																									//����� ��������� �� ������
			break;																																//������� �� �����
		case 12:																																//� ������ ���� ������� ������ ������� ���������� � ��������
			Wave.chunkSizeWoutHeader=qByteConverter(paramToWrite);																				//������������
			pringDebugMsg(3,structShift);																										//����� � ������� ����������� � ������ � ���������
			pringDebugMsg(41, structShift);																										//�������� �� ������ � �������(���� ��� �������� �� ��������������)
			break;																																//������� �� �����
	}																																			//����� �����
}																																				//����� ���� �������
uint32_t qByteConverter(uint32_t wordToConvert)																									//��������� ����������� 32->32 ���
{																																				//������ ���� ���������
	pringDebugMsg(4,0);																															//����� � ����������� ��� ����������� �� ���������
	return wordToConvert;																														//���������� ��������
}																																				//����� ���� �������
uint16_t dByteConverter(uint32_t wordToConvert)																									//��������� ����������� 32->16 ���
{																																				//������ ���� �������
	uint16_t doubleByteWord;																													//������������� ��������� ����������
	//doubleByteWord=wordToConvert<<16;																											//�������
	doubleByteWord=wordToConvert;																												//���������� � ���������� ���������� ��������
	pringDebugMsg(5,0);																															//����� �� ���� � �������
	return doubleByteWord;																														//���������� �������� �� ����� ������
}																																				//����� ���� �������
uint8_t sByteConverter(uint32_t wordToConvert)																									//��������� ����������� 32->8 ���
{																																				//������ ���� �������
	uint8_t singleByteWord;																														//�������������� ����������
	//singleByteWord=wordToConvert<<24;																											//�������?
	singleByteWord=wordToConvert;																												//���������� �������� � ��� ����������
	pringDebugMsg(6,0);																															//����� � ������� �� ����
	return singleByteWord;																														//���������� �������� �� ����� ������
}																																				//����� ���� �������
void structAnalyzer(void)																														//��������� �������� ���������, ������ �� ������, �Ѩ � ��������
{																																				//������ �������
	int chechedSteps=0;																															//�������
	int headerDifference;																														//����� ���������
	headerDifference=Wave.chunkSizeBytes-Wave.chunkSizeWoutHeader;																				//��������� ����� ���������
	pringDebugMsg(9,0);																															//����� � �������
	if(Wave.RiffSign==RIFFsignature)																											//��������� � �������� ����� RIFF
	{																																			//������ ����
		chechedSteps++;																															//����������� ���������� ����������� ��������� �� 1
		pringDebugMsg(39,0);																													//����� � ���
	}																																			//����� ����
	else																																		//�����...
	{pringDebugMsg(40,0);}																														//����� �� ������
	if(Wave.WaveSign==WAVEsignature)																											//���������� ����� WAVE
	{																																			//������ ����
		chechedSteps++;																															//������������� �������� �������� �������
		pringDebugMsg(43,0);																													//����� � �������
	}																																			//����� ����
	else																																		//�����...
	{pringDebugMsg(40,0);}																														//...����� ��������� �� ������
	if(Wave.fmtSign==fmtSignature)																												//���������� ����� fmt
	{																																			//������ ����
		chechedSteps++;																															//������������� �������� �������� �������
		pringDebugMsg(44,0);																													//����� � �������
	}																																			//����� ����
	else																																		//�����...
	{pringDebugMsg(40,0);}																														//...����� ��������� �� ������
	if(Wave.dataSign=dataSignature)																												//���������� ����� data
	{																																			//������ ����
		chechedSteps++;																															//������������� �������� �������� �������
		pringDebugMsg(45,0);																													//����� � �������
	}																																			//����� ����
	else																																		//�����...
	{pringDebugMsg(40,0);}																														//...�������� �� ������
	pringDebugMsg(46,0);																														//����� � ������ ������ ����������
	pringDebugMsg(47,0);																														//����� � �������
	printf(FileSizeMsg, Wave.chunkSizeBytes);																									//��������� �� ������ �����, ������ �� ���������
	pringDebugMsg(47,0);																														//����� � �������
	printf(FileSizeWoutHeaderMsg, Wave.chunkSizeWoutHeader);																					//����� � ������� ������ ��� ���������
	if(headerDifference==36)																													//���������� ������ ��������� ��� ����� ����� ������
	{																																			//������ ����
		chechedSteps++;																															//������������� �������� �������� �������
		pringDebugMsg(48,0);																													//����� � �������
	}																																			//����� ����
	else																																		//�����...
	{pringDebugMsg(49,0);}																														//...����� � ������� ��������� �� ������
	pringDebugMsg(47,0);																														//����� � �������
	printf(SampleRateMsg, Wave.sampleRate);																										//����� ������� �������������
	pringDebugMsg(47,0);																														//����� � �������
	printf(ByteRateMsg, Wave.byteRate);																											//����� �������
	pringDebugMsg(47,0);																														//����� � �������
	printf(BitDepthMsg, Wave.BitDepth);																											//����� ������� �������
	pringDebugMsg(47,0);																														//����� � �������
	printf(ChannelsMsg, Wave.soundChannels);																									//����� ����� �������
	pringDebugMsg(50,Wave.soundChannels);																										//����� ����� �������
	pringDebugMsg(47,0);																														//����� � �������
	printf(BytesInSampleMsg, Wave.BytesInSample);																								//����� ���������� ���� � �������
	pringDebugMsg(47,0);																														//����� � �������
	printf(CodecTypeMsg);																														//����� ��� ������
	pringDebugMsg(51,Wave.compressionCode);																										//����� ��� ������
	wordSamplesValuePos=((Wave.chunkSizeWoutHeader-8)*8)/Wave.soundChannels/Wave.BitDepth;														//��������� ��������� ���������� �������
	pringDebugMsg(68, wordSamplesValuePos);																										//����� � �������
	if(chechedSteps==5)																															//���������� ���������� ���������� ������ � ��������� � ��
	{																																			//������ ���� �����
		pringDebugMsg(52,0);																													//����� � �������
		ahsoka=1;																																//���� ��� ��� �� ���������� ���� �� ������
		checkStatus(2);																															//�������� �������� �����
	}																																			//����� ����
	else																																		//�����...
	{pringDebugMsg(17,0);}																														//�������� �� ������ � ������� �� ���������
}																																				//����� ���� �������
void structModifier(void)																														//������� ������ � ���������
{																																				//������ ���� �������
	float sampleDivide;																															//�������, ����������� ���������� ������� ��������� ����� � ���������� ������� ������ �� convertParams.ini
	uint16_t newBytesInSample;																													//��������� ���������� ��� ���������� ���������� ���� � ����� ������� �� ���� �������
	uint32_t newByteRate;																														//��������� ���������� ��� ���������� �������� �������� ������, ����/�
	uint32_t newFileSizeWOutHeader;																												//��������� ���������� ��� ���������� ������� ����� ��� ���������
	sampleDivide=Wave.sampleRate/FilSet.FSetSampleRate;																							//����� �� �������� ����������� ���������� �������, ��������� ���� �����
	pringDebugMsg(53,0);																														//����� ��������� � ������ ������ �������
	pringDebugMsg(99, FilSet.FSetSamplesValue);																									//����� � �������
	pringDebugMsg(58,0);																														//����� ��������� � ���, ��� ��� �������� ������ � ���������
	Wave.sampleRate=FilSet.FSetSampleRate;																										//������ � ��������� ������� �������������, ���������� �� ����� convertParams.ini
	pringDebugMsg(55, Wave.sampleRate);																											//����� ��������� �� ����
	Wave.BitDepth=FilSet.FSetBitDepth;																											//������ � ��������� ������� �������, ���������� �� ����� convertParams.ini
	pringDebugMsg(54, Wave.BitDepth);																											//����� ��������� �� ����
	Wave.soundChannels=FilSet.FSetChannels;																										//������ � ��������� ���������� �������, ���������� �� ����� convertParams.ini
	pringDebugMsg(57, Wave.soundChannels);																										//����� ��������� �� ����
	newByteRate=(Wave.sampleRate*Wave.BitDepth*Wave.soundChannels)/8;																			//���������� �������� �������� ������, ���� � �������
	Wave.byteRate=newByteRate;																													//������ � ��������� ����������
	pringDebugMsg(56, Wave.byteRate);																											//����� ��������� �� ����
	newBytesInSample=(Wave.BitDepth*Wave.soundChannels)/8;																						//���������� ���������� ������ � ����� ������� �� ���� �������
	Wave.BytesInSample=newBytesInSample;																										//������ � ���������
	pringDebugMsg(67, Wave.BytesInSample);																										//����� ��������� �� ����
	printSampleDivide(sampleDivide);																											//����� ������� ����������� �������
	newFileSizeWOutHeader=(((FilSet.FSetSamplesValue/sampleDivide)*Wave.BitDepth*Wave.soundChannels)/8)+8;										//���������� ������� ����� ��� ���������
	Wave.chunkSizeWoutHeader=newFileSizeWOutHeader;																								//������ � ���������
	pringDebugMsg(69, Wave.chunkSizeWoutHeader);																								//����� � �������
	Wave.chunkSizeBytes=newFileSizeWOutHeader+36;																								//�������� 36 ���� ���������
	pringDebugMsg(70, Wave.chunkSizeBytes);																										//����� � �������
	cruzo=1;																																	//���������� 1, ��� ������, � ���������� ����� ������� ��� ������������ �������
	checkStatus(6);																																//������� ������� �������� ����� ���������
}																																				//����� ���� �������
int WriteSettingsFile(void)																														//������� ���������� ����������������� ��������� � ������
{																																				//������ ���� �������
	pringDebugMsg(75,0);																														//����� � ������� ��������� � ������ ������
	clearHeaderBuffer();																														//������ ����� ���������
	writeBuffer(headerAddrs[0], headerAddrs[1], Wave.RiffSign, headerWordSizeOf[0], headerWordInvert[0]);										//����� � ����� ����� RIFF
	writeBuffer(headerAddrs[1], headerAddrs[2], Wave.chunkSizeBytes, headerWordSizeOf[1], headerWordInvert[1]);									//����� � ����� ������ �����
	writeBuffer(headerAddrs[2], headerAddrs[3], Wave.WaveSign, headerWordSizeOf[2], headerWordInvert[2]);										//����� � ����� ����� WAVE
	writeBuffer(headerAddrs[3], headerAddrs[4], Wave.fmtSign, headerWordSizeOf[3], headerWordInvert[3]);										//����� � ����� ����� fmt
	writeBuffer(headerAddrs[4], headerAddrs[5], Wave.DataFormatLenght, headerWordSizeOf[4], headerWordInvert[4]);								//����� � ����� ������ �����
	writeBuffer(headerAddrs[5], headerAddrs[6], Wave.compressionCode, headerWordSizeOf[5], headerWordInvert[5]);								//����� � ����� ��� ������
	writeBuffer(headerAddrs[6], headerAddrs[7], Wave.soundChannels, headerWordSizeOf[6], headerWordInvert[6]);									//����� � ����� ����� �������
	writeBuffer(headerAddrs[7], headerAddrs[8], Wave.sampleRate, headerWordSizeOf[7], headerWordInvert[7]);										//����� � ����� ������� �������������
	writeBuffer(headerAddrs[8], headerAddrs[9], Wave.byteRate, headerWordSizeOf[8], headerWordInvert[8]);										//����� � ����� �������
	writeBuffer(headerAddrs[9], headerAddrs[10], Wave.BytesInSample, headerWordSizeOf[9], headerWordInvert[9]);									//����� � ����� ������ ������� � ������
	writeBuffer(headerAddrs[10], headerAddrs[11], Wave.BitDepth, headerWordSizeOf[10], headerWordInvert[10]);									//����� � ����� ������� �������
	writeBuffer(headerAddrs[11], headerAddrs[12], Wave.dataSign, headerWordSizeOf[11], headerWordInvert[11]);									//����� � ����� ����� data
	writeBuffer(headerAddrs[12], headerAddrs[13], Wave.chunkSizeWoutHeader, headerWordSizeOf[12], headerWordInvert[12]);						//����� � ����� ������ ����� ��� ���������
	BufferReader();																																//�������� ���������� � ��������� ������ ��� ������ ��� ����������� � ������ �������
	pringDebugMsg(81,0);																														//���������� �� ����
	printf("%s",fileNameHdrDat);
	FWr=fopen(fileNameHdrDat, "wb");																											//������� ���� ��������� � ������ ��������������� ������
	if(FWr != NULL)																																//��������� ������� �� ������� ����
	{																																			//������ ����(������)
		printf(" �����\n");																														//����� � ������� ��� ��� ������
	}																																			//����� ����(������)
	else																																		//�����...
	{																																			//������ ����(����)
		printf(" �� ������� ������� ���� %s\n",fileNameHdrDat);																					//...����� � ��������� ���������
		exit(0);																																//������� � ����� ������ 0
	}																																			//����� ����(����)
	fseek(FWr, 0, SEEK_SET);																													//������������� ������ �� 0
	fwrite(FileHeader, sizeof(uint8_t), sizeof(FileHeader), FWr);																				//����� ��������� � ����
	fclose(FWr);																																//�������� ����� ��� ������
}																																				//����� ���� �����
int ReadSettingsFile(void)																														//������� ���������� �� �����
{																																				//������ ����
	uint32_t fSrcTagEndPos;																														//��������� ���������� � ������� ����� ������� ����� ���� FEND ��� ����� ���������
	uint32_t fNamtagEndPos;																														//��������� ���������� � ������� ����� ������� ����� ���� FEND ��� ���������������� ����� �����
	uint8_t readCursorPos=0;																													//��������� ��������� ���������� ������� ������� ����� ��������� ��� �����������
	char fSrcNameBuffer[64];																													//��������� ������ � ������� ����� ��������� "���������" �������� ��� �����(��� �����)
	char fNamNameBuffer[64];																													//��������� ������ � ������� ����� ��������� "���������" ��������������� ��� �����(��� �����)
	memset(fSrcNameBuffer, 0x00, sizeof(fSrcNameBuffer));																						//������ ������ ��������� �����
	memset(fNamNameBuffer, 0x00, sizeof(fNamNameBuffer));																						//������ ������ ��������������� �����
	char *endTag;																																//��������� ��������� �� ������ ����� ������� ������ � ������
	pringDebugMsg(59,1);																														//����� � ������� ���� � ������ �����
	FSet=fopen("convertParams.ini", "rb");																										//��������� ���� ��� ��������
	if(!FSet)																																	//��������� ����� �������� �����
	{																																			//������ ����
		pringDebugMsg(88,0);																													//���� ���� �� ������, ��� ��� ���������� �������, �������� ������� ��� ����� + ����� � �������
		printf("���� convertParams.ini �� ������ ��� ���������. ����� ������ ���� � ����������� �� �������� ���������\n");						//����� �� ���� � �������
		storeStructToFile();																													//���������� ��������� � ����
		pringDebugMsg(84,0);																													//����� �� ����������
	}																																			//����� ����
	else																																		//�����...
	{																																			//������ ����
		pringDebugMsg(89,0);																													//...����� � �������
		printf("���� convertParams.ini ������ � ������\n");																						//��� ���� ������																																			//����� ����
		fread(fileMassive, 1, sizeof(fileMassive), FSet);																						//������ ���� ��������� � ���������� ������
		cursorSymbol=strstr(fileMassive, wordFilenameSource);																					//���� ��� FSRC
		wordFsrcPos=cursorSymbol-fileMassive+1;																									//����� ����� ������ ����
		cursorPosit=wordFsrcPos+wordFilenameShift;																								//����� ����� �������
		fseek(FSet, cursorPosit, SEEK_SET);																										//������ ������ �� ������
		fscanf(FSet, "%s", &fileNameSrc);																										//������ ���������� ����� �� ������������� ������
		endTag=strstr(fileNameSrc, wordSrcFilenameEnd);																							//���������� � ��������� ����� ������� � �������� ���������� ��������� ����� FEND
		fSrcTagEndPos=endTag-fileNameSrc;																										//������������ ����� ������� ��������, � ������ ������ ��� ��� ��������� �����
		while(readCursorPos<fSrcTagEndPos)																										//��������� ���� ������������ ������� � ������ ������, ������� ����� ��� ����� �����
		{																																		//������ �����
			fSrcNameBuffer[readCursorPos]=fileNameSrc[readCursorPos];																			//����������� ��������� ������
			readCursorPos++;																													//������������� ������ �������
		}																																		//����� ����
		readCursorPos=0;																														//���������� ������� �������
		cursorSymbol=strstr(fileMassive, wordFilename);																							//���� ��� FNAM
		wordFnamePos=cursorSymbol-fileMassive+1;																								//����� ����� ������ ����
		cursorPosit=wordFnamePos+wordFilenameShift;																								//����� ����� �������
		fseek(FSet, cursorPosit, SEEK_SET);																										//������ ������ �� ������
		fscanf(FSet, "%s", &fileName);																											//������ ���������� ����� �� ������������� ������
		endTag=strstr(fileName, wordNameFilenameEnd);																							//���������� � ��������� ����� ������� � �������� ���������� ��������� ����� FEND
		fNamtagEndPos=endTag-fileName;																											//��������� ����� ���������������� ����� �����
		while(readCursorPos<fNamtagEndPos)																										//��������� ���� ����������� ������� � ������ ������ ������� ����� ��� ����� �����
		{																																		//������ ���� �����
			fNamNameBuffer[readCursorPos]=fileName[readCursorPos];																				//����������� ��������� ������
			fileNameHdrDat[readCursorPos]=fileName[readCursorPos];
			readCursorPos++;																													//������������� ������ �������
		}																																		//����� ����
		cursorSymbol=strstr(fileMassive, wordConvert);																							//���� ��� Convert
		wordConvertPos=cursorSymbol-fileMassive+1;																								//����� ����� ������ ����
		cursorPosit=wordConvertPos+wordConvertShift;																							//����� ����� �������
		fseek(FSet, cursorPosit, SEEK_SET);																										//������ ������ �� ������
		fscanf(FSet, "%d", &FilSet.FSetWasConverted);																							//������ ���������� �� ������������� ������
		cursorSymbol=strstr(fileMassive, wordSampleRate);																						//���� ��� SampleRate
		wordSampleRatePos=cursorSymbol-fileMassive+1;																							//����� ����� ������ ����
		cursorPosit=wordSampleRatePos+wordSampleRateShift;																						//����� ����� �������
		fseek(FSet, cursorPosit, SEEK_SET);																										//������ ������ �� ������
		fscanf(FSet, "%d", &FilSet.FSetSampleRate);																								//������ ���������� ����� �� ������������� ������
		cursorSymbol=strstr(fileMassive, wordChannels);																							//���� ��� Channels
		wordChannelsPos=cursorSymbol-fileMassive+1;																								//����� ����� ������ ����
		cursorPosit=wordChannelsPos+wordChannelsShift;																							//����� ����� �������
		fseek(FSet, cursorPosit, SEEK_SET);																										//������ ������ �� ������
		fscanf(FSet, "%d", &FilSet.FSetChannels);																								//������ ���������� ����� �� ������������� ������
		cursorSymbol=strstr(fileMassive, wordBitsPerSample);																					//���� ��� BitsPerSample
		wordBitsPerSamplePos=cursorSymbol-fileMassive+1;																						//����� ����� ������ ����
		cursorPosit=wordBitsPerSamplePos+wordBitsPerSampleShift;																				//����� ����� �������
		fseek(FSet, cursorPosit, SEEK_SET);																										//������ ������ �� ������
		fscanf(FSet, "%d", &FilSet.FSetBitDepth);																								//������ ���������� ����� �� ������������� ������
		cursorSymbol=strstr(fileMassive, WordCountOfSamples);																					//���� ��� BitsPerSample
		wordSamplesValuePos=cursorSymbol-fileMassive+1;																							//����� ����� ������ ����
		cursorPosit=wordSamplesValuePos+wordSamplesValueShift;																					//����� ����� �������
		fseek(FSet, cursorPosit, SEEK_SET);																										//������ ������ �� ������
		fscanf(FSet, "%d", &FilSet.FSetSamplesValue);																							//������ ���������� ����� �� ������������� ������
		pringDebugMsg(89,0);																													//��� � �������
		pringDebugMsg(94,fSrcTagEndPos);																										//����� ����� �������� �� ���� FSRC
		pringDebugMsg(89,0);																													//����� � �������
		printf("��� ��������� �����: %s\n", fSrcNameBuffer);																					//����� ��� ��������� �����
		pringDebugMsg(89,0);																													//��� � �������
		pringDebugMsg(94,fNamtagEndPos);																										//����� ����� �������� �� ���� FNAM
		pringDebugMsg(89,0);																													//����� � �������
		printf("��� ����� � ����������: %s\n", fNamNameBuffer);																					//����� ��� ������������� �����
		pringDebugMsg(89,0);																													//��� � �������
		printf("������ �������� �� ����� Convert,SampleRate,Channels,BitsPerSample,SamplesInChannel\n");										//����� ���� ��� ��� ����� ������ �������� �����
		pringDebugMsg(89,0);																													//��� � �������
		pringDebugMsg(90,wordConvertPos);																										//����� ����� �������� �� ���� Convert
		pringDebugMsg(89,0);																													//����� � �������
		pringDebugMsg(90,wordSampleRatePos);																									//����� ����� �������� �� ���� SampleRate
		pringDebugMsg(89,0);																													//����� � �������
		pringDebugMsg(90,wordChannelsPos);																										//����� ����� �������� �� ���� Channels
		pringDebugMsg(89,0);																													//����� � �������
		pringDebugMsg(90,wordBitsPerSamplePos);																									//����� ����� �������� �� ���� BitsPerSample
		pringDebugMsg(89,0);																													//����� � �������
		pringDebugMsg(90,wordSamplesValuePos);																									//����� ����� �������� �� ���� BitsPerSample
	}																																			//����� ����
	pringDebugMsg(89,0);																														//����� � �������
	if(DebugMode==1)																															//������� �� �������� ������ �������
	{																																			//������ ����
		printf("���-�� �������: %d\n", FilSet.FSetChannels);																					//����� ���������� �������
		pringDebugMsg(89,0);																													//����� � �������
		printf("������� �������������: %d ��\n", FilSet.FSetSampleRate);																		//����� ������� �������������
		pringDebugMsg(89,0);																													//����� � �������
		printf("���� �����������: %d\n", FilSet.FSetWasConverted);																				//����� ��������� ����� �����������(���� �� ��� ��� ���)
		pringDebugMsg(89,0);																													//����� � �������
		printf("��� � �������: %d ���\n", FilSet.FSetBitDepth);																					//����� ������� �������
		pringDebugMsg(89,0);																													//����� � �������
		printf("���������� ������� � ����� ������: %d\n", FilSet.FSetSamplesValue);																//����� ���������� ������� �� ���� �����
	}																																			//����� ����
	pringDebugMsg(60, FilSet.FSetSampleRate);																									//����� ������� ������������� � �������
	pringDebugMsg(62, FilSet.FSetChannels);																										//����� ���������� ������� � �������
	pringDebugMsg(61, FilSet.FSetBitDepth);																										//����� ������� ������� � �������
	if(FilSet.FSetWasConverted==0)																												//�������� ����� �����������
	{																																			//������ ����
		pringDebugMsg(63, FilSet.FSetWasConverted);																								//����� � ������� �����
		Egor=1;																																	//������ ����
		checkStatus(5);																															//�������� �������� �����
		pringDebugMsg(83,0);																													//����� � ������� ����������� ��� � ������ ��� ������ �� ������
	}																																			//����� ����
	else																																		//�����...
	{																																			//������ ����
		pringDebugMsg(63, FilSet.FSetWasConverted);																								//...�������� ����������� ���������
		Egor=1;																																	//��������� ���� ����))
		checkStatus(5);																															//�������� ��������
		fclose(FSet);																															//��������� ���� �.� �� ������ �� ����� � ������ ������
		structModifier();																														//����� ��������� � ����
		return 0;																																//���������� 0
	}																																			//����� ����
	fclose(FSet);																																//��������� �����, ���� �� ���-�� ��� �� ��� ������
}																																				//����� �������
inline void clearByteBuffer(void)																												//������� ���������� ������(������������ �������)
{																																				//������ ����
	pringDebugMsg(79,0);																														//����� � ������� ����������� ��� ���� ������ ������
	memset(ByteBuffer,0x00,sizeof(ByteBuffer));																									//������ ������
}																																				//����� ����
inline void clearHeaderBuffer(void)																												//������� ������� ���������(������������ �������
{																																				//������ ����
	pringDebugMsg(80,0);																														//����� ��������� � ��� ��� ��� ����� ������� ������
	for(int i=0;i<43;i++)																														//������ ����� ������
	{																																			//������ ���� �����
		FileHeader[i]=0;																														//������ ��������� ������
	}																																			//����� ���� �����
}																																				//����� ���� �������
inline void BufferReader(void)																													//������� ����������� ��������� � ��������� ������ ��� ������ ���������� �����������(������������)
{																																				//������ ����
	writeDebugHeaderBuffer();																													//�������� ������� �����������
	pringDebugMsg(25,0);																														//����� ����������� �� ����
}																																				//����� ����
uint32_t writeBuffer(int startOffset, int endOffset, uint32_t paramToWrite, int wordSize, bool SwapByte)										//������� ������ ������
{																																				//������ ����
	int debugCursorPos=0;																														//�������������� ����������
	int bufferPos=0;																															//�������������� ���������� ������� ��������
	pringDebugMsg(76,paramToWrite);																												//����� � ������� ��� ������� ������ ���������� ��������
	switch(wordSize)																															//����� ������� ������ � ����������� �� ������� ����������� �� �����
	{																																			//�� ���� 0 ���� - ������, 1 ���� - ����� 1 ����, 2 ����� - ����� ����� � �.�
		case 0:																																	//� ������ ���� 0 ����(NANI?)
			pringDebugMsg(77,0);																												//����� ��� ����� ���������� �� ���������� � ������� �� ���������
			break;																																//����� �� �����
		case 1:																																	//� ������ ���� 1 ����
			ByteBuffer[0]=paramToWrite;																											//����� � ����� 1 ����
			break;																																//������� �� �����
		case 2:																																	//� ������ ���� 2 �����
			ByteBuffer[0]=paramToWrite;																											//����� ������� ����
			ByteBuffer[1]=paramToWrite>>8;																										//����� ������� ����
			break;																																//������� �� �����
		case 4:																																	//� ������ ���� 4 �����
			ByteBuffer[0]=paramToWrite;																											//����� ������� ����
			ByteBuffer[1]=paramToWrite>>8;																										//����� ���� ��������
			ByteBuffer[2]=paramToWrite>>16;																										//����� ���� ��������
			ByteBuffer[3]=paramToWrite>>24;																										//����� ������� ����
			break;																																//������� �� �����
	}																																			//����� ���� �����
	massiveSwap(SwapByte);																														//�������������� ������
	while(debugCursorPos<wordSize)																												//�������� ���� ������ ����������� ���������� ������
	{																																			//������ �����
		pringDebugMsg(78, ByteBuffer[debugCursorPos]);																							//���������� � ������� �� ��� ��� ���������
		debugCursorPos++;																														//������������� ������
	}																																			//����� �����
	debugCursorPos=0;																															//���������� ����������
	while(startOffset<endOffset)																												//������ ����� ������ ����������� �� ������ � ��������� � �������� ���������
	{																																			//������ ���� �����
		FileHeader[startOffset]=ByteBuffer[bufferPos];																							//���������� ����������� �� ���������� �������
		bufferPos++;																															//������������� ���������� ������� ������� ���������� ������
		startOffset++;																															//������������� ���������� ������� ���������
	}																																			//����� �����
	bufferPos=0;																																//���������� ����������
	clearByteBuffer();																															//������ �����
}																																				//����� �������
void storeStructToFile(void)																													//������� ������ �������� � ����
{																																				//������ �������
	uint8_t crlfSign[2]={0x0D, 0x0A};																											//����� CR LF(������� ������� �� ����� ������)
	bool WordConverted=0;																														//�������������� ����
	char *FnameSrc="FSRC>";																														//��� ��������� �����
	char *FnameBod="FBOD>";																														//��� ���� �����
	char *Fnametgt="FTGT>";																														//��� ����� ����� ����������
	char *Fname="FNAM>";																														//��� �����
	char *WordConvert="Convert=";																												//������� ���� Convert
	char *WordSampleRate="SampleRate=";																											//������� ���� SampleRate
	char *WordChannels="Channels=";																												//������� ���� Channels
	char *WordBitsPerSample="BitsPerSample=";																									//������� ���� BitsPerSample
	char *WordCountOfSamples="SamplesInChannel=";																								//������� ���� SamplesInChannel
	pringDebugMsg(86,0);																														//���������� ��� ��� ����� ������ � ����
	FSet=fopen("convertParams.ini", "wb");																										//��������� ���� �� ������ ��� ��������(��� ��������? ��� ����� �������)
	fseek(FSet, 0, SEEK_SET);																													//������������ ������ �� 0
	fprintf(FSet, "%s", FnameSrc);																												//����� ��� FNAM
	fprintf(FSet, "%s", fileNameSrc);																											//����� ��� �����
	fprintf(FSet, "%s", wordSrcFilenameEnd);																									//����� ��� >FSND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//����� CR LF
	fprintf(FSet, "%s", Fname);																													//����� ��� FNAM
	fprintf(FSet, "%s", fileNameHdrDat);																										//����� ��� �����
	fprintf(FSet, "%s", wordNameFilenameEnd);																									//����� ��� >FNND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//����� CR LF
	fprintf(FSet, "%s", FnameBod);																												//����� ��� FBOD
	fprintf(FSet, "%s", fileNameBodDat);																										//����� ��� �����
	fprintf(FSet, "%s", wordBodyFilenameEnd);																									//����� ��� >FBND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//����� CR LF
	fprintf(FSet, "%s", Fnametgt);																												//����� ��� FTGT
	fprintf(FSet, "%s", fileNameTgtDat);																										//����� ��� �����
	fprintf(FSet, "%s", wordTargFilenameEnd);																									//����� ��� >FTND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//����� CR LF
	fprintf(FSet, "%s", WordConvert);																											//����� ��� Convert
	fprintf(FSet, "%d", WordConverted);																											//����� ���� ���������
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//����� CR LF
	fprintf(FSet, "%s", WordSampleRate);																										//����� ��� SampleRate
	fprintf(FSet, "%d", Wave.sampleRate);																										//����� ������� ������������� ������
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//����� CR LF
	fprintf(FSet, "%s", WordChannels);																											//����� ��� Channels
	fprintf(FSet, "%d", Wave.soundChannels);																									//����� ���������� �������
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//����� CR LF
	fprintf(FSet, "%s", WordBitsPerSample);																										//����� ��� BitsPerSample
	fprintf(FSet, "%d", Wave.BitDepth);																											//����� ������� �������
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//����� CR LF
	fprintf(FSet, "%s", WordCountOfSamples);																									//����� ��� BitsPerSample
	fprintf(FSet, "%d", wordSamplesValuePos);																									//����� ���������� �������
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//����� CR LF
	fclose(FSet);																																//��������� ����
	pringDebugMsg(87,0);																														//������������ � ������� � ����������� ������
}																																				//����� �������
