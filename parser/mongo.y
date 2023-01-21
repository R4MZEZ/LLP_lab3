%{
void yyerror (char *s);
int yylex();
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "signatures.h"
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

struct query_tree tree = {0};
struct query_tree empty_tree = {0};

struct extended_comparator* cmp;
size_t vtype;
size_t size = 0;

int sockfd, numbytes;

void print_tree();
void set_cur_operation(uint8_t operation);
void set_cur_value(char* field, uint64_t val, double fval);
void append_val_setting(char* field, uint64_t val, double fval);
void switch_filter();
void set_comp();
void set_command(uint8_t command);
void *test_malloc(size_t size_of);
void print_ram();
void send_data();

#define MAXDATASIZE 100
#define PORT "3939"
%}

%union {uint64_t num; char *string; float fnum;}
%token DB
%token FIND INSERT DELETE UPDATE
%token <string> PARENT STRING
%token SET OR
%token LT LET GT GET NE
%token OPBRACE CLBRACE
%token OPCBRACE CLCBRACE
%token OPSQBRACE CLSQBRACE
%token COLON DOLLAR COMMA QUOTE
%token <num> FALSE TRUE INT_NUMBER
%token <fnum> FLOAT_NUMBER
%type <num> bool value operation comp

%%

syntax:	printer syntax;
	|
	;

printer: mongosh {send_data();}

mongosh: DB FIND OPBRACE OPCBRACE filters CLCBRACE CLBRACE {set_command(0);}
	  |
	  DB DELETE OPBRACE OPCBRACE filters CLCBRACE CLBRACE {set_command(1);}
	  |
	  DB INSERT OPBRACE parent_def COMMA vals_def CLBRACE {set_command(2);}
	  |
	  DB UPDATE OPBRACE OPCBRACE filters CLCBRACE COMMA DOLLAR SET COLON vals_def CLBRACE {set_command(3);}
	  ;

parent_def : OPCBRACE PARENT COLON INT_NUMBER CLCBRACE {set_cur_operation(0);
							vtype = INTEGER_T;
							set_cur_value("parent", $4, 0);
							switch_filter();};

vals_def : OPCBRACE set_vals CLCBRACE;

filters : filter {switch_filter();} | filter COMMA filters {switch_filter();};

filter : STRING COLON value {
				set_cur_operation(0);
				float val;
				if (vtype == FLOAT_T){
					memcpy(&val, &$3, sizeof(uint64_t));
					set_cur_value($1, 0, val);
				}else
					set_cur_value($1, $3, 0);

			}
	 |
	 STRING COLON operation {set_cur_value($1, $3, 0);}
	 |
	 DOLLAR OR OPSQBRACE filter COMMA filter CLSQBRACE {set_comp();}
	 ;

operation: OPCBRACE DOLLAR comp COLON value CLCBRACE {set_cur_operation($3); $$ = $5;};

set_vals : set_val
	   |
	   set_val COMMA set_vals

set_val : STRING COLON value {
				if (vtype == FLOAT_T){
					float val;
					memcpy(&val, &$3, sizeof(uint64_t));
					append_val_setting($1, 0, val);
				}else
					append_val_setting($1, $3, 0);

                             };

value : QUOTE STRING QUOTE {vtype = STRING_T; $$ = $2;}
	|
	INT_NUMBER {vtype = INTEGER_T; $$ = $1;}
	|
	FLOAT_NUMBER {vtype = FLOAT_T; memcpy(&$$, &$1, sizeof(uint64_t));}
	|
	bool {vtype = INTEGER_T; $$ = $1;}
	;

bool : TRUE {$$ = 1;}
       |
       FALSE {$$ = 0;}
       ;

comp : LT {$$ = 1;}
       |
       LET {$$ = 2;}
       |
       GT {$$ = 3;}
       |
       GET {$$ = 4;}
       |
       NE {$$ = 5;}
       ;
%%                     /* C code */


void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[]) {
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];

	if (argc != 2) {
	fprintf(stderr, "usage: client hostname\n");
	return 1;
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
	return 1;
	}

	// Проходим через все результаты и соединяемся к первому возможному
	for (p = servinfo; p != NULL; p = p->ai_next) {
	if ((sockfd = socket(p->ai_family, p->ai_socktype,
			     p->ai_protocol)) == -1) {
	    perror("client: socket\n");
	    continue;
	}

	if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
	    close(sockfd);
	    perror("client: connect\n");
	    continue;
	}

	break;
	}

	if (p == NULL) {
	fprintf(stderr, "client: failed to connect\n");
	return 2;
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *) p->ai_addr),
	      s, sizeof s);
	printf("client: connecting to %s\n", s);

	freeaddrinfo(servinfo);

	while(1){
		yyparse();
	}
	close(sockfd);
	return 0;
}

