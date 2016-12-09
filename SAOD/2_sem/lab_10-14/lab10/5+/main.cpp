#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <math.h>

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
        m2 = m2 + "1";
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
    string mbuff = "";
    if(j == -1) j++;
    if(i)
    {
        m3 = "0";
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
            mbuff.clear();
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

void FileRead(const char *filename,void (*f)(string &, short int &, short int &))
{
	int i;
    char buff[] = {0, 0};
    char buf[] = {0, 0};
    short int lenc = 0;
    string m = "";
    short int j;
    FILE* pF = fopen("code.dat", "rb+");
    FILE* pF1 = fopen(filename, "wb+");
    do
    {
        fgets(buff, 2, pF);
        if(buff[0] == '0')
        {
			lenc++;
		} else {
			j = sizeof(short int) * 8 - 1;
			while (((lenc >> j) % 2) == 0 && j >= 0)
		    {
		        j--;
		    }
			f(m,j,lenc);
			lenc = 0;
			
			for(i = 0; i < m.length(); ++i)
			{
				buf[0] = m[i];
				fputc(buf[0], pF1);
			}
			
			m.clear();
		}
    }while( !(feof(pF)) );
    
	int x = ftell(pF);
	int y = ftell(pF1);
    printf("size of original: %i\n", x);
    printf("size of coded: %i\n", y);
    printf("k compressing: %2.4f\n", (double)y / x);
    
    
    fclose(pF);
    fclose(pF1);
}

main()
{
	void (*f)(string &, short int &, short int &);
	f = FixVar;
	FileRead("FixVar.dat", f);
	f = Omega;
	FileRead("Omega.dat", f);
	f = Gamma;
	FileRead("Gamma.dat", f);
	system("pause");
	return 0;
}
