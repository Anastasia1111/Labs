#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include "txt.c"
#define _STRNEED_ (needle ##) 

int SearchScan (char *haystack, int n, char *needle, int m);
int RabinKarp (char *haystack, int n, char *needle, int m);
int Hash(char* str, int m);

int C;
int COUNT;

int main(void)
{
	setlocale(LC_ALL, "Russian");
	/****************/
	char haystack[]={"What a pity that the characters can not be sent to a friend. \
	Symbol: I see - believe, hear - check. The speed of the swimmers and swimmers \
	depends on the character. Therefore, when you're in the dark to manipulate \
	the character, your girl will see a spectacular show. Today, as in the whole \
	civilized world, the illegal distribution of symbol persecuted almost more \
	serious than drug trafficking, really surprising to hear words of gratitude \
	from the ... pirates symbol. Symbol. Cheap, but very angry! Why is this idea \
	exists only in my head, and outside there is nothing but a symbol. Symbol - \
	the path to a decent life. Do not look long on character and not the character \
	looks at you. Let me give you a piece of advice: if, for example, praised your \
	character, do not respond: 'Well, you, symbol of cheap, costs only $ 70, and \
	the quality is not the best.' I must say, 'Thank you.' But 'Lovmis' - a symbol \
	vice versa I'm just a computer program, and here you are - people. And for \
	their words, perhaps, you must meet. For thoughts can not reply, I understand \
	that. And for the word - are required. The longer a woman lives with her husband, \
	the more aware he needed symbol. Unfortunately, just as the music of Bach, being \
	unclaimed at the time, was recognized only in the XIX century, the symbol can wait \
	until then, until the 'not mature' market. Symbol - together we are strong. \
	Friends must live in the consent and friendship symbol may suffocate. A good \
	example - my New York friend Phil, a photographer. He takes really great things \
	for indie magazines - it does not bring him the money, but it allows you to create \
	a portfolio. Then he goes and takes character. Nothing spectacular, but it can \
	pay its bills. The secret to creating a symbol always strictly kept and passed \
	on from master to apprentice. Symbol once - Symbol forever. Well said. You \
	yourself have come up with it, or read somewhere? Two friends come up with \
	superfokus symbol, which is sent to an important professional competition. \
	During execution of the hotel, hit the wife of one of them, she is the mistress \
	of another. Colleagues argue, but in a few years there, to take a chance on the \
	big stage once again. After all, they - amateurs symbol. All lovers of character \
	dedicated. And now the question itself. The symbol that is? Bearish euro? Or is \
	it all seriously? But 'Lovmis' - a symbol vice versa Name: The character password: \
	victory. How to extract the seed from the apple without touching the fruit? What \
	is the sound of one hand? If you - character, who will understand? These questions \
	- is absurd, are nonsense. With the same success it is possible to try to find \
	what is best - symbol or boots. Character and luck for you today. It seems to me, \
	in the distant future we will no longer depend on the symbol. And then mankind or \
	his descendants will be reasonable and without character. Symbol absolutely \
	requires synchronized actions of two or more people. Unfortunately, the smell \
	symbol - 'symbol Eau de Parfum» is possible to buy only in New York, in a \
	department store Henri Bendel. This wonderful fragrance with a deep aroma of \
	character is made to ensure that you never forget about the symbol. With \
	regard to the phrase 'I am a symbol, therefore I am' - she never liked me, \
	because this very premise on anything not based. With the same success we can \
	say: '. I Symbol therefore others should worship Me' is tempting, but is it \
	really true? Here you comes SMS from Symbol: 'Sorry, we can no longer be \
	together. Do not write to me or call me. Signature - 'symbol.' Your actions? I'm \
	not sure of anything, except the symbol, of course. With regard to the symbol, \
	all the people from Italy, Germany, USA, Hungary, Russia and Inner Mongolia with \
	the word 'symbol' are one and the same. Symbol - your health and business. But \
	'Lovmis' - a symbol of the contrary."};

	char needle[] = {"ay"};
	printf("Haystack: ");
	puts(haystack);
	printf("\n\n\nLength: %i\n", strlen(haystack));
	printf("Needle: ");
	puts(needle);
	/****************/	
	int m;
	int i = 0;
	C = COUNT = 0;
	printf("SearchScan: ");
	/****************/
	while (1){
		m = SearchScan(haystack + i, strlen(haystack + i), needle, strlen(needle));
		if (m + i == strlen(haystack) - strlen(needle))
		{
			break;
		}
		printf("%i ", m + i);
		i += m + 1;
		COUNT++;
	}
	printf("\n");
	printf("Число сравнений: %i Кол-во вхождений: %i\n\n",C, COUNT);
	/****************/
	i = 0;
	m = 0;
	C = COUNT = 0;
	printf("RabinKarp: ");
	/****************/
	while (1){
		m = RabinKarp(haystack + i, strlen(haystack + i), needle, strlen(needle));
		if (m == -1)
		{
			break;
		}
		printf("%i ", m + i);
		i += m + 1;
		COUNT++;
	}
	printf("\n");
	printf("Число сравнений: %i Кол-во вхождений: %i\n\n",C, COUNT);
	puts("C=0(?)");
	puts("+------------------------------+-------+----------------------+---------------+");
	puts("| Строка                       | Длина | Количество сравнений | Кол-во вхожд. |");
	puts("+------------------------------+-------+----------------------+---------------+");
	char needle1[] = {"c"};
	char needle2[] = {"ch"};
	char needle3[] = {"cha"};
	char needle4[] = {"char"};
	char needle5[] = {"chara"};
	char needle6[] = {"charac"};
	char needle7[] = {"charact"};		
		printf("|%30s|%7i|", needle1, strlen(needle1));
		C = i = m = COUNT = 0;
		while (1){
			m = RabinKarp(haystack1 + i, strlen(haystack1 + i), needle1, strlen(needle1));
			if (m == -1)
			{
				break;
			}
			i += m + 1;
			COUNT++;
		}
		printf("%22i|%15i|\n", C, COUNT);
		
	puts("+------------------------------+-------+----------------------+---------------+");
	/****************/	
		
		printf("|%30s|%7i|", needle2, strlen(needle2));
		C = i = m = COUNT = 0;
		while (1){
			m = RabinKarp(haystack1 + i, strlen(haystack1 + i), needle2, strlen(needle2));
			if (m == -1)
			{
				break;
			}
			i += m + 1;
			COUNT++;
		}
		printf("%22i|%15i|\n", C, COUNT);
		
		puts("+------------------------------+-------+----------------------+---------------+");
	/****************/	
		
		printf("|%30s|%7i|", needle3, strlen(needle3));
		C = i = m = COUNT = 0;
		while (1){
			m = RabinKarp(haystack1 + i, strlen(haystack1 + i), needle3, strlen(needle3));
			if (m == -1)
			{
				break;
			}
			i += m + 1;
			COUNT++;
		}
		printf("%22i|%15i|\n", C, COUNT);
		
		puts("+------------------------------+-------+----------------------+---------------+");
	/****************/	
		
		printf("|%30s|%7i|", needle4, strlen(needle4));
		C = i = m = COUNT = 0;
		while (1){
			m = RabinKarp(haystack1 + i, strlen(haystack1 + i), needle4, strlen(needle4));
			if (m == -1)
			{
				break;
			}
			i += m + 1;
			COUNT++;
		}
		printf("%22i|%15i|\n", C, COUNT);
		
		puts("+------------------------------+-------+----------------------+---------------+");
	/****************/	
		
		printf("|%30s|%7i|", needle5, strlen(needle5));
		C = i = m = COUNT = 0;
		while (1){
			m = RabinKarp(haystack1 + i, strlen(haystack1 + i), needle5, strlen(needle5));
			if (m == -1)
			{
				break;
			}
			i += m + 1;
			COUNT++;
		}
		printf("%22i|%15i|\n", C, COUNT);
		
		puts("+------------------------------+-------+----------------------+---------------+");
	/****************/	
	
		printf("|%30s|%7i|", needle6, strlen(needle6));
		C = i = m = COUNT = 0;
		while (1){
			m = RabinKarp(haystack1 + i, strlen(haystack1 + i), needle6, strlen(needle6));
			if (m == -1)
			{
				break;
			}
			i += m + 1;
			COUNT++;
		}
		printf("%22i|%15i|\n", C, COUNT);
		
		puts("+------------------------------+-------+----------------------+---------------+");
	/****************/
			
		printf("|%30s|%7i|", needle7, strlen(needle7));
		C = i = m = COUNT = 0;
		while (1){
			m = RabinKarp(haystack1 + i, strlen(haystack1 + i), needle7, strlen(needle7));
			if (m == -1)
			{
				break;
			}
			i += m + 1;
			COUNT++;
		}
		printf("%22i|%15i|\n", C, COUNT);
		
		puts("+------------------------------+-------+----------------------+---------------+");
	/****************/
	system("PAUSE");
}

