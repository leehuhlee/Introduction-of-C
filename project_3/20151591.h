#ifndef __P1__H__//prevent overlap header file
#define __P1__H__//prevent overlap header file
#define INPUT_LIMIT 100//Input's limit size
#define INPUT_SIZE 20//Tempotary input's size
#define BUCKET_SIZE 20//bucket's size
#define LINE_SIZE 100//assem's line size
#define ALPHABET_SIZE 26;//the counts of alphabet
typedef struct _History{
	int num;//The count of inputing mnemonic
	struct _History* next;//Pointer for next node
	struct _History* prev;//Pointer for previous node
	char mnemonic[INPUT_LIMIT];
}History;//This struct for saving the history of inputing mnemonic
typedef struct _Hash{
	int opcode;//This for saving opcode
	char mnemonic[INPUT_SIZE];//This for saving mnemonic
	char format[INPUT_SIZE];//This for saving mnemonic's format
	struct _Hash* next;//Pointer for next node
	struct _Hash* prev;//Pointer for previous node
}Hash;//This struct for saving the hash
typedef struct __Hash{
	char symbol[10];
	int loc;
	struct __Hash* next;
	struct __Hash* prev;
}Hash_symbol;
typedef struct __Ex_Hash{
	char symbol[10];
	int addr;
	int state;
	struct __Ex_Hash* next;
	struct __Ex_Hash* prev;
}Ex_Hash_symbol;
typedef struct __Print_Ex_Hash{
	char symbol[10];
	int addr;
	struct __Print_Ex_Hash* next;
	struct __Print_Ex_Hash* prev;
}Print_Ex_Hash_symbol;
typedef struct __array{
	int addr;
	char symbol[10];
}R_array;
Hash* hash_buckets[BUCKET_SIZE];//hash_buckets for hash
Hash_symbol* symbol_buckets[26];//make symbol_table as hash table
Ex_Hash_symbol* ex_symbol_buckets[26];//make extended symbol_table as hash table
Print_Ex_Hash_symbol* print_ex_symbol_buckets[3];//index 0 is for print symbol in first program , index 1 is for print symbol in second program , index 2 is for print symbol third program
int S_loc;//start location for run
int E_loc;//end location for run
int A_reg;//A register
int X_reg;//X register
int L_reg;//L register
int PC_reg;//PC register
int B_reg;//B register
int S_reg;//S register
int T_reg;//T register
int flag;//SW register
int bp[1000];//array for saving break points
int bp_index;//index for bp index
int run_first;//run the program at start location
int progaddr;//save the progaddr
/************************************************************
 *Input_change_function                                     *
 *Changing original input to formal input                   *
 *Input : (1) char* Input : original input                  *
 *(2) char* Input_change : memory for saving changed input  *
 *Output : None												*	
*************************************************************/
void Input_change_function(char* Input,char* Input_change);
/************************************************************
 *History_made                                              *
 *Making linked list of history				                *
 *Input : (1) History** head : pointer for linked's head	*
 *(2) int* index : the count of inputing mnemonic           *
 *(3) char* Input : original input                          *
 *Output : None												*	
 ************************************************************/
void History_made(History** head,int* index,char* Input);
/************************************************************
 *History_free                                              *
 *Free the linked list of history                           *
 *Input : History** head : pointer for linked's head        *
 *Output : None												*	
 ************************************************************/
void History_free(History** head);
/************************************************************
 *Help_print                                                *
 *Print the mnemonics                                       *
 *Input : None                                              *
 *Output : None												*	
 ************************************************************/
void Help_print();
/************************************************************
 *Dir_print                                                 *
 *Print the list of current directory's directorys and files*
 *Input : DIR** dir_info : pointer for current director     *
 *Output : None												*	
 ************************************************************/
void Dir_print(DIR** dir_info);
/************************************************************
 *Dump_print1                                               *
 *Print the ten lines of memory from index of last print    *
 *Input : (1) unsigned char** Memory : the array of memory  *
 *(2) int start_ : the end index of printed memory          *
 *Output : int end : the end index of printed memory        *	
 ************************************************************/
int Dump_print1(unsigned char** Memory , int start_);
/************************************************************
 *Dump_print2                                               *
 *Print the ten lines of memory from index of inputing start*
 *Input : (1) char* Input_change : the formal input         *
 *(2) unsigned char** Memory : the array of memory          *
 *Output : int end : the end index of printed last memory   *
 ************************************************************/
