#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
struct u_tab
{
   int no;
   char type[20];
   char name[20];
}u_tab[200];

struct lit
{
   int no;
   char name[20];
}lit_tab[100];

struct id
{
  int no;
  char name[20];
}id_tab[100];

FILE *fp1,*fp2,*fp3,*fp4,*fp5;

char line[80];

int lit_cnt=0,id_cnt=0,u_cnt=0,str;
//=========================================================
int search_idtab(char token[20])
{
  int i;

  for(i=0;i<id_cnt;i++)
  {
	if(strcmp(token,id_tab[i].name)==0)
	 return(i);
  }
  return(-1);
}
//=========================================================
int search_littab(char token[20])
{
  int i;
  for(i=0;i<lit_cnt;i++)
  {
	if(strcmp(token,lit_tab[i].name)==0)
	 return(i);
  }
  return(-1);
}
//=========================================================
void lex()
{
  int i,id,lit=0,term=0,l=0,terminal_no,res;

  char token[20],token1[20],terminal[20],str[80];

  fp1=fopen("Src.txt","r");

  if(fp1==NULL)
  {
	printf("\n\n source file not found::");
	exit(0);
  }

  while(!feof(fp1))
  {
  	fgets(str,80,fp1);
  for(i=0;str[i]!='\0';i++)
  {
	  id=lit=term=l=0;

	  strcpy(token,"");

	  if(str[i]=='{'||str[i]=='}'||str[i]=='['||str[i]==']')
	  {
		token[l]=str[i];
		l++;
		token[l]='\0';
	  }

	  if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/')
	  {
		token[l]=str[i];
		l++;
		token[l]='\0';
	  }


	  if(str[i]==','||str[i]=='.'||str[i]==';'||str[i]=='"')
	  {
		token[l]=str[i];
		l++;
		token[l]='\0';
	  }

	  if(str[i]=='#'||str[i]=='%'||str[i]=='('||str[i]==')')
	  {
		token[l]=str[i];
		l++;
		token[l]='\0';
	  }
	  
	  	while(str[i]=='%'){
	  			 i++;
	  	 		if(str[i]=='d'||str[i]=='f'||str[i]=='s'){
	  			    i++;
	  			    goto b;					
	  	}
	  	b:  if(str[i]==','){
	  		token[l]=str[i];
	  		l++;i++;
	  		
	  	}
		token[l]='\0';
	  }
	
	  if(str[i]=='<')
	  {
		   token[l]=str[i];
		   l++;
		   if(str[i+1]=='=')
		   {
			 token[l]=str[i+1];
			 i++;
			 l++;
		  }
		  token[l]='\0';
	  }
	  else if(str[i]=='=')
	  {
		 token[l]=str[i];
		 l++;
		 if(str[i+1]=='='||str[i+1]=='>')
		 {
		   token[l]=str[i+1];
		   l++;
		   i++;
		 }
		 token[l]='\0';
	  }
	  else if(str[i]=='>'){
		token[l]='>';
		l++;
		token[l]='\0';
	  }
	  else if(isalpha(str[i]))
	  {
		token[l]=str[i];
		l++;
		i++;
	 while( isalpha(str[i]) || isdigit(str[i]) || str[i]=='_'||str[i]=='.'){
			token[l]=str[i];
			i++;
			l++;
		}
		i--;
		token[l]='\0';
		id=1;
	 }
	 else if(isalpha(str[i])){
	 	token1[l]=str[i];
	 	l++;
	 	i++;
	 	while(isalpha(str[i])){
	 		token1[l]=str[i];
	 		l++;
	 		i++;
	 	}
	 	i--;
	 	token1[l]='\0';
	 	//str=1;
	 }
	 else if(isdigit(str[i]))
	 {
		token[l]=str[i];
		l++;
		i++;
		while(isdigit(str[i]))
		{
		 token[l]=str[i];
		 l++;
		 i++;
		}
		i--;
		token[l]='\0';
		lit=1;
	 }

	fp2=fopen("terminal.txt","r");

	if(fp2==NULL)
	{
	 printf("\n\n terminal file not found::");
	 exit(0);
	}
	while(!feof(fp2))
	{
	 // fgets(line,80,fp2);
	  fscanf(fp2,"%s%d",terminal,&terminal_no);
	  if(strcmp(terminal,token)==0)
	  {
		strcpy(u_tab[u_cnt].name,token);
		strcpy(u_tab[u_cnt].type,"term");
		u_tab[u_cnt].no=terminal_no;
		term=1;
		u_cnt++;
	   }
	   
	}
	fclose(fp2);
	if(term!=1&&id==1)
	{
		 res=search_idtab(token);

		 if(res==-1)//not found
		 {
			strcpy(u_tab[u_cnt].name,token);
			strcpy(u_tab[u_cnt].type,"ID");
			u_tab[u_cnt].no=id_cnt;

			strcpy(id_tab[id_cnt].name,token);
			id_tab[id_cnt].no=id_cnt;

			id_cnt++;
			u_cnt++;
		 }
		 else
		 {
			strcpy(u_tab[u_cnt].name,token);
			strcpy(u_tab[u_cnt].type,"ID");
			u_tab[u_cnt].no=res;
			u_cnt++;
		 }
	}

	if(term!=1&&lit==1)
	{
		  res=search_littab(token);
		 if(res==-1)//not found
		 {
			strcpy(u_tab[u_cnt].name,token);
			strcpy(u_tab[u_cnt].type,"lit");
			u_tab[u_cnt].no=lit_cnt;

			strcpy(lit_tab[lit_cnt].name,token);
			lit_tab[lit_cnt].no=lit_cnt;

			lit_cnt++;
			u_cnt++;
		 }
		 else
		 {
			strcpy(u_tab[u_cnt].name,token);
			strcpy(u_tab[u_cnt].type,"lit");
			u_tab[u_cnt].no=res;
			u_cnt++;
		 }
	}
	/*if(term!=1&&str==1){

	}*/
  }//for
 }
}
//=========================================================
void printUniver()
{ int i;

  fp3=fopen("UST.txt","w");
  fprintf(fp3,"\n\n UNIVERSAL SYMB TABLE");
  fprintf(fp3,"\nTERMINAL\tTYPE\tNO");
  printf("\n\n UNIVERSAL SYMB TABLE");
  printf("\nNO\tTERMINAL\tTYPE");
  for(i=0;i<u_cnt;i++)
  {
		fprintf(fp3,"\n%d\t\t%s\t%s",u_tab[i].no,u_tab[i].name,u_tab[i].type);
		printf("\n%d\t\t%s\t%s",u_tab[i].no,u_tab[i].name,u_tab[i].type);
  }
}
//=========================================================
void printLit()
{
	int i;
	fp4=fopen("Literal.txt","w");
	fprintf(fp4,"\n\n litral table");
    fprintf(fp4,"\nNO\tliteral");
    printf("\n\n litral table");
    printf("\nNO\tliteral");
  for(i=0;i<lit_cnt;i++)
  {
	fprintf(fp4,"\n%d\t\t%s",lit_tab[i].no,lit_tab[i].name);
	printf("\n%d\t\t%s",lit_tab[i].no,lit_tab[i].name);
  }
}
void printID()
{ int i;

  fp5=fopen("id.txt","w");
  fprintf(fp5,"\n\n IDENTIFIER TABLE");
  fprintf(fp5,"\nIndex\t\tID");
  printf("\n\n IDENTIFIER TABLE");
  printf("\nIndex\t\tID");
  for(i=0;i<id_cnt;i++)
  {
		fprintf(fp5,"\n%d\t\t%s",id_tab[i].no,id_tab[i].name);
		printf("\n%d\t\t%s",id_tab[i].no,id_tab[i].name);
  }
}

