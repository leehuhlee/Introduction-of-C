#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "20151591.h"
unsigned int Two_s_complement_result(int TA,int Pc_loc)
{
	return (TA+((~Pc_loc)+1))&4095;
}
void Make_listfile_syboltable_checkerror(char* Input_change)
{
	int start_flag;//indicate after meeting START DIRECTIVE
	int error_flag;//indicate that pass1 has error
	int first_symbol_flag;//START DIRECTIVE has symbol
	int len;//the number of string character
	char filename[50];//save the filename
	FILE* fp_r_assem;//file pointer for filename.ams
	char Code[1000][100];//save the assemcode line
	char Code_temp[100];//tranfer the assemcode line for tokenization
	int index;//index
	int Line[1000];//save the line number of assemcode fil
	int Loc[1000];//save the location
	char Error[1000][100];//save the error
	int index_error;//index for error print
	char junk[10];//token about the thing that is not necessary
	int coma_count;//the number of ','
	int s_count;//the number of '''
	int sh_count;//the number of'#'
	int plus_count;//the number of'+'
	int at_cout;//the number of '@'
	int junk_count;//the number of characters that is not necessary
	int count;//the count of thing
	int line;//for calculating line number at pass1
	int loc;//for calculating location at pass1
	char first_symbol[10];//save the first symbol
	int start_loc;//start location
	int end_loc;//end location
	char* input_1;//token for the first partition of input
	char* input_2;//token for the second partition of input
	char* input_3;//token for the third partition of input
	char* input_4;//token for the fourth partition of input
	char* input_5;//token for the five partition of input
	char* input_BYTE;//token for the BYTE DIRECTIVE lin
	char* input_BYTE_2;//token for the first partition of BYTE DIRECTIVE assemcode line
	char* input_BYTE_3;//token for the first partition of BYTE DIRECTIVE assemcode line
	char Code_BYTE[100];//tranfer the assemcode line for tokenization
	int input1_state;//first partition state
	int input2_state;//second partition state
	int i;//index for loop
	char* sight;//decide the end of file
	char program_name[50];//save the file name
	int ob_len[1000];//object code's lentgh->-1 change line  0 START END comment
	char ob_code[1000][100];//save object code
	int error_flag2;//pass2 error_flag
	int Pc_loc;//for Pc relative
	int B_loc;//for Base relative
	char Error_2[1000][100];//save the error
	int index_error_2;//save the error through pass2
	char filename_lst[50];//filename.lst
	char filename_obj[50];//filename.obj
	FILE* fp_w_lst;//file pointer for filename.lst
	FILE* fp_w_ob;//file pointer for filename.obj
	int p;//index for 2loop
	int N,I;//N , I about instruction
	int X,B,P,E;//X , B , P , E about instruction
	int Decimal;//save assemcode's decimal number
	int TA;//Target address
	char Base_symbol[20];//LDB's operand symbol
	int Base_symbol_flag;//indicate that there is LDB's operand symbol
	char object_code[1000][100];//object code
	int obj_index;//index for object code
	int first_flag;//indicate each first line object code of filename.obj
	int start_loc_print[1000];// save the each "T~~" start location about filename.obj
	int modification_loc[1000];//save the FORMAT4's location
	int index_modification;// index for modification_loc
	int point_count;//the number of '.'
	//pass..2
	//Initialize
	start_flag=0;	error_flag=0;	first_symbol_flag=0;
	input1_state=0;	input2_state=0;
	len=0;	count =0;
	coma_count=0;	s_count=0;	sh_count=0;	plus_count=0;	at_cout=0;	junk_count=0;
	line=0;	loc=0;
	start_loc=0;	end_loc=0;
	index=-1; index_error=-1;	index_modification=-1;
	sscanf(Input_change,"%s%s",junk,filename);//tokenize to get filename
	len=strlen(filename);
	if(len<5 || filename[len-1]!='m' || filename[len-2]!='s' || filename[len-3]!='a' || filename[len-4]!='.')//it is not assemcode file
	{
		printf("The file name as user's input is not assemcode\n");
		return;
	}
	for(i=0;i<len-4;i++)//before ".asm" '.'character aprrears
	{
		if(filename[i] == '.')
		{
			printf("The file name as user's input is not assemcode\n");
			return;
		}
	}
	strcpy(filename_lst,filename);	strtok(filename_lst,".");	strcat(filename_lst,".lst");
	strcpy(filename_obj,filename);	strtok(filename_obj,".");	strcat(filename_obj,".obj");//Make filenames about list file and object file
	input_1=NULL;	input_2=NULL;	input_3=NULL;	input_4=NULL;	input_5=NULL;
	Free_symbol_table();//free the already symbol table

	Decimal=0;
	Base_symbol_flag=0;
	Base_symbol[0]='\0';
	N=0; I=0; X=0;	B=0;	P=0;	E=0;	TA=0;
	Pc_loc=0; B_loc=-1; 
	error_flag2=0;	index_error_2=-1;
	for(i=0;i<=1000;i++)
		ob_code[i][0]='\0';
	//initialize end


	//pass1	: check error ( check whther right foramt , the overlap of symbol) and make symbol table
	fp_r_assem=fopen(filename,"rt");//file open for reading assemcodefile
	if(fp_r_assem==NULL)//if there is not assemcodefile
	{
		printf("There does not exist file as user's input\n");
		return;
	}
	while(1)//read the filename.asm
	{
		if(feof(fp_r_assem)==EOF)//if file pointer meets EOF, end the loop
			break;
		index++;
		sight=fgets(Code[index],sizeof(char)*99,fp_r_assem);
		if(sight==NULL)//if file pointer meets EOF , end the loop 
			break;
		if(feof(fp_r_assem)==EOF)//if file pointer meets EOF ,end the loop
			break;
		line+=5;//when read a line , line number +5
		Line[index]=line;
		strcpy(Code_temp,Code[index]);

		input_1=NULL;	input_2=NULL;	input_3=NULL;	input_4=NULL;	input_5=NULL;
		input_1=strtok(Code_temp,"\t,' \n"); input_2=strtok(NULL,"\t,' \n"); input_3=strtok(NULL,"\t,' \n"); input_4=strtok(NULL,"\t,' \n"); input_5=strtok(NULL,"\t,' \n");
		
		input1_state=Differentiate(input_1);
		input2_state=Differentiate(input_2);
		//if LDB line has symbol
		if(input_1!=NULL&&strcmp("LDB",input_1)==0)//if it has LDB symbol operand , save this at Base_symbol[20] for BASE line
		{
			if(input_2!=NULL)
			{
				if('A'<=input_2[0]&&input_2[0]<='Z'&&Differentiate_2(input_2)==0)//simple address
				{
					strcpy(Base_symbol,input_2);	Base_symbol_flag=1;
				}
				else if((input_2[0]=='#'||input_2[0]=='@')&&Differentiate_2(input_2+1)==0)//indirect address or immediate address
				{
					strcpy(Base_symbol,input_2+1);	Base_symbol_flag=1;
				}
			}
		}//if LDB line does not have symbol
		else if(input_1!=NULL&&Differentiate_2(input_1)==0&&input_2!=NULL&&strcmp("LDB",input_2)==0)//if it has LDB symbol opernad , save this at Base_symbol[20] for BASE line
		{
			if(input_3!=NULL)
			{
				if('A'<=input_3[0]&&input_3[0]<='Z'&&Differentiate_2(input_3)==0)//simple address
				{
					strcpy(Base_symbol,input_3);	Base_symbol_flag=1;
				}
				else if((input_2[0]=='#'||input_2[0]=='@')&&Differentiate_2(input_3+1)==0)//indirect address or immediate address
				{
					strcpy(Base_symbol,input_3+1);	Base_symbol_flag=1;
				}
			}
		}
		
		coma_count=0;	s_count=0;	sh_count=0;	plus_count=0;	at_cout=0;	junk_count=0;	point_count=0;//intialize all counts

			for(i=0;i<strlen(Code[index]);i++)
			{
				if(Code[index][i]=='.')
				{
					point_count++;
				}
				else if(Code[index][i]==','&&point_count==0)//before meet comment , if assemcode line has ',' , count up
					coma_count++;
				else if(Code[index][i]=='#'&&point_count==0)//before meet comment , if assemcode line has '#' , count up
					sh_count++;
				else if(Code[index][i]=='@'&&point_count==0)//before meet comment , if assemcode line has '@' , count up
					at_cout++;
				else if(Code[index][i]=='+'&&point_count==0)//before meet comment , if assemcode line has '+' , count up
					plus_count++;
				else if(Code[index][i]=='\''&&point_count==0)//before meet comment , if assemcode line has ''' , count up
					s_count++;
				else if(('A'<=Code_temp[i]&&Code_temp[i]<='Z')||('0'<=Code_temp[i]&&Code_temp[i]<='9'))
					continue;
				else//before meet comment , if assemcode line has invalid character , count up
					junk_count++;
			}

		if(start_flag==1)//after meeting START DIRECTIVE but before meeting first mnemonic or DIRECTIVE , 
		{
			if(1<=input1_state && input1_state<=4)//it does not have first symbol
			{
				start_flag=2;
				first_symbol_flag=0;
			}
			else if(input1_state==0 && (1<=input2_state&&input2_state<=4))//it has first symbol
			{
				start_flag=2;
				strcpy(first_symbol,input_1);
				first_symbol_flag=1;
			}
		}
		

		if((coma_count!=0&&coma_count!=1))//if the number of ',' is over 2 , 
		{
			error_flag=1;
			sprintf(Error[++index_error],"line%d error : it is wrong\n",line);
		}
		else if(input1_state==-2)//if the symbol is already in symbol table , 
		{
			error_flag=1;
			sprintf(Error[++index_error],"line%d error : this line's symbol already appears above as aymbol\n",line);
		}
		else if(input1_state==-4)//meet white space line
		{
			sprintf(Code[index],"\n");
		}
		else if(input_1[0]=='.')//meet the comment
			Loc[index]=-1;//when making list file location -1 means that does not file print the location
		else if(input1_state==0&&input2_state==5)//Meet the START Line
		{
			strcpy(program_name,input_1);
			start_flag=1;//indicate START DIRECTIVE meet 
			if(Check_START5(input_1,input_2,input_3,input_4)==1)//right format
			{
				if(Is_hexa(input_3)==1)//if input3 is hexadecimal number , 
				{
					sscanf(input_3,"%x",&start_loc);
				}
				else//if input3 is not hexadecimal number , start location is 0
					start_loc=0;
				loc=start_loc;
				Loc[index]=loc;
				Symbol_table_make(input_1,start_loc);
			}
			else//wrong format
			{
				loc=0;
				start_loc=0;
				Loc[index]=loc;
				error_flag=1;
				sprintf(Error[++index_error],"line%d error : START format wrong\n",line);
			}
		}
		else if(input1_state==6)//meet the END line
		{
			end_loc=loc;//save the end location
			Loc[index]=-1;//location -1 means does not file print location  
			if(first_symbol_flag==0)//first_symbol does not exist
			{
				if(Check_END6(input_1,input_2,input_3,input_4,NULL)!=1)//wrong format
				{
					error_flag=1;
					sprintf(Error[++index_error],"line%d error : END format wrong\n",line);
				}
			}
			else//if there is symbol
			{
				if(Check_END6(input_1,input_2,input_3,input_4,first_symbol)!=1)//wrong format
				{
					error_flag=1;
					sprintf(Error[++index_error],"line%d error : END format wrong\n",line);
				}
			}
			if(input1_state==0)//if first token is symbol
				Symbol_table_make(input_1,end_loc);//insert symbol in symbol table
		}
		else if(input1_state==0&&input2_state==7&&input_3!=NULL)//meet the BYTE line
		{
			Loc[index]=loc;//save the location
			if(strcmp("C",input_3)==0)//BYTE C's case
			{
				input_BYTE=NULL; input_BYTE_2=NULL;	input_BYTE_3=NULL;
				Loc[index]=loc;
				strcpy(Code_BYTE,Code[index]);
				input_BYTE=strtok(Code_BYTE,"\t ");
				input_BYTE=strtok(NULL,"\t ");
				input_BYTE=strtok(NULL,"\t ");//
				

				input_BYTE_2=strtok(input_BYTE,"'\n");
				input_BYTE_2=strtok(NULL,"'\n");
				input_BYTE_3=strtok(NULL,"'\n");//tokenize double times to check whether BYTE FORMAT is wrong
				if(input_BYTE_2!=NULL && (input_BYTE_3==NULL||input_BYTE_3[0]=='.'))
					loc+=strlen(input_BYTE_2);
				else
				{
					error_flag=1;
					sprintf(Error[++index_error],"line%d error : BYTE operand wrong\n",line);
				}

			}
			else if(strcmp("X",input_3)==0)//BYTE X's case
			{

				input_BYTE=NULL; input_BYTE_2=NULL;	input_BYTE_3=NULL;
				Loc[index]=loc;
				strcpy(Code_BYTE,Code[index]);
				input_BYTE=strtok(Code_BYTE,"\t ");
				input_BYTE=strtok(NULL,"\t ");
				input_BYTE=strtok(NULL,"\t ");//
				

				input_BYTE_2=strtok(input_BYTE,"'\n");
				input_BYTE_2=strtok(NULL,"'\n");
				input_BYTE_3=strtok(NULL,"'\n");
				
				//To Check BYTE FORMAT , tokenize double times

				if(input_BYTE_2!=NULL &&strlen(input_BYTE_2)%2==0&&Is_hexa(input_BYTE_2)==1&& (input_BYTE_3==NULL||input_BYTE_3[0]=='.'))
					loc+=strlen(input_BYTE_2)/2;
				else//BYTE operand is wrong
				{
					error_flag=1;
					sprintf(Error[++index_error],"line%d error : BYTE operand wrong\n",line);
				}
			}
			else//BYTE operand is wrong
			{
					error_flag=1;
					sprintf(Error[++index_error],"line%d error : BYTE operand wrong\n",line);
			}
				Symbol_table_make(input_1,Loc[index]);
		}
		else if((input1_state==0&&input2_state==8)||input1_state==8)//meet the RESB line
		{
			Loc[index]=loc;
			if(input1_state==0)//there is symbol
			{
				if(Check_RESB8(input_1,input_2,input_3,input_4)==1)//it is right RESB FORMAT
				{
					sscanf(input_3,"%d",&count);
					loc+=count;
				}
				else//it is not along with RESB FORMAT
				{
					error_flag=1;
					sprintf(Error[++index_error],"line%d error : RESB format wrong\n",line);
				}
				Symbol_table_make(input_1,Loc[index]);//insert symbol into symbol table
			}
			else//there is not symbol
			{
				if(Check_RESB8(input_1,input_2,input_3,input_4)==1)//it is right RESB FORMAT
				{
					sscanf(input_2,"%d",&count);
					loc+=count;
				}
				else
				{
					error_flag=1;
					sprintf(Error[++index_error],"line%d error : RESB format wrong\n",line);
				}
			}
		}
		else if((input1_state==0&&input2_state==9)||input1_state==9)//meet the WORD line
		{
			Loc[index]=loc;

			if(Check_WORD9(input_1,input_2,input_3,input_4)==1)//right format
				loc+=3;
			else//wrong format
			{
				error_flag=1;
				sprintf(Error[++index_error],"line%d error : WORD format wrong\n",line);
			}
				Symbol_table_make(input_1,Loc[index]);//insert symbol into symbol table
		}
		else if((input1_state==0&&input2_state==10)||input1_state==10)//meet the RESW line
		{
			Loc[index]=loc;
			if(input1_state==0)//there is symbol
			{
				if(Check_RESW10(input_1,input_2,input_3,input_4)==1)//right format
				{
					sscanf(input_3,"%d",&count);
					loc+=count*3;
				}
				else//wrong format
				{
					error_flag=1;
					sprintf(Error[++index_error],"line%d error : RESW format wrong\n",line);
				}
				Symbol_table_make(input_1,Loc[index]);//insert symbol into symbol table
			}
			else//there is not symbol
			{
				if(Check_RESW10(input_1,input_2,input_3,input_4)==1)//right format
				{
					sscanf(input_3,"%d",&count);
					loc+=count*3;
				}
				else//wrong format
				{
					error_flag=1;
					sprintf(Error[++index_error],"line%d error : RESW format wrong\n",line);
				}
			}
		}
		else if(input1_state==11)//meet the BASE line
		{
			Loc[index]=loc;
				if(input_2!=NULL&&(input_3==NULL||input_3[0]=='.'))
						continue;
				else
				{
					error_flag=1;
					sprintf(Error[++index_error],"line%d error : BASE format wrong\n",line);
				}
		}
		else if((input1_state==0&&input2_state==1)||input1_state==1)//meet the FORMAT1 mnemonic line
		{
			Loc[index]=loc;
			if(Check_FORM1(input_1,input_2,input_3)==1)//right format
				loc+=1;
			else//wrong format
			{
				error_flag=1;
				if(input1_state==0)
					sprintf(Error[++index_error],"line%d error : %s format1 wrong\n",line,input_2);
				else
					sprintf(Error[++index_error],"line%d error : %s format1 wrong\n",line,input_1);
			}
			if(input1_state==0)//there is symbol
				Symbol_table_make(input_1,Loc[index]);
		}
		else if((input1_state==0&&input2_state==2)||input1_state==2)//meet the FORMAT2 mnemonic line
		{
			Loc[index]=loc;
			if(Check_FORM2(input_1,input_2,input_3,input_4,input_5,coma_count)==1)//right format
				loc+=2;
			else//wrong format
			{
				error_flag=1;
				if(input1_state==0)
					sprintf(Error[++index_error],"line%d error : %s format2 wrong\n",line,input_2);
				else
					sprintf(Error[++index_error],"line%d error : %s format2 wrong\n",line,input_1);
			}
			if(input1_state==0)//there is symbol
				Symbol_table_make(input_1,Loc[index]);
		}
		else if((input1_state==0&&input2_state==3)||input1_state==3)//meet the FORMAT3 mnemonic line
		{
			Loc[index]=loc;
			if(input1_state==0)//there is symbol
			{
				if(Check_FORM3(input_1,input_2,input_3,input_4,input_5)==1)//right format
				{
					loc+=3;
				}
				else//wrong format
				{
					error_flag=1;
					sprintf(Error[++index_error],"line%d error : %s format3 wrong\n",line,input_2);
				}
				Symbol_table_make(input_1,Loc[index]);//LDB
			}
			else//there is not symbol
			{
				if(Check_FORM3(input_1,input_2,input_3,input_4,input_5)==1)//right format
				{
					loc+=3;
				}
				else//wrong format
				{
					error_flag=1;
					sprintf(Error[++index_error],"line%d error : %s format3 wrong\n",line,input_1);
				}
			}
		}
		else if((input1_state==0&&input2_state==4)||input1_state==4)//meet the FORMAT4 mnemonic line
		{
			Loc[index]=loc;
			if(input1_state==0)//there is symbol
			{
				if(Check_FORM4(input_1,input_2,input_3,input_4,input_5)==1)//right format
					loc+=4;
				else//wrong format
				{
					error_flag=1;
					sprintf(Error[++index_error],"line%d error : %s format4 wrong\n",line,input_2);
				}
				Symbol_table_make(input_1,Loc[index]);
			}
			else//there is not symbol
			{
				if(Check_FORM4(input_1,input_2,input_3,input_4,input_5)==1)//right format
					loc+=4;
				else//wrong format
				{
					error_flag=1;
					sprintf(Error[++index_error],"line%d error : %s format4 wrong\n",line,input_1);
				}
			}
		}
		else
		{
			error_flag=1;
			sprintf(Error[++index_error],"line%d error : code is wrong\n",line);
		}
	}
	fclose(fp_r_assem);
	index--;
	if(error_flag==1)//if it has error print the error
	{
		for(i=0;i<=index_error;i++)
			printf("%s",Error[i]);
		Free_symbol_table();
		printf("line error : your assem code has error please check your code please\n");
		return;
	}
	//pass2 : make object code and additional error check ( right operand ) 
	for(p=0;p<=index;p++)
	{
		strcpy(Code_temp,Code[p]);
		input_1=NULL; input_2=NULL;	input_3=NULL;	input_4=NULL;	input_5=NULL;
		input_1=strtok(Code_temp,"\t,' \n");	input_2=strtok(NULL,"\t,' \n");	input_3=strtok(NULL,"\t,' \n");	input_4=strtok(NULL,"\t,' \n");	input_5=strtok(NULL,"\t,' \n");//tokenize
		input1_state=Differentiate_2(input_1);	input2_state=Differentiate_2(input_2);//search the state of input
		N=0;	I=0;	X=0;	B=0;	P=0;	E=0;	Decimal=0;
		if(input_1==NULL)
		{
			sprintf(ob_code[p],"\n");
			ob_len[p]=0;
			continue;
		}
		else if(input_1[0]=='.')//meet the comment
			ob_len[p]=0;
		else if(input2_state==5)//meet start
			ob_len[p]=0;
		else if(input1_state==6)//meet END
			ob_len[p]=0;
		else if(input1_state==7||(input1_state==0&&input2_state==7))//meet BYTE so 
		{
			if(input1_state==7)//there is not symbol
			{
				if(strcmp("C",input_2)==0)
				{
					strcpy(Code_BYTE,Code[p]);
					input_BYTE=strtok(Code_BYTE,"\t ");
					input_BYTE=strtok(NULL,"\t ");
					input_BYTE=strtok(NULL,"\t ");//

					input_BYTE_2=strtok(input_BYTE,"'");
					input_BYTE_2=strtok(NULL,"'");
					input_BYTE_3=strtok(NULL,"'");
					//tokenize double times to check whether BYTE FORMAT is right
					for(i=0;i<strlen(input_BYTE_2);i++)
						sprintf((*(ob_code+p)+2*i),"%02X",input_BYTE_2[i]);
					ob_code[p][2*i]='\0';
				}
				else if(input_2!=NULL&&strcmp("X",input_2)==0)
				{
					for(i=0;i<strlen(input_3);i++)
						ob_code[p][i]=input_3[i];
					ob_code[p][i]='\0';
				}
				ob_len[p]=strlen(ob_code[p]);
			}
			else//there is symbol
			{
				if(strcmp("C",input_3)==0)
				{
					for(i=0;i<strlen(input_4);i++)
						sprintf((*(ob_code+p)+2*i),"%02X",input_4[i]);
					ob_code[p][2*i]='\0';
				}
				else if(input_3!=NULL&&strcmp("X",input_3)==0)
				{
					for(i=0;i<strlen(input_4);i++)
						ob_code[p][i]=input_4[i];
					ob_code[p][i]='\0';
				}
				ob_len[p]=strlen(ob_code[p]);
			}
		}
		else if(input1_state==8||input2_state==8)//meet RESB
			ob_len[p]=-1;
		else if(input2_state==9)//meet WORD
		{
			if(input1_state==0&&input2_state==9&&input_3!=NULL&&Is_decimal(input_3)==1&&(input_4==NULL||input_4[0]=='.'))//there is symbol
			{
				sscanf(input_3,"%d",&count);
				if(0<=count&&count<=16777215)//it is over oxffffff
				{
					sprintf(ob_code[p],"%06X",count);
					ob_len[p]=strlen(ob_code[p]);
				}
				else
				{
					error_flag2=1;
					sprintf(Error_2[++index_error_2],"line%d error : WORD operand is over 16777215\n",Line[p]);
				}
			}
			else
			{
				error_flag2=1;
				sprintf(Error_2[++index_error_2],"line%d error : WORD operand is wrong\n",Line[p]);

			}
		}
		else if(input1_state==10||input2_state==10)//meet RESW
			ob_len[p]=-1;
		else if(input1_state==1||input2_state==1)//meet FORMAT1
		{
			if(input1_state==1)//there is not symbol
				sprintf(ob_code[p],"%02X",Opcode_get(input_1));
			else//there is symbol
				sprintf(ob_code[p],"%02X",Opcode_get(input_2));
			ob_len[p]=strlen(ob_code[p]);
		}
		else if(input1_state==2||input2_state==2)//meet FORMAT2
		{
			if(input_1!=NULL&&strcmp("CLEAR",input_1)==0&&input_2!=NULL&&Is_register(input_2)==1&&(input_3==NULL||input_3[0]=='.'))//meet CLEAR mnemonic and there is not symbol
			{
				sprintf(ob_code[p],"%02X%01X%01X",Opcode_get(input_1) , Register_num_get(input_2) , 0);	ob_len[p]=strlen(ob_code[p]);
			}
			else if(input1_state==0 &&input_2!=NULL && strcmp("CLEAR",input_2)==0 && Is_register(input_3)==1 && (input_4==NULL||input_4[0]=='.'))//meet CLEAR mnemonic and there is symbol
			{
				sprintf(ob_code[p],"%02X%01X%01X",Opcode_get(input_2) , Register_num_get(input_3) , 0);	ob_len[p]=strlen(ob_code[p]);
			}
			else if(input_1!=NULL&&strcmp("TIXR",input_1)==0&&input_2!=NULL&&Is_register(input_2)==1&&(input_3==NULL||input_3[0]=='.'))//meet TIXR mnemonic and there is not symbol
			{
				sprintf(ob_code[p],"%02X%01X%01X",Opcode_get(input_1) , Register_num_get(input_2) , 0);	ob_len[p]=strlen(ob_code[p]);
			}
			else if(input1_state==0 &&input_2!=NULL && strcmp("TIXR",input_2)==0 && Is_register(input_3)==1 && (input_4==NULL||input_4[0]=='.'))//meet TIXR mnemonic and there is symbol
			{
				sprintf(ob_code[p],"%02X%01X%01X",Opcode_get(input_2) , Register_num_get(input_3) , 0);	ob_len[p]=strlen(ob_code[p]);
			}
			else if(input1_state==2)//there is not symbol
			{
				sprintf(ob_code[p],"%02X%01X%01X",Opcode_get(input_1),Register_num_get(input_2),Register_num_get(input_3));	ob_len[p]=strlen(ob_code[p]);
			}
			else if(input2_state==2)//there is symbol
			{
				sprintf(ob_code[p],"%02X%01X%01X",Opcode_get(input_2),Register_num_get(input_3),Register_num_get(input_4));	ob_len[p]=strlen(ob_code[p]);
			}
			else//error
			{
				error_flag2=1;
				sprintf(Error_2[++index_error_2],"line%d error : it is does not along wiht FORMAT2 form\n",Line[p]);
			}
		}
		else if(input1_state==4||input2_state==4)//meet FORMAT4
		{E=1;B=0;P=0;
			if((strcmp("RSUB",input_1+1)==0&&(input_2==NULL||input_2[0]=='.'))||((input_2!=NULL&&strcmp("RSUB",input_2+1)==0)&&(input_3==NULL||input_3[0]=='.')))//the case of RSUB
			{
				sprintf(ob_code[p],"4F100000");
				ob_len[p]=strlen(ob_code[p]);
				modification_loc[++index_modification]=Loc[p];
			}
			else if(input1_state==4&&input_2!=NULL)//there is not symbol
			{
				if(input_3!=NULL&&strcmp("X",input_3)==0 && (input_4==NULL||input_4[0]=='.'))//there is X index
				{X=1;
					if(input_2[0]=='@')//indirect address
					{N=1;I=0;
						if(Check_already_symbol(input_2+1)==1)//operand is symbol
						{
							sprintf(ob_code[p],"%02X%01X%05X",Opcode_get(input_1+1)+N*2+I , X*2*2*2+B*2*2+P*2+E , Loc_from_symbol(input_2+1));	ob_len[p]=strlen(ob_code[p]);
							modification_loc[++index_modification]=Loc[p];
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT4's operand is wrong\n",Line[p]);
						}
					}
					else if(input_2[0]=='#')//immediate address
					{N=0;I=1;
						if(Is_decimal(input_2+1)==1)//operand is Decimal number
						{
							sscanf(input_2+1,"%d",&Decimal);
							if(0<=Decimal&&Decimal<=1048575)//check operand's range
							{
								sprintf(ob_code[p],"%02X%01X%05X",Opcode_get(input_1+1)+N*2+I , X*2*2*2+B*2*2+P*2+E , Decimal);	ob_len[p]=strlen(ob_code[p]);
							}
							else//error
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : FORMAT4's operand is wrong\n",Line[p]);
							}
						}
						else if(Check_already_symbol(input_2+1)==1)//operand is symbol
						{
							sprintf(ob_code[p],"%02X%01X%05X",Opcode_get(input_1+1)+N*2+I , X*2*2*2+B*2*2+P*2+E , Loc_from_symbol(input_2+1));	ob_len[p]=strlen(ob_code[p]);
							modification_loc[++index_modification]=Loc[p];
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT4's operand is wrong\n",Line[p]);
						}
					}
					else//simple address
					{N=1;I=1;
						if(Check_already_symbol(input_2)==1)//operand is symbol
						{
							sprintf(ob_code[p],"%02X%01X%05X",Opcode_get(input_1+1)+N*2+I , X*2*2*2+B*2*2+P*2+E , Loc_from_symbol(input_2));	ob_len[p]=strlen(ob_code[p]);
							modification_loc[++index_modification]=Loc[p];
						}
						else//error form 
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT4's operand is wrong\n",Line[p]);
						}
					}
				}
				else if(input_3==NULL||input_3[0]=='.')//there is not Xindex
				{X=0;
					if(input_2[0]=='@')//indirect address
					{N=1;I=0;
						if(Check_already_symbol(input_2+1)==1)//operand is symbol
						{
							sprintf(ob_code[p],"%02X%01X%05X",Opcode_get(input_1+1)+N*2+I , X*2*2*2+B*2*2+P*2+E , Loc_from_symbol(input_2+1));	ob_len[p]=strlen(ob_code[p]);
							modification_loc[++index_modification]=Loc[p];
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT4's operand is wrong\n",Line[p]);
						}
					}
					else if(input_2[0]=='#')//immediate address
					{N=0;I=1;
						if(Is_decimal(input_2+1)==1)//operand is Decimal number
						{
							sscanf(input_2+1,"%d",&Decimal);
							if(0<=Decimal&&Decimal<=1048575)//check the range
							{
								sprintf(ob_code[p],"%02X%01X%05X",Opcode_get(input_1+1)+N*2+I , X*2*2*2+B*2*2+P*2+E , Decimal);	ob_len[p]=strlen(ob_code[p]);
							}
							else//error
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : FORMAT4's operand is wrong\n",Line[p]);
							}
						}
						else if(Check_already_symbol(input_2+1)==1)//operand is symbol
						{
							sprintf(ob_code[p],"%02X%01X%05X",Opcode_get(input_1+1)+N*2+I , X*2*2*2+B*2*2+P*2+E , Loc_from_symbol(input_2+1));	ob_len[p]=strlen(ob_code[p]);
							modification_loc[++index_modification]=Loc[p];
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT4's operand is wrong\n",Line[p]);
						}
					}
					else//simple address
					{N=1;I=1;
						if(Check_already_symbol(input_2)==1)//operand is symbol
						{
							sprintf(ob_code[p],"%02X%01X%05X",Opcode_get(input_1+1)+N*2+I , X*2*2*2+B*2*2+P*2+E , Loc_from_symbol(input_2));	ob_len[p]=strlen(ob_code[p]);
							modification_loc[++index_modification]=Loc[p];
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : it is not along with right FORMAT4\n",Line[p]);
						}
					}
				}
				else//error
				{
					error_flag2=1;
					sprintf(Error_2[++index_error_2],"line%d error : it is not along with right FORMAT4\n",Line[p]);
				}
			}
			else if(input2_state==4&&input_3!=NULL)//there is symbol
			{
				if(input_4!=NULL&&strcmp("X",input_4)==0 && (input_5==NULL||input_5[0]=='.'))//there is Xindex
				{X=0;
					if(input_3[0]=='@')//indirect address
					{N=1;I=0;
						if(Check_already_symbol(input_3+1)==1)//operand is symbol
						{
							sprintf(ob_code[p],"%02X%01X%05X",Opcode_get(input_2+1)+N*2+I , X*2*2*2+B*2*2+P*2+E , Loc_from_symbol(input_3+1));	ob_len[p]=strlen(ob_code[p]);
							modification_loc[++index_modification]=Loc[p];
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT4's operand is wrong\n",Line[p]);
						}
					}
					else if(input_3[0]=='#')//immediate address
					{N=0;I=1;
						if(Is_decimal(input_3+1)==1)//operand is Decimal number
						{
							sscanf(input_3+1,"%d",&Decimal);
							if(0<=Decimal&&Decimal<=1048575)//check the range
							{
								sprintf(ob_code[p],"%02X%01X%05X",Opcode_get(input_2+1)+N*2+I , X*2*2*2+B*2*2+P*2+E , Decimal);	ob_len[p]=strlen(ob_code[p]);
							}
							else//error
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : FORMAT4's operand is wrong\n",Line[p]);
							}
						}
						else if(Check_already_symbol(input_3+1)==1)//operand is symbol
						{
							sprintf(ob_code[p],"%02X%01X%05X",Opcode_get(input_2+1)+N*2+I , X*2*2*2+B*2*2+P*2+E , Loc_from_symbol(input_3+1));	ob_len[p]=strlen(ob_code[p]);
							modification_loc[++index_modification]=Loc[p];
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT4's operand is wrong\n",Line[p]);
						}
					}
					else//simple address
					{N=1;I=1;
						if(Check_already_symbol(input_3)==1)//operand is symbol
						{
							sprintf(ob_code[p],"%02X%01X%05X",Opcode_get(input_2+1)+N*2+I , X*2*2*2+B*2*2+P*2+E , Loc_from_symbol(input_3));	ob_len[p]=strlen(ob_code[p]);
							modification_loc[++index_modification]=Loc[p];
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT4's operand is wrong\n",Line[p]);
						}
					}
				}
				else if(input_4==NULL||input_4[0]=='.')//there is not Xindex
				{X=0;
					if(input_3[0]=='@')//indirect address
					{N=1;I=0;
						if(Check_already_symbol(input_3+1)==1)//operand is symbol
						{
							sprintf(ob_code[p],"%02X%01X%05X",Opcode_get(input_2+1)+N*2+I , X*2*2*2+B*2*2+P*2+E , Loc_from_symbol(input_3+1));	ob_len[p]=strlen(ob_code[p]);
							modification_loc[++index_modification]=Loc[p];
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT4's operand is wrong\n",Line[p]);
						}
					}
					else if(input_3[0]=='#')//immediate address
					{N=0;I=1;
						if(Is_decimal(input_3+1)==1)//operand is Decimal number
						{
							sscanf(input_3+1,"%d",&Decimal);
							if(0<=Decimal&&Decimal<=1048575)//check the range
							{
								sprintf(ob_code[p],"%02X%01X%05X",Opcode_get(input_2+1)+N*2+I , X*2*2*2+B*2*2+P*2+E , Decimal);	ob_len[p]=strlen(ob_code[p]);
							}
							else//error
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : FORMAT4's operand is wrong\n",Line[p]);
							}
						}
						else if(Check_already_symbol(input_3+1)==1)//operand is symbol
						{
							sprintf(ob_code[p],"%02X%01X%05X",Opcode_get(input_2+1)+N*2+I , X*2*2*2+B*2*2+P*2+E , Loc_from_symbol(input_3+1));	ob_len[p]=strlen(ob_code[p]);
							modification_loc[++index_modification]=Loc[p];
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT4's operand is wrong\n",Line[p]);
						}
					}
					else//simple address
					{N=1;I=1;
						if(Check_already_symbol(input_3)==1)//operand is symbol
						{
							sprintf(ob_code[p],"%02X%01X%05X",Opcode_get(input_2+1)+N*2+I , X*2*2*2+B*2*2+P*2+E , Loc_from_symbol(input_3));	ob_len[p]=strlen(ob_code[p]);
							modification_loc[++index_modification]=Loc[p];
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : it is not along with right FORMAT4\n",Line[p]);
						}
					}
				}
				else//error
				{
					error_flag2=1;
					sprintf(Error_2[++index_error_2],"line%d error : FORMAT4's operand is wrong\n",Line[p]);
				}
			}
		}
		else if((input1_state==0&&input2_state==11)||input1_state==11)//meet BASE
		{
			ob_len[p]=0;
			if(input1_state==11)//there is not symbol
			{
				if(Base_symbol_flag==1)//there is LDB operand symbol
				{
					if(Check_already_symbol(Base_symbol)==1)//there is already symbol
					{
						if(input_2!=NULL&&strcmp(input_2,Base_symbol)==0)
							B_loc=Loc_from_symbol(Base_symbol);
						else
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : Base operand symbol is not same as LDB's operand symbol\n",Line[p]);
						}
					}
					else//there is not already symbol
					{
						error_flag2=1;
						sprintf(Error_2[++index_error_2],"line%d error : LDB's operand symbol is not existed\n",Line[p]);
					}
				}	
				else//there is not LDB operand symbol
				{
					error_flag2=1;
					sprintf(Error_2[++index_error_2],"line%d error : there is not already right LDB'S operand symbol\n",Line[p]);
				}
			}
			else //there is symbol
			{
				if(Base_symbol_flag==1)//there is LDB operand symbol
				{
					if(Loc_from_symbol(Base_symbol)!=-1)//there is already symbol
					{
						if(input_3!=NULL&&strcmp(input_3,Base_symbol)==0)
							B_loc=Loc_from_symbol(Base_symbol);
						else
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : Base operand symbol is not same as LDB's operand symbol\n",Line[p]);
						}
					}
					else//there is not already symbol
					{
						error_flag2=1;
						sprintf(Error_2[++index_error_2],"line%d error : LDB's operand symbol is not existed\n",Line[p]);
					}
				}	
				else//there is not LDB operand symbol
				{
					error_flag2=1;
					sprintf(Error_2[++index_error_2],"line%d error : there is not right LDB'S operand symbol\n",Line[p]);
				}
			}
		}
		else if((input1_state==0&&input2_state==3)||input1_state==3)//meet FORMAT3
		{E=0;
			if((input_1!=NULL&&strcmp("RSUB",input_1)==0&&(input_2==NULL||input_2[0]=='.'))||(input_2!=NULL&&strcmp("RSUB",input_2)==0))//the case of RSUB
			{
				sprintf(ob_code[p],"4F0000");
				ob_len[p]=strlen(ob_code[p]);
			}
			else if(input1_state==3&&input_2!=NULL)//there is not symbol
			{
				if(input_3!=NULL&&strcmp("X",input_3)==0&&(input_4==NULL||input_4[0]=='.'))//there is Xindex
				{X=1;
					if(input_2[0]=='#')//immediate address
					{N=0;I=1;
						if(Is_decimal(input_2+1)==1)//operand is Decimal number
						{B=0;P=0;
							sscanf(input_2+1,"%d",&Decimal);	TA=Decimal;	Pc_loc=Loc[p]+3;	B_loc=Loc_from_symbol(Base_symbol);
							if(TA>4095)//check the range
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : FORMAT3's operand your number input is over 4095\n",Line[p]);
							}
							else
							{
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_1)+2*N+I , X*2*2*2+B*2*2+P*2+E , TA);	ob_len[p]=strlen(ob_code[p]);
							}
						}
						else if(Check_already_symbol(input_2+1)==1)//operand is symbol
						{
							Pc_loc=Loc[p]+3;	TA=Loc_from_symbol(input_2+1);	B_loc=Loc_from_symbol(Base_symbol);
							if(-2048<=TA-Pc_loc && TA-Pc_loc<=2047)//Pc relative
							{B=0;P=1;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_1)+2*N+I , X*2*2*2+B*2*2+P*2+E , Two_s_complement_result(TA,Pc_loc));	ob_len[p]=strlen(ob_code[p]);
							}
							else if(0<=TA-B_loc && TA-B_loc<=4095)//Base relative
							{B=1;P=0;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_1)+2*N+I , X*2*2*2+B*2*2+P*2+E , TA - B_loc);	ob_len[p]=strlen(ob_code[p]);
							}
							else//error
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : you need to chage FORMAT3 to FORMAT4\n",Line[p]);
							}
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT3's operand is wrong\n",Line[p]);
						}
					}
					else if(input_2[0]=='@')//indirect address
					{N=1;I=0;
						if(Check_already_symbol(input_2+1)==1)
						{
							Pc_loc=Loc[p]+3;	TA=Loc_from_symbol(input_2+1);	B_loc=Loc_from_symbol(Base_symbol);
							if(-2048<=TA - Pc_loc && TA - Pc_loc<=2047)//Pc relative
							{B=0;P=1;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_1)+2*N+I , X*2*2*2+B*2*2+P*2+E , Two_s_complement_result(TA,Pc_loc));	ob_len[p]=strlen(ob_code[p]);
							}
							else if(0<=TA-B_loc&&TA-B_loc<=4095)//Base relative
							{B=1;P=0;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_1)+2*N+I , X*2*2*2+B*2*2+P*2+E , TA-B_loc);	ob_len[p]=strlen(ob_code[p]);
							}
							else//error
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : you need to chage FORMAT3 to FORMAT4\n",Line[p]);
							}
						}
						else
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT3's operand is wrong\n",Line[p]);
						}
					}
					else//simple address
					{N=1;I=1;
						if(Check_already_symbol(input_2)==1)//operand is symbol
						{
							Pc_loc=Loc[p]+3;	TA=Loc_from_symbol(input_2);	B_loc=Loc_from_symbol(Base_symbol);
							if(-2048<= TA-Pc_loc && TA-Pc_loc <=2047)//Pc relative
							{B=0;P=1;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_1)+2*N+I , X*2*2*2+B*2*2+P*2+E , Two_s_complement_result(TA,Pc_loc));	ob_len[p]=strlen(ob_code[p]);
							}
							else if(0<=TA - B_loc && TA - B_loc<=4095)//Base relative
							{B=1;P=0;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_1)+2*N+I , X*2*2*2+B*2*2+P*2+E , TA-B_loc);	ob_len[p]=strlen(ob_code[p]);
							}
							else//error
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : you need to chage FORMAT3 to FORMAT4\n",Line[p]);
							}
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT3's operand is wrong\n",Line[p]);
						}
					}
				}
				else if(input_2!=NULL&&(input_3==NULL||input_3[0]=='.'))//there is not Xindex
				{X=0;
					if(input_2[0]=='#')//immediate address
					{N=0;I=1;
						if(Is_decimal(input_2+1)==1)//operand is Decimal number
						{B=0;P=0;
							sscanf(input_2+1,"%d",&Decimal);	Pc_loc=Loc[p]+3; TA=Decimal;	B_loc=Loc_from_symbol(Base_symbol);
							if(TA>4095)//check the range
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : FORMAT3's operand your number input is over 4095\n",Line[p]);
							}
							else//error
							{
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_1)+2*N+I , X*2*2*2+B*2*2+P*2+E , TA);	ob_len[p]=strlen(ob_code[p]);
							}
						}
						else if(Check_already_symbol(input_2+1)==1)//operand is symbol
						{
							Pc_loc=Loc[p]+3;	TA=Loc_from_symbol(input_2+1);	B_loc=Loc_from_symbol(Base_symbol);
							if(-2048<= TA-Pc_loc && TA-Pc_loc <=2047)//Pc relative
							{B=0;P=1;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_1)+2*N+I , X*2*2*2+B*2*2+P*2+E , Two_s_complement_result(TA,Pc_loc));	ob_len[p]=strlen(ob_code[p]);
							}
							else if(0<=TA-B_loc&&TA-B_loc<=4095)//Base relative
							{B=1;P=0;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_1)+2*N+I , X*2*2*2+B*2*2+P*2+E , TA-B_loc);	ob_len[p]=strlen(ob_code[p]);
							}
							else//error
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : you need to chage FORMAT3 to FORMAT4\n",Line[p]);
							}
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT3's operand is wrong\n",Line[p]);
						}
					}
					else if(input_2[0]=='@')//indirect address
					{N=1;I=0;
						if(Check_already_symbol(input_2+1)==1)//operand is symbol
						{
							Pc_loc=Loc[p]+3;	TA=Loc_from_symbol(input_2+1);	B_loc=Loc_from_symbol(Base_symbol);
							if(-2048<=TA - Pc_loc && TA - Pc_loc <=2047)//Pc relative
							{B=0;P=1;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_1)+2*N+I , X*2*2*2+B*2*2+P*2+E , Two_s_complement_result(TA,Pc_loc));	ob_len[p]=strlen(ob_code[p]);
							}
							else if(0<=TA-B_loc&&TA-B_loc<=4095)//Base relative
							{B=1;P=0;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_1)+2*N+I , X*2*2*2+B*2*2+P*2+E , TA-B_loc);	ob_len[p]=strlen(ob_code[p]);
							}
							else//error
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : you need to chage FORMAT3 to FORMAT4\n",Line[p]);
							}
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT3's operand is wrong\n",Line[p]);
						}
					}
					else//simple address
					{N=1;I=1;
						if(Check_already_symbol(input_2)==1)//operand is symbol
						{
							Pc_loc=Loc[p]+3;	TA=Loc_from_symbol(input_2); B_loc=Loc_from_symbol(Base_symbol);

							if(-2048<=TA-Pc_loc&&TA-Pc_loc<=2047)//Pc relative
							{B=0;P=1;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_1)+2*N+I , X*2*2*2+B*2*2+P*2+E , Two_s_complement_result(TA,Pc_loc));	ob_len[p]=strlen(ob_code[p]);
							}
							else if(0<=TA-B_loc&&TA-B_loc<=4095)//Base relative
							{B=1;P=0;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_1)+2*N+I , X*2*2*2+B*2*2+P*2+E , TA-B_loc);	ob_len[p]=strlen(ob_code[p]);
							}
							else//error
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : you need to chage FORMAT3 to FORMAT4\n",Line[p]);
							}
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT3's operand is wrong\n",Line[p]);
						}
					}
				}
				else//error
				{
					error_flag2=1;
					sprintf(Error_2[++index_error_2],"line%d error : it is not along with right FORMAT3 form\n",Line[p]);
				}
			}
			else//there is symbol
			{
				if(input_3!=NULL&&input_4!=NULL&&strcmp("X",input_4)==0&&(input_5==NULL||input_5[0]=='.'))//there is Xindex
				{X=1;
					if(input_3[0]=='#')//immediate address
					{N=0;I=1;
						if(Is_decimal(input_3+1)==1)//operand is Decimal number
						{B=0;P=0;
							sscanf(input_3+1,"%d",&Decimal);	Pc_loc=Loc[p]+3; TA=Decimal;	B_loc=Loc_from_symbol(Base_symbol);
							if(TA>4095)//check the range
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : FORMAT3's operand your number input is over 4095\n",Line[p]);
							}
							else
							{
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_2)+2*N+I , X*2*2*2+B*2*2+P*2+E , TA);	ob_len[p]=strlen(ob_code[p]);
							}
						}
						else if(Check_already_symbol(input_3+1)==1)//operand is symbol
						{
							Pc_loc=Loc[p]+3;	TA=Loc_from_symbol(input_3+1);	B_loc=Loc_from_symbol(Base_symbol);
							if(-2048<=TA- Pc_loc && TA-Pc_loc <=2047)//Pc relative
							{B=0;P=1;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_2)+2*N+I , X*2*2*2+B*2*2+P*2+E , Two_s_complement_result(TA,Pc_loc));	ob_len[p]=strlen(ob_code[p]);
							}
							else if(0<=TA-B_loc&&TA-B_loc<=4095)//Base relative
							{B=1;P=0;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_2)+2*N+I , X*2*2*2+B*2*2+P*2+E , TA-B_loc);	ob_len[p]=strlen(ob_code[p]);
							}
							else//error
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : you need to chage FORMAT3 to FORMAT4\n",Line[p]);
							}
						}
						else
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT3's operand is wrong\n",Line[p]);
						}
					}
					else if(input_3[0]=='@')//indirect address
					{N=1;I=0;
						if(Check_already_symbol(input_3+1)==1)//operand is symbol
						{
							Pc_loc=Loc[p]+3;	TA=Loc_from_symbol(input_3+1);	B_loc=Loc_from_symbol(Base_symbol);
							if(-2048<=TA-Pc_loc&&TA-Pc_loc<=2047)//Pc relative
							{B=0;P=1;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_2)+2*N+I , X*2*2*2+B*2*2+P*2+E , Two_s_complement_result(TA,Pc_loc));	ob_len[p]=strlen(ob_code[p]);
							}
							else if(0<=TA-B_loc&&TA-B_loc<=4095)//Base relative
							{B=1;P=0;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_2)+2*N+I , X*2*2*2+B*2*2+P*2+E , TA-B_loc);	ob_len[p]=strlen(ob_code[p]);
							}
							else//error
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : you need to chage FORMAT3 to FORMAT4\n",Line[p]);
							}
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT3's operand is wrong\n",Line[p]);
						}
					}
					else//simple address
					{N=1;I=1;
						if(Check_already_symbol(input_3)==1)//operand is symbol
						{
							Pc_loc=Loc[p]+3;	TA=Loc_from_symbol(input_3);	B_loc=Loc_from_symbol(Base_symbol);
							if(-2048<=TA-Pc_loc&&TA-Pc_loc<=2047)//Pc relative
							{B=0;P=1;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_2)+2*N+I , X*2*2*2+B*2*2+P*2+E , Two_s_complement_result(TA,Pc_loc));	ob_len[p]=strlen(ob_code[p]);
							}
							else if(0<=TA-B_loc&&TA-B_loc<=4095)//Base relative
							{B=1;P=0;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_2)+2*N+I , X*2*2*2+B*2*2+P*2+E , TA-B_loc);	ob_len[p]=strlen(ob_code[p]);
							}
							else//error
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : you need to chage FORMAT3 to FORMAT4\n",Line[p]);
							}
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT3's operand is wrong\n",Line[p]);
						}
					}
				}
				else if(input_3!=NULL&&(input_4==NULL||input_4[0]=='.'))//there is not Xindex
				{X=0;
					if(input_3[0]=='#')//immediate address
					{N=0;I=1;
						if(Is_decimal(input_3+1)==1)//operand is Decimal number
						{B=0;P=0;
							sscanf(input_3+1,"%d",&Decimal);	Pc_loc=Loc[p]+3; TA=Decimal;	B_loc=Loc_from_symbol(Base_symbol);
							if(TA>4095)//check the range
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : FORMAT3's operand your number input is over 4095\n",Line[p]);
							}
							else//error
							{
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_2)+2*N+I , X*2*2*2+B*2*2+P*2+E , TA);	ob_len[p]=strlen(ob_code[p]);
							}
						}
						else if(Check_already_symbol(input_3+1)==1)//operand is symbol
						{
							Pc_loc=Loc[p]+3;	TA=Loc_from_symbol(input_3+1);	B_loc=Loc_from_symbol(Base_symbol);
							if(-2048<=TA - Pc_loc && TA - Pc_loc<=2047)//Pc relative
							{B=0;P=1;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_2)+2*N+I , X*2*2*2+B*2*2+P*2+E , Two_s_complement_result(TA,Pc_loc));	ob_len[p]=strlen(ob_code[p]);
							}
							else if(0<=TA-B_loc&&TA-B_loc<=4095)//Base relative
							{B=1;P=0;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_2)+2*N+I , X*2*2*2+B*2*2+P*2+E , TA-B_loc);	ob_len[p]=strlen(ob_code[p]);
							}
							else//error
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : you need to chage FORMAT3 to FORMAT4\n",Line[p]);
							}
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT3's operand is wrong\n",Line[p]);
						}
					}
					else if(input_3[0]=='@')//indirect address
					{N=1;I=0;
						if(Check_already_symbol(input_3+1)==1)//operand is symbol
						{
							Pc_loc=Loc[p]+3;	TA=Loc_from_symbol(input_3+1);	B_loc=Loc_from_symbol(Base_symbol);
							if(-2048<=TA - Pc_loc && TA-Pc_loc<=2047)//Pc relative
							{B=0;P=1;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_2)+2*N+I , X*2*2*2+B*2*2+P*2+E , Two_s_complement_result(TA,Pc_loc));	ob_len[p]=strlen(ob_code[p]);
							}
							else if(0<=TA-B_loc&&TA-B_loc<=4095)//Base relative
							{B=1;P=0;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_2)+2*N+I , X*2*2*2+B*2*2+P*2+E , TA-B_loc);	ob_len[p]=strlen(ob_code[p]);
							}
							else//error
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : you need to chage FORMAT3 to FORMAT4\n",Line[p]);
							}
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT3's operand is wrong\n",Line[p]);
						}
					}
					else//simple address
					{N=1;I=1;
						if(Check_already_symbol(input_3)==1)//operand is symbol
						{
							Pc_loc=Loc[p]+3;	TA=Loc_from_symbol(input_3);
							B_loc=Loc_from_symbol(Base_symbol);
							if(-2048<=TA - Pc_loc && TA - Pc_loc<=2047)//Pc relative
							{B=0;P=1;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_2)+2*N+I , X*2*2*2+B*2*2+P*2+E , Two_s_complement_result(TA,Pc_loc));	ob_len[p]=strlen(ob_code[p]);
							}
							else if(0<=TA-B_loc&&TA-B_loc<=4095)//Base relative
							{B=1;P=0;
								sprintf(ob_code[p],"%02X%01X%03X",Opcode_get(input_2)+2*N+I , X*2*2*2+B*2*2+P*2+E , TA-B_loc);	ob_len[p]=strlen(ob_code[p]);
							}
							else//error
							{
								error_flag2=1;
								sprintf(Error_2[++index_error_2],"line%d error : you need to chage FORMAT3 to FORMAT4\n",Line[p]);
							}
						}
						else//error
						{
							error_flag2=1;
							sprintf(Error_2[++index_error_2],"line%d error : FORMAT3's operand is wrong\n",Line[p]);
						}
					}
				}
				else//error
				{
					error_flag2=1;
					sprintf(Error_2[++index_error_2],"line%d error : it is not along with right FORMAT3 form\n",Line[p]);
				}
			}
		}
		else//error
		{
			error_flag2=1;
			sprintf(Error_2[++index_error_2],"line%d error : it is not right code\n",Line[p]);
		}
	}

	if(error_flag2==1)//if it has error print the error
	{
		for(i=0;i<=index_error;i++)
			printf("%s",Error[i]);
		for(i=0;i<=index_error_2;i++)
			printf("%s",Error_2[i]);
		Free_symbol_table();
		printf("line error : your assem code has error please check your code please\n");
		return;
	}
	
	fp_w_lst=fopen(filename_lst,"wt");//file open to write list file
	for(i=0;i<=index;i++)//write list file
	{
		len=strlen(Code[i]);
		if(2<=len)
			Code[i][len-1]='\0';
		if(i==index&&strcmp("\n",Code[index])==0)
			continue;
		if(Loc[i]!=-1 && ob_len[i]!=-1&&ob_len[i]!=0)//print all information of line
			fprintf(fp_w_lst,"\t%d\t%04X\t%-80s\t%s\n",Line[i],Loc[i],Code[i],ob_code[i]);
		else if(Loc[i]==-1 && ob_len[i]!=-1&&ob_len[i]!=0)//print the information except location
			fprintf(fp_w_lst,"\t%d\t    \t%-80s\t%s\n",Line[i],Code[i],ob_code[i]);
		else if(Loc[i]!=-1 && (ob_len[i]==0||ob_len[i]==-1))//print the information except object code
			fprintf(fp_w_lst,"\t%d\t%04X\t%-80s\n",Line[i],Loc[i],Code[i]);
		else//print the information except location and object code
			fprintf(fp_w_lst,"\t%d\t\t%-80s\n",Line[i],Code[i]);
	}
	fclose(fp_w_lst);
	//make object file
	fp_w_ob=fopen(filename_obj,"wt");
	fprintf(fp_w_ob,"H%-6s%06X%06X",program_name,start_loc,end_loc-start_loc);//file print the head
	
	count=0;
	first_flag=0;//indicate first object code
	obj_index=0;
	
	for(i=0;i<1000;i++)
		object_code[i][0]='\0';
	i=0;
	while(1)
	{
		if(i==index)
		{
			if(ob_len[i]!=0&&ob_len[i]!=-1)
			{
				if(count+ob_len[i]<=60)
				{
					strcat(object_code[obj_index],ob_code[i]);
				}
				else
				{
					obj_index++;
					start_loc_print[obj_index]=Loc[i];
					strcpy(object_code[obj_index],ob_code[i]);
				}
			}

			break;
		}

		if(first_flag==0)//meet first object code
		{
			if(ob_len[i]==0)
				i++;
			else if(ob_len[i]==-1)
				i++;
			else
			{
				start_loc_print[obj_index]=Loc[i];
				strcpy(object_code[obj_index],ob_code[i]);	count+=ob_len[i];
				i++;
				first_flag=1;
			}
		}
		else
		{
			if(ob_len[i]==0)
				i++;
			else if(ob_len[i]==-1)
			{
				obj_index++;
				i++;
				first_flag=0;
				count=0;
			}
			else
			{
				if(count+ob_len[i]<=60)
				{
					strcat(object_code[obj_index],ob_code[i]);	count+=ob_len[i];
					i++;
				}
				else
				{
					obj_index++;
					first_flag=0;
					count=0;
				}
			}
		}
	}
	for(i=0;i<=obj_index;i++)
		fprintf(fp_w_ob,"\nT%06X%02X%s",start_loc_print[i],(unsigned)strlen(object_code[i])/(unsigned)2,object_code[i]);
	if(index_modification!=-1)//file print the modification
	{
		for(i=0;i<=index_modification;i++)
			fprintf(fp_w_ob,"\nM%06X05",modification_loc[i]-start_loc+1);
	}
	fprintf(fp_w_ob,"\nE%06X\n",start_loc);//file print the end
	fclose(fp_w_ob);
	printf("\t    output file : [%s] , [%s]\n",filename_lst,filename_obj);
}
int Differentiate_2(char* Target)
{
	char Target_change[10];//if there is '+' at Target[0] , remove '+'
	Hash* temp;//searching for hash table
	int plus_flag;//Determine Target[0] is '+'
	int format;//Determine the format of mnemonic
	int index;//for hash_buckets
	int i;//index for loop

	temp=NULL; plus_flag=0; format=0;
	
	if(Target==NULL)
		return -4;//if NULL , 

	if(Target[0] == '+')//remove the '+'
	{
		strcpy(Target_change,(Target+1));	
		plus_flag=1;
	}
	else
		strcpy(Target_change,Target);

	if(strcmp("START",Target_change)==0)//Determine whether Directive
		return 5;//if "START" Directive , 
	else if(strcmp("END",Target_change)==0)
		return 6;//if "END" Directive , 
	else if(strcmp("BYTE",Target_change)==0)
		return 7;//if "BYTE" Directive , 
	else if(strcmp("RESB",Target_change)==0)
		return 8;//if "RESB" Directive , 
	else if(strcmp("WORD",Target_change)==0)
		return 9;//if "WORD" Directive , 
	else if(strcmp("RESW",Target_change)==0)
		return 10;//if "RESW" Directive , 
	else if(strcmp("BASE",Target_change)==0)
		return 11;//if "BASE" Directive , 

	index=Hash_function(Target_change);//Determine it is menemoc
	temp=hash_buckets[index];

	while(1)
	{
		if(temp==NULL)
			break;
		if(strcmp(temp->mnemonic,Target_change)==0)
		{
			
			sscanf(temp->format,"%d",&format);
		
			if(format==1)
				return 1;//if mnemonic is format 1 , 
			else if(format==2)
				return 2;//if mnemonic is format 2 , 
			else
			{
				if(plus_flag!=0)
				{
					return 4;//if mnemonic is format 3 , 
				}
				else
					return 3;//if mnemonic is formet 4 , 
			}
		}
		temp=temp->next;
	}

	if('A'>Target[0]||Target[0]>'Z')
		return -1;//it is not along with symbol format

	for(i=1;i<strlen(Target);i++)
	{
		if(('0'<=Target[i]&&Target[i]<='9')||('A'<=Target[i]&&Target[i]<='Z'))
			continue;
		else
			return -1;//it is not along with symbol format
	}
	if(Is_mn_or_di(Target)!=1)
	return -3;

	return 0;//it is symbol

}
int Register_num_get(char* Target)
{
	if(Target==NULL)
		return -1;//NULL
	if(strcmp("A",Target)==0)
		return 0;//A register
	if(strcmp("X",Target)==0)
		return 1;//X register
	if(strcmp("L",Target)==0)
		return 2;//L register
	if(strcmp("B",Target)==0)
		return 3;//B register
	if(strcmp("S",Target)==0)
		return 4;//S register
	if(strcmp("T",Target)==0)
		return 5;//T register
	if(strcmp("F",Target)==0)
		return 6;//F register
	if(strcmp("PC",Target)==0)
		return 8;//PC register
	if(strcmp("SW",Target)==0)
		return 9;//SW register
	return -1;//not register
}
int Opcode_get(char* Target)
{
	int index;
	Hash* temp;
	if(Target==NULL)
		return -1;
	index=Hash_function(Target);//get the hash table index
	temp=hash_buckets[index];
	while(1)
	{
		if(temp==NULL)
			break;
		if(strcmp(Target,temp->mnemonic)==0)
			return temp->opcode;
		temp=temp->next;
	}
	return -1;
}
void Print_Symbol()
{
	Hash_symbol* temp;
	int flag=0;
	int i;
	for(i=25;i>0;i--)
	{
		temp=symbol_buckets[i];
		if(temp==NULL)//to go to another bucket
			continue;
		while(1)
		{
			if(temp==NULL)
				break;
			printf("\t%s\t%04X\n",temp->symbol,temp->loc);//print the symbol location
			flag++;
			temp=temp->next;
		}
	}
	if(flag==0)
		printf("There is no symbols\n");
}

