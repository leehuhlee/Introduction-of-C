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
Hash* hash_buckets[BUCKET_SIZE];//hash_buckets for hash
Hash_symbol* symbol_buckets[26];//make symbol_table as hash table
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
#endif//prevent overlap header file
