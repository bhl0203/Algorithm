#include "20161617.h"

char input_order[80];//input order
char part_order[80];;//part of the input_order

//linked list 구현
typedef struct node *nptr;
typedef struct node{
	int No;
	char order[80];
	nptr next; 
}node;

typedef struct opnode *op_nptr;
typedef struct opnode{
	char opcode[10];
	char mnemonic[10];
	char tmp[5];
	op_nptr next;
}opnode;

op_nptr oproot[20];
//linked list for opcode
nptr root;
//number of commands saved in linked list
int command_num = 0;
//memory table
char **table;
//address of memory for memory command part
int val;
//position of latest dump
int address_pos;

/* * * * * * * * * * * * 
   Shell command functions
   * * * * * * * * * * */
void add_node(char*);
void read_directory();
void print_history();

/* 
   memory command functions
*/

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

/*
   opcode command functions
*/
//add opcode nodes on linked list
void add_opcode_node(int,char*,char*,char*);
//search input opcode
void search_opcode(char*);
//print all opcode
void print_opcode();

int main(){
	int i,j;
	int l;
	//input address value
	int start = 0, end = 16*65536-1;
	//opcode file
	FILE *fp = fopen("opcode.txt","r");
	//opcode
	char *opcode;
	//opcode hashtree list number
	int op;
	//mnemonic
	char *mnemonic;
	//final input for opcode
	char *temp;
	//opcode input string
	for(i=0;i<20;i++){
		oproot[i] = (op_nptr)malloc(sizeof(opnode));
	}
	
	while(1){
		op = 0;
		if(feof(fp)) break;
		opcode = (char*)malloc(20*sizeof(char));
		mnemonic = (char*)malloc(20*sizeof(char));
		temp = (char*)malloc(20*sizeof(char));
		fscanf(fp,"%s %s %s",opcode,mnemonic,temp);
		if(feof(fp)) break;
		for(i=0;i<strlen(mnemonic);i++){
			op += (mnemonic[i]-'A');
		}
		op = op%20;
		add_opcode_node(op,opcode,mnemonic,temp);
		free(opcode);
		free(mnemonic);
		free(temp);
	}




	//initialize history root
	root = (nptr)malloc(sizeof(node));
	//memory table
	table = (char**)malloc(65536*sizeof(char*));
	for(i=0;i<65536;i++){
		table[i] = (char*)malloc(16*sizeof(char));
	}
	//initialize memory table
	for(i=0;i<65536;i++){
		for(j=0;j<16;j++){
			table[i][j] = 0;
		}
	}
	
	
	
	while(1){
		//initialize input order string
		for(int i=0;i<80;i++){
			input_order[i] = '\0';
			part_order[i] = '\0';
		}

		
		printf("sicsim>");
		//input order
		scanf("%s",input_order);
		/*
		   Shell command
		*/
		//help
		if(strcmp(input_order,"h") == 0 || strcmp(input_order,"help") == 0){
			add_node(input_order);
			printf("h[elp]\n");
			printf("d[ir]\n");
			printf("q[uit]\n");
			printf("hi[story]\n");
			printf("du[mp] [start, end]\n");
			printf("e[dit] address, value\n");
			printf("f[ill] start, end, value\n");
			printf("reset\n");
			printf("opcode mnemonic\n");
			printf("opcodelist\n");

			continue;
		}
		//directory
		else if(strcmp(input_order,"d") == 0 || strcmp(input_order,"dir") == 0){
			add_node (input_order);
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
				/* * * * * * * * * *
				   only starting point address appointed
				* * * * * * * * * */
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
				/* * * * * * * * * * *
					both starting and ending point address appointed
				* * * * * * * * * * */
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
			if(pos_comma == NULL){
				printf("WRONG INPUT!\n");
				continue;
			}
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
			//exception handling
			l = strlen(part_order);
			strncat(input_order,part_order,(l-1));
			add_node(input_order);
			edit_memory(start,val);
			
		}
		//fill
		else if(strcmp(input_order,"f") == 0 || strcmp(input_order,"fill") == 0){
			//fill add, add, val
			fgets(part_order,80,stdin);
			char* pos_space = strchr(part_order,' ');
			char* pos_comma = strchr(part_order,',');
			if(pos_comma == NULL){
				printf("WRONG INPUT!\n");
				continue;
			}
			l = pos_comma - (pos_space + 1);
			start = calc_address(pos_space + 1,l);
			//calculate start address 
			pos_space = strchr(pos_comma,' ');
			pos_comma = strchr(pos_space,',');
			if(pos_comma == NULL){
				printf("WRONG INPUT!\n");
				continue;
			}
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
		
		/* * * * * * * *
		   OPCODE TABLE command
		* * * * * * * * */
		//opcode mnemonic
		else if(strcmp(input_order,"opcode") == 0){
			fgets(part_order,80,stdin);
			search_opcode(part_order+1);
		}
		//opcodelist
		else if(strcmp(input_order,"opcodelist") == 0){
			add_node(input_order);
			print_opcode();
		}
		else if(input_order[0] == '\n' || input_order[0] == ' '){
			continue;
		}
		else{
			printf("WRONG COMMAND!\n");
		}
	}
	
	return 0;
}

//shell command functions
void add_node(char* input){

	nptr tmp;
	//search final position of linked list
	for(tmp = root;tmp->next != NULL ; tmp = tmp->next){
	}
	nptr new;
	new = (nptr)malloc(sizeof(node));
	//initialize data of node to be added
	new->next = NULL;
	strcpy(new->order,input);
	new->No = ++command_num;
	//add node
	tmp->next = new;
	return;
}
//////////////////////////////////////////////여기 고쳐야함
void read_directory(){
	//디렉토리 / 파일 구분
	char *cwd;
	cwd = getcwd(NULL,BUFSIZ);
	struct dirent *entry;
	struct stat st;
	DIR *dir = opendir(cwd);
	char* directory_check;
	char* file_check;
	if(dir == NULL) {
		printf("WRONG PATH!\n");
		return;
	}
	while((entry=readdir(dir)) != NULL){
		directory_check = (char*)malloc(9999*sizeof(char));
		strcpy(directory_check,entry->d_name);
		//check whether file name is directory or not
		DIR *dir_tmp = opendir(directory_check);
		if(dir_tmp == NULL){
			if(lstat(entry->d_name, &st) == -1) continue;
			if(st.st_mode & S_IEXEC)
				printf("%s*\t",entry->d_name);
			else printf("%s\t",entry->d_name);
			//if it is not directory
		}
		if(dir_tmp != NULL){
			//if it is a directory, add'/' before printing
			printf("%s/\t",entry->d_name);
			closedir(dir_tmp);
		}
		free(directory_check);
	}
	closedir(dir);
	
	
	printf("\n");
	return;
}
void print_history(){
	//print all history
	nptr tmp=root->next;
	for(;tmp != NULL;tmp = tmp->next){
		printf("%d %s\n",tmp->No,tmp->order);
	}
	return;
}
//memory command functions

int calc_address(char* str,int l){
	int res = 0;
	//calculate input string into integer variable
	for(int i=0;i<l;i++){
		if(str[i] == 'A' || str[i] == 'a') { res = res*16 + 10;}
		else if(str[i] == 'B' || str[i] == 'b') { res = res*16 + 11;}
		else if(str[i] == 'C' || str[i] == 'c') { res = res*16 + 12;}
		else if(str[i] == 'D' || str[i] == 'd') { res = res*16 + 13;}
		else if(str[i] == 'E' || str[i] == 'e') { res = res*16 + 14;}
		else if(str[i] == 'F' || str[i] == 'f') { res = res*16 + 15;}
		else{ res = res*16 + (str[i]-'0');}
	}
	return res;
}

void print(int start, int end){
	int si = (start/16);
	int sj = start%16;
	int ei = (end/16);
	int ej = end%16;
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
					printf("%02X ",(unsigned char)table[i][j]);
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
					printf("%02X ",(unsigned char)table[i][j]);
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
				printf("%02X ",(unsigned char)table[i][j]);
			}
			printf("; ");
			for(int j = 0; j < 16; j++){
				if(table[i][j] < 20 || table[i][j] > 126){
					printf(".");
					continue;
				}
				else printf("%2c",table[i][j]);
			}
			printf("\n");
		}
		if((si != ei) && (i == ei)){
			for(int j = 0; j <=ej; j++){
				printf("%02X ",(unsigned char)table[i][j]);
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
				printf("%2c",table[i][j]);
			}
			k = ej;
			while(k < 15){
				printf(".");
				k++;
			}
			printf("\n");
		}	
	}
	if(end == 16*65536-1) address_pos = 0;
	return;	
}
void print_memory1(){
	//if input has no memory range appointed
	int end;
	if(address_pos + 159 >= 16*65536){
		//if ending point exceeds total memory
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
	//only starting point appointed
	int end;
	if(start + 159 >= 16*65536){
		//if ending point exceeds total memory
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
	//starting point and ending point appointed
	print(start,end);
	address_pos = end + 1;
	if (end == 16*65536-1) address_pos = 0;
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
	//change all memory value from starting point to ending point
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
	//set all memory value to 0
	for(int i=0;i<65536;i++)
		for(int j=0;j<16;j++)
			table[i][j] = 0;
	return;
}

void add_opcode_node(int op, char* opcode,char* mnemonic, char* yet){
	op_nptr tmp;
	for(tmp = oproot[op];tmp->next != NULL;tmp = tmp->next){}
	//search final point
	op_nptr new;
	new = (op_nptr)malloc(sizeof(opnode));
	new->next = NULL;
	//initialize next opcode node
	strcpy(new->opcode,opcode);
	strcpy(new->mnemonic,mnemonic);
	strcpy(new->tmp,yet);
	tmp -> next = new;
	return;
}

void search_opcode(char* str){
	int n = 0;
	char order[80] = "opcode ";
	str[strlen(str)-1] = '\0';
	for(int i = 0; i < strlen(str); i++){
		n += (str[i]-'A');
	}
	n = n%20;

	op_nptr tmp;
	for(tmp = oproot[n];tmp != NULL; tmp = tmp->next){
		if(strcmp(str,tmp->mnemonic) == 0){
			strcat(order,tmp->mnemonic);
			add_node(order);
			printf("opcode is %s\n",tmp->opcode);
			//found -> print corresponding opcode and return
			return;
		}
	}
	//opcode does not exist
	printf("OPCODE DOES NOT EXIST!\n");
	return;
}


void print_opcode(){
	op_nptr tmp;
	for(int i=0;i<20;i++){
		printf("%d : ",i);
		for(tmp = oproot[i]->next;tmp != NULL; tmp = tmp -> next){
			printf("[%s,%s]",tmp->mnemonic,tmp->opcode);
			if(tmp -> next != NULL) printf(" -> ");
		}
		printf("\n");
	}

	return;
}