void send_data(){
	char buf[MAXDATASIZE];

	if (send(sockfd, "Hello, server!", 13, 0) == -1)
		perror("send");

	if ((numbytes = recv(sockfd, buf, MAXDATASIZE - 1, 0)) == -1) {
		perror("recv");
		return 1;
	}
	buf[numbytes] = 0;
	printf("client: received `%s`\n", buf);
}



void *test_malloc(size_t size_of){
    size += size_of;
    return malloc(size_of);
}

void print_ram(){
    printf("RAM USAGE: %zu bytes\n", size);
}

void append_val_setting(char* field, uint64_t val, double fval){
	struct value_setting* vs = test_malloc(sizeof(struct value_setting));
	struct field_value_pair fv = {.field = field, .val_type = vtype};
	fv.real_value = fval;
	fv.int_value = val;
	vs->fv = fv;
	vs->next = tree.settings;
	tree.settings = vs;

}

void set_cur_operation(uint8_t operation){
	struct extended_comparator* tmp = test_malloc(sizeof(struct extended_comparator));
	tmp->next = cmp;
	tmp->operation = operation;
	cmp = tmp;

}

void set_cur_value(char* field, uint64_t val, double fval){
	struct field_value_pair fv = {.field = field, .val_type = vtype};
	fv.real_value = fval;
	fv.int_value = val;
	cmp->fv = fv;
}

void switch_filter(){
	struct filter* f = test_malloc(sizeof(struct filter));
	struct comparator* tmp = test_malloc(sizeof(struct comparator));
        f->next = tree.filters;

        if (cmp->connected){
		tmp->next = test_malloc(sizeof(struct comparator));
		tmp->next->operation = cmp->connected->operation;
		tmp->next->fv = cmp->connected->fv;
	}
	tmp->operation = cmp->operation;
	tmp->fv = cmp->fv;

	if (tree.filters)
		tree.filters->comp_list = tmp;
	else{
		f->comp_list = tmp;
		tree.filters = f;
		f = test_malloc(sizeof(struct filter));
		f->next = tree.filters;
	}

	cmp = cmp->next;
	tree.filters = f;
}

void set_comp(){
	struct extended_comparator* tmp = NULL;
	tmp = cmp->next->next;
	cmp->connected = cmp->next;
	cmp->next = tmp;
}

void set_command(uint8_t command){
	tree.command = command;
}

void print_tree(){
	printf("COMMAND: %x\n", tree.command);
	size_t filter_count = 0;
	size_t comp_count = 0;
	printf(" FILTERS:\n");
	while (tree.filters){
		if (tree.filters->comp_list)
			printf("  FILTER %zu:\n", filter_count++);
		while (tree.filters->comp_list){
			char* field = tree.filters->comp_list->fv.field;
			uint64_t value = tree.filters->comp_list->fv.int_value;
			float fvalue = tree.filters->comp_list->fv.real_value;
			printf("   COMPARATOR %zu:\n", comp_count++);
			printf("    FIELD '%s'\n    OPERATION '%d'\n", field, tree.filters->comp_list->operation);
			switch(tree.filters->comp_list->fv.val_type){
				case STRING_T: printf("    VALUE '%s'\n", value); break;
				case INTEGER_T: printf("    VALUE '%d'\n", value); break;
				case FLOAT_T: printf("    VALUE '%f'\n", fvalue); break;
			}
			tree.filters->comp_list = tree.filters->comp_list->next;
		}
		printf("\n");
		comp_count = 0;
		tree.filters = tree.filters->next;
	}
	if (tree.settings)
		printf(" SETTINGS: \n");
	while (tree.settings){
		printf("  FIELD '%s'\n", tree.settings->fv.field);
		switch(tree.settings->fv.val_type){
			case STRING_T: printf("  VALUE '%s'\n", tree.settings->fv.int_value); break;
			case INTEGER_T: printf("  VALUE '%lu'\n", tree.settings->fv.int_value); break;
			case FLOAT_T: printf("  VALUE '%f'\n", tree.settings->fv.real_value); break;
		}
		printf("\n");
		tree.settings = tree.settings->next;
	}

	print_ram();
//	tree = empty_tree;
}


void yyerror (char *s) {fprintf (stderr, "%s\n", s);}