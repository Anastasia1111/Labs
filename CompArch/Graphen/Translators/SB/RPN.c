#include "Btranslator.h"

int priority (char op) {
	if (op < 0)
		return 4;
	return
		op == '+' || op == '-' ? 1 :
		op == '*' || op == '/' ? 2 :
		-1;
}

void process_op (char op, char* rpn, int* lci) {
	if (op < 0) {
		struct varlist *pvar = vhead;
		while (pvar != NULL){
			if (pvar->name[0] == 'm' && pvar->name[1] == 'n') break;
			pvar = pvar->next;
		}
		if (pvar == NULL){
			pvar = (struct varlist *)malloc(sizeof(struct varlist));
			pvar->name[0] = 'm';
			pvar->name[1] = 'n';
			if (vhead!=NULL) pvar->address = vhead->address-1;
			else pvar->address = 99;
			pvar->next = vhead;
			vhead = pvar;
		}
		
		char var = rpn[*lci];
		rpn[*lci] = 'm';
		rpn[*lci+1] = 'n';
		rpn[*lci+2] = var;
		rpn[*lci+3] = '*';
		*lci += 3;
	}
	else {
		switch (op) {
			case '+':  rpn[++*lci] = '+';  break;
			case '-':  rpn[++*lci] = '-';  break;
			case '*':  rpn[++*lci] = '*';  break;
			case '/':  rpn[++*lci] = '/';  break;
			case '=':  rpn[++*lci] = '=';  break;
		}
	}
}

int RPN (char* input, char* output)
{
	char rpn[350];
	int lci = -1;
	
	struct oplist *ophead = NULL;
	struct oplist *pop;
	struct varlist *pvar;
	
	int i = 0;
	int may_unary = 1;
	
	while (input[i] != '\n') {
		if (input[i] != ' ')
			if (input[i] == '(') {
				pop = (struct oplist *)malloc(sizeof(struct oplist));
				pop->op = '(';
				pop->next = ophead;
				ophead = pop;
				may_unary = 1;
			} else
				if (input[i] == ')') {
					while (ophead->op != '(' && pop != NULL){
						process_op(ophead->op, rpn, &lci);
						pop = ophead;
						ophead = ophead->next;
						free(pop);
					}
					if (pop != NULL){
						pop = ophead;
						ophead= ophead->next;
						free(pop);
					} else {
						error_log(5);
						return 1;
					}
					may_unary = 0;
				} else
					if (input[i]=='+' || input[i]=='-' || input[i]=='*' || input[i]=='/' || input[i]=='=') {
						char curop = input[i];
						if (may_unary && curop == '-')  curop = -curop;
						while (ophead!=NULL && priority(ophead->op) >= priority(curop)){
							process_op(ophead->op, rpn, &lci);
							pop = ophead;
							ophead = ophead->next;
							free(pop);
						}
						pop = (struct oplist *)malloc(sizeof(struct oplist));
						pop->op = curop;
						pop->next = ophead;
						ophead = pop;
						may_unary = 1;
					} else {
						if (input[i]>='A' && input[i]<='Z') {
							pvar = vhead;
							while (pvar != NULL){
								if (input[i] == pvar->name[0] && pvar->name[1] == 0) break;
								pvar = pvar->next;
							}
							if (pvar == NULL){
								pvar = (struct varlist *)malloc(sizeof(struct varlist));
								pvar->name[0] = input[i];
								pvar->name[1] = 0;
								if (vhead!=NULL) pvar->address = vhead->address-1;
								else pvar->address = 99;
								pvar->next = vhead;
								vhead = pvar;
							}
							rpn[++lci] = input[i];
							may_unary = 0;
						} else {
							if (input[i]>='0' && input[i]<='9') {
								rpn[++lci] = input[i];
								may_unary = 0;
							} else {
								error_log(5);
								return 1;
							}
						}
					}
		++i;
	}
		
	while (ophead != NULL) {
		process_op(ophead->op, rpn, &lci);
		pop = ophead;
		ophead= ophead->next;
		free(pop);
	}
	rpn[++lci] = '\0';
	
	return 0;
}