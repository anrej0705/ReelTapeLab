//Exheader - �ணࠬ�� �।�����祭� ��� �����祭�� ��������� �� WAV 䠩�� ��� ���쭥�襩 ࠡ��� � ��� - ����䨪�樥� � ������� � ���� 䠩�
//��ଠ� ��������� ������ ���� ᫥���騬 RIFFeeeeWAVEfmt kkkkgghhrrrryyyyooqqppppzzzz
// RIFF - ��⪠ �ଠ� 䠩��, DWORD 4 ����
// eeee - ࠧ��� �ᥣ� 䠩�� � ����� DWORD 4 ����
// WAVE - ������祭�� �� 䠩� ��㪮��� DWORD 4 ����
// fmt  - ������祭�� �� ����� ���� ��⠫� � 䠩�� DWORD 4 ����, ��᫥���� ᨬ��� ���⮡ࠦ����� - 0x20 WORD 2 ����
// kkkk - ��� �ଠ� ���(PCM) DWORD 4 ����
// gg - ����� 㪠��� �����, ���筮 ���(PCM) WORD 2 ����
// hh - ����� 㪠���� ������⢮ ������ WORD 2 ����
// rrrr - ���� ����⨧�樨 � ����� DWORD 4 ����
// yyyy - ᪮���� ��।�� ������ � ����� � ᥪ㭤� DWORD 4 ����
// oo - ������⢮ ���� ��� ����� �롮ન ������ �� ������ WORD 2 ����
// qq - ��㡨�� �롮ન � ���� WORD 2 ����
// data - ��⪠ ���������� �� ����� ���� ����� DWORD 4 ����
// zzzz - ࠧ��� 䠩�� ����� ࠧ��� ��������� DWORD 4 ����
//��᫥ �����祭�� ��������� �ணࠬ�� �������� 䠩� convertParams.ini � ���஬ ᮤ�ঠ���
// ����祭��� ⥣��� FSRC-FSND ��室��� ��� 䠩��
// ����祭��� ⥣��� FBOD-FBND ��� ���⥩��� wav ������
// ����祭��� ⥣��� FHDT-FHND ��� 䠩�� � ����������, ����ᠭ�� �⮩ �ணࠬ���
// ����祭��� ⥣��� FTGT-FTND ��� ����筮�� 䠩��
// 䫠� ���ﭨ� �������樨 - 0(�� �������஢��), 1(�������஢��)
// ����� ����⨧�樨 䠩�� � �����
// ������⢮ ������� � 䠩��
// ��㡨�� �롮ન
// ������⢮ �롮ப � ����� ������
//����� ����� �ணࠬ�� �஢���� ����稥 䠩�� convertParams.ini � �᫨
//�� ��室�� � ᮧ���� ����. ����� ��� 䠩�, ��� ���뢠�� ��� � � �����
//���� �஢���� 䫠� �������樨. �᫨ 0 - �ணࠬ�� �����蠥� ࠡ���
//�᫨ 1 � �ணࠬ�� �⠥� ��⠫�� �����, ������ ��� 䠩�� ���������
//� ᮧ���� 䠩� ᮣ��᭮ ����ᠭ���� ����� ��᫥ ⥣� FHDT. ����� �ணࠬ��
//�� ���⠭��� ������ �ନ��� ��������� ��������� � �����뢠�� ��� � 䠩�
#include<locale.h>																																//������⥪� ���������, �㦭� ��� ���᪮�� �몠 � ���᮫�
#include<stdbool.h>																																//������⥪� ��� ࠡ��� � �����묨 �᫠�, C99
#include<stdint.h>																																//������⥪� ��� ࠡ��� � ���⠭����묨 �᫠�� uint8_t, uint16_t, uint32_t
#include<stdio.h>																																//������⥪� ��� ࠡ��� � ���᮫��, �뢮� � ���᮫� � ���뢠��� � ���
#include<conio.h>																																//������⥪� ��� ࠡ��� � ������
#include<stdlib.h>																																//������⥪� ⨯�� ��६�����
#include<string.h>																																//������⥪� ᨬ������ ��६�����
#include<windows.h>
#include "debug.h"																																//������⥪� �⫠����� ᮮ�饭��
#define codePageInfo 				"������ ������� ⠡��� �ਫ������ OEM CP-866\n"
#define StartMsg					"\nv0.2.7 build 41\n"																						//����饭�� ��� �뢮�� � ���᮫�, 1 ����
#define StartMsgTwo					"������ �ணࠬ�� ���� ��������⮬ � ᠬ� �� ᥡ� �� ����� ��᫠\n\n"									//����饭�� ��� �뢮�� � ���᮫�, 2 ����
#define FileSizeMsg					"������ 䠩��, �����: %d ����\n"																			//����饭�� ��� �뢮�� ࠧ��� 䠩��
#define FileSizeWoutHeaderMsg		"������ 䠩�� ��� ��� ���������: %d ����\n"																//����饭�� ��� �뢮�� ࠧ��� 䠩�� ��� ���������
#define SampleRateMsg				"����� ����⨧�樨: %d ��\n"																			//����饭�� ��� �뢮�� ����� ����⨧�樨
#define ByteRateMsg					"������� ��।�� ������: %d ����/�\n"																		//����饭�� ��� �뢮�� ᪮��� ��।�� ������ � �����
#define BitDepthMsg					"��㡨�� �롮ન: %d ���\n"																					//����饭�� ��� �뢮�� ��㡨�� �롮ન
#define ChannelsMsg					"������⢮ �������: %d"																					//����饭�� ��� �뢮�� ������⢠ �������
#define BytesInSampleMsg			"������⢮ ���� � ����� �롮થ � ��� �������: %d ����\n"												//����饭�� ��� �뢮�� ������⢮ ���� � �롮થ � ��� ������� �ࠧ�
#define CodecTypeMsg				"��� ����஢���� ��㪠:"																					//����饭�� ��� �뢮�� ⨯� ����஢���� ��㪠 � 䠩��
const uint8_t wordFilenameShift=4;																												//���饭�� � ����� �� ᠬ��� ��ࠬ���
const uint8_t wordConvertShift=7;																												//���饭�� � ����� �� ᠬ��� ��ࠬ���
const uint8_t wordSampleRateShift=10;																											//���饭�� � ����� �� ᠬ��� ��ࠬ���
const uint8_t wordChannelsShift=8;																												//���饭�� � ����� �� ᠬ��� ��ࠬ���
const uint8_t wordBitsPerSampleShift=13;																										//���饭�� � ����� �� ᠬ��� ��ࠬ���
const uint8_t wordSamplesValueShift=16;																											//���饭�� � ����� �� ᠬ��� ��ࠬ���
const uint16_t pcmFormat=0x0001;
const uint32_t RIFFsignature=0x52494646;																										//��⪠ RIFF, ��ࠧ��
const uint32_t WAVEsignature=0x57415645;																										//��⪠ WAVE, ��ࠧ��
const uint32_t fmtSignature=0x666D7420;																											//��⪠ fmt , ��ࠧ��
const uint32_t dataSignature=0x64617461;																										//��⪠ data, ��ࠧ��
const uint32_t dataFormatLength=0x00000010;
char headerNameSuffix[11]="_header.dat";																										//���䨪� � ����� �८�ࠧ㥬��� 䠩��
char headerBodySuffix[9]="_body.dat";																											//���䨪� � ����� �८�ࠧ㥬��� 䠩��
char headerConvSuffix[9]="_conv.wav";																											//���䨪� � ����� �८�ࠧ㥬��� 䠩��
char fileMassive[256];																															//���ᨢ � ����� �⠥��� ᮤ�ন��� 䠩�� convertParams.ini
char fileNameRAW[128];																															//���ᨢ, � ���஬ �࠭���� ��� 䠩�� ������ ����
char fileNameSrc[64];																															//���ᨢ � ������ ��室���� 䠩��
char fileNameHdrDat[64];																														//���ᨢ � ������ ��������筮�� 䠩��
char fileNameBodDat[64];																														//���ᨢ � ������ ��������筮�� 䠩��
char fileNameTgtDat[64];																														//���ᨢ � ������ ��������筮�� 䠩��
char fileName[64];																																//���ᨢ � ������ 䠩��
char *wordFilenameSource="FSRC";																												//�������� ��� ��ࠬ��� ����� 䠩��
char *wordFilenameBody="FBOD";		   																											//�������� ��� ��ࠬ��� ����� 䠩��
char *wordFilename="FNAM";																														//�������� ��� ��ࠬ��� ����� 䠩��
char *wordFilenameTarget="FTGT";																												//�������� ��� ��ࠬ��� ����� 䠩��
char *wordSrcFilenameEnd=">FSND";																												//�������� ��� ��ࠬ��� ����� 䠩��
char *wordNameFilenameEnd=">FNND";																												//�������� ��� ��ࠬ��� ����� 䠩��
char *wordBodyFilenameEnd=">FBND";																												//�������� ��� ��ࠬ��� ����� 䠩��
char *wordTargFilenameEnd=">FTND";																												//�������� ��� ��ࠬ��� ����� 䠩��
char *wordConvert="Convert";																													//�������� ��� 䫠�� ���ﭨ� �������樨
char *wordSampleRate="SampleRate";																												//�������� ��� ��ࠬ��� ����� ����⨧�樨
char *wordChannels="Channels";																													//�������� ��� ��ࠬ��� ������⢠ �������
char *wordBitsPerSample="BitsPerSample";																										//�������� ��� ��ࠬ��� ��������饣� ������⢮ ��� � �롮થ
char *WordCountOfSamples="SamplesInChannel";																									//�������� ��� ��ࠬ��� ��������饣� ������⢮ �롮ப
char *cursorSymbol;																																//��ࠬ��� � ����� �㤥� ������� ������ ����� � ���ண� ��稭����� �᪮��� ᫮��
uint8_t fileLength;																																//���� ��६����� ��� �࠭���� ���ଠ樨 � ����� 䠩��
uint32_t cursorPosit;																															//������ ����� �� ��砫� �᫠ ��ࠬ���
uint32_t wordFsrcPos;																															//������ ⥣� FSRC
uint32_t wordFnamePos;																															//������ ⥣� FNAM
uint32_t wordConvertPos;																														//� ������ ������, �� ������ �㦭� ���⠢��� ����� ��� �⥭�� ��ࠬ��� FSetWasConverted 
uint32_t wordSampleRatePos;																														//� ������ ������, �� ������ �㦭� ���⠢��� ����� ��� �⥭�� ��ࠬ��� FSetSampleRate
uint32_t wordChannelsPos;																														//� ������ ������, �� ������ �㦭� ���⠢��� ����� ��� �⥭�� ��ࠬ��� FSetChannels
uint32_t wordBitsPerSamplePos;																													//� ������ ������, �� ������ �㦭� ���⠢��� ����� ��� �⥭�� ��ࠬ��� FSetBitDepth
uint32_t wordSamplesValuePos;																													//� �㤥� ������� ������⢮ �롮ப � 1 ������ 䠩��
bool DebugMode=1;																																//०�� �⫠���, 1 - ���, 0 - �몫
bool analyzeState;																																//���ﭨ� �㭪樨 �⥭��, 1 - �� ���, 0 - ���-� ��稫��� �訡��
bool convertState;																																//���ﭨ� �㭪樨 �८�ࠧ������ � ����� � ��������, 1 - �� ���, 0 - ���-� ��稫��� �訡��
bool cruzo;																																		//���ﭨ� ���뢠���� � 䠩�� convertParams.ini
bool ahsoka;																																	//���ﭨ� �㭪樨 �஢�ન �ࠢ��쭮�� ������ � �������, 1 - �� ���, 0 - ����� � ������� �� ᮢ������ � ��ࠧ栬�, �����稫��� 䠭⠧�� �� �����
bool gabella;																																	//�᫨ 1 - ���ଠ�� � ��������� �ᯥ譮 ����ᠭ�, �᫨ 0 - �ந��諮 ��-� ⠪�� �� �� ���� �������
bool Egor;																																		//���ﭨ� �㭪樨 �⥭�� �� 䠩�� convertParams.ini
bool doubledoor;																																//㪠��⥫� ���ﭨ� ����� � 䠩�, �᫨ 1 � �� ���, �᫨ 0 � 䠩� �� �� ����ᠭ
FILE* FSet;																																		//�����⥫� �� 䠩� � ��ࠬ��ࠬ� ���������
FILE* FRd;																																		//�����⥫� �� 䠩� � ���ண� �� �㤥� ������
FILE* FWr;																																		//�����⥫� �� 䠩� � ����� �㤥� ��� ������, ���� � ���� �� �ਬ����
const int HeaderSize=44;																														//��ࠬ��� ����� ��������� � �����(�� 0 ���� �� ��砫� ᠬ�� ������ WAVE), ��������� ����� �ᥣ�� ���� � �� �� �����
int headerAddrs[14]={0,4,8,12,16,20,22,24,28,32,34,36,40,44};																					//ᯨ᮪ ���ᮢ � ��������� � ������ �㦭� ���� ��ࠬ���� 䠩��
int headerWordSizeOf[13]={sizeof(uint32_t),sizeof(uint32_t),sizeof(uint32_t),sizeof(uint32_t),													//ᯨ᮪ ����� ᫮�, �⠥��� �� ���������(ᯨ᮪ �易� � headerAddrs � headerWordInvert)
						sizeof(uint32_t),sizeof(uint16_t),sizeof(uint16_t),sizeof(uint32_t),													//����� � ᫮��� 訧�
						sizeof(uint32_t),sizeof(uint16_t),sizeof(uint16_t),sizeof(uint32_t),
						sizeof(uint32_t)};																										//ᯨ᮪ ����� ᮤ�ন� ����� ������� ��ࠬ��� � �����
