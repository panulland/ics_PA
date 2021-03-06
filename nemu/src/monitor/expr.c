#include "nemu.h"
#include "cpu/reg.h"
#include "cpu/cpu.h"
#include "memory/memory.h"

#include <stdlib.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, EQ, NUM, HEX, REG, SYMB, DEREF, NEG

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// white space
	{"\\+", '+'},
	{"-", '-'},
	{"\\*", '*'},
	{"/", '/'},
	{"\\(", '('},
	{"\\)", ')'},
	{"==", EQ},
	{"0[xX][0-9a-fA-F]+",HEX},
	{"[0-9]+", NUM},
	{"\\$e[a,c,d,b]x", REG},
	{"\\$e[sib]p", REG},
	{"\\$e[sd]i", REG},
	{"[a-zA-Z]+[a-zA-Z0-9]*", SYMB},
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for more times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			assert(ret != 0);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				// char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				// printf("match regex[%d] at position %d with len %d: %.*s", i, position, substr_len, substr_len, substr_start);
				position += substr_len;

				
				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */


				switch(rules[i].token_type) {
					case NOTYPE: break;
					case NUM:
					case HEX:
					case SYMB:
					case REG: for(int i=0;i<substr_len;i++) tokens[nr_token].str[i] = e[position-substr_len+i];
					     tokens[nr_token].str[substr_len]='\0';
					default: tokens[nr_token].type = rules[i].token_type;
							 nr_token ++;
				}

				break;
			}
		}

		if(i == NR_REGEX) {
			// printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}

bool check_parentheses(int s, int e, bool *success) {
	int flag=0;
	for(int i = s;i <= e;i++) {
		if(tokens[i].type == '(')
			flag++;
		else if(tokens[i].type == ')')
			flag--;
		if(flag < 0) {
			*success=false;
			return false;
		}
	}
	if(flag != 0) {
		*success=false;
		return false;
	}
	if(tokens[s].type != '(' || tokens[e].type != ')')
		return false;
	for(int i=s+1;i<e;i++) {
		if(tokens[i].type =='(')
			flag++;
		else if(tokens[i].type == ')')
			flag--;
		if(flag<0)
			return false;
	}
	if(flag!=0)
		return false;
	return true;
}

uint32_t eval(int s, int e, bool *success) {
	if(s > e) {
		*success = false;
		return 0;
	}
	else if(s == e) {
		*success = true;
		int len = 0;
		for(int i=0;tokens[s].str[i]!='\0';i++)
			len++;
		uint32_t res = 0;
		int n = 1;
		switch(tokens[s].type) {
			case NUM: 
			    	  for(int i=len-1;i>=0;i--) {
				     	  res += (tokens[s].str[i]-'0')*n;
					  n*=10;
     				  }
     				  break;
			case HEX: 
     				  for(int i=len-1;i>1;i--) {
					  if(tokens[s].str[i]<='9')
						  res += (tokens[s].str[i]-'0')*n;
					  else if(tokens[s].str[i]<='F')
						  res += (tokens[s].str[i]-'A'+10)*n;
					  else
						  res += (tokens[s].str[i]-'a'+10)*n;
     					  n*=16;
     				  }
     				  break;
			case REG: if(tokens[s].str[3]=='x') {
				     switch(tokens[s].str[2]) {
					     case 'a': res = cpu.eax; break;
				     	     case 'c': res = cpu.ecx; break;
					     case 'd': res = cpu.edx; break;
					     case 'b': res = cpu.ebx; break;
				     }
			     }
			     else if(tokens[s].str[3] == 'i') {
				     if(tokens[s].str[2] == 's')
					     res = cpu.esi;
				     else
					     res = cpu.edi;
			     }
			     else if(tokens[s].str[3]=='p') {
				     switch(tokens[s].str[2]) {
					     case 'b': res = cpu.ebp; break;
					     case 's': res = cpu.esp; break;
					     case 'i': res = cpu.eip; break;
				     }
			     }
			     break;
		}
		return res;
				     
	}
	else if(check_parentheses(s,e,success) == true) {
		*success = true;
		return eval(s+1,e-1,success);
	}
	else if(tokens[s].type == DEREF) {
		uint32_t addr=eval(s+1,e,success);
		return paddr_read(addr,4);
	}
	else if(tokens[s].type == NEG) {
		uint32_t val=eval(s+1,e,success);
		return -val;
	}
	else {
		*success = true;
		int op = s;
		int class = 1;
		int flag = 0;
		for(int i=s;i<e;i++) {
			if(tokens[i].type == '(')
				flag++;
			else if(tokens[i].type == ')')
				flag--;
			else if((tokens[i].type == '+' || tokens[i].type == '-')&&flag==0) {
				op = i;
				class = 0;
			}
			else if((tokens[i].type == '*' || tokens[i].type == '/')&&flag==0) {
				if(class == 1)
					op = i;
			}
		}
		uint32_t val1 = eval(s,op - 1,success);
		uint32_t val2 = eval(op + 1,e,success);
		switch(tokens[op].type) {
			case '+': return val1 + val2; break;
			case '-': return val1 - val2; break;
			case '*': return val1 * val2; break;
			case '/': return val1 / val2; break;
			default: *success=false;return 0;
		}
	}
}

uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}

	for(int i=0;i<nr_token;i++) {
		if(tokens[i].type == '*' && (i==0 || tokens[i-1].type == '+' || tokens[i-1].type == '-' || tokens[i-1].type == '*' || tokens[i-1].type == '/' || tokens[i-1].type == '(')) {
			tokens[i].type = DEREF;
		}
	}
	for(int i=0;i<nr_token;i++) {
		if(tokens[i].type == '-' && (i==0 || tokens[i-1].type == '+' || tokens[i-1].type == '-' || tokens[i-1].type == '*' || tokens[i-1].type == '/' || tokens[i-1].type == '(')) {
			tokens[i].type = NEG;
		}
	}
	return eval(0,nr_token-1,success);
}

