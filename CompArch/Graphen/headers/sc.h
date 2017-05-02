#ifndef SC_LIBS
#define SC_LIBS

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#endif //SC_LIBS

#ifndef SC_H
#define SC_H

#include <stdlib.h>

#define REG_OVERFLOW 0x1
#define REG_ZERO_DIV 0x2
#define REG_OVERLIMIT_MEM 0x3
#define REG_STEP_IGNORE 0x4
#define REG_WR_COM 0x5

#define ramSize 100
int RAM[ramSize];
extern char REG;
extern char InstCount;
extern short int Accum;

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