int headerWordInvert[13]={1,0,1,1,0,0,0,0,0,0,0,1,0};																							//ᯨ᮪ ��� �㭪樨, �������騩 ���冷� ���⮢ - � ���� ��� � ��砫�
int headerDebugPrintParameters[13]={0,0,0,0,0,1,1,0,0,1,1,0};																					//ᯨ᮪ ⨯�� ᮮ�饭�� �뢮�� ��� �㭪樨 �뢮�� �⫠����� ��ࠬ��஢
uint8_t FileHeader[44];																															//� ��९��뢠���� ���������
uint8_t ByteBuffer[4];																															//����� �࠭���� ��ࠬ��� ��������� �⮡� ����� ࠧ �� �������� � �᭮����� ���ᨢ�
uint8_t headerReader(void);																														//�㭪�� �⥭�� ��������� � ��������
uint8_t massiveSwap(bool swapState);																											//�㪭�� ��������� ���浪� ᫥������� ���⮢
uint8_t sByteConverter(uint32_t wordToConvert);																									//�㭪�� ��������� ࠧ�來���
uint8_t GetFileName(char* nameOfFile);																											//�㭪�� ����祭�� ����� 䠩��(�� ᠬ�� ���� ��� ��祣� �� ��������)
uint16_t dByteConverter(uint32_t wordToConvert);																								//�㭪�� ��������� ࠧ�來���(� 32 �� 16 ���)
uint32_t qByteConverter(uint32_t wordToConvert);																								//�㭪�� ��������� ࠧ�來���(� 32 �� 8 ���)
uint32_t byteConverter(int startOffset, int endOffset, int ByteLenght, bool invertState);														//�㭪�� ��� �८�ࠧ������ �㦭�� ��� ᮤ�ন����  ���ᨢ� � ���� ᫮�� � ࠧ��� �������
uint32_t structFiller(int structShift, uint32_t paramToWrite);																					//�㭪�� ����� � ��������
uint32_t writeBuffer(int startOffset, int endOffset, uint32_t paramToWrite, int wordSize, bool SwapByte);										//�㭪�� ����� ���������� �������� � ���ᨢ, �����⮢�� � ����� � 䠩�
void transformFileName(char *sourceFileName, uint8_t sourceLenght, char *suffixToAttach, uint8_t suffixLength, char *arrToStore);				//�㭪�� �����樨 ����� 䠩�� �� ����祭���� ��室����
void storeStructToFile();																														//�㭪�� ��� ����� ��ࠬ��஢ ��������� � �⤥��� 䠩� � ���� ��������
void checkStatus(uint8_t statusCode);																											//�㭪�� ��� �஢�ન ���ﭨ� ��室� �� ��㣨� �㭪権, ��� �����㦥��� �訡��
void structAnalyzer(void);																														//�㭪�� ��� �஢�ન �������� � �뢮�� �� ᮤ�ন����
void structModifier(void);																														//�㭪�� ��� ����䨪�樨 ��������
void clearByteBuffer(void);																														//���⪠ ���� ��᫥ ࠡ���
void clearHeaderBuffer(void);																													//���⪠ ���� ��������� ��᫥ ����樨 �⥭�� 䠩��
void writeDebugHeaderBuffer(void);																												//������ ���� ᮤ�ন��� ���ண� �뢮����� � �⫠����� 楫��
void BufferReader(void);																														//�㭪��-����窠 ��� �⫠����� 楫��
void printHelpMsg(void);																														//�㭪��-�ࠢ�� � ��砥 ���⮣� �맮�� ��� �맮�� �� �������� -h.-H,-help,-HELP
void generateHead(void);
int WriteSettingsFile(void);																													//�㭪�� �����뢠��� ��ࠬ���� �८�ࠧ������
int ReadSettingsFile(void);																														//�㭪�� ���뢠��� ��ࠬ���� �८�ࠧ������
struct WaveHeader																																//�������, � ������ �㤥� ������� ���ଠ�� � ��������� 䠩��
{																																				//��砫� �������� ���������
	uint32_t RiffSign;																															//��⪠ RIFF
	uint32_t chunkSizeBytes;																													//ࠧ��� 䠩�� � ����������
	uint32_t WaveSign;																															//��⪠ WAVE
	uint32_t fmtSign;																															//��⪠ fmt
	uint32_t DataFormatLenght;																													//����� �ଠ� ������
	uint16_t compressionCode;																													//��� ᦠ��
	uint16_t soundChannels;																														//������⢮ �������
	uint32_t sampleRate;																														//���� �롮ப
	uint32_t byteRate;																															//᪮���� ��।�� ������, ����
	uint16_t BytesInSample;																														//������⢮ ���� � ����� �롮થ � ��� �������
	uint16_t BitDepth;																															//��㡨�� ����⨧�樨
	uint32_t dataSign;																															//��⪠ data
	uint32_t chunkSizeWoutHeader;																												//ࠧ��� 䠩�� ��� ���������
};																																				//����� �������� ���������
struct FilSettings																																//�������, � ������ ������� ��ࠬ���� �� 䠩�� convertParams.ini
{																																				//��砫� ��������
	int FSetWasConverted;																														//䫠� ����� �����뢠�� - �� �� �������஢�� 䠩� �⮡ ᤥ���� �뢮� - ����� ��������� ��� ���
	int FSetBitDepth;																															//��㡨�� ����⨧�樨
	int FSetChannels;																															//������⢮ �������
	long FSetSampleRate;																														//���� �롮ப
	uint32_t FSetSamplesValue;																													//������⢮ �롮ப
};																																				//����� ��������
struct FilSettings FilSet;																														//��饭�� ����� ��������
struct WaveHeader Wave;																															//��饭�� ����� ��������
int main(int argc, char *argv[])																												//���ᠭ�� main � ��⮤� ��।�� ��㬥�⮢ �� ��������� ��ப�
{																																				//��砫� ⥫� main
	unsigned int codePageNum;
	bool setOutCodePageStatus;
	bool setInCodePageStatus;
	memset(fileMassive,0x00,sizeof(fileMassive));																								//��⨬ ���ᨢ fileMassive
	memset(fileNameRAW,0x00,sizeof(fileNameRAW));																								//��⨬ ���ᨢ fileNameRAWs
	memset(fileNameSrc,0x00,sizeof(fileNameSrc));																								//��⨬ ���ᨢ fileNameSrc
	memset(fileName,0x00,sizeof(fileName));																										//��⨬ ���ᨢ fileName
	memset(FileHeader,0x00,sizeof(FileHeader));																									//��⨬ ���ᨢ FileHeader
	memset(ByteBuffer,0x00,sizeof(ByteBuffer));																									//��⨬ ���ᨢ ByteBuffer
	SetConsoleTitle("WAV head converter v0.2.7 build 41 by Anrej0705");
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
	if(DebugMode==1)																															//�஢�ઠ, ����祭 �� ०�� �⫠���
	{pringDebugMsg(36,0);}																														//�᫨ ����祭 � �뢮� ᮮ�饭��
	pringDebugMsg(33,0);																														//㢥�������� � ��砫� ࠡ��� �ண�
	pringDebugMsg(85,argc);																														//ᮮ�饭�� � ������⢥ ��㬥�⮢, ����祭��� �� ��������� ��ப�
	if(argc<=1)
	{
		pringDebugMsg(101,0);
		printf(" �� 㪠���� ��㬥���! �맮� �ࠢ�� -help\n");
		return 0;
	}
	for(uint8_t i=0;i<argc;i++)
	{
		printf("argv %d %s\n",i,argv[i]);
	}
	for(uint8_t i=0;i<64;i++)
	{
		if(!(strcmp(argv[i], "-h")&&strcmp(argv[1], "-H")&&strcmp(argv[1], "-HELP")&&strcmp(argv[1], "-help")))
		{
			printHelpMsg();
		}
		if(!(strcmp(argv[i], "-makehead")))
		{
			pringDebugMsg(101,0);
			printf(" ��㬥�� -makehead ������\n");
			ReadSettingsFile();
			cursorSymbol=strstr(fileMassive, wordConvert);
			structModifier();
			generateHead();
			exit(1);
		}
		else
		{
			pringDebugMsg(101,0);
			printf(" ��������� ��㬥�� %s\n",argv);
			exit(1);
		}
	}
	if(argc<2)
	{
		printf("�� 㪠���� ��� 䠩��\n");
		printf("�맮� �ࠢ�� -h, -H, -help, -HELP\n\n");
		pringDebugMsg(84,0);
	}
	if(argc>4)
	{
		printf("���誮� ����� ��㬥�⮢\n");
		pringDebugMsg(84,0);
	}
	printf(StartMsg);
	printf(StartMsgTwo);
	if(!(strcmp(argv[1], "-h")&&strcmp(argv[1], "-H")&&strcmp(argv[1], "-HELP")&&strcmp(argv[1], "-help")))
	{
		printHelpMsg();
	}
	printf("��ன ��㬥�� ��������, ᮧ������ 䠩� � ������ �� 㬮�砭��\n\n");
	FRd=fopen(argv[1], "rb");
	fileLength=GetFileName(argv[1]);
	transformFileName(fileName,fileLength,headerNameSuffix,sizeof(headerNameSuffix),fileNameHdrDat);											//������㥬 ��� 䠩�� � ���������� �� ��室����
	transformFileName(fileName,fileLength,headerBodySuffix,sizeof(headerBodySuffix),fileNameBodDat);											//������㥬 ��� 䠩�� � ⥫�� �� ��室����
	transformFileName(fileName,fileLength,headerConvSuffix,sizeof(headerConvSuffix),fileNameTgtDat);											//������㥬 ��� 䠩�� � ⥫�� �� ��室����
	if(!FRd)																																	//�஢�ઠ ����⢮����� 䠩�� ��(FRd)=0?
	{																																			//⮣��...
		pringDebugMsg(89,0);																													//������
		pringDebugMsg(91,0);																													//ᮮ�饭�� �� �������⢨� 䠩��
		exit(1);																																//��室 �� �ணࠬ�� � ����� 1(䠩� �� ������)
	}																																			//����� ⥫� �஢�ન
	fseek(FRd, 0, SEEK_SET);																													//��⠭���� ����� �� ����(�ᯥ譮��� ������ ����樨 ���� �� �஢������ �����)
	pringDebugMsg(26,0);																														//���ࠥ� �⫠��筮� ᮮ�饭�� � ��砫� �⥭�� ���������
	fread(FileHeader, 1, HeaderSize, FRd);																										//�믮��塞 �⥭�� � ����� FileHeader, �⠥� ���� 44 ����(㪠���� � HeaderSize)
	writeDebugHeaderBuffer();																													//⮫쪮 ��� ०��� �⫠���, ������ � �⤥��� ���� �� ���ண� �㤥� �뢮������ �� �࠭ �⫠���
	pringDebugMsg(25,0);																														//�뢮� ᮤ�ন���� ���� FileHeader
	pringDebugMsg(29,0);																														//�뢮� ᮮ�饭�� � ⮬, �� ���� �⥭�� ᮤ�ন���� �⮣� ����
	headerReader();																																//�맮� �㭪樨 �⥭�� ���������
	fclose(FRd);																																//�����⨥ 䠩�� ��� �⥭��
	checkStatus(1);																																//�஢�ઠ ���� ��室� �㭪樨 �⥭�� ���������
	structAnalyzer();																															//�맮� �㭪樨 �஢�ન �������� �� �ࠢ��쭮���
	ReadSettingsFile();																															//�맮� �㭪樨 �⥭�� �� 䠩�� ��ࠬ��஢
	WriteSettingsFile();																														//�맮� �㭪樨 ����� ��ࠬ��஢ � 䠩�
	pringDebugMsg(82,0);																														//�뢮� ᮮ�饭�� �����襭�� ࠡ��� �ணࠬ��
	//pringDebugMsg(38,0);					//������� ��� �������������																			//�ணࠬ�� ᮮ�頥� �� ⮬ �� �� �㤥� ����� ������ ������ Enter
	//getchar();																																//��祣� �� ������, ����� ������ ������ Enter
}																																				//����� ⥫� main
void generateHead(void)
{
	pringDebugMsg(101,0);
	printf(" �������� ��������...\n");
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
		printf(" �ᯥ�\n");
	}
	else
	{
		printf(" �� 㤠���� ᮧ���� 䠩� %s\n",fileNameHdrDat);
		exit(0);
	}
	fseek(FWr, 0, SEEK_SET);
	fwrite(FileHeader, sizeof(uint8_t), sizeof(FileHeader), FWr);
	fclose(FWr);
}
inline void printHelpMsg(void)																													//�㭪�� �뢮�� �ࠢ�筮� ���ଠ樨 � ���᮫�
{																																				//��砫� ⥫�
	printf(StartMsg);																															//�뢮��� ����� �ணࠬ��
	printf("�ᯮ�짮�����: Exheader.exe source_file output_file(�롮�筮)\n\n");																//�ࠢ��, ��砫�
	printf("- �� ������⢨� ��ண� ��㬥��, 䠩� � ���������� ᮧ������ �\n  ��४�ਨ ����᪠ Exheader.exe\n");							//�ࠢ��, �த�������
	printf("- ���ਬ��, �맮� Exheader.exe C:\\foreign8.wav ᮧ���� �� �����\n  �맮�� ���������� 䠩� foreign8_header.dat\n");				//�ࠢ��, �த�������
	printf("  � �맮� Exheader C:\\foreign8.wav C:\\aaa\\foreign8dat.wav ᮧ���� �� ��� C:\\aaa 䠩� foreign8dat.wav.dat\n\n");				//�ࠢ��, �த�������
	printf("- ������ 䠩� �ᥣ�� �㤥� � ���७��� .dat � ᮤ�ঠ�� � ᥡ�\n  ��ନ஢���� �� convertParams.ini ���������\n");			//�ࠢ��, �த�������
	exit(1);																																	//��室 � ����� 1
}																																				//����� ⥫� �ࠢ�筮� �㭪樨
inline void writeDebugHeaderBuffer(void)																										//�-��� ����஢���� ��������� � �⤥��� ���� ��� �뢮�� �⫠����� ᮮ�饭��
{																																				//��砫� ⥫� �-�樨
	for(int j=0;j<43;j++)																														//��砫� 横�� ����஢���� ���ᨢ��
	{																																			//��砫� ⥫� 横��
		FileHeaderMSG[j]=FileHeader[j];																											//��ᨬ���쭮� ����஢���� � ��࠭����� ���� ᨬ���� �⭮�⥫쭮 ��砫� ���ᨢ��
	}																																			//����� ⥫� 横��
}																																				//����� ⥫� �㭪樨
uint8_t GetFileName(char* nameOfFile) 																											//�㭪�� ����祭�� ����� 䠩�� �� ���
{																																				//��砫� ⥫�
	uint8_t symbolCountInFileName;																												//��६����� �࠭��� ����� ����� 䠩��, ������ ���७��
	strcpy(fileNameRAW,nameOfFile);																												//�㡫�஢���� ��ப� � ���ᨢ
	uint8_t nameLenght = strlen(nameOfFile);																									//������ ������⢠ �������� ᨬ�����
	char *lastSymbolEntry = strrchr(fileNameRAW, 92);																							//��宦����� ��᫥����� �宦����� ᨬ���� "\"
	uint8_t entryPos = lastSymbolEntry-fileNameRAW+1;																							//㪠��⥫� �� ������ ��᫥����� �宦����� ᨬ����
	if(lastSymbolEntry==NULL)																													//�᫨ �㭪�� strrchr �����頥� NULL...
	{																																			//...� ��稭��� ��ࠡ��� ����� ��� �⤥����� ����� ��� � 䠩��
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		pringDebugMsg(92,0);																													//��襬 ᮮ�饭�� � ������ NULL �㭪樥� strrchr
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		printf("����� ����� 䠩�� = %d\n", nameLenght);																							//��襬 ᮮ�饭�� � ����� ����� 䠩�� ������ ���� �� ����
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		printf("��� ���뢠����� 䠩��: ");																										//��襬 ��� ���뢠����� 䠩��
		for(int i=0;i<nameLenght;i++)																											//��砫� 横�� �뢮�� ����� 䠩��
		{																																		//��砫� ⥫� 横��
			printf("%c",fileNameRAW[i]);																										//��ᨬ����� �뢮� ����� 䠩�� �� ���ᨢ�
		}																																		//����� ⥫� 横��
		printf("\n");																															//���⠬ ��७�� ���⪨
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		pringDebugMsg(93, entryPos);																											//�뢮��� ������ ��᫥����� ���������� �㦭��� ᨬ����
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		printf("��᫥���� �宦����� ᨬ����: %s\n", lastSymbolEntry);																			//��襬 ��᫥���� �宦����� ᨬ����
		symbolCountInFileName = strlen(fileNameRAW);																							//������뢠�� ����� ����� 䠩��, � ᨬ�����
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		pringDebugMsg(94,symbolCountInFileName);																								//��襬 ����祭��� � १���� ������ �᫮
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		printf("����祭��� ��� 䠩��: ");																										//�뢮��� ����祭��� ��� 䠩��
		for(int i=0;i<symbolCountInFileName;i++)																								//��砫� 横�� �뢮�� �����
		{																																		//��砫� ⥫� 横��
			fileNameSrc[i]=fileNameRAW[i];																										//�㡫�஢���� �ਣ����쭮�� ����� 䠩�� � ���ᨢ
			fileName[i]=fileNameRAW[i];																											//��७�ᨬ ��� � ��㣮� ���ᨢ ��ᨬ���쭮
			printf("%c",fileName[i]);																											//� ������ ��ᨬ���쭮 �뢮��� ��७�ᨬ�� ��� � ���᮫�
		}																																		//����� ⥫� 横��
		printf("\n");																															//��७�ᨬ �����
		return symbolCountInFileName;																											//�����頥� ����� ����� 䠩��
	}																																			//����� ⥫�(��⨭�)
	else																																		//���� �⤥�塞 ���� �� 䠩�� �� ����� 䠩��
	{																																			//��砫� ⥫�
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		printf("����� �����, ������ ���� � 䠩�� = %d\n", nameLenght);																			//��襬 ����� ����� 䠩��
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		printf("��� ���뢠����� 䠩��: ");																										//��襬 ��� ���뢠����� 䠩��
		for(int i=0;i<nameLenght;i++)																											//��砫� 横�� �뢮�� ����� 䠩��
		{																																		//��砫� ⥫� 横��
			printf("%c",fileNameRAW[i]);																										//��ᨬ����� �뢮� ����� 䠩��
		}																																		//����� ⥫� 横��
		printf("\n");																															//��७�� ���⪨
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		pringDebugMsg(93, entryPos);																											//��襬 ������ ᨬ����, ����� �饬 � ��ப�
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		printf("��᫥���� �宦����� ᨬ����: %s\n", lastSymbolEntry);																			//��ப� � ⮩ ����樨 ��� �� ������ ᨬ����
		symbolCountInFileName = nameLenght-entryPos;																							//��⠥� ������⢮ ᨬ����� � ����� 䠩��
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		pringDebugMsg(94,symbolCountInFileName);																								//��襬 ����祭�� � १���� ���᫥��� �᫮
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		printf("����祭��� ��� 䠩��: ");																										//��襬 ����祭��� ��� 䠩��(㦥 ᠬ� ���)
		for(int i=0;i<symbolCountInFileName;i++)																								//��稭��� �뢮� ����� 䠩��
		{																																		//��砫� ⥫� 横��
			fileNameSrc[i]=fileNameRAW[i+entryPos];																								//�㡫�஢���� �ਣ����쭮�� ����� 䠩�� � ���ᨢ
			fileName[i]=fileNameRAW[i+entryPos];																								//��ᨬ���쭮 �뢮��� ��� 䠩�� � ᬥ饭��� � ��砫� �����
			printf("%c",fileName[i]);																											//� �ࠧ� �� ���⠥�, ⠪�� �� ᨬ����
		}																																		//����� ⥫�
		printf("\n");																															//��७�� ���⪨
		return symbolCountInFileName;																											//�����頥� ����� ����� 䠩�� � ���� �맮�� �㭪樨
	}																																			//����� ⥫�(����)
}																																				//����� ⥫� �㭪樨
void transformFileName(char *sourceFileName, uint8_t sourceLenght, char *suffixToAttach, uint8_t suffixLength, char *arrToStore)				//�㭪�� �����஢���� ����� 䠩��
{																																				//��砫� ⥫� �㭪樨
	char tempMas[64];																															//���樠�����㥬 �६���� ����
	memset(tempMas,0x00,sizeof(tempMas));																										//� ��⨬ ���
	uint8_t filenameWithoutExtension=sourceLenght-4;																							//���樠������ ��६����� ����� ����� 䠩�� ��� ���७��
	uint8_t generatedFileNameWithSuffix;																										//���樠������ ��६����� ����� ᣥ���஢������ ����� 䠩��
	pringDebugMsg(95,0);																														//��襬 � ���᮫�
	pringDebugMsg(96,0);																														//��襬 ������� � ��砫� ࠡ��� �㭪樨
	for(int i=0;i<filenameWithoutExtension+suffixLength;i++)																					//��砫� 横�� �����樨 ����� 䠩��
	{																																			//��砫� ⥫� 横��
		if(i<filenameWithoutExtension)																											//��砫� ��७�� ����� 䠩��
		{																																		//��砫� ⥫�
			tempMas[i]=sourceFileName[i];																										//��ᨬ����� ��७�� ����� 䠩��
		}																																		//����� ⥫�
		if(i>=filenameWithoutExtension)																											//��砫� ����� ���䨪� � ����� 䠩��
		{																																		//��砫� ⥫�
			tempMas[i]=suffixToAttach[i-filenameWithoutExtension];																				//��ᨬ���쭠� ������ ���䨪� � ����� 䠩��
		}																																		//����� ⥫�
	}																																			//����� ⥫� 横��
	generatedFileNameWithSuffix = filenameWithoutExtension+suffixLength;																		//�ନ஢���� ����� ����� 䠩�� ����� � ���䨪ᮬ
	if(strlen(tempMas)==generatedFileNameWithSuffix)																							//�ࠢ������ ����祭��� ��� � ������ ����� 䠩��
	{																																			//��砫� ⥫� 横��
		pringDebugMsg(95,0);																													//��襬 � ���᮫�
		pringDebugMsg(98,0);																													//��襬 �஢���
	}																																			//����� ⥫� 横��
	else																																		//� ��砥 �᫨ ����� �� ᮢ������
	{																																			//� ��襬 � ���᮫� ᮮ�饭�� �� �訡��
		pringDebugMsg(15,0);																													//� ��室�� �� �ணࠬ��
	}																																			//����� ⥫� 横��
	pringDebugMsg(95,0);																														//��襬 � ���᮫�
	printf("����祭��� ��� 䠩��: ");																											//��襬 ᣥ���஢����� ��� 䠩��
	for(int i=0;i<generatedFileNameWithSuffix;i++)																								//��砫� 横�� ��७�� ����� 䠩�� �� �६������ ���ᨢ�
	{																																			//��砫� ⥫� 横��
		fileName[i]=tempMas[i];																													//��ᨬ����� ��७�� ����� 䠩��
		arrToStore[i]=tempMas[i];																												//�㡫��㥬 � ���ᨢ �� 㪠��⥫� ��� ����� �� ��砩���� ��������� � 室� ࠡ��� �ணࠬ�� �.� �ண� ���-� �������� ������⭮ ���
		printf("%c",arrToStore[i]);																												//� �ࠧ� �� �뢮� � ���᮫�
	}																																			//����� ⥫� 横��
	printf("\n");																																//��७�� ���⪨
	pringDebugMsg(95,0);																														//��襬 � ���᮫�
	pringDebugMsg(94,generatedFileNameWithSuffix);																								//��襬 ����� ᣥ���஢������ �����
	pringDebugMsg(95,0);																														//��襬 � ���᮫�
	pringDebugMsg(97,0);																														//㢥����塞 �� ��� 䠩�� ��࠭��� � ������쭮� ���ᨢ�
}																																				//����� ⥫� �㭪樨
uint8_t headerReader(void)																														//�����쭠� �㭪�� 
{																																				//��砫� ⥫� �-�樨
	uint32_t LongByteWord;																														//���塞 �६����� 4 ������ ��६�����
	int hA=0,hB=0,hC=0,hD=0;																													//����뫨
	struct WaveHeader Wave;																														//������� �������� �������� � �⮩ �㭪樨(��祬?)
	for(int i=0;i<13;i++)																														//��砫� 横�� ����� ��������� � ��������
	{																																			//��砫� ⥫� 横��
		pringDebugMsg(8,0);																														//���⠥� ࠧ����⥫� � ���᮫�, ��� �����
		pringDebugMsg(7, hB);																													//�����뢠�� �⥯��� ������������ ��������
		LongByteWord=byteConverter(headerAddrs[hA], headerAddrs[hA+1], headerWordSizeOf[hC], headerWordInvert[hD]);								//��뢠�� �㭪�� �������樨 �ଠ� ������, �� ��ࠬ���� ��� �⮣� ��६ �� ���ᨢ�� � ��砫� 䠩��
		checkStatus(0);																															//�஢��塞 䫠��-ᨣ��������� �訡��
		pringDebugMsg(headerDebugPrintParameters[hB], LongByteWord);																			//��襬 �⫠��筮� ᮮ�饭��, � ���஬ 㪠�뢠���� �������� ��ࠬ��� ���������
		structFiller(hB, LongByteWord);																											//��襬 � �������� ᪮����祭��� ���祭��
		clearByteBuffer();																														//��⪨� ���� ��᫥ ����砭�� ࠡ��� � ���
		LongByteWord=0;																															//��⨬ ��६����� � ������ �⠥� ᮤ�ন��� ���ᨢ�(��祬? ��६����� 㭨�⮦����� ��᫥ ��室� �� �㭪樨)
		hA++;																																	//������
		hB++;																																	//������
		hC++;																																	//������
		hD++;																																	//������
	}																																			//����� ⥫� 横��
	pringDebugMsg(8,0);																															//��襬 ࠧ����⥫� � ���᮫�, ����� ⠪� ��� �����
	analyzeState=1;																																//�����뢠�� 䫠� ���ﭨ� �㭪樨(������-����窠 �⮡ �ண� ࠡ�⠫�)
	return analyzeState;																														//�모�뢠��, ⠪ �� ��直� ��砩, �� �� ���祭��
}																																				//����� ⥫� �㭪樨
uint32_t byteConverter(int startOffset, int endOffset, int ByteLenght, bool invertState)														//�㭪樨 ��४��뢠��� �ଠ⮢ ������ �� 32 � 8,16,32 ࠧ�來�
{																																				//��砫� ⥫� �㭪樨
	uint32_t quadByte;																															//���塞 4 ���⮢�� �६����� ��६�����
	uint16_t doubleByte;																														//���塞 ���塠�⮢�� �६����� ��६�����
	uint8_t singleByte;																															//���塞 �������⮢�� �६����� ��६�����
	int i=0;																																	//���塞 㪠��⥫� ���� ���ᨢ��
	int startMarker=startOffset;																												//���塞 � ��ࠢ������ ����祭���� ��ࠬ���� 㪠��⥫� ��砫� ���� ���뢠���
	int endMarker=endOffset;																													//���塞 � ��ࠢ������ ����祭���� ��ࠬ���� 㪠������ ���� ���� ���뢠���
	while(startMarker<endMarker)																												//��砫� 横�� ����� �६������ ����
	{																																			//��砫� ⥫� 横��
		ByteBuffer[i]=FileHeader[startMarker];																									//�����⮢� ��९��뢠�� � ���� ᮤ�ন���, ��室�饥�� �� 㪠������ ����
		pringDebugMsg(32,ByteBuffer[i]);																										//ᮮ�頥� � ���᮫� � �த��뢠���� ࠡ��
		i++;																																	//���६����㥬 ���� ����
		startMarker++;																															//���६����㥬 ���� ���ᨢ� � ���ண� ���� ������
	}																																			//����� ⥫� 横��
	i=0;																																		//��⨬ ��६�����(��祬? ��� ����� �� �㦭�)
	switch(ByteLenght)																															//��稭��� ����� �����⮢�� ��ࠬ��� � �뤠�
	{																																			//��砫� ⥫� switch
		case 0:																																	//� ��砥 �᫨ ��ࠬ��� �� �������
			pringDebugMsg(30,0);																												//��襬 � ���᮫� 㢥�������� �� �⮬
			convertState=0;																														//��襬 䫠� �訡��
			break;																																//��室�� �� 横��
		case 1:																																	//� ��砥 �᫨ ��ࠬ��� 1 �����
			pringDebugMsg(31,0);																												//��襬 ᮮ�饭�� � ���᮫� �� �⮬
			singleByte=FileHeader[startMarker];																									//�����뢠�� ��ࠬ��� � ��६����� ��� �뤠�
			convertState=1;																														//���⠢�塞 䫠� �ᯥ譮� ����樨
			return singleByte;																													//�����頥� ��६����� �� ���� �맮�� �㭪樨
			break;																																//��室�� �� 横��
		case 2:																																	//� ��砥 �᫨ ��६����� 2 ���⭠�
			massiveSwap(invertState);																											//��뢠�� �㭪�� ��ॢ���뢠��� ��६����� � ��।��� �� ��ࠬ��� � ���ଠ樥� � ����室����� ��ॢ���
			doubleByte=ByteBuffer[0];																											//��襬 ����訩 ����
			doubleByte=doubleByte|ByteBuffer[1]<<8;																								//��襬 ���訩 ����
			pringDebugMsg(28,doubleByte);																										//�����뢠�� � ���᮫� ��� ��६�����
			convertState=1;																														//���⠢�塞 䫠� �ᯥ譮� ����樨
			return doubleByte;																													//�����頥� ��६����� �� ���� �맮�� �㭪樨
			break;																																//��室�� �� 横��
		case 4:																																	//� ��砥 �᫨ ��६����� 4 ���⭠�
			massiveSwap(invertState);																											//��뢠�� �㭪�� ��ॢ��稢���� ��६����� � ��।��� �� ��ࠬ��� � ���ଠ樥� � ����室����� ��ॢ���
			quadByte=ByteBuffer[0];																												//��襬 ����訩 ����
			quadByte=quadByte|ByteBuffer[1]<<8;																									//��襬 ���� ������
			quadByte=quadByte|ByteBuffer[2]<<16;																								//��襬 ���� ������
			quadByte=quadByte|ByteBuffer[3]<<24;																								//��襬 ���訩 ����
			pringDebugMsg(27,quadByte);																											//� ���᮫� ����ਬ �� �⮬ � �����뢠�� १����
			convertState=1;																														//���⠢�塞 䫠� �ᯥ譮� ����樨
			return quadByte;																													//�����頥� ��६����� �� ���� �맮��
			break;																																//��室�� �� 横��
	}																																			//����� ⥫� 横��
	return convertState;																														//�����頥� 䫠� ���ﭨ�
}																																				//����� �㭪樨
uint8_t massiveSwap(bool swapState)																												//����砫쭮 �⥭�� �������� �������, ���⮬� ��� "����⠭���� ���⮢ �� �ॡ����" ���ࠧ㬥������
{																																				//������ �� ��ଠ��� ���冷�, � ���� �� �������
	uint32_t tempByte;																															//���塞 �६����� ��६�����
	uint8_t tempBuffer[4];																														//���塞 �६���� ���� ��� �⮣�
	memset(tempBuffer,0x00,sizeof(tempBuffer));																									//� �ࠧ� ��⨬ ��� �� ����⭮�� ����
	if(swapState==1)																															//��ॢ��稢��� ������?
	{																																			//�᫨ ������, �...
		pringDebugMsg(34,0);																													//...ᮮ�頥� �� �⮬ � ���᮫�
		tempBuffer[0]=ByteBuffer[3];																											//��稭��� ��ॢ��稢���
		tempBuffer[1]=ByteBuffer[2];																											//��襬 ������ ����樨 ᮧ������� ���� � ��砫�...
		tempBuffer[2]=ByteBuffer[1];																											//...� ��饣� �६������ ���� � ����
		tempBuffer[3]=ByteBuffer[0];																											//...��⥬...
		ByteBuffer[0]=tempBuffer[0];																											//...��४��뢠�� �� �� ����� ������ ��� ���� � ��砫�
		ByteBuffer[1]=tempBuffer[1];																											//...
		ByteBuffer[2]=tempBuffer[2];																											//...
		ByteBuffer[3]=tempBuffer[3];																											//...
	}																																			//����� ��ॢ���
	else																																		//�᫨ �� ������, �...
	{pringDebugMsg(35,0);}																														//...��襬 � ���᮫� �� �� ������ � ��室�� �� �㭪樨
}																																				//����� ⥫� �㭪樨
void checkStatus(uint8_t statusCode)																											//�����쭠� �㭪��
{																																				//��砫� ⥫� �㭪樨
	pringDebugMsg(74, statusCode);																												//ᮮ�頥� �� �⮬ � ���᮫� � �����뢠�� ��� �஢�ન
	switch(statusCode)																															//��砫� �஢�ન
	{																																			//��砫� ⥫� switch
		case 0:																																	//� ��砥 �᫨ 㪠��� ��� 0(���ﭨ� �������樨)
			if(convertState!=0)																													//�஢�ઠ ������ 䫠�� �訡�� �������樨
			{pringDebugMsg(10,0);}																												//� ��� �ᯥ� ��襬 � ���᮫� �� �⮬
			else																																//����...
			{pringDebugMsg(20,convertState);pringDebugMsg(15,0);}																				//...�����뢠�� ᮤ�ন��� 䫠��
			pringDebugMsg(20,convertState);																										//� ��室�� �ணࠬ�� � ����� 0(�訡��)
			break;																																//��室 �� 横��
		case 1:																																	//� ��砥 �᫨ 㪠��� ��� 1(���ﭨ� �������樨)
			if(analyzeState!=0)																													//�஢��塞 ���ﭨ� ���������� ��������
			{pringDebugMsg(11,0);}																												//� ��砥 �ᯥ� ��襬 �� �⮬
			else																																//����...
			{pringDebugMsg(21,analyzeState);pringDebugMsg(16,0);}																				//...�����뢠�� ᮤ�ন��� 䫠��
			pringDebugMsg(21,analyzeState);																										//� ᮮ�頥� �� �訡��
			break;																																//��室�� �� 横��
		case 2:																																	//� ��砥 �᫨ 㪠��� ��� 2(���ﭨ� �������� ���������)
			if(ahsoka!=0)																														//�஢��塞 ���ﭨ� 䫠��
			{pringDebugMsg(12,0);}																												//� ��砥 �᫨ ������� ��������� �ࠢ��쭠�, ����ਬ �� �⮬ � ���᮫�
			else																																//����...
			{pringDebugMsg(22,ahsoka);pringDebugMsg(17,0);}																						//��襬 � ���᮫� 㢥�������� � ��⮩ �������
			pringDebugMsg(22,ahsoka);																											//� �����뢠�� ���ﭨ� 䫠��
			break;																																//��室�� �� �㭪樨
		case 3:																																	//� ��砥 �᫨ 㪠��� ��� 3(����䨪��� ���������)
			if(gabella!=0)																														//�᫨ ����䨪��� �뫠 �ᯥ譠
			{pringDebugMsg(13,0);}																												//��襬 �� �⮬ � ���᮫�
			else																																//����...
			{pringDebugMsg(23,gabella);pringDebugMsg(18,0);}																					//...��襬 � ���᮫� �訡�� ����樨 ����䨪�樨 ���������
			pringDebugMsg(23,gabella);																											//�����뢠�� ᮤ�ন��� 䫠��
			break;																																//��室�� �� �㭪樨
		case 4:																																	//� ��砥 �᫨ ����祭 ��� 4
			if(doubledoor!=0)																													//�஢��塞 �ᯥ譮��� ����� ���������
			{pringDebugMsg(14,0);}																												//��襬 �� �⮬ � ���᮫�
			else																																//����...
			{pringDebugMsg(24,doubledoor);pringDebugMsg(19,0);}																					//...��襬 �� �訡�� � ���᮫�
			pringDebugMsg(24,doubledoor);																										//� �����뢠�� ᮤ�ন��� 䫠��
			break;																																//��室�� �� �㭪樨
		case 5:																																	//� ��砥 �᫨ ����祭 ��� 5
			if(Egor!=0)																															//�஢��塞 �ᯥ� ���⠭��� ��ࠬ��஢
			{pringDebugMsg(64,0);}																												//� ��砥 �᫨ ���⠭� �ᯥ譮, ��襬 � ���᮫�
			else																																//����...
			{pringDebugMsg(66,Egor);pringDebugMsg(65,0);}																						//��襬 ᮮ�饭�� �� �訡��
			pringDebugMsg(66,Egor);																												//� �����뢠�� ���ﭨ� 䫠��
			break;																																//��室�� �� �㭪樨
		case 6:																																	//� ��砥 �᫨ ����祭 ��� 6
			if(cruzo!=0)																														//�஢��塞 �ᯥ� ।���஢���� ��������
			{pringDebugMsg(72,0);}																												//�᫨ �� ��� � ��襬 � ���᮫�
			else																																//����...
			{pringDebugMsg(71,cruzo);pringDebugMsg(73,0);}																						//...㢥����塞 � ���᮫� �� �訡��
			pringDebugMsg(71,cruzo);																											//� �����뢠�� ���ﭨ� ��६�����
			break;																																//��室�� �� �㭪樨
	}																																			//����� ⥫� 横��
}																																				//����� ⥫� �㭪樨
uint32_t structFiller(int structShift, uint32_t paramToWrite)																					//���筠� �஢�ઠ �ࠢ��쭮�� ��������, ⮫쪮 �� ��⪠�
{																																				//��砫� �㭪樨
	uint32_t qWordToConvert;																													//ᮧ���� �६����� 2 ������ ��६�����
	uint16_t dWordToConvert;																													//ᮧ���� �६����� 4 ������ ��६�����
	switch(structShift)																															//��砫� 横�� switch
	{																																			//��砫� ⥫� 横��
		case 0:																																	//� ��砥 �᫨ ��࠭� ������ ��⪨ RIFF
			Wave.RiffSign=qByteConverter(paramToWrite);																							//����砥� ���� � ������� �������樨 �� ��室���� ���ᨢ�
			pringDebugMsg(3,0);																													//��襬 � ���᮫� 㢥�������� � ����� � ��������
			if(Wave.RiffSign==RIFFsignature)																									//�ࠢ������ � �⠫����
			{pringDebugMsg(41, structShift);}																									//� ��砥 �᫨ ����祭��� ��⪠ ᮢ������ � �⠫���� ��襬 �� �⮬ ���᮫�
			else																																//����...
			{pringDebugMsg(42, structShift);}																									//����ਬ �� �訡��
			break;																																//��室�� �� 横��
		case 1:																																	//� ��砥 �᫨ ��࠭� ������ ��⪨ ࠧ��� 䠩��
			Wave.chunkSizeBytes=qByteConverter(paramToWrite);																					//��������㥬 � 4 ����� �ଠ�
			pringDebugMsg(3,structShift);																										//��襬 � ���᮫� 㢥�������� � ����� � ��������																									
			pringDebugMsg(41, structShift);																										//ᮮ�頥� �� �ᯥ� � ���᮫�(���� �� �஢�ઠ �� �����⢫����)
			break;																																//��室�� �� 横��
		case 2:																																	//� ��砥 �᫨ ��࠭� ������ ��⪨ WAVE
			Wave.WaveSign=qByteConverter(paramToWrite);																							//��������㥬
			pringDebugMsg(3,structShift);																										//��襬 � ���᮫� 㢥�������� � ����� � ��������
			if(Wave.WaveSign==WAVEsignature)																									//�ࠢ������ � �⠫����
			{pringDebugMsg(41, structShift);}																									//ᮮ�頥� �� �ᯥ� � ���᮫�(���� �� �஢�ઠ �� �����⢫����)
			else																																//����...
			{pringDebugMsg(42, structShift);}																									//ᮮ�頥� �� �訡��
			break;																																//��室 �� 横��
		case 3:																																	//� ��砥 �᫨ ��࠭� ������ ��⪨ fmt
			Wave.fmtSign=qByteConverter(paramToWrite);																							//��������㥬																							
			pringDebugMsg(3,structShift);																										//��襬 � ���᮫� 㢥�������� � ����� � ��������
			if(Wave.fmtSign==fmtSignature)																										//�ࠢ������ � �⠫����
			{pringDebugMsg(41, structShift);}																									//ᮮ�頥� �� �ᯥ� � ���᮫�(���� �� �஢�ઠ �� �����⢫����)
			else																																//����...
			{pringDebugMsg(42, structShift);}																									//��襬 �� �訡��
			break;																																//��室�� �� 横��
		case 4:																																	//� ��砥 �᫨ ��࠭� ������ �ଠ� ������
			Wave.DataFormatLenght=qByteConverter(paramToWrite);																					//��������㥬
			pringDebugMsg(3,structShift);																										//��襬 � ���᮫� 㢥�������� � ����� � ��������
			pringDebugMsg(41, structShift);																										//ᮮ�頥� �� �ᯥ� � ���᮫�(���� �� �஢�ઠ �� �����⢫����)
			break;																																//��室�� �� 横��
		case 5:																																	//� ��砥 �᫨ ��࠭� ������ ���� ᦠ��
			Wave.compressionCode=dByteConverter(paramToWrite);																					//��������㥬
			pringDebugMsg(3,structShift);																										//��襬 � ���᮫� 㢥�������� � ����� � ��������
			pringDebugMsg(41, structShift);																										//ᮮ�頥� �� �ᯥ� � ���᮫�(���� �� �஢�ઠ �� �����⢫����)
			break;																																//��室�� �� 横��
		case 6:																																	//� ��砥 �᫨ ��࠭� ������ ������⢠ �������
			Wave.soundChannels=dByteConverter(paramToWrite);																					//��������㥬
			pringDebugMsg(3,structShift);																										//��襬 � ���᮫� 㢥�������� � ����� � ��������
			pringDebugMsg(41, structShift);																										//ᮮ�頥� �� �ᯥ� � ���᮫�(���� �� �஢�ઠ �� �����⢫����)
			break;																																//��室�� �� 横��
		case 7:																																	//� ��砥 �᫨ ��࠭� ������ ����� ����⨧�樨
			Wave.sampleRate=qByteConverter(paramToWrite);																						//��������㥬
			pringDebugMsg(3,structShift);																										//��襬 � ���᮫� 㢥�������� � ����� � ��������
			pringDebugMsg(41, structShift);																										//ᮮ�頥� �� �ᯥ� � ���᮫�(���� �� �஢�ઠ �� �����⢫����)	
			break;																																//��室�� �� 横��
		case 8:																																	//� ��砥 �᫨ ��࠭� ������ ���३�
			Wave.byteRate=qByteConverter(paramToWrite);																							//��������㥬
			pringDebugMsg(3,structShift);																										//��襬 � ���᮫� 㢥�������� � ����� � ��������
			pringDebugMsg(41, structShift);																										//ᮮ�頥� �� �ᯥ� � ���᮫�(���� �� �஢�ઠ �� �����⢫����)
			break;																																//��室�� �� 横��
		case 9:																																	//� ��砥 �᫨ ��࠭� ������ ������ ᥬ��� � �����
			Wave.BytesInSample=dByteConverter(paramToWrite);																					//��������㥬
			pringDebugMsg(3,structShift);																										//��襬 � ���᮫� 㢥�������� � ����� � ��������
			pringDebugMsg(41, structShift); 																									//ᮮ�頥� �� �ᯥ� � ���᮫�(���� �� �஢�ઠ �� �����⢫����)
			break;																																//��室�� �� 横��
		case 10:																																//� ��砥 �᫨ ��࠭� ������ ��㡨�� �롮�
			Wave.BitDepth=dByteConverter(paramToWrite);																							//��������㥬
			pringDebugMsg(3,structShift);																										//��襬 � ���᮫� 㢥�������� � ����� � ��������
			pringDebugMsg(41, structShift);																										//ᮮ�頥� �� �ᯥ� � ���᮫�(���� �� �஢�ઠ �� �����⢫����)
			break;																																//��室�� �� 横��
		case 11:																																//� ��砥 �᫨ ��࠭� ������ ��⪨ data
			Wave.dataSign=qByteConverter(paramToWrite);																							//��������㥬
			pringDebugMsg(3,structShift);																										//��襬 � ���᮫� 㢥�������� � ����� � ��������
			if(Wave.dataSign==dataSignature)																									//�ࠢ������ � �⠫����
			{pringDebugMsg(41, structShift);}																									//ᮮ�頥� �� �ᯥ� � ���᮫�(���� �� �஢�ઠ �� �����⢫����)
			else																																//����...
			{pringDebugMsg(42, structShift);}																									//��襬 ᮮ�饭�� �� �訡��
			break;																																//��室�� �� 横��
		case 12:																																//� ��砥 �᫨ ��࠭� ������ ࠧ��� ���⥩��� � ᥬ�����
			Wave.chunkSizeWoutHeader=qByteConverter(paramToWrite);																				//��������㥬
			pringDebugMsg(3,structShift);																										//��襬 � ���᮫� 㢥�������� � ����� � ��������
			pringDebugMsg(41, structShift);																										//ᮮ�頥� �� �ᯥ� � ���᮫�(���� �� �஢�ઠ �� �����⢫����)
			break;																																//��室�� �� 横��
	}																																			//����� 横��
}																																				//����� ⥫� �㭪樨
uint32_t qByteConverter(uint32_t wordToConvert)																									//�������� ࠧ�來��� 32->32 ���
{																																				//��砫� ⥫� ��������
	pringDebugMsg(4,0);																															//��襬 � 㢥�������� �� ��������� �� �ॡ����
	return wordToConvert;																														//�����頥� ���祭��
}																																				//����� ⥫� �㭪樨
uint16_t dByteConverter(uint32_t wordToConvert)																									//�������� ࠧ�來��� 32->16 ���
{																																				//��砫� ⥫� �㭪樨
	uint16_t doubleByteWord;																													//���樠������ �६����� ��६�����
	//doubleByteWord=wordToConvert<<16;																											//������
	doubleByteWord=wordToConvert;																												//�����뢠�� � ��६����� ��।���� ��㬥��
	pringDebugMsg(5,0);																															//��襬 �� �⮬ � ���᮫�
	return doubleByteWord;																														//�����頥� ���祭�� �� ���� �맮��
}																																				//����� ⥫� �㭪樨
uint8_t sByteConverter(uint32_t wordToConvert)																									//�������� ࠧ�來��� 32->8 ���
{																																				//��砫� ⥫� �㭪樨
	uint8_t singleByteWord;																														//���樠�����㥬 ��६�����
	//singleByteWord=wordToConvert<<24;																											//������?
	singleByteWord=wordToConvert;																												//�����뢠�� ��㬥�� � ��� ��६�����
	pringDebugMsg(6,0);																															//��襬 � ���᮫� �� �⮬
	return singleByteWord;																														//�����頥� ���祭�� �� ���� �맮��
}																																				//����� ⥫� �㭪樨
void structAnalyzer(void)																														//���筠� �஢�ઠ ��������, ⮫쪮 �� ��⪠�, ��� � ��������
{																																				//��砫� �㭪樨
	int chechedSteps=0;																															//������
	int headerDifference;																														//����� ���������
	headerDifference=Wave.chunkSizeBytes-Wave.chunkSizeWoutHeader;																				//����塞 ����� ���������
	pringDebugMsg(9,0);																															//��襬 � ���᮫�
	if(Wave.RiffSign==RIFFsignature)																											//�࠭����� � �⠫���� ���� RIFF
	{																																			//��砫� ⥫�
		chechedSteps++;																															//���騢��� ������⥫� �஢�७��� ����⮢ �� 1
		pringDebugMsg(39,0);																													//��襬 � ��
	}																																			//����� ⥫�
	else																																		//����...
	{pringDebugMsg(40,0);}																														//��襬 �� �訡��
	if(Wave.WaveSign==WAVEsignature)																											//�ࠢ������ ���� WAVE
	{																																			//��砫� ⥫�
		chechedSteps++;																															//���६����㥬 ���祭�� ���稪� ��室�
		pringDebugMsg(43,0);																													//��襬 � ���᮫�
	}																																			//����� ⥫�
	else																																		//����...
	{pringDebugMsg(40,0);}																														//...��襬 ᮮ�饭�� �� �訡��
	if(Wave.fmtSign==fmtSignature)																												//�ࠢ������ ��⪨ fmt
	{																																			//��砫� ⥫�
		chechedSteps++;																															//���६����㥬 ���祭�� ���稪� ��室�
		pringDebugMsg(44,0);																													//��襬 � ���᮫�
	}																																			//����� ⥫�
	else																																		//����...
	{pringDebugMsg(40,0);}																														//...��襬 ᮮ�饭�� �� �訡��
	if(Wave.dataSign=dataSignature)																												//�ࠢ������ ���� data
	{																																			//��砫� ⥫�
		chechedSteps++;																															//���६����㥬 ���祭�� ���稪� ��室�
		pringDebugMsg(45,0);																													//��襬 � ���᮫�
	}																																			//����� ⥫�
	else																																		//����...
	{pringDebugMsg(40,0);}																														//...ᮮ�頥� �� �訡��
	pringDebugMsg(46,0);																														//��襬 � ��砫� �⥭�� ��ࠬ��஢
	pringDebugMsg(47,0);																														//��襬 � ���᮫�
	printf(FileSizeMsg, Wave.chunkSizeBytes);																									//㪠�뢠�� �� ࠧ��� 䠩��, ����� �� ���������
	pringDebugMsg(47,0);																														//��襬 � ���᮫�
	printf(FileSizeWoutHeaderMsg, Wave.chunkSizeWoutHeader);																					//��襬 � ���᮫� ࠧ��� ��� ���������
	if(headerDifference==36)																													//�ࠢ������ ࠧ��� ��������� ��� ��� ����� ������
	{																																			//��砫� ⥫�
		chechedSteps++;																															//���६����㥬 ���祭�� ���稪� ��室�
		pringDebugMsg(48,0);																													//��襬 � ���᮫�
	}																																			//����� ⥫�
	else																																		//����...
	{pringDebugMsg(49,0);}																														//...��襬 � ���᮫� ᮮ�饭�� �� �訡��
	pringDebugMsg(47,0);																														//��襬 � ���᮫�
	printf(SampleRateMsg, Wave.sampleRate);																										//��襬 ����� ����⨧�樨
	pringDebugMsg(47,0);																														//��襬 � ���᮫�
	printf(ByteRateMsg, Wave.byteRate);																											//��襬 ���३�
	pringDebugMsg(47,0);																														//��襬 � ���᮫�
	printf(BitDepthMsg, Wave.BitDepth);																											//��襬 ��㡨�� �롮ન
	pringDebugMsg(47,0);																														//��襬 � ���᮫�
	printf(ChannelsMsg, Wave.soundChannels);																									//��襬 ����� �������
	pringDebugMsg(50,Wave.soundChannels);																										//��襬 ����� �������
	pringDebugMsg(47,0);																														//��襬 � ���᮫�
	printf(BytesInSampleMsg, Wave.BytesInSample);																								//��襬 ������⢮ ���� � �롮થ
	pringDebugMsg(47,0);																														//��襬 � ���᮫�
	printf(CodecTypeMsg);																														//��襬 ⨯ ������
	pringDebugMsg(51,Wave.compressionCode);																										//��襬 ��� ᦠ��
	wordSamplesValuePos=((Wave.chunkSizeWoutHeader-8)*8)/Wave.soundChannels/Wave.BitDepth;														//����塞 ���⭮� ������⢮ �롮ப
	pringDebugMsg(68, wordSamplesValuePos);																										//��襬 � ���᮫�
	if(chechedSteps==5)																															//�ࠢ������ ������⢮ �ன������ �⠯�� � �ॡ㥬� � �
	{																																			//��砫� ⥫� 横��
		pringDebugMsg(52,0);																													//��襬 � ���᮫�
		ahsoka=1;																																//�᫨ �� �� � �모�뢠�� 䫠� �� �ᯥ�
		checkStatus(2);																															//��뢠�� �஢��� 䫠��
	}																																			//����� ⥫�
	else																																		//����...
	{pringDebugMsg(17,0);}																														//ᮮ�頥� �� �訡�� � ��室�� �� �ணࠬ��
}																																				//����� ⥫� �㭪樨
void structModifier(void)																														//�㭪�� ����� � ��������
{																																				//��砫� ⥫� �㭪樨
	float sampleDivide;																															//������, ᮮ⭮襭�� ������⢮ �롮ப ��室���� 䠩�� � �������� �롮ப ������ �� convertParams.ini
	uint16_t newBytesInSample;																													//�६����� ��६����� ��� ���᫥��� ������⢠ ���� � ����� �롮થ � ��� �������
	uint32_t newByteRate;																														//�६����� ��६����� ��� ���᫥��� ᪮��� ��।�� ������, ����/�
	uint32_t newFileSizeWOutHeader;																												//�६����� ��६����� ��� ���᫥��� ࠧ��� 䠩�� ��� ���������
	sampleDivide=Wave.sampleRate/FilSet.FSetSampleRate;																							//�ࠧ� �� ������ ᮮ⭮襭�� ������⢠ �롮ப, ������� ���� �����
	pringDebugMsg(53,0);																														//�뢮� ᮮ�饭�� � ��砫� ࠡ�� �㭪樨
	pringDebugMsg(99, FilSet.FSetSamplesValue);																									//�뢮� � ���᮫�
	pringDebugMsg(58,0);																														//�뢮� ᮮ�饭�� � ⮬, �� �� ��筥��� ������ � ��������
	Wave.sampleRate=FilSet.FSetSampleRate;																										//������ � �������� ����� ����⨧�樨, ����祭�� �� 䠩�� convertParams.ini
	pringDebugMsg(55, Wave.sampleRate);																											//�뢮� ᮮ�饭�� �� �⮬
	Wave.BitDepth=FilSet.FSetBitDepth;																											//������ � �������� ��㡨�� �롮ન, ����祭�� �� 䠩�� convertParams.ini
	pringDebugMsg(54, Wave.BitDepth);																											//�뢮� ᮮ�饭�� �� �⮬
	Wave.soundChannels=FilSet.FSetChannels;																										//������ � �������� ������⢮ �������, ����祭��� �� 䠩�� convertParams.ini
	pringDebugMsg(57, Wave.soundChannels);																										//�뢮� ᮮ�饭�� �� �⮬
	newByteRate=(Wave.sampleRate*Wave.BitDepth*Wave.soundChannels)/8;																			//���᫥��� ᪮��� ��।�� ������, ���� � ᥪ㭤�
	Wave.byteRate=newByteRate;																													//������ � �������� १����
	pringDebugMsg(56, Wave.byteRate);																											//�뢮� ᮮ�饭�� �� �⮬
	newBytesInSample=(Wave.BitDepth*Wave.soundChannels)/8;																						//���᫥��� ������⢠ ���⮢ � ����� �롮થ � ��� �������
	Wave.BytesInSample=newBytesInSample;																										//������ � ��������
	pringDebugMsg(67, Wave.BytesInSample);																										//�뢮� ᮮ�饭�� �� �⮬
	printSampleDivide(sampleDivide);																											//�뢮� �筮�� ᮮ⭮襭�� �롮ப
	newFileSizeWOutHeader=(((FilSet.FSetSamplesValue/sampleDivide)*Wave.BitDepth*Wave.soundChannels)/8)+8;										//���᫥��� ࠧ��� 䠩�� ��� ���������
	Wave.chunkSizeWoutHeader=newFileSizeWOutHeader;																								//������ � ��������
	pringDebugMsg(69, Wave.chunkSizeWoutHeader);																								//�뢮� � ���᮫�
	Wave.chunkSizeBytes=newFileSizeWOutHeader+36;																								//�������� 36 ���� ���������
	pringDebugMsg(70, Wave.chunkSizeBytes);																										//�뢮� � ���᮫�
	cruzo=1;																																	//�����뢠�� 1, �� ���, � ���쭥�襬 �㤥� ����ᠭ ��� ᠬ��஢�ન �㭪樨
	checkStatus(6);																																//��뢠� �㭪�� �஢�ન 䫠�� ���ﭨ�
}																																				//����� ⥫� �㭪樨
int WriteSettingsFile(void)																														//�㭪�� �����⮢�� ������஢������ ��������� � �����
{																																				//��砫� ⥫� �㭪樨
	pringDebugMsg(75,0);																														//��襬 � ���᮫� ᮮ�饭�� � ��砫� ࠡ���
	clearHeaderBuffer();																														//��⨬ ���� ���������
	writeBuffer(headerAddrs[0], headerAddrs[1], Wave.RiffSign, headerWordSizeOf[0], headerWordInvert[0]);										//��襬 � ���� ���� RIFF
	writeBuffer(headerAddrs[1], headerAddrs[2], Wave.chunkSizeBytes, headerWordSizeOf[1], headerWordInvert[1]);									//��襬 � ���� ࠧ��� 䠩��
	writeBuffer(headerAddrs[2], headerAddrs[3], Wave.WaveSign, headerWordSizeOf[2], headerWordInvert[2]);										//��襬 � ���� ���� WAVE
	writeBuffer(headerAddrs[3], headerAddrs[4], Wave.fmtSign, headerWordSizeOf[3], headerWordInvert[3]);										//��襬 � ���� ���� fmt
	writeBuffer(headerAddrs[4], headerAddrs[5], Wave.DataFormatLenght, headerWordSizeOf[4], headerWordInvert[4]);								//��襬 � ���� ࠧ��� 䠩��
	writeBuffer(headerAddrs[5], headerAddrs[6], Wave.compressionCode, headerWordSizeOf[5], headerWordInvert[5]);								//��襬 � ���� ��� ᦠ��
	writeBuffer(headerAddrs[6], headerAddrs[7], Wave.soundChannels, headerWordSizeOf[6], headerWordInvert[6]);									//��襬 � ���� ����� �������
	writeBuffer(headerAddrs[7], headerAddrs[8], Wave.sampleRate, headerWordSizeOf[7], headerWordInvert[7]);										//��襬 � ���� ����� ����⨧�樨
	writeBuffer(headerAddrs[8], headerAddrs[9], Wave.byteRate, headerWordSizeOf[8], headerWordInvert[8]);										//��襬 � ���� ���३�
	writeBuffer(headerAddrs[9], headerAddrs[10], Wave.BytesInSample, headerWordSizeOf[9], headerWordInvert[9]);									//��襬 � ���� ࠧ��� �롮ન � �����
	writeBuffer(headerAddrs[10], headerAddrs[11], Wave.BitDepth, headerWordSizeOf[10], headerWordInvert[10]);									//��襬 � ���� ��㡨�� �롮ન
	writeBuffer(headerAddrs[11], headerAddrs[12], Wave.dataSign, headerWordSizeOf[11], headerWordInvert[11]);									//��襬 � ���� ���� data
	writeBuffer(headerAddrs[12], headerAddrs[13], Wave.chunkSizeWoutHeader, headerWordSizeOf[12], headerWordInvert[12]);						//��襬 � ���� ࠧ��� 䠩�� ��� ���������
	BufferReader();																																//�����㥬 ᮤ�ন��� � �⤥��� ���ᨢ ��� ������ ��� ᮤ�ন���� � ०��� �⫠���
	pringDebugMsg(81,0);																														//㢥����塞 �� �⮬
	printf("%s",fileNameHdrDat);
	FWr=fopen(fileNameHdrDat, "wb");																											//ᮧ���� 䠩� ��������� � ࠭��� ᣥ���஢���� ������
	if(FWr != NULL)																																//�஢��塞 㤠���� �� ᮧ���� 䠩�
	{																																			//��砫� ⥫�(��⨭�)
		printf(" �ᯥ�\n");																														//��襬 � ���᮫� �� �� ���
	}																																			//����� ⥫�(��⨭�)
	else																																		//����...
	{																																			//��砫� ⥫�(����)
		printf(" �� 㤠���� ᮧ���� 䠩� %s\n",fileNameHdrDat);																					//...��襬 � �������� �஡�����
		exit(0);																																//��室�� � ����� �訡�� 0
	}																																			//����� ⥫�(����)
	fseek(FWr, 0, SEEK_SET);																													//��⠭�������� ����� �� 0
	fwrite(FileHeader, sizeof(uint8_t), sizeof(FileHeader), FWr);																				//��襬 ��������� � 䠩�
	fclose(FWr);																																//�����⨥ 䠩�� ��� �����
}																																				//����� ⥫� 横��
int ReadSettingsFile(void)																														//�⠫�� ��ࠬ��஢ �� 䠩��
{																																				//��砫� ⥫�
	uint32_t fSrcTagEndPos;																														//���塞 ��६����� � ���ன �㤥� �࠭��� ���� ⥣� FEND ��� ����� ��室����
	uint32_t fNamtagEndPos;																														//���塞 ��६����� � ���஥ �㤥� �࠭��� ���� ⥣� FEND ��� ᣥ���஢������ ����� 䠩��
	uint8_t readCursorPos=0;																													//���塞 �������� ��६����� ���ᨢ� ������ �㤥� �ਬ����� �� ����஢����
	char fSrcNameBuffer[64];																													//���塞 ���ᨢ � ���஬ �㤥� �࠭����� "��饭���" ��室��� ��� 䠩��(��� ⥣��)
	char fNamNameBuffer[64];																													//���塞 ���ᨢ � ���஬ �㤥� �࠭����� "��饭���" ᣥ���஢����� ��� 䠩��(��� ⥣��)
	memset(fSrcNameBuffer, 0x00, sizeof(fSrcNameBuffer));																						//��⨬ ���ᨢ ��室���� �����
	memset(fNamNameBuffer, 0x00, sizeof(fNamNameBuffer));																						//��⨬ ���ᨢ ᣥ���஢����� �����
	char *endTag;																																//���塞 㪠��⥫� �� ������ ᫮�� ���஥ ����� � ��ப�
	pringDebugMsg(59,1);																														//��襬 � ���᮫� ���� � �⥭�� 䠩��
	FSet=fopen("convertParams.ini", "rb");																										//���뢠�� 䠩� ��� ����୨�
	if(!FSet)																																	//�஢��塞 䠪� ������ 䠩��
	{																																			//��砫� ⥫�
		pringDebugMsg(88,0);																													//�᫨ 䠩� �� ������, ��� ��� ���������� ������, ��⠥��� ᮧ���� ��� ����� + ��襬 � ���᮫�
		printf("���� convertParams.ini �� ������ ��� ���०���. �㤥� ᮧ��� 䠩� � ��ࠬ��ࠬ� �� ⥪�饣� ���������\n");						//��襬 �� �⮬ � ���᮫�
		storeStructToFile();																													//�����뢠�� ����ன�� � 䠩�
		pringDebugMsg(84,0);																													//��室 �� �ணࠬ���
	}																																			//����� ⥫�
	else																																		//����...
	{																																			//��砫� ⥫�
		pringDebugMsg(89,0);																													//...��襬 � ���᮫�
		printf("���� convertParams.ini ������ � �����\n");																						//�� 䠩� �����																																			//����� ⥫�
		fread(fileMassive, 1, sizeof(fileMassive), FSet);																						//�⠥� 䠩� 㪠����� � ��㬥��� ࠭���
		cursorSymbol=strstr(fileMassive, wordFilenameSource);																					//�饬 ⥣ FSRC
		wordFsrcPos=cursorSymbol-fileMassive+1;																									//��襬 ���� ��砫� ⥣�
		cursorPosit=wordFsrcPos+wordFilenameShift;																								//��襬 ���� �����
		fseek(FSet, cursorPosit, SEEK_SET);																										//�⠢�� ����� �� �����
		fscanf(FSet, "%s", &fileNameSrc);																										//�⠥� ᮤ�ন��� 䠩�� �� ���⠢������� �����
		endTag=strstr(fileNameSrc, wordSrcFilenameEnd);																							//�����뢠�� � 㪠��⥫� ���� ����� � ���ண� ��稭����� ��������� ᫮�� FEND
		fSrcTagEndPos=endTag-fileNameSrc;																										//������뢠�� ����� �㦭��� �ࠣ����, � ������ ��砥 �� ��� ��室���� 䠩��
		while(readCursorPos<fSrcTagEndPos)																										//���塞 横� �㡫�஢���� ���ᨢ� � ��㣮� ���ᨢ, ����� �㦥� ��� ����� 楫��
		{																																		//��砫� 横��
			fSrcNameBuffer[readCursorPos]=fileNameSrc[readCursorPos];																			//��ᨬ���쭮 ��७�ᨬ ���ᨢ
			readCursorPos++;																													//���६����㥬 ������ ���ᨢ�
		}																																		//����� ⥫�
		readCursorPos=0;																														//���뢠�� ���稪 ������
		cursorSymbol=strstr(fileMassive, wordFilename);																							//�饬 ⥣ FNAM
		wordFnamePos=cursorSymbol-fileMassive+1;																								//��襬 ���� ��砫� ⥣�
		cursorPosit=wordFnamePos+wordFilenameShift;																								//��襬 ���� �����
		fseek(FSet, cursorPosit, SEEK_SET);																										//�⠢�� ����� �� �����
		fscanf(FSet, "%s", &fileName);																											//�⠥� ᮤ�ন��� 䠩�� �� ���⠢������� �����
		endTag=strstr(fileName, wordNameFilenameEnd);																							//�����뢠�� � 㪠��⥫� ���� ����� � ���ண� ��稭����� ��������� ᫮�� FEND
		fNamtagEndPos=endTag-fileName;																											//����塞 ����� ᣥ���஢������ ����� 䠩��
		while(readCursorPos<fNamtagEndPos)																										//���塞 横� ����஢���� ���ᨢ� � ��㣮� ���ᨢ ����� �㦥� ��� ����� 楫��
		{																																		//��砫� ⥫� 横��
			fNamNameBuffer[readCursorPos]=fileName[readCursorPos];																				//��ᨬ���쭮 ��७�ᨬ ���ᨢ
			fileNameHdrDat[readCursorPos]=fileName[readCursorPos];
			readCursorPos++;																													//���६����㥬 ������ ���ᨢ�
		}																																		//����� ⥫�
		cursorSymbol=strstr(fileMassive, wordConvert);																							//�饬 ⥣ Convert
		wordConvertPos=cursorSymbol-fileMassive+1;																								//��襬 ���� ��砫� ⥣�
		cursorPosit=wordConvertPos+wordConvertShift;																							//��襬 ���� �����
		fseek(FSet, cursorPosit, SEEK_SET);																										//�⠢�� ����� �� �����
		fscanf(FSet, "%d", &FilSet.FSetWasConverted);																							//�⠥� ᮤ�ন��� �� ���⠢������� �����
		cursorSymbol=strstr(fileMassive, wordSampleRate);																						//�饬 ⥣ SampleRate
		wordSampleRatePos=cursorSymbol-fileMassive+1;																							//��襬 ���� ��砫� ⥣�
		cursorPosit=wordSampleRatePos+wordSampleRateShift;																						//��襬 ���� �����
		fseek(FSet, cursorPosit, SEEK_SET);																										//�⠢�� ����� �� �����
		fscanf(FSet, "%d", &FilSet.FSetSampleRate);																								//�⠥� ᮤ�ন��� 䠩�� �� ���⠢������� �����
		cursorSymbol=strstr(fileMassive, wordChannels);																							//�饬 ⥣ Channels
		wordChannelsPos=cursorSymbol-fileMassive+1;																								//��襬 ���� ��砫� ⥣�
		cursorPosit=wordChannelsPos+wordChannelsShift;																							//��襬 ���� �����
		fseek(FSet, cursorPosit, SEEK_SET);																										//�⠢�� ����� �� �����
		fscanf(FSet, "%d", &FilSet.FSetChannels);																								//�⠥� ᮤ�ন��� 䠩�� �� ���⠢������� �����
		cursorSymbol=strstr(fileMassive, wordBitsPerSample);																					//�饬 ⥣ BitsPerSample
		wordBitsPerSamplePos=cursorSymbol-fileMassive+1;																						//��襬 ���� ��砫� ⥣�
		cursorPosit=wordBitsPerSamplePos+wordBitsPerSampleShift;																				//��襬 ���� �����
		fseek(FSet, cursorPosit, SEEK_SET);																										//�⠢�� ����� �� �����
		fscanf(FSet, "%d", &FilSet.FSetBitDepth);																								//�⠥� ᮤ�ন��� 䠩�� �� ���⠢������� �����
		cursorSymbol=strstr(fileMassive, WordCountOfSamples);																					//�饬 ⥣ BitsPerSample
		wordSamplesValuePos=cursorSymbol-fileMassive+1;																							//��襬 ���� ��砫� ⥣�
		cursorPosit=wordSamplesValuePos+wordSamplesValueShift;																					//��襬 ���� �����
		fseek(FSet, cursorPosit, SEEK_SET);																										//�⠢�� ����� �� �����
		fscanf(FSet, "%d", &FilSet.FSetSamplesValue);																							//�⠥� ᮤ�ন��� 䠩�� �� ���⠢������� �����
		pringDebugMsg(89,0);																													//��� � ���᮫�
		pringDebugMsg(94,fSrcTagEndPos);																										//��襬 ���� ᬥ饭�� �� ⥣� FSRC
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		printf("��� ��室���� 䠩��: %s\n", fSrcNameBuffer);																					//��襬 ��� ��室���� 䠩��
		pringDebugMsg(89,0);																													//��� � ���᮫�
		pringDebugMsg(94,fNamtagEndPos);																										//��襬 ���� ᬥ饭�� �� ⥣� FNAM
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		printf("��� 䠩�� � ����������: %s\n", fNamNameBuffer);																					//��襬 ��� ��������筮�� 䠩��
		pringDebugMsg(89,0);																													//��� � ���᮫�
		printf("���� ᬥ饭�� �� ⥣�� Convert,SampleRate,Channels,BitsPerSample,SamplesInChannel\n");										//��襬 ���� �� �� ���� ���� ᬥ饭�� ⥣��
		pringDebugMsg(89,0);																													//��� � ���᮫�
		pringDebugMsg(90,wordConvertPos);																										//��襬 ���� ᬥ饭�� �� ⥣� Convert
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		pringDebugMsg(90,wordSampleRatePos);																									//��襬 ���� ᬥ饭�� �� ⥣� SampleRate
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		pringDebugMsg(90,wordChannelsPos);																										//��襬 ���� ᬥ饭�� �� ⥣� Channels
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		pringDebugMsg(90,wordBitsPerSamplePos);																									//��襬 ���� ᬥ饭�� �� ⥣� BitsPerSample
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		pringDebugMsg(90,wordSamplesValuePos);																									//��襬 ���� ᬥ饭�� �� ⥣� BitsPerSample
	}																																			//����� ⥫�
	pringDebugMsg(89,0);																														//��襬 � ���᮫�
	if(DebugMode==1)																															//������ �� �஢��� ०��� �⫠���
	{																																			//��砫� ⥫�
		printf("���-�� �������: %d\n", FilSet.FSetChannels);																					//��襬 ������⢮ �������
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		printf("����� ����⨧�樨: %d ��\n", FilSet.FSetSampleRate);																		//��襬 ����� ����⨧�樨
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		printf("���� �������樨: %d\n", FilSet.FSetWasConverted);																				//��襬 ���ﭨ� 䫠�� �������樨(�뫠 �� ��� ��� ���)
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		printf("��� � �롮થ: %d ���\n", FilSet.FSetBitDepth);																					//��襬 ��㡨�� �롮ન
		pringDebugMsg(89,0);																													//��襬 � ���᮫�
		printf("������⢮ �롮ப � ����� ������: %d\n", FilSet.FSetSamplesValue);																//��襬 ������⢮ �롮ப �� ���� �����
	}																																			//����� ⥫�
	pringDebugMsg(60, FilSet.FSetSampleRate);																									//��襬 ����� ����⨧�樨 � ���᮫�
	pringDebugMsg(62, FilSet.FSetChannels);																										//��襬 ������⢮ ������� � ���᮫�
	pringDebugMsg(61, FilSet.FSetBitDepth);																										//��襬 ��㡨�� �롮ન � ���᮫�
	if(FilSet.FSetWasConverted==0)																												//�஢�ઠ 䠪� �������樨
	{																																			//��砫� ⥫�
		pringDebugMsg(63, FilSet.FSetWasConverted);																								//��襬 � ���᮫� ᭮��
		Egor=1;																																	//�⠢�� 䫠�
		checkStatus(5);																															//��뢠�� �஢��� 䫠��
		pringDebugMsg(83,0);																													//��襬 � ���᮫� 㢥�������� �� � 䠩��� �� ��祣� �� ������
	}																																			//����� ⥫�
	else																																		//����...
	{																																			//��砫� ⥫�
		pringDebugMsg(63, FilSet.FSetWasConverted);																								//...��稭��� �ନ஢��� ���������
		Egor=1;																																	//��������� 䫠� ��))
		checkStatus(5);																															//��뢠�� �஢���
		fclose(FSet);																															//����뢠�� 䠩� �.� �� ����� �� �㦥� � ����� ������
		structModifier();																														//��襬 ��������� � 䠩�
		return 0;																																//�����頥� 0
	}																																			//����� ⥫�
	fclose(FSet);																																//����뢠�� ��⮪, �᫨ �� ���-� �� �� �� ������
}																																				//����� �㭪樨
inline void clearByteBuffer(void)																												//���⪠ �६������ ����(���ࠨ������ �㭪��)
{																																				//��砫� ⥫�
	pringDebugMsg(79,0);																														//��襬 � ���᮫� 㢥�������� �� ���� ��⪠ ����
	memset(ByteBuffer,0x00,sizeof(ByteBuffer));																									//��⨬ ���ᨢ
}																																				//����� ⥫�
inline void clearHeaderBuffer(void)																												//���⪠ ���ᨢ� ���������(���ࠨ������ �㭪��
{																																				//��砫� ⥫�
	pringDebugMsg(80,0);																														//��襬 ᮮ�饭�� � ⮬ �� �� �㤥� ����� ���ᨢ
	for(int i=0;i<43;i++)																														//��砫� 横�� ��⪨
	{																																			//��砫� ⥫� 横��
		FileHeader[i]=0;																														//��⨬ �����⮢� ���ᨢ
	}																																			//����� ⥫� 横��
}																																				//����� ⥫� �㭪樨
inline void BufferReader(void)																													//�㭪�� ����஢���� ��������� � �⤥��� ���ᨢ ��� ������ �⫠����� 㢥��������(���ࠨ������)
{																																				//��砫� ⥫�
	writeDebugHeaderBuffer();																													//��뢠�� �㭪�� ����஢����
	pringDebugMsg(25,0);																														//��襬 㢥�������� �� �⮬
}																																				//����� ⥫�
uint32_t writeBuffer(int startOffset, int endOffset, uint32_t paramToWrite, int wordSize, bool SwapByte)										//�㭪�� ����� ����
{																																				//��砫� ⥫�
	int debugCursorPos=0;																														//���樠�����㥬 ��६�����
	int bufferPos=0;																															//��樠������㥬 ��६����� ������ ���ᨢ��
	pringDebugMsg(76,paramToWrite);																												//��襬 � ���᮫� �� ��稭�� ����� ����祭�� ��ࠬ���
	switch(wordSize)																															//�롮� ᯮᮡ� ����� � ����ᨬ��� �� ࠧ��� ����祭���� �� �室�
	{																																			//� ���� 0 ���� - �訡��, 1 ���� - ��襬 1 ����, 2 ���� - ���� ��襬 � �.�
		case 0:																																	//� ��砥 �᫨ 0 ����(NANI?)
			pringDebugMsg(77,0);																												//��襬 �� ⠪�� ��६����� �� ������� � ��室�� �� �ணࠬ��
			break;																																//��室 �� 横��
		case 1:																																	//� ��砥 �᫨ 1 ����
			ByteBuffer[0]=paramToWrite;																											//��襬 � ���� 1 ����
			break;																																//��室�� �� 横��
		case 2:																																	//� ��砥 �᫨ 2 ����
			ByteBuffer[0]=paramToWrite;																											//��襬 ���訩 ����
			ByteBuffer[1]=paramToWrite>>8;																										//��襬 ����訩 ����
			break;																																//��室�� �� 横��
		case 4:																																	//� ��砥 �᫨ 4 ����
			ByteBuffer[0]=paramToWrite;																											//��襬 ���訩 ����
			ByteBuffer[1]=paramToWrite>>8;																										//��襬 ���� �������
			ByteBuffer[2]=paramToWrite>>16;																										//��襬 ���� �������
			ByteBuffer[3]=paramToWrite>>24;																										//��襬 ����訩 ����
			break;																																//��室�� �� 横��
	}																																			//����� ⥫� 横��
	massiveSwap(SwapByte);																														//��ॢ��稢��� ���ᨢ
	while(debugCursorPos<wordSize)																												//��뢠�� 横� ������ ᮤ�ন���� �६������ ����
	{																																			//��砫� 横��
		pringDebugMsg(78, ByteBuffer[debugCursorPos]);																							//�����뢠�� � ���᮫� � �� ⠬ ��室����
		debugCursorPos++;																														//���६����㥬 ������
	}																																			//����� 横��
	debugCursorPos=0;																															//���뢠�� ��६�����
	while(startOffset<endOffset)																												//��砫� 横�� ����� ����஢���� �� ���� � ��������� � ������� ᬥ饭���
	{																																			//��砫� ⥫� 横��
		FileHeader[startOffset]=ByteBuffer[bufferPos];																							//�����⮢�� ����஢���� �� �६������ ���ᨢ�
		bufferPos++;																															//���६����㥬 ��६����� ������ ���ᨢ� �६������ ����
		startOffset++;																															//���६����㥬 ��६����� ���ᨢ� ���������
	}																																			//����� 横��
	bufferPos=0;																																//���뢠�� ��६�����
	clearByteBuffer();																															//��⨬ ����
}																																				//����� �㭪樨
void storeStructToFile(void)																													//�㭪�� ����� ����஥� � 䠩�
{																																				//��砫� �㭪樨
	uint8_t crlfSign[2]={0x0D, 0x0A};																											//��⪠ CR LF(��७�� ���⪨ �� ����� ��ப�)
	bool WordConverted=0;																														//���樠�����㥬 䫠�
	char *FnameSrc="FSRC>";																														//��� ��室���� 䠩��
	char *FnameBod="FBOD>";																														//��� ⥫� 䠩��
	char *Fnametgt="FTGT>";																														//��� 䠩�� ��᫥ ᪫�������
	char *Fname="FNAM>";																														//��� 䠩��
	char *WordConvert="Convert=";																												//��ࠧ�� ⥣� Convert
	char *WordSampleRate="SampleRate=";																											//��ࠧ�� ⥣� SampleRate
	char *WordChannels="Channels=";																												//��ࠧ�� ⥣� Channels
	char *WordBitsPerSample="BitsPerSample=";																									//��ࠧ�� ⥣� BitsPerSample
	char *WordCountOfSamples="SamplesInChannel=";																								//��ࠧ�� ⥣� SamplesInChannel
	pringDebugMsg(86,0);																														//㢥����塞 �� �� �㤥� ����� � 䠩�
	FSet=fopen("convertParams.ini", "wb");																										//���뢠�� 䠩� �� ������ ��� ������(��� ������? ��� ⥪�� �����)
	fseek(FSet, 0, SEEK_SET);																													//��⠭������� ����� �� 0
	fprintf(FSet, "%s", FnameSrc);																												//��襬 ⥣ FNAM
	fprintf(FSet, "%s", fileNameSrc);																											//��襬 ��� 䠩��
	fprintf(FSet, "%s", wordSrcFilenameEnd);																									//��襬 ⥣ >FSND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//��襬 CR LF
	fprintf(FSet, "%s", Fname);																													//��襬 ⥣ FNAM
	fprintf(FSet, "%s", fileNameHdrDat);																										//��襬 ��� 䠩��
	fprintf(FSet, "%s", wordNameFilenameEnd);																									//��襬 ⥣ >FNND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//��襬 CR LF
	fprintf(FSet, "%s", FnameBod);																												//��襬 ⥣ FBOD
	fprintf(FSet, "%s", fileNameBodDat);																										//��襬 ��� 䠩��
	fprintf(FSet, "%s", wordBodyFilenameEnd);																									//��襬 ⥣ >FBND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//��襬 CR LF
	fprintf(FSet, "%s", Fnametgt);																												//��襬 ⥣ FTGT
	fprintf(FSet, "%s", fileNameTgtDat);																										//��襬 ��� 䠩��
	fprintf(FSet, "%s", wordTargFilenameEnd);																									//��襬 ⥣ >FTND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//��襬 CR LF
	fprintf(FSet, "%s", WordConvert);																											//��襬 ⥣ Convert
	fprintf(FSet, "%d", WordConverted);																											//��襬 䫠� ���ﭨ�
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//��襬 CR LF
	fprintf(FSet, "%s", WordSampleRate);																										//��襬 ⥣ SampleRate
	fprintf(FSet, "%d", Wave.sampleRate);																										//��襬 ����� ����⨧�樨 �᫮�
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//��襬 CR LF
	fprintf(FSet, "%s", WordChannels);																											//��襬 ⥣ Channels
	fprintf(FSet, "%d", Wave.soundChannels);																									//��襬 ������⢮ �������
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//��襬 CR LF
	fprintf(FSet, "%s", WordBitsPerSample);																										//��襬 ⥣ BitsPerSample
	fprintf(FSet, "%d", Wave.BitDepth);																											//��襬 ��㡨�� �롮ન
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//��襬 CR LF
	fprintf(FSet, "%s", WordCountOfSamples);																									//��襬 ⥣ BitsPerSample
	fprintf(FSet, "%d", wordSamplesValuePos);																									//��襬 ������⢮ �롮ப
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//��襬 CR LF
	fclose(FSet);																																//����뢠�� 䠩�
	pringDebugMsg(87,0);																														//����뢠���� � ���᮫� � �த������� ࠡ��
}																																				//����� �㭪樨
