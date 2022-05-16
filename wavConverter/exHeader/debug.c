#include<locale.h>																																//���������� ����������, ����� ��� �������� ����� � �������
#include<stdbool.h>																																//���������� ��� ������ � ��������� ������, C99
#include<stdint.h>																																//���������� ��� ������ � �������������� ������� uint8_t, uint16_t, uint32_t
#include<stdio.h>																																//���������� ��� ������ � ��������, ����� � ������� � ���������� � ���
#include<conio.h>																																//����������
#include<stdlib.h>																																//����������
#include "debug.h"																																//��������� � ����� ����� � �������������� ���������
bool debugFlag=1;																																//���� 1 - ���������� ��������� �������, ���� 0 - �� ���������� ��������� �������, ���� � ���� �� ��������
uint8_t FileHeaderMSG[44];																														//���� �������������� ��������� ��� ������ � ����� �������
extern void printSampleDivide(float SamplesDivide)
{
	if(debugFlag==1)
	{
		printf("[�������][���.���������] ����������� ���������� ������� ��������� ����� � �������� �� convertParams.ini: %f\n", SamplesDivide);
	}
}
extern void pringDebugMsg(int debugMsgNum, uint32_t firstParameter)
{
	if(debugFlag==1)
	{
		switch(debugMsgNum)
		{
			case 0:
				printf("[�������][������ ���������] ������� ������� ��������: 0x%08X\n", firstParameter);
				break;
			case 1:
				printf("[�������][������ ���������] ������� ������� ��������: 0x%04X\n", firstParameter);
				break;
			case 2:
				printf("[�������][������ ���������] ������� ������� ��������: 0x%02X\n", firstParameter);
				break;
			case 3:
				printf("[�������][������ ���������] ������ � ���������... ");
				break;
			case 4:
				printf("[�������][����������� 32>>32 ���] �������������� ����������� �� ���������\n");
				break;
			case 5:
				printf("[�������][����������� 32>>16 ���] ����������� �������������� ����������� ����� ��� ������ � ���������...\n");
				break;
			case 6:
				printf("[�������][����������� 32>>8 ���] ����������� �������������� ����������� ����� ��� ������ � ���������...\n");
				break;
			case 7:
				printf("[�������][������ ���������] ���������� ��������� WaveHeader (%d/13)...\n", firstParameter+1);
				break;
			case 8:
				printf("_________________________________________________________________________________________________________________\n");
				break;
			case 9:
				printf("[�������][�������� ���������] ������ � �������� ���������� ���������\n");
				break;
			case 10:
				printf("[�������][���������] �������������� ��������� �������\n");
				break;
			case 11:
				printf("[�������][������] ���������� ��������� ������ �������\n");
				break;
			case 12:
				printf("[�������][������] �������� ��������� ��������� � ��� ����������\n");
				break;
			case 13:
				printf("[�������][���������] ����������� ��������� ��������� �������\n");
				break;
			case 14:
				printf("[�������][������] ��������� ������� �������\n");
				break;
			case 15:
				printf("[�������][���������] ������ ��������������!\n");
				printf("[�������][��������] ������� Enter ��� �����������...\n");
				getchar();
				exit(1);
				break;
			case 16:
				printf("[�������][������] ������ ��� ���������� ���������\n");
				printf("[�������][��������] ������� Enter ��� �����������...\n");
				getchar();
				exit(1);
				break;
			case 17:
				printf("[�������][������] ��������� �������� ������, ��������� ����������� �����\n");
				printf("[�������][��������] ������� Enter ��� �����������...\n");
				getchar();
				exit(1);
				break;
			case 18:
				printf("[�������][���������] ������ ��� ���������� ����������� ���������\n");
				printf("[�������][��������] ������� Enter ��� �����������...\n");
				getchar();
				exit(1);
				break;
			case 19:
				printf("[�������][������] ������ ��� ������ ��������� � ����\n");
				printf("[�������][��������] ������� Enter ��� �����������...\n");
				getchar();
				exit(1);
				break;
			case 20:
				printf("[�������][��� ������ �������] �������� convertState = %d\n", firstParameter);
				break;
			case 21:
				printf("[�������][��� ������ �������] �������� analyzeState = %d\n", firstParameter);
				break;
			case 22:
				printf("[�������][��� ������ �������] �������� ahsoka = %d\n", firstParameter);
				break;
			case 23:
				printf("[�������][��� ������ �������] �������� gabella = %d\n", firstParameter);
				break;
			case 24:
				printf("[�������][��� ������ �������] �������� doubledoor = %d\n", firstParameter);
				break;
			case 25:
				for(int i=0;i<43;i++)
				{
					printf("[�������][������] ���� �� ���������: 0x%02X\n", FileHeaderMSG[i]);
				}
				break;
			case 26:
				printf("[�������][������ ���������] ������ ���������...\n");
				break;
			case 27:
				printf("[�������][���������] �������� 32 ������ �����: 0x%08X\n", firstParameter);
				break;
			case 28:
				printf("[�������][���������] �������� 16 ������ �����: 0x%04X\n", firstParameter);
				break;
			case 29:
				printf("[�������][�����.�����] ��������� �������� �������\n");
				break;
			case 30:
				printf("[�������][���������] �������������� ��������\n");
				break;
			case 31:
				printf("[�������][���������] �������� ����� ����� ����� 8 ���. �������������� �� ����� ������\n");
				break;
			case 32:
				printf("[�������][�����] ���������� ������: 0x%02X\n", firstParameter);
				break;
			case 33:
				printf("[�������][�����.�����] ������ ������...\n");
				break;
			case 34:
				printf("[�������][��������] ������������ ������ �� ���������\n");
				break;
			case 35:
				printf("[�������][��������] ������������ ������\n");
				break;
			case 36:
				printf("[�������][����� �������] ������� ����� �������\n");
				break;
			case 37:
				printf("[�������][�������] ��������� ������� ��-�� ���������� ��������� ������ �������(�������� ��� �������� �� ~95%%)\n");//����� �� ������������
				break;
			case 38:
				printf("[�������][��������] ������� Enter ��� �����������...\n");
				break;
			case 39:
				printf("[�������][�������� ���������] ����� RIFF ���������� � ��� �� �����\n");
				break;
			case 40:
				printf("[�������][�������� ���������] ���� �� ����� ����������. �� ����� ���������� WAV ����?\n");
				break;
			case 41:
				printf(" �����!(%d/13)\n", firstParameter+1);
				break;
			case 42:
				printf(" ������!(%d/13)\n", firstParameter+1);
				break;
			case 43:
				printf("[�������][�������� ���������] ����� WAVE ���������� � ��� �� �����\n");
				break;
			case 44:
				printf("[�������][�������� ���������] ����� fmt  ���������� � ��� �� �����\n");
				break;
			case 45:
				printf("[�������][�������� ���������] ����� data ���������� � ��� �� �����\n");
				break;
			case 46:
				printf("[�������][�������� ���������] ����� ��������� �����...\n");
				break;
			case 47:
				printf("[�������][�������� ���������] ");
				break;
			case 48:
				printf("[�������][�������� ���������] ����� ��������� ��� ����� ����� data ���������� � ���������� 36 ����\n");
				break;
			case 49:
				printf("[�������][�������� ���������] ����� ��������� �� ��������� � ��������, ��������� �����������");
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
					printf(", ������\n");
				}
				if(firstParameter==4)
				{
					printf(", ������\n");
				}
				break;
			case 51:
				if(firstParameter==1)
				{
					printf(" PCM\n");
				}
				break;
			case 52:
				printf("[�������][�������� ���������] ��������� ��������� � ��� ����������\n");
				break;
			case 53:
				printf("[�������][���.���������] ���������� ���������...\n");
				break;
			case 54:
				printf("[�������][���.���������] �������� ������� �������: %d ���\n", firstParameter);
				break;
			case 55:
				printf("[�������][���.���������] �������� ������� �������������: %d ��\n", firstParameter);
				break;
			case 56:
				printf("[�������][���.���������] �������� �������� �������� ������: %d ����/�\n", firstParameter);
				break;
			case 57:
				printf("[�������][���.���������] �������� ���������� �������: %d", firstParameter);
				if(firstParameter==1)
				{
					printf(", ����\n");
				}
				if(firstParameter==2)
				{
					printf(", ������\n");
				}
				if(firstParameter==4)
				{
					printf(", ������\n");
				}
				break;
			case 58:
				printf("[�������][���.���������] ������ �������� � ���������...\n");
				break;
			case 59:
				printf("[�������][������ ����������] �������� ���� � ����������� �����������");
				if(firstParameter==0)
				{
					printf(" ��� ������\n");
				}
				else
				{
					printf(" ��� ������\n");
				}
				break;
			case 60:
				printf("[�������][������ ����������] ������� �������������: %d ��\n", firstParameter);
				break;
			case 61:
				printf("[�������][������ ����������] ������� �������: %d ���\n", firstParameter);
				break;
			case 62:
				printf("[�������][������ ����������] �������: %d, ", firstParameter);
				if(firstParameter==1)
				{
					printf("����\n");
				}
				if(firstParameter==2)
				{
					printf("������\n");
				}
				if(firstParameter==4)
				{
					printf("������(�������� ���������)\n");
				}
				break;
			case 63:
				printf("[�������][������ ����������] �������������? ");
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
				printf("[�������][������ ����������] ��������� ������� ��������� �� ����� convertParams.ini\n");
				break;
			case 65:
				printf("[�������][������ ����������] ��������� ������ ��� ������ ���������� �� ����� convertParams.ini\n");
				printf("[�������][��������] ������� Enter ��� �����������...\n");
				getchar();
				exit(1);
				break;
			case 66:
				printf("[�������][��� ������ �������] �������� Egor = %d\n", firstParameter);
				break;
			case 67:
				printf("[�������][���.���������] �������� ���������� ������ � ����� ������� �� ���� �������: %d ����\n", firstParameter);
				break;
			case 68:
				printf("[�������][�������� ���������] ���������� ������� � 1 ������ %d(+/-8) �������\n", firstParameter);
				break;
			case 69:
				printf("[�������][���.���������] ��������� ������ ����� ��� ���������, ����������� �� ���������� ����������: %d ����\n", firstParameter);
				break;
			case 70:
				printf("[�������][���.���������] ��������� ������ �����, ����������� �� ���������� ����������: %d ����\n", firstParameter);
				break;
			case 71:
				printf("[�������][��� ������ �������] �������� cruzo = %d\n", firstParameter);
				break;
			case 72:
				printf("[�������][���.���������] �������������� ��������� ���������\n", firstParameter);
				break;
			case 73:
				printf("[�������][������] ������ ��� �������������� ���������\n");
				printf("[�������][��������] ������� Enter ��� �����������...\n");
				getchar();
				exit(1);
				break;
			case 74:
				printf("[�������][��� ������ �������] ������� ������� �������� ����� ��������� � ����� ��������: %d\n", firstParameter);
				break;
			case 75:
				printf("[�������][������ ���������] ������� ������ ����������� ��������� � ���� convertedHeader.txt\n");
				break;
			case 76:
				printf("[�������][������ � �����] ��������� ���������� ����� 0x%08X � �����\n", firstParameter);
				break;
			case 77:
				printf("[�������][������ � �����] ����� � ������� �������� �� ����������!\n");
				printf("[�������][��������] ������� Enter ��� �����������...\n");
				getchar();
				exit(1);
				break;
			case 78:
				printf("[�������][������ � �����] ���� �� ���������� ������: 0x%02X\n", firstParameter);
				break;
			case 79:
				printf("[�������][�������] ������� ���������� ������...\n");
				break;
			case 80:
				printf("[�������][�������] ������� ������������� ������...\n");
				break;
			case 81:
				printf("[�������][������] ������ ����������� ������ � ����...");
				break;
			case 82:
				printf("[�������][�����.�����] ��������� ������� ��������� � ������ �����������, �� ������ ������� �������� � ���������� ����� converted.dat\n");
				break;
			case 83:
				printf("[�������][������ ����������] ���� ��� �� ��� ������������, ����������� ������ ��������� �� ����� ������\n");
				//printf("[�������][��������] ������� Enter ��� �����������...\n");	//������� ��� �������������
				//getchar();
				exit(1);
				break;
			case 84:
				printf("[�������][��������] ������� Enter ��� �����������...\n");
				//getchar();
				exit(1);
				break;
			case 85:
				printf("[�������][�����.�����] ���������� ���������� ����������: %d\n", firstParameter);
				break;
			case 86:
				printf("[�������][������] ������ ������ �� ��������� � ����\n");
				break;
			case 87:
				printf("[�������][������] ������ ���������\n");
				break;
			case 88:
				printf("[�������][������] ");
				break;
			case 89:
				printf("[�������][������] ");
				break;
			case 90:
				printf("������ ����� ��: %d ����\n", firstParameter);
				break;
			case 91:
				printf("����� ���� �� ����������\n");
				break;
			case 92:
				printf("������� strrchr ������� NULL\n");
				break;
			case 93:
				printf("��������� ��������� �������: %d\n", firstParameter);
				break;
			case 94:
				printf("���������� �������� � ����� ����� = %d\n", firstParameter);
				break;
			case 95:
				printf("[�������][���.����� �����] ");
				break;
			case 96:
				printf("������� ��������� ����� ����� ���������\n");
				break;
			case 97:
				printf("��������������� ��� ����� ��������� ��� ���������� ������\n");
				break;
			case 98:
				printf("����� ����� ����� ��������� � ������ ����������� �������\n");
				break;
			case 99:
				printf("[�������][���.���������] ���������� ������� � ��������������� �����: %d\n", firstParameter);
				break;
			case 100:
				printf("������� ��������� ����� ����� ����\n");
				break;
		}
	}
}