int Dump_print2(char* Input_change,unsigned char** Memory);
/*****************************************************************
 *Dump_print3                                                    *
 *Print the memory from inputed start index to end index         *
 *Input : (1) char* Input_change : the formal input              *
 *(2)unsigned char** Memory : the array of memory                *
 *Output : int  end : the end index of printed last memory       *
 *****************************************************************/
int Dump_print3(char* Input_change,unsigned char** Memory);
/************************************************************
 *Determine_mnemonic                                        *
 *Decide Input                                              *
 *Input : char* Input_change : the formal input             *
 *Output : int Case : Case is standard of input             *
 ************************************************************/
int Determine_mnemonic(char* Input_change);
/************************************************************
 *Fill_function                                             *
 *Set the value of memory from start index to end index     *
 *Input : (1) unsigned char** Memory : pointer for memory   *
 *(2) char* Input_change : the formal input                 *
 *Output : None                                             *
 ************************************************************/
void Fill_function(unsigned char** Memory , char* Input_change);
/************************************************************
 *Edit_function                                             *
 *Set the value of memory at target index                   *
 *Input : (1) unsigned char** Memory : pointer for memory   *
 *(2) char* Input_change : the formal input                 *
 *Output : None                                             *
 ************************************************************/
void Edit_function(unsigned char** Memory , char* Input_change);
/************************************************************
 *Input_opctext                                             *
 *Get the data from opcode.txt                              *
 *Input : (1) int* opcode : the array space for opcode      *
 *(2) char** mnemonic : the array space for mnemonic        *
 *(3) char** format : the array space for format            *
 *Output : int value : tell about the success of fuction    *
 ************************************************************/
int Input_opctext(int* opcode,char** mnemonic,char** format);
/************************************************************
 *free_Input_opctext                                        *
 *free the array of mnemonics                               *
 *Input : (1) int* opcode : the array space for opcode      *
 *(2) char** mnemonic : the array space for mnemonic        *
 *(3) char** format : the array space for format            *
 *Output : None                                             *
 ************************************************************/
void free_Input_opctext(int* opcode,char** mnemonic,char** format);
/************************************************************
 *Make_hash_table_function                                  *
 *Make the hash table for mnemonics                         *
 *Input : (1) Hash** hash_buckets : the bucket for hash     *
 *(2) int* opcode : the array space for opcode              *
 *(3) char** mnemonic : the array space for mnemonic        *
 *(4) char** format : the array space for format            *
 *Output : None                                             *
 ************************************************************/
void Make_hash_table_function(Hash** hash_buckets,int* opcode,char** mnemonic,char** format);
/************************************************************
 *Hash_function                                             *
 *Hash fuction for getting index                            *
 *Input :  char** material  : the mnemonic                  *
 *Output : int sum : index for hash                         *
 ************************************************************/
int Hash_function(char* material);
/************************************************************
 *Opcodelist_print                                          *
 *Print the opcodelist along the format of hash             *
 *Input :  Hash** hash_buckets : the bucket for hash        *
 *Output : None                                             *
 ************************************************************/
void Opcodelist_print(Hash** hash_buckets);
/************************************************************
 *Opcode_print                                              *
 *Search and print the opcode along the format              *
 *Input : (1) char* Input_change : the formal input         *
 *(2) Hash** hash_buckets : the bucket for hash format      *
 *Output : None                                             *
 ************************************************************/
void Opcode_print(char* Input_change,Hash** hash_buckets);
/***********************************************************
 *type_print                                               *
 *print the contents of file                               *
 *Input : char* Input_change: the formal input             *
 *Output : None                                            *
 **********************************************************/
void type_print(char* Input_change);
/*************************************************************
 *Symbol_table_make                                          *
 *Make the symbol table                                      *
 *Input : char* symbol : symbol , int loc : symbol's location*
 *Output : -1 : wrong format , 0 : same symbol already appear*
 *1 : success about making symbol                            *
 *************************************************************/
int Symbol_table_make(char* Symbol,int loc);
/*************************************************************
 *Free_symbol_table                                          *
 *free the symbol table                                      *
 *Input : Nothing                                            *
 *Output : Nothing                                           *
 *************************************************************/
