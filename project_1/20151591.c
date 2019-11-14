#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "20151591.h"
void Input_change_function(char* Input,char* Input_change)
{
	int i,j;//This is index
	int len_1;//lentgh for Input
	int len_2;//lentgh for Input_change
	len_1 = strlen(Input);
	Input[--len_1] = '\0';//remove '\n'
	len_2 = 0;

		for(i = 0 ; i <= len_1 ; i++)//edit the space of Input
		{
			if(Input[i] != ' ' && Input[i] != '	')
				Input_change[len_2++] = Input[i];
			else if(Input[i] == ' ')
			{
				if(i + 1 <= len_1 && Input[i+1] != ',' && 0 <= i-1 && Input[i-1] != ',' && Input[i-1] != ' ' && Input[i-1] != '	')
					Input_change[len_2++] = ' ';
			}
			else if(Input[i] == '	')
			{
				if(i + 1 <= len_1 && Input[i+1] != ',' && 0 <= i-1 && Input[i-1] != ',' && Input[i-1] != ' ' && Input[i-1] != '	')
					Input_change[len_2++] = ' ';
			}
		}
		len_2 = strlen(Input_change);
		Input_change[len_2] = '\0';
		j=len_2;
		j--;
		while(Input_change[j] == ' ' || Input_change[j] == '	')//edit the space for last partition
		{
			if(Input_change[j] == ' ' || Input_change[j] == '	')
				Input_change[j] = '\0';
			j--;
		}

		for(i=0 ; i <= len_2 ; i++)//edit the space in front of ','
		{
			if(Input_change[i] == ' ' && i + 1 <= len_2 && Input_change[i+1] == ',')
			{
				for(j = i ; j <= len_2 ; j++)
				{
					if(j + 1 <= len_2)
						Input_change[j] = Input_change[j+1];
				}
			}
		}
}
void History_made(History** head,int* index,char* Input)
{
	History* tmp=NULL;//search for linked list of history
	History* moment=NULL;//pointer for previous node
	
	if(*index==1)//when linked list is vacant , add node to linked list of history
	{
		*head=(History*)malloc(sizeof(History));
		(*head)->num=1;
		(*head)->next=NULL;
		(*head)->prev=NULL;
		strcpy((*head)->mnemonic,Input);
		(*index)++;
	}
	else//when linked list is not vacant , add node to linked list of history
	{
		tmp=(*head);
		while(1)
		{
			if(tmp->next==NULL)
				break;

			tmp=tmp->next;
		}
		moment=tmp;
		tmp->next=(History*)malloc(sizeof(History));
		tmp=tmp->next;
		tmp->num=(*index);
		tmp->next=NULL;
		tmp->prev=moment;
		strcpy(tmp->mnemonic,Input);
		(*index)++;
	}
}
void History_free(History** head)
{
	History* tmp=NULL;//search for linked list of history
	History* Free_target=NULL;//pointer for free target of node

	tmp=(*head);
	while(1)
	{
		if(tmp==NULL)
		{
			*head=NULL;
			break;
		}

		Free_target=tmp;
		tmp=tmp->next;
		free(Free_target);
	}
}
void Dir_print(DIR** dir_info)
{
	struct dirent* dir;//pointer for current directory
	struct stat buf;//This for searching state of directory and file of current directory
	int flag;//This for deciding when print '\n'

	flag=0;
	if(*dir_info == NULL)
	{
		printf("There is no files and directorys\n");
		return;
	}
	if(*dir_info!=NULL)
	{
		while(1)
		{
			dir=readdir(*dir_info);
			if(dir == NULL)
				break;
			stat(dir->d_name,&buf);

			if(S_ISDIR(buf.st_mode))
			{
				if(strcmp(dir->d_name,".")!=0&&strcmp(dir->d_name,"..")!=0)//except for upper directory
				{
					printf("\t%s/  ",dir->d_name);
					flag++;
					if(flag==4)
					{
						printf("\n");
						flag=0;
					}
				}
			}
			else
			{
				if((buf.st_mode&S_IEXEC)==S_IEXEC)
				{
					printf("\t%s*  ",dir->d_name);
					flag++;
					if(flag==4)
					{
						printf("\n");
						flag=0;
					}
				}
				else
				{
					printf("\t%s  ",dir->d_name);
					flag++;
					if(flag==4)
					{
						printf("\n");
						flag=0;
					}
				}
			}
		}
	}
	else
		printf("Current Directory does not have Directorys and Files.\n");
	printf("\n");
}
int Dump_print1(unsigned char** Memory,int start_)
{
	int First_Index_first;//index of start memory
	int First_Index_second;//index of start memory
	int End_Index_first;//index of end memory
	int End_Index_second;//index of end memory
	int Memory_num;//memory partition number
	int i,j;//index for loop
	int end;//end index
	int start;//start index

	Memory_num=0;

	start=start_;

	if(start < 0 || 1048575 < start)
	{
		printf(" Error Dump Input : start input over available range\n");
		return -1;
	}
	end = start + 159;
	
	First_Index_first = start/16;
	First_Index_second = start%16;
	Memory_num = First_Index_first*16;

	if(end > 1048575)
	{
		end = 1048575;
		End_Index_first = end/16;
		End_Index_second = end%16;

	}
	else
	{
		End_Index_first = end/16;
		End_Index_second = end%16;
	}

	for(i=First_Index_first; i<=End_Index_first ;i++)//print the format of memory
	{
		if(i == First_Index_first && i == End_Index_first)
		{
			printf("%05X  ",Memory_num);
			Memory_num+=16;
			for(j=0;j<16;j++)
			{
				if(First_Index_second<=j && j<=End_Index_second) 
					printf("%02X  ",Memory[i][j]);
				else
					printf("    ");
			}
			printf(";  ");

			for(j=0;j<16;j++)
			{
				if(First_Index_second<=j&&j<=End_Index_second)
				{
					if(32<=Memory[i][j]&&Memory[i][j]<=126)
						printf("%c",Memory[i][j]);
					else
						printf(".");
				}
				else
					printf(".");
			}
			printf("\n");

		}
		else if(i == First_Index_first)//if start line , 
		{
			printf("%05X  ",Memory_num);
			Memory_num+=16;

			for(j=0;j<16;j++)
			{
				if(First_Index_second<=j)
					printf("%02X  ",Memory[i][j]);
				else
					printf("    ");
			}
			printf(";  ");

			for(j=0;j<16;j++)
			{
				if(First_Index_second<=j)
				{
					if(32<=Memory[i][j]&&Memory[i][j]<=126)
						printf("%c",Memory[i][j]);
					else
						printf(".");

				}
				else
					printf(".");
			}
			printf("\n");
		}
		else if(i == End_Index_first)//if end line , 
		{
			printf("%05X  ",Memory_num);
			Memory_num+=16;

			for(j=0;j<16;j++)
			{
				if(j<=End_Index_second)
					printf("%02X  ",Memory[i][j]);
				else
					printf("    ");
			}
			printf(";  ");

			for(j=0;j<16;j++)
			{
				if(j>End_Index_second)
					printf(".");
				else
				{
					if(32<=Memory[i][j]&&Memory[i][j]<=126)
						printf("%c",Memory[i][j]);
					else
						printf(".");
				}
			}
			printf("\n");

		}
		else//if it is not first line and end line , 
		{
			printf("%05X  ",Memory_num);
			Memory_num+=16;
	
			for(j=0;j<16;j++)
				printf("%02X  ",Memory[i][j]);

			printf(";  ");

			for(j=0;j<16;j++)
			{
				if(32<=Memory[i][j]&&Memory[i][j]<=126)
						printf("%c",Memory[i][j]);
					else
						printf(".");

			}
			printf("\n");

		}
	}
		return end;
}
void Help_print()
{
	printf("h[elp]\n");
	printf("d[ir]\n");
	printf("q[uit]\n");
	printf("hi[story]\n");
	printf("du[mp] [start , end]\n");
	printf("e[dit] address, value\n");
	printf("f[ill] start , end, value\n");
	printf("reset\n");
	printf("opcode mnemonic\n");
	printf("opcodelist\n");
}
int Determine_mnemonic(char* Input_change)
{
	int flag;//This for searching ' ' of Input_change after mnemonic
	int space_count;//the count of ' '
	int coma_count;//the count of ','
	int i;//index
	int len;//length of Input_change
	char* Input_1;//first token of Input_change
	char* Input_2;//second token of Input_change
	char* Input_3;//third token of Input_change
	char Input_temp[INPUT_LIMIT];//temporary space for Input_change
	
	flag=0;
	space_count=0;
	coma_count=0;
	len=0;

	if(strcmp("q",Input_change) == 0 || strcmp("quit",Input_change) == 0)//if "q" or "quit" mnemonic , 
		return 0;
	else if(strcmp("h",Input_change) == 0 || strcmp("help",Input_change) == 0)//if "h" or "help" mnemonic , 
		return 1;
	else if(strcmp("hi",Input_change) == 0 || strcmp("history",Input_change) == 0)//if "hi" or "history" mnemonic , 
		return 2;
	else if(strcmp("d",Input_change) == 0 || strcmp("dir",Input_change) == 0)//if "d" or "dir" mnemonic , 
		return 3;
	else if(strcmp("du",Input_change) == 0 || strcmp("dump",Input_change) == 0)//if "du" or "dump" mnemonic , 
		return 4;
	else if((Input_change[0] == 'd' && Input_change[1] == 'u' && Input_change[2] == ' ') || (Input_change[0] == 'd' && Input_change[1] == 'u' && Input_change[2] == 'm' && Input_change[3] == 'p' && Input_change[4] == ' '))//if dump format 2 or dump format 3 , 
	{
		len = strlen(Input_change);
		for(i=0 ; i < len ; i++)
		{
			if(Input_change[i] == ' ')
			{
				space_count++;
				flag++;
			}
			else if(Input_change[i] == ',')
				coma_count++;
			else if(space_count != 0)
			{
				if(('0' <= Input_change[i] && Input_change[i] <= '9') || ('a' <= Input_change[i] && Input_change[i] <= 'f') || ('A' <= Input_change[i] && Input_change[i] <='F'))
					continue;
				else
					return -1;
			}
		}
		
		if(space_count == 1 && coma_count == 0)//dump format 2.
			return 5;
		
		if(space_count == 1 && coma_count == 1)//dump format 3.
			return 6;
	}
	else if(strcmp("reset",Input_change) == 0)//if "reset" mnemonic , 
		return 7;
	else if((Input_change[0] == 'f' && Input_change[1] == ' ') || (Input_change[0] == 'f' && Input_change[1] == 'i' && Input_change[2] == 'l' && Input_change[3] == 'l' && Input_change[4] == ' '))//if "f" or "fill" mnemonic , 
	{
		len = strlen(Input_change);
		for(i=0 ; i < len ; i++)
		{
			if(Input_change[i] == ' ')
			{
				space_count++;
				flag++;
			}
			else if(Input_change[i] == ',')
				coma_count++;
			else if(space_count != 0)
			{
				if(('0' <= Input_change[i] && Input_change[i] <= '9') || ('a' <= Input_change[i] && Input_change[i] <= 'f') || ('A' <= Input_change[i] && Input_change[i] <='F'))
					continue;
				else
					return -1;
			}
			if(space_count == 1 && coma_count == 2)
				return 8;
		}
	}
	else if((Input_change[0] == 'e' && Input_change[1] == ' ') || (Input_change[0] == 'e' && Input_change[1] == 'd' && Input_change[2] == 'i' && Input_change[3] == 't' && Input_change[4] == ' '))//if "e" or "edit" mnemonic
	{
		len = strlen(Input_change);
		for(i=0 ; i < len ; i++)
		{
			if(Input_change[i] == ' ')
			{
				space_count++;
				flag++;
			}
			else if(Input_change[i] == ',')
				coma_count++;
			else if(space_count != 0)
			{
				if(('0' <= Input_change[i] && Input_change[i] <= '9') || ('a' <= Input_change[i] && Input_change[i] <= 'f') || ('A' <= Input_change[i] && Input_change[i] <='F'))
					continue;
				else
					return -1;//if error mnemonic , 
			}
			if(space_count == 1 && coma_count == 1)
				return 9;

		}

	}
	else if(strcmp(Input_change,"opcodelist") == 0)//if "opcodelist" mnemonic
	{
		return 10;
	}
	else
	{
		strcpy(Input_temp,Input_change);
		Input_1 = strtok(Input_temp," ");	
		Input_2 = strtok(NULL," ");
		Input_3 = strtok(NULL," ");

		if(Input_1 == NULL || Input_2 == NULL || Input_3 != NULL)
			return -1;//if error mnemonic , 

		if(strcmp(Input_1,"opcode") == 0)//if "opcode" mnemonic candidate , 
			return 11;
	}
	return -1;//if error mnemonic , 
}
int Dump_print2(char* Input_change,unsigned char** Memory)
{
	char dump_junk[INPUT_SIZE];//This for junk string
	int start;//start index
	int end;//end index
	int Memory_num;//This for memory partition
	int First_Index_first;//index of start memory
	int First_Index_second;//index of start memory
	int End_Index_first;//index of end memory
	int End_Index_second;//index of end memory
	int i,j;//index

	sscanf(Input_change,"%s %x",dump_junk,&start);
	
	if(start < 0 || 1048575 < start)//error input
	{
		printf(" Error Dump Input : start input over available range\n");
		return -1;
	}
	
	end = start + 159;
	First_Index_first = start/16;
	First_Index_second = start%16;
	Memory_num = First_Index_first*16;

	if(end > 1048575)
	{
		end = 1048575;
		End_Index_first = end/16;
		End_Index_second = end%16;
	}
	else
	{
		End_Index_first = end/16;
		End_Index_second = end%16;
	}
	
	for(i=First_Index_first;i<=End_Index_first;i++)//print the format of memory
	{
		if(i == First_Index_first && i == End_Index_first)
		{
			printf("%05X  ",Memory_num);
			Memory_num+=16;
			for(j=0;j<16;j++)
			{
				if(First_Index_second<=j && j<=End_Index_second) 
					printf("%02X  ",Memory[i][j]);
				else
					printf("    ");
			}
			printf(";  ");

			for(j=0;j<16;j++)
			{
				if(First_Index_second<=j&&j<=End_Index_second)
				{
					if(32<=Memory[i][j]&&Memory[i][j]<=126)
						printf("%c",Memory[i][j]);
					else
						printf(".");
				}
				else
					printf(".");
			}
			printf("\n");

		}
		else if(i == First_Index_first)//if first index , 
		{
			printf("%05X  ",Memory_num);
			Memory_num+=16;

			for(j=0;j<16;j++)
			{
				if(First_Index_second<=j)
					printf("%02X  ",Memory[i][j]);
				else
					printf("    ");
			}
			printf(";  ");

			for(j=0;j<16;j++)
			{
				if(j<First_Index_second)
					printf(".");
				else
				{
					if(32<=Memory[i][j]&&Memory[i][j]<=126)
						printf("%c",Memory[i][j]);
					else
						printf(".");
				}
			}
			printf("\n");
		}
		else if(i == End_Index_first)//if end index , 
		{
			printf("%05X  ",Memory_num);
			Memory_num+=16;

			for(j=0;j<16;j++)
			{
				if(j<=End_Index_second)
					printf("%02X  ",Memory[i][j]);
				else
					printf("    ");
			}
			printf(";  ");

			for(j=0;j<16;j++)
			{
				if(j>End_Index_second)
					printf(".");
				else
				{
					if(32<=Memory[i][j]&&Memory[i][j]<=126)
						printf("%c",Memory[i][j]);
					else
						printf(".");
				}
			}
			printf("\n");
		}
		else//if it is not first index and end index , 
		{
			printf("%05X  ",Memory_num);
			Memory_num+=16;
	
			for(j=0;j<16;j++)
				printf("%02X  ",Memory[i][j]);

			printf(";  ");

			for(j=0;j<16;j++)
			{
				if(32<=Memory[i][j]&&Memory[i][j]<=126)
						printf("%c",Memory[i][j]);
					else
						printf(".");
			}
			printf("\n");
		}
	}
	return end;
}
int Dump_print3(char* Input_change,unsigned char** Memory)
{
	char dump_junk[INPUT_SIZE];//This for junk string
	int start;//start index
	int end;//end index
	int Memory_num;//This for memory partition
	int First_Index_first;//index of start memory
	int First_Index_second;//index of start memory
	int End_Index_first;//index of end memory
	int End_Index_second;//index of end memory
	int i,j;//index

	start=0;

	sscanf(Input_change,"%s %x,%x",dump_junk,&start,&end);
	
	if(start < 0 || 1048575 < start)//error input
		{
			printf(" Error Dump Input : start input over available range\n");
			return -1;
		}
	if(end < 0 || 1048575 < end)
	{
		printf(" Error Dump Input : end input over available range \n");
		return -1;
	}
	if(end<start)
	{
		printf(" Error Dump Input : start input > end input\n");
		return -1;
	}
	
	First_Index_first = start/16;
	First_Index_second = start%16;
	Memory_num = First_Index_first*16;

	if(end > 1048575)
	{
		end = 1048575;
		End_Index_first = end/16;
		End_Index_second = end%16;

	}
	else
	{
		End_Index_first = end/16;
		End_Index_second = end%16;
	}

	for(i=First_Index_first;i<=End_Index_first;i++)//print the format of memory
	{
		if(i == First_Index_first && i == End_Index_first)//if first line and end line , 
		{
			printf("%05X  ",Memory_num);
			Memory_num+=16;

			for(j=0;j<16;j++)
			{
				if(First_Index_second<=j && j<=End_Index_second)
					printf("%02X  ",Memory[i][j]);
				else
					printf("    ");
			}
			printf(";  ");

			for(j=0;j<16;j++)
			{
				if(First_Index_second<=j && j<=End_Index_second)
				{
					if(32<=Memory[i][j]&&Memory[i][j]<=126)
						printf("%c",Memory[i][j]);
					else
						printf(".");
				}
				else
					printf(".");
			}
			printf("\n");
		}
		else if(i == First_Index_first)//if first line , 
		{
			printf("%05X  ",Memory_num);
			Memory_num+=16;

			for(j=0;j<16;j++)
			{
				if(First_Index_second<=j)
					printf("%02X  ",Memory[i][j]);
				else
					printf("    ");
			}
			printf(";  ");

			for(j=0;j<16;j++)
			{
				if(j<First_Index_second)
					printf(".");
				else
				{
					if(32<=Memory[i][j]&&Memory[i][j]<=126)
						printf("%c",Memory[i][j]);
					else
						printf(".");
				}
			}
			printf("\n");
		}
		else if(i == End_Index_first)//if end line , 
		{
			printf("%05X  ",Memory_num);
			Memory_num+=16;

			for(j=0;j<16;j++)
			{
				if(j<=End_Index_second)
					printf("%02X  ",Memory[i][j]);
				else
					printf("    ");
			}
			printf(";  ");

			for(j=0;j<16;j++)
			{
				if(j>End_Index_second)
					printf(".");
				else
				{
					if(32<=Memory[i][j]&&Memory[i][j]<=126)
						printf("%c",Memory[i][j]);
					else
						printf(".");
				}
			}
			printf("\n");
		}
		else//if it is not first line and end line , 
		{
			printf("%05X  ",Memory_num);
			Memory_num+=16;
	
			for(j=0;j<16;j++)
				printf("%02X  ",Memory[i][j]);

			printf(";  ");

			for(j=0;j<16;j++)
			{
				if(32<=Memory[i][j]&&Memory[i][j]<=126)
						printf("%c",Memory[i][j]);
					else
						printf(".");
			}
			printf("\n");
		}
	}
	return end;
}
void Fill_function(unsigned char** Memory , char* Input_change)
{
	int start;//start index
	int end;//end index
	unsigned int value_;//value input
	unsigned char value;//changed value input
	char Fill_Junk[INPUT_SIZE];//junk for  "f" or "fill" string , 
	int First_Index_first;//index of start memory
	int First_Index_second;//index of start memory
	int End_Index_first;//index of end memory
	int End_Index_second;//index of end memory
	int i,j;//index

	sscanf(Input_change,"%s %x,%x,%x",Fill_Junk,&start,&end,&value_);
	value = 0;
	value = value | value_;//or bit operate for changing value input
	if(value_ < 0 || 255 < value_)
	{
		printf(" Error Fill Input : value input over available range \n");
		return;
	}
	if(start < 0 || 1048575 < start)//error input
		{
			printf(" Error Fill Input : start input over available range\n");
			return;
		}
	if(end < 0 || 1048575 < end)
	{
		printf(" Error Fill Input : end input over available range\n");
		return;
	}
	if(end<start)
	{
		printf(" Error Fill Input : start input over end input\n");
		return;
	}
	if(value < 0 || 255 < value)
	{
		printf(" Error Fill Input : value input over available range \n");
		return;
	}
	
	First_Index_first = start/16;
	First_Index_second = start%16;

	if(end > 1048575)
	{
		end = 1048575;
		End_Index_first = end/16;
		End_Index_second = end%16;
	}
	else
	{
		End_Index_first = end/16;
		End_Index_second = end%16;
	}

	for(i=First_Index_first;i<=End_Index_first;i++)//edit value of memory
	{
		if(i == First_Index_first && i == End_Index_first)
		{
			for(j=0;j<16;j++)
			{
				if(First_Index_second<=j&&j<=End_Index_second)
					Memory[i][j] = value;
			}
		}
		else if(i == First_Index_first)
		{
			for(j=0;j<16;j++)
			{
				if(First_Index_second<=j)
					Memory[i][j] = value;
			}
		}
		else if(i == End_Index_first)
		{
			for(j=0;j<16;j++)
			{
				if(j<=End_Index_second)
					Memory[i][j] = value;
			}
		}
		else
		{
			for(j=0;j<16;j++)
				Memory[i][j] = value;
		}
	}
}
void Edit_function(unsigned char** Memory , char* Input_change)
{
	int Target;//target index
	int Target_first_index;//index of target memory
	int Target_second_index;//index of target memory
	char Edit_junk[INPUT_SIZE];//junk of "e" or "edit" string
	unsigned int value_;//value input
	unsigned char value;//changed value input

	sscanf(Input_change,"%s %x,%x",Edit_junk,&Target,&value_);
	value = 0;
	value = value | value_;//or bit operate for changing value input
	if(value_ < 0 || 255 < value_)
	{
		printf(" Error Fill Input : value input over available range \n");
		return;
	}
	if(value < 0 || value > 255)//error input
	{
		printf(" Error Edit Input : value input over available range\n");
		return;
	}
	if(Target < 0 || Target > 1048575)
	{
		printf(" Error Edit Input : target input over available range\n");
		return;
	}

	Target_first_index = Target / 16;
	Target_second_index = Target % 16;
	Memory[Target_first_index][Target_second_index]=value;
}
int Input_opctext(int* opcode,char** mnemonic,char** format)
{
	FILE* fp;//pointer for file struct
	int ret;//Decide when loop end
	int i;//index

	i=0;
	fp=fopen("opcode.txt","r");
	
	if(fp == NULL)//if there is no opcode.txt , 
	{	
		printf("there is no opcode.txt\n");
		return 0;
	}

	while(ret != EOF)
	{
		ret = fscanf(fp,"%x%s%s",&opcode[i],mnemonic[i],format[i]);
		i++;
	}
	fclose(fp);
	return 1;
}
void free_Input_opctext(int* opcode,char** mnemonic,char** format)
{
	int i;//index
	free(opcode);//free the array of opcode

	for(i=0;i<58;i++)//free the array of mnemonic
		free(mnemonic[i]);
	free(mnemonic);

	for(i=0;i<58;i++)//free the array of format
		free(format[i]);
	free(format);
}
int Hash_function(char* material)
{
	int i;
	int sum;

	sum=0;

	for(i=0;i<strlen(material);i++)
		sum+=material[i];

	return sum%20;
}
void Make_hash_table_function(Hash** hash_buckets,int* opcode,char** mnemonic,char** format)
{
	int index;//the index of hash table
	int i;//index
	Hash* New_node;//pointer for new node
	Hash* temp;//pointer for searching node

	index=0;
	New_node=NULL;

	for(i=0;i<58;i++)//making hash table
	{
		New_node=(Hash*)malloc(sizeof(Hash));
		New_node->opcode = opcode[i];
		strcpy(New_node->mnemonic,mnemonic[i]);
		strcpy(New_node->format,format[i]);
		New_node->next = NULL;
		New_node->prev = NULL;

		index = Hash_function(New_node->mnemonic);

		if(hash_buckets[index] == NULL)
			hash_buckets[index] = New_node;
		else
		{
			temp = hash_buckets[index];
			while(1)
			{
				if(temp->next == NULL)
					break;

				temp = temp->next;
			}
			temp->next = New_node;
			New_node->prev = temp;
		}
	}
}
void free_hash_table(Hash** hash_buckets)
{
	int i;//index
	Hash* temp;//pointer for searching the hash table
	Hash* Free_target;//pointer for free the node

	for(i=0;i<20;i++)//free the hash table
	{
		temp=hash_buckets[i];

		if(temp == NULL)
			continue;
		else
		{
			while(1)
			{
				Free_target=temp;
				temp=temp->next;
				free(Free_target);

				if(temp == NULL)
					break;
			}
			hash_buckets[i]=NULL;
		}
	}
}
void Opcodelist_print(Hash** hash_buckets)
{
	Hash* temp;//pointer for searching hash table
	int i;//index
	
	for(i=0;i<20;i++)//printing the hash table
	{
		temp=hash_buckets[i];

		printf("%d : ",i);
		while(1)
		{
			if(temp == NULL)
				break;

			printf("[%s, %X]",temp->mnemonic,temp->opcode);

			if(temp->next!=NULL)
				printf(" -> ");

			temp=temp->next;
		}
		printf("\n");
	}
}
void Opcode_print(char* Input_change,Hash** hash_buckets)
{
	int index;//index of hash table
	char input_opcode[INPUT_LIMIT];//string of inputing opcode
	char input_mnemonic[INPUT_LIMIT];//string of inputing mnemonic
	int flag=0;
	Hash* temp;//pointer for searching hash table
	index=0;
	sscanf(Input_change,"%s%s",input_opcode,input_mnemonic);
	index=Hash_function(input_mnemonic);
	temp = hash_buckets[index];
	while(1)//searching the hash table
	{
		if(temp == NULL)
			break;
		if(strcmp(temp->mnemonic,input_mnemonic)==0)
		{
			flag=1;
			break;
		}

		temp=temp->next;
	}
	if(flag == 0)//error search
		printf("Eroor Opcode_print : mnemonic input is error\n");
	else
		printf("opcode is %X\n",temp->opcode);
}
int main()
{
	char* Input;//original input
	char* Input_change;//changed input
	History* History_head;//the head of linked list of history
	History* History_tmp;//pointer for searching linked list of history
	int History_index;//order of input
	DIR* dir_info;//pointer for searching current directory
	unsigned char** Memory;//memory
	int len;//length of Input
	int Case;//classify the case
	int start;//start index of printing memory
	int start_;//decide right start index
	int* opcode;//array for opcode
	char** mnemonic;//array for mnemonic
	char** format;//array for format
	Hash* hash_buckets[BUCKET_SIZE];//hash_buckets for hash
	int opcode_txt;//Decide the success of function
	int i,j;//index

	opcode_txt=0;
	History_index=1;
	start_=0;
	start=0;
	History_head=NULL;
	History_tmp=NULL;

	Memory=(unsigned char**)malloc(sizeof(unsigned char*)*65536);
	for(i=0;i<65536;i++)
		Memory[i]=(unsigned char*)malloc(sizeof(unsigned char)*16);
	
	for(i=0;i<65536;i++)
		for(j=0;j<16;j++)
			Memory[i][j]=0;
	
	opcode=(int*)malloc(sizeof(int)*58);

	mnemonic=(char**)malloc(sizeof(char*)*58);
	for(i=0;i<58;i++)
		mnemonic[i]=(char*)malloc(sizeof(char)*10);

	format=(char**)malloc(sizeof(char*)*58);
	for(i=0;i<58;i++)
		format[i]=(char*)malloc(sizeof(char)*10);

	opcode_txt=Input_opctext(opcode,mnemonic,format);

	if(opcode_txt == 0)//error about opcode.txt
	{
		printf("There is no opcode.txt\n");
		return 0;
	}
	
	for(i = 0 ; i < 20 ; i++)
		hash_buckets[i] = NULL;

	Make_hash_table_function(hash_buckets,opcode,mnemonic,format);

	while(1)
	{
		printf("sicsim> ");

		Input=(char*)malloc(sizeof(char)*INPUT_LIMIT);//Input original thing

		fgets(Input,sizeof(char)*INPUT_LIMIT+1,stdin);
		
		len = strlen(Input);

		if(len < 0 || len > 90)//Check Input size
		{
			printf("Error Input : Input size over range\n");
			return 0;
		}
		
		Input_change=(char*)malloc(sizeof(char)*(len+1));

		Input_change_function(Input,Input_change);//Change the Input

		Case = Determine_mnemonic(Input_change);//Decide Case

		switch(Case)
		{
			case 0://input "q" or "quit"
				History_free(&History_head);
				for(i=0;i<65536;i++)
					free(Memory[i]);
				free(Memory);
				free_Input_opctext(opcode,mnemonic,format);
				free_hash_table(hash_buckets);
				free(Input);
				free(Input_change);
				return 0;
			case 1://input "h" or "help"
				History_made(&History_head,&History_index,Input);
				Help_print();
				free(Input);
				free(Input_change);
				break;
			case 2://input "hi" or "history"
				History_made(&History_head,&History_index,Input);
				History_tmp = History_head;
				while(1)
				{
					if(History_tmp==NULL)
						break;
	
					printf("%d     %s\n",History_tmp->num,History_tmp->mnemonic);
					History_tmp=History_tmp->next;
				}
				free(Input);
				free(Input_change);
				break;
			case 3://input "d" or "dir"
				History_made(&History_head,&History_index,Input);	
				dir_info=opendir("./");
				Dir_print(&dir_info);
				closedir(dir_info);
				free(Input);
				free(Input_change);
				break;
			case 4://input "du" or "dump"
				History_made(&History_head,&History_index,Input);
				start_ = Dump_print1(Memory,start) + 1;
				if(start_ > 1048575)
					start = 0;
				else if(start_ != -1)
					start=start_;
				free(Input);
				free(Input_change);
				break;
			case 5://input "d start" or "dump start"
				History_made(&History_head,&History_index,Input);//dump case 2
				start_ = Dump_print2(Input_change , Memory)+1;
				if(start_ > 1048575)
					start=0;
				else if(start_ != -1)
					start=start_;
				free(Input);
				free(Input_change);
				break;
			case 6://input "d start,end" or "dump start,end"
				History_made(&History_head,&History_index,Input);//dump case 3
				start_ = Dump_print3(Input_change , Memory)+1;
				if(start_>1048575)
					start=0;
				else if(start_ != -1)
					start=start_;
				free(Input);
				free(Input_change);
				break;
			case 7://input "reset"
				History_made(&History_head,&History_index,Input);
				for(i=0;i<65536;i++)
					for(j=0;j<16;j++)
						Memory[i][j]=0;
				free(Input);
				free(Input_change);
				break;
			case 8://input "f start,end,value" or "fill start,end,value"
				History_made(&History_head,&History_index,Input);
				Fill_function(Memory , Input_change);
				free(Input);
				free(Input_change);
				break;
			case 9://input "e target,value" or "edit target,value"
				History_made(&History_head,&History_index,Input);
				Edit_function(Memory , Input_change);
				free(Input);
				free(Input_change);
				break;
			case 10://input "opcodelist"
				History_made(&History_head,&History_index,Input);
				Opcodelist_print(hash_buckets);	
				free(Input);
				free(Input_change);
				break;
			case 11://input "opcode mnemonic"
				History_made(&History_head,&History_index,Input);
				Opcode_print(Input_change,hash_buckets);
				free(Input);
				free(Input_change);
				break;
			default://input wrong input
				printf("Error Input\n");
				free(Input);
				free(Input_change);
				break;
		}
	}
}
