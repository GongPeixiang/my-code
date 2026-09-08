#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAXLEN 100

char s[MAXLEN + 2];
bool in_bound[3] = {false, false, false};

void parse_term(int *pos);
void parse_formula(int *pos);

void parse_formula(int *pos)
{
	while (s[*pos] != '\0') {
		if (s[*pos] == 'F') {
			(*pos) += 2;
			parse_term(pos);
			printf("=");
			if (s[*pos] == ',')
				++(*pos);
			parse_term(pos);
			++(*pos);
		} else if (s[*pos] == '(' || s[*pos] == ')') {
			printf("%c", s[*pos]);
			++(*pos);
		} else 
			++(*pos);
	}
}

void parse_term(int *pos) 
{
	if (s[*pos] == 'f' || s[*pos] == 'g') {
		char op = (s[*pos] == 'f') ? '+' : '*';
		(*pos) += 2;
		parse_term(pos);
		printf("%c", op);
		if (s[*pos] == ',') 
			++(*pos);
		parse_term(pos);
		++(*pos);
	} else if (s[*pos] == 'x' || s[*pos] == 'y' || s[*pos] == 'z') {
		int idx = s[*pos] - 'x';
		if (in_bound[idx]) 
			printf("%c", s[*pos]);
		else
			printf("%d", idx + 1);
		++(*pos);
	} else if (s[*pos] == 'a') {
		printf("0");
		++(*pos);
	}
}

int main() 
{
	if (!fgets(s, sizeof(s), stdin)) 
		return 0;
	int len = strlen(s);
	s[--len] = '\0';
	
	int pos = 0;
	while (s[pos] == 'V' || s[pos] == 'E') {
		printf("%c%c", s[pos], s[pos + 1]);
		in_bound[s[pos + 1] - 'x'] = true;
		pos += 2;
	}
	
	parse_formula(&pos);
	printf("\n");
	
	return 0;
}