void Free_symbol_table();
/*************************************************************
 *Differentiate                                              *
 *Determine the kind of input at paas 1                      *
 *Input : char* Target : input's small partition             *
 *Output : -4 : NULL , -3 : symbol is Directive or mnemonic  *
 *-2 : already symbol , -1 : wrong format symbol             *
 *0 : symbol , 1 : FORMAT1 , 2 : FORMAT2 , 3 : FORMAT3       *
 *4 : FORMAT4 , 5 : START , 6 : END , BYTE : 7 , RESB : 8    *
 *9 : WORD , 10 : RESW , 11 : BASE                           *
 *************************************************************/
int Differentiate(char* Target);
/*************************************************************
 *Is_decimal                                                 *
 *Determine whether parameter is decimal number              *
 *Input : char* Target : input's small partition             *
 *Output : 0 : it is not decimal number                      *
 *1 : it is decimal number                                   *
 *************************************************************/
int Is_decimal(char* Target);
/*************************************************************
 *Is_hexa                                                    *
 *Determine whether parameter is hexa number                 *
 *Input : char* Target : input's small partition             *
 *Output : 0 : it is not hexa number                         *
 *1 : it is hexa number                                      *
 *************************************************************/
int Is_hexa(char* Target);
/*************************************************************
 *Is_register                                                *
 *Determine whether parameter is register                    *
 *Input : char* Target : input's small partition             *
 *Output : 0 : it is not register                            *
 *1 : it is register                                         *
 *************************************************************/
int Is_register(char* Target);
/*************************************************************
 *Is_mn_or_di                                                *
 *Determine whether parameter is mnemonic or directive       *
 *Input : char* Target : input's small partition             *
 *Output : 0 : it is not mnemonic and directive              *
 *1 : it is mnemonic or directive                            *
 *************************************************************/
int Is_mn_or_di(char* Target);
/*************************************************************
 *Check_already_symbol                                       *
 *Determine whether parameter is symbol that already appears *
 *Input : char* Target : input's small partition             *
 *Output : 0 : it is not already symbol                      *
 *1 : it is already symbol                                   *
 *************************************************************/
int Check_already_symbol(char* Target);
/*************************************************************
 *Loc_from_symbol                                            *
 *Get the location about symbol                              *
 *Input : char* Target : input's small partition             *
 *Output : -1 : it is not already symbol                     *
 * symbol_buckets[index]->loc : the location of symbol       *
 *************************************************************/
int Loc_from_symbol(char* Target);
/************************************************************************************
 *Check_FORM1                                                                       *
 *Check whether assem line is along with right FORMAT1                              *
 *Input : char* Input_1 ~~ char* Input_3 : small partition of input                 *
 *Output : 0 : it is not right                                                      *
 *1 : it is right                                                                   *
 ************************************************************************************/
int Check_FORM1(char* Input_1,char* Input_2,char* Input_3);
/*************************************************************************************************************
 *Check_FORM2																								 *
 *Check whether assem line is along with right FORMAT2														 *
 *Input : char* Input_1 ~~ char* Input_5 : small partition of input , int coma_count : the number of ','input*
 *Output : 0 : it is not right																				 *
 *1 : it is right																					         *
 *************************************************************************************************************/
int Check_FORM2(char* Input_1,char* Input_2,char* Input_3,char* Input_4,char* Input_5,int coma_count);
/************************************************************************************
 *Check_FORM3                                                                       *
 *Check whether assem line is along with right FORMAT3                              *
 *Input : char* Input_1 ~~ char* Input_5 : small partition of input                 *
 *Output : 0 : it is not right                                                      *
 *1 : it is right                                                                   *
 ************************************************************************************/
int Check_FORM3(char* Input_1,char* Input_2,char* Input_3,char* Input_4,char* Input_5);
/************************************************************************************
 *Check_FORM4                                                                       *
 *Check whether assem line is along with right FORMAT4                              *
 *Input : char* Input_1 ~~ char* Input_5 : small partition of input                 *
 *Output : 0 : it is not right                                                      *
 *1 : it is right                                                                   *
 ************************************************************************************/
int Check_FORM4(char* Input_1,char* Input_2,char* Input_3,char* Input_4,char* Input_5);
/************************************************************************************
 *Check_START5                                                                      *
 *Check whether assem line is along with right START DIRECTIVE format               *
 *Input : char* Input_1 ~~ char* Input_4 : small partition of input                 *
 *Output : 0 : it is not right                                                      *
 *1 : it is right                                                                   *
 ************************************************************************************/
