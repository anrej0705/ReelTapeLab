//Exheader - ¯à®£à ¬¬  ¯à¥¤­ §­ ç¥­  ¤«ï ¨§¢«¥ç¥­¨ï § £®«®¢ª  ¨§ WAV ä ©«  ¤«ï ¤ «ì­¥©è¥© à ¡®âë á ­¨¬ - ¬®¤¨ä¨ª æ¨¥© ¨ § ¯¨áìî ¢ ­®¢ë© ä ©«
//”®à¬ â § £®«®¢ª  ¤®«¦¥­ ¡ëâì á«¥¤ãîé¨¬ RIFFeeeeWAVEfmt kkkkgghhrrrryyyyooqqppppzzzz
// RIFF - ¬¥âª  ä®à¬ â  ä ©« , DWORD 4 ¡ ©â 
// eeee - à §¬¥à ¢á¥£® ä ©«  ¢ ¡ ©â å DWORD 4 ¡ ©â 
// WAVE - ®¡®§­ ç¥­¨¥ çâ® ä ©« §¢ãª®¢®© DWORD 4 ¡ ©â 
// fmt  - ®¡®§­ ç¥­¨¥ çâ® ¤ «ìè¥ ¡ã¤ãâ ¤¥â «¨ ® ä ©«¥ DWORD 4 ¡ ©â , ¯®á«¥¤­¨© á¨¬¢®« ­¥®â®¡à ¦ ¥âáï - 0x20 WORD 2 ¡ ©â 
// kkkk - ¤«ï ä®à¬ â  ˆŠŒ(PCM) DWORD 4 ¡ ©â 
// gg - §¤¥áì ãª § ­ ª®¤¥ª, ®¡ëç­® ˆŠŒ(PCM) WORD 2 ¡ ©â 
// hh - §¤¥áì ãª § ­® ª®«¨ç¥áâ¢® ª ­ «® WORD 2 ¡ ©â 
// rrrr - ç áâ®â  ¤¨áªà¥â¨§ æ¨¨ ¢ £¥àæ å DWORD 4 ¡ ©â 
// yyyy - áª®à®áâì ¯¥à¥¤ ç¨ ¤ ­­ëå ¢ ¡ ©â å ¢ á¥ªã­¤ã DWORD 4 ¡ ©â 
// oo - ª®«¨ç¥áâ¢® ¡ ©â ¤«ï ®¤­®© ¢ë¡®àª¨ ¢ª«îç ï ¢á¥ ª ­ «ë WORD 2 ¡ ©â 
// qq - £«ã¡¨­  ¢ë¡®àª¨ ¢ ¡¨â å WORD 2 ¡ ©â 
// data - ¬¥âª  ®¡®§­ ç îé ï çâ® ¤ «ìè¥ ¡ã¤ãâ ¤ ­­ë¥ DWORD 4 ¡ ©â 
// zzzz - à §¬¥à ä ©«  ¬¨­ãá à §¬¥à § £®«®¢ª  DWORD 4 ¡ ©â 
//®á«¥ ¨§¢«¥ç¥­¨ï § £®«®¢ª  ¯à®£à ¬¬  £¥­¥à¨àã¥â ä ©« convertParams.ini ¢ ª®â®à®¬ á®¤¥à¦ âáï
// ¯®¬¥ç¥­­®¥ â¥£ ¬¨ FSRC-FSND ¨áå®¤­®¥ ¨¬ï ä ©« 
// ¯®¬¥ç¥­­®¥ â¥£ ¬¨ FBOD-FBND ¨¬ï ª®­â¥©­¥à  wav ¤ ­­ëå
// ¯®¬¥ç¥­­®¥ â¥£ ¬¨ FHDT-FHND ¨¬ï ä ©«  á § £®«®¢ª®¬, § ¯¨á ­­ë¬ íâ®© ¯à®£à ¬¬®©
// ¯®¬¥ç¥­­®¥ â¥£ ¬¨ FTGT-FTND ¨¬ï ª®­¥ç­®£® ä ©« 
// ä« £ á®áâ®ï­¨ï ª®­¢¥àâ æ¨¨ - 0(­¥ ª®­¢¥àâ¨à®¢ ­), 1(ª®­¢¥àâ¨à®¢ ­)
// ç áâ®âã ¤¨áªà¥â¨§ æ¨¨ ä ©«  ¢ £¥àæ å
// ª®«¨ç¥áâ¢® ª ­ «®¢ ¢ ä ©«¥
// £«ã¡¨­ã ¢ë¡®àª¨
// ª®«¨ç¥áâ¢® ¢ë¡®à®ª ¢ ®¤­®¬ ª ­ «¥
//Š ¦¤ë© § ¯ãáª ¯à®£à ¬¬  ¯à®¢¥àï¥â ­ «¨ç¨¥ ä ©«  convertParams.ini ¨ ¥á«¨
//­¥ ­ å®¤¨â â® á®§¤ ¥â ­®¢ë©.  ©¤ï íâ®â ä ©«, ®­  ®âªàë¢ ¥â ¥£® ¨ ¢ ¯¥à¢ãî
//®ç¥à¤ì ¯à®¢¥àï¥â ä« £ ª®­¢¥àâ æ¨¨. …á«¨ 0 - ¯à®£à ¬¬  § ¢¥àè ¥â à ¡®âã
//¥á«¨ 1 â® ¯à®£à ¬¬  ç¨â ¥â ®áâ «ì­ë¥ ¤ ­­ë¥, ¢ª«îç ï ¨¬ï ä ©«  § £®«®¢ª 
//¨ á®§¤ ¥â ä ©« á®£« á­® § ¯¨á ­­®¬ã ¨¬¥­¨ ¯®á«¥ â¥£  FHDT. „ «¥¥ ¯à®£à ¬¬ 
//¨§ ¯à®ç¨â ­­ëå ¤ ­­ëå ä®à¬¨àã¥â ¬¨­¨¬ «ì­ë© § £®«®¢®ª ¨ § ¯¨áë¢ ¥â ¥£® ¢ ä ©«
#include<locale.h>																																//¨¡«¨®â¥ª  «®ª «¨§ æ©, ­ã¦­  ¤«ï àãááª®£® ï§ëª  ¢ ª®­á®«¨
#include<stdbool.h>																																//¨¡«¨®â¥ª  ¤«ï à ¡®âë á ¤¢®¨ç­ë¬¨ ç¨á« ¬, C99
#include<stdint.h>																																//¨¡¨«®â¥ª  ¤«ï à ¡®âë á ­¥áâ ­¤ àâ­ë¬¨ ç¨á« ¬¨ uint8_t, uint16_t, uint32_t
#include<stdio.h>																																//¨¡«¨®â¥ª  ¤«ï à ¡®âë á ª®­á®«ìî, ¢ë¢®¤ ¢ ª®­á®«ì ¨ áç¨âë¢ ­¨¥ á ­¥¥
#include<conio.h>																																//¨¡¨«®â¥ª  ¤«ï à ¡®âë á ¢¢®¤®¬
#include<stdlib.h>																																//¨¡¨«®â¥ª  â¨¯®¢ ¯¥à¥¬¥­­ëå
#include<string.h>																																//¨¡«¨®â¥ª¥ á¨¬¢®«ì­ëå ¯¥à¥¬¥­­ëå
#include<windows.h>
#include "debug.h"																																//¨¡«¨®â¥ª  ®â« ¤®ç­ëå á®®¡é¥­¨©
#define codePageInfo 				"‡ ¤ ­  ª®¤®¢ ï â ¡«¨æ  ¯à¨«®¦¥­¨ï OEM CP-866\n"
#define StartMsg					"\nv0.2.7 build 41\n"																						//‘®®¡é¥­¨¥ ¤«ï ¢ë¢®¤  ¢ ª®­á®«ì, 1 ç áâì
#define StartMsgTwo					"„ ­­ ï ¯à®£à ¬¬  ï¢«ï¥âáï ª®¬¯®­¥­â®¬ ¨ á ¬  ¯® á¥¡¥ ­¥ ¨¬¥¥â á¬ëá« \n\n"									//‘®®¡é¥­¨¥ ¤«ï ¢ë¢®¤  ¢ ª®­á®«ì, 2 ç áâì
#define FileSizeMsg					" §¬¥à ä ©« , ¯®«­ë©: %d  ©â\n"																			//‘®®¡é¥­¨¥ ¤«ï ¢ë¢®¤  à §¬¥à  ä ©« 
#define FileSizeWoutHeaderMsg		" §¬¥à ä ©«  ¡¥§ ãç¥â  § £®«®¢ª : %d  ©â\n"																//‘®®¡é¥­¨¥ ¤«ï ¢ë¢®¤  à §¬¥à  ä ©«  ¡¥§ § £®«®¢ª 
#define SampleRateMsg				"— áâ®â  ¤¨áªà¥â¨§ æ¨¨: %d ƒæ\n"																			//‘®®¡é¥­¨¥ ¤«ï ¢ë¢®¤  ç áâ®âë ¤¨áªà¥â¨§ æ¨¨
#define ByteRateMsg					"‘ª®à®áâì ¯¥à¥¤ ç¨ ¤ ­­ëå: %d  ©â/á\n"																		//‘®®¡é¥­¨¥ ¤«ï ¢ë¢®¤  áª®à®áâ¨ ¯¥à¥¤ ç¨ ¤ ­­ëå ¢ ¡ ©â å
#define BitDepthMsg					"ƒ«ã¡¨­  ¢ë¡®àª¨: %d ¨â\n"																					//‘®®¡é¥­¨¥ ¤«ï ¢ë¢®¤  £«ã¡¨­ë ¢ë¡®àª¨
#define ChannelsMsg					"Š®«¨ç¥áâ¢® ª ­ «®¢: %d"																					//‘®®¡é¥­¨¥ ¤«ï ¢ë¢®¤  ª®«¨ç¥áâ¢  ª ­ «®¢
#define BytesInSampleMsg			"Š®«¨ç¥áâ¢® ¡ ©â ¢ ®¤­®© ¢ë¡®àª¥ á® ¢á¥å ª ­ «®¢: %d  ©â\n"												//‘®®¡é¥­¨¥ ¤«ï ¢ë¢®¤  ª®«¨ç¥áâ¢® ¡ ©â ¢ ¢ë¡®àª¥ á® ¢á¥å ª ­ «®¢ áà §ã
#define CodecTypeMsg				"’¨¯ ª®¤¨à®¢ ­¨ï §¢ãª :"																					//‘®®¡é¥­¨¥ ¤«ï ¢ë¢®¤  â¨¯  ª®¤¨à®¢ ­¨ï §¢ãª  ¢ ä ©«¥
const uint8_t wordFilenameShift=4;																												//‘¬¥é¥­¨¥ ¢ ¡ ©â å ¤® á ¬®£® ¯ à ¬¥âà 
const uint8_t wordConvertShift=7;																												//‘¬¥é¥­¨¥ ¢ ¡ ©â å ¤® á ¬®£® ¯ à ¬¥âà 
const uint8_t wordSampleRateShift=10;																											//‘¬¥é¥­¨¥ ¢ ¡ ©â å ¤® á ¬®£® ¯ à ¬¥âà 
const uint8_t wordChannelsShift=8;																												//‘¬¥é¥­¨¥ ¢ ¡ ©â å ¤® á ¬®£® ¯ à ¬¥âà 
const uint8_t wordBitsPerSampleShift=13;																										//‘¬¥é¥­¨¥ ¢ ¡ ©â å ¤® á ¬®£® ¯ à ¬¥âà 
const uint8_t wordSamplesValueShift=16;																											//‘¬¥é¥­¨¥ ¢ ¡ ©â å ¤® á ¬®£® ¯ à ¬¥âà 
const uint16_t pcmFormat=0x0001;
const uint32_t RIFFsignature=0x52494646;																										//¬¥âª  RIFF, ®¡à §¥æ
const uint32_t WAVEsignature=0x57415645;																										//¬¥âª  WAVE, ®¡à §¥æ
const uint32_t fmtSignature=0x666D7420;																											//¬¥âª  fmt , ®¡à §¥æ
const uint32_t dataSignature=0x64617461;																										//¬¥âª  data, ®¡à §¥æ
const uint32_t dataFormatLength=0x00000010;
char headerNameSuffix[11]="_header.dat";																										//áãää¨ªá ª ¨¬¥­¨ ¯à¥®¡à §ã¥¬®£® ä ©« 
char headerBodySuffix[9]="_body.dat";																											//áãää¨ªá ª ¨¬¥­¨ ¯à¥®¡à §ã¥¬®£® ä ©« 
char headerConvSuffix[9]="_conv.wav";																											//áãää¨ªá ª ¨¬¥­¨ ¯à¥®¡à §ã¥¬®£® ä ©« 
char fileMassive[256];																															//¬ áá¨¢ ¢ ª®â®àë© ç¨â ¥âáï á®¤¥à¦¨¬®¥ ä ©«  convertParams.ini
char fileNameRAW[128];																															//¬ áá¨¢, ¢ ª®â®à®¬ åà ­¨âáï ¨¬ï ä ©«  ¢ª«îç ï ¯ãâì
char fileNameSrc[64];																															//¬ áá¨¢ á ¨¬¥­¥¬ ¨áå®¤­®£® ä ©« 
char fileNameHdrDat[64];																														//¬ áá¨¢ á ¨¬¥­¥¬ § £®«®¢®ç­®£® ä ©« 
char fileNameBodDat[64];																														//¬ áá¨¢ á ¨¬¥­¥¬ § £®«®¢®ç­®£® ä ©« 
char fileNameTgtDat[64];																														//¬ áá¨¢ á ¨¬¥­¥¬ § £®«®¢®ç­®£® ä ©« 
char fileName[64];																																//¬ áá¨¢ á ¨¬¥­¥¬ ä ©« 
char *wordFilenameSource="FSRC";																												// §¢ ­¨¥ ¤«ï ¯ à ¬¥âà  ¨¬¥­¨ ä ©« 
char *wordFilenameBody="FBOD";		   																											// §¢ ­¨¥ ¤«ï ¯ à ¬¥âà  ¨¬¥­¨ ä ©« 
char *wordFilename="FNAM";																														// §¢ ­¨¥ ¤«ï ¯ à ¬¥âà  ¨¬¥­¨ ä ©« 
char *wordFilenameTarget="FTGT";																												// §¢ ­¨¥ ¤«ï ¯ à ¬¥âà  ¨¬¥­¨ ä ©« 
char *wordSrcFilenameEnd=">FSND";																												// §¢ ­¨¥ ¤«ï ¯ à ¬¥âà  ¨¬¥­¨ ä ©« 
char *wordNameFilenameEnd=">FNND";																												// §¢ ­¨¥ ¤«ï ¯ à ¬¥âà  ¨¬¥­¨ ä ©« 
char *wordBodyFilenameEnd=">FBND";																												// §¢ ­¨¥ ¤«ï ¯ à ¬¥âà  ¨¬¥­¨ ä ©« 
char *wordTargFilenameEnd=">FTND";																												// §¢ ­¨¥ ¤«ï ¯ à ¬¥âà  ¨¬¥­¨ ä ©« 
char *wordConvert="Convert";																													// §¢ ­¨¥ ¤«ï ä« £  á®áâ®ï­¨ï ª®­¢¥àâ æ¨¨
char *wordSampleRate="SampleRate";																												// §¢ ­¨¥ ¤«ï ¯ à ¬¥âà  ç áâ®âë ¤¨áªà¥â¨§ æ¨¨
char *wordChannels="Channels";																													// §¢ ­¨¥ ¤«ï ¯ à ¬¥âà  ª®«¨ç¥áâ¢  ª ­ «®¢
char *wordBitsPerSample="BitsPerSample";																										// §¢ ­¨¥ ¤«ï ¯ à ¬¥âà  ®¡®§­ ç îé¥£® ª®«¨ç¥áâ¢® ¡¨â ¢ ¢ë¡®àª¥
char *WordCountOfSamples="SamplesInChannel";																									// §¢ ­¨¥ ¤«ï ¯ à ¬¥âà  ®¡®§­ ç îé¥£® ª®«¨ç¥áâ¢® ¢ë¡®à®ª
char *cursorSymbol;																																// à ¬¥âà ¢ ª®â®àë© ¡ã¤¥â ¯¨á âìáï ¯®§¨æ¨ï ªãàá®à  á ª®â®à®£® ­ ç¨­ ¥âáï ¨áª®¬®¥ á«®¢®
uint8_t fileLength;																																//Ž¡é ï ¯¥à¥¬¥­­ ï ¤«ï åà ­¥­¨ï ¨­ä®à¬ æ¨¨ ® ¤«¨­¥ ä ©« 
uint32_t cursorPosit;																															//®§¨æ¨ï ªãàá®à  ¤® ­ ç «  ç¨á«  ¯ à ¬¥âà 
uint32_t wordFsrcPos;																															//®§¨æ¨ï â¥£  FSRC
uint32_t wordFnamePos;																															//®§¨æ¨ï â¥£  FNAM
uint32_t wordConvertPos;																														//‘î¤  ¯¨è¥âáï ¯®§¨æ¨ï, ­  ª®â®àãî ­ã¦­® ¢ëáâ ¢¨âì ªãàá®à ¤«ï çâ¥­¨ï ¯ à ¬¥âà  FSetWasConverted 
uint32_t wordSampleRatePos;																														//‘î¤  ¯¨è¥âáï ¯®§¨æ¨ï, ­  ª®â®àãî ­ã¦­® ¢ëáâ ¢¨âì ªãàá®à ¤«ï çâ¥­¨ï ¯ à ¬¥âà  FSetSampleRate
uint32_t wordChannelsPos;																														//‘î¤  ¯¨è¥âáï ¯®§¨æ¨ï, ­  ª®â®àãî ­ã¦­® ¢ëáâ ¢¨âì ªãàá®à ¤«ï çâ¥­¨ï ¯ à ¬¥âà  FSetChannels
uint32_t wordBitsPerSamplePos;																													//‘î¤  ¯¨è¥âáï ¯®§¨æ¨ï, ­  ª®â®àãî ­ã¦­® ¢ëáâ ¢¨âì ªãàá®à ¤«ï çâ¥­¨ï ¯ à ¬¥âà  FSetBitDepth
uint32_t wordSamplesValuePos;																													//áî¤  ¡ã¤¥â ¯¨á âìáï ª®«¨ç¥áâ¢® ¢ë¡®à®ª ¢ 1 ª ­ «¥ ä ©« 
bool DebugMode=1;																																//à¥¦¨¬ ®â« ª¤¨, 1 - ¢ª«, 0 - ¢ëª«
bool analyzeState;																																//á®áâ®ï­¨¥ äã­ªæ¨¨ çâ¥­¨ï, 1 - ¢á¥ å®à®è®, 0 - £¤¥-â® á«ãç¨« áì ®è¨¡ª 
bool convertState;																																//á®áâ®ï­¨¥ äã­ªæ¨¨ ¯à¥®¡à §®¢ ­¨  ¨ § ¯¨á¨ ¢ áâàãªâãàã, 1 - ¢á¥ å®à®è®, 0 - £¤¥-â® á«ãç¨« áì ®è¨¡ª 
bool cruzo;																																		//á®áâ®ï­¨¥ áç¨âë¢ ¥¬®¥ á ä ©«  convertParams.ini
bool ahsoka;																																	//á®áâ®ï­¨¥ äã­ªæ¨¨ ¯à®¢¥àª¨ ¯à ¢¨«ì­®áâ¨ ¤ ­­ëå ¢ áâàãªâãà¥, 1 - ¢á¥ å®à®è®, 0 - ¤ ­­ë¥ ¢ áâàãªâãà¥ ­¥ á®¢¯ ¤ îâ á ®¡à §æ ¬¨, § ª®­ç¨« áì ä ­â §¨ï ­  ¨¬¥­ 
bool gabella;																																	//¥á«¨ 1 - ¨­ä®à¬ æ¨ï ¢ § £®«®¢®ª ãá¯¥è­® § ¯¨á ­ , ¥á«¨ 0 - ¯à®¨§®è«® çâ®-â® â ª®¥ çâ® ­¥ ¤ «® § ¯¨á âì
bool Egor;																																		//á®áâ®ï­¨¥ äã­ªæ¨¨ çâ¥­¨ï ¨§ ä ©«  convertParams.ini
bool doubledoor;																																//ãª § â¥«ì á®áâ®ï­¨ï § ¯¨á¨ ¢ ä ©«, ¥á«¨ 1 â® ¢á¥ å®à®è®, ¥á«¨ 0 â® ä ©« ­¥ ¡ë« § ¯¨á ­
bool argFound=0;
FILE* FSet;																																		//“ª § â¥«ì ­  ä ©« á ¯ à ¬¥âà ¬¨ § £®«®¢ª 
FILE* FRd;																																		//“ª § â¥«ì ­  ä ©« á ª®â®à®£® ¢á¥ ¡ã¤¥â ç¨â âìáï
FILE* FWr;																																		//“ª § â¥«ì ­  ä ©« ¢ ª®â®àë© ¡ã¤¥â ¨¤â¨ § ¯¨áì, ¯®ª  ¢ ª®¤¥ ­¥ ¯à¨¬¥­¥­
const int HeaderSize=44;																														//¯ à ¬¥âà ¤«¨­ë § £®«®¢ª  ¢ ¡ ©â å(®â 0 ¡ ©â  ¤® ­ ç «  á ¬¨å ¤ ­­ëå WAVE), § £®«®¢®ª ¨¬¥¥â ¢á¥£¤  ®¤­ã ¨ âã ¦¥ ¤«¨­ã
int headerAddrs[14]={0,4,8,12,16,20,22,24,28,32,34,36,40,44};																					//á¯¨á®ª  ¤à¥á®¢ ¢ § £®«®¢ª¥ á ª®â®àëå ­ã¦­® ç¨â âì ¯ à ¬¥âàë ä ©« 
int headerWordSizeOf[13]={sizeof(uint32_t),sizeof(uint32_t),sizeof(uint32_t),sizeof(uint32_t),													//á¯¨á®ª ¤«¨­­ á«®¢, ç¨â ¥¬ëå ¨§ § £®«®¢ª (á¯¨á®ª á¢ï§ ­ á headerAddrs ¨ headerWordInvert)
						sizeof(uint32_t),sizeof(uint16_t),sizeof(uint16_t),sizeof(uint32_t),													//§¤¥áì ï á«®¢¨« è¨§ã
						sizeof(uint32_t),sizeof(uint16_t),sizeof(uint16_t),sizeof(uint32_t),
						sizeof(uint32_t)};																										//á¯¨á®ª ª®â®àë© á®¤¥à¦¨â ¤«¨­ã ª ¦¤®£® ¯ à ¬¥âà  ¢ ¡ ©âå
