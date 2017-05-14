#include "Btranslator.h"

int priority (char op) {
	if (op < 0)
		return 4;
	return
		op == '+' || op == '-' ? 1 :
		op == '*' || op == '/' ? 2 :
		-1;
}

int process_op (char op, char* rpn, int* lci) {
	if (op < 0) {
		struct varlist *pvar = vhead;
		while (pvar != NULL) {
			if (pvar->name[0] == 'm' && pvar->name[1] == 'n' && pvar->name[2] == 0) break;
			pvar = pvar->next;
		}
		if (pvar == NULL) {
			pvar = (struct varlist *)malloc(sizeof(struct varlist));
			pvar->name[0] = 'm';
			pvar->name[1] = 'n';
			pvar->name[2] = 0;
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
			default: return 1; 
		}
	}
	return 0;
}

int RPN (char* input)
{
	char rpn[1000];
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
					while (ophead != NULL && ophead->op != '(') {
						if (process_op(ophead->op, rpn, &lci)) {
							error_log(5);
							return 1;
						}
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
						if (may_unary && curop == '-') curop = -curop;
						while (ophead!=NULL && priority(ophead->op) >= priority(curop)) {
							if (process_op(ophead->op, rpn, &lci)) {
								error_log(5);
								return 1;
							}
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
							while (pvar != NULL) {
								if (pvar->name[0] == input[i] && pvar->name[1] == 0) break;
								pvar = pvar->next;
							}
							if (pvar == NULL) {
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
								int dig = 0;
								while (input[i]>='0' && input[i]<='9') {
									dig *= 10;
									dig += input[i] - '0';
									++i;
								}
								--i;
								if (dig <= 0x1FFF) {
									char dig1 = dig/1000 + '0';
									char dig2 = dig%1000/100 + '0';
									char dig3 = dig%100/10 + '0';
									char dig4 = dig%10 + '0';
									rpn[++lci] = dig1;
									rpn[++lci] = dig2;
									rpn[++lci] = dig3;
									rpn[++lci] = dig4;
									pvar = vhead;
									while (pvar != NULL) {
										if (pvar->name[0] == dig1 &&
											pvar->name[1] == dig2 &&
											pvar->name[2] == dig3 &&
											pvar->name[3] == dig4 &&
											pvar->name[4] == 0) break;
										pvar = pvar->next;
									}
									if (pvar == NULL) {
										pvar = (struct varlist *)malloc(sizeof(struct varlist));
										pvar->name[0] = dig1;
										pvar->name[1] = dig2;
										pvar->name[2] = dig3;
										pvar->name[3] = dig4;
										pvar->name[4] = 0;
										if (vhead!=NULL) pvar->address = vhead->address-1;
										else pvar->address = 99;
										pvar->next = vhead;
										vhead = pvar;
									}
									may_unary = 0;
								} else {
									error_log(6);
									return 1;
								}
							} else {
								error_log(5);
								return 1;
							}
						}
					}
		++i;
	}
		
	while (ophead != NULL) {
		if(process_op(ophead->op, rpn, &lci)){
			error_log(5);
			return 1;
		}
		pop = ophead;
		ophead= ophead->next;
		free(pop);
	}
	rpn[++lci] = '\0';
	
	struct varlist *varhead = NULL;
	struct varlist *pnvar;
	struct acomlist *pcom;
	i = 0;
	while (rpn[i] != '\0') {
		if (rpn[i]>='A' && rpn[i]<='Z') {
			pvar = vhead;
			while (pvar != NULL){
				if (pvar->name[0] == rpn[i] && pvar->name[1] == 0) break;
				pvar = pvar->next;
			}
			pnvar = (struct varlist *)malloc(sizeof(struct varlist));
			pnvar->address = pvar->address;
			pnvar->name[0] = pvar->name[0];
			pnvar->name[1] = 0;
			pnvar->next = varhead;
			varhead = pnvar;
		} else {
			if (rpn[i]>='0' && rpn[i]<='9') {
				pvar = vhead;
				while (pvar != NULL){
					if (pvar->name[0] == rpn[i] &&
						pvar->name[1] == rpn[i+1] &&
						pvar->name[2] == rpn[i+2] &&
						pvar->name[3] == rpn[i+3] &&
						pvar->name[4] == 0) break;
					pvar = pvar->next;
				}
				pnvar = (struct varlist *)malloc(sizeof(struct varlist));
				pnvar->address = pvar->address;
				pnvar->name[0] = pvar->name[0];
				pnvar->name[1] = pvar->name[1];
				pnvar->name[2] = pvar->name[2];
				pnvar->name[3] = pvar->name[3];
				pnvar->name[4] = 0;
				pnvar->next = varhead;
				varhead = pnvar;
				i += 3;
				
				pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
				pcom->number = pnvar->address;
				pcom->param = 	(pnvar->name[0]-'0') * 1000 +
								(pnvar->name[1]-'0') * 100 +
								(pnvar->name[2]-'0') * 10 +
								(pnvar->name[3]-'0');
				pcom->oper = EQU;
				pcom->next = NULL;
				if (ahead!=NULL) atail->next = pcom;
				else ahead = pcom;
				atail = pcom;
			} else {
				if (rpn[i]>='a' && rpn[i]<='z') {
					pvar = vhead;
					while (pvar != NULL){
						if (pvar->name[0] == rpn[i] && pvar->name[1] == rpn[i+1] && pvar->name[2] == 0) break;
						pvar = pvar->next;
					}
					pnvar = (struct varlist *)malloc(sizeof(struct varlist));
					pnvar->address = pvar->address;
					pnvar->name[0] = pvar->name[0];
					pnvar->name[1] = pvar->name[1];
					pnvar->name[2] = 0;
					pnvar->next = varhead;
					varhead = pnvar;
					if (rpn[i] == 'm' && rpn[i+1] == 'n') {
						pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
						pcom->number = pnvar->address;
						pcom->param = -1;
						pcom->oper = EQU;
						pcom->next = NULL;
						if (ahead!=NULL) atail->next = pcom;
						else ahead = pcom;
						atail = pcom;
					}
					++i;
				} else {
					if (rpn[i]=='+' || rpn[i]=='-' || rpn[i]=='*' || rpn[i]=='/' || rpn[i]=='=') {
						struct varlist *right = (struct varlist *)malloc(sizeof(struct varlist));
						right->address = varhead->address;
						right->name[0] = varhead->name[0];
						right->name[1] = varhead->name[1];
						right->name[2] = varhead->name[2];
						right->name[3] = varhead->name[3];
						right->name[4] = varhead->name[4];
						right->next = NULL;
						pvar = varhead;
						varhead = varhead->next;
						free(pvar);
						struct varlist *left = (struct varlist *)malloc(sizeof(struct varlist));
						left->address = varhead->address;
						left->name[0] = varhead->name[0];
						left->name[1] = varhead->name[1];
						left->name[2] = varhead->name[2];
						left->name[3] = varhead->name[3];
						left->name[4] = varhead->name[4];
						left->next = NULL;
						pvar = varhead;
						varhead = varhead->next;
						free(pvar);
						
						if (rpn[i-1]!='+' && rpn[i-1]!='-' && rpn[i-1]!='*' && rpn[i-1]!='/' && rpn[i-1]!='=') {
							pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
							pcom->number = COMNUM++;
							pcom->param = left->address;
							pcom->oper = LOAD;
							pcom->next = NULL;
							if (ahead!=NULL) atail->next = pcom;
							else ahead = pcom;
							atail = pcom;
						}
						
						switch(rpn[i]){
							case '+':
								if (right->name[0] == 'a' && right->name[1] == 'c' && right->name[2] == 0) {
									pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
									pcom->number = COMNUM++;
									pcom->param = left->address;
									pcom->oper = ADD;
									pcom->next = NULL;
									if (ahead!=NULL) atail->next = pcom;
									else ahead = pcom;
									atail = pcom;
								} else {
									pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
									pcom->number = COMNUM++;
									pcom->param = right->address;
									pcom->oper = ADD;
									pcom->next = NULL;
									if (ahead!=NULL) atail->next = pcom;
									else ahead = pcom;
									atail = pcom;
								}
								break;
							case '-':
								if (right->name[0] == 'a' && right->name[1] == 'c' && right->name[2] == 0) {
									pvar = vhead;
									while (pvar != NULL) {
										if (pvar->name[0] == 'a' && pvar->name[1] == 'c' && pvar->name[2] == 0) break;
										pvar = pvar->next;
									}
									if (pvar == NULL) {
										pvar = (struct varlist *)malloc(sizeof(struct varlist));
										pvar->name[0] = 'a';
										pvar->name[1] = 'c';
										pvar->name[2] = 0;
										if (vhead!=NULL) pvar->address = vhead->address-1;
										else pvar->address = 99;
										pvar->next = vhead;
										vhead = pvar;
									}
									pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
									pcom->number = COMNUM++;
									pcom->param = pvar->address;
									pcom->oper = STORE;
									pcom->next = NULL;
									if (ahead!=NULL) atail->next = pcom;
									else ahead = pcom;
									atail = pcom;
									
									pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
									pcom->number = COMNUM++;
									pcom->param = left->address;
									pcom->oper = LOAD;
									pcom->next = NULL;
									atail->next = pcom;
									atail = pcom;
									
									pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
									pcom->number = COMNUM++;
									pcom->param = pvar->address;
									pcom->oper = SUB;
									pcom->next = NULL;
									atail->next = pcom;
									atail = pcom;
								} else {
									pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
									pcom->number = COMNUM++;
									pcom->param = right->address;
									pcom->oper = SUB;
									pcom->next = NULL;
									if (ahead!=NULL) atail->next = pcom;
									else ahead = pcom;
									atail = pcom;
								}
								break;
							case '*':
								if (right->name[0] == 'a' && right->name[1] == 'c' && right->name[2] == 0) {
									pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
									pcom->number = COMNUM++;
									pcom->param = left->address;
									pcom->oper = MUL;
									pcom->next = NULL;
									if (ahead!=NULL) atail->next = pcom;
									else ahead = pcom;
									atail = pcom;
								} else {
									pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
									pcom->number = COMNUM++;
									pcom->param = right->address;
									pcom->oper = MUL;
									pcom->next = NULL;
									if (ahead!=NULL) atail->next = pcom;
									else ahead = pcom;
									atail = pcom;
								}
								break;
							case '/':
								if (right->name[0] == 'a' && right->name[1] == 'c' && right->name[2] == 0) {
									pvar = vhead;
									while (pvar != NULL) {
										if (pvar->name[0] == 'a' && pvar->name[1] == 'c' && pvar->name[2] == 0) break;
										pvar = pvar->next;
									}
									if (pvar == NULL) {
										pvar = (struct varlist *)malloc(sizeof(struct varlist));
										pvar->name[0] = 'a';
										pvar->name[1] = 'c';
										pvar->name[2] = 0;
										if (vhead!=NULL) pvar->address = vhead->address-1;
										else pvar->address = 99;
										pvar->next = vhead;
										vhead = pvar;
									}
									pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
									pcom->number = COMNUM++;
									pcom->param = pvar->address;
									pcom->oper = STORE;
									pcom->next = NULL;
									if (ahead!=NULL) atail->next = pcom;
									else ahead = pcom;
									atail = pcom;
									
									pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
									pcom->number = COMNUM++;
									pcom->param = left->address;
									pcom->oper = LOAD;
									pcom->next = NULL;
									atail->next = pcom;
									atail = pcom;
									
									pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
									pcom->number = COMNUM++;
									pcom->param = pvar->address;
									pcom->oper = DIVIDE;
									pcom->next = NULL;
									atail->next = pcom;
									atail = pcom;
								} else {
									pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
									pcom->number = COMNUM++;
									pcom->param = right->address;
									pcom->oper = DIVIDE;
									pcom->next = NULL;
									if (ahead!=NULL) atail->next = pcom;
									else ahead = pcom;
									atail = pcom;
								}
								break;
							case '=':
								if (right->name[0] == 'a' && right->name[1] == 'c' && right->name[2] == 0) {
									pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
									pcom->number = COMNUM++;
									pcom->param = left->address;
									pcom->oper = STORE;
									pcom->next = NULL;
									if (ahead!=NULL) atail->next = pcom;
									else ahead = pcom;
									atail = pcom;
								} else {
									pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
									pcom->number = COMNUM++;
									pcom->param = right->address;
									pcom->oper = LOAD;
									pcom->next = NULL;
									if (ahead!=NULL) atail->next = pcom;
									else ahead = pcom;
									atail = pcom;
									
									pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
									pcom->number = COMNUM++;
									pcom->param = left->address;
									pcom->oper = STORE;
									pcom->next = NULL;
									atail->next = pcom;
									atail = pcom;
								}
								break;
						}
						
						if (rpn[i+1]!='+' && rpn[i+1]!='-' && rpn[i+1]!='*' && rpn[i+1]!='/' && rpn[i+1]!='=' && rpn[i+1]!='\0') {
							pvar = vhead;
							char num = '0'-1;
							while (pvar != NULL){
								++num;
								pvar = vhead;
								while (pvar != NULL) {
									if (pvar->name[0] == 'b' && pvar->name[1] == num && pvar->name[2] == 0) break;
									pvar = pvar->next;
								}
							}
							pvar = (struct varlist *)malloc(sizeof(struct varlist));
							pvar->name[0] = 'b';
							pvar->name[1] = num;
							pvar->name[2] = 0;
							if (vhead!=NULL) pvar->address = vhead->address-1;
							else pvar->address = 99;
							pvar->next = vhead;
							vhead = pvar;
							
							pnvar = (struct varlist *)malloc(sizeof(struct varlist));
							pnvar->address = pvar->address;
							pnvar->name[0] = pvar->name[0];
							pnvar->name[1] = pvar->name[1];
							pnvar->name[2] = 0;
							pnvar->next = varhead;
							varhead = pnvar;
							
							pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
							pcom->number = COMNUM++;
							pcom->param = pnvar->address;
							pcom->oper = STORE;
							pcom->next = NULL;
							if (ahead!=NULL) atail->next = pcom;
							else ahead = pcom;
							atail = pcom;
						} else {
							pnvar = (struct varlist *)malloc(sizeof(struct varlist));
							pnvar->address = 100;
							pnvar->name[0] = 'a';
							pnvar->name[1] = 'c';
							pnvar->name[2] = 0;
							pnvar->next = varhead;
							varhead = pnvar;
						}
					} else {
						error_log(5);
						return 1;
					}
				}
			}
		}
		++i;
	}
	pvar = varhead;
	varhead = varhead->next;
	free(pvar);
	if (varhead != NULL){
		error_log(5);
		return 1;
	}
	
	return 0;
}