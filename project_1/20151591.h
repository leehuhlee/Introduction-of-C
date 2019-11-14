#ifndef __P1__H__//prevent overlap header file
#define __P1__H__//prevent overlap header file
#define INPUT_LIMIT 100//Input's limit size
#define INPUT_SIZE 20//Tempotary input's size
#define BUCKET_SIZE 20//bucket's size
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
 *Search and print the opcode     along the format          *
 *Input : (1) char* Input_change : the formal input         *
 *(2) Hash** hash_buckets : the bucket for hash format      *
 *Output : None                                             *
 ************************************************************/
void Opcode_print(char* Input_change,Hash** hash_buckets);
#endif//prevent overlap header file
