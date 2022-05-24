#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#define scanSignalCorrect	4
#define bufferLength		32768
#define StartMsg			"v0.0.1 build 1\n"
#define codePageInfo 		"������ ������� ⠡��� �ਫ������ OEM CP-866\n"
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
uint8_t tSP;		//����� ������-��⥪�� �����
uint8_t tTR;		//����� ������ ���.1
uint8_t tFL;		//����� ������ ���.0
uint8_t tSB;		//����� ���� ����� ��ࠢ��� ��⮢
uint8_t tSPlow;
uint8_t tSPhigh;
uint8_t tTRlow;
uint8_t tTRhigh;
uint8_t tFLlow;
uint8_t tFLhigh;
uint8_t tSBlow;
uint8_t tSBhigh;
uint8_t chunksSum;
uint8_t resultByte=0x00;
uint16_t carrierFreq=12000;
uint16_t wavSampleRate=48000;
uint8_t *inputBuffer;
uint8_t *lasstBufferMas;
uint32_t packetConverter(uint8_t *sourceArray, uint32_t arrPos, uint16_t bufferSize);
int main(void)
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
		printf("��४��祭�� ������� ��࠭��� �� �ॡ����\n");
	}
	printf("WAV(����⭠� FM �������)->�८�ࠧ���⥫� �ଠ⮢ BIN \n");
	printf(StartMsg);
	printf("�� � ��栭�, � ᫥⥫ � �ࠣ� ⠪ �� ⥯��� �ண� ����॥ �㤥� �������. \n�ᥬ ��� �� ��⠫�� ᮡ�������\n");
	//FIn=fopen("test.wav","rb");
	//if(!FIn&&argc<2)
	//{
	//	printf("�� ������ 䠩� %s, ��� �� 㪠���� ��㬥���\n",argv[1]);
	//	exit(1);
	//}
	tSP=(wavSampleRate/carrierFreq)*pkgSeparatorTiming;
	tTR=(wavSampleRate/carrierFreq)*logTrueTiming;
	tFL=(wavSampleRate/carrierFreq)*logElseTiming;
	tSB=(wavSampleRate/carrierFreq)*bitSeparatorTiming;
	printf("������� �⮯-���: %d\n������� ���.0: %d\n������� ���.1: %d\n������� ���� ����� ��ࠢ��� ��⮢: %d\n",tSP,tFL,tTR,tSB);
	printf("f(����)=%d\nf(�����)=%d\n",wavSampleRate,carrierFreq);
	printf("�������� ࠧ��� ����� �����ᮢ %d tau\n",pulseDeviation*2);
	tSPlow=tSP-pulseDeviationMinus;
	tSPhigh=tSP+pulseDeviationPlus;
	tTRlow=tTR-pulseDeviationMinus;
	tTRhigh=tTR+pulseDeviationPlus;
	tFLlow=tFL-pulseDeviationMinus;
	tFLhigh=tFL+pulseDeviationPlus;
	tSBlow=tSB-pulseDeviationMinus;
	tSBhigh=tSB+pulseDeviationPlus;
	printf("������� �⮯-���: %d...%d\n������� ���.0: %d...%d\n������� ���.1: %d...%d\n������� ����: %d...%d\n",tSPlow,tSPhigh,tFLlow,tFLhigh,tTRlow,tTRhigh,tSBlow,tSBhigh);
	FIn=fopen("test.wav","rb");
	if(!FIn)
	{
		printf("�� ������ 䠩� <NULL>, ��� �� 㪠���� ��㬥���\n");
		exit(1);
	}
	printf("����� ������⢮ 砭��� 䠩��, ������ ��᫥����: ");
	scanf("%d",&numberOfIterations);
	printf("������⢮ 砭���, ������ ��᫥����: %d\n",numberOfIterations);
	for(uint8_t i=0;i<numberOfIterations;i++)
	{
		printf("����� ࠧ��� 砭�� �%d: ",i);
		scanf("%d",&chuksEnum[i]);
		printf("\n");
	}
	printf("����� ࠧ��� ��᫥����� 砭�� 䠩��: ");
	scanf("%d",&lastChunkSize);
	printf("�������� ࠧ��� ��᫥����� 砭��: %d ����\n",lastChunkSize);
	printf("�������� ࠧ���� 砭���:\n");
	for(uint8_t i=0;i<numberOfIterations;i++)
	{
		printf("�%d: %d\n",i,chuksEnum[i]);
	}
	fseek(FIn,0,SEEK_END);
	//fileSize=ftell(FIn);
	//modOfDiv=fmod(fileSize, bufferLength);
	//printf("������ ����� ���⮢(RAW): %f\n",modOfDiv);
	//roundedVal=round(modOfDiv);
	//printf("������ ����� ���⮢: %d\n", roundedVal);
	//numberOfIterations=(fileSize-modOfDiv)/bufferLength;
	if(roundedVal!=0)
	{
		numberOfIterations++;
	}
	printf("�㬬�୮� ������⢮ ������: %d\n",numberOfIterations);
	lasstBufferMas=malloc(roundedVal);
	FOut=fopen("test","wb");
	fileIndex=fileIndex+43;
	fseek(FOut,fileWriteIndex,SEEK_SET);
	for(uint8_t steps=0;steps<numberOfIterations;steps++)
	{
		if(steps<numberOfIterations-1)
		{
			printf("������஢���� 䠩��, ��室 %d, 㪠��⥫� 砭�� �� �室��� ��⮪� %d, 㪠��⥫� 砭�� �� ��室��� ��⮪� %d\n",steps,fileIndex,fileWriteIndex);
		}
		else
		{
			printf("������஢���� 䠩��(���⮪), ��室 %d, 㪠��⥫� 砭�� �� �室��� ��⮪� %d, 㪠��⥫� 砭�� �� ��室��� ��⮪� %d\n",steps,fileIndex,fileWriteIndex);
			stopRead=lastChunkSize;
			//break;
		}
		memset(decodeBuffer,0x00,sizeof(decodeBuffer));
		memset(inputBuffer,0x00,bufferLength);
		fseek(FIn,fileIndex,SEEK_SET);
		fread(inputBuffer,1,chuksEnum[steps],FIn);
		bufferPos=1;
		while(1)
		{	
			bufferPos=packetConverter(inputBuffer, bufferPos, bufferLength);
			decodeBuffer[decodeBufIndx]=resultByte;
			//printf("%d 0x%02X\n",decodeBufIndx,resultByte);
			if(decodeBufIndx==stopRead)
				break;	
			decodeBufIndx++;
		}
		fwrite(decodeBuffer,1,sizeof(decodeBuffer),FOut);
		decodeBufIndx=0;
		fileIndex=fileIndex+bufferPos;
		fileWriteIndex=fileWriteIndex+sizeof(decodeBuffer);
	}
}
uint32_t packetConverter(uint8_t *sourceArray, uint32_t arrPos, uint16_t bufferSize)
{
	//printf("����� �%d, ᮤ�ন��� ���ᨢ� �� ������� %d 0x%02X\n",i,i,sourceArray[i]);
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
	//printf("������ ���� ������ %d ����\n",bufferSize);
	/*printf("���� ������-��⥪��, �।��������� ��������: %d...%d\n",arrPos-pulseDeviation,arrPos+tSPhigh);*/
	for(uint32_t i=arrPos-pulseDeviation;i<arrPos+tSPhigh;i++){byteCount++;
		if(sourceArray[i]==dataAmplitudeHi){
			if((byteCount>=tSPlow)&&(lowLimTrig!=1)){lowLimTrig=1;}}
		else if(sourceArray[i]==byteInvert){
			if((byteCount<=tSPhigh)&&(sourceArray[i]==byteInvert)&&(higLimTrig!=1)){byteCount--;
				higLimTrig=1;}}
		if((lowLimTrig&&higLimTrig)==1){/*printf("������-��⥪�� ������ %d...%d\n",arrPos,i);*/
			arrPos=i+1;
			break;}}
	lowLimTrig=0;
	higLimTrig=0;
	byteCount=0;
	/*printf("���� ����, �।��������� ��������: %d...%d\n",arrPos-pulseDeviation,arrPos+tSBhigh);*/
	for(uint32_t i=arrPos-pulseDeviation;i<arrPos+tSBhigh;i++){byteCount++;
		if(sourceArray[i]==byteInvert){
			if((byteCount>=tSBlow)&&(lowLimTrig!=1)){lowLimTrig=1;}}
		else if(sourceArray[i]==dataAmplitudeHi){
			if((byteCount<=tSBhigh)&&(sourceArray[i]==dataAmplitudeHi)&&(higLimTrig!=1)){byteCount--;
				higLimTrig=1;}}
		if((lowLimTrig&&higLimTrig)==1){/*printf("��㧠 ������� %d...%d\n",arrPos,i);*/
			arrPos=i+1;
			break;}}
	lowLimTrig=0;
	higLimTrig=0;
	byteCount=0;
	arrPos=arrPos+3;
	while(bitProceed>-1){
		/*printf("���� ��� %d/7 �।��������� ��������: %d...%d\n",bitProceed,arrPos-pulseDeviation,arrPos+tSBhigh);*/
		for(uint32_t i=arrPos-pulseDeviation;i<arrPos+tFLhigh+pulseDeviation;i++){byteCount++;
			if((sourceArray[i]==dataAmplitudeHi)&&(lowLimTrig!=1)){bitTrig++;
				lowLimTrig=1;}
			else if((sourceArray[i]==byteInvert)&&(lowLimTrig==1)&&(higLimTrig==0)){higLimTrig=1;
				bitTrig--;}if(bitTrig==1){pulseCounter++;}
			if((higLimTrig==1)&&(lowLimTrig==1)){arrPos=i+1;
				break;}}
		if(pulseCounter==tTR)
			bitArr[bitProceed]=1;
		if(pulseCounter==tFL)
			bitArr[bitProceed]=0;
		lowLimTrig=0;
		higLimTrig=0;
		byteCount=0;
		pulseCounter=0;
		bitProceed--;
		/*printf("���� ����, �।��������� ��������: %d...%d\n",arrPos-pulseDeviation,arrPos+tSBhigh);*/
		for(uint32_t i=arrPos-pulseDeviation;i<arrPos+tSBhigh;i++){byteCount++;
			if(sourceArray[i]==byteInvert){
				if((byteCount>=tSBlow)&&(lowLimTrig!=1)){lowLimTrig=1;}}
			else if(sourceArray[i]==dataAmplitudeHi){
				if((byteCount<=tSBhigh)&&(sourceArray[i]==dataAmplitudeHi)&&(higLimTrig!=1)){byteCount--;
					higLimTrig=1;}}
			if((lowLimTrig&&higLimTrig)==1){/*printf("��㧠 ������� %d...%d\n",arrPos,i);*/
				arrPos=i+1;
				break;}}
		lowLimTrig=0;
		higLimTrig=0;
		byteCount=0;}
	arrPos=arrPos-3;
	//printf("Value to return: %d\n",arrPos);
	if(resultByte!=0)
		resultByte=0x00;
	for(uint8_t i=0;i<8;i++)
	{resultByte=resultByte|bitArr[7-i]<<i;}
	return arrPos;
}
