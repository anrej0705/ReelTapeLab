#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#define StartMsg			"v0.0.1 build 1\n"
#define codePageInfo 		"������ ������� ⠡��� �ਫ������ OEM CP-866\n"
char fileBuffer[256];
char fileName[128];
char tempName[9]="generated";
char headerNameSuffix[11]="_header.dat";																										//���䨪� � ����� �८�ࠧ㥬��� 䠩��
char headerBodySuffix[9]="_body.dat";																											//���䨪� � ����� �८�ࠧ㥬��� 䠩��
char headerConvSuffix[12]="_conv_FM.wav";																										//���䨪� � ����� �८�ࠧ㥬��� 䠩��
char fileNameHdrDat[64];																														//���ᨢ � ������ ��������筮�� 䠩��
char fileNameBodDat[64];																														//���ᨢ � ������ ��������筮�� 䠩��
char fileNameTgtDat[64];																														//���ᨢ � ������ ��������筮�� 䠩��
char *wordFilenameSource="FSRC";																												//�������� ��� ��ࠬ��� ����� 䠩��
char *wordFilenameBody="FBOD";		   																											//�������� ��� ��ࠬ��� ����� 䠩��
char *wordFilename="FNAM";																														//�������� ��� ��ࠬ��� ����� 䠩��
char *wordFilenameTarget="FTGT";																												//�������� ��� ��ࠬ��� ����� 䠩��
char *wordSrcFilenameEnd=">FSND";																												//�������� ��� ��ࠬ��� ����� 䠩��
char *wordNameFilenameEnd=">FNND";																												//�������� ��� ��ࠬ��� ����� 䠩��
char *wordBodyFilenameEnd=">FBND";																												//�������� ��� ��ࠬ��� ����� 䠩��
char *wordTargFilenameEnd=">FTND";																												//�������� ��� ��ࠬ��� ����� 䠩��
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
uint8_t tSP;		//����� ������-��⥪�� �����
uint8_t tTR;		//����� ������ ���.1
uint8_t tFL;		//����� ������ ���.0
uint8_t tSB;		//����� ���� ����� ��ࠢ��� ��⮢
uint16_t carrierFreq=12000;
uint16_t wavSampleRate=48000;
uint32_t summaryPacketLength;
uint32_t roundedVal=0;
uint32_t numberOfIterations;
bool binArr[8];
uint8_t outArr[128];
void createInputArr(bool *appPtr, uint8_t sizeArr, uint8_t inputByte);
void storeStructToFile(void);
uint8_t createDataPacket(bool *arrIn, uint8_t *arrOut, uint8_t packetNumber);
uint8_t createBit(uint8_t *inputMas, uint8_t startAdr, uint8_t endAdr, uint8_t charToFill, uint8_t bitPauseRange);
uint32_t appendArray(uint8_t *arrToAppend, uint32_t reallocMemory, uint32_t bufferIndex);
void transformFileName(char *sourceFileName, uint8_t sourceLenght, char *suffixToAttach, uint8_t suffixLength, char *arrToStore);
uint8_t *bufferMas;
uint8_t *lasstBufferMas;
int main(void)
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
	SoundChannels=1;
	BitDepth=8;
	bufferMas = malloc(32768);					//���� ��� ���� ᥬ���� ������㥬�� �� 256 ���� ������. ������ 墠���
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
		printf("��४��祭�� ������� ��࠭��� �� �ॡ����\n");
	}
	printf("�८�ࠧ���⥫� �ଠ⮢ BIN->WAV(����⭠� FM �������) \n");
	printf(StartMsg);
	printf("�� � ��栭�, � ᫥⥫ � �ࠣ� ⠪ �� ⥯��� �ண� ����॥ �㤥� �������. \n�ᥬ ��� �� ��⠫�� ᮡ�������\n");
	FIn=fopen("picLarge.png","rb");
	FOut=fopen("test.dat", "wb");
	fseek(FIn,0,SEEK_END);
	fileSize=ftell(FIn);
	//printf("������ �室���� 䠩��: %d ����\n",fileSize);
	tSP=(wavSampleRate/carrierFreq)*pkgSeparatorTiming;
	tTR=(wavSampleRate/carrierFreq)*logTrueTiming;
	tFL=(wavSampleRate/carrierFreq)*logElseTiming;
	tSB=(wavSampleRate/carrierFreq)*bitSeparatorTiming;
	printf("������� �⮯-���: %d\n������� ���.0: %d\n������� ���.1: %d\n������� ���� ����� ��ࠢ��� ��⮢: %d\n",tSP,tTR,tFL,tSB);
	printf("f(����)=%d\nf(�����)=%d\n",wavSampleRate,carrierFreq);
	modOfDiv=fmod(fileSize, sizeof(fileBuffer));
	//printf("������ ����� ���⮢: %f\n",modOfDiv);
	roundedVal=round(modOfDiv);
	//printf("���㣫����� ���祭��: %d\n", roundedVal);
	numberOfIterations=(fileSize-modOfDiv)/sizeof(fileBuffer);
	//printf("�㬬�୮� ������⢮ ������ ࠧ��஬ %d ���� �� ������: %d\n",sizeof(fileBuffer),numberOfIterations);
	lasstBufferMas=malloc(roundedVal);
	if(lasstBufferMas!=NULL)
	{
		printf("����� ࠧ��� ���� ��� ���⮪ � %d ����\n",roundedVal);
	}
	stopIteration=sizeof(fileBuffer);
	while(writeIterations<numberOfIterations+1)
	{
		writeIterations++;
		if(writeIterations>numberOfIterations)
		{
			printf("������ ����筮�� ����� �%d ࠧ��஬ � %d ����\n",writeIterations,roundedVal);
			stopIteration=roundedVal;
		}
		else
		{
			//printf("������ ����� �%d\n",writeIterations);
		}
		//printf("��砫� ����� ��室���� 䠩�� %d ����\n",inputFileReadIndex);
		//printf("��砫� ����� �� %d ����\n",arrIndex);
		memset(bufferMas,0x00,sizeof(bufferMas));
		fseek(FIn,inputFileReadIndex,SEEK_SET);
		fread(fileBuffer,1,sizeof(fileBuffer),FIn);
		//printf("������ ����: %d ����\n",stopIteration);
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
			pRange=createDataPacket(binArr, outArr, iterations);
			//printf("����� ����� ������ %d ����\n",pRange);
			summaryPacketLength=summaryPacketLength+pRange;
			transferIndex=appendArray(outArr, summaryPacketLength, transferIndex);
			//printf("�㬬��� ࠧ��� ����� ������ ��ꥬ�� %d ����⮢: %d ����\n",iterations,transferIndex);
			iterations++;
		}
		//printf("�㬬��� ࠧ��� ����ᠭ���� �����: %d ᥬ���\n",transferIndex);
		inputFileReadIndex=inputFileReadIndex+iterations;
		fseek(FOut,arrIndex,SEEK_SET);
		fwrite(bufferMas, 1, transferIndex, FOut);
		iterations=0;
		arrIndex=arrIndex+transferIndex;
		transferIndex=0;
	}
	transferIndex=ftell(FOut);
	printf("�㬬��� ࠧ��� ����ᠭ���� �����: %d ����\n",transferIndex);
	
	transformFileName(tempName, sizeof(tempName), headerNameSuffix, sizeof(headerNameSuffix), fileNameHdrDat);
	transformFileName(tempName, sizeof(tempName), headerBodySuffix, sizeof(headerBodySuffix), fileNameBodDat);
	transformFileName(tempName, sizeof(tempName), headerConvSuffix, sizeof(headerConvSuffix), fileNameTgtDat);
	
	free(bufferMas);
	fclose(FIn);
	fclose(FOut);
	storeStructToFile();
	return 0;
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
uint8_t createDataPacket(bool *arrIn, uint8_t *arrOut, uint8_t packetNumber)
{
	uint8_t arrPos=0;
	uint8_t packetRange=0;
	arrPos=arrPos=createBit(outArr, arrPos, tSP+tSB, separatorAmpHi, tSB);
	packetRange=arrPos;
	for(int i=0;i<8;i++)
	{
		if(arrIn[i]==0)
		{
			packetRange=packetRange+tFL+tSB;
			arrPos=createBit(outArr, arrPos, arrPos+tFL, dataAmplitudeHi, tSB);
		}
		else
		{
			packetRange=packetRange+tTR+tSB;
			arrPos=createBit(outArr, arrPos, arrPos+tTR, dataAmplitudeHi, tSB);
		}
	}
	arrPos=createBit(outArr, arrPos, arrPos+1, nullTerminator, 0);
	return arrPos-1;
}
inline uint8_t createBit(uint8_t *inputMas, uint8_t startAdr, uint8_t endAdr, uint8_t charToFill, uint8_t bitPauseRange)
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
uint32_t appendArray(uint8_t *arrToAppend, uint32_t reallocMemory, uint32_t bufferIndex)
{
	uint8_t inputArrIndexStart=0;
	char temp;
	while(bufferIndex<reallocMemory)
	{
		bufferMas[bufferIndex]=outArr[inputArrIndexStart];
		inputArrIndexStart++;
		bufferIndex++;
		temp=outArr[inputArrIndexStart];
		if(temp==nullTerminator)
		{
			return bufferIndex;
		}
	}
	return bufferIndex;
}
void storeStructToFile(void)																													//�㭪�� ����� ����஥� � 䠩�
{																																				//��砫� �㭪樨
	uint8_t crlfSign[2]={0x0D, 0x0A};																											//��⪠ CR LF(��७�� ���⪨ �� ����� ��ப�)
	bool WordConverted=1;																														//���樠�����㥬 䫠�
	char *FnameSrc="FSRC>";																														//��� ��室���� 䠩��
	char *FnameBod="FBOD>";																														//��� ⥫� 䠩��
	char *Fnametgt="FTGT>";																														//��� 䠩�� ��᫥ ᪫�������
	char *Fname="FNAM>";																														//��� 䠩��
	char *WordConvert="Convert=";																												//��ࠧ�� ⥣� Convert
	char *WordSampleRate="SampleRate=";																											//��ࠧ�� ⥣� SampleRate
	char *WordChannels="Channels=";																												//��ࠧ�� ⥣� Channels
	char *WordBitsPerSample="BitsPerSample=";																									//��ࠧ�� ⥣� BitsPerSample
	char *WordCountOfSamples="SamplesInChannel=";																								//��ࠧ�� ⥣� SamplesInChannel
	FSet=fopen("convertParams.ini", "wb");																										//���뢠�� 䠩� �� ������ ��� ������(��� ������? ��� ⥪�� �����)
	fseek(FSet, 0, SEEK_SET);																													//��⠭������� ����� �� 0
	fprintf(FSet, "%s", FnameSrc);																												//��襬 ⥣ FNAM
	fprintf(FSet, "%s", tempName);																												//��襬 ��� 䠩��
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
	fprintf(FSet, "%d", wavSampleRate);																											//��襬 ����� ����⨧�樨 �᫮�
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//��襬 CR LF
	fprintf(FSet, "%s", WordChannels);																											//��襬 ⥣ Channels
	fprintf(FSet, "%d", SoundChannels);																											//��襬 ������⢮ �������
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//��襬 CR LF
	fprintf(FSet, "%s", WordBitsPerSample);																										//��襬 ⥣ BitsPerSample
	fprintf(FSet, "%d", BitDepth);																												//��襬 ��㡨�� �롮ન
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//��襬 CR LF
	fprintf(FSet, "%s", WordCountOfSamples);																									//��襬 ⥣ BitsPerSample
	fprintf(FSet, "%d", summaryPacketLength);																									//��襬 ������⢮ �롮ப
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//��襬 CR LF
	fclose(FSet);																																//����뢠�� 䠩�
}																																				//����� �㭪樨
void transformFileName(char *sourceFileName, uint8_t sourceLenght, char *suffixToAttach, uint8_t suffixLength, char *arrToStore)				//�㭪�� �����஢���� ����� 䠩��
{																																				//��砫� ⥫� �㭪樨
	char tempMas[128];																															//���樠�����㥬 �६���� ����
	memset(tempMas,0x00,sizeof(tempMas));																										//� ��⨬ ���
	uint8_t filenameWithoutExtension=sourceLenght;																								//���樠������ ��६����� ����� ����� 䠩�� ��� ���७��
	uint8_t generatedFileNameWithSuffix;																										//���樠������ ��६����� ����� ᣥ���஢������ ����� 䠩��
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
	printf("����祭��� ��� 䠩��: ");																											//��襬 ᣥ���஢����� ��� 䠩��
	for(int i=0;i<generatedFileNameWithSuffix;i++)																								//��砫� 横�� ��७�� ����� 䠩�� �� �६������ ���ᨢ�
	{																																			//��砫� ⥫� 横��
		fileName[i]=tempMas[i];																													//��ᨬ����� ��७�� ����� 䠩��
		arrToStore[i]=tempMas[i];																												//�㡫��㥬 � ���ᨢ �� 㪠��⥫� ��� ����� �� ��砩���� ��������� � 室� ࠡ��� �ணࠬ�� �.� �ண� ���-� �������� ������⭮ ���
		printf("%c",arrToStore[i]);																												//� �ࠧ� �� �뢮� � ���᮫�
	}																																			//����� ⥫� 横��
	printf("\n");																																//��७�� ���⪨
}