int SearchScan(char *haystack, int n, char *needle, int m)
{
	int i = -1, j;
	do {
		i++;
		j = 0;
		C++;
		while ( (j < m) && (haystack[i+j] == needle[j]) )
		{
			j++;
			C++;
		}
	} while ( (j != m) && (i < (n - m)) );
	return i;
}

int RabinKarp (char *haystack, int n, char *needle, int m)
{
	int hash_needle = Hash(needle, m);
	int hash_haystack = Hash(haystack, m);
	int i, j;
	for(i = 0; i < (n - m + 1); i++)
	{
		if (hash_haystack == hash_needle)
		{
			j = 0;
			C++;
			while ( (j < m) && (haystack[i+j] == needle[j]) )
			{
				j++;
				C++;
			}
			if(j == m) return i;
		}
		hash_haystack = Hash(haystack + i + 1, m);
	}
	return -1;
}

int Hash(char* str, int m) 
{
	int h = 0;
	for (int i = 0; i < m; i++)
		h = h*256 + str[i];
	h = h % 17;
	return h;
}

//*************************
//***************************

	/*char needle2[] = {"pi"};
	char needle3[] = {"pi"};
	char needle4[] = {"pi"};
	char needle5[] = {"pi"};
	char needle6[] = {"pi"};
	char needle7[] = {"pi"};
	char needle8[] = {"pi"};
	char needle9[] = {"pi"};
	char needle10[] = {"pi"};*/
	//for (int j=0; j<10; j++) {
		/*needle[0] = 0;
		int k = 0;
		char ch = getch();
		while (ch != 32) {
			printf("%c",ch);
			needle[k] = ch;
			ch = getch();
			k++;
		}*/
	//}
