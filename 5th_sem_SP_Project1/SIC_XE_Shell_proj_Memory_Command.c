#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

//sj 번호 구하는 식이 맞는지 집가서 확인!!!!





char *input_order;//input order
char *part_order;//part of the input_order
int his_num;//counting number for history

//linked list 구현
typedef struct node *nptr;
typedef struct node{
	int No;
	char order[80];
	nptr next; 
}node;

nptr root;
//number of commands saved in linked list
int command_num = 0;
//memory table
char **table;
//address of memory for memory command part
int val;
//position of latest dump
int address_pos;

//Shell command functions
void add_node(char*);
void read_directory();
void print_history();

//memory command functions

//calculating input memory into hexadecimal
int calc_address(char* str,int l);

//no address appointed
void print_memory1();
//only starting point appointed
void print_memory2(int);
//start & end point appointed
void print_memory3(int,int);
void edit_memory(int,int);
void fill_memory(int,int,int);
void reset();

//

int main(){
	int i,j;
	int l;
	//input address value
	int start = 0, end = 16*65536-1;
	char tmp;
	root = (nptr)malloc(sizeof(node));
	table = (char**)malloc(65536*sizeof(char*));
	for(i=0;i<65536;i++){
		table[i] = (char*)malloc(16*sizeof(char));
	}
	for(i=0;i<65536;i++){
		for(j=0;j<16;j++){
			table[i][j] = 50;
		}
	}
	
	
	
	while(1){
		input_order = (char*)malloc(80*sizeof(char));
		part_order = (char*)malloc(80*sizeof(char));
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
			fgets(part_order,80,stdin);
			
			//without address appointed
			if(part_order[0] == '\n') {
				add_node(input_order);
				print_memory1();
			}
			else if(part_order[0] == ' '){
				char* pos_space = strchr(part_order,' ');
				char* pos_comma = strchr(part_order,',');
				char* pos_enter = strchr(part_order,'\n');
				//only starting point address appointed
				if(pos_comma == NULL){
					l = pos_enter - (pos_space+1);
					start = calc_address(pos_space+1,l);
					//calculate starting point address
					if(start < 0 || start >= 16*(65536)){
						printf("WRONG RANGE OF ADDRESS!\n");
						continue;
					}

					l = strlen(part_order) - 1;
					strncat(input_order,part_order,l);
					add_node(input_order);
					//if the query is correct, add to history
					print_memory2(start);
				}

				//both starting and ending point address appointed
				if(pos_comma != NULL){
					l = pos_comma - (pos_space + 1);
					start = calc_address(pos_space + 1,l);
					l = pos_enter - (pos_comma + 2);
					end = calc_address(pos_comma + 2,l);
					//calculate starting point and ending point addresses
					if(end < start || start < 0 || end >= (16*65536)){
						printf("WRONG RANGE OF ADDRESS!\n");
						continue;
					}
					l = strlen(part_order) - 1;
					strncat(input_order,part_order,l);
					add_node(input_order);
					//if the query is correct, add to history
					print_memory3(start,end);
				}
			}
		}
		//edit
		else if(strcmp(input_order,"e") == 0 || strcmp(input_order,"edit") == 0){
			fgets(part_order,80,stdin);
			
			char* pos_space = strchr(part_order,' ');
			char* pos_comma = strchr(part_order,',');
			char* pos_enter = strchr(part_order,'\n');
			l = pos_comma - (pos_space + 1);
			start = calc_address(pos_space + 1,l);
			//calculate appointed address
			l = pos_enter - (pos_comma + 2);
			val = calc_address(pos_comma + 2,l);
			//calculate input value
			if(start < 0 || start >= (16*65536)){
				printf("WRONG RANGE OF ADDRESS!\n");
				continue;
			}
			if(val > 126 || val < 32){
				printf("INPUT VALUE = %d, WRONG VALUE!\n",val);
				continue;
			}
			//exception handling
			l = strlen(part_order);
			strncat(input_order,part_order,(l-1));
			add_node(input_order);
			
			edit_memory(start,val);
			
		}
		//fill
		else if(strcmp(input_order,"f") == 0 || strcmp(input_order,"fill") == 0){
			//fill add, add, val
			//        .    .   	-> 여기가 현재 pos_comma
			//         .   .	-> 두번째  pos_space
			//	       .   . 	-> 두번째 pos_comma
			//					. -> pos_enter
			//
			fgets(part_order,80,stdin);
			char* pos_space = strchr(part_order,' ');
			char* pos_comma = strchr(part_order,',');
			l = pos_comma - (pos_space + 1);
			start = calc_address(pos_space + 1,l);
			//calculate start address 
			pos_space = strchr(pos_comma,' ');
			pos_comma = strchr(pos_space,',');
			l = pos_comma - (pos_space + 1);
			end = calc_address(pos_space + 1,l);
			//calculate end address
			char* pos_enter = strchr(part_order,'\n');
			l = pos_enter - (pos_comma + 2);
			val = calc_address(pos_comma + 2,l);
			//calculate value
			if(end < start || start < 0 || end >= (16*65536)){
				printf("WRONG RANGE OF ADDRESS!\n");
				continue;
			}
			if(val > 126 || val < 32){
				printf("WRONG VALUE!\n");
				continue;
			}
			//exception handling
			l = strlen(part_order);
			strncat(input_order,part_order,l-1);
			add_node(input_order);
			//add to node
			fill_memory(start,end,val);
			
		}
		//reset
		else if(strcmp(input_order,"reset") == 0){
			add_node(input_order);
			reset();
		}
		
		//OPCODE TABLE command
		
		else if(strcmp(input_order,"opcode") == 0){
			
		}
		else if(strcmp(input_order,"opcodelist") == 0){
			
		}
		else{
			printf("%s\n",input_order);
			printf("WRONG COMMAND!\n");
		}
		free(input_order);
		free(part_order);
	}
	
	return 0;
}

