#include<locale.h>																																//¨¡«¨®â¥ª  «®ª «¨§ æ©, ­ã¦­  ¤«ï àãááª®£® ï§ëª  ¢ ª®­á®«¨
#include<stdbool.h>																																//¨¡«¨®â¥ª  ¤«ï à ¡®âë á ¤¢®¨ç­ë¬¨ ç¨á« ¬, C99
#include<stdint.h>																																//¨¡¨«®â¥ª  ¤«ï à ¡®âë á ­¥áâ ­¤ àâ­ë¬¨ ç¨á« ¬¨ uint8_t, uint16_t, uint32_t
#include<stdio.h>																																//¨¡«¨®â¥ª  ¤«ï à ¡®âë á ª®­á®«ìî, ¢ë¢®¤ ¢ ª®­á®«ì ¨ áç¨âë¢ ­¨¥ á ­¥¥
#include<conio.h>																																//¨¡¨«®â¥ª 
#include<stdlib.h>																																//¨¡¨«®â¥ª 
#include "debug.h"																																//‡ £®«®¢®ª ª íâ®¬ã ä ©«ã á ¯¥à¥ç¨á«¥­­ë¬¨ äã­ªæ¨ï¬¨
bool debugFlag=1;																																//¥á«¨ 1 - ¯®ª §ë¢ âì á®®¡é¥­¨ï ®â« ¤ª¨, ¥á«¨ 0 - ­¥ ¯®ª §ë¢ âì á®®¡é¥­¨ï ®â« ¤ª¨, ¯®ª  ¢ ª®¤¥ ­¥ ¯à¨¬¥­¥­
uint8_t FileHeaderMSG[44];																														//áî¤  ¯¥à¥¯¨áë¢ ¥âáï § £®«®¢®ª ¤«ï ¢ë¢®¤  ¢ à¥¦¨¬ ®â« ¤ª¨
extern void printSampleDivide(float SamplesDivide)
{
	if(debugFlag==1)
	{
		printf("[Ž’‹€„Š€][ŒŽ„.‘’“Š’“›] ‘®®â­®è¥­¨¥ ª®«¨ç¥áâ¢  ¢ë¡®à®ª ¨áå®¤­®£® ä ©«  ª §­ ç¥­¨î ¨§ convertParams.ini: %f\n", SamplesDivide);
	}
}
extern void pringDebugMsg(int debugMsgNum, uint32_t firstParameter)
{
	if(debugFlag==1)
	{
		switch(debugMsgNum)
		{
			case 0:
				printf("[Ž’‹€„Š€][—’…ˆ… ‡€ƒŽ‹Ž‚Š€] ”ã­ªæ¨ï ¢¥à­ã«  §­ ç¥­¨¥: 0x%08X\n", firstParameter);
				break;
			case 1:
				printf("[Ž’‹€„Š€][—’…ˆ… ‡€ƒŽ‹Ž‚Š€] ”ã­ªæ¨ï ¢¥à­ã«  §­ ç¥­¨¥: 0x%04X\n", firstParameter);
				break;
			case 2:
				printf("[Ž’‹€„Š€][—’…ˆ… ‡€ƒŽ‹Ž‚Š€] ”ã­ªæ¨ï ¢¥à­ã«  §­ ç¥­¨¥: 0x%02X\n", firstParameter);
				break;
			case 3:
				printf("[Ž’‹€„Š€][—’…ˆ… ‡€ƒŽ‹Ž‚Š€] ‡ ¯¨áì ¢ áâàãªâãàã... ");
				break;
			case 4:
				printf("[Ž’‹€„Š€][ŠŽ‚…’€–ˆŸ 32>>32 ˆ’] à¥®¡à §®¢ ­¨¥ à §àï¤­®áâ¨ ­¥ âà¥¡ã¥âáï\n");
				break;
			case 5:
				printf("[Ž’‹€„Š€][ŠŽ‚…’€–ˆŸ 32>>16 ˆ’] ‚ë¯®«­ï¥âáï ¯à¥®¡à §®¢ ­¨¥ à §àï¤­®áâ¨ á«®¢  ¤«ï § ¯¨á¨ ¢ áâàãªâãàã...\n");
				break;
			case 6:
				printf("[Ž’‹€„Š€][ŠŽ‚…’€–ˆŸ 32>>8 ˆ’] ‚ë¯®«­ï¥âáï ¯à¥®¡à §®¢ ­¨¥ à §àï¤­®áâ¨ á«®¢  ¤«ï § ¯¨á¨ ¢ áâàãªâãàã...\n");
				break;
			case 7:
				printf("[Ž’‹€„Š€][—’…ˆ… ‡€ƒŽ‹Ž‚Š€] ‡ ¯®«­¥­¨¥ áâàãªâãàë WaveHeader (%d/13)...\n", firstParameter+1);
				break;
			case 8:
				printf("_________________________________________________________________________________________________________________\n");
				break;
			case 9:
				printf("[Ž’‹€„Š€][Ž‚…Š€ ‘’“Š’“›] —â¥­¨¥ ¨ ¯à®¢¥àª  § ¯¨á ­­®© áâàãªâãàë\n");
				break;
			case 10:
				printf("[Ž’‹€„Š€][ŠŽ‚…’…] à¥®¡à §®¢ ­¨¥ § ¢¥àè¥­® ãá¯¥è­®\n");
				break;
			case 11:
				printf("[Ž’‹€„Š€][—’…ˆ…] ‡ ¯®«­¥­¨¥ áâàãªâãàë ¯à®è«® ãá¯¥è­®\n");
				break;
			case 12:
				printf("[Ž’‹€„Š€][€€‹ˆ‡] à®¢¥àª  áâàãªâãàë § ¢¥àè¥­  ¨ ®­  ¯à ¢¨«ì­ ï\n");
				break;
			case 13:
				printf("[Ž’‹€„Š€][‡€ƒŽ‹Ž‚ŽŠ] Œ®¤¨ä¨ª æ¨ï § £®«®¢ª  ¯à®¢¥¤¥­  ãá¯¥è­®\n");
				break;
			case 14:
				printf("[Ž’‹€„Š€][‡€ˆ‘œ] ‡ £®«®¢®ª ãá¯¥è­® § ¯¨á ­\n");
				break;
			case 15:
				printf("[Ž’‹€„Š€][ŠŽ‚…’…] Žè¨¡ª  ¯à¥®¡à §®¢ ­¨ï!\n");
				printf("[Ž’‹€„Š€][Ž†ˆ„€ˆ…]  ¦¬¨â¥ Enter ¤«ï ¯à®¤®«¦¥­¨ï...\n");
				getchar();
				exit(1);
				break;
			case 16:
				printf("[Ž’‹€„Š€][—’…ˆ…] Žè¨¡ª  ¯à¨ § ¯®«­¥­¨¨ áâàãªâãàë\n");
				printf("[Ž’‹€„Š€][Ž†ˆ„€ˆ…]  ¦¬¨â¥ Enter ¤«ï ¯à®¤®«¦¥­¨ï...\n");
				getchar();
				exit(1);
				break;
			case 17:
				printf("[Ž’‹€„Š€][€€‹ˆ‡] ‘âàãªâãà  á®¤¥à¦¨â ®è¨¡ª¨, ¯à®¢¥àìâ¥ æ¥«®áâ­®áâì ä ©« \n");
				printf("[Ž’‹€„Š€][Ž†ˆ„€ˆ…]  ¦¬¨â¥ Enter ¤«ï ¯à®¤®«¦¥­¨ï...\n");
				getchar();
				exit(1);
				break;
			case 18:
				printf("[Ž’‹€„Š€][‡€ƒŽ‹Ž‚ŽŠ] Žè¨¡ª  ¯à¨ ¢ë¯®«­¥­¨¨ ¬®¤¨ä¨ª æ¨¨ § £®«®¢ª \n");
				printf("[Ž’‹€„Š€][Ž†ˆ„€ˆ…]  ¦¬¨â¥ Enter ¤«ï ¯à®¤®«¦¥­¨ï...\n");
				getchar();
				exit(1);
				break;
			case 19:
				printf("[Ž’‹€„Š€][‡€ˆ‘œ] Žè¨¡ª  ¯à¨ § ¯¨á¨ § £®«®¢ª  ¢ ä ©«\n");
				printf("[Ž’‹€„Š€][Ž†ˆ„€ˆ…]  ¦¬¨â¥ Enter ¤«ï ¯à®¤®«¦¥­¨ï...\n");
				getchar();
				exit(1);
				break;
			case 20:
				printf("[Ž’‹€„Š€][ŠŽ„ ‚›•Ž„€ ”“Š–ˆˆ]  à ¬¥âà convertState = %d\n", firstParameter);
				break;
			case 21:
				printf("[Ž’‹€„Š€][ŠŽ„ ‚›•Ž„€ ”“Š–ˆˆ]  à ¬¥âà analyzeState = %d\n", firstParameter);
				break;
			case 22:
				printf("[Ž’‹€„Š€][ŠŽ„ ‚›•Ž„€ ”“Š–ˆˆ]  à ¬¥âà ahsoka = %d\n", firstParameter);
				break;
			case 23:
				printf("[Ž’‹€„Š€][ŠŽ„ ‚›•Ž„€ ”“Š–ˆˆ]  à ¬¥âà gabella = %d\n", firstParameter);
				break;
			case 24:
				printf("[Ž’‹€„Š€][ŠŽ„ ‚›•Ž„€ ”“Š–ˆˆ]  à ¬¥âà doubledoor = %d\n", firstParameter);
				break;
			case 25:
				for(int i=0;i<44;i++)
				{
					printf("[Ž’‹€„Š€][—’…ˆ…]  ©â ¨§ § £®«®¢ª : 0x%02X (%d/43)\n", FileHeaderMSG[i],i+1);
				}
				break;
			case 26:
				printf("[Ž’‹€„Š€][—’…ˆ… ‡€ƒŽ‹Ž‚Š€] —â¥­¨¥ § £®«®¢ª ...\n");
				break;
			case 27:
				printf("[Ž’‹€„Š€][ŠŽ‚…’…] ®«ãç¥­® 32 ¡¨â­®¥ á«®¢®: 0x%08X\n", firstParameter);
				break;
			case 28:
				printf("[Ž’‹€„Š€][ŠŽ‚…’…] ®«ãç¥­® 16 ¡¨â­®¥ á«®¢®: 0x%04X\n", firstParameter);
				break;
			case 29:
				printf("[Ž’‹€„Š€][Ž‘Ž‚.”Š–ˆŸ] ‡ £®«®¢®ª ¯à®ç¨â ­ ãá¯¥è­®\n");
				break;
			case 30:
				printf("[Ž’‹€„Š€][ŠŽ‚…’…] ¥áãé¥áâ¢ãîé¨© ¯ à ¬¥âà\n");
				break;
			case 31:
				printf("[Ž’‹€„Š€][ŠŽ‚…’…] ˆáå®¤­®¥ á«®¢® ¨¬¥¥â ¤«¨­ã 8 ¡¨â. à¥®¡à §®¢ ­¨¥ ­¥ ¨¬¥¥â á¬ëá« \n");
				break;
			case 32:
				printf("[Ž’‹€„Š€][“”…] ‘®¤¥à¦¨¬®¥ ¡ãä¥à : 0x%02X\n", firstParameter);
				break;
			case 33:
				printf("[Ž’‹€„Š€][Ž‘Ž‚.”Š–ˆŸ]  ç «® à ¡®âë...\n");
				break;
			case 34:
				printf("[Ž’‹€„Š€][ˆ‚…‘ˆŸ] ¥à¥áâ ­®¢ª  ¡ ©â®¢ ­¥ âà¥¡ã¥âáï\n");
				break;
			case 35:
				printf("[Ž’‹€„Š€][ˆ‚…‘ˆŸ] ¥à¥áâ ­®¢ª  ¡ ©â®¢\n");
				break;
			case 36:
				printf("[Ž’‹€„Š€][…†ˆŒ Ž’‹€„Šˆ] ‚ª«îç¥­ à¥¦¨¬ ®â« ¤ª¨\n");
				break;
			case 37:
				printf("[Ž’‹€„Š€][Ž‘’€Ž‚] à®¨§®è¥« ®áâ ­®¢ ¨§-§  ®âáãâáâ¢¨ï ­¥ª®â®àëå ¢ ¦­ëå äã­ªæ¨©(®á­®¢­®© ª®¤ § ¢¥àè¥­ ­  ~95%%)\n");//¡®«¥¥ ­¥ ¨á¯®«ì§ã¥âáï
				break;
			case 38:
				printf("[Ž’‹€„Š€][Ž†ˆ„€ˆ…]  ¦¬¨â¥ Enter ¤«ï ¯à®¤®«¦¥­¨ï...\n");
				break;
			case 39:
				printf("[Ž’‹€„Š€][Ž‚…Š€ ‘’“Š’“›] Œ¥âª  RIFF ®¡­ àã¦¥­  ¨ ®­  ­  ¬¥áâ¥\n");
				break;
			case 40:
				printf("[Ž’‹€„Š€][Ž‚…Š€ ‘’“Š’“›] Ž¤­  ¨§ ¬¥â®ª ®âáãâá¢ã¥â. ‚ë â®ç­® ®âªàë¢ ¥â¥ WAV ä ©«?\n");
				break;
			case 41:
				printf(" “á¯¥å!(%d/13)\n", firstParameter+1);
				break;
			case 42:
				printf(" Žè¨¡ª !(%d/13)\n", firstParameter+1);
				break;
			case 43:
				printf("[Ž’‹€„Š€][Ž‚…Š€ ‘’“Š’“›] Œ¥âª  WAVE ®¡­ àã¦¥­  ¨ ®­  ­  ¬¥áâ¥\n");
				break;
			case 44:
				printf("[Ž’‹€„Š€][Ž‚…Š€ ‘’“Š’“›] Œ¥âª  fmt  ®¡­ àã¦¥­  ¨ ®­  ­  ¬¥áâ¥\n");
				break;
			case 45:
				printf("[Ž’‹€„Š€][Ž‚…Š€ ‘’“Š’“›] Œ¥âª  data ®¡­ àã¦¥­  ¨ ®­  ­  ¬¥áâ¥\n");
				break;
			case 46:
				printf("[Ž’‹€„Š€][Ž‚…Š€ ‘’“Š’“›] —¨â î ¯ à ¬¥âàë ä ©« ...\n");
				break;
			case 47:
				printf("[Ž’‹€„Š€][Ž‚…Š€ ‘’“Š’“›] ");
				break;
			case 48:
				printf("[Ž’‹€„Š€][Ž‚…Š€ ‘’“Š’“›] „«¨­  § £®«®¢ª  ¡¥§ ãç¥â  ¬¥âª¨ data ¯à ¢¨«ì­ ï ¨ á®áâ ¢«ï¥â 36  ©â\n");
				break;
			case 49:
				printf("[Ž’‹€„Š€][Ž‚…Š€ ‘’“Š’“›] „«¨­  § £®«®¢ª  ­¥ á®¢¯ ¤ ¥â á íâ «®­®¬, ¯à®£à ¬¬  ®áâ ­®¢«¥­ ");
				getchar();
				exit(1);
				break;
			case 50:
				if(firstParameter==1)
				{
					printf(", Œ®­®\n");
				}
				if(firstParameter==2)
				{
					printf(", ‘â¥à¥®\n");
				}
				if(firstParameter==4)
				{
					printf(", Š¢ ¤à®\n");
				}
				break;
			case 51:
				if(firstParameter==1)
				{
					printf(" PCM\n");
				}
				break;
			case 52:
				printf("[Ž’‹€„Š€][Ž‚…Š€ ‘’“Š’“›] ‘âàãªâãà  ¯à®ç¨â ­  ¨ ®­  ¯à ¢¨«ì­ ï\n");
				break;
			case 53:
				printf("[Ž’‹€„Š€][ŒŽ„.‘’“Š’“›] ¥¤ ªâ¨àãî áâàãªâãàã...\n");
				break;
			case 54:
				printf("[Ž’‹€„Š€][ŒŽ„.‘’“Š’“›] ‡ ¯¨á ­  £«ã¡¨­  ¢ë¡®àª¨: %d ¨â\n", firstParameter);
				break;
			case 55:
				printf("[Ž’‹€„Š€][ŒŽ„.‘’“Š’“›] ‡ ¯¨á ­  ç áâ®â  ¤¨áªà¥â¨§ æ¨¨: %d ƒæ\n", firstParameter);
				break;
			case 56:
				printf("[Ž’‹€„Š€][ŒŽ„.‘’“Š’“›] ‡ ¯¨á ­  áª®à®áâì ¯¥à¥¤ ç¨ ¤ ­­ëå: %d  ©â/á\n", firstParameter);
				break;
			case 57:
				printf("[Ž’‹€„Š€][ŒŽ„.‘’“Š’“›] ‡ ¯¨á ­® ª®«¨ç¥áâ¢® ª ­ «®¢: %d", firstParameter);
				if(firstParameter==1)
				{
					printf(", ¬®­®\n");
				}
				if(firstParameter==2)
				{
					printf(", áâ¥à¥®\n");
				}
				if(firstParameter==4)
				{
					printf(", ª¢ ¤à®\n");
				}
				break;
			case 58:
				printf("[Ž’‹€„Š€][ŒŽ„.‘’“Š’“›] ‡ ¯¨áì §­ ç¥­¨© ¢ áâàãªâãàã...\n");
				break;
			case 59:
				printf("[Ž’‹€„Š€][—’…ˆ… €€Œ…’Ž‚] Žâªàë¢ î ä ©« á ¯ à ¬¥âà ¬¨ ª®­¢¥àâ æ¨¨");
				if(firstParameter==0)
				{
					printf(" ¤«ï § ¯¨á¨\n");
				}
				else
				{
					printf(" ¤«ï çâ¥­¨ï\n");
				}
				break;
			case 60:
				printf("[Ž’‹€„Š€][—’…ˆ… €€Œ…’Ž‚] — áâ®â  ¤¨áªà¥â¨§ æ¨¨: %d ƒæ\n", firstParameter);
				break;
			case 61:
				printf("[Ž’‹€„Š€][—’…ˆ… €€Œ…’Ž‚] ƒ«ã¡¨­  ¢ë¡®àª¨: %d ¨â\n", firstParameter);
				break;
			case 62:
				printf("[Ž’‹€„Š€][—’…ˆ… €€Œ…’Ž‚] Š ­ «®¢: %d, ", firstParameter);
				if(firstParameter==1)
				{
					printf("¬®­®\n");
				}
				if(firstParameter==2)
				{
					printf("áâ¥à¥®\n");
				}
				if(firstParameter==4)
				{
					printf("ª¢ ¤à®(­¥¯®«­ ï ¯®¤¤¥à¦ª )\n");
				}
				break;
			case 63:
				printf("[Ž’‹€„Š€][—’…ˆ… €€Œ…’Ž‚] Š®­¢¥àâ¨à®¢ ­? ");
				if(firstParameter==1)
				{
					printf("¤ \n");
				}
				else
				{
					printf("­¥â\n");
				}
				break;
			case 64:
				printf("[Ž’‹€„Š€][—’…ˆ… €€Œ…’Ž‚]  à ¬¥âàë ãá¯¥è­® ¯à®ç¨â ­ë ¨§ ä ©«  convertParams.ini\n");
				break;
			case 65:
				printf("[Ž’‹€„Š€][—’…ˆ… €€Œ…’Ž‚] à®¨§®è«  ®è¨¡ª  ¯à¨ çâ¥­¨¨ ¯ à ¬¥âà®¢ ¨§ ä ©«  convertParams.ini\n");
				printf("[Ž’‹€„Š€][Ž†ˆ„€ˆ…]  ¦¬¨â¥ Enter ¤«ï ¯à®¤®«¦¥­¨ï...\n");
				getchar();
				exit(1);
				break;
			case 66:
				printf("[Ž’‹€„Š€][ŠŽ„ ‚›•Ž„€ ”“Š–ˆˆ]  à ¬¥âà Egor = %d\n", firstParameter);
				break;
			case 67:
				printf("[Ž’‹€„Š€][ŒŽ„.‘’“Š’“›] ‡ ¯¨á ­® ª®«¨ç¥áâ¢® ¡ ©â®¢ ¢ ®¤­®© ¢ë¡®àª¥ á® ¢á¥å ª ­ «®¢: %d  ©â\n", firstParameter);
				break;
			case 68:
				printf("[Ž’‹€„Š€][Ž‚…Š€ ‘’“Š’“›] Š®«¨ç¥áâ¢® ¢ë¡®à®ª ¢ 1 ª ­ «¥ %d(+/-8) ‚ë¡®à®ª\n", firstParameter);
				break;
			case 69:
				printf("[Ž’‹€„Š€][ŒŽ„.‘’“Š’“›] à¨¬¥à­ë© à §¬¥à ä ©«  ¡¥§ § £®«®¢ª , ®á­®¢ë¢ ïáì ­  ¯®«ãç¥­­ëå ¯ à ¬¥âà å: %d  ©â\n", firstParameter);
				break;
			case 70:
				printf("[Ž’‹€„Š€][ŒŽ„.‘’“Š’“›] à¨¬¥à­ë© à §¬¥à ä ©« , ®á­®¢ë¢ ïáì ­  ¯®«ãç¥­­ëå ¯ à ¬¥âà å: %d  ©â\n", firstParameter);
				break;
			case 71:
				printf("[Ž’‹€„Š€][ŠŽ„ ‚›•Ž„€ ”“Š–ˆˆ]  à ¬¥âà cruzo = %d\n", firstParameter);
				break;
			case 72:
				printf("[Ž’‹€„Š€][ŒŽ„.‘’“Š’“›] ¥¤ ªâ¨à®¢ ­¨¥ áâàãªâãàë § ¢¥àè¥­®\n", firstParameter);
				break;
			case 73:
				printf("[Ž’‹€„Š€][‡€ˆ‘œ] Žè¨¡ª  ¯à¨ à¥¤ ªâ¨à®¢ ­¨¨ áâàãªâãàë\n");
				printf("[Ž’‹€„Š€][Ž†ˆ„€ˆ…]  ¦¬¨â¥ Enter ¤«ï ¯à®¤®«¦¥­¨ï...\n");
				getchar();
				exit(1);
				break;
			case 74:
				printf("[Ž’‹€„Š€][ŠŽ„ ‚›•Ž„€ ”“Š–ˆˆ] ‚ë§¢ ­  äã­ªæ¨ï ¯à®¢¥àª¨ ä« £  á®áâ®ï­¨ï á ª®¤®¬ ¯à®¢¥àª¨: %d\n", firstParameter);
				break;
			case 75:
				printf("[Ž’‹€„Š€][‡€ˆ‘œ ‡€ƒŽ‹Ž‚Š€]  ç¨­ î § ¯¨áì ¯®«ãç¥­­®£® § £®«®¢ª  ¢ ä ©« convertedHeader.txt\n");
				break;
			case 76:
				printf("[Ž’‹€„Š€][‡€ˆ‘œ ‚ “”…] ‡ ¯¨áë¢ î ¯®«ãç¥­­®¥ á«®¢® 0x%08X ¢ ¡ãä¥à\n", firstParameter);
				break;
			case 77:
				printf("[Ž’‹€„Š€][‡€ˆ‘œ ‚ “”…] ‘«®¢  á ­ã«¥¢ë¬ à §¬¥à®¬ ­¥ áãé¥áâ¢ã¥â!\n");
				printf("[Ž’‹€„Š€][Ž†ˆ„€ˆ…]  ¦¬¨â¥ Enter ¤«ï ¯à®¤®«¦¥­¨ï...\n");
				getchar();
				exit(1);
				break;
			case 78:
				printf("[Ž’‹€„Š€][‡€ˆ‘œ ‚ “”…]  ©â ¨§ ¢à¥¬¥­­®£® ¡ãä¥à : 0x%02X\n", firstParameter);
				break;
			case 79:
				printf("[Ž’‹€„Š€][Ž—ˆ‘’Š€] Žç¨áâª  ¢à¥¬¥­­®£® ¡ãä¥à ...\n");
				break;
			case 80:
				printf("[Ž’‹€„Š€][Ž—ˆ‘’Š€] Žç¨áâª  § £®«®¢®ç­®£® ¡ãä¥à ...\n");
				break;
			case 81:
				printf("[Ž’‹€„Š€][‡€ˆ‘œ] ‡ ¯¨áì á®¤¥à¦¨¬®£® ¡ãä¥à  ¢ ä ©«...");
				break;
			case 82:
				printf("[Ž’‹€„Š€][Ž‘Ž‚.”Š–ˆŸ] ‡ £®«®¢®ª ãá¯¥è­® ¯¥à¥¯¨á ­ á ­®¢ë¬¨ ¯ à ¬¥âà ¬¨, ­¥ § ¡ã¤ì áª«¥¨âì § £®«®¢ª ¨ á®¤¥à¦¨¬®¥ ä ©«  converted.dat\n");
				break;
			case 83:
				printf("[Ž’‹€„Š€][—’…ˆ… €€Œ…’Ž‚] ” ©« ¥é¥ ­¥ ¡ë« ¯à¥®¡à §®¢ ­, ¤ «ìè­¥©è ï à ¡®â  ¯à®£à ¬¬ë ­¥ ¨¬¥¥â á¬ëá« \n");
				//printf("[Ž’‹€„Š€][Ž†ˆ„€ˆ…]  ¦¬¨â¥ Enter ¤«ï ¯à®¤®«¦¥­¨ï...\n");	//ŠŽ‘’›‹œ „‹Ÿ €‚’ŽŒ€’ˆ‡€–ˆˆ
				//getchar();
				exit(1);
				break;
			case 84:
				printf("[Ž’‹€„Š€][Ž†ˆ„€ˆ…]  ¦¬¨â¥ Enter ¤«ï ¯à®¤®«¦¥­¨ï...\n");
				//getchar();
				exit(1);
				break;
			case 85:
				printf("[Ž’‹€„Š€][Ž‘Ž‚.”Š–ˆŸ] Š®«¨ç¥áâ¢® ¯®«ãç¥­­ëå  à£ã¬¥­â®¢: %d\n", firstParameter);
				break;
			case 86:
				printf("[Ž’‹€„Š€][‡€ˆ‘œ] ‡ ¯¨áì ¤ ­­ëå ¨§ áâàãªâãàë ¢ ä ©«\n");
				break;
			case 87:
				printf("[Ž’‹€„Š€][‡€ˆ‘œ] ‡ ¯¨áì § ¢¥àè¥­ \n");
				break;
			case 88:
				printf("[Ž’‹€„Š€][‡€ˆ‘œ] ");
				break;
			case 89:
				printf("[Ž’‹€„Š€][—’…ˆ…] ");
				break;
			case 90:
				printf(" ç «® á«®¢  ­ : %d  ©â\n", firstParameter);
				break;
			case 91:
				printf("’ ª®© ä ©« ­¥ áãé¥áâ¢ã¥â\n");
				break;
			case 92:
				printf("”ã­ªæ¨ï strrchr ¢¥à­ã«  NULL\n");
				break;
			case 93:
				printf("®á«¥¤­¥¥ ¢å®¦¤¥­¨¥ á¨¬¢®« : %d\n", firstParameter);
				break;
			case 94:
				printf("Š®«¨ç¥áâ¢® á¨¬¢®«®¢ ¢ ¨¬¥­¨ ä ©«  = %d\n", firstParameter);
				break;
			case 95:
				printf("[Ž’‹€„Š€][ŒŽ„.ˆŒ…ˆ ”€ˆ‹€] ");
				break;
			case 96:
				printf(" ç¨­ î £¥­¥à æ¨î ¨¬¥­¨ ä ©«  § £®«®¢ª \n");
				break;
			case 97:
				printf("‘£¥­¥à¨à®¢ ­­®¥ ¨¬ï ä ©«  á®åà ­¥­® ¤«ï ¤ «ì­¥©è¥© à ¡®âë\n");
				break;
			case 98:
				printf("„«¨­  ¨¬¥­¨ ä ©«  á®¢¯ ¤ ¥â á ¤«¨­®© § ¯¨á ­­®£® ¬ áá¨¢ \n");
				break;
			case 99:
				printf("[Ž’‹€„Š€][ŒŽ„.‘’“Š’“›] Š®«¨ç¥áâ¢® ¢ë¡®à®ª ¢ ¯à¥®¡à §®¢ ­­®¬ ä ©«¥: %d\n", firstParameter);
				break;
			case 100:
				printf(" ç¨­ î £¥­¥à æ¨î ¨¬¥­¨ ä ©«  â¥« \n");
				break;
			case 101:
				printf("[Ž’‹€„Š€]");
				break;
		}
	}
}
