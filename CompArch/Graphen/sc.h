#ifndef SC_H
#define SC_H

#include <stdlib.h>
#include <stdio.h>

#define REG_OVERFLOW 0x18
#define REG_ZERO_DIV 0x19
#define REG_OVERLIMIT_MEM 0x1A
#define REG_STEP_IGNORE 0x1B
#define REG_WR_COM 0x1C

#define ramSize 100
int RAM[ramSize];
extern int REG;/* 0-14 = accumulator
		*16-22 = command pointer
		*24-28 = flag register
		* 	24 (code 1):overfilling
		*	25 (code 2):division on 0
		*	26 (code 3):exit over limits of memory
		* 	27 (code 4):step inpulses ignoring
		* 	28 (code 5):wrong command
		* */ 


int sc_memoryInit(); /* �������������� ����������� ������ Simple Computer, ������� 
���� � ������� ������� ��������. � �������� ������������ ������ ������������ 
������ ����� �����, ������������ ���������� � ������ ����������. ������ �������
����� 100 ��������� */

int sc_memorySet (int address, int value); /* ������ �������� ��������� ������ 
������ ��� value. ���� ����� ������� �� ���������� �������, �� ��������������� 
���� ������ �� ������� ������ � ������ ������� ������������ � �������*/

int sc_memoryGet (int address, int * value); /* ���������� �������� ��������� 
������ ������ � value. ���� ����� ������� �� ���������� �������, �� ��������������� 
���� ������ �� ������� ������ � ������ ������� ������������ � �������. �������� 
value � ���� ������ �� ���������� */

int sc_memorySave (char * filename); /* ��������� ���������� ������ � ���� �
�������� ���� (��������� ������� write ��� fwrite) */

int sc_memoryLoad (char * filename); /* ��������� �� ���������� ����� ���������� 
����������� ������ (��������� ������� read ��� fread) */

int sc_regInit (void); /* �������������� ������� ������ ������� ��������� */

int sc_regSet (int register, int value); /* ������������� �������� ���������� 
�������� ������. ��� ������� ��������� ������ ������ �������������� �����, ���������� 
��������� (#define). ���� ������ ������������ ����� �������� ��� ������������ 
��������, �� ������� ����������� � ������� */

int sc_regGet (int register, int * value); /* ���������� �������� ����������
�����. ���� ������ ������������ ����� ��������, �� ������� ����������� � �������*/

int sc_commandEncode (int command, int operand, int * value); /* �������� 
������� � ��������� ������� � ��������� � �������� ��������� � value. ���� ������� 
������������ �������� ��� ������� ��� ��������, �� ������� ����������� �
�������. � ���� ������ �������� value �� ���������� */

int sc_commandDecode (int value, int * command, int * operand); /* ���������� 
�������� ��� ������� Simple Computer. ���� ������������� ����������, ��
��������������� ���� ���������� ������� � ������� ����������� � ������� */

#endif // SC_H