//=========================================================
int main()
{
  lex();
   printUniver();
   printLit();
   printID();
	return 0;
}
/*
=================================================================
		   Terminal File

# 1
include 2
++ 3
+ 4
conio.h 5
< 6
void 7
main 8
( 9
) 10
{ 11
} 12
= 13
if 14
while 15
for 16
, 17
> 18
int 19
<= 20
== 21
printf 22
stdio.h 23
;  24
getch 25
=================================================================
	  Source File

#include<stdio.h>
#include<conio.h>

void main()
{
	int i,j=1,k=2,flag;
	for(i=0;i<=4;i++)
	{
		k=i+j;
	}
	flag=5;
	if(flag==10)
		printf("Hello Students");
	getch();
}
=================================================================
 UNIVERSAL SYMB TABLE
TERMINAL        TYPE    NO
#               term    1
include         term    2
<               term    6
stdio.h         term    23
>               term    18
#               term    1
include         term    2
<               term    6
conio.h         term    5
>               term    18
void            term    7
main            term    8
(               term    9
)               term    10
{               term    11
int             term    19
i               ID      0
,               term    17
j               ID      1
=               term    13
1               lit     0
,               term    17
k               ID      2
=               term    13
2               lit     1
,               term    17
flag            ID      3
for             term    16
(               term    9
i               ID      0
=               term    13
0               lit     2
i               ID      0
<=              term    20
4               lit     3
i               ID      0
+               term    4
+               term    4
)               term    10
{               term    11
k               ID      2
=               term    13
i               ID      0
+               term    4
j               ID      1
}               term    12
flag            ID      3
=               term    13
5               lit     4
if              term    14
(               term    9
flag            ID      3
==              term    21
10              lit     5
)               term    10
printf          term    22
(               term    9
Hello           ID      4
Students        ID      5
)               term    10
getch           term    25
(               term    9
)               term    10
}               term    12
=========================================================
 litral table
litral  NO
1       0
2       1
0       2
4       3
5       4
10      5
*/