int Check_START5(char* Input_1,char* Input_2,char* Input_3,char* Input_4);
/************************************************************************************
 *Check_END6                                                                        *
 *Check whether assem line is along with right END DIRECTIVE format                 *
 *Input : char* Input_1 ~~ char* Input_4 : small partition of input                 *
 *Output : 0 : it is not right                                                      *
 *1 : it is right                                                                   *
 ************************************************************************************/
int Check_END6(char* Input_1,char* Input_2,char* Input_3,char* Input_4,char* first_symbol);
/************************************************************************************
 *Check_RESB8                                                                       *
 *Check whether assem line is along with right RESB format                          *
 *Input : char* Input_1 ~~ char* Input_4 : small partition of input                 *
 *Output : 0 : it is not right                                                      *
 *1 : it is right                                                                   *
 ************************************************************************************/
int Check_RESB8(char* Input_1,char* Input_2,char* Input_3,char* Input_4);
/************************************************************************************
 *Check_WORD9                                                                       *
 *Check whether assem line is along with right WORD format                          *
 *Input : char* Input_1 ~~ char* Input_4 : small partition of input                 *
 *Output : 0 : it is not right                                                      *
 *1 : it is right                                                                   *
 ************************************************************************************/
int Check_WORD9(char* Input_1,char* Input_2,char* Input_3,char* Input_4);
/************************************************************************************
 *Check_RESW10                                                                      *
 *Check whether assem line is along with right RESW format                          *
 *Input : char* Input_1 ~~ char* Input_4 : the small partition of input             *
 *Output : 0 : it is not right                                                      *
 *1 : it is right                                                                   *
 ************************************************************************************/
int Check_RESW10(char* Input_1,char* Input_2,char* Input_3,char* Input_4);
/*************************************************************************************************************************
 *Check_BASE11																											 *
 *Check whether assem line is along with right BASE format																 *
 *Input : char* Input_1 ~~ char* Input_3 : small partition of input , LDB_symbol : LDB mnemonic's operand                *
 *Output : 0 : it is not right																							 *
 *1 : it is right																										 *
 *************************************************************************************************************************/
void Make_listfile_syboltable_checkerror(char* Input_change);
/*************************************************************
 *Print_Symbol                                               *
 *Print the symbol table                                     *
 *Input : Nothing                                            *
 *Output : Nothing                                           *
 *************************************************************/
void Print_Symbol();
/****************************************************************
 *Two_s_complement_result                                       *
 *Doing two's comlement substraction                            *
 *Input : int TA : first operand , int Pc_loc : second operand  *
 *Output : the result of two' comlement substraction            *
 ****************************************************************/
unsigned int Two_s_complement_result(int TA,int Pc_loc);
/*************************************************************
 *Opcode_get                                                 *
 *Get Opcode about mnemonic                                  *
 *Input : char* Target : the small partition of input        *
 *Output : -1 : input is not mnemonic                        *
 *temp->opcode : mnemonic's opcode                           *
 *************************************************************/
int Opcode_get(char* Target);
/*************************************************************
 *Opcode_get                                                 *
 *Get Opcode about mnemonic                                  *
 *Input : char* Target : the small partition of input        *
 *Output : the register number                               *
 *************************************************************/
int Register_num_get(char* Target);
/*************************************************************
 *Differentiate_2                                            *
 *Determine the kind of input at paas 2                      *
 *Input : char* Target : input's small partition             *
 *Output : -4 : NULL , -3 : symbol is Directive or mnemonic  *
 *-2 : already symbol , -1 : wrong format symbol             *
 *0 : symbol , 1 : FORMAT1 , 2 : FORMAT2 , 3 : FORMAT3       *
 *4 : FORMAT4 , 5 : START , 6 : END , BYTE : 7 , RESB : 8    *
 *9 : WORD , 10 : RESW , 11 : BASE                           *
 *************************************************************/
int Differentiate_2(char* Target);
/*************************************************************
 *Set_progaddr                                               *
 *setting the program start location                         *
 *Input : char* Input_change : formal input                  *
 *Output : Nothing                                           *
 *************************************************************/
void Set_progaddr(char* Input_change);
/*************************************************************
 *Loader_function                                            *
 *Link and Load the object files                             *
 *Input : char* Input_change : formal input                  *
 *unsigned char** Memory : Memory                            *
 *Output : Nothing                                           *
 *************************************************************/
