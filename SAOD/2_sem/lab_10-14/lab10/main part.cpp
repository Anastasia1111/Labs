#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

void FixVar(string &m1, short int &j, short int &i)
{
    int k;
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
};

void Gamma(string &m2, short int &j, short int &i)
{
    if(i)
    {
        int k;
        if(j == -1) j++;
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
    } else {
    }
};

void Omega(string &m3, short int &j, short int &i)
{
    int k, l;
    string mbuff = " ";
    if(j == -1) j++;
    if(i)
    {
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
            j = sizeof(short int)* 8 - 1;
            while (((l >> j) % 2) == 0 && j >= 0)
            {
                j--;
            }
        }
    } else {
		
    }
}

void FileRead()
{
    char buff = 0;
    char buf = 0;
    string m = "";
    int bit_count = 0; // number of 0
    FILE* pF = fopen("code.dat", "rb+");
    FILE* pF1 = fopen("code1.dat", "wb+");
    do
    {
        fgets(&buff, 2, pF);
        puts(&buff);
        short int size = sizeof(char)*8-1;
        short int chr = buff+1;
        Omega(m,size,chr);
		for (int k=0; k<m.size(); k++){
			
			if (bit_count==8)
			{
				fputc((int)buf, pF1);
				buf = 0;
				bit_count = 0;
			}
			if(m[k]=='1')
			{
				buf++;
			}
			buf <<= 1;
			bit_count++;
		}
    }while( !(feof(pF)) );
	if(bit_count!=0)
	{
		for(int j=bit_count; j<8; j++)
			buff<<=1;
		fputc((int)buf, pF);
		buf = 0;
		bit_count = 0;
	}
    
    fclose(pF);
    fclose(pF1);
}

int main(void)
{
    printf("\nsizeof( short int) = %i bites\n\n",sizeof(short int) * 8);
    puts("+-----+-----------------------------------------------------------------------+");
    puts("| num |                    cod name                                           |");
    puts("|     +------------------------+------------------------+---------------------+");
    puts("|     |     F + V              |     Gamma-code         |  Omega-code         |");
    puts("+-----+------------------------+------------------------+---------------------+");
    short int i = 0;
    short int j;
    int k;
    string m1, m2, m3;
    string mbuff = " ";
    while (i < 10)
    {
        cout << "|" << setw(5) << i << "|";
        m1 = m2 = m3 = "";
        j = sizeof(short int) * 8 - 1;//exponenta

        FixVar(m1, j, i);

        cout << setw(24) << m1 << "|";
//**************************Gamma***********************************************
        Gamma(m2, j, i);
        if(i) {cout << setw(24) << m2 << "|";}
        else {cout << "------------------------+";}
//**************************Omega***********************************************
        Omega(m3, j, i);
        if(i){cout << setw(21) << m3 << "|" << endl;}
        else {cout << "---------------------+ ";}
        cout << "+-----+------------------------+------------------------+---------------------+" << endl;
        ++i;
    }

//******************************************************************************
//coding length series
//******************************************************************************
    i = 0;
    char mess[] = " `";
    cout << "String for length series:" << endl;
    cout << mess << "endl" << endl;
    cout << "String for length series:\n\n" << endl;
    while (i < strlen(mess))
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
    cout << "\n\nCode string:\n\n" << endl;
    while (i < strlen(mess))
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
    
    //FileRead();
    
    system("pause");
    return 0;
}

//для вывода есть функция sprintf!!!
