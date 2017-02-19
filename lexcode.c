#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lex.h"


bool is_type(char *);
char* substring(char * , int ,int );
int check_regex(char *);
char* yytext(void);
int yylineno(void);

int flag =1;

/*char *tokentype[] = {";", ",", "'", "(", ")", "=", ".", "create", "table", "select", "delete", "from", "where", "insert", "into", "integer", "in", "values", "update", "set", "drop", "column", "add", "not", "NULL", "primary", "key", "*", "alter"};*/


typedef struct token{
	int token_class;
	char *token_text;
	int line_no;
} token;

int token_ptr = 0;		// icrement at each insertion for new token in token_list
int current_token_ptr = -1;		// increment at each call for yylex()
token token_list[1000];


int current_line_no = 0;


int tokenizefull(){
	char *a=(char * )malloc(sizeof(char)*1000);
	while(gets(a)){
		current_line_no++;
		char *tok= strtok(a," \t\n");
		while(tok != NULL){	int itemp=0;
			char *temp=(char * )malloc(sizeof(char)*100);
			strcpy(temp ,tok);
			while(strlen(temp) >0){
				while(!is_type(temp))          //define this func s.t it adds qualifying tokens to main token array.
					temp[strlen(temp)-1] ='\0';   //NULL char
				
				itemp += strlen(temp);
				strcpy(temp, substring(tok, itemp, strlen(tok)));  //define this func (string, start index, end index)

			}free(temp);
			tok = strtok(NULL, " \t\n");
		}

	}	
		
}

int yylex(){
	
	if(flag==1){
		tokenizefull();
		flag=0;
	}
	current_token_ptr++;
	return token_list[current_token_ptr].token_class;
	
}


bool is_type(char *temp){

	
	if ( strcmp(temp, ";")== 0 ) {
		token_list[token_ptr].token_class = semi_colon;
		token_list[token_ptr].token_text = ";";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, ",")== 0 ) {
		token_list[token_ptr].token_class = comma;
		token_list[token_ptr].token_text = ",";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, ".")== 0 ) {
		token_list[token_ptr].token_class = dot;
		token_list[token_ptr].token_text = ".";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "'")== 0 ) {
		token_list[token_ptr].token_class = quote;
		token_list[token_ptr].token_text = "'";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "(")== 0 ) {
		token_list[token_ptr].token_class = left_parenthesis;
		token_list[token_ptr].token_text = "(";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, ")")== 0 ) {
		token_list[token_ptr].token_class = right_parenthesis;
		token_list[token_ptr].token_text = ")";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "=")== 0 ) {
		token_list[token_ptr].token_class = equal;
		token_list[token_ptr].token_text = "=";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}	
	else if ( strcmp(temp, "create")== 0 ) {
		token_list[token_ptr].token_class = create;
		token_list[token_ptr].token_text = "create";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "table")== 0 ) {
		token_list[token_ptr].token_class = table;
		token_list[token_ptr].token_text = "table";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "select")== 0 ) {
		token_list[token_ptr].token_class = select;
		token_list[token_ptr].token_text = "select";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "delete")== 0 ) {
		token_list[token_ptr].token_class = delete;
		token_list[token_ptr].token_text = "delete";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "from")== 0 ) {
		token_list[token_ptr].token_class = from;
		token_list[token_ptr].token_text = "from";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "where")== 0 ) {
		token_list[token_ptr].token_class = where;
		token_list[token_ptr].token_text = "where";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "insert")== 0 ) {
		token_list[token_ptr].token_class = insert;
		token_list[token_ptr].token_text = "insert";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "into")== 0 ) {
		token_list[token_ptr].token_class = into;
		token_list[token_ptr].token_text = "into";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "values")== 0 ) {
		token_list[token_ptr].token_class = values;
		token_list[token_ptr].token_text = "values";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "update")== 0 ) {
		token_list[token_ptr].token_class = update;
		token_list[token_ptr].token_text = "update";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "set")== 0 ) {
		token_list[token_ptr].token_class = set;
		token_list[token_ptr].token_text = "set";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "drop")== 0 ) {
		token_list[token_ptr].token_class = drop;
		token_list[token_ptr].token_text = "drop";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "column")== 0 ) {
		token_list[token_ptr].token_class = column;
		token_list[token_ptr].token_text = "column";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "add")== 0 ) {
		token_list[token_ptr].token_class = add;
		token_list[token_ptr].token_text = "add";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "not")== 0 ) {
		token_list[token_ptr].token_class = not;
		token_list[token_ptr].token_text = "not";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "null")== 0 ) {
		token_list[token_ptr].token_class = null;
		token_list[token_ptr].token_text = "null";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "primary")== 0 ) {
		token_list[token_ptr].token_class = primary;
		token_list[token_ptr].token_text = "primary";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "key")== 0 ) {
		token_list[token_ptr].token_class = key;
		token_list[token_ptr].token_text = "key";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "*")== 0 ) {
		token_list[token_ptr].token_class = identifier;
		token_list[token_ptr].token_text = "*";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "integer")== 0 ) {
		token_list[token_ptr].token_class = data_type;
		token_list[token_ptr].token_text = "integer";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "alter")== 0 ) {
		token_list[token_ptr].token_class = alter;
		token_list[token_ptr].token_text = "alter";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else if ( strcmp(temp, "alter")== 0 ) {
		token_list[token_ptr].token_class = alter;
		token_list[token_ptr].token_text = "alter";
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
		return true;
		}
	else{
		if(check_regex(temp)){			//if regex then return identifier else erro
			return true;
		}
		else 
			return false;	
		
	}
	
	
}