void Loader_function(char* Input_change,unsigned char** Memory);
/*************************************************************
 *Check_double_symbol                                        *
 *check double symbol in external symbol table               *
 *Input : char* symbol : external symbol                     *
 *int addr : symbol's address                                *
 *Output : 1 : there is already same symbol                  *
 * 0 : there is not already same symbol                      *
 *************************************************************/
int Check_double_symbol(char* symbol,int addr);
/*************************************************************
 *Make_ex_symbol_table                                       *
 *insert the external symbol node to symbol table            *
 *Input : char* symbol : external symbol                     *
 *int addr : symbol's address                                *
 *int state : show external symbol where                     *
 *Output : 1 : success                                       *
 * 0 : fail                                                  *
 **************************************************************/
int Make_ex_symbol_table(char* symbol,int addr,int state);
/*************************************************************
 *Free_ex_symbol_table                                       *
 *Free the external symbol table                             *
 *Input : Nothing                                            *
 *Output : Nothing                                           *
 **************************************************************/
void Free_ex_symbol_table();
/*************************************************************
 *Make_print_ex_symbol_table                                 *
 *make linked lis for printing the load map                  *
 *Input : char* symbol : external symbol                     *
 *int addr : symbol's address                                *
 *int state : show external symbol where                     *
 *Output : 1 : success                                       *
 * 0 : fail                                                  *
 **************************************************************/
int Make_print_ex_symbol_table(char* symbol,int addr,int state);
/*************************************************************
 *Print_Ex_Symbol                                            *
 *print the load map                                         *
 *Input : char* prog_name_1 : first object filename          *
 *char* prog_name_2 : second object filename                 *
 *char* prog_name_3 : third object filename                  *
 *int start1 : first object file's start location            *
 *int start2 : second object file's start location           *
 *int start3 : third object file's start location            *
 *int length1 : first object file's length                   *
 *int length2 : second object file's length                  *
 *int length3 : third object file's length                   *
 * int count_program : the number of program                 *
 *Output : nothing                                           *
 **************************************************************/
void Print_Ex_Symbol(char* prog_name_1,char* prog_name_2,char* prog_name_3,int start1,int start2,int start3,int length1,int length2,int length3,int count_program);
/*************************************************************
 *Get_addr_from_ex_symbol_table                              *
 *get address from external symbol table                     *
 *Input : char* R_symbol : R record's external symbol        *
 *Output : address                                           *
 * -1 : fail                                                 *
 **************************************************************/
int Get_addr_from_ex_symbol_table(char* R_symbol);
/*************************************************************
 *Bp_print                                                   *
 *print the break points                                     *
 *Input : nothing                                            *
 *Output : nothing                                           *
 **************************************************************/
void Bp_print();
/*************************************************************
 *Bp_clear                                                   *
 *clear the array about break points                         *
 *Input : nothing                                            *
 *Output : nothing                                           *
 **************************************************************/
void Bp_clear();
/*************************************************************
 *Bp_set                                                     *
 *set the break points                                       *
 *Input : char* Input_change : formal input                  *
 *Output : nothing                                           *
 **************************************************************/
void Bp_set(char* Input_change);
/*************************************************************
 *what_xbp                                                   *
 *search the x,b,p bit and decide addressing mode            *
 *Input : unsigned char** Memory : memory                    *
 *Output : 2 : PC relative                                   *
 * 0 : direct addressing                                     *
 * 4 : Base relative                                         *
 * 8 : direct addressing and x indexed                       *
 * 10 : PC relative and x indexed                            *
 * 12 : Base relative and x indexed                          *
 * -1 : not FORMAT3                                          *
 **************************************************************/
int what_xbp(unsigned char** Memory);
/*************************************************************
 *If_breakpoint                                              *
 *decide whether PC is break point                           *
 *Input : int PC_reg : program counter                       *
 *Output : break point                                       *
 * -1 : not break point                                      *
 **************************************************************/
int If_breakpoint(int PC_reg);
/*************************************************************
 *Run                                                        *
 *run the program                                            *
 *Input : unsigned char** Memory : memory                    *
 *Output : nothing                                           *
 **************************************************************/
void Run(unsigned char** Memory);
/*************************************************************
 *what_ni                                                    *
 *search n,i bit and decide addressing mode                  *
 *Input : unsigned char** Memory : memory                    *
 *Output : 0 : SIC 1 : immediate addressing                  *
 * 2 : indirect addressing 3 : simple addressing             *
 **************************************************************/
