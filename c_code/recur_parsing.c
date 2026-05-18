#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LINESIZE 50

char tokens[LINESIZE + 2]; // '\n' and '\0'
int pos;

int parse_expr(void);
int parse_term(void);
int parse_fac(void);

int parse_fac(void) 
{
	char cur_tok = tokens[pos];
	if (isdigit(cur_tok)) {
		int val = 0;
        while (isdigit(tokens[pos])) {
            val = val * 10 + (tokens[pos] - '0');
            pos++;
        }
        return val;
	} else if (cur_tok == '(') {
		pos++;  // (
		int val = parse_expr();
		pos++;  // )
		return val;
	}
	return -1;      // exceptions
}

int parse_term(void) 
{
	int left = parse_fac();
	char tok;
	while (((tok = tokens[pos]) == '*' || tok == '/') && tok != '\0') {
		char op = tokens[pos++];
		int right = parse_fac();
		switch (op) {
		case '*': left *= right; break;
		case '/': left /= right; break;
		default: break;
		}
	}
	return left;
}

int parse_expr(void) 
{
	int left = parse_term();
	char tok;
	while (((tok = tokens[pos]) == '+' || tok == '-') && tok != '\0') {
		char op = tokens[pos++];
		int right = parse_term();
		switch (op) {
		case '+': left += right; break;
		case '-': left -= right; break;
		default: break;
		}
	}
	return left;
}

int evaluate() 
{
	pos = 0;
	int val = parse_expr();
	return val;
}

int main() 
{
	while (fgets(tokens, LINESIZE + 2, stdin) != NULL) {
		int val = evaluate();
		printf("%d\n", val);
	}
	return 0;
}