int check_regex(char *temp){
	
	regex_t regex1,regex2,regex3;
	int reti1,reti2,reti3;;
	char* pattern1 = "^varchar([0-9][0-9]*)$";
	char* pattern3 = "^[_a-zA-Z][_a-zA-Z0-9]*$";
	char* pattern2 = "^[0-9][0-9]*$";
	reti1 = regcomp(&regex1, pattern1, 0);
	reti2 = regcomp(&regex2, pattern2, 0);
	reti3 = regcomp(&regex3, pattern3, 0);

	if(!regexec(&regex1, temp, 0, NULL, 0)){		// if match then 0 else 1
		token_list[token_ptr].token_class = data_type;
		token_list[token_ptr].token_text=(char *)malloc(strlen(temp)*sizeof(char));
		strcpy(token_list[token_ptr].token_text, temp);
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
	}
	else if(!regexec(&regex2, temp, 0, NULL, 0)){		// if match then 0 else 1
		token_list[token_ptr].token_class = integer;
		token_list[token_ptr].token_text=(char *)malloc(strlen(temp)*sizeof(char));
		strcpy(token_list[token_ptr].token_text , temp);
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
	}
	else if(!regexec(&regex3, temp, 0, NULL, 0)){		// if match then 0 else 1
		token_list[token_ptr].token_class = identifier;
		token_list[token_ptr].token_text=(char *)malloc(strlen(temp)*sizeof(char));
		strcpy(token_list[token_ptr].token_text ,temp);
		token_list[token_ptr].line_no = current_line_no;
		token_ptr++;
	}
	else{
//		printf("%s:unexpected character\n",temp);
		return 0;
	}	

	return 1;

}


char* substring(char* input, int start, int end){
	
	char *temp;
	temp = memcpy(temp,&input[start],end-start);
	temp[end-start] = '\0';
	return temp;
}


char* yytext(){

	return token_list[current_token_ptr].token_text;

}

int yylineno(){  return token_list[current_token_ptr].line_no;}



int main(void)
{

	int ntoken, vtoken;
	ntoken = yylex();
	while(ntoken){
		printf("%d:%s:%d\n", ntoken,yytext(),yylineno());
		ntoken=yylex();
	}
	return 0;
}

