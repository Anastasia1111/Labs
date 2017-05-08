#include <stdlib.h>
#include "headers/myBigChars.h"
#include "headers/sc.h"
#include "headers/myReadKey.h"
#include <signal.h>
#include <sys/time.h>


void initialize();
void memory_window();
void accumulator_window();
void instCount_window();
void operation_window();
void flags_window();
void keys_window();
void print_value();
void print_Accum();
void set_Accum();
void set_InstCount();

int pause(void);
void write_ram(int x, int y);
void big_window();
void print_flag();
void IncInstCount(int signo);
void StopIt(int signo);
int commandwindow();
char write_hex_num(enum keys button, int num[2]);
int ALU(int command, int operand);
int CU();
void refresh();
void enter_ram();
void operation();
void IOterminal();
int setInput(int operand);