int headerWordInvert[13]={1,0,1,1,0,0,0,0,0,0,0,1,0};																							//á¯¨á®ª ¤«ï äã­ªæ¨¨, ¨§¬¥­ïîé¨© ¯®àï¤®ª ¡ ©â®¢ - á ª®­æ  ¨«¨ á ­ ç « 
int headerDebugPrintParameters[13]={0,0,0,0,0,1,1,0,0,1,1,0};																					//á¯¨á®ª â¨¯®¢ á®®¡é¥­¨© ¢ë¢®¤  ¤«ï äã­ªæ¨¨ ¢ë¢®¤  ®â« ¤®ç­ëå ¯ à ¬¥âà®¢
uint8_t FileHeader[44];																															//áî¤  ¯¥à¥¯¨áë¢ ¥âáï § £®«®¢®ª
uint8_t ByteBuffer[4];																															//§¤¥áì åà ­¨âáï ¯ à ¬¥âà § £®«®¢ª  çâ®¡ë ª ¦¤ë© à § ­¥ ®¡à é âìáï ª ®á­®¢­®¬ã ¬ áá¨¢ã
uint8_t headerReader(void);																														//äã­ªæ¨ï çâ¥­¨ï § £®«®¢ª  ¢ áâàãªâãàã
uint8_t massiveSwap(bool swapState);																											//äãª­æ¨ï ¨§¬¥­¥­¨ï ¯®àï¤ª  á«¥¤®¢ ­¨ï ¡ ©â®¢
uint8_t sByteConverter(uint32_t wordToConvert);																									//äã­ªæ¨ï ¯®­¨¦¥­¨ï à §àï¤­®áâ¨
uint8_t GetFileName(char* nameOfFile);																											//äã­ªæ¨ï ¯®«ãç¥­¨ï ¨¬¥­¨ ä ©« (­  á ¬®¬ ¤¥«¥ ®­  ­¨ç¥£® ­¥ ¯®­¨¦ ¥â)
uint16_t dByteConverter(uint32_t wordToConvert);																								//äã­ªæ¨ï ¯®­¨¦¥­¨ï à §àï¤­®áâ¨(á 32 ¤® 16 ¡¨â)
uint32_t qByteConverter(uint32_t wordToConvert);																								//äã­ªæ¨ï ¯®­¨¦¥­¨ï à §àï¤­®áâ¨(á 32 ¤® 8 ¡¨â)
uint32_t byteConverter(int startOffset, int endOffset, int ByteLenght, bool invertState);														//äã­ªæ¨ï ¤«ï ¯à¥®¡à §®¢ ­¨ï ­ã¦­®© ç áâ¨ á®¤¥à¦¨¬®£®  ¬ áá¨¢  ¢ ®¤­® á«®¢® á à §­®© ¤«¨­­®©
uint32_t structFiller(int structShift, uint32_t paramToWrite);																					//äã­ªæ¨ï § ¯¨á¨ ¢ áâàãªâãàã
uint32_t writeBuffer(int startOffset, int endOffset, uint32_t paramToWrite, int wordSize, bool SwapByte);										//äã­ªæ¨ï § ¯¨á¨ ¨§¬¥­¥­­®© áâàãªâãàë ¢ ¬ áá¨¢, ¯®¤£®â®¢ª  ª § ¯¨á¨ ¢ ä ©«
void transformFileName(char *sourceFileName, uint8_t sourceLenght, char *suffixToAttach, uint8_t suffixLength, char *arrToStore);				//äã­ªæ¨ï £¥­¥à æ¨¨ ¨¬¥­¨ ä ©«  ¨§ ¯®«ãç¥­­®£® ¨áå®¤­¨ª 
void storeStructToFile();																														//äã­ªæ¨ï ¤«ï § ¯¨á¨ ¯ à ¬¥âà®¢ § £®«®¢ª  ¢ ®â¤¥«ì­ë© ä ©« ¢ ¢¨¤¥ áâàãªâãàë
void checkStatus(uint8_t statusCode);																											//äã­ªæ¨ï ¤«ï ¯à®¢¥àª¨ á®áâ®ï­¨ï ¢ëå®¤  ¨§ ¤àã£¨å äã­ªæ¨©, ¤«ï ®¡­ àã¦¥­¨ï ®è¨¡ª¨
void structAnalyzer(void);																														//äã­ªæ¨ï ¤«ï ¯à®¢¥àª¨ áâàãªâãàë ¨ ¢ë¢®¤  ¥¥ á®¤¥à¦¨¬®£®
void structModifier(void);																														//äã­ªæ¨ï ¤«ï ¬®¤¨ä¨ª æ¨¨ áâàãªâãàë
void clearByteBuffer(void);																														//®ç¨áâª  ¡ãä¥à  ¯®á«¥ à ¡®âë
void clearHeaderBuffer(void);																													//®ç¨áâª  ¡ãä¥à  § £®«®¢ª  ¯®á«¥ ®¯¥à æ¨¨ çâ¥­¨ï ä ©« 
void writeDebugHeaderBuffer(void);																												//§ ¯¨áì ¡ãä¥à á®¤¥à¦¨¬®¥ ª®â®à®£® ¢ë¢®¤¨âáï ¢ ®â« ¤®ç­ëå æ¥«ïå
void BufferReader(void);																														//äã­ªæ¨ï-§ âëçª  ¤«ï ®â« ¤®ç­ëå æ¥«¥©
void printHelpMsg(void);																														//äã­ªæ¨ï-á¯à ¢ª  ¢ á«ãç ¥ ¯ãáâ®£® ¢ë§®¢  ¨«¨ ¢ë§®¢  ¯® ª®¬ ­¤ ¬ -h.-H,-help,-HELP
void generateHead(void);
int WriteSettingsFile(void);																													//äã­ªæ¨ï § ¯¨áë¢ îé ï ¯ à ¬¥âàë ¯à¥®¡à §®¢ ­¨ï
int ReadSettingsFile(void);																														//äã­ªæ¨ï áç¨âë¢ îé ï ¯ à ¬¥âàë ¯à¥®¡à §®¢ ­¨ï
struct WaveHeader																																//áâàãªâãà , ¢ ª®â®àãî ¡ã¤¥â ¯¨á âìáï ¨­ä®à¬ æ¨ï á § £®«®¢ª  ä ©« 
{																																				//­ ç «® áâàãªâãàë § £®«®¢ª 
	uint32_t RiffSign;																															//¬¥âª  RIFF
	uint32_t chunkSizeBytes;																													//à §¬¥à ä ©«  á § £®«®¢ª®¬
	uint32_t WaveSign;																															//¬¥âª  WAVE
	uint32_t fmtSign;																															//¬¥âª  fmt
	uint32_t DataFormatLenght;																													//¤«¨­  ä®à¬ â  ¤ ­­ëå
	uint16_t compressionCode;																													//ª®¤ á¦ â¨ï
	uint16_t soundChannels;																														//ª®«¨ç¥áâ¢® ª ­ «®¢
	uint32_t sampleRate;																														//ç áâ®â  ¢ë¡®à®ª
	uint32_t byteRate;																															//áª®à®áâì ¯¥à¥¤ ç¨ ¤ ­­ëå, ¡ ©â
	uint16_t BytesInSample;																														//ª®«¨ç¥áâ¢® ¡ ©â ¢ ®¤­®© ¢ë¡®àª¥ á® ¢á¥å ª ­ «®¢
	uint16_t BitDepth;																															//£«ã¡¨­  ¤¨áªà¥â¨§ æ¨¨
	uint32_t dataSign;																															//¬¥âª  data
	uint32_t chunkSizeWoutHeader;																												//à §¬¥à ä ©«  ¡¥§ § £®«®¢ª 
};																																				//ª®­¥æ áâàãªâãàë § £®«®¢ª 
struct FilSettings																																//áâàãªâãà , ¢ ª®â®àãî ¯¨èãâáï ¯ à ¬¥âàë ¨§ ä ©«  convertParams.ini
{																																				//­ ç «® áâàãªâãàë
	int FSetWasConverted;																														//ä« £ ª®â®àë© ¯®ª §ë¢ ¥â - ¡ë« «¨ ª®­¢¥àâ¨à®¢ ­ ä ©« çâ®¡ á¤¥« âì ¢ë¢®¤ - ¯¨á âì § £®«®¢®ª ¨«¨ ­¥â
	int FSetBitDepth;																															//£«ã¡¨­  ¤¨áªà¥â¨§ æ¨¨
	int FSetChannels;																															//ª®«¨ç¥áâ¢® ª ­ «®¢
	long FSetSampleRate;																														//ç áâ®â  ¢ë¡®à®ª
	uint32_t FSetSamplesValue;																													//ª®«¨ç¥áâ¢® ¢ë¡®à®ª
};																																				//ª®­¥æ áâàãªâãàë
struct FilSettings FilSet;																														//ã¯à®é¥­¨¥ ¨¬¥­¨ áâàãªâãàë
struct WaveHeader Wave;																															//ã¯à®é¥­¨¥ ¨¬¥­¨ áâàãªâãàë
int main(int argc, char *argv[])																												//®¯¨á ­¨¥ main ¨ ¬¥â®¤  ¯¥à¥¤ ç¨  à£ã¬¥­â®¢ ¨§ ª®¬ ­¤­®© áâà®ª¨
{																																				//­ ç «® â¥«  main
	unsigned int codePageNum;
	bool setOutCodePageStatus;
	bool setInCodePageStatus;
	memset(fileMassive,0x00,sizeof(fileMassive));																								//ç¨áâ¨¬ ¬ áá¨¢ fileMassive
	memset(fileNameRAW,0x00,sizeof(fileNameRAW));																								//ç¨áâ¨¬ ¬ áá¨¢ fileNameRAWs
	memset(fileNameSrc,0x00,sizeof(fileNameSrc));																								//ç¨áâ¨¬ ¬ áá¨¢ fileNameSrc
	memset(fileName,0x00,sizeof(fileName));																										//ç¨áâ¨¬ ¬ áá¨¢ fileName
	memset(FileHeader,0x00,sizeof(FileHeader));																									//ç¨áâ¨¬ ¬ áá¨¢ FileHeader
	memset(ByteBuffer,0x00,sizeof(ByteBuffer));																									//ç¨áâ¨¬ ¬ áá¨¢ ByteBuffer
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
		printf("¥à¥ª«îç¥­¨¥ ª®¤®¢®© áâà ­¨æë ­¥ âà¥¡ã¥âáï\n");
	}
	--argc;
	++argv;
	if(DebugMode==1)																															//¯à®¢¥àª , ¢ª«îç¥­ «¨ à¥¦¨¬ ®â« ¤ª¨
	{pringDebugMsg(36,0);}																														//¥á«¨ ¢ª«îç¥­ â® ¢ë¢®¤ á®®¡é¥­¨ï
	pringDebugMsg(33,0);																														//ã¢¥¤®¬«¥­¨¥ ® ­ ç «¥ à ¡®âë ¯à®£¨
	pringDebugMsg(85,argc);																														//á®®¡é¥­¨¥ ¨ ª®«¨ç¥áâ¢¥  à£ã¬¥­â®¢, ¯®«ãç¥­­ëå ¨§ ª®¬ ­¤­®© áâà®ª¨
	if(argc<1)
	{
		pringDebugMsg(101,0);
		printf(" ¥ ãª § ­ë  à£ã¬¥­âë! ‚ë§®¢ á¯à ¢ª¨ -help\n");
		return 0;
	}
	for(uint8_t i=0;i<argc;i++)
	{
		if(!(strcmp(argv[i], "-h")))
		{
			printHelpMsg();
		}
		else if(!(strcmp(argv[i], "-H")))
		{
			printHelpMsg();
		}
		else if(!(strcmp(argv[i], "-HELP")))
		{
			printHelpMsg();
		}
		else if(!(strcmp(argv[i], "-help")))
		{
			printHelpMsg();
		}
		if(!(strcmp(argv[i], "-makehead")))
		{
			pringDebugMsg(101,0);
			printf(" €à£ã¬¥­â -makehead ­ ©¤¥­\n");
			ReadSettingsFile();
			cursorSymbol=strstr(fileMassive, wordConvert);
			structModifier();
			generateHead();
			exit(1);
		}
	}
	if(argc>4)
	{
		printf("‘«¨èª®¬ ¬­®£®  à£ã¬¥­â®¢\n");
		pringDebugMsg(84,0);
	}
	printf(StartMsg);
	printf(StartMsgTwo);
	printf("‚â®à®©  à£ã¬¥­â ®âáãâá¢ã¥â, á®§¤ ¥âáï ä ©« á ¨¬¥­¥¬ ¯® ã¬®«ç ­¨î\n\n");
	FRd=fopen(argv[0], "rb");
	if(FRd==NULL)
	{
		printf("¥ ã¤ «®áì ®âªàëâì ä ©« %s\n",argv[0]);
	}
	fileLength=GetFileName(argv[0]);
	transformFileName(fileName,fileLength,headerNameSuffix,sizeof(headerNameSuffix),fileNameHdrDat);											//£¥­¥à¨àã¥¬ ¨¬ï ä ©«  á § £®«®¢ª®¬ ¨§ ¨áå®¤­¨ª 
	transformFileName(fileName,fileLength,headerBodySuffix,sizeof(headerBodySuffix),fileNameBodDat);											//£¥­¥à¨àã¥¬ ¨¬ï ä ©«  á â¥«®¬ ¨§ ¨áå®¤­¨ª 
	transformFileName(fileName,fileLength,headerConvSuffix,sizeof(headerConvSuffix),fileNameTgtDat);											//£¥­¥à¨àã¥¬ ¨¬ï ä ©«  á â¥«®¬ ¨§ ¨áå®¤­¨ª 
	if(!FRd)																																	//¯à®¢¥àª  áãé¥áâ¢®¢ ­¨ï ä ©«  …(FRd)=0?
	{																																			//â®£¤ ...
		pringDebugMsg(89,0);																													//ª®áâë«ì
		pringDebugMsg(91,0);																													//á®®¡é¥­¨¥ ®¡ ®âáâãâáâ¢¨¨ ä ©« 
		exit(1);																																//¢ëå®¤ ¨§ ¯à®£à ¬¬ë á ª®¤®¬ 1(ä ©« ­¥ ­ ©¤¥­)
	}																																			//ª®­¥æ â¥«  ¯à®¢¥àª¨
	fseek(FRd, 0, SEEK_SET);																													//ãáâ ­®¢ª  ªãàá®à  ­   ¤à¥á(ãá¯¥è­®áâì ¤ ­­®© ®¯¥à æ¨¨ ¯®ª  ­¥ ¯à®¢¥àï¥âáï ­¨ª ª)
	pringDebugMsg(26,0);																														//¢ëá¨à ¥¬ ®â« ¤®ç­®¥ á®®¡é¥­¨¥ ® ­ ç «¥ çâ¥­¨ï § £®«®¢ª 
	fread(FileHeader, 1, HeaderSize, FRd);																										//¢ë¯®«­ï¥¬ çâ¥­¨¥ ¢ ¡ãää¥à FileHeader, ç¨â ¥¬ ¯¥à¢ë¥ 44 ¡ ©â (ãª § ­ë ¢ HeaderSize)
	writeDebugHeaderBuffer();																													//â®«ìª® ¤«ï à¥¦¨¬  ®â« ¤ª¨, § ¯¨áì ¢ ®â¤¥«ì­ë© ¡ãä¥à ¨§ ª®â®à®£® ¡ã¤¥â ¢ë¢®¤¨âìáï ­  íªà ­ ®â« ¤ª¨
	pringDebugMsg(25,0);																														//¢ë¢®¤ á®¤¥à¦¨¬®£® ¡ãä¥à  FileHeader
	pringDebugMsg(29,0);																														//¢ë¢®¤ á®®¡é¥­¨ï ® â®¬, çâ® ­ ç â® çâ¥­¨ï á®¤¥à¦¨¬®£® íâ®£® ¡ãä¥à 
	headerReader();																																//¢ë§®¢ äã­ªæ¨¨ çâ¥­¨ï § £®«®¢ª 
	fclose(FRd);																																//§ ªàëâ¨¥ ä ©«  ¤«ï çâ¥­¨ï
	checkStatus(1);																																//¯à®¢¥àª  ª®¤  ¢ëå®¤  äã­ªæ¨¨ çâ¥­¨ï § £®«®¢ª 
	structAnalyzer();																															//¢ë§®¢ äã­ªæ¨¨ ¯à®¢¥àª¨ áâàãªâãàë ­  ¯à ¢¨«ì­®áâì
	ReadSettingsFile();																															//¢ë§®¢ äã­ªæ¨¨ çâ¥­¨ï ¨§ ä ©«  ¯ à ¬¥âà®¢
	WriteSettingsFile();																														//¢ë§®¢ äã­ªæ¨¨ § ¯¨á¨ ¯ à ¬¥âà®¢ ¢ ä ©«
	pringDebugMsg(82,0);																														//¢ë¢®¤ á®®¡é¥­¨ï § ¢¥àè¥­¨ï à ¡®âë ¯à®£à ¬¬ë
	//pringDebugMsg(38,0);					//ŠŽ‘’›‹œ „‹Ÿ €‚’ŽŒ€’ˆ‡€–ˆˆ																			//¯à®£à ¬¬  á®®¡é ¥â ®â â®¬ çâ® é á ¡ã¤¥â ¦¤ âì ­ ¦ â¨ï ª« ¢¨è¨ Enter
	//getchar();																																//­¨ç¥£® ­¥ ¤¥« âì, ¦¤ âì ­ ¦ â¨ï ª« ¢¨è¨ Enter
}																																				//ª®­¥æ â¥«  main
void generateHead(void)
{
	pringDebugMsg(101,0);
	printf(" ƒ¥­¥à¨àãî áâàãªâãàã...\n");
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
		printf(" “á¯¥å\n");
	}
	else
	{
		printf(" ¥ ã¤ «®áì á®§¤ âì ä ©« %s\n",fileNameHdrDat);
		exit(0);
	}
	fseek(FWr, 0, SEEK_SET);
	fwrite(FileHeader, sizeof(uint8_t), sizeof(FileHeader), FWr);
	fclose(FWr);
}
inline void printHelpMsg(void)																													//äã­ªæ¨ï ¢ë¢®¤  á¯à ¢®ç­®© ¨­ä®à¬ æ¨¨ ¢ ª®­á®«ì
{																																				//­ ç «® â¥« 
	printf(StartMsg);																															//¢ë¢®¤¨¬ ¢¥àá¨î ¯à®£à ¬¬ë
	printf("ˆá¯®«ì§®¢ ­¨¥: Exheader.exe source_file output_file(¢ë¡®à®ç­®)\n\n");																//á¯à ¢ª , ­ ç «®
	printf("- à¨ ®âáãâáâ¢¨¨ ¢â®à®£®  à£ã¬¥­â , ä ©« á § £®«®¢ª®¬ á®§¤ ¥âáï ¢\n  ¤¨à¥ªâ®à¨¨ § ¯ãáª  Exheader.exe\n");							//á¯à ¢ª , ¯à®¤®«¦¥­¨¥
	printf("-  ¯à¨¬¥à, ¢ë§®¢ Exheader.exe C:\\foreign8.wav á®§¤ áâ ¯® ¬¥áâã\n  ¢ë§®¢  § £®«®¢®ç­ë© ä ©« foreign8_header.dat\n");				//á¯à ¢ª , ¯à®¤®«¦¥­¨¥
	printf("  € ¢ë§®¢ Exheader C:\\foreign8.wav C:\\aaa\\foreign8dat.wav á®§¤ áâ ¯® ¯ãâ¨ C:\\aaa ä ©« foreign8dat.wav.dat\n\n");				//á¯à ¢ª , ¯à®¤®«¦¥­¨¥
	printf("- Š®­¥ç­ë© ä ©« ¢á¥£¤  ¡ã¤¥â á à áè¨à¥­¨¥¬ .dat ¨ á®¤¥à¦ âì ¢ á¥¡¥\n  áä®à¬¨à®¢ ­­ë© ¨§ convertParams.ini § £®«®¢®ª\n");			//á¯à ¢ª , ¯à®¤®«¦¥­¨¥
	exit(1);																																	//¢ëå®¤ á ª®¤®¬ 1
}																																				//ª®­¥æ â¥«  á¯à ¢®ç­®© äã­ªæ¨¨
inline void writeDebugHeaderBuffer(void)																										//ä-ªæ¨ï ª®¯¨à®¢ ­¨ï § £®«®¢ª  ¢ ®â¤¥«ì­ë© ¡ãä¥à ¤«ï ¢ë¢®¤  ®â« ¤®ç­ëå á®®¡é¥­¨©
{																																				//­ ç «® â¥«  ä-ªæ¨¨
	for(int j=0;j<43;j++)																														//­ ç «® æ¨ª«  ª®¯¨à®¢ ­¨ï ¬ áá¨¢®¢
	{																																			//­ ç «® â¥«  æ¨ª« 
		FileHeaderMSG[j]=FileHeader[j];																											//¯®á¨¬¢®«ì­®¥ ª®¯¨à®¢ ­¨¥ á á®åà ­¥­¨¥¬  ¤à¥á  á¨¬¢®«  ®â­®á¨â¥«ì­® ­ ç «  ¬ áá¨¢®¢
	}																																			//ª®­¥æ â¥«  æ¨ª« 
}																																				//ª®­¥æ â¥«  äã­ªæ¨¨
uint8_t GetFileName(char* nameOfFile)
{
	uint8_t symbolCountInFileName;																												//¯¥à¥¬¥­­ ï åà ­ïé ï ¤«¨­ã ¨¬¥­¨ ä ©« , ¢ª«îç ï à áè¨à¥­¨¥
	strcpy(fileNameRAW,nameOfFile);																												//¤ã¡«¨à®¢ ­¨¥ áâà®ª¨ ¢ ¬ áá¨¢
	uint8_t nameLenght = strlen(nameOfFile);																									//¯®¤áç¥â ª®«¨ç¥áâ¢  ¢¢¥¤¥­ëå á¨¬¢®«®¢
	char *lastSymbolEntry = strrchr(fileNameRAW, 92);																							//­ å®¦¤¥­¨¥ ¯®á«¥¤­¥£® ¢å®¦¤¥­¨ï á¨¬¢®«  "\"
	uint8_t entryPos = lastSymbolEntry-fileNameRAW+1;																							//ãª § â¥«ì ­  ¨­¤¥ªá ¯®á«¥¤­¥£® ¢å®¦¤¥­¨ï á¨¬¢®« 
	if(lastSymbolEntry==NULL)																													//¥á«¨ äã­ªæ¨ï strrchr ¢®§¢à é ¥â NULL...
	{																																			//...â® ­ ç¨­ ¥¬ ®¡à ¡®âªã ¨¬¥­¨ ¡¥§ ®â¤¥«¥­¨ï § ¯¨á¨ ¯ãâ¨ ª ä ©«ã
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		pringDebugMsg(92,0);																													//¯¨è¥¬ á®®¡é¥­¨¥ ® ¢®§¢à â¥ NULL äã­ªæ¨¥© strrchr
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		printf("„«¨­  ¨¬¥­¨ ä ©«  = %d\n", nameLenght);																							//¯¨è¥¬ á®®¡é¥­¨¥ ® ¤«¨­¥ ¨¬¥­¨ ä ©«  ¢ª«îç ï ¯ãâì ¤® ­¥£®
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		printf("ˆ¬ï ®âªàë¢ ¥¬®£® ä ©« : ");																										//¯¨è¥¬ ¨¬ï ®âªàë¢ ¥¬®£® ä ©« 
		for(int i=0;i<nameLenght;i++)																											//­ ç «® æ¨ª«  ¢ë¢®¤  ¨¬¥­¨ ä ©« 
		{																																		//­ ç «® â¥«  æ¨ª« 
			printf("%c",fileNameRAW[i]);																										//¯®á¨¬¢®«ì­ë© ¢ë¢®¤ ¨¬¥­¨ ä ©«  ¨§ ¬ áá¨¢ 
		}																																		//ª®­¥æ â¥«  æ¨ª« 
		printf("\n");																															//¯¥ç â ¬ ¯¥à¥­®á ª à¥âª¨
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		pringDebugMsg(93, entryPos);																											//¢ë¢®¤¨¬ ¯®§¨æ¨î ¯®á«¥¤­¥£® ­ ©¤¥­­®£® ­ã¦­®£® á¨¬¢®« 
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		printf("®á«¥¤­¥¥ ¢å®¦¤¥­¨¥ á¨¬¢®« : %s\n", lastSymbolEntry);																			//¯¨è¥¬ ¯®á«¥¤­¥¥ ¢å®¦¤¥­¨¥ á¨¬¢®« 
		symbolCountInFileName = strlen(fileNameRAW);																							//¯®¤áç¨âë¢ ¥¬ ¤«¨­ã ¨¬¥­¨ ä ©« , ¢ á¨¬¢®« å
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		pringDebugMsg(94,symbolCountInFileName);																								//¯¨è¥¬ ¯®«ãç¥­­®¥ ¢ à¥§ã«ìâ â¥ ¯®¤áç¥â  ç¨á«®
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		printf("®«ãç¥­­®¥ ¨¬ï ä ©« : ");																										//¢ë¢®¤¨¬ ¯®«ãç¥­­®¥ ¨¬ï ä ©« 
		for(int i=0;i<symbolCountInFileName;i++)																								//­ ç «® æ¨ª«  ¢ë¢®¤  ¨¬¥­¨
		{																																		//­ ç «® â¥«  æ¨ª« 
			fileNameSrc[i]=fileNameRAW[i];																										//¤ã¡«¨à®¢ ­¨¥ ®à¨£¨­ «ì­®£® ¨¬¥­¨ ä ©«  ¢ ¬ áá¨¢
			fileName[i]=fileNameRAW[i];																											//¯¥à¥­®á¨¬ ¨¬ï ¢ ¤àã£®© ¬ áá¨¢ ¯®á¨¬¢®«ì­®
			printf("%c",fileName[i]);																											//¨ § ®¤­® ¯®á¨¬¢®«ì­® ¢ë¢®¤¨¬ ¯¥à¥­®á¨¬®¥ ¨¬ï ¢ ª®­á®«ì
		}																																		//ª®­¥æ â¥«  æ¨ª« 
		printf("\n");																															//¯¥à¥­®á¨¬ ª à¥âªã
		return symbolCountInFileName;																											//¢®§¢à é ¥¬ ¤«¨­ã ¨¬¥­¨ ä ©« 
	}																																			//ª®­¥æ â¥« (¨áâ¨­ )
	else																																		//¨­ ç¥ ®â¤¥«ï¥¬ ¯ãâì ¤® ä ©«  ®â ¨¬¥­¨ ä ©« 
	{																																			//­ ç «® â¥« 
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		printf("„«¨­  ¨¬¥­¨, ¢ª«îç ï ¯ãâì ª ä ©«ã = %d\n", nameLenght);																			//¯¨è¥¬ ¤«¨­ã ¨¬¥­¨ ä ©« 
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		printf("ˆ¬ï ®âªàë¢ ¥¬®£® ä ©« : ");																										//¯¨è¥¬ ¨¬ï ®âªàë¢ ¥¬®£® ä ©« 
		for(int i=0;i<nameLenght;i++)																											//­ ç «® æ¨ª«  ¢ë¢®¤  ¨¬¥­¨ ä ©« 
		{																																		//­ ç «® â¥«  æ¨ª« 
			printf("%c",fileNameRAW[i]);																										//¯®á¨¬¢®«ì­ë© ¢ë¢®¤ ¨¬¥­¨ ä ©« 
		}																																		//ª®­¥æ â¥«  æ¨ª« 
		printf("\n");																															//¯¥à¥­®á ª à¥âª¨
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		pringDebugMsg(93, entryPos);																											//¯¨è¥¬ ¯®§¨æ¨î á¨¬¢®« , ª®â®àë© ¨é¥¬ ¢ áâà®ª¥
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		printf("®á«¥¤­¥¥ ¢å®¦¤¥­¨¥ á¨¬¢®« : %s\n", lastSymbolEntry);																			//áâà®ªã á â®© ¯®§¨æ¨¨ £¤¥ ¡ë« ­ ©¤¥­ á¨¬¢®«ì
		symbolCountInFileName = nameLenght-entryPos;																							//áç¨â ¥¬ ª®«¨ç¥áâ¢® á¨¬¢®«®¢ ¢ ¨¬¥­¨ ä ©« 
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		pringDebugMsg(94,symbolCountInFileName);																								//¯¨è¥¬ ¯®«ãç¥­®¥ ¢ à¥§ã«ìâ â¥ ¢ëç¨á«¥­¨© ç¨á«®
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		printf("®«ãç¥­­®¥ ¨¬ï ä ©« : ");																										//¯¨è¥¬ ¯®«ãç¥­­®¥ ¨¬ï ä ©« (ã¦¥ á ¬® ¨¬ï)
		for(int i=0;i<symbolCountInFileName;i++)																								//­ ç¨­ ¥¬ ¢ë¢®¤ ¨¬¥­¨ ä ©« 
		{																																		//­ ç «® â¥«  æ¨ª« 
			fileNameSrc[i]=fileNameRAW[i+entryPos];																								//¤ã¡«¨à®¢ ­¨¥ ®à¨£¨­ «ì­®£® ¨¬¥­¨ ä ©«  ¢ ¬ áá¨¢
			fileName[i]=fileNameRAW[i+entryPos];																								//¯®á¨¬¢®«ì­® ¢ë¢®¤¨¬ ¨¬ï ä ©«  á® á¬¥é¥­¨¥¬ ¢ ­ ç «® ¨¬¥­¨
			printf("%c",fileName[i]);																											//¨ áà §ã ¦¥ ¯¥ç â ¥¬, â ª¦¥ ¯® á¨¬¢®«ã
		}																																		//ª®­¥æ â¥« 
		printf("\n");																															//¯¥à¥­®á ª à¥âª¨
		return symbolCountInFileName;																											//¢®§¢à é ¥¬ ¤«¨­ã ¨¬¥­¨ ä ©«  ¢ ¬¥áâ® ¢ë§®¢  äã­ªæ¨¨
	}																																			//ª®­¥æ â¥« («®¦ì)
}																																				//ª®­¥æ â¥«  äã­ªæ¨¨
void transformFileName(char *sourceFileName, uint8_t sourceLenght, char *suffixToAttach, uint8_t suffixLength, char *arrToStore)				//äã­ªæ¨ï £¥­¥à¨à®¢ ­¨ï ¨¬¥­¨ ä ©« 
{																																				//­ ç «® â¥«  äã­ªæ¨¨
	char tempMas[64];																															//¨­¨æ¨ «¨§¨àã¥¬ ¢à¥¬¥­­ë© ¡ãä¥à
	memset(tempMas,0x00,sizeof(tempMas));																										//¨ ç¨áâ¨¬ ¥£®
	uint8_t filenameWithoutExtension=sourceLenght-4;																							//¨­¨æ¨ «¨§ æ¨ï ¯¥à¥¬¥­­®© ¤«¨­ë ¨¬¥­¨ ä ©«  ¡¥§ à áè¨à¥­¨ï
	uint8_t generatedFileNameWithSuffix;																										//¨­¨æ¨ «¨§ æ¨ï ¯¥à¥¬¥­­®© ¤«¨­ë á£¥­¥à¨à®¢ ­­®£® ¨¬¥­¨ ä ©« 
	pringDebugMsg(95,0);																														//¯¨è¥¬ ¢ ª®­á®«ì
	pringDebugMsg(96,0);																														//¯¨è¥¬ ®¡êï¢«¥­¨¥ ® ­ ç «¥ à ¡®âë äã­ªæ¨¨
	for(int i=0;i<filenameWithoutExtension+suffixLength;i++)																					//­ ç «® æ¨ª«  £¥­¥à æ¨¨ ¨¬¥­¨ ä ©« 
	{																																			//­ ç «® â¥«  æ¨ª« 
		if(i<filenameWithoutExtension)																											//­ ç «® ¯¥à¥­®á  ¨¬¥­¨ ä ©« 
		{																																		//­ ç «® â¥« 
			tempMas[i]=sourceFileName[i];																										//¯®á¨¬¢®«ì­ë© ¯¥à¥­®á ¨¬¥­¨ ä ©« 
		}																																		//ª®­¥æ â¥« 
		if(i>=filenameWithoutExtension)																											//­ ç «® § ¯¨á¨ áãää¨ªá  ª ¨¬¥­¨ ä ©« 
		{																																		//­ ç «® â¥« 
			tempMas[i]=suffixToAttach[i-filenameWithoutExtension];																				//¯®á¨¬¢®«ì­ ï § ¯¨áì áãää¨ªá  ª ¨¬¥­¨ ä ©« 
		}																																		//ª®­¥æ â¥« 
	}																																			//ª®­¥æ â¥«  æ¨ª« 
	generatedFileNameWithSuffix = filenameWithoutExtension+suffixLength;																		//ä®à¬¨à®¢ ­¨¥ ¤«¨­ë ¨¬¥­¨ ä ©«  ¢¬¥áâ¥ á áãää¨ªá®¬
	if(strlen(tempMas)==generatedFileNameWithSuffix)																							//áà ¢­¨¢ ¥¬ ¯®«ãç¥­­®¥ ¨¬ï ¨ à áç¥â­ãî ¤«¨­ã ä ©« 
	{																																			//­ ç «® â¥«  æ¨ª« 
		pringDebugMsg(95,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		pringDebugMsg(98,0);																													//¯¨è¥¬ ¯à®¢¥àªã
	}																																			//ª®­¥æ â¥«  æ¨ª« 
	else																																		//¢ á«ãç ¥ ¥á«¨ ¤«¨­ë ­¥ á®¢¯ ¤ îâ
	{																																			//â® ¯¨è¥¬ ¢ ª®­á®«ì á®®¡é¥­¨¥ ®¡ ®è¨¡ª¥
		pringDebugMsg(15,0);																													//¨ ¢ëå®¤¨¬ ¨§ ¯à®£à ¬¬ë
	}																																			//ª®­¥æ â¥«  æ¨ª« 
	pringDebugMsg(95,0);																														//¯¨è¥¬ ¢ ª®­á®«ì
	printf("®«ãç¥­­®¥ ¨¬ï ä ©« : ");																											//¯¨è¥¬ á£¥­¥à¨à®¢ ­­®¥ ¨¬ï ä ©« 
	for(int i=0;i<generatedFileNameWithSuffix;i++)																								//­ ç «® æ¨ª«  ¯¥à¥­®á  ¨¬¥­¨ ä ©«  ¨§ ¢à¥¬¥­­®£® ¬ áá¨¢ 
	{																																			//­ ç «® â¥«  æ¨ª« 
		fileName[i]=tempMas[i];																													//¯®á¨¬¢®«ì­ë© ¯¥à¥­®á ¨¬¥­¨ ä ©« 
		arrToStore[i]=tempMas[i];																												//¤ã¡«¨àã¥¬ ¢ ¬ áá¨¢ ¯® ãª § â¥«î ¤«ï § é¨âë ®â á«ãç ©­®£® ¨§¬¥­¥­¨ï ¢ å®¤¥ à ¡®âë ¯à®£à ¬¬ë â.ª ¯à®£  £¤¥-â® ¡ £ ¥âáï ­¥¯®­ïâ­® £¤¥
		printf("%c",arrToStore[i]);																												//¨ áà §ã ¦¥ ¢ë¢®¤ ¢ ª®­á®«ì
	}																																			//ª®­¥æ â¥«  æ¨ª« 
	printf("\n");																																//¯¥à¥­®á ª à¥âª¨
	pringDebugMsg(95,0);																														//¯¨è¥¬ ¢ ª®­á®«ì
	pringDebugMsg(94,generatedFileNameWithSuffix);																								//¯¨è¥¬ ¤«¨­ã á£¥­¥à¨à®¢ ­­®£® ¨¬¥­¨
	pringDebugMsg(95,0);																														//¯¨è¥¬ ¢ ª®­á®«ì
	pringDebugMsg(97,0);																														//ã¢¥¤®¬«ï¥¬ çâ® ¨¬ï ä ©«  á®åà ­¥­® ¢ £«®¡ «ì­®¬ ¬ áá¨¢¥
}																																				//ª®­¥æ â¥«  äã­ªæ¨¨
uint8_t headerReader(void)																														//ª®áâë«ì­ ï äã­ªæ¨ï 
{																																				//­ ç «® â¥«  ä-ªæ¨¨
	uint32_t LongByteWord;																														//®¡êï¢«ï¥¬ ¢à¥¬¥­­ãî 4 ¡ ©â­ãî ¯¥à¥¬¥­­ãî
	int hA=0,hB=0,hC=0,hD=0;																													//ª®áâë«¨
	struct WaveHeader Wave;																														//®¡êï¢«¥­¨¥ ­ §¢ ­¨ï áâàãªâãàë ¢ íâ®© äã­ªæ¨¨(§ ç¥¬?)
	for(int i=0;i<13;i++)																														//­ ç «® æ¨ª«  § ¯¨á¨ § £®«®¢ª  ¢ áâàãªâãàã
	{																																			//­ ç «® â¥«  æ¨ª« 
		pringDebugMsg(8,0);																														//¯¥ç â ¥¬ à §¤¥«¨â¥«ì ¢ ª®­á®«ì, ¤«ï ªà á®âë
		pringDebugMsg(7, hB);																													//¯®ª §ë¢ ¥¬ áâ¥¯¥­ì § ¯®«­¥­­®áâ¨ áâàãªâãàë
		LongByteWord=byteConverter(headerAddrs[hA], headerAddrs[hA+1], headerWordSizeOf[hC], headerWordInvert[hD]);								//¢ë§ë¢ ¥¬ äã­ªæ¨î ª®­¢¥àâ æ¨¨ ä®à¬ â  ¤ ­­ëå, ¢á¥ ¯ à ¬¥âàë ¤«ï íâ®£® ¡¥à¥¬ ¨§ ¬ áá¨¢®¢ ¢ ­ ç «¥ ä ©« 
		checkStatus(0);																															//¯à®¢¥àï¥¬ ä« £¨-á¨£­ «¨§ â®àë ®è¨¡ª¨
		pringDebugMsg(headerDebugPrintParameters[hB], LongByteWord);																			//¯¨è¥¬ ®â« ¤®ç­®¥ á®®¡é¥­¨¥, ¢ ª®â®à®¬ ãª §ë¢ ¥âáï ­ §¢ ­¨¥ ¯ à ¬¥âà  § £®«®¢ª 
		structFiller(hB, LongByteWord);																											//¯¨è¥¬ ¢ áâàãªâãàã áª®­¢¥àç¥­­®¥ §­ ç¥­¨¥
		clearByteBuffer();																														//ç¨áâª¨¬ ¡ãä¥à ¯®á«¥ ®ª®­ç ­¨ï à ¡®âë á ­¨¬
		LongByteWord=0;																															//ç¨áâ¨¬ ¯¥à¥¬¥­­ãî ¢ ª®â®àãî ç¨â ¥¬ á®¤¥à¦¨¬®¥ ¬ áá¨¢ (§ ç¥¬? ¯¥à¥¬¥­­ ï ã­¨çâ®¦ ¥âáï ¯®á«¥ ¢ëå®¤  ¨§ äã­ªæ¨¨)
		hA++;																																	//ª®áâë«ì
		hB++;																																	//ª®áâë«ì
		hC++;																																	//ª®áâë«ì
		hD++;																																	//ª®áâë«ì
	}																																			//ª®­¥æ â¥«  æ¨ª« 
	pringDebugMsg(8,0);																															//¯¨è¥¬ à §¤¥«¨â¥«ì ¢ ª®­á®«ì, ®¯ïâì â ª¨ ¤«ï ªà á®âë
	analyzeState=1;																																//§ ¯¨áë¢ ¥¬ ä« £ á®áâ®ï­¨ï äã­ªæ¨¨(ª®áâë«ì-§ âëçª  çâ®¡ ¯à®£  à ¡®â « )
	return analyzeState;																														//¢ëª¨¤ë¢ ¥¬, â ª ­  ¢áïª¨© á«ãç ©, íâ® ¦¥ §­ ç¥­¨¥
}																																				//ª®­¥æ â¥«  äã­ªæ¨¨
uint32_t byteConverter(int startOffset, int endOffset, int ByteLenght, bool invertState)														//äã­ªæ¨¨ ¯¥à¥ª¨¤ë¢ ­¨ï ä®à¬ â®¢ ¤ ­­ëå ¨§ 32 ¢ 8,16,32 à §àï¤­ë¥
{																																				//­ ç «® â¥«  äã­ªæ¨¨
	uint32_t quadByte;																															//®¡êï¢«ï¥¬ 4 ¡ ©â®¢ãî ¢à¥¬¥­­ãî ¯¥à¥¬¥­­ãî
	uint16_t doubleByte;																														//®¡êï¢«ï¥¬ ¤¢ãå¡ ©â®¢ãî ¢à¥¬¥­­ãî ¯¥à¥¬¥­­ãî
	uint8_t singleByte;																															//®¡êï¢«ï¥¬ ®¤­®¡ ©â®¢ãî ¢à¥¬¥­­ãî ¯¥à¥¬¥­­ãî
	int i=0;																																	//®¡êï¢«ï¥¬ ãª § â¥«ì  ¤à¥á  ¬ áá¨¢®¢
	int startMarker=startOffset;																												//®¡êï¢«ï¥¬ ¨ ¯à¨à ¢­¨¢ ¥¬ ¯®«ãç¥­­®¬ã ¯ à ¬¥âàã ãª § â¥«ì ­ ç «   ¤à¥á  áç¨âë¢ ­¨ï
	int endMarker=endOffset;																													//®¡êï¢«ï¥¬ ¨ ¯à¨à ¢­¨¢ ¥¬ ¯®«ãç¥­­®¬ã ¯ à ¬¥âàã ãª § «¥«ì ª®­æ   ¤à¥á  áç¨âë¢ ­¨ï
	while(startMarker<endMarker)																												//­ ç «® æ¨ª«  § ¯¨á¨ ¢à¥¬¥­­®£® ¡ãä¥à 
	{																																			//­ ç «® â¥«  æ¨ª« 
		ByteBuffer[i]=FileHeader[startMarker];																									//¯®¡ ©â®¢® ¯¥à¥¯¨áë¢ ¥¬ ¢ ¡ãä¥à á®¤¥à¦¨¬®¥, ­ å®¤ïé¥¥áï ­  ãª § ­­®¬  ¤à¥á¥
		pringDebugMsg(32,ByteBuffer[i]);																										//á®®¡é ¥¬ ¢ ª®­á®«ì ® ¯à®¤¥«ë¢ ¥¬®© à ¡®â¥
		i++;																																	//¨­ªà¥¬¨­¨àã¥¬  ¤à¥á ¡ãä¥à 
		startMarker++;																															//¨­ªà¥¬¨­¨àã¥¬  ¤à¥á ¬ áá¨¢  á ª®â®à®£® ¨¤¥â § ¯¨áì
	}																																			//ª®­¥æ â¥«  æ¨ª« 
	i=0;																																		//ç¨áâ¨¬ ¯¥à¥¬¥­­ãî(§ ç¥¬? ®­  ¡®«¥¥ ­¥ ­ã¦­ )
	switch(ByteLenght)																															//­ ç¨­ ¥¬ ¯à®æ¥áá ¯®¤£®â®¢ª¨ ¯ à ¬¥âà  ª ¢ë¤ ç¥
	{																																			//­ ç «® â¥«  switch
		case 0:																																	//¢ á«ãç ¥ ¥á«¨ ¯ à ¬¥âà ­¥ áãé¥áâ¢ã¥â
			pringDebugMsg(30,0);																												//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ ®¡ íâ®¬
			convertState=0;																														//¯¨è¥¬ ä« £ ®è¨¡ª¨
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 1:																																	//¢ á«ãç ¥ ¥á«¨ ¯ à ¬¥âà 1 ¡ ©â­ë©
			pringDebugMsg(31,0);																												//¯¨è¥¬ á®®¡é¥­¨¥ ¢ ª®­á®«ì ®¡ íâ®¬
			singleByte=FileHeader[startMarker];																									//§ ¯¨áë¢ ¥¬ ¯ à ¬¥âà ¢ ¯¥à¥¬¥­­ãî ¤«ï ¢ë¤ ç¨
			convertState=1;																														//¢ëáâ ¢«ï¥¬ ä« £ ãá¯¥è­®© ®¯¥à æ¨¨
			return singleByte;																													//¢®§¢à é ¥¬ ¯¥à¥¬¥­­ãî ­  ¬¥áâ® ¢ë§®¢  äã­ªæ¨¨
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 2:																																	//¢ á«ãç ¥ ¥á«¨ ¯¥à¥¬¥­­ ï 2 ¡ ©â­ ï
			massiveSwap(invertState);																											//¢ë§ë¢ ¥¬ äã­ªæ¨î ¯¥à¥¢¥àâë¢ ­¨ï ¯¥à¥¬¥­­®© ¨ ¯¥à¥¤ ¥¬ ¥© ¯ à ¬¥âà á ¨­ä®à¬ æ¨¥© ® ­¥®¡å®¤¨¬®áâ¨ ¯¥à¥¢®à®â 
			doubleByte=ByteBuffer[0];																											//¯¨è¥¬ ¬« ¤è¨© ¡ ©â
			doubleByte=doubleByte|ByteBuffer[1]<<8;																								//¯¨è¥¬ áâ àè¨© ¡ ©â
			pringDebugMsg(28,doubleByte);																										//¯®ª §ë¢ ¥¬ ¢ ª®­á®«¨ íâã ¯¥à¥¬¥­­ãî
			convertState=1;																														//¢ëáâ ¢«ï¥¬ ä« £ ãá¯¥è­®© ®¯¥à æ¨¨
			return doubleByte;																													//¢®§¢à é ¥¬ ¯¥à¥¬¥­­ãî ­  ¬¥áâ® ¢ë§®¢  äã­ªæ¨¨
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 4:																																	//¢ á«ãç ¥ ¥á«¨ ¯¥à¥¬¥­­ ï 4 ¡ ©â­ ï
			massiveSwap(invertState);																											//¢ë§ë¢ ¥¬ äã­ªæ¨î ¯¥à¥¢®à ç¨¢ ­¨ï ¯¥à¥¬¥­­®© ¨ ¯¥à¥¤ ¥¬ ¥© ¯ à ¬¥âà á ¨­ä®à¬ æ¨¥© ® ­¥®¡å®¤¨¬®áâ¨ ¯¥à¥¢®à®â 
			quadByte=ByteBuffer[0];																												//¯¨è¥¬ ¬« ¤è¨© ¡ ©â
			quadByte=quadByte|ByteBuffer[1]<<8;																									//¯¨è¥¬ ¡ ©â ¯®áâ àè¥
			quadByte=quadByte|ByteBuffer[2]<<16;																								//¯¨è¥¬ ¡ ©â ¯®áâ àè¥
			quadByte=quadByte|ByteBuffer[3]<<24;																								//¯¨è¥¬ áâ àè¨© ¡ ©â
			pringDebugMsg(27,quadByte);																											//¢ ª®­á®«¨ £®¢®à¨¬ ®¡ íâ®¬ ¨ ¯®ª §ë¢ ¥¬ à¥§ã«ìâ â
			convertState=1;																														//¢ëáâ ¢«ï¥¬ ä« £ ãá¯¥è­®© ®¯¥à æ¨¨
			return quadByte;																													//¢®§¢à é ¥¬ ¯¥à¥¬¥­­ãî ­  ¬¥áâ® ¢ë§®¢ 
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
	}																																			//ª®­¥æ â¥«  æ¨ª« 
	return convertState;																														//¢®§¢à é ¥¬ ä« £ á®áâ®ï­¨ï
}																																				//ª®­¥æ äã­ªæ¨¨
uint8_t massiveSwap(bool swapState)																												//¨§­ ç «ì­® çâ¥­¨¥ ¤¥« ¥âáï ­ ®¡®à®â, ¯®íâ®¬ã ¯®¤ "¥à¥áâ ­®¢ª  ¡ ©â®¢ ­¥ âà¥¡ã¥âáï" ¯®¤à §ã¬¥¢ ¥âáï
{																																				//¢®§¢à â ¨å ­®à¬ «ì­ë© ¯®àï¤®ª, â® ¥áâì ­¥ ­ ®¡®à®â
	uint32_t tempByte;																															//®¡êï¢«ï¥¬ ¢à¥¬¥­­ãî ¯¥à¥¬¥­­ãî
	uint8_t tempBuffer[4];																														//®¡êï¢«ï¥¬ ¢à¥¬¥­­ë© ¡ãä¥à ¤«ï íâ®£®
	memset(tempBuffer,0x00,sizeof(tempBuffer));																									//¨ áà §ã ç¨áâ¨¬ ¥£® ®â ¢¥à®ïâ­®£® ¬ãá®à 
	if(swapState==1)																															//¯¥à¥¢®à ç¨¢ âì ­­­ ¤ ?
	{																																			//¥á«¨ ­­­ ¤ , â®...
		pringDebugMsg(34,0);																													//...á®®¡é ¥¬ ®¡ íâ®¬ ¢ ª®­á®«ì
		tempBuffer[0]=ByteBuffer[3];																											//­ ç¨­ ¥¬ ¯¥à¥¢®à ç¨¢ âì
		tempBuffer[1]=ByteBuffer[2];																											//¯¨è¥¬  ¤à¥áãï ¯®§¨æ¨¨ á®§¤ ­­®£® ¡ãä¥à  á ­ ç « ...
		tempBuffer[2]=ByteBuffer[1];																											//...¨ ®¡é¥£® ¢à¥¬¥­­®£® ¡ãä¥à  á ª®­æ 
		tempBuffer[3]=ByteBuffer[0];																											//...§ â¥¬...
		ByteBuffer[0]=tempBuffer[0];																											//...¯¥à¥ª¨¤ë¢ ¥¬ ¢á¥ íâ¨ ¡ ©âë  ¤à¥áãï ®¡  ¡ãä¥à  á ­ ç « 
		ByteBuffer[1]=tempBuffer[1];																											//...
		ByteBuffer[2]=tempBuffer[2];																											//...
		ByteBuffer[3]=tempBuffer[3];																											//...
	}																																			//ª®­¥æ ¯¥à¥¢®à®â 
	else																																		//¥á«¨ ­¥ ­­­ ¤ , â®...
	{pringDebugMsg(35,0);}																														//...¯¨è¥¬ ¢ ª®­á®«ì çâ® ­¥ ­­­ ¤  ¨ ¢ëå®¤¨¬ ¨§ äã­ªæ¨¨
}																																				//ª®­¥æ â¥«  äã­ªæ¨¨
void checkStatus(uint8_t statusCode)																											//ª®áâë«ì­ ï äã­ªæ¨ï
{																																				//­ ç «® â¥«  äã­ªæ¨¨
	pringDebugMsg(74, statusCode);																												//á®®¡é ¥¬ ®¡ íâ®¬ ¢ ª®­á®«ì ¨ ¯®ª §ë¢ ¥¬ ª®¤ ¯à®¢¥àª¨
	switch(statusCode)																															//­ ç «® ¯à®¢¥àª¨
	{																																			//­ ç «® â¥«  switch
		case 0:																																	//¢ á«ãç ¥ ¥á«¨ ãª § ­ ª®¤ 0(á®áâ®ï­¨¥ ª®­¢¥àâ æ¨¨)
			if(convertState!=0)																													//¯à®¢¥àª  ­ «¨ç¨ï ä« £  ®è¨¡ª¨ ª®­¢¥àâ æ¨¨
			{pringDebugMsg(10,0);}																												//¢ á«ãç¥ ãá¯¥å  ¯¨è¥¬ ¢ ª®­á®«ì ®¡ íâ®¬
			else																																//¨­ ç¥...
			{pringDebugMsg(20,convertState);pringDebugMsg(15,0);}																				//...¯®ª §ë¢ ¥¬ á®¤¥à¦¨¬®¥ ä« £ 
			pringDebugMsg(20,convertState);																										//¨ ¢ëå®¤¨¬ ¯à®£à ¬¬ë á ª®¤®¬ 0(®è¨¡ª )
			break;																																//¢ëå®¤ ¨§ æ¨ª« 
		case 1:																																	//¢ á«ãç ¥ ¥á«¨ ãª § ­ ª®¤ 1(á®áâ®ï­¨¥ ª®­¢¥àâ æ¨¨)
			if(analyzeState!=0)																													//¯à®¢¥àï¥¬ á®áâ®ï­¨¥ § ¯®«­¥­¨ï áâàãªâãàë
			{pringDebugMsg(11,0);}																												//¢ á«ãç ¥ ãá¯¥å  ¯¨è¥¬ ®¡ íâ®¬
			else																																//¨­ ç¥...
			{pringDebugMsg(21,analyzeState);pringDebugMsg(16,0);}																				//...¯®ª §ë¢ ¥¬ á®¤¥à¦¨¬®¥ ä« £ 
			pringDebugMsg(21,analyzeState);																										//¨ á®®¡é ¥¬ ®¡ ®è¨¡ª¥
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 2:																																	//¢ á«ãç ¥ ¥á«¨ ãª § ­ ª®¤ 2(á®áâ®ï­¨¥ áâàãªâãàë § £®«®¢ª )
			if(ahsoka!=0)																														//¯à®¢¥àï¥¬ á®áâ®ï­¨¥ ä« £ 
			{pringDebugMsg(12,0);}																												//¢ á«ãç ¥ ¥á«¨ áâàãªâãà  § £®«®¢ª  ¯à ¢¨«ì­ ï, £®¢®à¨¬ ®¡ íâ®¬ ¢ ª®­á®«ì
			else																																//¨­ ç¥...
			{pringDebugMsg(22,ahsoka);pringDebugMsg(17,0);}																						//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ ® ¡¨â®© áâàãªâãà¥
			pringDebugMsg(22,ahsoka);																											//¨ ¯®ª §ë¢ ¥¬ á®áâ®ï­¨¥ ä« £ 
			break;																																//¢ëå®¤¨¬ ¨§ äã­ªæ¨¨
		case 3:																																	//¢ á«ãç ¥ ¥á«¨ ãª § ­ ª®¤ 3(¬®¤¨ä¨ª æ¨ï § £®«®¢ª )
			if(gabella!=0)																														//¥á«¨ ¬®¤¨ä¨ª æ¨ï ¡ë«  ãá¯¥è­ 
			{pringDebugMsg(13,0);}																												//¯¨è¥¬ ®¡ íâ®¬ ¢ ª®­á®«ì
			else																																//¨­ ç¥...
			{pringDebugMsg(23,gabella);pringDebugMsg(18,0);}																					//...¯¨è¥¬ ¢ ª®­á®«ì ®è¨¡ªã ®¯¥à æ¨¨ ¬®¤¨ä¨ª æ¨¨ § £®«®¢ª 
			pringDebugMsg(23,gabella);																											//¯®ª §ë¢ ¥¬ á®¤¥à¦¨¬®¥ ä« £ 
			break;																																//¢ëå®¤¨¬ ¨§ äã­ªæ¨¨
		case 4:																																	//¢ á«ãç ¥ ¥á«¨ ¯®«ãç¥­ ª®¤ 4
			if(doubledoor!=0)																													//¯à®¢¥àï¥¬ ãá¯¥è­®áâì § ¯¨á¨ § £®«®¢ª 
			{pringDebugMsg(14,0);}																												//¯¨è¥¬ ®¡ íâ®¬ ¢ ª®­á®«ì
			else																																//¨­ ç¥...
			{pringDebugMsg(24,doubledoor);pringDebugMsg(19,0);}																					//...¯¨è¥¬ ®¡ ®è¨¡ª¨ ¢ ª®­á®«¨
			pringDebugMsg(24,doubledoor);																										//¨ ¯®ª §ë¢ ¥¬ á®¤¥à¦¨¬®¥ ä« £ 
			break;																																//¢ëå®¤¨¬ ¨§ äã­ªæ¨¨
		case 5:																																	//¢ á«ãç ¥ ¥á«¨ ¯®«ãç¥­ ª®¤ 5
			if(Egor!=0)																															//¯à®¢¥àï¥¬ ãá¯¥å ¯à®ç¨â ­­ëå ¯ à ¬¥âà®¢
			{pringDebugMsg(64,0);}																												//¢ á«ãç ¥ ¥á«¨ ¯à®ç¨â ­® ãá¯¥è­®, ¯¨è¥¬ ¢ ª®­á®«ì
			else																																//¨­ ç¥...
			{pringDebugMsg(66,Egor);pringDebugMsg(65,0);}																						//¯¨è¥¬ á®®¡é¥­¨¥ ®â ®è¨¡ª¨
			pringDebugMsg(66,Egor);																												//¨ ¯®ª §ë¢ ¥¬ á®áâ®ï­¨¥ ä« £ 
			break;																																//¢ëå®¤¨¬ ¨§ äã­ªæ¨¨
		case 6:																																	//¢ á«ãç ¥ ¥á«¨ ¯®«ãç¥­ ª®¤ 6
			if(cruzo!=0)																														//¯à®¢¥àï¥¬ ãá¯¥å à¥¤ ªâ¨à®¢ ­¨ï áâàãªâãàë
			{pringDebugMsg(72,0);}																												//¥á«¨ ¢á¥ å®à®è® â® ¯¨è¥¬ ¢ ª®­á®«ì
			else																																//¨­ ç¥...
			{pringDebugMsg(71,cruzo);pringDebugMsg(73,0);}																						//...ã¢¥¤®¬«ï¥¬ ¢ ª®­á®«¨ ®¡ ®è¨¡ª¥
			pringDebugMsg(71,cruzo);																											//¨ ¯®ª §ë¢ ¥¬ á®áâ®ï­¨¥ ¯¥à¥¬¥­­®©
			break;																																//¢ëå®¤¨¬ ¨§ äã­ªæ¨¨
	}																																			//ª®­¥æ â¥«  æ¨ª« 
}																																				//ª®­¥æ â¥«  äã­ªæ¨¨
uint32_t structFiller(int structShift, uint32_t paramToWrite)																					//ç áâ¨ç­ ï ¯à®¢¥àª  ¯à ¢¨«ì­®áâ¨ áâàãªâãàë, â®«ìª® ¯® ¬¥âª ¬
{																																				//­ ç «® äã­ªæ¨¨
	uint32_t qWordToConvert;																													//á®§¤ ¥¬ ¢à¥¬¥­­ãî 2 ¡ ©â­ãî ¯¥à¥¬¥­­ãî
	uint16_t dWordToConvert;																													//á®§¤ ¥¬ ¢à¥¬¥­­ãî 4 ¡ ©â­ãî ¯¥à¥¬¥­­ãî
	switch(structShift)																															//­ ç «® æ¨ª«  switch
	{																																			//­ ç «® â¥«  æ¨ª« 
		case 0:																																	//¢ á«ãç ¥ ¥á«¨ ¢ë¡à ­  § ¯¨áì ¬¥âª¨ RIFF
			Wave.RiffSign=qByteConverter(paramToWrite);																							//¯®«ãç ¥¬ ¬¥âªã á ¯®¬®éìî ª®­¢¥àâ æ¨¨ ¨§ ¨áå®¤­®£® ¬ áá¨¢ 
			pringDebugMsg(3,0);																													//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ ® § ¯¨á¨ ¢ áâàãªâãàã
			if(Wave.RiffSign==RIFFsignature)																									//áà ¢­¨¢ ¥¬ á íâ «®­®¬
			{pringDebugMsg(41, structShift);}																									//¢ á«ãç ¥ ¥á«¨ ¯®«ãç¥­­ ï ¬¥âª  á®¢¯ ¤ ¥â á íâ «®­®¬ ¯¨è¥¬ ®¡ íâ®¬ ª®­á®«ì
			else																																//¨­ ç¥...
			{pringDebugMsg(42, structShift);}																									//£®¢®à¨¬ ®¡ ®è¨¡ª¥
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 1:																																	//¢ á«ãç ¥ ¥á«¨ ¢ë¡à ­  § ¯¨áì ¬¥âª¨ à §¬¥à  ä ©« 
			Wave.chunkSizeBytes=qByteConverter(paramToWrite);																					//ª®­¢¥àâ¨àã¥¬ ¢ 4 ¡ ©â­ë© ä®à¬ â
			pringDebugMsg(3,structShift);																										//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ ® § ¯¨á¨ ¢ áâàãªâãàã																									
			pringDebugMsg(41, structShift);																										//á®®¡é ¥¬ ®¡ ãá¯¥å¥ ¢ ª®­á®«ì(¯®ª  çâ® ¯à®¢¥àª  ­¥ ®áãé¥áâ¢«ï¥âáï)
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 2:																																	//¢ á«ãç ¥ ¥á«¨ ¢ë¡à ­  § ¯¨áì ¬¥âª¨ WAVE
			Wave.WaveSign=qByteConverter(paramToWrite);																							//ª®­¢¥àâ¨àã¥¬
			pringDebugMsg(3,structShift);																										//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ ® § ¯¨á¨ ¢ áâàãªâãàã
			if(Wave.WaveSign==WAVEsignature)																									//áà ¢­¨¢ ¥¬ á íâ «®­®¬
			{pringDebugMsg(41, structShift);}																									//á®®¡é ¥¬ ®¡ ãá¯¥å¥ ¢ ª®­á®«ì(¯®ª  çâ® ¯à®¢¥àª  ­¥ ®áãé¥áâ¢«ï¥âáï)
			else																																//¨­ ç¥...
			{pringDebugMsg(42, structShift);}																									//á®®¡é ¥¬ ®¡ ®è¨¡ª¥
			break;																																//¢ëå®¤ ¨§ æ¨ª« 
		case 3:																																	//¢ á«ãç ¥ ¥á«¨ ¢ë¡à ­  § ¯¨áì ¬¥âª¨ fmt
			Wave.fmtSign=qByteConverter(paramToWrite);																							//ª®­¢¥àâ¨àã¥¬																							
			pringDebugMsg(3,structShift);																										//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ ® § ¯¨á¨ ¢ áâàãªâãàã
			if(Wave.fmtSign==fmtSignature)																										//áà ¢­¨¢ ¥¬ á íâ «®­®¬
			{pringDebugMsg(41, structShift);}																									//á®®¡é ¥¬ ®¡ ãá¯¥å¥ ¢ ª®­á®«ì(¯®ª  çâ® ¯à®¢¥àª  ­¥ ®áãé¥áâ¢«ï¥âáï)
			else																																//¨­ ç¥...
			{pringDebugMsg(42, structShift);}																									//¯¨è¥¬ ®¡ ®è¨¡ª¥
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 4:																																	//¢ á«ãç ¥ ¥á«¨ ¢ë¡à ­  § ¯¨áì ä®à¬ â  ¤ ­­ëå
			Wave.DataFormatLenght=qByteConverter(paramToWrite);																					//ª®­¢¥àâ¨àã¥¬
			pringDebugMsg(3,structShift);																										//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ ® § ¯¨á¨ ¢ áâàãªâãàã
			pringDebugMsg(41, structShift);																										//á®®¡é ¥¬ ®¡ ãá¯¥å¥ ¢ ª®­á®«ì(¯®ª  çâ® ¯à®¢¥àª  ­¥ ®áãé¥áâ¢«ï¥âáï)
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 5:																																	//¢ á«ãç ¥ ¥á«¨ ¢ë¡à ­  § ¯¨áì ª®¤  á¦ â¨ï
			Wave.compressionCode=dByteConverter(paramToWrite);																					//ª®­¢¥àâ¨àã¥¬
			pringDebugMsg(3,structShift);																										//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ ® § ¯¨á¨ ¢ áâàãªâãàã
			pringDebugMsg(41, structShift);																										//á®®¡é ¥¬ ®¡ ãá¯¥å¥ ¢ ª®­á®«ì(¯®ª  çâ® ¯à®¢¥àª  ­¥ ®áãé¥áâ¢«ï¥âáï)
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 6:																																	//¢ á«ãç ¥ ¥á«¨ ¢ë¡à ­  § ¯¨áì ª®«¨ç¥áâ¢  ª ­ «®¢
			Wave.soundChannels=dByteConverter(paramToWrite);																					//ª®­¢¥àâ¨àã¥¬
			pringDebugMsg(3,structShift);																										//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ ® § ¯¨á¨ ¢ áâàãªâãàã
			pringDebugMsg(41, structShift);																										//á®®¡é ¥¬ ®¡ ãá¯¥å¥ ¢ ª®­á®«ì(¯®ª  çâ® ¯à®¢¥àª  ­¥ ®áãé¥áâ¢«ï¥âáï)
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 7:																																	//¢ á«ãç ¥ ¥á«¨ ¢ë¡à ­  § ¯¨áì ç áâ®âë ¤¨áªà¥â¨§ æ¨¨
			Wave.sampleRate=qByteConverter(paramToWrite);																						//ª®­¢¥àâ¨àã¥¬
			pringDebugMsg(3,structShift);																										//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ ® § ¯¨á¨ ¢ áâàãªâãàã
			pringDebugMsg(41, structShift);																										//á®®¡é ¥¬ ®¡ ãá¯¥å¥ ¢ ª®­á®«ì(¯®ª  çâ® ¯à®¢¥àª  ­¥ ®áãé¥áâ¢«ï¥âáï)	
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 8:																																	//¢ á«ãç ¥ ¥á«¨ ¢ë¡à ­  § ¯¨áì ¡¨âà¥©â 
			Wave.byteRate=qByteConverter(paramToWrite);																							//ª®­¢¥àâ¨àã¥¬
			pringDebugMsg(3,structShift);																										//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ ® § ¯¨á¨ ¢ áâàãªâãàã
			pringDebugMsg(41, structShift);																										//á®®¡é ¥¬ ®¡ ãá¯¥å¥ ¢ ª®­á®«ì(¯®ª  çâ® ¯à®¢¥àª  ­¥ ®áãé¥áâ¢«ï¥âáï)
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 9:																																	//¢ á«ãç ¥ ¥á«¨ ¢ë¡à ­  § ¯¨áì ¥¬ª®áâ¨ á¥¬¯«  ¢ ¡ ©â å
			Wave.BytesInSample=dByteConverter(paramToWrite);																					//ª®­¢¥àâ¨àã¥¬
			pringDebugMsg(3,structShift);																										//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ ® § ¯¨á¨ ¢ áâàãªâãàã
			pringDebugMsg(41, structShift); 																									//á®®¡é ¥¬ ®¡ ãá¯¥å¥ ¢ ª®­á®«ì(¯®ª  çâ® ¯à®¢¥àª  ­¥ ®áãé¥áâ¢«ï¥âáï)
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 10:																																//¢ á«ãç ¥ ¥á«¨ ¢ë¡à ­  § ¯¨áì £«ã¡¨­ë ¢ë¡®àª
			Wave.BitDepth=dByteConverter(paramToWrite);																							//ª®­¢¥àâ¨àã¥¬
			pringDebugMsg(3,structShift);																										//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ ® § ¯¨á¨ ¢ áâàãªâãàã
			pringDebugMsg(41, structShift);																										//á®®¡é ¥¬ ®¡ ãá¯¥å¥ ¢ ª®­á®«ì(¯®ª  çâ® ¯à®¢¥àª  ­¥ ®áãé¥áâ¢«ï¥âáï)
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 11:																																//¢ á«ãç ¥ ¥á«¨ ¢ë¡à ­  § ¯¨áì ¬¥âª¨ data
			Wave.dataSign=qByteConverter(paramToWrite);																							//ª®­¢¥àâ¨àã¥¬
			pringDebugMsg(3,structShift);																										//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ ® § ¯¨á¨ ¢ áâàãªâãàã
			if(Wave.dataSign==dataSignature)																									//áà ¢­¨¢ ¥¬ á íâ «®­®¬
			{pringDebugMsg(41, structShift);}																									//á®®¡é ¥¬ ®¡ ãá¯¥å¥ ¢ ª®­á®«ì(¯®ª  çâ® ¯à®¢¥àª  ­¥ ®áãé¥áâ¢«ï¥âáï)
			else																																//¨­ ç¥...
			{pringDebugMsg(42, structShift);}																									//¯¨è¥¬ á®®¡é¥­¨¥ ®¡ ®è¨¡ª¥
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 12:																																//¢ á«ãç ¥ ¥á«¨ ¢ë¡à ­  § ¯¨áì à §¬¥à  ª®­â¥©­¥à  á á¥¬¯« ¬¨
			Wave.chunkSizeWoutHeader=qByteConverter(paramToWrite);																				//ª®­¢¥àâ¨àã¥¬
			pringDebugMsg(3,structShift);																										//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ ® § ¯¨á¨ ¢ áâàãªâãàã
			pringDebugMsg(41, structShift);																										//á®®¡é ¥¬ ®¡ ãá¯¥å¥ ¢ ª®­á®«ì(¯®ª  çâ® ¯à®¢¥àª  ­¥ ®áãé¥áâ¢«ï¥âáï)
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
	}																																			//ª®­¥æ æ¨ª« 
}																																				//ª®­¥æ â¥«  äã­ªæ¨¨
uint32_t qByteConverter(uint32_t wordToConvert)																									//ª®­¢¥àâ¥à à §àï¤­®áâ¨ 32->32 ¡¨â
{																																				//­ ç «® â¥«  ª®­¢¥àâ¥à
	pringDebugMsg(4,0);																															//¯¨è¥¬ ¢ ã¢¥¤®¬«¥­¨¥ çâ® ª®­¢¥àâ æ¨ï ­¥ âà¥¡ã¥âáï
	return wordToConvert;																														//¢®§¢à é ¥¬ §­ ç¥­¨¥
}																																				//ª®­¥æ â¥«  äã­ªæ¨¨
uint16_t dByteConverter(uint32_t wordToConvert)																									//ª®­¢¥àâ¥à à §àï¤­®áâ¨ 32->16 ¡¨â
{																																				//­ ç «® â¥«  äã­ªæ¨¨
	uint16_t doubleByteWord;																													//¨­¨æ¨ «¨§ æ¨ï ¢à¥¬¥­­®© ¯¥à¥¬¥­­®©
	//doubleByteWord=wordToConvert<<16;																											//ª®áâë«ì
	doubleByteWord=wordToConvert;																												//§ ¯¨áë¢ ¥¬ ¢ ¯¥à¥¬¥­­ãî ¯¥à¥¤ ­­ë©  à£ã¬¥­â
	pringDebugMsg(5,0);																															//¯¨è¥¬ ®¡ íâ®¬ ¢ ª®­á®«ì
	return doubleByteWord;																														//¢®§¢à é ¥¬ §­ ç¥­¨¥ ­  ¬¥áâ® ¢ë§®¢ 
}																																				//ª®­¥æ â¥«  äã­ªæ¨¨
uint8_t sByteConverter(uint32_t wordToConvert)																									//ª®­¢¥àâ¥à à §àï¤­®áâ¨ 32->8 ¡¨â
{																																				//­ ç «® â¥«  äã­ªæ¨¨
	uint8_t singleByteWord;																														//¨­¨æ¨ «¨§¨àã¥¬ ¯¥à¥¬¥­­ãî
	//singleByteWord=wordToConvert<<24;																											//ª®áâë«ì?
	singleByteWord=wordToConvert;																												//§ ¯¨áë¢ ¥¬  à£ã¬¥­â ¢ íâã ¯¥à¥¬¥­­ãî
	pringDebugMsg(6,0);																															//¯¨è¥¬ ¢ ª®­á®«ì ®¡ íâ®¬
	return singleByteWord;																														//¢®§¢à é ¥¬ §­ ç¥­¨¥ ­  ¬¥áâ® ¢ë§®¢ 
}																																				//ª®­¥æ â¥«  äã­ªæ¨¨
void structAnalyzer(void)																														//ç áâ¨ç­ ï ¯à®¢¥àª  áâàãªâãàë, â®«ìª® ¯® ¬¥âª ¬, ‚‘ð ‚ ŠŽ‘’›‹Ÿ•
{																																				//­ ç «® äã­ªæ¨¨
	int chechedSteps=0;																															//ª®áâë«ì
	int headerDifference;																														//¤«¨­  § £®«®¢ª 
	headerDifference=Wave.chunkSizeBytes-Wave.chunkSizeWoutHeader;																				//¢ëç¨á«ï¥¬ ¤«¨­ã § £®«®¢ª 
	pringDebugMsg(9,0);																															//¯¨è¥¬ ¢ ª®­á®«ì
	if(Wave.RiffSign==RIFFsignature)																											//áà ­¨¢ ¥¬ á íâ «®­®¬ ¬¥âªã RIFF
	{																																			//­ ç «® â¥« 
		chechedSteps++;																															//¯à¨à é¨¢ ¥¬ ¯®ª § â¥«ì ¯à®¢¥à¥­­ëå í«¥¬¥­â®¢ ­  1
		pringDebugMsg(39,0);																													//¯¨è¥¬ ¢ ç â
	}																																			//ª®­¥æ â¥« 
	else																																		//¨­ ç¥...
	{pringDebugMsg(40,0);}																														//¯¨è¥¬ ®¡ ®è¨¡ª¥
	if(Wave.WaveSign==WAVEsignature)																											//áà ¢­¨¢ ¥¬ ¬¥âªã WAVE
	{																																			//­ ç «® â¥« 
		chechedSteps++;																															//¨­ªà¥¬¨­¨àã¥¬ §­ ç¥­¨¥ áç¥âç¨ª  ¯à®å®¤ 
		pringDebugMsg(43,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
	}																																			//ª®­¥æ â¥« 
	else																																		//¨­ ç¥...
	{pringDebugMsg(40,0);}																														//...¯¨è¥¬ á®®¡é¥­¨¥ ®¡ ®è¨¡ª¥
	if(Wave.fmtSign==fmtSignature)																												//áà ¢­¨¢ ¥¬ ¬¥âª¨ fmt
	{																																			//­ ç «® â¥« 
		chechedSteps++;																															//¨­ªà¥¬¨­¨àã¥¬ §­ ç¥­¨¥ áç¥âç¨ª  ¯à®å®¤ 
		pringDebugMsg(44,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
	}																																			//ª®­¥æ â¥« 
	else																																		//¨­ ç¥...
	{pringDebugMsg(40,0);}																														//...¯¨è¥¬ á®®¡é¥­¨¥ ®¡ ®è¨¡ª¥
	if(Wave.dataSign=dataSignature)																												//áà ¢­¨¢ ¥¬ ¬¥âªã data
	{																																			//­ ç «® â¥« 
		chechedSteps++;																															//¨­ªà¥¬¨­¨àã¥¬ §­ ç¥­¨¥ áç¥âç¨ª  ¯à®å®¤ 
		pringDebugMsg(45,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
	}																																			//ª®­¥æ â¥« 
	else																																		//¨­ ç¥...
	{pringDebugMsg(40,0);}																														//...á®®¡é ¥¬ ®¡ ®è¨¡ª¥
	pringDebugMsg(46,0);																														//¯¨è¥¬ ® ­ ç «¥ çâ¥­¨ï ¯ à ¬¥âà®¢
	pringDebugMsg(47,0);																														//¯¨è¥¬ ¢ ª®­á®«ì
	printf(FileSizeMsg, Wave.chunkSizeBytes);																									//ãª §ë¢ ¥¬ ­  à §¬¥à ä ©« , ¢§ïâë© ¨§ § £®«®¢ª 
	pringDebugMsg(47,0);																														//¯¨è¥¬ ¢ ª®­á®«ì
	printf(FileSizeWoutHeaderMsg, Wave.chunkSizeWoutHeader);																					//¯¨è¥¬ ¢ ª®­á®«ì à §¬¥à ¡¥§ § £®«®¢ª 
	if(headerDifference==36)																													//áà ¢­¨¢ ¥¬ à §¬¥à § £®«®¢ª  ¡¥§ ãç¥â  ¡«®ª  ¤ ­­ëå
	{																																			//­ ç «® â¥« 
		chechedSteps++;																															//¨­ªà¥¬¨­¨àã¥¬ §­ ç¥­¨¥ áç¥âç¨ª  ¯à®å®¤ 
		pringDebugMsg(48,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
	}																																			//ª®­¥æ â¥« 
	else																																		//¨­ ç¥...
	{pringDebugMsg(49,0);}																														//...¯¨è¥¬ ¢ ª®­á®«ì á®®¡é¥­¨¥ ®¡ ®è¨¡ª¥
	pringDebugMsg(47,0);																														//¯¨è¥¬ ¢ ª®­á®«ì
	printf(SampleRateMsg, Wave.sampleRate);																										//¯¨è¥¬ ç áâ®âã ¤¨áªà¥â¨§ æ¨¨
	pringDebugMsg(47,0);																														//¯¨è¥¬ ¢ ª®­á®«ì
	printf(ByteRateMsg, Wave.byteRate);																											//¯¨è¥¬ ¡¨âà¥©â
	pringDebugMsg(47,0);																														//¯¨è¥¬ ¢ ª®­á®«ì
	printf(BitDepthMsg, Wave.BitDepth);																											//¯¨è¥¬ £«ã¡¨­ã ¢ë¡®àª¨
	pringDebugMsg(47,0);																														//¯¨è¥¬ ¢ ª®­á®«ì
	printf(ChannelsMsg, Wave.soundChannels);																									//¯¨è¥¬ ª®«¢® ª ­ «®¢
	pringDebugMsg(50,Wave.soundChannels);																										//¯¨è¥¬ ª®«¢® ª ­ «®¢
	pringDebugMsg(47,0);																														//¯¨è¥¬ ¢ ª®­á®«ì
	printf(BytesInSampleMsg, Wave.BytesInSample);																								//¯¨è¥¬ ª®«¨ç¥áâ¢® ¡ ©â ¢ ¢ë¡®àª¥
	pringDebugMsg(47,0);																														//¯¨è¥¬ ¢ ª®­á®«ì
	printf(CodecTypeMsg);																														//¯¨è¥¬ â¨¯ ª®¤¥ª 
	pringDebugMsg(51,Wave.compressionCode);																										//¯¨è¥¬ ª®¤ á¦ â¨ï
	wordSamplesValuePos=((Wave.chunkSizeWoutHeader-8)*8)/Wave.soundChannels/Wave.BitDepth;														//¢ëç¨á«ï¥¬ à áç¥â­®¥ ª®«¨ç¥áâ¢® ¢ë¡®à®ª
	pringDebugMsg(68, wordSamplesValuePos);																										//¯¨è¥¬ ¢ ª®­á®«ì
	if(chechedSteps==5)																															//áà ¢­¨¢ ¥¬ ª®«¨ç¥áâ¢® ¯à®©¤¥­­ëå íâ ¯®¢ á âà¥¡ã¥¬ë¬ ¢ â§
	{																																			//­ ç «® â¥«  æ¨ª« 
		pringDebugMsg(52,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		ahsoka=1;																																//¥á«¨ ¢á¥ £ã¤ â® ¢ëª¨¤ë¢ ¥â ä« £ ®¡ ãá¯¥å¥
		checkStatus(2);																															//¢ë§ë¢ ¥¬ ¯à®¢¥àªã ä« £ 
	}																																			//ª®­¥æ â¥« 
	else																																		//¨­ ç¥...
	{pringDebugMsg(17,0);}																														//á®®¡é ¥¬ ®¡ ®è¨¡ª¥ ¨ ¢ëå®¤¨¬ ¨§ ¯à®£à ¬¬ë
}																																				//ª®­¥æ â¥«  äã­ªæ¨¨
void structModifier(void)																														//äã­ªæ¨ï § ¯¨á¨ ¢ áâàãªâãàã
{																																				//­ ç «® â¥«  äã­ªæ¨¨
	float sampleDivide;																															//Š®áâë«ì, á®®â­®è¥­¨¥ ª®«¨ç¥áâ¢® ¢ë¡®à®ª ¨áå®¤­®£® ä ©«  ª ª®«¨ç¥áâ¢ã ¢ë¡®à®ª ¢§ïâëå ¨§ convertParams.ini
	uint16_t newBytesInSample;																													//‚à¥¬¥­­ ï ¯¥à¥¬¥­­ ï ¤«ï ¢ëç¨á«¥­¨ï ª®«¨ç¥áâ¢  ¡ ©â ¢ ®¤­®© ¢ë¡®àª¥ á® ¢á¥å ª ­ «®¢
	uint32_t newByteRate;																														//‚à¥¬¥­­ ï ¯¥à¥¬¥­­ ï ¤«ï ¢ëç¨á«¥­¨ï áª®à®áâ¨ ¯¥à¥¤ ç¨ ¤ ­­ëå,  ©â/á
	uint32_t newFileSizeWOutHeader;																												//‚à¥¬¥­­ ï ¯¥à¥¬¥­­ ï ¤«ï ¢ëç¨á«¥­¨ï à §¬¥à  ä ©«  ¡¥§ § £®«®¢ª 
	sampleDivide=Wave.sampleRate/FilSet.FSetSampleRate;																							//‘à §ã ¦¥ ¢ëç¨á«ïî á®®â­®è¥­¨ï ª®«¨ç¥áâ¢  ¢ë¡®à®ª, ­ ¯¥ç â î çãâì ¯®§¦¥
	pringDebugMsg(53,0);																														//‚ë¢®¤ á®®¡é¥­¨ï ® ­ ç «¥ à ¡®â¥ äã­ªæ¨¨
	pringDebugMsg(99, FilSet.FSetSamplesValue);																									//‚ë¢®¤ ¢ ª®­á®«ì
	pringDebugMsg(58,0);																														//‚ë¢®¤ á®®¡é¥­¨ï ® â®¬, çâ® é á ­ ç­¥âáï § ¯¨áì ¢ áâàãªâãàã
	Wave.sampleRate=FilSet.FSetSampleRate;																										//‡ ¯¨áì ¢ áâàãªâãàã ç áâ®âë ¤¨áªà¥â¨§ æ¨¨, ¯®«ãç¥­­ë¥ ¨§ ä ©«  convertParams.ini
	pringDebugMsg(55, Wave.sampleRate);																											//‚ë¢®¤ á®®¡é¥­¨ï ®¡ íâ®¬
	Wave.BitDepth=FilSet.FSetBitDepth;																											//‡ ¯¨áì ¢ áâàãªâãàã £«ã¡¨­ë ¢ë¡®àª¨, ¯®«ãç¥­­ë¥ ¨§ ä ©«  convertParams.ini
	pringDebugMsg(54, Wave.BitDepth);																											//‚ë¢®¤ á®®¡é¥­¨ï ®¡ íâ®¬
	Wave.soundChannels=FilSet.FSetChannels;																										//‡ ¯¨áì ¢ áâàãªâãàã ª®«¨ç¥áâ¢® ª ­ «®¢, ¯®«ãç¥­­ëå ¨§ ä ©«  convertParams.ini
	pringDebugMsg(57, Wave.soundChannels);																										//‚ë¢®¤ á®®¡é¥­¨ï ®¡ íâ®¬
	newByteRate=(Wave.sampleRate*Wave.BitDepth*Wave.soundChannels)/8;																			//‚ëç¨á«¥­¨ï áª®à®áâ¨ ¯¥à¥¤ ç¨ ¤ ­­ëå, ¡ ©â ¢ á¥ªã­¤ã
	Wave.byteRate=newByteRate;																													//‡ ¯¨áì ¢ áâàãªâãàã à¥§ã«ìâ â 
	pringDebugMsg(56, Wave.byteRate);																											//‚ë¢®¤ á®®¡é¥­¨ï ®¡ íâ®¬
	newBytesInSample=(Wave.BitDepth*Wave.soundChannels)/8;																						//‚ëç¨á«¥­¨¥ ª®«¨ç¥áâ¢  ¡ ©â®¢ ¢ ®¤­®© ¢ë¡®àª¥ á® ¢á¥å ª ­ «®¢
	Wave.BytesInSample=newBytesInSample;																										//‡ ¯¨áì ¢ áâàãªâãàã
	pringDebugMsg(67, Wave.BytesInSample);																										//‚ë¢®¤ á®®¡é¥­¨ï ®¡ íâ®¬
	printSampleDivide(sampleDivide);																											//‚ë¢®¤ â®ç­®£® á®®â­®è¥­¨ï ¢ë¡®à®ª
	newFileSizeWOutHeader=(((FilSet.FSetSamplesValue/sampleDivide)*Wave.BitDepth*Wave.soundChannels)/8)+8;										//‚ëç¨á«¥­¨¥ à §¬¥à  ä ©«  ¡¥§ § £®«®¢ª 
	Wave.chunkSizeWoutHeader=newFileSizeWOutHeader;																								//‡ ¯¨áì ¢ áâàãªâãàã
	pringDebugMsg(69, Wave.chunkSizeWoutHeader);																								//‚ë¢®¤ ¢ ª®­á®«ì
	Wave.chunkSizeBytes=newFileSizeWOutHeader+36;																								//„®¡ ¢«ïî 36 ¡ ©â § £®«®¢ª 
	pringDebugMsg(70, Wave.chunkSizeBytes);																										//‚ë¢®¤ ¢ ª®­á®«ì
	cruzo=1;																																	//‡ ¯¨áë¢ ¥¬ 1, ¢á¥ å®à®è®, ¢ ¤ «ì­¥©è¥¬ ¡ã¤¥â § ¯¨á ­ ª®¤ á ¬®¯à®¢¥àª¨ äã­ªæ¨¨
	checkStatus(6);																																//‚ë§ë¢ î äã­ªæ¨î ¯à®¢¥àª¨ ä« £  á®áâ®ï­¨ï
}																																				//ª®­¥æ â¥«  äã­ªæ¨¨
int WriteSettingsFile(void)																														//äã­ªæ¨ï ¯®¤£®â®¢ª¨ ¬®¤¨ä¨æ¨à®¢ ­­®£® § £®«®¢ª  ª § ¯¨á¨
{																																				//­ ç «® â¥«  äã­ªæ¨¨
	pringDebugMsg(75,0);																														//¯¨è¥¬ ¢ ª®­á®«ì á®®¡é¥­¨¥ ® ­ ç «¥ à ¡®âë
	clearHeaderBuffer();																														//ç¨áâ¨¬ ¡ãä¥à § £®«®¢ª 
	writeBuffer(headerAddrs[0], headerAddrs[1], Wave.RiffSign, headerWordSizeOf[0], headerWordInvert[0]);										//¯¨è¥¬ ¢ ¡ãä¥à ¬¥âªã RIFF
	writeBuffer(headerAddrs[1], headerAddrs[2], Wave.chunkSizeBytes, headerWordSizeOf[1], headerWordInvert[1]);									//¯¨è¥¬ ¢ ¡ãä¥à à §¬¥à ä ©« 
	writeBuffer(headerAddrs[2], headerAddrs[3], Wave.WaveSign, headerWordSizeOf[2], headerWordInvert[2]);										//¯¨è¥¬ ¢ ¡ãä¥à ¬¥âªã WAVE
	writeBuffer(headerAddrs[3], headerAddrs[4], Wave.fmtSign, headerWordSizeOf[3], headerWordInvert[3]);										//¯¨è¥¬ ¢ ¡ãä¥à ¬¥âªã fmt
	writeBuffer(headerAddrs[4], headerAddrs[5], Wave.DataFormatLenght, headerWordSizeOf[4], headerWordInvert[4]);								//¯¨è¥¬ ¢ ¡ãä¥à à §¬¥à ä ©« 
	writeBuffer(headerAddrs[5], headerAddrs[6], Wave.compressionCode, headerWordSizeOf[5], headerWordInvert[5]);								//¯¨è¥¬ ¢ ¡ãä¥à ª®¤ á¦ â¨ï
	writeBuffer(headerAddrs[6], headerAddrs[7], Wave.soundChannels, headerWordSizeOf[6], headerWordInvert[6]);									//¯¨è¥¬ ¢ ¡ãä¥à ª®«¢® ª ­ «®¢
	writeBuffer(headerAddrs[7], headerAddrs[8], Wave.sampleRate, headerWordSizeOf[7], headerWordInvert[7]);										//¯¨è¥¬ ¢ ¡ãä¥à ç áâ®âã ¤¨áªà¥â¨§ æ¨¨
	writeBuffer(headerAddrs[8], headerAddrs[9], Wave.byteRate, headerWordSizeOf[8], headerWordInvert[8]);										//¯¨è¥¬ ¢ ¡ãä¥à ¡¨âà¥©â
	writeBuffer(headerAddrs[9], headerAddrs[10], Wave.BytesInSample, headerWordSizeOf[9], headerWordInvert[9]);									//¯¨è¥¬ ¢ ¡ãä¥à à §¬¥à ¢ë¡®àª¨ ¢ ¡ ©â å
	writeBuffer(headerAddrs[10], headerAddrs[11], Wave.BitDepth, headerWordSizeOf[10], headerWordInvert[10]);									//¯¨è¥¬ ¢ ¡ãä¥à £«ã¡¨­ã ¢ë¡®àª¨
	writeBuffer(headerAddrs[11], headerAddrs[12], Wave.dataSign, headerWordSizeOf[11], headerWordInvert[11]);									//¯¨è¥¬ ¢ ¡ãä¥à ¬¥âªã data
	writeBuffer(headerAddrs[12], headerAddrs[13], Wave.chunkSizeWoutHeader, headerWordSizeOf[12], headerWordInvert[12]);						//¯¨è¥¬ ¢ ¡ãä¥à à §¬¥à ä ©«  ¡¥§ § £®«®¢ª 
	BufferReader();																																//ª®¯¨àã¥¬ á®¤¥à¦¨¬®¥ ¢ ®â¤¥«ì­ë© ¬ áá¨¢ ¤«ï ¯®ª §  ¥£® á®¤¥à¦¨¬®£® ¢ à¥¦¨¬¥ ®â« ¤ª¨
	pringDebugMsg(81,0);																														//ã¢¥¤®¬«ï¥¬ ®¡ íâ®¬
	printf("%s",fileNameHdrDat);
	FWr=fopen(fileNameHdrDat, "wb");																											//á®§¤ ¥¬ ä ©« § £®«®¢ª  á à ­­¥¥ á£¥­¥à¨à®¢ ­­ë¬ ¨¬¥­¥¬
	if(FWr != NULL)																																//¯à®¢¥àï¥¬ ã¤ «®áì «¨ á®§¤ âì ä ©«
	{																																			//­ ç «® â¥« (¨áâ¨­ )
		printf(" “á¯¥å\n");																														//¯¨è¥¬ ¢ ª®­á®«ì çâ® ¢á¥ å®à®è®
	}																																			//ª®­¥æ â¥« (¨áâ¨­ )
	else																																		//¨­ ç¥...
	{																																			//­ ç «® â¥« («®¦ì)
		printf(" ¥ ã¤ «®áì á®§¤ âì ä ©« %s\n",fileNameHdrDat);																					//...¯¨è¥¬ ® ­¥ª®â®àëå ¯à®¡«¥¬ å
		exit(0);																																//¢ëå®¤¨¬ á ª®¤®¬ ®è¨¡ª¨ 0
	}																																			//ª®­¥æ â¥« («®¦ì)
	fseek(FWr, 0, SEEK_SET);																													//ãáâ ­ ¢«¨¢ ¥¬ ªãàá®à ­  0
	fwrite(FileHeader, sizeof(uint8_t), sizeof(FileHeader), FWr);																				//¯¨è¥¬ § £®«®¢®ª ¢ ä ©«
	fclose(FWr);																																//§ ªàëâ¨¥ ä ©«  ¤«ï § ¯¨á¨
}																																				//ª®­¥æ â¥«  æ¨ª« 
int ReadSettingsFile(void)																														//ç¨â «ª  ¯ à ¬¥âà®¢ ¨§ ä ©« 
{																																				//­ ç «® â¥« 
	uint32_t fSrcTagEndPos;																														//®¡êï¢«ï¥¬ ¯¥à¥¬¥­­ãî ¢ ª®â®à®© ¡ã¤¥¬ åà ­¨âì  ¤à¥á â¥£  FEND ¤«ï ¨¬¥­¨ ¨áå®¤­¨ª 
	uint32_t fNamtagEndPos;																														//®¡êï¢«ï¥¬ ¯¥à¥¬¥­­ãî ¢ ª®â®à®¥ ¡ã¤¥¬ åà ­¨âì  ¤à¥á â¥£  FEND ¤«ï á£¥­¥à¨à®¢ ­­®£® ¨¬¥­¨ ä ©« 
	uint8_t readCursorPos=0;																													//®¡êï¢«ï¥¬ ¨­¤¥ªá­ãî ¯¥à¥¬¥­­ãî ¬ áá¨¢  ª®â®àãî ¡ã¤¥¬ ¯à¨¬¥­ïâì ¯à¨ ª®¯¨à®¢ ­¨¨
	char fSrcNameBuffer[64];																													//®¡êï¢«ï¥¬ ¬ áá¨¢ ¢ ª®â®à®¬ ¡ã¤¥â åà ­¨âìáï "®ç¨é¥­­®¥" ¨áå®¤­®¥ ¨¬ï ä ©« (¡¥§ â¥£®¢)
	char fNamNameBuffer[64];																													//®¡êï¢«ï¥¬ ¬ áá¨¢ ¢ ª®â®à®¬ ¡ã¤¥â åà ­¨âìáï "®ç¥é¥­­®¥" á£¥­¥à¨à®¢ ­­®¥ ¨¬ï ä ©« (¡¥§ â¥£®¢)
	memset(fSrcNameBuffer, 0x00, sizeof(fSrcNameBuffer));																						//ç¨áâ¨¬ ¬ áá¨¢ ¨áå®¤­®£® ¨¬¥­¨
	memset(fNamNameBuffer, 0x00, sizeof(fNamNameBuffer));																						//ç¨áâ¨¬ ¬ áá¨¢ á£¥­¥à¨à®¢ ­®£® ¨¬¥­¨
	char *endTag;																																//®¡êï¢«ï¥¬ ãª § â¥«ì ­  ¨­¤¥ªá á«®¢  ª®â®à®¥ ¨é¥âáï ¢ áâà®ª¥
	pringDebugMsg(59,1);																														//¯¨è¥¬ ¢ ª®­á®«ì ¨­äã ® çâ¥­¨¨ ä ©« 
	FSet=fopen("convertParams.ini", "rb");																										//®âªàë¢ ¥¬ ä ©« ª ª ¡¨­ à­¨ª
	if(!FSet)																																	//¯à®¢¥àï¥¬ ä ªâ¨ ®âªàëâ¨ï ä ©« 
	{																																			//­ ç «® â¥« 
		pringDebugMsg(88,0);																													//¥á«¨ ä ©« ­¥ ­ ©¤¥­, ¨«¨ ¥£® ­¥¢®§¬®¦­® ®âªàëâì, ¯ëâ ¥¬áï á®§¤ âì ¥£® ¢­®¢ì + ¯¨è¥¬ ¢ ª®­á®«ì
		printf("” ©« convertParams.ini ­¥ ­ ©¤¥­ ¨«¨ ¯®¢à¥¦¤¥­. ã¤¥â á®§¤ ­ ä ©« á ¯ à ¬¥âà ¬¨ ¨§ â¥ªãé¥£® § £®«®¢ª \n");						//¯¨è¥¬ ®¡ íâ®¬ ¢ ª®­á®«ì
		storeStructToFile();																													//§ ¯¨áë¢ ¥¬ ­ áâà®©ª¨ ¢ ä ©«
		pringDebugMsg(84,0);																													//¢ëå®¤ ¨§ ¯à®£à ¬¬¬ë
	}																																			//ª®­¥æ â¥« 
	else																																		//¨­ ç¥...
	{																																			//­ ç «® â¥« 
		pringDebugMsg(89,0);																													//...¯¨è¥¬ ¢ ª®­á®«ì
		printf("” ©« convertParams.ini ­ ©¤¥­ ¨ ®âªàëâ\n");																						//çâ® ä ©« ®âªàëâ																																			//ª®­¥æ â¥« 
		fread(fileMassive, 1, sizeof(fileMassive), FSet);																						//ç¨â ¥¬ ä ©« ãª § ­­ë© ¢  à£ã¬¥­â å à ­­¥¥
		cursorSymbol=strstr(fileMassive, wordFilenameSource);																					//¨é¥¬ â¥£ FSRC
		wordFsrcPos=cursorSymbol-fileMassive+1;																									//¯¨è¥¬  ¤à¥á ­ ç «  â¥£ 
		cursorPosit=wordFsrcPos+wordFilenameShift;																								//¯¨è¥¬  ¤à¥á ªãàá®à 
		fseek(FSet, cursorPosit, SEEK_SET);																										//áâ ¢¨¬ ªãàá®à ¯®  ¤à¥áã
		fscanf(FSet, "%s", &fileNameSrc);																										//ç¨â ¥¬ á®¤¥à¦¨¬®¥ ä ©«  ¯® ¢ëáâ ¢«¥­­®¬ã  ¤à¥áã
		endTag=strstr(fileNameSrc, wordSrcFilenameEnd);																							//§ ¯¨áë¢ ¥¬ ¢ ãª § â¥«ì  ¤à¥á ªãàá®à  á ª®â®à®£® ­ ç¨­ ¥âáï ­ ©¤¥­­®¥ á«®¢® FEND
		fSrcTagEndPos=endTag-fileNameSrc;																										//¯®¤áç¨âë¢ ¥¬ ¤«¨­ã ­ã¦­®£® äà £¬¥­ , ¢ ¤ ­­®¬ á«ãç ¥ íâ® ¨¬ï ¨áå®¤­®£® ä ©« 
		while(readCursorPos<fSrcTagEndPos)																										//®¡êï¢«ï¥¬ æ¨ª« ¤ã¡«¨à®¢ ­¨ï ¬ áá¨¢  ¢ ¤àã£®© ¬ áá¨¢, ª®â®àë© ­ã¦¥­ ¤«ï ¤¥¡ £ æ¥«¥©
		{																																		//­ ç «® æ¨ª« 
			fSrcNameBuffer[readCursorPos]=fileNameSrc[readCursorPos];																			//¯®á¨¬¢®«ì­® ¯¥à¥­®á¨¬ ¬ áá¨¢
			readCursorPos++;																													//¨­ªà¥¬¨­¨àã¥¬ ¨­¤¥ªá ¬ áá¨¢ 
		}																																		//ª®­¥æ â¥« 
		readCursorPos=0;																														//á¡à áë¢ ¥¬ áç¥âç¨ª ¨­¤¥ªá 
		cursorSymbol=strstr(fileMassive, wordFilename);																							//¨é¥¬ â¥£ FNAM
		wordFnamePos=cursorSymbol-fileMassive+1;																								//¯¨è¥¬  ¤à¥á ­ ç «  â¥£ 
		cursorPosit=wordFnamePos+wordFilenameShift;																								//¯¨è¥¬  ¤à¥á ªãàá®à 
		fseek(FSet, cursorPosit, SEEK_SET);																										//áâ ¢¨¬ ªãàá®à ¯®  ¤à¥áã
		fscanf(FSet, "%s", &fileName);																											//ç¨â ¥¬ á®¤¥à¦¨¬®¥ ä ©«  ¯® ¢ëáâ ¢«¥­­®¬ã  ¤à¥áã
		endTag=strstr(fileName, wordNameFilenameEnd);																							//§ ¯¨áë¢ ¥¬ ¢ ãª § â¥«ì  ¤à¥á ªãàá®à  á ª®â®à®£® ­ ç¨­ ¥âáï ­ ©¤¥­­®¥ á«®¢® FEND
		fNamtagEndPos=endTag-fileName;																											//¢ëç¨á«ï¥¬ ¤«¨­ã á£¥­¥à¨à®¢ ­­®£® ¨¬¥­¨ ä ©« 
		while(readCursorPos<fNamtagEndPos)																										//®¡êï¢«ï¥¬ æ¨ª« ª®¯¨à®¢ ­¨ï ¬ áá¨¢  ¢ ¤àã£®© ¬ áá¨¢ ª®â®àë© ­ã¦¥­ ¤«ï ¤¥¡ £ æ¥«¥©
		{																																		//­ ç «® â¥«  æ¨ª« 
			fNamNameBuffer[readCursorPos]=fileName[readCursorPos];																				//¯®á¨¬¢®«ì­® ¯¥à¥­®á¨¬ ¬ áá¨¢
			fileNameHdrDat[readCursorPos]=fileName[readCursorPos];
			readCursorPos++;																													//¨­ªà¥¬¨­¨àã¥¬ ¨­¤¥ªá ¬ áá¨¢ 
		}																																		//ª®­¥æ â¥« 
		cursorSymbol=strstr(fileMassive, wordConvert);																							//¨é¥¬ â¥£ Convert
		wordConvertPos=cursorSymbol-fileMassive+1;																								//¯¨è¥¬  ¤à¥á ­ ç «  â¥£ 
		cursorPosit=wordConvertPos+wordConvertShift;																							//¯¨è¥¬  ¤à¥á ªãàá®à 
		fseek(FSet, cursorPosit, SEEK_SET);																										//áâ ¢¨¬ ªãàá®à ¯®  ¤à¥áã
		fscanf(FSet, "%d", &FilSet.FSetWasConverted);																							//ç¨â ¥¬ á®¤¥à¦¨¬®¥ ¯® ¢ëáâ ¢«¥­­®¬ã  ¤à¥áã
		cursorSymbol=strstr(fileMassive, wordSampleRate);																						//¨é¥¬ â¥£ SampleRate
		wordSampleRatePos=cursorSymbol-fileMassive+1;																							//¯¨è¥¬  ¤à¥á ­ ç «  â¥£ 
		cursorPosit=wordSampleRatePos+wordSampleRateShift;																						//¯¨è¥¬  ¤à¥á ªãàá®à 
		fseek(FSet, cursorPosit, SEEK_SET);																										//áâ ¢¨¬ ªãàá®à ¯®  ¤à¥áã
		fscanf(FSet, "%d", &FilSet.FSetSampleRate);																								//ç¨â ¥¬ á®¤¥à¦¨¬®¥ ä ©«  ¯® ¢ëáâ ¢«¥­­®¬ã  ¤à¥áã
		cursorSymbol=strstr(fileMassive, wordChannels);																							//¨é¥¬ â¥£ Channels
		wordChannelsPos=cursorSymbol-fileMassive+1;																								//¯¨è¥¬  ¤à¥á ­ ç «  â¥£ 
		cursorPosit=wordChannelsPos+wordChannelsShift;																							//¯¨è¥¬  ¤à¥á ªãàá®à 
		fseek(FSet, cursorPosit, SEEK_SET);																										//áâ ¢¨¬ ªãàá®à ¯®  ¤à¥áã
		fscanf(FSet, "%d", &FilSet.FSetChannels);																								//ç¨â ¥¬ á®¤¥à¦¨¬®¥ ä ©«  ¯® ¢ëáâ ¢«¥­­®¬ã  ¤à¥áã
		cursorSymbol=strstr(fileMassive, wordBitsPerSample);																					//¨é¥¬ â¥£ BitsPerSample
		wordBitsPerSamplePos=cursorSymbol-fileMassive+1;																						//¯¨è¥¬  ¤à¥á ­ ç «  â¥£ 
		cursorPosit=wordBitsPerSamplePos+wordBitsPerSampleShift;																				//¯¨è¥¬  ¤à¥á ªãàá®à 
		fseek(FSet, cursorPosit, SEEK_SET);																										//áâ ¢¨¬ ªãàá®à ¯®  ¤à¥áã
		fscanf(FSet, "%d", &FilSet.FSetBitDepth);																								//ç¨â ¥¬ á®¤¥à¦¨¬®¥ ä ©«  ¯® ¢ëáâ ¢«¥­­®¬ã  ¤à¥áã
		cursorSymbol=strstr(fileMassive, WordCountOfSamples);																					//¨é¥¬ â¥£ BitsPerSample
		wordSamplesValuePos=cursorSymbol-fileMassive+1;																							//¯¨è¥¬  ¤à¥á ­ ç «  â¥£ 
		cursorPosit=wordSamplesValuePos+wordSamplesValueShift;																					//¯¨è¥¬  ¤à¥á ªãàá®à 
		fseek(FSet, cursorPosit, SEEK_SET);																										//áâ ¢¨¬ ªãàá®à ¯®  ¤à¥áã
		fscanf(FSet, "%d", &FilSet.FSetSamplesValue);																							//ç¨â ¥¬ á®¤¥à¦¨¬®¥ ä ©«  ¯® ¢ëáâ ¢«¥­­®¬ã  ¤à¥áã
		pringDebugMsg(89,0);																													//áàñ¬ ¢ ª®­á®«ì
		pringDebugMsg(94,fSrcTagEndPos);																										//¯¨è¥¬  ¤à¥á á¬¥é¥­¨ï ¯® â¥£ã FSRC
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		printf("ˆ¬ï ¨áå®¤­®£® ä ©« : %s\n", fSrcNameBuffer);																					//¯¨è¥¬ ¨¬ï ¨áå®¤­®£® ä ©« 
		pringDebugMsg(89,0);																													//áàñ¬ ¢ ª®­á®«ì
		pringDebugMsg(94,fNamtagEndPos);																										//¯¨è¥¬  ¤à¥á á¬¥é¥­¨ï ¯® â¥£ã FNAM
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		printf("ˆ¬ï ä ©«  á § £®«®¢ª®¬: %s\n", fNamNameBuffer);																					//¯¨è¥¬ ¨¬ï § £®«®¢®ç­®£® ä ©« 
		pringDebugMsg(89,0);																													//áàñ¬ ¢ ª®­á®«ì
		printf("€¤à¥á  á¬¥é¥­¨© ¯® â¥£ ¬ Convert,SampleRate,Channels,BitsPerSample,SamplesInChannel\n");										//¯¨è¥¬ ¨­äã çâ® é á ¡ã¤ãâ  ¤à¥á  á¬¥é¥­¨© â¥£®¢
		pringDebugMsg(89,0);																													//áàñ¬ ¢ ª®­á®«ì
		pringDebugMsg(90,wordConvertPos);																										//¯¨è¥¬  ¤à¥á á¬¥é¥­¨ï ¯® â¥£ã Convert
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		pringDebugMsg(90,wordSampleRatePos);																									//¯¨è¥¬  ¤à¥á á¬¥é¥­¨ï ¯® â¥£ã SampleRate
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		pringDebugMsg(90,wordChannelsPos);																										//¯¨è¥¬  ¤à¥á á¬¥é¥­¨ï ¯® â¥£ã Channels
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		pringDebugMsg(90,wordBitsPerSamplePos);																									//¯¨è¥¬  ¤à¥á á¬¥é¥­¨ï ¯® â¥£ã BitsPerSample
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		pringDebugMsg(90,wordSamplesValuePos);																									//¯¨è¥¬  ¤à¥á á¬¥é¥­¨ï ¯® â¥£ã BitsPerSample
	}																																			//ª®­¥æ â¥« 
	pringDebugMsg(89,0);																														//¯¨è¥¬ ¢ ª®­á®«ì
	if(DebugMode==1)																															//ª®áâë«ì ­  ¯à®¢¥àªã à¥¦¨¬  ®â« ¤ª¨
	{																																			//­ ç «® â¥« 
		printf("Š®«-¢® ª ­ «®¢: %d\n", FilSet.FSetChannels);																					//¯¨è¥¬ ª®«¨ç¥áâ¢® ª ­ «®¢
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		printf("— áâ®â  ¤¨áªà¥â¨§ æ¨¨: %d ƒæ\n", FilSet.FSetSampleRate);																		//¯¨è¥¬ ç áâ®âã ¤¨áªà¥â¨§ æ¨¨
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		printf("”« £ ª®­¢¥àâ æ¨¨: %d\n", FilSet.FSetWasConverted);																				//¯¨è¥¬ á®áâ®ï­¨¥ ä« £  ª®­¢¥àâ æ¨¨(¡ë«  «¨ ®­  ¨«¨ ­¥â)
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		printf("¨â ¢ ¢ë¡®àª¥: %d ¨â\n", FilSet.FSetBitDepth);																					//¯¨è¥¬ £«ã¡¨­ã ¢ë¡®àª¨
		pringDebugMsg(89,0);																													//¯¨è¥¬ ¢ ª®­á®«ì
		printf("Š®«¨ç¥áâ¢® ¢ë¡®à®ª ¢ ®¤­®¬ ª ­ «¥: %d\n", FilSet.FSetSamplesValue);																//¯¨è¥¬ ª®«¨ç¥áâ¢® ¢ë¡®à®ª ­  ®¤¨­ ª ­ «
	}																																			//ª®­¥æ â¥« 
	pringDebugMsg(60, FilSet.FSetSampleRate);																									//¯¨è¥¬ ç áâ®âã ¤¨áªà¥â¨§ æ¨¨ ¢ ª®­á®«ì
	pringDebugMsg(62, FilSet.FSetChannels);																										//¯¨è¥¬ ª®«¨ç¥áâ¢® ª ­ «®¢ ¢ ª®­á®«ì
	pringDebugMsg(61, FilSet.FSetBitDepth);																										//¯¨è¥¬ £«ã¡¨­ã ¢ë¡®àª¨ ¢ ª®­á®«ì
	if(FilSet.FSetWasConverted==0)																												//¯à®¢¥àª  ä ªâ  ª®­¢¥àâ æ¨¨
	{																																			//­ ç «® â¥« 
		pringDebugMsg(63, FilSet.FSetWasConverted);																								//¯¨è¥¬ ¢ ª®­á®«ì á­®¢ 
		Egor=1;																																	//áâ ¢¨¬ ä« £
		checkStatus(5);																															//¢ë§ë¢ ¥¬ ¯à®¢¥àªã ä« £ 
		pringDebugMsg(83,0);																													//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ çâ® á ä ©«®¬ ¥é¥ ­¨ç¥£® ­¥ ¤¥« «¨
	}																																			//ª®­¥æ â¥« 
	else																																		//¨­ ç¥...
	{																																			//­ ç «® â¥« 
		pringDebugMsg(63, FilSet.FSetWasConverted);																								//...­ ç¨­ ¥¬ ä®à¬¨à®¢ âì § £®«®¢®ª
		Egor=1;																																	//¯®¤­¨¬ ¥¬ ä« £ å¥å¥))
		checkStatus(5);																															//¢ë§ë¢ ¥¬ ¯à®¢¥àªã
		fclose(FSet);																															//§ ªàë¢ ¥¬ ä ©« â.ª ®­ ¡®«ìè¥ ­¥ ­ã¦¥­ ¢ ¤ ­­ë© ¬®¬¥­â
		structModifier();																														//¯¨è¥¬ § £®«®¢®ª ¢ ä ©«
		return 0;																																//¢®§¢à é ¥¬ 0
	}																																			//ª®­¥æ â¥« 
	fclose(FSet);																																//§ ªàë¢ ¥¬ ¯®â®ª, ¥á«¨ ®­ £¤¥-â® ¥é¥ ­¥ ¡ë« § ªàëâ
}																																				//ª®­¥æ äã­ªæ¨¨
inline void clearByteBuffer(void)																												//®ç¨áâª  ¢à¥¬¥­­®£® ¡ãä¥à (¢áâà ¨¢ ¥¬ ï äã­ªæ¨ï)
{																																				//­ ç «® â¥« 
	pringDebugMsg(79,0);																														//¯¨è¥¬ ¢ ª®­á®«ì ã¢¥¤®¬«¥­¨¥ çâ® ¨¤¥â ç¨áâª  ¡ãä¥à 
	memset(ByteBuffer,0x00,sizeof(ByteBuffer));																									//ç¨áâ¨¬ ¬ áá¨¢
}																																				//ª®­¥æ â¥« 
inline void clearHeaderBuffer(void)																												//®ç¨áâª  ¬ áá¨¢  § £®«®¢ª (¢áâà ¨¢ ¥¬ ï äã­ªæ¨ï
{																																				//­ ç «® â¥« 
	pringDebugMsg(80,0);																														//¯¨è¥¬ á®®¡é¥­¨¥ ® â®¬ çâ® é á ¡ã¤¥¬ ç¨áâ¨âì ¬ áá¨¢
	for(int i=0;i<43;i++)																														//­ ç «® æ¨ª«  ç¨áâª¨
	{																																			//­ ç «® â¥«  æ¨ª« 
		FileHeader[i]=0;																														//ç¨áâ¨¬ ¯®¡ ©â®¢® ¬ áá¨¢
	}																																			//ª®­¥æ â¥«  æ¨ª« 
}																																				//ª®­¥æ â¥«  äã­ªæ¨¨
inline void BufferReader(void)																													//äã­ªæ¨ï ª®¯¨à®¢ ­¨¥ § £®«®¢ª  ¢ ®â¤¥«ì­ë© ¬ áá¨¢ ¤«ï ¯®ª §  ®â« ¤®ç­ëå ã¢¥¤®¬«¥­¨©(¢áâà ¨¢ ¥¬ ï)
{																																				//­ ç «® â¥« 
	writeDebugHeaderBuffer();																													//¢ë§ë¢ ¥¬ äã­ªæ¨î ª®¯¨à®¢ ­¨ï
	pringDebugMsg(25,0);																														//¯¨è¥¬ ã¢¥¤®¬«¥­¨¥ ®¡ íâ®¬
}																																				//ª®­¥æ â¥« 
uint32_t writeBuffer(int startOffset, int endOffset, uint32_t paramToWrite, int wordSize, bool SwapByte)										//äã­ªæ¨ï § ¯¨á¨ ¡ãä¥à 
{																																				//­ ç «® â¥« 
	int debugCursorPos=0;																														//¨­¨æ¨ «¨§¨àã¥¬ ¯¥à¥¬¥­­ãî
	int bufferPos=0;																															//¨­æ¨ ¨«¨§¨àã¥¬ ¯¥à¥¬¥­­ãî ¨­¤¥ªá  ¬ áá¨¢®¢
	pringDebugMsg(76,paramToWrite);																												//¯¨è¥¬ ¢ ª®­á®«ì çâ® ­ ç¨­ ¬ ¯¨á âì ¯®«ãç¥­­ë© ¯ à ¬¥âà
	switch(wordSize)																															//¢ë¡®à á¯®á®¡  § ¯¨á¨ ¢ § ¢¨á¨¬®áâ¨ ®â à §¬¥à  ¯®«ãç¥­­®£® ­  ¢å®¤¥
	{																																			//â® ¥áâì 0 ¡ ©â - ®è¨¡ª , 1 ¡ ©â - ¯¨è¥¬ 1 ¡ ©â, 2 ¡ ©â  - ¡ ©â  ¯¨è¥¬ ¨ â.¤
		case 0:																																	//¢ á«ãç ¥ ¥á«¨ 0 ¡ ©â(NANI?)
			pringDebugMsg(77,0);																												//¯¨è¥¬ çâ® â ª¨å ¯¥à¥¬¥­­ëå ­¥ áãé¥áâ¢ã¥â ¨ ¢ëå®¤¨¬ ¨§ ¯à®£à ¬¬ë
			break;																																//¢ëå®¤ ¨§ æ¨ª« 
		case 1:																																	//¢ á«ãç ¥ ¥á«¨ 1 ¡ ©â
			ByteBuffer[0]=paramToWrite;																											//¯¨è¥¬ ¢ ¡ãä¥à 1 ¡ ©â
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 2:																																	//¢ á«ãç ¥ ¥á«¨ 2 ¡ ©â 
			ByteBuffer[0]=paramToWrite;																											//¯¨è¥¬ áâ àè¨© ¡ ©â
			ByteBuffer[1]=paramToWrite>>8;																										//¯¨è¥¬ ¬« ¤è¨© ¡ ©â
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
		case 4:																																	//¢ á«ãç ¥ ¥á«¨ 4 ¡ ©â 
			ByteBuffer[0]=paramToWrite;																											//¯¨è¥¬ áâ àè¨© ¡ ©â
			ByteBuffer[1]=paramToWrite>>8;																										//¯¨è¥¬ ¡ ©â ¯®¬« ¤è¥
			ByteBuffer[2]=paramToWrite>>16;																										//¯¨è¥¬ ¡ ©â ¯®¬« ¤è¥
			ByteBuffer[3]=paramToWrite>>24;																										//¯¨è¥¬ ¬« ¤è¨© ¡ ©â
			break;																																//¢ëå®¤¨¬ ¨§ æ¨ª« 
	}																																			//ª®­¥æ â¥«  æ¨ª« 
	massiveSwap(SwapByte);																														//¯¥à¥¢®à ç¨¢ ¥¬ ¬ áá¨¢
	while(debugCursorPos<wordSize)																												//¢ë§ë¢ ¥¬ æ¨ª« ¯®ª §  á®¤¥à¦¨¬®£® ¢à¥¬¥­­®£® ¡ãä¥à 
	{																																			//­ ç «® æ¨ª« 
		pringDebugMsg(78, ByteBuffer[debugCursorPos]);																							//¯®ª §ë¢ ¥¬ ¢ ª®­á®«¨ â® çâ® â ¬ ­ å®¤¨âáï
		debugCursorPos++;																														//¨­ªà¥¬¨­¨àã¥¬ ¨­¤¥ªá
	}																																			//ª®­¥æ æ¨ª« 
	debugCursorPos=0;																															//á¡à áë¢ ¥¬ ¯¥à¥¬¥­­ãî
	while(startOffset<endOffset)																												//­ ç «® æ¨ª«  § ¯¨á¨ ª®¯¨à®¢ ­¨ï ¨§ ¡ãä¥à  ¢ § £®«®¢®ª á § ¤ ­­ë¬ á¬¥é¥­¨¥¬
	{																																			//­ ç «® â¥«  æ¨ª« 
		FileHeader[startOffset]=ByteBuffer[bufferPos];																							//¯®¡ ©â®¢®¥ ª®¯¨à®¢ ­¨¥ ¨§ ¢à¥¬¥­­®£® ¬ áá¨¢ 
		bufferPos++;																															//¨­ªà¥¬¨­¨àã¥¬ ¯¥à¥¬¥­­ãî ¨­¤¥ªá  ¬ áá¨¢  ¢à¥¬¥­­®£® ¡ãä¥à 
		startOffset++;																															//¨­ªà¥¬¨­¨àã¥¬ ¯¥à¥¬¥­­ãî ¬ áá¨¢  § £®«®¢ª 
	}																																			//ª®­¥æ æ¨ª« 
	bufferPos=0;																																//á¡à áë¢ ¥¬ ¯¥à¥¬¥­­ãî
	clearByteBuffer();																															//ç¨áâ¨¬ ¡ãä¥à
}																																				//ª®­¥æ äã­ªæ¨¨
void storeStructToFile(void)																													//äã­ªæ¨ï § ¯¨á¨ ­ áâà®¥ª ¢ ä ©«
{																																				//­ ç «® äã­ªæ¨¨
	uint8_t crlfSign[2]={0x0D, 0x0A};																											//¬¥âª  CR LF(¯¥à¥­®á ª à¥âª¨ ­  ­®¢ãî áâà®ªã)
	bool WordConverted=0;																														//¨­¨æ¨ «¨§¨àã¥¬ ä« £
	char *FnameSrc="FSRC>";																														//¨¬ï ¨áå®¤­®£® ä ©« 
	char *FnameBod="FBOD>";																														//¨¬ï â¥«  ä ©« 
	char *Fnametgt="FTGT>";																														//¨¬ï ä ©«  ¯®á«¥ áª«¥¨¢ ­¨ï
	char *Fname="FNAM>";																														//¨¬ï ä ©« 
	char *WordConvert="Convert=";																												//®¡à §¥æ â¥£  Convert
	char *WordSampleRate="SampleRate=";																											//®¡à §¥æ â¥£  SampleRate
	char *WordChannels="Channels=";																												//®¡à §¥æ â¥£  Channels
	char *WordBitsPerSample="BitsPerSample=";																									//®¡à §¥æ â¥£  BitsPerSample
	char *WordCountOfSamples="SamplesInChannel=";																								//®¡à §¥æ â¥£  SamplesInChannel
	pringDebugMsg(86,0);																														//ã¢¥¤®¬«ï¥¬ çâ® é á ¡ã¤¥¬ ¯¨á âì ¢ ä ©«
	FSet=fopen("convertParams.ini", "wb");																										//®âªàë¢ ¥¬ ä ©« ­  § ¯¨áì ª ª ¡¨­ à­ë©(§ ç ¡¨­ à­ë©? âãâ â¥ªáâ ®¡ëç­ë©)
	fseek(FSet, 0, SEEK_SET);																													//ãáâ ­¢«¨¢ ¥¬ ªãàá®à ­  0
	fprintf(FSet, "%s", FnameSrc);																												//¯¨è¥¬ â¥£ FNAM
	fprintf(FSet, "%s", fileNameSrc);																											//¯¨è¥¬ ¨¬ï ä ©« 
	fprintf(FSet, "%s", wordSrcFilenameEnd);																									//¯¨è¥¬ â¥£ >FSND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//¯¨è¥¬ CR LF
	fprintf(FSet, "%s", Fname);																													//¯¨è¥¬ â¥£ FNAM
	fprintf(FSet, "%s", fileNameHdrDat);																										//¯¨è¥¬ ¨¬ï ä ©« 
	fprintf(FSet, "%s", wordNameFilenameEnd);																									//¯¨è¥¬ â¥£ >FNND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//¯¨è¥¬ CR LF
	fprintf(FSet, "%s", FnameBod);																												//¯¨è¥¬ â¥£ FBOD
	fprintf(FSet, "%s", fileNameBodDat);																										//¯¨è¥¬ ¨¬ï ä ©« 
	fprintf(FSet, "%s", wordBodyFilenameEnd);																									//¯¨è¥¬ â¥£ >FBND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//¯¨è¥¬ CR LF
	fprintf(FSet, "%s", Fnametgt);																												//¯¨è¥¬ â¥£ FTGT
	fprintf(FSet, "%s", fileNameTgtDat);																										//¯¨è¥¬ ¨¬ï ä ©« 
	fprintf(FSet, "%s", wordTargFilenameEnd);																									//¯¨è¥¬ â¥£ >FTND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//¯¨è¥¬ CR LF
	fprintf(FSet, "%s", WordConvert);																											//¯¨è¥¬ â¥£ Convert
	fprintf(FSet, "%d", WordConverted);																											//¯¨è¥¬ ä« £ á®áâ®ï­¨ï
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//¯¨è¥¬ CR LF
	fprintf(FSet, "%s", WordSampleRate);																										//¯¨è¥¬ â¥£ SampleRate
	fprintf(FSet, "%d", Wave.sampleRate);																										//¯¨è¥¬ ç áâ®âã ¤¨áªà¥â¨§ æ¨¨ ç¨á«®¬
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//¯¨è¥¬ CR LF
	fprintf(FSet, "%s", WordChannels);																											//¯¨è¥¬ â¥£ Channels
	fprintf(FSet, "%d", Wave.soundChannels);																									//¯¨è¥¬ ª®«¨ç¥áâ¢® ª ­ «®¢
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//¯¨è¥¬ CR LF
	fprintf(FSet, "%s", WordBitsPerSample);																										//¯¨è¥¬ â¥£ BitsPerSample
	fprintf(FSet, "%d", Wave.BitDepth);																											//¯¨è¥¬ £«ã¡¨­ã ¢ë¡®àª¨
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//¯¨è¥¬ CR LF
	fprintf(FSet, "%s", WordCountOfSamples);																									//¯¨è¥¬ â¥£ BitsPerSample
	fprintf(FSet, "%d", wordSamplesValuePos);																									//¯¨è¥¬ ª®«¨ç¥áâ¢® ¢ë¡®à®ª
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//¯¨è¥¬ CR LF
	fclose(FSet);																																//§ ªàë¢ ¥¬ ä ©«
	pringDebugMsg(87,0);																														//®âç¨âë¢ ¥¬áï ¢ ª®­á®«ì ® ¯à®¤¥« ­­®© à ¡®â¥
}																																				//ª®­¥æ äã­ªæ¨¨
