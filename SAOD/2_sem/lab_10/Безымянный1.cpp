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
	
	/*string mess = "m@0 e`";
	string m4 = "";
	short int counter = 1;
	for (i = mess.length() * 8 - 1; i >=0; i--)
	{
		if((mess >> i) % 2 == 0)
		{
			count++;
		} else {
			j = 15;//exponenta	
			while (((counter >> j) % 2) == 0 && j >= 0)
			{
				j--;
			}
			for (k = j; k > 0; --k)//print exponenta
			{
				m4 = m4 + '0';
			}
			m4 = m4 + " 1 ";
			for (k = j-1; k >= 0; --k)//print mantissa
			{
				if((counter >> k) % 2 == 1)
				{
					m4 = m4 + "1";
				} else {
					m4 = m4 + "0";
				}
			}
			cout << m4;
			counter = 1;
		}
	}*/
	system("pause");
	return 0;
}

//для вывода есть функция sprintf!!!