int Is_register(char* Target)
{
	if(Target==NULL)
		return 0;
	if(strcmp(Target,"A")==0 || strcmp(Target,"X")==0 || strcmp(Target,"L")==0 || strcmp(Target,"PC")==0 || strcmp(Target,"SW")==0 ||strcmp(Target,"B")==0 ||strcmp(Target,"S")==0 ||strcmp(Target,"T")==0 ||strcmp(Target,"F")==0 )
		return 1;
	else
		return 0;
}
int Check_FORM1(char* Input_1,char* Input_2,char* Input_3)
{
	if(Differentiate(Input_1)==0&&Differentiate(Input_2)==1&& (Input_3==NULL||Input_3[0]=='.'))
		return 1;
	else if(Differentiate(Input_1)==1&& (Input_2==NULL||Input_2[0]=='.'))
		return 1;
	else
		return 0;
}
int Check_FORM2(char* Input_1,char* Input_2,char* Input_3,char* Input_4,char* Input_5,int coma_count)
{
	if(strcmp("CLEAR",Input_1)==0 && Input_2!=NULL && Is_register(Input_2)==1 && (Input_3==NULL||Input_3[0]=='.'))
		return 1;
	else if(Differentiate(Input_1)==0 && Input_2!=NULL&&strcmp("CLEAR",Input_2)==0 && Input_3!=NULL && Is_register(Input_3)==1 && (Input_4==NULL||Input_4[0]=='.'))
		return 1;
	else if(strcmp("SVC",Input_1)==0 && Input_2!=NULL && Is_decimal(Input_2)==1 && (Input_3==NULL||Input_3[0]=='.'))
		return 1;
	else if(Differentiate(Input_1)==0 && Input_2!=NULL&&strcmp("SVC",Input_2)==0 && Input_3!=NULL && Is_decimal(Input_3)==1 && (Input_4==NULL||Input_4[0]=='.'))
		return 1;
	else if(strcmp("TIXR",Input_1)==0 && Is_register(Input_2)==1 && (Input_3==NULL||Input_3[0]=='.'))
		return 1;
	else if(Differentiate(Input_1)==0 && Input_2!=NULL&&strcmp("TIXR",Input_2)==0 && Is_register(Input_3)==1 && (Input_4==NULL||Input_4[0]=='.'))
		return 1;
	else if(Differentiate(Input_1)==0)
	{
		if(Input_2!=NULL&&(strcmp("SHIFTL",Input_2)==0||strcmp("SHIFTR",Input_2)==0) && Is_register(Input_3)==1 && Is_decimal(Input_4)==1 && (Input_5==NULL||Input_5[0]=='.'))
		{
			if(coma_count!=1)
				return 0;
			return 1;
		}
		else if(Input_2!=NULL&&(strcmp("CLEAR",Input_2)==0||strcmp("TIXR",Input_2)==0) && Is_register(Input_3)==1 && (Input_4==NULL||Input_4[0]=='.'))
			return 1;
		else if(Input_2!=NULL&&strcmp("SVC",Input_2)==0 && Is_decimal(Input_3)==1 && (Input_4==NULL||Input_4[0]=='.'))
			return 1;
		else if(Differentiate(Input_2)==2 && Is_register(Input_3)==1 && Is_register(Input_4)==1 &&(Input_5==NULL||Input_5[0]=='.'))
		{
			if(coma_count!=1)
				return 0;
			return 1;
		}
		else 
			return 0;
	}
	else if(Differentiate(Input_1)==2)
	{
		if(Input_1!=NULL&&(strcmp("SHIFTL",Input_1)==0||strcmp("SHIFTR",Input_1)==0) && Is_register(Input_2)==1 && Is_decimal(Input_3)==1 && (Input_4==NULL||Input_4[0]=='.'))
		{
			if(coma_count!=1)
				return 0;
			return 1;
		}
		else if(Input_1!=NULL&&(strcmp("CLEAR",Input_1)==0||strcmp("TIXR",Input_1)==0) && Is_register(Input_2)==1 && (Input_3==NULL||Input_3[0]=='.'))
			return 1;
		else if(Input_1!=NULL&&strcmp("SVC",Input_1)==0 && Is_decimal(Input_2)==1 && (Input_3==NULL||Input_3[0]=='.'))
			return 1;
		else if(Differentiate(Input_1)==2 && Is_register(Input_2)==1 && Is_register(Input_3)==1 &&(Input_4==NULL||Input_4[0]=='.'))
		{
			if(coma_count!=1)
				return 0;
			return 1;
		}
		else 
			return 0;
	}
	return 0;
}
int Check_FORM3(char* Input_1,char* Input_2,char* Input_3,char* Input_4,char* Input_5)
{
	if(Differentiate(Input_1)==0)//there is symbol
	{
		if(Input_2!=NULL&&strcmp("RSUB",Input_2)==0 && (Input_3==NULL||Input_3[0]=='.'))
			return 1;
		else if( Differentiate(Input_2)==3 && ( ( Input_3!=NULL && ( Input_4==NULL||Input_4[0]=='.' ) ) || ( ( Input_3!=NULL&&Input_4!=NULL&&strcmp("X",Input_4 )==0 )&&( Input_5==NULL||Input_5[0]=='.' ) ) ) )
			return 1;
		else 
			return 0;
	}
	else if(Differentiate(Input_1)==3)//there is not symbol
	{
		if(Input_1!=NULL&&strcmp("RSUB",Input_1)==0 && (Input_3==NULL||Input_3[0]=='.'))
			return 1;
		else if( Differentiate(Input_1)==3 && ( ( Input_2!=NULL && ( Input_3==NULL||Input_3[0]=='.' ) ) || ( ( Input_2!=NULL&&Input_3!=NULL&&strcmp("X",Input_3 )==0 )&&( Input_4==NULL||Input_4[0]=='.' ) ) ) )
			return 1;
		else 
			return 0;
	}
	return 0;
}
int Check_FORM4(char* Input_1,char* Input_2,char* Input_3,char* Input_4,char* Input_5)
{
	if(Differentiate(Input_1)==0)//there is symbol
	{
		if(Input_2!=NULL&&strcmp("RSUB",(Input_2+1))==0 && (Input_3==NULL||Input_3[0]=='.'))
			return 1;
		else if(Differentiate((Input_2+1))==3 && Input_3!=NULL && (Input_4==NULL||Input_4[0]=='.'))
			return 1;
		else if(Differentiate(Input_2+1)==3 && Input_3!=NULL && Input_4!=NULL && strcmp("X",Input_4+1)==0 && (Input_5==NULL||Input_5[0]=='.'))
			return 1;
		else 
			return 0;
	}
	else if(Differentiate((Input_1+1))==3)//there is not symbol
	{
		if(Input_1!=NULL&&strcmp("RSUB",(Input_1+1))==0 && (Input_2==NULL||Input_2[0]=='.'))
			return 1;
		else if(Differentiate((Input_1+1))==3 && (Input_2!=NULL&&Input_2[0]!='.') && (Input_3==NULL||Input_3[0]=='.'))
			return 1;
		else if(Differentiate(Input_1+1)==3 && Input_2!=NULL && Input_3!=NULL && strcmp("X",Input_3+1)==0 && (Input_4==NULL||Input_4[0]=='.'))
			return 1;
		else 
			return 0;
	}
	return 0;
}
int Check_START5(char* Input_1,char* Input_2,char* Input_3,char* Input_4)
{
	 if(Differentiate(Input_1)==0 && Differentiate(Input_2)==5 && Is_hexa(Input_3)==1 &&(Input_4==NULL||Input_4[0]=='.'))
		return 1;
	else
		return 0;
}
int Check_END6(char* Input_1,char* Input_2,char* Input_3,char* Input_4,char* first_symbol)
{
	if(Differentiate(Input_1)==6)//if END line does not have symbol
	{
		if(Input_2==NULL || Input_2[0]=='.')//if END line does not have symbol operand
			return 1;
		else if(first_symbol!=NULL &&Input_2!=NULL&& strcmp(Input_2,first_symbol)==0 && (Input_3==NULL||Input_3[0]=='.'))//if END line has symbol operand , this should be same as first symbol at first mnemonic
			return 1;
		else
			return 0;
	}
	else
		return 0;
}
int Check_RESB8(char* Input_1,char* Input_2,char* Input_3,char* Input_4)
{
	if(Differentiate(Input_1)==0 && Differentiate(Input_2)==8 && Is_decimal(Input_3)==1 && (Input_4==NULL||Input_4[0]=='.'))
		return 1;
	else if(Differentiate(Input_1)==8 && Is_decimal(Input_2)==1 && (Input_3==NULL||Input_3[0]=='.'))
		return 1;
	else
		return 0;
}
int Check_WORD9(char* Input_1,char* Input_2,char* Input_3,char* Input_4)
{
	if(Differentiate(Input_1)==0 && Differentiate(Input_2)==9 && Is_decimal(Input_3)==1 && (Input_4==NULL||Input_4[0]=='.'))
		return 1;
	else if(Differentiate(Input_1)==9 && Is_decimal(Input_2)==1 && (Input_3==NULL||Input_3[0]=='.'))
		return 1;
	else
		return 0;
}
int Check_RESW10(char* Input_1,char* Input_2,char* Input_3,char* Input_4)
{
	if(Differentiate(Input_1)==0 && Differentiate(Input_2)==10 && Is_decimal(Input_3)==1 && (Input_4==NULL||Input_4[0]=='.'))
		return 1;
	else if(Differentiate(Input_1)==10 && Is_decimal(Input_2)==1 && (Input_3==NULL||Input_3[0]=='.'))
		return 1;
	else
		return 0;
}
int Is_decimal(char* Target)
{
	int i;
	if(Target==NULL)
		return 0;
	for(i=0;i<strlen(Target);i++)
	{
		if('0'<=Target[i]&&Target[i]<='9')
			continue;
		else
			return 0;
	}
	return 1;
}
int Is_hexa(char* Target)
{
	int i;//count for loop
	if(Target==NULL)
		return 0;
	for(i=0;i<strlen(Target);i++)
	{
		if(('0'<=Target[i]&&Target[i]<='9') || ('A'<=Target[i]&&Target[i]<='F'))
			continue;
		else
			return 0;
	}
	return 1;
}
int Is_mn_or_di(char* Target)
{
	Hash* temp;
	int index;//index
	if(Target==NULL)
		return 2;//if NULL
	if(strcmp(Target,"START")==0 || strcmp(Target,"END")==0 || strcmp(Target,"BYTE")==0 || strcmp(Target,"RESB")==0 || strcmp(Target,"WORD")==0 || strcmp(Target,"RESW")==0)
		return -1;//if DIRECTIVE  
	if(strcmp(Target,"BASE")==0)
		return -2;//if BASE

	index=Hash_function(Target);
	temp=hash_buckets[index];
	while(1)
	{
		if(temp==NULL)
			break;

		if(strcmp(temp->mnemonic,Target)==0)
			return 0;
		temp=temp->next;
	}
	return 1;//it is not mnemonic and DIRECTIVE  
}
int Check_already_symbol(char* Target)
{
	int index;
	Hash_symbol* temp;
	if(Target==NULL)
		return 0;
	index=Target[0]-'A';
	temp=symbol_buckets[index];
	while(1)
	{
		if(temp==NULL)
			break;
		if(strcmp(temp->symbol,Target)==0)
			return 1;//there is same symbol in symbol table 
		temp=temp->next;
	}
	return 0;
}
int Loc_from_symbol(char* Target)
{
	int index;
	Hash_symbol* temp;//searching about symbol table   
	if(Target==NULL)
		return 0;
	index=Target[0]-'A';
	if(index<0)//if index is wrong
		return 0;
	temp=symbol_buckets[index];
	while(1)
	{
		if(temp==NULL)
			break;
		if(strcmp(temp->symbol,Target)==0)
			return temp->loc;
		temp=temp->next;
	}
	return -1;//there is not same symbol
}
int Symbol_table_make(char*Symbol,int loc)
{
	int index;
	Hash_symbol* New_node;
	Hash_symbol* temp;
	if(Symbol==NULL)
		return -2;

	New_node=(Hash_symbol*)malloc(sizeof(Hash_symbol));
	New_node->prev=NULL;	New_node->next=NULL;	New_node->loc = loc;	strcpy(New_node->symbol,Symbol);

	if('A'>Symbol[0] || Symbol[0]>'Z')
	{
		free(New_node);
		return -1;//error Because first Symbol's element is not alphabet
	}

	if(Differentiate(Symbol)!=0)//it is not symbol format
	{
		free(New_node);
		return -1;
	}
	index=Symbol[0]-'A';

	if(symbol_buckets[index]==NULL)
	{
		symbol_buckets[index]=New_node;
		return 1;
	}
	else
	{
		temp=symbol_buckets[index];

		if(strcmp(Symbol,temp->symbol)>0)
		{
			New_node->next=temp;	temp->prev=New_node;	symbol_buckets[index]=New_node;
			return 1;
		}
		else if(strcmp(Symbol,temp->symbol)==0)
		{free(New_node);
			return 0;//error Because same symbol
		}
		else
		{
			while(1)
			{
				if(temp->next == NULL)
					break;
				temp=temp->next;

				if(strcmp(Symbol,temp->symbol)==0)
				{free(New_node);
					return 0;//error Because same symbol
				}
				else if(strcmp(Symbol,temp->symbol)>0)
				{
					temp->prev->next=New_node;
					New_node->prev=temp->prev;
					New_node->next=temp;
					temp->prev=New_node;
					return 1;//Input the node success
				}
			}
			temp->next=New_node;
			New_node->prev=temp;
			return 1;//Input the node success
		}
	}
}
void Free_symbol_table()
{
	Hash_symbol* temp;//pointer for searching symbol table
	Hash_symbol* free_target;//free target
	int i;
	for(i=0;i<26;i++)
	{
		temp=symbol_buckets[i];
		while(1)
		{
			if(temp==NULL)
				break;

			free_target=temp;
			temp=temp->next;
			free(free_target);
		}
		symbol_buckets[i]=NULL;//symbol buckets to vacant
	}
}
int Differentiate(char* Target)
{
	char Target_change[10];//if there is '+' at Target[0] , remove '+'
	Hash* temp;//searching for hash table
	int plus_flag;//Determine Target[0] is '+'
	int format;//Determine the format of mnemonic
	int index;//for hash_buckets
	int i;//index for loop

	temp=NULL; plus_flag=0; format=0;
	
	if(Target==NULL)
		return -4;//if NULL , 

	if(Target[0] == '+')//remove the '+'
	{
		strcpy(Target_change,(Target+1));	
		plus_flag=1;
	}
	else
		strcpy(Target_change,Target);

	if(strcmp("START",Target_change)==0)//Determine whether Directive
		return 5;//if "START" Directive , 
	else if(strcmp("END",Target_change)==0)
		return 6;//if "END" Directive , 
	else if(strcmp("BYTE",Target_change)==0)
		return 7;//if "BYTE" Directive , 
	else if(strcmp("RESB",Target_change)==0)
		return 8;//if "RESB" Directive , 
	else if(strcmp("WORD",Target_change)==0)
		return 9;//if "WORD" Directive , 
	else if(strcmp("RESW",Target_change)==0)
		return 10;//if "RESW" Directive , 
	else if(strcmp("BASE",Target_change)==0)
		return 11;//if "BASE" Directive , 

	index=Hash_function(Target_change);//Determine it is menemoc
	temp=hash_buckets[index];

	while(1)
	{
		if(temp==NULL)
			break;
		if(strcmp(temp->mnemonic,Target_change)==0)
		{
			
			sscanf(temp->format,"%d",&format);
		
			if(format==1)
				return 1;//if mnemonic is format 1 , 
			else if(format==2)
				return 2;//if mnemonic is format 2 , 
			else
			{
				if(plus_flag!=0)
				{
					return 4;//if mnemonic is format 3 , 
				}
				else
					return 3;//if mnemonic is formet 4 , 
			}
		}
		temp=temp->next;
	}

	if('A'>Target[0]||Target[0]>'Z')
		return -1;//it is not along with symbol format

	for(i=1;i<strlen(Target);i++)
	{
		if(('0'<=Target[i]&&Target[i]<='9')||('A'<=Target[i]&&Target[i]<='Z'))
			continue;
		else
			return -1;//it is not along with symbol format
	}
	if(Check_already_symbol(Target)==1)
		return -2;
	if(Is_mn_or_di(Target)!=1)
		return -3;
	return 0;//it is symbol
}
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
			if(Input[i] != '	' && Input[i] != ' ')
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
	printf("assemble filename\n");
	printf("type filename\n");
	printf("symbol\n");
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
	else if(Input_change[0] == 't' && Input_change[1] == 'y' && Input_change[2] == 'p' && Input_change[3] == 'e' && Input_change[4] == ' ')//if "type filename"mnemonic 
	{
		len = strlen(Input_change);
		for(i=0 ; i < len ; i++)
		{
			if(Input_change[i] == ' ')
				space_count++;
		}

		if(space_count == 1)
			return 12;
		else
			return -1;
	}
	else if(Input_change[0] == 'a'&&Input_change[1] == 's'&&Input_change[2] == 's'&&Input_change[3] == 'e'&&Input_change[4] == 'm'&&Input_change[5] == 'b'&&Input_change[6] == 'l'&&Input_change[7] == 'e'&& Input_change[8] == ' ')
	{//if "assemble filename"mnemonic   
		len = strlen(Input_change);
		for(i=0 ; i < len ; i++)
		{
			if(Input_change[i] == ' ')
				space_count++;
		}

		if(space_count == 1)
			return 13;
		else
			return -1;
	}
	else if(strcmp("symbol",Input_change)==0)
	{
		return 14;
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
		printf("Error Opcode_print : mnemonic input is error\n");
	else
		printf("opcode is %X\n",temp->opcode);
}
void type_print(char* Input_change)
{
	char Input_1_[6];
	char Input_2_[INPUT_LIMIT];
	FILE* fp;
	int ret;
	
	ret =1;

	sscanf(Input_change,"%s%s",Input_1_,Input_2_);

	fp=fopen(Input_2_,"rt");

	if(fp == NULL)
	{
		printf("There is not the file that is same as user's input\n");
	}
	else
	{
		while(1)
		{
			if(ret == EOF)
				break;
			else
				printf("%c",ret);
			ret = fgetc(fp);
		}
		fclose(fp);
	}
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
		for(i=0;i<65536;i++)
					free(Memory[i]);
		free(Memory);
		free_Input_opctext(opcode,mnemonic,format);
		return 0;
	}

	for(i = 0 ; i < BUCKET_SIZE ; i++)
		hash_buckets[i] = NULL;
	Make_hash_table_function(hash_buckets,opcode,mnemonic,format);

	for(i=0;i<26;i++)
		symbol_buckets[i] = NULL;

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
			case 12://input "type filename"
				History_made(&History_head,&History_index,Input);
				type_print(Input_change);
				free(Input);
				free(Input_change);
				break;
			case 13://input "assemble filename"
				History_made(&History_head,&History_index,Input);
				Make_listfile_syboltable_checkerror(Input_change);

				free(Input);
				free(Input_change);
				break;
			case 14://input "symbol"
				History_made(&History_head,&History_index,Input);
				Print_Symbol();
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
