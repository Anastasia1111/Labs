#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
	printf("\nsizeof( short int) = %i bytes\n\n",sizeof(short int));
	puts("+-----+-----------------------------------------------------------------------+");
	puts("| num |                    cod name                                           |");
	puts("|     +------------------------+------------------------+---------------------+");
	puts("|     |     F + V              |     Gamma-code         |  Omega-code         |");
	puts("+-----+------------------------+------------------------+---------------------+");
	short int i = 0;
	short int j;
	short int l;
	int k;
	string m1, m2, m3;
	string mbuff = " ";
	while (i < 33)
	{
		cout << "+" << setw(5) << i << "+";
		
		m1 = m2 = m3 = "";
		j = 15;//exponenta	
		while (((i >> j) % 2) == 0 && j >= 0)
		{
			j--;
		}
		for (k = 3; k >= 0; --k)//print exponenta
		{
			if(((j+1) >> k) % 2 == 1) // j + 1 for true exp
			{
				m1 = m1 + '1';
			} else {
				m1 = m1 + '0';
			}
		}
		m1 = m1 + ' ';
		for (k = j-1; k >= 0; --k)//print mantissa
		{
			if((i >> k) % 2 == 1)
			{
				m1 = m1 + '1';
			} else {
				m1 = m1 + '0';
			}
		}
		if(j == -1) j++;
		cout << setw(24) << m1 << "+";
//**************************Gamma***********************************************
		if(i)
		{
			for (k = j; k > 0; --k)//print exponenta
			{
				m2 = m2 + '0';
			}
			m2 = m2 + " 1 ";
			for (k = j-1; k >= 0; --k)//print mantissa
			{
				if((i >> k) % 2 == 1)
				{
					m2 = m2 + "1";
				} else {
					m2 = m2 + "0";
				}
			}
			cout << setw(24) << m2 << "+";
//**************************Omega***********************************************
				m3 = " 0";
				l = i;
				//j + 1 = real exponenta
				while ((j+1) >= 2)
				{
					for (k = j; k >= 0; --k)
					{
						if((l >> k) % 2 == 1)
						{
							mbuff = mbuff + '1';
						} else {
							mbuff = mbuff + '0';
						}
					}
					m3 = mbuff + m3;
					mbuff = ' ';
					l = j;
					j = 15;
					while (((l >> j) % 2) == 0 && j >= 0)
					{
						j--;
					}
				}
				cout << setw(21) << m3 << "+" << endl;
		} else {
			cout << "------------------------+---------------------+" << endl;
		}
		cout << "+-----+------------------------+------------------------+---------------------+" << endl;
		++i;
	}
	
//******************************************************************************
//coding length series
//******************************************************************************
	i = 0;
	char mess[] = "  ` `   `` `";
	cout << "String for length series:" << endl;
	cout << mess << "endl" << endl;
	cout << "String for length series:" << endl;
	while (i < 6)
	{
		for(j = 7; j >= 0; --j)
		{
			if((mess[i] >> j) % 2 == 1)
			{
				cout << "1";
			} else {
				cout << "0";
			}
		}
		cout << " ";
		i++;	
	}
	cout << endl;
	mbuff = "";
	int count = 0;
	char buff;
	i = 0;
	cout << "Code string:" << endl;
	while (i < 6)
	{
		for(j = 7; j >= 0; --j)
		{
			count++;
			if(((mess[i] >> j) % 2 == 1))
			{
				buff = (char)count;
				count = 7;
				while (((buff >> count) % 2) == 0 && count >= 0)
				{
					count--;
				}
				for (k = count; k > 0; --k)//print exponenta
				{
					mbuff = mbuff + '0';
				}
				mbuff = mbuff + "1";
				for (k = count - 1; k >= 0; --k)//print mantissa
				{
					if((buff >> k) % 2 == 1)
					{
						mbuff = mbuff + "1";
					} else {
						mbuff = mbuff + "0";
					}
				}
				mbuff += " ";
				count = 0;
			}
		}
		++i;
	}
	count++;
	buff = (char)count;
	count = 7;
	while (((buff >> count) % 2) == 0 && count >= 0)
	{
		count--;
	}
	for (k = count; k > 0; --k)//print exponenta
	{
		mbuff = mbuff + '0';
	}
	mbuff = mbuff + "1";
	for (k = count - 1; k >= 0; --k)//print mantissa
	{
		if((buff >> k) % 2 == 1)
		{
			mbuff = mbuff + "1";
		} else {
			mbuff = mbuff + "0";
		}
	}
	cout << mbuff << endl;
	system("pause");
	return 0;
}

//для вывода есть функция sprintf!!!
