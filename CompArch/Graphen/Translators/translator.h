#include <stdio.h>
#include <string.h>

#define STR_SIZE 256
FILE *in;
FILE *out;

extern int STRN;

enum commands {READ = 0x10, WRITE = 0x11, LOAD = 0x20, STORE = 0x21, ADD = 0x30, SUB = 0x31, DIVIDE = 0x32, MUL = 0x33, JUMP = 0x40,
JNEG = 0x41, JZ = 0x42, HALT = 0x43, RCR = 0x63, RCCL = 0x69};

void error_log(int code);
int translate(char *input);
int translate_command(char *input, enum commands *output);
int main(int argc, char* argv[]);
