#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

char *input_order;//input order
char *part_order;//part of the input_order
int his_num;//counting number for history

//linked list 구현
typedef struct node *nptr;
typedef struct node{
	int No;
	char order[30];
	nptr next; 
}node;

nptr root;
int command_num = 0;
char **table;

void add_node(char*);
void read_directory();
void print_history();
void reset();

int main(){
	int i,j;
	root = (nptr)malloc(sizeof(node));
	table = (char**)malloc(65536*sizeof(char*));
	for(i=0;i<65536;i++){
		table[i] = (char*)malloc(16*sizeof(char));
	}
	
	
	
	
	while(1){
		input_order = (char*)malloc(30*sizeof(char));
		printf("sicsim>");
		scanf("%s",input_order);
		
		//Shell command
		//help
		if(strcmp(input_order,"h") == 0 || strcmp(input_order,"help") == 0){
			add_node(input_order);
			printf("h[elp]\n");
			printf("d[ir]\n");
			printf("q[uit]\n");
			printf("hi[story]\n");
			printf("du[mp] [start, end]\n");
			printf("e[dit] address,value\n");
			printf("f[ill] start,end,value\n");
			printf("reset\n");
			printf("opcode mnemonic\n");
			printf("opcodelist\n");

			continue;
		}
		//directory
		else if(strcmp(input_order,"d") == 0 || strcmp(input_order,"dir") == 0){
			read_directory();
			
			
			
		}
		//quit
		else if(strcmp(input_order,"q") == 0 || strcmp(input_order,"quit") == 0){
			return 0;
		}
		//history
		else if(strcmp(input_order,"hi") == 0 || strcmp(input_order,"history") == 0){
			add_node(input_order);
			print_history();
			
			
			
		}
		//Memory command
		//dump
		else if(strcmp(input_order,"du") == 0 || strcmp(input_order,"dump") == 0){
			printf("dump\n");
			
			
			
		}
		//edit
		else if(strcmp(input_order,"e") == 0 || strcmp(input_order,"edit") == 0){
			printf("edit\n");
			
		}
		//fill
		else if(strcmp(input_order,"f") == 0 || strcmp(input_order,"fill") == 0){

			printf("fill\n");
			
		}
		//reset
		else if(strcmp(input_order,"reset") == 0){
			add_node(input_order);
			reset();
		}
		
		//OPCODE TABLE command
		
		else if(strcmp(input_order,"opcode")){
			
		}
		else if(strcmp(input_order,"opcodelist")){
			
		}
		else{
			printf("WRONG COMMAND!\n");
		}
		free(input_order);
		free(part_order);

	}
	
	return 0;
}
void add_node(char* input){

	nptr tmp;
	for(tmp = root;tmp->next != NULL ; tmp = tmp->next){
	}
	nptr new;
	new = (nptr)malloc(sizeof(node));
	strcpy(new->order,input);
	new->No = ++command_num;
	tmp->next = new;
	return;
}
void read_directory(){
	//디렉토리 / 파일 구분
	char *cwd;
	char wd[BUFSIZ];
	cwd = getcwd(NULL,BUFSIZ);
	struct dirent *entry;
	DIR *dir = opendir(cwd);
	if(dir == NULL) {
		printf("WRONG PATH!\n");
		return;
	}
	while((entry=readdir(dir)) != NULL){
		printf("%s\t",entry->d_name);
	}
	closedir(dir);
	
	
	
	return;
}
void print_history(){
	nptr tmp=root->next;
	for(;tmp != NULL;tmp = tmp->next){
		printf("%d %s\n",tmp->No,tmp->order);
	}
	return;
}
void reset(){
	for(int i=0;i<65536;i++)
		for(int j=0;j<16;j++)
			table[i][j] = 0;
	return;
}
