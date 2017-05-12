#include "Btranslator.h"

int priority (char op) {
	return op == '+' || op == '-' ? 1 : 2;
}

int RPN (char* input char* &output)// string is end by \n , you can add any param, commands in sc.h
{
	char rpn[sizeof(input)/sizeof(*input)];
	rpn = "";
	
	opstack *ophead = NULL;
	opstack *pop;
	//varlist *varhead = NULL;
	varlist *pvar;
	
	int i = 0;
	
	while (input[i] != '\n') {
		if (input[i] == '(') {
			pop = (opstack *)malloc(sizeof(opstack));
			pop.op = '(';
			pop->next = ophead;
			ophead = pop;
		} else
			if (input[i] == ')') {
				while (ophead.op != '(' && ophead.op != NULL){
					rpn += ophead.op;
					pop = ophead;
					ophead= ophead->next;
					free(pop);
				}
				if (ophead.op != NULL){
					pop = ophead;
					ophead= ophead->next;
					free(pop);
				}
			} else
				if (input[i]=='+' || input[i]=='-' || input[i]=='*' || input[i]=='/') {
					char curop = input[i];
					while (ophead!=NULL && priority(ophead.op) >= priority(curop)){
						rpn += ophead.op;
						pop = ophead;
						ophead= ophead->next;
						free(pop);
					}
					pop = (opstack *)malloc(sizeof(opstack));
					pop.op = curop;
					pop->next = ophead;
					ophead = pop;
				} else {
					pvar = head; // имеется в виду varlist'вый head, но я хз, как обратить именно к ниму когда ты объявил их 2
					while (head != NULL){
						if (input[i] == pvar.name) break;
						pvar = pvar->next;
					}
					if (pvar == NULL){
						pvar = (varlist *)malloc(sizeof(varlist));
						pvar.name = input[i];
						pvar->next = head;
						head = pvar;
					}
					rpn += input[i];
				}
		++i;
	}
		
	while (ophead != NULL) {
		rpn += ophead.op;
		pop = ophead;
		ophead= ophead->next;
		free(pop);
	}
	rpn += '\n';
	
	return 0;
}