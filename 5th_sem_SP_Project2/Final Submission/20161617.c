#include "20161617.h"

char input_order[80];//input order
char part_order[80];//part of the input_order


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

op_nptr oproot[20];
//linked list for opcode
sn_nptr symbolroot[26];
//linked list for symbol table
ob_nptr obroot[3];
//linked list for object code
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
/* * * * * * * 
   1 = invalid mnemonic
   2 = invalid opcode

   * * * * * */


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
void add_obnode(long long int, int,int);
long long int calc_opcode(int,int,char*,char*,char*,char*);
int return_mnemonic_number(char);
char* return_opcode(char*);
int size_opcode(char*,char*,char*);
void print_symbol_table();




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
