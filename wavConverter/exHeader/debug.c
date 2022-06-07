#include<locale.h>																																//������⥪� ���������, �㦭� ��� ���᪮�� �몠 � ���᮫�
#include<stdbool.h>																																//������⥪� ��� ࠡ��� � �����묨 �᫠�, C99
#include<stdint.h>																																//������⥪� ��� ࠡ��� � ���⠭����묨 �᫠�� uint8_t, uint16_t, uint32_t
#include<stdio.h>																																//������⥪� ��� ࠡ��� � ���᮫��, �뢮� � ���᮫� � ���뢠��� � ���
#include<conio.h>																																//������⥪�
#include<stdlib.h>																																//������⥪�
#include "debug.h"																																//��������� � �⮬� 䠩�� � ����᫥��묨 �㭪�ﬨ
bool debugFlag=1;																																//�᫨ 1 - �����뢠�� ᮮ�饭�� �⫠���, �᫨ 0 - �� �����뢠�� ᮮ�饭�� �⫠���, ���� � ���� �� �ਬ����
uint8_t FileHeaderMSG[44];																														//� ��९��뢠���� ��������� ��� �뢮�� � ०�� �⫠���
extern void printSampleDivide(float SamplesDivide)
{
	if(debugFlag==1)
	{
		printf("[�������][���.���������] ���⭮襭�� ������⢠ �롮ப ��室���� 䠩�� � ���祭�� �� convertParams.ini: %f\n", SamplesDivide);
	}
}
extern void pringDebugMsg(int debugMsgNum, uint32_t firstParameter)
{
	if(debugFlag==1)
	{
		switch(debugMsgNum)
		{
			case 0:
				printf("[�������][������ ���������] �㭪�� ���㫠 ���祭��: 0x%08X\n", firstParameter);
				break;
			case 1:
				printf("[�������][������ ���������] �㭪�� ���㫠 ���祭��: 0x%04X\n", firstParameter);
				break;
			case 2:
				printf("[�������][������ ���������] �㭪�� ���㫠 ���祭��: 0x%02X\n", firstParameter);
				break;
			case 3:
				printf("[�������][������ ���������] ������ � ��������... ");
				break;
			case 4:
				printf("[�������][����������� 32>>32 ���] �८�ࠧ������ ࠧ�來��� �� �ॡ����\n");
				break;
			case 5:
				printf("[�������][����������� 32>>16 ���] �믮������ �८�ࠧ������ ࠧ�來��� ᫮�� ��� ����� � ��������...\n");
				break;
			case 6:
				printf("[�������][����������� 32>>8 ���] �믮������ �८�ࠧ������ ࠧ�來��� ᫮�� ��� ����� � ��������...\n");
				break;
			case 7:
				printf("[�������][������ ���������] ���������� �������� WaveHeader (%d/13)...\n", firstParameter+1);
				break;
			case 8:
				printf("_________________________________________________________________________________________________________________\n");
				break;
			case 9:
				printf("[�������][�������� ���������] �⥭�� � �஢�ઠ ����ᠭ��� ��������\n");
				break;
			case 10:
				printf("[�������][���������] �८�ࠧ������ �����襭� �ᯥ譮\n");
				break;
			case 11:
				printf("[�������][������] ���������� �������� ��諮 �ᯥ譮\n");
				break;
			case 12:
				printf("[�������][������] �஢�ઠ �������� �����襭� � ��� �ࠢ��쭠�\n");
				break;
			case 13:
				printf("[�������][���������] ����䨪��� ��������� �஢����� �ᯥ譮\n");
				break;
			case 14:
				printf("[�������][������] ��������� �ᯥ譮 ����ᠭ\n");
				break;
			case 15:
				printf("[�������][���������] �訡�� �८�ࠧ������!\n");
				printf("[�������][��������] ������ Enter ��� �த�������...\n");
				getchar();
				exit(1);
				break;
			case 16:
				printf("[�������][������] �訡�� �� ���������� ��������\n");
				printf("[�������][��������] ������ Enter ��� �த�������...\n");
				getchar();
				exit(1);
				break;
			case 17:
				printf("[�������][������] ������� ᮤ�ন� �訡��, �஢���� 楫��⭮��� 䠩��\n");
				printf("[�������][��������] ������ Enter ��� �த�������...\n");
				getchar();
				exit(1);
				break;
			case 18:
				printf("[�������][���������] �訡�� �� �믮������ ����䨪�樨 ���������\n");
				printf("[�������][��������] ������ Enter ��� �த�������...\n");
				getchar();
				exit(1);
				break;
			case 19:
				printf("[�������][������] �訡�� �� ����� ��������� � 䠩�\n");
				printf("[�������][��������] ������ Enter ��� �த�������...\n");
				getchar();
				exit(1);
				break;
			case 20:
				printf("[�������][��� ������ �������] ��ࠬ��� convertState = %d\n", firstParameter);
				break;
			case 21:
				printf("[�������][��� ������ �������] ��ࠬ��� analyzeState = %d\n", firstParameter);
				break;
			case 22:
				printf("[�������][��� ������ �������] ��ࠬ��� ahsoka = %d\n", firstParameter);
				break;
			case 23:
				printf("[�������][��� ������ �������] ��ࠬ��� gabella = %d\n", firstParameter);
				break;
			case 24:
				printf("[�������][��� ������ �������] ��ࠬ��� doubledoor = %d\n", firstParameter);
				break;
			case 25:
				for(int i=0;i<44;i++)
				{
					printf("[�������][������] ���� �� ���������: 0x%02X (%d/43)\n", FileHeaderMSG[i],i+1);
				}
				break;
			case 26:
				printf("[�������][������ ���������] �⥭�� ���������...\n");
				break;
			case 27:
				printf("[�������][���������] ����祭� 32 ��⭮� ᫮��: 0x%08X\n", firstParameter);
				break;
			case 28:
				printf("[�������][���������] ����祭� 16 ��⭮� ᫮��: 0x%04X\n", firstParameter);
				break;
			case 29:
				printf("[�������][�����.�����] ��������� ���⠭ �ᯥ譮\n");
				break;
			case 30:
				printf("[�������][���������] ���������騩 ��ࠬ���\n");
				break;
			case 31:
				printf("[�������][���������] ��室��� ᫮�� ����� ����� 8 ���. �८�ࠧ������ �� ����� ��᫠\n");
				break;
			case 32:
				printf("[�������][�����] ����ন��� ����: 0x%02X\n", firstParameter);
				break;
			case 33:
				printf("[�������][�����.�����] ��砫� ࠡ���...\n");
				break;
			case 34:
				printf("[�������][��������] ����⠭���� ���⮢ �� �ॡ����\n");
				break;
			case 35:
				printf("[�������][��������] ����⠭���� ���⮢\n");
				break;
			case 36:
				printf("[�������][����� �������] ����祭 ०�� �⫠���\n");
				break;
			case 37:
				printf("[�������][�������] �ந��襫 ��⠭�� ��-�� ������⢨� �������� ������ �㭪権(�᭮���� ��� �����襭 �� ~95%%)\n");//����� �� �ᯮ������
				break;
			case 38:
				printf("[�������][��������] ������ Enter ��� �த�������...\n");
				break;
			case 39:
				printf("[�������][�������� ���������] ��⪠ RIFF �����㦥�� � ��� �� ����\n");
				break;
			case 40:
				printf("[�������][�������� ���������] ���� �� ��⮪ ��������. �� �筮 ���뢠�� WAV 䠩�?\n");
				break;
			case 41:
				printf(" �ᯥ�!(%d/13)\n", firstParameter+1);
				break;
			case 42:
				printf(" �訡��!(%d/13)\n", firstParameter+1);
				break;
			case 43:
				printf("[�������][�������� ���������] ��⪠ WAVE �����㦥�� � ��� �� ����\n");
				break;
			case 44:
				printf("[�������][�������� ���������] ��⪠ fmt  �����㦥�� � ��� �� ����\n");
				break;
			case 45:
				printf("[�������][�������� ���������] ��⪠ data �����㦥�� � ��� �� ����\n");
				break;
			case 46:
				printf("[�������][�������� ���������] ���� ��ࠬ���� 䠩��...\n");
				break;
			case 47:
				printf("[�������][�������� ���������] ");
				break;
			case 48:
				printf("[�������][�������� ���������] ����� ��������� ��� ��� ��⪨ data �ࠢ��쭠� � ��⠢��� 36 ����\n");
				break;
			case 49:
				printf("[�������][�������� ���������] ����� ��������� �� ᮢ������ � �⠫����, �ணࠬ�� ��⠭������");
				getchar();
				exit(1);
				break;
			case 50:
				if(firstParameter==1)
				{
					printf(", ����\n");
				}
				if(firstParameter==2)
				{
					printf(", ��८\n");
				}
				if(firstParameter==4)
				{
					printf(", �����\n");
				}
				break;
			case 51:
				if(firstParameter==1)
				{
					printf(" PCM\n");
				}
				break;
			case 52:
				printf("[�������][�������� ���������] ������� ���⠭� � ��� �ࠢ��쭠�\n");
				break;
			case 53:
				printf("[�������][���.���������] ��������� ��������...\n");
				break;
			case 54:
				printf("[�������][���.���������] ����ᠭ� ��㡨�� �롮ન: %d ���\n", firstParameter);
				break;
			case 55:
				printf("[�������][���.���������] ����ᠭ� ���� ����⨧�樨: %d ��\n", firstParameter);
				break;
			case 56:
				printf("[�������][���.���������] ����ᠭ� ᪮���� ��।�� ������: %d ����/�\n", firstParameter);
				break;
			case 57:
				printf("[�������][���.���������] ����ᠭ� ������⢮ �������: %d", firstParameter);
				if(firstParameter==1)
				{
					printf(", ����\n");
				}
				if(firstParameter==2)
				{
					printf(", ��८\n");
				}
				if(firstParameter==4)
				{
					printf(", �����\n");
				}
				break;
			case 58:
				printf("[�������][���.���������] ������ ���祭�� � ��������...\n");
				break;
			case 59:
				printf("[�������][������ ����������] ���뢠� 䠩� � ��ࠬ��ࠬ� �������樨");
				if(firstParameter==0)
				{
					printf(" ��� �����\n");
				}
				else
				{
					printf(" ��� �⥭��\n");
				}
				break;
			case 60:
				printf("[�������][������ ����������] ����� ����⨧�樨: %d ��\n", firstParameter);
				break;
			case 61:
				printf("[�������][������ ����������] ��㡨�� �롮ન: %d ���\n", firstParameter);
				break;
			case 62:
				printf("[�������][������ ����������] �������: %d, ", firstParameter);
				if(firstParameter==1)
				{
					printf("����\n");
				}
				if(firstParameter==2)
				{
					printf("��८\n");
				}
				if(firstParameter==4)
				{
					printf("�����(�������� �����প�)\n");
				}
				break;
			case 63:
				printf("[�������][������ ����������] �������஢��? ");
				if(firstParameter==1)
				{
					printf("��\n");
				}
				else
				{
					printf("���\n");
				}
				break;
			case 64:
				printf("[�������][������ ����������] ��ࠬ���� �ᯥ譮 ���⠭� �� 䠩�� convertParams.ini\n");
				break;
			case 65:
				printf("[�������][������ ����������] �ந��諠 �訡�� �� �⥭�� ��ࠬ��஢ �� 䠩�� convertParams.ini\n");
				printf("[�������][��������] ������ Enter ��� �த�������...\n");
				getchar();
				exit(1);
				break;
			case 66:
				printf("[�������][��� ������ �������] ��ࠬ��� Egor = %d\n", firstParameter);
				break;
			case 67:
				printf("[�������][���.���������] ����ᠭ� ������⢮ ���⮢ � ����� �롮થ � ��� �������: %d ����\n", firstParameter);
				break;
			case 68:
				printf("[�������][�������� ���������] ������⢮ �롮ப � 1 ������ %d(+/-8) �롮ப\n", firstParameter);
				break;
			case 69:
				printf("[�������][���.���������] �ਬ��� ࠧ��� 䠩�� ��� ���������, �᭮�뢠��� �� ����祭��� ��ࠬ����: %d ����\n", firstParameter);
				break;
			case 70:
				printf("[�������][���.���������] �ਬ��� ࠧ��� 䠩��, �᭮�뢠��� �� ����祭��� ��ࠬ����: %d ����\n", firstParameter);
				break;
			case 71:
				printf("[�������][��� ������ �������] ��ࠬ��� cruzo = %d\n", firstParameter);
				break;
			case 72:
				printf("[�������][���.���������] ������஢���� �������� �����襭�\n", firstParameter);
				break;
			case 73:
				printf("[�������][������] �訡�� �� ।���஢���� ��������\n");
				printf("[�������][��������] ������ Enter ��� �த�������...\n");
				getchar();
				exit(1);
				break;
			case 74:
				printf("[�������][��� ������ �������] �맢��� �㭪�� �஢�ન 䫠�� ���ﭨ� � ����� �஢�ન: %d\n", firstParameter);
				break;
			case 75:
				printf("[�������][������ ���������] ��稭�� ������ ����祭���� ��������� � 䠩� convertedHeader.txt\n");
				break;
			case 76:
				printf("[�������][������ � �����] �����뢠� ����祭��� ᫮�� 0x%08X � ����\n", firstParameter);
				break;
			case 77:
				printf("[�������][������ � �����] ����� � �㫥�� ࠧ��஬ �� �������!\n");
				printf("[�������][��������] ������ Enter ��� �த�������...\n");
				getchar();
				exit(1);
				break;
			case 78:
				printf("[�������][������ � �����] ���� �� �६������ ����: 0x%02X\n", firstParameter);
				break;
			case 79:
				printf("[�������][�������] ���⪠ �६������ ����...\n");
				break;
			case 80:
				printf("[�������][�������] ���⪠ ��������筮�� ����...\n");
				break;
			case 81:
				printf("[�������][������] ������ ᮤ�ন���� ���� � 䠩�...");
				break;
			case 82:
				printf("[�������][�����.�����] ��������� �ᯥ譮 ��९�ᠭ � ���묨 ��ࠬ��ࠬ�, �� ����� ᪫���� �������� � ᮤ�ন��� 䠩�� converted.dat\n");
				break;
			case 83:
				printf("[�������][������ ����������] ���� �� �� �� �८�ࠧ����, ����譥��� ࠡ�� �ணࠬ�� �� ����� ��᫠\n");
				//printf("[�������][��������] ������ Enter ��� �த�������...\n");	//������� ��� �������������
				//getchar();
				exit(1);
				break;
			case 84:
				printf("[�������][��������] ������ Enter ��� �த�������...\n");
				//getchar();
				exit(1);
				break;
			case 85:
				printf("[�������][�����.�����] ������⢮ ����祭��� ��㬥�⮢: %d\n", firstParameter);
				break;
			case 86:
				printf("[�������][������] ������ ������ �� �������� � 䠩�\n");
				break;
			case 87:
				printf("[�������][������] ������ �����襭�\n");
				break;
			case 88:
				printf("[�������][������] ");
				break;
			case 89:
				printf("[�������][������] ");
				break;
			case 90:
				printf("��砫� ᫮�� ��: %d ����\n", firstParameter);
				break;
			case 91:
				printf("����� 䠩� �� �������\n");
				break;
			case 92:
				printf("�㭪�� strrchr ���㫠 NULL\n");
				break;
			case 93:
				printf("��᫥���� �宦����� ᨬ����: %d\n", firstParameter);
				break;
			case 94:
				printf("������⢮ ᨬ����� � ����� 䠩�� = %d\n", firstParameter);
				break;
			case 95:
				printf("[�������][���.����� �����] ");
				break;
			case 96:
				printf("��稭�� ������� ����� 䠩�� ���������\n");
				break;
			case 97:
				printf("������஢����� ��� 䠩�� ��࠭��� ��� ���쭥�襩 ࠡ���\n");
				break;
			case 98:
				printf("����� ����� 䠩�� ᮢ������ � ������ ����ᠭ���� ���ᨢ�\n");
				break;
			case 99:
				printf("[�������][���.���������] ������⢮ �롮ப � �८�ࠧ������� 䠩��: %d\n", firstParameter);
				break;
			case 100:
				printf("��稭�� ������� ����� 䠩�� ⥫�\n");
				break;
			case 101:
				printf("[�������]");
				break;
		}
	}
}
