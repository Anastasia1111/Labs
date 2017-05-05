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

enum commands {READ = 0x10, WRITE = 0x11, LOAD = 0x20, STORE = 0x21, ADD = 0x30, SUB = 0x31, DIVIDE = 0x32, MUL = 0x33, JUMP = 0x40,
JNEG = 0x41, JZ = 0x42, HALT = 0x43,  RCR = 0x63, RCCL = 0x69};

int sc_memoryInit(); /* инициализирует оперативную память Simple Computer, задавая 
всем её ячейкам нулевые значения. В качестве «оперативной памяти» используется 
массив целых чисел, определенный статически в рамках библиотеки. Размер массива
равен 100 элементам */

int sc_memorySet (int address, int value); /* задает значение указанной ячейки 
памяти как value. Если адрес выходит за допустимые границы, то устанавливается 
флаг «выход за границы памяти» и работа функции прекращается с ошибкой*/

int sc_memoryGet (int address, int * value); /* возвращает значение указанной 
ячейки памяти в value. Если адрес выходит за допустимые границы, то устанавливается 
флаг «выход за границы памяти» и работа функции прекращается с ошибкой. Значение 
value в этом случае не изменяется */

int sc_memorySave (char * filename); /* сохраняет содержимое памяти в файл в
бинарном виде (используя функцию write или fwrite) */

int sc_memoryLoad (char * filename); /* загружает из указанного файла содержимое 
оперативной памяти (используя функцию read или fread) */

int sc_regInit (void); /* инициализирует регистр флагов нулевым значением */

int sc_regSet (int register, int value); /* устанавливает значение указанного 
регистра флагов. Для номеров регистров флагов должны использоваться маски, задаваемые 
макросами (#define). Если указан недопустимый номер регистра или некорректное 
значение, то функция завершается с ошибкой */

int sc_regGet (int register, int * value); /* возвращает значение указанного
флага. Если указан недопустимый номер регистра, то функция завершается с ошибкой*/

int sc_commandEncode (int command, int operand, int * value); /* кодирует 
команду с указанным номером и операндом и помещает результат в value. Если указаны 
неправильные значения для команды или операнда, то функция завершается с
ошибкой. В этом случае значение value не изменяется */

int sc_commandDecode (int value, int * command, int * operand); /* декодирует 
значение как команду Simple Computer. Если декодирование невозможно, то
устанавливается флаг «ошибочная команда» и функция завершается с ошибкой */

#endif // SC_H
