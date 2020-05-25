#include "20161617.h"

char input_order[80];//input order
char part_order[80];//part of the input_order

int lastlen;
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

typedef struct symbolnode *sn_nptr;
typedef struct symbolnode{
	char symbol[20];
	int loc;
	sn_nptr next;
}symbolnode;

typedef struct objectnode *ob_nptr;
typedef struct objectnode{
	char obcode[10];
	int length;
	int loc;
	ob_nptr next;
}objectnode;

typedef struct estabnode *es_nptr;
typedef struct estabnode{
	char symbol[10];
	int address;
	es_nptr next;
}estabnode;

op_nptr oproot[20];
//linked list for opcode
sn_nptr symbolroot[26];
//linked list for symbol table
ob_nptr obroot[3];
//linked list for object code
es_nptr esroot[3];
//linked list for external symbol table
nptr root;
//number of commands saved in linked list
int command_num = 0;
//memory table
char **table;
//address of memory for memory command part
int val;
//position of latest dump
int address_pos;
//position of BASE
int base;
//starting and ending point for asm file
int START;
int END;
//length of printed object code line
int length_obj = 0;
//checking current position on object code linked list
ob_nptr current;
char* obj_line;
int start_address=0;

//checking for errors
int error_type = 0;
int check_previous = 0;

//program address variable
long long int progaddress = 0;

//E record data
int exeaddr = 0;
int reg[9] = {0,};

//checking for estab already exists
int estabcheck = 0;

int *bp;


/* * * * * * * * * * * * 
   Shell command functions
 * * * * * * * * * * */
void add_node(char*);
void read_directory();
void print_history();
void read_filename(FILE*);
/* * * * * * * * * * * *
   memory command functions
 * * * * * * * * * * */

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

/* * * * * * * * * * * *
   opcode command functions
 * * * * * * * * * * * */

//add opcode nodes on linked list
void add_opcode_node(int,char*,char*,char*);
//search input opcode
void search_opcode(char*);
//print all opcode
void print_opcode();

/* * * * * * * * * * * *
   SIC/XE assembler command functions
 * * * * * * * * * * * */
void create_symbol_table(char*,int);
void obj_lst(char*);
int calc_format(char*);
int calc_symbol_loc(char*);
char* convert_obcode(long long int);
void add_obnode(long long int, int,int);
long long int calc_opcode(int,int,char*,char*,char*,char*);
int return_mnemonic_number(char);
char* return_opcode(char*);
int size_opcode(char*,char*,char*);
void print_symbol_table();

/* * * * * * * * * * * *
	project 3 command functions
 * * * * * * * * * * * */
//loader function 1
int loaderpass1(int n, char* progname[], FILE* prog[],int progl[]);
//adding estab node for making estab
int add_esnode(char*,int);
//loader function 2
int loaderpass2(int n, char* progname[], FILE* prog[],int progl[]);
int saver(char arr[][8], char* str,int l);
void l_T(char* str,int n);
void M(char* str, int n,char arr[][8]);


//return string into long long int(string to hex)
//long long int breakpoint(char*);


//run function

void run();
void format1(int);
void format2(int);
void format34(int,int);
//function for STL,A,S,X...
void store(int,int);

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
	//symbol table memory allocation

	for(int i=0;i<26;i++){
		symbolroot[i] = (sn_nptr)malloc(sizeof(symbolnode));
		symbolroot[i]->next = NULL;
	}
	//initialize external symbol table for loader function pass1
	for(int i=0;i<3;i++){
		esroot[i] = (es_nptr)malloc(sizeof(estabnode));
		esroot[i]->next = NULL;
	}
	
	bp = (int*)malloc(sizeof(int)*65536*16);
	memset(bp,0,sizeof(bp));