//shell command functions
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
//////////////////////////////////////////////여기 고쳐야함
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
//memory command functions

int calc_address(char* str,int l){
	int res = 0;
	for(int i=0;i<l;i++){
		if(str[i] == 'A') { res = res*16 + 10;}
		else if(str[i] == 'B') { res = res*16 + 11;}
		else if(str[i] == 'C') { res = res*16 + 12;}
		else if(str[i] == 'D') { res = res*16 + 13;}
		else if(str[i] == 'E') { res = res*16 + 14;}
		else if(str[i] == 'F') { res = res*16 + 15;}
		else{ res = res*16 + (str[i]-'0');}
	}
	return res;
}

void print(int start, int end){
	int si = (start/16);
	int sj = start%16;
	int ei = (end/16);
	int ej = end%16;
	char line[16];
	int k;
	for(int i = si; i <= ei ; i++){
		printf("%05X ",i*16);
		if(i == si){
			k = 0;
			while(k < sj){
				printf("   ");
				k++;
			}
			if(si == ei){
				for(int j = sj; j <= ej; j++){
					printf("%2X ",table[i][j]);
				}
				k = ej;
				while(k<15){
					printf("   ");
					k++;
				}
				printf("; ");
				//print ASCII value representation
				k = 0;
				while(k<sj){
					printf(".");
					k++;
				}
				for(int i = sj;i<=ej;i++){
					if(table[si][i] < 20 || table[si][i] > 126){
						printf(".");
						continue;
					}
					else printf("%c",table[si][i]);
				}
		
				k = ej;
				while(k<15){
					printf(".");
					k++;
				}
				printf("\n");
				
			}
			if(si != ei){
				for(int j = sj; j < 16; j++){
					printf("%2X ",table[i][j]);
				}
				printf("; ");
				for(int j = 0; j < sj; j++){
					printf(".");
				}
				for(int j = sj; j < 16; j++){
					if(table[i][j] < 20 || table[i][j] > 126){
						printf(".");
						continue;
					}
					else printf("%c",table[i][j]);	
				}
				printf("\n");
			}
		}
		if((i != si) && (si != ei) && (i != ei)){
			for(int j = 0; j < 16; j++){
				printf("%2X ",table[i][j]);
			}
			printf("; ");
			for(int j = 0; j < 16; j++){
				if(table[i][j] < 20 || table[i][j] > 126){
					printf(".");
					continue;
				}
				else printf("%c",table[i][j]);
			}
			printf("\n");
		}
		if((si != ei) && (i == ei)){
			for(int j = 0; j <=ej; j++){
				printf("%2X ",table[i][j]);
			}
			k = ej;
			while(k < 15){
				printf("   ");
				k++;
			}
			printf("; ");
			for(int j = 0; j <=ej; j++)	{
				if(table[i][j] < 20 || table[i][j] > 126){
					printf(".");
					continue;
				}
				printf("%c",table[i][j]);
			}
			k = ej;
			while(k < 15){
				printf(".");
				k++;
			}
			printf("\n");
		}	
	}	
	return;	
}
void print_memory1(){
	int end;
	if(address_pos + 159 >= 16*65536){
		end = 16*65536 - 1;
		print(address_pos,end);
		address_pos = 0;
	}
	else{
		end = address_pos + 159;
		print(address_pos,end);
		address_pos = end + 1;
	}
	return;
}
void print_memory2(int start){
	int end;
	if(start + 159 >= 16*65536){
		end = 16*65536 - 1;
		print(start,end);
		address_pos = 0;
	}
	else{
		end = start + 159;
		print(start,end);
		address_pos = end + 1;
	}
	return;
}
void print_memory3(int start,int end){
	print(start,end);
	address_pos = end + 1;
	return;
}

void edit_memory(int address,int value){
	
	int i,j;
	j = address%16;
	i = address/16;
	table[i][j] = value;
	
	return;
}
void fill_memory(int start, int end, int value){
	int si = start/16;
	int sj = start%16;
	int ei = end/16;
	int ej = end%16;
	//첫째 줄
	int k = sj;
	if (si == ei){
		while(k <= ej){
			table[si][k] = value;
			k++;
		}
	}
	else{//si != ei
		while(si < ei){
			for(;sj<16;sj++){
				table[si][sj] = value;
			}
			sj = 0;
			si++;
		}
		//si = ei인 상황
		for(;sj<=ej;sj++){
			table[si][sj] = value;
		}
	}
	return;
}

void reset(){
	for(int i=0;i<65536;i++)
		for(int j=0;j<16;j++)
			table[i][j] = 0;
	return;
}