int what_ni(unsigned char** Memory);
/*************************************************************
 *STL                                                        *
 *deal with STL                                              *
 *Input : unsigned char** Memory : memory                    *
 *Output : nothing                                           *
 **************************************************************/
void STL(unsigned char** Memory);
/*************************************************************
 *STA                                                        *
 *deal with STA                                              *
 *Input : unsigned char** Memory : memory                    *
 *Output : nothing                                           *
 **************************************************************/
void STA(unsigned char** Memory);
/*************************************************************
 *STX                                                        *
 *deal with STX                                              *
 *Input : unsigned char** Memory : memory                    *
 *Output : nothing                                           *
 **************************************************************/
void STX(unsigned char** Memory);
/*************************************************************
 *LDA                                                        *
 *deal with LDA                                              *
 *Input : unsigned char** Memory : memory                    *
 *Output : nothing                                           *
 **************************************************************/
void LDA(unsigned char** Memory);
/*************************************************************
 *LDB                                                        *
 *deal with LDB                                              *
 *Input : unsigned char** Memory : memory                    *
 *Output : nothing                                           *
 **************************************************************/
void LDB(unsigned char** Memory);
/*************************************************************
 *LDT                                                        *
 *deal with LDT                                              *
 *Input : unsigned char** Memory : memory                    *
 *Output : nothing                                           *
 **************************************************************/
void LDT(unsigned char** Memory);
/*************************************************************
 *LDCH                                                       *
 *deal with LDCH                                             *
 *Input : unsigned char** Memory : memory                    *
 *Output : nothing                                           *
 **************************************************************/
void LDCH(unsigned char** Memory);
/*************************************************************
 *STCH                                                       *
 *deal with STCH                                             *
 *Input : unsigned char** Memory : memory                    *
 *Output : nothing                                           *
 **************************************************************/
void STCH(unsigned char** Memory);
/*************************************************************
 *TIXR                                                       *
 *deal with TIXR                                             *
 *Input : unsigned char** Memory : memory                    *
 *Output : 1 : x+1 is bigger                                 *
 * 0 : x+1 is same                                           *
 * -1 : x+1 is small                                         *
 **************************************************************/
int TIXR(unsigned char** Memory);
/*************************************************************
 *COMP                                                       *
 *deal with COMP                                             *
 *Input : unsigned char** Memory : memory                    *
 *Output : 1 : A is bigger                                   *
 * 0 : A is same                                             *
 * -1 : A is small                                           *
 **************************************************************/
int COMP(unsigned char** Memory);
/*************************************************************
 *COMPR                                                      *
 *deal with COMPR                                            *
 *Input : unsigned char** Memory : memory                    *
 *Output : 1 : left operand is bigger                        *
 * 0 : result is same                                        *
 * -1 : left operand is small                                *
 **************************************************************/
int COMPR(unsigned char** Memory);
/*************************************************************
 *JEQ                                                        *
 *deal with JEQ                                              *
 *Input : unsigned char** Memory : memory                    *
 *Output : nothing                                           *
 **************************************************************/
void JEQ(unsigned char** Memory);
/*************************************************************
 *Get_regiter_data                                           *
 *Get the value of operand register                          *
 *Input : unsigned char** Memory : memory                    *
 *Output : register's data                                   *
 **************************************************************/
int Get_regiter_data(int num);
/*************************************************************
 *JLT                                                        *
 *deal with JLT                                              *
 *Input : unsigned char** Memory : memory                    *
 *Output : nothing                                           *
 **************************************************************/
void JLT(unsigned char** Memory);
/*************************************************************
 *J                                                          *
 *deal with J                                                *
 *Input : unsigned char** Memory : memory                    *
 *Output : nothing                                           *
 **************************************************************/
void J_(unsigned char** Memory);
/*************************************************************
 *JSUB                                                       *
 *deal with JSUB                                             *
 *Input : unsigned char** Memory : memory                    *
 *Output : nothing                                           *
 **************************************************************/
void JSUB(unsigned char** Memory);
/*************************************************************
*Run                                                        *
*practice run input                                         *
*Input : unsigned char** Memory : memory                    *
*Output : nothing                                           *
**************************************************************/
void Run(unsigned char** Memory);
#endif//prevent overlap header file