//	for(int i=0;i<65536*16;i++) bp[i] = 1;
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
			printf("assemble filename\n");
			printf("type filename\n");
			printf("symbol\n");
			printf("progaddr address\n");
			printf("loader object filename1 object filename2 ...\n");
			printf("bp\n");
			printf("bp clear\n");
			printf("bp address\n");
			printf("run\n");
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
		//type filename
		else if(strcmp(input_order,"type") == 0){
			fgets(part_order,80,stdin);
			//read wanted filename
			l = strlen(part_order);
			part_order[l-1] = '\0';
			//target file name saved in part_order
			FILE *readfile = fopen(part_order+1,"r");
			if(readfile == NULL) {
				//if file doesn't exist
				printf("file not found!\n");
				continue;
			}
			else {
				//if file exists
				strncat(input_order,part_order,l-1);
				//add to history
				add_node(input_order);
				read_filename(readfile);
			}

			fclose(readfile);
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
			if(val < 0 || val >= 16*16){
				printf("WRONG INPUT!\n");
				continue;
			}
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
			if(val < 0 || val >= 16*16){
				printf("WRONG INPUT!\n");
				continue;
			}
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

		/* * * * * * * * 
		   SIC/XE assembler command
		 * * * * * * * */
		//assemble filename
		else if(strcmp(input_order,"assemble") == 0){
			fgets(part_order,80,stdin);
			//cut out target filename
			l = strlen(part_order);
			part_order[l-1] = '\0';
			obj_lst(part_order+1);
		}
		//symbol
		else if(strcmp(input_order,"symbol") == 0){
			add_node(input_order);
			print_symbol_table();
		}
		
		/* * * * * * * *
			project 3 command
		 * * * * * * * */
		//program address appointment command
		//progaddr
		else if(strcmp(input_order, "progaddr") == 0){
//			scanf("%llX",&progaddress);
			fgets(part_order,80,stdin);
			if(part_order[0] == '\n' || part_order[0] == '\0'){
				printf("Wrong Input!\n");
				continue;
			}
			int l = strlen(part_order);
			part_order[l-1] = '\0';
			progaddress = strtol(part_order+1,NULL,16);
			if(progaddress<0 || progaddress>0xFFFFF){
				printf("Wrong range of program address!\n");
				continue;
			}
			strcat(input_order,part_order);
			add_node(input_order);
		}
		//loader command
		else if(strcmp(input_order,"loader") == 0){
			int prog_num = 0;
			int prog_length[3] = {0,};
			char* progname[3];
			FILE* prog[3];
			int errorflag = 0;
			for(int i=0;i<3;i++){
				progname[i]= (char*)malloc(sizeof(char)*26);
				memset(progname[i],0,sizeof(progname[i]));
			}
			fgets(part_order,80,stdin);
			prog_num = sscanf(part_order,"%s %s %s",progname[0], progname[1], progname[2]);
			/* * * * * * * *
			   pass1
			 * * * * * * * */
			if(estabcheck == 1){
				//if estab alreay exists, initialize it
				for(int i=0;i<3;i++){
					esroot[i] = NULL;
				}
				for(int i=0;i<3;i++){
					esroot[i] = (es_nptr)malloc(sizeof(estabnode));
					esroot[i]->next = NULL;
				}
				estabcheck = 0;
					
			}
			errorflag = loaderpass1(prog_num,progname,prog,prog_length);
			if(errorflag == 1){
				errorflag = 0;
				continue;
			}
						
			
			/* * * * * * * *
			   pass2
			 * * * * * * * */
			if(errorflag == 0){
				errorflag = loaderpass2(prog_num,progname,prog,prog_length);
			}
			if(errorflag == 1){
				errorflag = 0;
				continue;
			}
			
			/* * * * * * * *
			   final print
			 * * * * * * * */
			reg[2] = prog_length[0];
			lastlen = prog_length[0] + esroot[0]->address;
			//saving program length
			reg[8] = esroot[0]->address;
			//saving program length on L register
			printf("control symbol address length\n");
			printf("section name\n");
			printf("--------------------------------\n");
			for(int i=0;i<prog_num;i++){
				printf("%-6s           %04X   %04X\n",esroot[i]->symbol,esroot[i]->address,prog_length[i]);
				//print control section,symbol name, address length
				es_nptr tmp;
				for(tmp = esroot[i]->next;tmp != NULL;tmp = tmp->next){
					printf("        %6s   %04X\n",tmp->symbol,tmp->address);
				}
				//print all external symbols
			}
			
			printf("--------------------------------\n");
			printf("           total length %04X\n",prog_length[0]+prog_length[1]+prog_length[2]);
			estabcheck = 1;
			for(int i=0;i<3;i++){
				free(progname[i]);
			}
			int l = strlen(part_order);
			part_order[l-1] = '\0';
			strcat(input_order,part_order);
			add_node(input_order);
		}
		
		//breakpoint command
		else if(strcmp(input_order, "bp") == 0){
			fgets(part_order,80,stdin);
			//print all breakpoints
			if(part_order[0] == '\n'){
				printf("\t    breakpoint\n");
				printf("\t    ----------\n");
				for(int i=0;i<65536*16;i++){
					if(bp[i]) printf("\t    %X\n",i);
				}
				add_node(input_order);
				continue;
			}
			//clear all breakpoints
			l = strlen(part_order);
			part_order[l-1] = '\0';
			if(strcmp(part_order+1,"clear") == 0){
				for(int i=0;i<65536*16;i++){
					bp[i] = 0;
				}
				printf("\t    [ok] clear all breakpoints\n");
				add_node("bp clear");
			}
			//create breakpoint
			else{
				int k = strtol(part_order+1,NULL,16);
				if(k>0xFFFFF || k < 0){
					printf("wrong range of breakpoint!\n");
					continue;
				}
				//exception for wrong range of address
				bp[k] = 1;
				printf("\t    [ok] create breakpoint %04X\n",k);
				strcat(input_order,part_order);
				add_node(input_order);
			}
		}
		else if(strcmp(input_order,"run") == 0){
			//all functions on external function
			run();
			add_node("run");
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
void read_filename(FILE* readfile){
	char c;
	while((c = fgetc(readfile)) != EOF){
		printf("%c",c);
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
					if(table[si][i] < 0x20 || table[si][i] > 126){
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
					if(table[i][j] < 0x20 || table[i][j] > 126){
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
				if(table[i][j] < 0x20 || table[i][j] > 126){
					printf(".");
					continue;
				}
				else printf("%c",table[i][j]);
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
				if(table[i][j] < 0x20 || table[i][j] > 126){
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
/* * * * * * * * * * * *
   SIC/XE assembler command functions
 * * * * * * * * * * * */
void create_symbol_table(char* str,int loc){
	sn_nptr tmp;
	sn_nptr before;
	sn_nptr new;
	new = (sn_nptr)malloc(sizeof(symbolnode));
	new->next = NULL;
	new->loc = loc;
	strcpy(new->symbol,str);
	//if it is first node
	if(symbolroot[str[0]-'A'] -> next == NULL){
		symbolroot[str[0]-'A']->next = new;
		return;
	}
	before = symbolroot[str[0]-'A'];
	for(tmp = symbolroot[str[0]-'A']->next;tmp != NULL;tmp = tmp->next){
		//if it is not first node
		if(strcmp(tmp->symbol,str)>0){
			//tmp_symbol>input str
			before->next = new;
			new->next = tmp;
			before = before->next;
			//push before current node
		}

		if(strcmp(tmp->symbol,str)<0){
			//tmp_symbol<input str
			if(tmp->next != NULL){
				if(strcmp(tmp->next->symbol,str)<0)
					continue;
				else{
					new->next = tmp->next;
					tmp->next = new;
				}
			}
			if(tmp->next == NULL){
				tmp->next = new;
			}
			//push after current node if next node is smaller than new node
		}
	}
	return;
}
void create_obj(FILE* fp,int flag){
	//creating object file(printing lines)
	//do nothing
	if(flag == 0){
		return;
	}
	int l = current->length;
	//print current line and change line
	if(flag == 1){
		//6 - starting address, 2 - length of line in bytes, line
		fprintf(fp,"T%06X%02X%s\n",start_address,length_obj/2,obj_line);
		length_obj = 0;
		free(obj_line);
		start_address = current->loc;
		obj_line = (char*)malloc(sizeof(char)*256);
		memset(obj_line,0,sizeof(obj_line));
	}
	if(flag == 2){
		//start new line
		if(length_obj == 0){
			//initialize line
			start_address = current->loc;
			strncpy(obj_line,current->obcode,l);
			length_obj += l;
		}
		//string gone too far
		else if(length_obj + current->length > 60){
		//6 - starting address, 2 - length of line in bytes, line
			fprintf(fp,"T%06X%02X%s\n",start_address,length_obj/2,obj_line);
			start_address = current->loc;
			free(obj_line);
			length_obj = l;
			obj_line = (char*)malloc(sizeof(char)*256);
			memset(obj_line,0,sizeof(obj_line));
			strncpy(obj_line,current->obcode,l);
		}
		//ordinary case
		else{
			length_obj += l;
			strncat(obj_line,current->obcode,l);
		}
	}
	return;
}
void obj_lst(char* f){
	//location counter
	int loc;
	//line counter
	int line = 5;
	long long int object = 0;
	char* ob;
	char* str;
	char* str1;
	char* str2;
	char* str3;
	char* str4;
	
	char* string;
	// input number of buffers on current line
	int ret;
	//size of current opcode
	int mem = 9;
	//flag for checking symbol exists / stch / ldch / compr
	int flag = 0;
	FILE *fp = fopen(f,"r");
	int startcheck = 0;
	int endcheck = 0;
	if(fp == NULL){
		printf("FILE NOT FOUND!!!\n");
		return;
	}
	if(check_previous == 1){
		for(int i=0;i<26;i++){
			free(symbolroot[i]);
			symbolroot[i] = (sn_nptr)malloc(sizeof(symbolnode));
			symbolroot[i] -> next = NULL;
		}
	}
	//make string into ***.obj
	while(!feof(fp)){
		str = (char*)malloc(sizeof(char)*80);
		str1 = (char*)malloc(sizeof(char)*20);
		str2 = (char*)malloc(sizeof(char)*20);
		str3 = (char*)malloc(sizeof(char)*20);
		str4 = (char*)malloc(sizeof(char)*20);
		string = fgets(str,80,fp);
		ret = sscanf(str,"%s %s %s %s",str1,str2,str3,str4);
		if(strcmp(str2,"START") == 0) {
			//check if there is starting point
			startcheck = 1;
			START = atoi(str3);
			loc = START;
		}
		if(startcheck == 0){
			// crash program if there is no starting point on first line
			printf("WRONG START POINT!\n");
			fclose(fp);
			return;
		}
		if(strcmp(str1,"END") == 0) {
			//check if there is ending point
			endcheck = 1;
			END = loc;
			break;
		}
		//symbol exists
		if(str[0]<='Z' && str[0]>='A'){
			//str1 == symbol
			create_symbol_table(str1,loc);
			//check if there is previously compiled code(symbol table)
			check_previous = 1;
			//str2 == opcode
			if(str2[0] == '+'){
				mem = 4;
			}
			else{
				//save memory of opcode in bytes
				mem = size_opcode(str2,str3,str4);
				if(mem == -1){
					printf("INVALID OPCODE MNEMONIC\n");
					fclose(fp);
					return;
				}
			}
			loc = loc + mem;
			//str3 == ?

		}
		//without symbol
		else{
			//str1 == opcode
			if(str1[0] == '+'){
				mem = 4;
			}
			else{
				mem = size_opcode(str1,str2,str3);
				if(mem == -1){
					printf("INVALID OPCODE MNEMONIC\n");
					fclose(fp);
					return;
				}
			}
			loc = loc + mem;


			//str2 == ?
		}

		free(str);
		free(str1);
		free(str2);
		free(str3);
		free(str4);
	}
	fclose(fp);
	if(endcheck == 0){
		printf("NO END INPUT\n");
		return;
	}
//symbol table created
	if(startcheck == 0) return;


	loc = 0;
	fp = fopen(f,"r");

	int l = strlen(f);
	char flst[50];
	char fobj[50];
	for(int i=0;i<50;i++){
		flst[i] = '\0';
		fobj[i] = '\0';
	}
	//names of object and list file
	strncpy(flst,f,l-4);
	strncpy(fobj,f,l-4);
	strncat(flst,".lst",4);
	strncat(fobj,".obj",4);


	FILE *lst = fopen(flst,"w");
	FILE *obj = fopen(fobj,"w");
	obj_line = (char*)malloc(sizeof(char)*256);
	int obj_flag;
	//0 - do nothing
	//1 - print string, then change line
	//2 - strcat string
	while(!feof(fp)){
		object = 1;
		obj_flag = 2;
		str = (char*)malloc(sizeof(char)*80);
		ob = (char*)malloc(sizeof(char)*5);
		str1 = (char*)malloc(sizeof(char)*20);
		str2 = (char*)malloc(sizeof(char)*20);
		str3 = (char*)malloc(sizeof(char)*20);
		str4 = (char*)malloc(sizeof(char)*20);
		string = fgets(str,80,fp);
		char* ent = strchr(string,'\n');
		l = ent-string;
		string[l] = '\0';
		ret = sscanf(str,"%s %s %s %s",str1,str2,str3,str4);
		//start or end
		if(strcmp(str1,"END") == 0){
			fprintf(lst,"%d\t          %-s\n",line,string);
			break;
		}
		if(strcmp(str2,"START") == 0){
			loc = atoi(str3);
			//initialize object code root
			obroot[0] = (ob_nptr)malloc(sizeof(objectnode));
			strcpy(obroot[0]->obcode,str1);
			obroot[0]->next = NULL;
			obroot[1] = (ob_nptr)malloc(sizeof(objectnode));
			current = obroot[1];
			obroot[1]->next = NULL;
			obroot[2] = (ob_nptr)malloc(sizeof(objectnode));
			//initialize starting location
			START = loc;
			fprintf(lst,"%d\t  %04X    %-s\n",line,loc,string);
			fprintf(obj,"H%-6s%06X%06X\n",obroot[0]->obcode,START,END-START);
			line = line+5;
			continue;
		}
		//symbol exists
		if(str[0]<='Z' && str[0]>='A'){
			flag = 1;
			//str1 == symbol
			//str2 == opcode
			if(strcmp(str2,"BYTE") == 0){
				if(str3[0] == 'X')	flag = 5;
				if(str3[0] == 'C')	flag = 6;
			}
			if(strcmp(str2,"RESW") == 0 || strcmp(str2,"RESB") == 0){
				if(length_obj == 0){
					obj_flag = 0;
				}
				if(length_obj != 0){
					obj_flag = 1;
				}
				flag = 9;
			}
			if(calc_format(str2) == 2){
				flag = 7;
			}
			if(str2[0] == '+'){
				flag = 2;
				mem = 4;
			}
			else{
				
				mem = size_opcode(str2,str3,str4);
				if(mem == -1){
					return;
				}
			}
			if(flag == 1){
				//foramt 3
				object = calc_opcode(flag,loc+mem,str1,str2,str3,str4);
				fprintf(lst,"%d\t  %04X    %-25s\t%06llX\n",line,loc,string,object);
			}
			if(flag == 2){
				//foramt 4
				object = calc_opcode(flag,loc+mem,str1,str2+1,str3,str4);
				fprintf(lst,"%d\t  %04X    %-25s\t%08llX\n",line,loc,string,object);
			}
			//flag = 5, 6
			//command 'BYTE' - calculate program counter according to command in bytes
			if(flag == 5){
				
				object = calc_opcode(flag,loc+mem,str1,str2+1,str3,str4);
				fprintf(lst,"%d\t  %04X    %-25s\t%02llX\n",line,loc,string,object);
			}
			if(flag == 6){
				object = calc_opcode(flag,loc+mem,str1,str2+1,str3,str4);
				fprintf(lst,"%d\t  %04X    %-25s\t%llX\n",line,loc,string,object);
			}
			if(flag == 7){
				//format 2
				object = calc_opcode(flag,loc+mem,str1,str2,str3,str4);
				fprintf(lst,"%d\t  %04X    %-25s\t%04llX\n",line,loc,string,object);
			}
			if(flag == 9){
				//no need of object code (RESW, RESB)
				object = calc_opcode(flag,loc+mem,str1,str2,str3,str4);
				fprintf(lst,"%d\t  %04X    %-25s\t\n",line,loc,string);
			}
			create_obj(obj,obj_flag);
			loc = loc + mem;

		}
		//comment in asm file
		else if(str[0]=='.'){
			fprintf(lst,"%d\t          %s\n",line,string);
		}
		//without symbol
		//repitition of program above, only strings shifted right (str1 -> str2, ...)
		else{
			flag = 3;
						//BASE case
			if(strcmp(str1,"BASE") == 0){
				base = calc_symbol_loc(str2);
				fprintf(lst,"%d\t          %-s\n",line,string);
				line = line+5;
				continue;
			}
			if(calc_format(str1) == 2){
				mem = 2;
				flag = 8;
			}

			if(strcmp(str1,"RESW") == 0 || strcmp(str1,"RESB") == 0){
				if(length_obj == 0){
					obj_flag = 0;
				}
				if(length_obj != 0){
					obj_flag = 1;
				}
				flag = 9;
			}
			//str1 == opcode
			else if(str1[0] == '+'){
				flag = 4;
				mem = 4;
			}
			else{
				mem = size_opcode(str1,str2,str3);
				if(mem == -1){
					return;
				}
			}
			if(flag == 3){
				//
				object = calc_opcode(flag,loc+mem,str1,str2,str3,str4);
				fprintf(lst,"%d\t  %04X    %-25s\t%06llX\n",line,loc,string,object);
			}
			if(flag == 4){
				object = calc_opcode(flag,loc+mem,str1+1,str2,str3,str4);
				fprintf(lst,"%d\t  %04X    %-25s\t%08llX\n",line,loc,string,object);
			}
			if(flag == 8){
				object = calc_opcode(flag,loc+mem,str1,str2,str3,str4);
				fprintf(lst,"%d\t  %04X    %-25s\t%04llX\n",line,loc,string,object);
			}

			if(flag == 9){
				object = calc_opcode(flag,loc+mem,str1,str2,str3,str4);
				fprintf(lst,"%d\t  %04X    %-25s\t\n",line,loc,string);
			}

			loc = loc + mem;
			
			create_obj(obj,obj_flag);
			//str2 == ?
		}


		line = line+5;
		free(ob);
		free(str);
		free(str1);
		free(str2);
		free(str3);
		free(str4);
	}
	//print final line of object file
	fprintf(obj,"T%06X%02X%s\n",start_address,length_obj/2,obj_line);
	free(obj_line);

	ob_nptr tmp;
	for(tmp = obroot[2]->next;tmp != NULL;tmp = tmp->next){
		fprintf(obj,"M%06X05\n",tmp->loc+1);
	}
	//print memory relocated positions in .obj file
	fprintf(obj,"E%06X",START);
	fclose(lst);
	fclose(obj);
	fclose(fp);
	char node_str[20] = "assemble ";
	for(int i = 9;i<20;i++) node_str[i] = '\0';
	strcat(node_str,f);
	add_node(node_str);
	
	//if all process is done, free all headers
	for(int i=0;i<3;i++){
		free(obroot[i]);
	}	
	return;
}
int calc_format(char* str){
	//return format(size of memory needed for input command)
	int format = 4;
	int n = 0;
	int l = strlen(str);
	for(int i=0;i<l;i++){
		n = n + (str[i]-'A');
	}
	n = n % 20;
	op_nptr tmp;
	//check for value saved in oproot linked list
	for(tmp = oproot[n];tmp != NULL;tmp = tmp->next){
		if(strcmp(str,tmp->mnemonic) == 0){
			format = (int)(tmp->tmp[0]-'0');
		}
	}
	return format;
}
int calc_symbol_loc(char* str){
	int res;
	sn_nptr tmp;
	if(str[0] == '#' || str[0] == '@'){
		for(tmp = symbolroot[str[1]-'A'];tmp != NULL;tmp = tmp->next){
			if(strcmp(tmp->symbol,str+1) == 0){
				return tmp->loc;
			}
		}
	}
	else{
		for(tmp = symbolroot[str[0]-'A'];tmp != NULL;tmp = tmp->next){
			if(strcmp(tmp->symbol,str) == 0){
				return tmp->loc;
			}
		}
	}
	//return error
	return -1;
}
char* convert_obcode(long long int ob){
	//conver obcode from hexadecimal to string
	char* str;
	char tmp[10];
	int cnt = 0;
	str = (char*)malloc(sizeof(char)*10);
	for(int i=0;i<10;i++) {
		str[i] = '0';
		tmp[i] = '0';
	}
	while(ob != 0){
		if(ob%16 == 10) tmp[cnt] = 'A';
		else if(ob%16 == 11) tmp[cnt] = 'B';
		else if(ob%16 == 12) tmp[cnt] = 'C';
		else if(ob%16 == 13) tmp[cnt] = 'D';
		else if(ob%16 == 14) tmp[cnt] = 'E';
		else if(ob%16 == 15) tmp[cnt] = 'F';
		else tmp[cnt] = (ob % 16) + '0';
		ob = ob / 16;
		cnt++;
	}
	//save backwards
	if(cnt == 1 && tmp[0] >='0' && tmp[0]<='9'){
		str[0] = '0';
		str[1] = tmp[0];
		str[2] = '\0';
		return str;
	}
	if(cnt == 5) cnt = 6;
	if(cnt == 7) cnt = 8;
	tmp[cnt] = '\0';
	str[cnt] = '\0';
	int l = cnt-1;
	//save in correct order in another string
	for(int i = 0;i<=l;i++){
		str[i] = tmp[l-i];
	}
	return str;
}
void add_obnode(long long int ob, int loc, int flag){
	//add to memory allocation too if flag = 1;
	ob_nptr new;
	char* obcode;
	obcode = (char*)malloc(sizeof(char)*10);
	//saved object code to string
	obcode = convert_obcode(ob);
	//initialize new objectnode
	new = (ob_nptr)malloc(sizeof(objectnode));
	new -> next = NULL;
	strcpy(new->obcode,obcode);
	new->length = strlen(obcode);
	new->loc = loc;
	current->next = new;



	ob_nptr tmp2;
	ob_nptr new2;
	
	if(flag == 1){
		//if memory is relocated, also save in obroot[w]
		for(tmp2 = obroot[2];tmp2 ->next != NULL;tmp2 = tmp2->next){}
		new2 = (ob_nptr)malloc(sizeof(objectnode));
		new2->next = NULL;
		strcpy(new2->obcode,obcode);
		new2->length = strlen(obcode);
		new2->loc = loc;
		tmp2->next = new2;

	}
	current = current->next;
	return;
}
long long int calc_opcode(int flag,int loc,char* str1, char* str2, char* str3, char* str4){
	long long int res = 0;
	int n,i,x,b,p,e;
	int format;
	int tmp;
	int disp;
	//variables for saving object node
	int mem;
	//checking for format 4 & '#'
	int ob_flag = 0;
	
	
	x = 0;
	e = 0;
	if(flag == 1 || flag == 2){
		//str2 = mnemonic
		format = calc_format(str2);
	}
	if(flag == 3 || flag == 4){
		//str1 = mnemonic
		format = calc_format(str1);
	}
	char* ob;
	ob = (char*)malloc(sizeof(char)*8);
	if(format == 1){
		mem = 1;
		if(flag == 1 || flag == 2){
			//str2 = mnemonic
			ob = return_opcode(str2);
			if(ob == NULL) return -1;
			res = calc_address(ob,2);
		}
		if(flag == 3 || flag == 4){
			//str1 = mnemonic
			ob = return_opcode(str1);
			if(ob == NULL) return -1;
			res = calc_address(ob,2);
		}
	}
	else if(format>2){
		if(flag == 1){
			mem = 3;
			//symbol exists, str1 = symbol, str2 = mnemonic, str3 = command, format 3
			ob = return_opcode(str2);
			if(ob == NULL) return -1;
			res = calc_address(ob,2);
			//address- pc?
			if(str4[0] == 'X'){
				str3[strlen(str3)-1] = '\0';
			}

			tmp = calc_symbol_loc(str3);
			//check whether format is base relative, or program relative
			disp = tmp - loc;
			if(-2048 <= disp && disp <= 2047){
				if(disp < 0)
					disp = disp + 4096;
				b = 0,p = 1;
			}
			else if(disp <= -2049){
				disp = tmp - base;
				b = 1,p = 0;

			}
			//done calculating b,p
			
			if(str4[0] == 'X'){
				x = 1;
			}
			if(str3[0] == '#'){
				//immediate addressing
				if(str3[1] >= '0' && str3[1] <= '9'){
					n = 0,i = 1,b = 0,p = 0;
					disp = atoi(str3+1);
				}
				else{
					n = 0,i = 1,b = 0,p = 1;
				}
			}
			if(str3[0] == '@'){
				//indirect addressing
				n = 1,i = 0;
			}
			else{
				//simple addressing
				n = 1,i = 1;
			}
			//done calculating n,i
			res = res + 2*n + i;
			res = 16*res+8*x+4*b+2*p+e;
			res = res*16*16*16+disp;
		}

		if(flag == 2){
			ob_flag = 1;
			mem = 4;
			//symbol exists, str1 = symbol, str2 = mnemonic, str3 = command, format 4
			e = 1;
			b = 0,p = 0;
			ob = return_opcode(str2);
			if(ob == NULL) return -1;
			res = calc_address(ob,2);
			if(str4[0] == 'X'){
				str3[strlen(str3)-1] = '\0';
			}

			tmp = calc_symbol_loc(str3);
			disp = tmp;
			//program counter relative
			if(str4[0] == 'X'){
				x = 1;
			}
			if(str3[0] == '#'){
				//should not add to memory relocation if immediate addressing
				ob_flag = 0;
				//immediate addressing
				n = 0,i = 1;
				if(str2[1] >= '0' && str2[1] <= '9'){
					n = 0,i = 1;
					disp = atoi(str3+1);
				}
			}
			if(str3[0] == '@'){
				//indirect addressing
				n = 1,i=0;
			}
			else{
				//simple addressing
				n=1,i=1;
			}
			//done calculating n,i
			res = res + 2*n + i;
			res = 16*res+8*x+4*b+2*p+e;
			res = res*16*16*16*16*16+disp;
			
		}
		if(flag == 3){
			mem = 3;
			//symbol X str1 = mnemonic, str2 = command, format 3
			ob = return_opcode(str1);
			if(ob == NULL) return -1;
			res = calc_address(ob,2);
			if(strcmp(str1,"RSUB") == 0){
				res = res+3;
				res = res*256*256;
				add_obnode(res,loc-mem,ob_flag);
				return res;
			}
			if(str3[0] == 'X'){
				str2[strlen(str2)-1] = '\0';
			}
			tmp = calc_symbol_loc(str2);
			
			disp = tmp-loc;
			if(-2048 <= disp && disp <= 2047){
				if(disp < 0)
					disp = disp + 4096;
				b = 0,p = 1;
			}
			else if(disp <= -2049){
				disp = tmp - base;
				b = 1,p = 0;

			}
			//done calculating b,p
		
			if(str3[0] == 'X'){
				x = 1;
			}
			if(str2[0] == '#'){
				//immediate addressing
				if(str2[1] >= '0' && str2[1] <= '9'){
					n = 0,i = 1,b = 0,p = 0;
					disp = atoi(str2+1);
				}
				else{
					n = 0,i = 1,b = 0,p = 1;
				}
			}
			else if(str2[0] == '@'){
				//indirect addressing
				n = 1,i = 0;
			}
			else{
				//simple addressing

				n = 1,i = 1;
			}
			//add n,i
			res = res + 2*n + i;
			//add x,b,p,e
			res = 16*res+8*x+4*b+2*p+e;
			//add disp
			res = res*16*16*16+disp;
		}
		if(flag == 4){
			ob_flag = 1;
			mem = 4;
			//symbol X str1 = mnemonic, str2 = command, format 4
			e = 1;
			b = 0,p = 0;
			ob = return_opcode(str1);
			if(ob == NULL) return -1;
			res = calc_address(ob,2);
			if(str3[0] == 'X'){
				str2[strlen(str2)-1] = '\0';
			}

			tmp = calc_symbol_loc(str2);
			disp = tmp;
			//program counter relative
			if(str3[0] == 'X'){
				x = 1;
			}
			if(str2[0] == '#'){
				//should not add to memory allocation if immediate addressing
				ob_flag = 0;
				//immediate addressing
					n = 0,i=1;
					if(str2[1] >= '0' && str2[1] <= '9'){
						disp = atoi(str2+1);
					}
			}
			else if(str2[0] == '@'){
				//indirect addressing
				n = 1,i=0;
			}
			else{
				//simple addressing
				n=1,i=1;
			}
			//done calculating n,i
			res = res + 2*n + i;
			res = 16*res+8*x+4*b+2*p+e;
			res = res*16*16*16*16*16+disp;
	
		}
		
	}
	if(flag == 5){
		mem = 1;
		//BYTE
		//str1 = symbol, str2 = BYTE, str3 = X
		//hexa
		res = calc_address(str3+2,2);
	}
	if(flag == 6){
		mem = strlen(str3)-3;
		//BYTE
		//str1 = symbol, str2 = BYTE, str3 = C
		//character
		res = 0;
		for(int k = 2;;k++){
			if(str3[k] == '\'') break;
			res = res*256+str3[k];
		}
	}
	if(flag == 7){
		mem = 2;
		//format2,symbol O
		ob = return_opcode(str2);
		if(ob == NULL) return -1;
		res = calc_address(ob,2);
		res = res*256;
		res = res + 16*(return_mnemonic_number(str3[0]));
		if(str3[1] == ','){
			res = res + return_mnemonic_number(str4[0]);
		}
	}
	if (flag == 8){
		mem = 2;
		//format2, symbol X
		ob = return_opcode(str1);
		if(ob == NULL) return -1;
		res = calc_address(ob,2);
		res = res*256;
		res = res + 16*(return_mnemonic_number(str2[0]));
		if(str2[1] == ','){
			res = res + return_mnemonic_number(str3[0]);
		}

	}
	free(ob);
	add_obnode(res,loc-mem,ob_flag);
	return res;
}
int return_mnemonic_number(char c){
	//return mnemonic number for given register
	if(c == 'A') return 0;
	if(c == 'X') return 1;
	if(c == 'L') return 2;
	if(c == 'B') return 3;
	if(c == 'S') return 4;
	if(c == 'T') return 5;
	if(c == 'F') return 6;
	if(c == 'P') return 8;
}

char* return_opcode(char* str){
	//return the opcode for given mnemonic
	int n = 0;
	int l = strlen(str);
	for(int i=0;i<l;i++){
		n = n + (str[i]-'A');
	}
	n = n%20;
	op_nptr tmp;
	char* sent = (char*)malloc(sizeof(char)*10);
	for(tmp = oproot[n];tmp!= NULL;tmp = tmp->next){
		if(strcmp(tmp->mnemonic,str) == 0){
			strcpy(sent,tmp->opcode);
			return sent;
		}
	}
	printf("INVALID MNEMONIC!!!\n");
	error_type = 1;
	return NULL;

}
int size_opcode(char* str,char* size,char* command){
	//calculate memory of given command
	int l;
	if(strcmp(str,"RESB") == 0){
		return atoi(size);
	}
	else if(strcmp(str,"RESW") == 0){
		return 3*atoi(size);
	}
	else if(strcmp(str,"BYTE") == 0){
		if(size[0] == 'X')
			return 1;
		if(size[0] == 'C'){
			char* pos = strchr(size,'\'');
			l = strlen(pos) - 2;
			return l;
		}
	}	
	int res = 0;
	op_nptr tmp;
	//integer for finding hashcode of input opcode
	int n = 0;
	l = strlen(str);
	for(int i=0;i<l;i++){
		n = n + (str[i]-'A');
	}
	n = n%20;
	for(tmp = oproot[n];tmp!= NULL;tmp = tmp->next){
		if(strcmp(tmp->mnemonic,str) == 0){
			return((tmp->tmp[0])-'0');
		}
	}
	if(strcmp(str,"START") == 0) return 0;
	if(strcmp(str,"END") == 0) return 0;
	if(strcmp(str,"BASE") == 0) return 0;
	if(str[0] == '.') return 0;
	return -1;
}
void print_symbol_table(){
	sn_nptr tmp;
	for(int i=0;i<26;i++){
		if(symbolroot[i]->next == NULL) continue;
		else{
			for(tmp = symbolroot[i]->next;tmp != NULL;tmp = tmp->next){
				printf("       %s\t%04X\n",tmp->symbol,tmp->loc);
			}
		}
	}

	return;
}
//create estab - external symbol table
int loaderpass1(int n, char* progname[], FILE* prog[],int progl[]){
	char* str;
	char* string;
	int check = 0;
	for(int i=0;i<n;i++){
		//for all input programs
		prog[i] = fopen(progname[i],"r");
		if(prog[i] == NULL){
			printf("%s doesn't exist!\n",progname[i]);
			while(i>0) fclose(prog[--i]);
			return 1;
		}
		
		while(!feof(prog[i])){
			str = (char*)malloc(sizeof(char)*280);
			memset(str,0,sizeof(str));
			string = fgets(str,280,prog[i]);
			//read every line of program

			//header line
			if(str[0] == 'H'){
				char name[6];
				memset(name,0,sizeof(name));
				char mem_proglength[12];
				memset(mem_proglength,0,sizeof(mem_proglength));
				sscanf(str,"%s %s",name,mem_proglength);
				//name of program and length of program
				memset(esroot[i]->symbol,0,10*(sizeof(char)));
				strcpy(esroot[i]->symbol,name+1);
				//put into first line of estab list root
				progl[i] = calc_address(mem_proglength+6,6);
				if(i == 0){
					esroot[i]->address = progaddress;
				}
				else{
					esroot[i]->address = esroot[i-1]->address + progl[i-1];
				}
				//save starting address of program
			}
			else if(str[0] == 'D'){
				//memset(tmpstr,0,sizeof(tmpstr));
				for(int j=0;j<strlen(str+1);j=j+12){
					if(strlen(str+1+j)>12){
						check = add_esnode(str+1+j,i);
						//save symbols to estab
						if(check == 1){
							return 1;
						}
					}
				}
			}
			
			free(str);
		}
	}
	
	for(int i=0;i<n;i++){
		fclose(prog[i]);
	}
	return 0;
}
int add_esnode(char* str_in,int n){
	char str[6];
	int addr = calc_address(str_in+6,6);
	memset(str,0,sizeof(str));
	strncpy(str,str_in,6);
	for(int i=0;i<6;i++){
		if(str[i] == ' ') str[i] = '\0';
	}
	es_nptr tmp;
	es_nptr new;
	
	new = (es_nptr)malloc(sizeof(estabnode));
	new->next = NULL;
	strcpy(new->symbol,str);
	//create new node

	for(tmp = esroot[n];tmp ->next != NULL;tmp = tmp->next){}
	//search for current lists's end
	new->address = esroot[n]->address+addr;
	tmp->next = new;
	//add new node that consists of symbol name and address

	return 0;
}
int loaderpass2(int n, char* progname[], FILE* prog[],int progl[]){
	char* str;
	char* string;
	int check = 0;
	for(int i=0;i<n;i++){
		prog[i] = fopen(progname[i],"r");
		//since the program already passed pass1
		//file should exists, so there is no need for
		//checking whether the file exits
		char refcheck[100][8];
		for(int j=0;j<100;j++){
			memset(refcheck[j],0,sizeof(refcheck[j]));
		}
		//table for checking all reference symbols
		strncpy(refcheck[1],esroot[i]->symbol,8);
		while(!feof(prog[i])){
			str = (char*)malloc(sizeof(char)*280);
			memset(str,0,sizeof(str));
			string = fgets(str,280,prog[i]);
			if(str[0] == 'R'){
				for(int j=0;j<strlen(str+1);j = j+8){
					if(strlen(str+1+j)>8){
						check = saver(refcheck,str+1+j,8);
						if(check != 0){
						//if fails to find reference symbol
							while(i>=0){
								fclose(prog[i--]);
							}
							printf("reference symbol doesn't exist!\n");
							return 1;
							//return error code
						}
					}
					if(strlen(str+1+j)<=8){
						int l = strlen(str+1+j);
						check = saver(refcheck,str+1+j,l);
						if(check != 0){
						//if fails to find reference symbol
							while(i>=0){
								fclose(prog[i--]);
							}
							printf("reference symbol doesn't exist!\n");
							return 1;
							//return error code
						}
					}

				}
			}
			else if(str[0] == 'T'){
				//T line
				l_T(str+1,i);
			}
			else if(str[0] == 'M'){
				//M line
				M(str+1,i,refcheck);
			}
			else if(str[0] == 'E'){
				if(str[1] >= '0' && str[1] <= '0') exeaddr = strtol(str+1,NULL,16);
				exeaddr += esroot[i]->address;
			}
		}
		
		
	}
	//if there is no problem till the end, close all programs
	for(int i=0;i<n;i++){
		fclose(prog[i]);
	}
	return 0;
}
int saver(char arr[][8], char* str,int l){
	//save reference table & address
	int index = 0;
	index = (str[0]-'0')*10 + (str[1]-'0');
	strncpy(arr[index],str+2,l-2);
	for(int i=0;i<8;i++){
		if(arr[index][i] == ' ' || arr[index][i] == '\n') arr[index][i] = '\0';
	}
	int checker = 0;
	for(int i=0;i<3;i++){
		es_nptr tmp;
		for(tmp = esroot[i]->next;tmp != NULL;tmp = tmp->next){
			//if there is repitition of symbol name, set error flag
			if(strcmp(tmp->symbol,arr[index]) == 0) checker = 1;
		}
	}
	if(checker == 0) return 1;
	return 0;
}
void l_T(char* str,int n){
	char addstr[6];
	char strl[2];
	int addr;
	strncpy(addstr,str,6);
	strncpy(strl,str+6,2);
	addr = esroot[n]->address + strtol(addstr,NULL,16);
	//set starting point address
	int l = strtol(strl,NULL,16);
	//l = length of str in hex
	for(int i=0;i<l;i++){
		char strtmp[2];
		strncpy(strtmp,str+8+(2*i),2);
		int tmp = strtol(strtmp,NULL,16);
		table[((addr+i)/16)][(addr+i)%16] = tmp;
		//upload the line read to memory
	}	
	return;
}
int findestab(int n, int num, char arr[][8]){
	int res = 0;
	char str[6];
	memset(str,0,sizeof(str));
	strncpy(str,arr[num],sizeof(arr[num]));

	//num = index 01~05
	for(int i=0;i<3;i++){
		es_nptr tmp;
		for(tmp = esroot[i];tmp!= NULL;tmp = tmp->next){
			if(strcmp(tmp->symbol,str) == 0) res = tmp->address;
		}
	}
	//return needed address
	return res;
}
void M(char* str, int n, char arr[][8]){
	//memory relocation
	char addstr[6];
	char numstr[2];
	int addr;
	strncpy(addstr,str,6);
	//relocated memory address
	strncpy(numstr,str+9,2);
	//external symbol number
	addr = esroot[n]->address + strtol(addstr,NULL,16);
	int num = strtol(numstr,NULL,16);
	int res = findestab(n,num,arr);
	int tmp[3];
	tmp[2] = res%(1<<8);
	//memory (m.2)
	tmp[1] = (res/(1<<8))%(1<<8);
	//memory (m.1)
	tmp[0] = res/(1<<16);
	//memory (m)
	int carry = 0;
	int k;
	if(str[8] == '+'){
		k = table[(addr+2)/16][(addr+2)%16];
		//add m.2
		if(k<0) k = k + 256;
		if(k + tmp[2] >= 256){
			table[(addr+2)/16][(addr+2)%16] = k + tmp[2] - 256;
			carry = 1;
		}
		else table[(addr+2)/16][(addr+2)%16] = k + tmp[2];
		
		//add m.1
		k = table[(addr+1)/16][(addr+1)%16];
		if(k<0) k = k + 256;
		//if carry
		if(k + tmp[1] + carry >= 256){
			table[(addr+1)/16][(addr+1)%16] = k + tmp[1] + carry - 256;
			carry = 1;
		}
		//if !carry
		else {
			table[(addr+1)/16][(addr+1)%16] = k + tmp[1] + carry;
			carry = 0;
		}
		
		//add m
		k = table[addr/16][addr%16];
		if(k<0) k = k + 256;
		k = k + tmp[0] + carry;

		if(k >= 256){
			table[addr/16][addr%16] = k - 256;
		}
			
	}
	
	if(str[8] == '-'){
		k = table[(addr+2)/16][(addr+2)%16];
		if(k<0) k = k + 256;
		//sub m.2
		//if carry
		if(k - tmp[2] < 0){
			table[(addr+2)/16][(addr+2)%16] = k - tmp[2] + 256;
			carry = 1;
		}
		//if !carry
		else table[(addr+2)/16][(addr+2)%16] = k - tmp[2];
		
		k = table[(addr+1)/16][(addr+1)%16];
		if(k<0) k = k + 256;
		//sub m.1
		//if carry
		if(k + tmp[1] + carry < 0){
			table[(addr+1)/16][(addr+1)%16] = k - tmp[1] - carry + 256;
			carry = 1;
		}
		//if !carry
		else {
			table[(addr+1)/16][(addr+1)%16] = k - tmp[1] - carry;
			carry = 0;
		}

		k = table[addr/16][addr%16];
		if(k<0) k = k + 256;
		//sub m
		k = k - tmp[0] - carry;

		if(k >= 256){
			table[addr/16][addr%16] = k - 256;
		}
			
	}

	
	return;
}
void run(){
	int PC;
	reg[8] = exeaddr;
	unsigned char t;
	for(reg[8] = exeaddr;;){
		PC = reg[8];
		int format;
		t = table[PC/16][PC%16];
		//read first two bytes of memory
		switch(t/16){
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 13:
			case 14:
				format = 3;
				//basically 3
				if(((table[(PC+1)/16][(PC+1)%16]/16) % 2) == 1) format = 4;
				//if e bit is set on next byte
				break;
			case 9:
			case 10:
			case 11:
				//basically 2
				format = 2;
				break;
			case 12:
			case 15:
				//basically 1
				format = 1;
				break;
			default:
				break;
		}
		int opc = (unsigned char)table[PC/16][PC%16];
		//opc is the mnemonic (opcode) for memory read
		switch(format){
			case 1:
				format1(opc);
				reg[8] = reg[8] + 1;
				//add program counter
				break;
			case 2:
				format2(opc);
				reg[8] = reg[8] + 2;
				//add program counter
				break;
			case 3:
				format34(opc,3);
				break;
			case 4:
				format34(opc,4);
				break;
		}

		if(bp[reg[8]]){
			//if breakpoint is met
			printf("A : %06X  X : %06X\n",reg[0],reg[1]);
			printf("L : %06X PC : %06X\n",reg[2],reg[8]);
			printf("B : %06X  S : %06X\n",reg[3],reg[4]);
			printf("T : %06X\n",reg[5]);
			printf("            Stop at checkpoint [%X]\n",reg[8]);
			exeaddr = reg[8];

			return;
		}

		if(reg[8] >= lastlen){
			//if end of program
			printf("A : %06X  X : %06X\n",reg[0],reg[1]);
			printf("L : %06X PC : %06X\n",reg[2],reg[8]);
			printf("B : %06X  S : %06X\n",reg[3],reg[4]);
			printf("T : %06X\n",reg[5]);
			printf("            End Program\n");
			exeaddr = reg[8];
			return;
		}

	}
}
void format1(int code){
//no format 1 for copy.obj!

}
void format2(int code){
	//= 0
	//> 1
	//< 2
	int r1,r2;
	unsigned char t;
	unsigned char t1,t2;
	t = table[(reg[8]+1)/16][(reg[8]+1)%16];
	//next byte on memory
	switch(code){
		case 0xB4:
			//CLEAR
			//clear memory
			r1 = t/16;
			reg[r1] = 0;
			break;
		case 0xA0:
			//COMPR
			//compare two registers, and save the result on SW register (reg[9])
			r1 = t/16;
			r2 = t%16;
			if(table[reg[r1]/16][reg[r1]%16] == table[reg[r2]/16][reg[r2]%16]) reg[9] = 0;
			if((unsigned char)table[reg[r1]/16][reg[r1]%16] > (unsigned char)table[reg[r2]/16][reg[r2]%16]) reg[9] = 1;
			if((unsigned char)table[reg[r1]/16][reg[r1]%16] < (unsigned char)table[reg[r2]/16][reg[r2]%16]) reg[9] = 2;
			break;
		case 0xB8:
			//TIXR
			//increase X, compare with given register with X, and save result
			//on SW register (reg[9])
			reg[1]++;
			r1 = reg[1];
			r2 = reg[t/16];
			if(table[r1/16][r1%16] == table[r2/16][r2%16]) reg[9] = 0;
			if((unsigned char)table[r1/16][r1%16] > (unsigned char)table[r2/16][r2%16]) reg[9] = 1;
			if((unsigned char)table[r1/16][r1%16] < (unsigned char)table[r2/16][r2%16]) reg[9] = 2;
			break;
	}
}
void format34(int code,int f){
	int nextpc = reg[8]+f;
	int n,i,x,b,p,e;
	i = code%2;
	n = (code/2)%2;
	unsigned char t1;
	unsigned char t2;
	unsigned char t3;
	t1 = table[(reg[8]+1)/16][(reg[8]+1)%16];
	t2 = table[(reg[8]+2)/16][(reg[8]+2)%16];
	t3 = table[(reg[8]+3)/16][(reg[8]+3)%16];
	//next byte on memory
	e = (t1/16)%2;
	p = (t1/32)%2;
	b = (t1/64)%2;
	x = (t1/128)%2;
	//tb = address
	//ta = data in address
	int ta, tb;
	if(f == 3)
		ta = ((t1%16)<<8) + t2;
	if(f == 4)
		ta = ((((t1%16)<<8)+t2)<<8)+t3;
	
	
	if(b == 1){
		//if program is base relative
		ta = ta + reg[3];
	}
	if(p == 1){
		//if program is pc relative
		if(ta >= 2048)
			ta = ta - 4096;
		ta += nextpc;
	}

	if(x == 1){
		//if program refers to x register
		ta = ta + reg[1];
	}
	code = code/4;
	code = code*4;
	//find opcode
	unsigned char d1;
	unsigned char d2;
	unsigned char d3;
	d1 = (unsigned char)table[(ta)/16][(ta)%16];
	d2 = (unsigned char)table[(ta+1)/16][(ta+1)%16];
	d3 = (unsigned char)table[(ta+2)/16][(ta+2)%16];
	int sum = (d1<<16)+(d2<<8)+d3;
	if(n == 0 && i == 1){//immediate addressing
		tb = ta;
	}
	if(n == 1 && i == 0){//indirect addressing
		tb = sum;
		d1 = (unsigned char)table[(tb)/16][(tb)%16];
		d2 = (unsigned char)table[(tb+1)/16][(tb+1)%16];
		d3 = (unsigned char)table[(tb+2)/16][(tb+2)%16];
		ta = (d1<<16)+(d2<<8)+d3;
		//for indirect addressing, first ta becomes address(tb)
		//and ta should change into data saved to tb, tb.1, tb.2
	}
	if(n == 1 && i == 1){//simple addressing
		tb = ta;
		ta = sum;
	}

	switch(code){
		case 0x14:
			//STL
			//store L-register data to memory
			store(2,tb);
			break;
		case 0x68:
			//LDB
			//load memory data to B-register
			reg[3] = ta;
			break;
		case 0x48:
			//JSUB
			//jump to memory saved in L-register
			reg[2] = nextpc;
			nextpc = tb;
			break;
		case 0x00:
			//LDA
			//load memory data to A-register
			reg[0] = ta;
			break;
		case 0x28:
			//COMP
			//compare data and save the result to SW register (reg[9])
			if(reg[0] == ta) reg[9] = 0;
			if(reg[0] > ta) reg[9] = 1;
			if(reg[0] < ta) reg[9] = 2;
			break;
		case 0x30:
			//JEQ
			//jump if equal
			if(reg[9] == 0) nextpc = tb;
			break;
		case 0x3C:
			//J
			//jump to memory
			nextpc = tb;

			break;
		case 0x0C:
			//STA
			//store data in A register in memory
			store(0,tb);
			break;
		case 0x74:
			//LDT
			//load data to T-register
			reg[5] = ta;
			break;
		case 0xE0:
			//TD
			//change SW register to '<'
			reg[9] = 2;
			break;
		case 0xD8:
			//RD
			//set memory so that register A and S are the same
			reg[0] = 0;
			break;
		case 0x54:
			//STCH
			//store character
			table[tb/16][tb%16] = reg[0]%(1<<8);
			break;
		case 0x38:
			//JLT
			//jump if larger than
			if(reg[9] == 2) nextpc = tb;
			break;
		case 0x10:
			//STX
			//store memory from X-register
			store(1,tb);
			break;
		case 0x4C:
			//RSUB
			//return to subroutine
			nextpc = reg[2];
			break;
		case 0x50:
			//LDCH
			//load character
			reg[0] = ((reg[0]>>8)<<8);
			reg[0] += (ta/(1<<16));
			break;
		case 0xDC:
			//WD
			//do nothing
			break;
		
	}
	reg[8] = nextpc;
}
void store(int r,int ta){
	//store data from register to memory
	table[ta/16][ta%16] = (reg[r]/(1<<16))%(1<<8);
	table[(ta+1)/16][(ta+1)%16] = (reg[r]/(1<<8))%(1<<8);
	table[(ta+2)/16][(ta+2)%16] = reg[r]%(1<<8);
}
