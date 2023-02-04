#include <stdio.h>

void createfileFunc(char []);
void catFunc(char []);
void insertFunc(char []);
void extractArgs(char [],char [][10],char [][128],int );
void findFunc(char []);
int search(char *searchKey,char *buff);

int main()
{

    char commands[15][20] = {"createfile","cat","insertstr","remove","copy","cut","paste","find","replace","grep","undo","auto-indent","compare","tree","arman"};
    char input[128];
    char input_command[20];
    char input_argument[128];
    int i;
    char tempch;

    gets(input);

    int j;
    for (j=0; input[j]!=' '; j++)
    {
        input_command[j]=input[j];
    }
    input_command[j]='\0';


    j++;
    tempch=input[j];
    int k=0;
    while(tempch!='\0')
    {
        j++;
        input_argument[k]=tempch;
        tempch=input[j];
        k++;

    }
    input_argument[k]=tempch;


    for(i=0; i<15; i++)
        if (strcmp(input_command,commands[i])==0)
            break;

    switch(i)
    {
    case 0:
        createfileFunc(input_argument);
        break;
    case 1:
        catFunc(input_argument);
        break;
    case 2:
        insertFunc(input_argument);
        break;
    case 3:
        //removeFunc(input_argument);
        break;
    case 4:
        //copyFunc(input_argument);
        break;
    case 5:
        //cutFunc(input_argument);
        break;
    case 6:
        //pasteFunc(input_argument);
        break;
    case 7:
        findFunc(input_argument);
        break;
    case 8:
        //replaceFunc(input_argument);
        break;
    case 9:
        //grepFunc(input_argument);
        break;
    case 10:
        //undoFunc(input_argument);
        break;
    case 11:
        //indentFunc(input_argument);
        break;
    case 12:
        //compareFunc(input_argument);
        break;
    case 13:
        //treeFunc(input_argument);
        break;
    }



    return 0;

}

void createfileFunc(char argstr[])
{

    char strkeyword[1][10]= {"-file"};
    char keyarg[1][128];
    extractArgs(argstr,strkeyword,keyarg,1);

    FILE *fileID;
    fileID=fopen(keyarg[0],"w");
    fclose(fileID);

}

void catFunc(char argstr[])
{

    char strkeyword[1][10]= {"-file"};
    char keyarg[1][128];
    extractArgs(argstr,strkeyword,keyarg,1);

    FILE *fileID;
    fileID=fopen(keyarg[0],"r");

    char temp;
    temp=getc(fileID);
    while(temp!=EOF)
    {
        putchar(temp);
        temp=getc(fileID);
    }

    fclose(fileID);

}


void insertFunc(char argstr[])
{

    char strkeyword[3][10]= {"-file","-str","-pos"};
    char keyarg[3][128];
    int posL,posC;

    extractArgs(argstr,strkeyword,keyarg,3);
    sscanf(keyarg[2],"%d:%d",&posL,&posC);
    FILE *fileID;
    fileID=fopen(keyarg[0],"a");
    for (int i=1; i<posL; i++)
        fprintf(fileID,"\n");

    for (int i=0; i<posC; i++)
        fprintf(fileID," ");

    fprintf(fileID,keyarg[1]);

    fclose(fileID);

}

void extractArgs(char argstr[],char strkeyword[][10],char keyarg[][128],int Nkeyword)
{
    int j=0,k,index=0;
    char tempch;
    char keyword[10];
    while (argstr[j]!='\0')
    {
        k=0;
        while(argstr[j]!=' ')
        {
            keyword[k]=argstr[j];
            j++;
            k++;
        }
        keyword[k]='\0';

        for(index=0; index<Nkeyword; index++)
            if (strcmp(keyword,strkeyword[index])==0)
                break;


        j++;
        tempch=argstr[j];
        k=0;
        while(!(tempch==' ' || tempch=='\0'))
        {
            j++;
            keyarg[index][k]=tempch;
            tempch=argstr[j];
            k++;
        }
        keyarg[index][k]='\0';
        j++;

    }

}



void findFunc(char argstr[])
{

    char strkeyword[5][10]= {"-file","-str","-at","-count","-all"};
    char keyarg[5][128];
    char buff[128];
    int occurance[50];
    extractArgs(argstr,strkeyword,keyarg,2);
    FILE *fileID;
    fileID=fopen(keyarg[0],"r");
    int count=0;
    int ichar=-1;
    int index=-1;
    char tempchar;


    do {
        tempchar = getc(fileID);
        ichar++;

        if (tempchar==keyarg[1][0])
        {
            index=ichar;
            for (int i=1; i<strlen(keyarg[1]); i++)
            {
                tempchar=getc(fileID);
                ichar++;
                if (tempchar!=keyarg[1][i])
                {
                    index = -1;
                    break;
                }
            }
            if (index>-1)
            {
                occurance[count]=index;
                count++;
            }
        }


    } while (tempchar != EOF);
    fclose(fileID);




    if (strstr(argstr,strkeyword[2])!=NULL){
        printf("%d",occurance[atoi(keyarg[2])-1]);
    }
    else if (strstr(argstr,strkeyword[3])!=NULL){
        printf("%d",count+1);
    }
    else if (strstr(argstr,strkeyword[4])!=NULL){
        for(int i=0;i<=count;i++)
            printf("%d,",occurance[i]);
    }
    else
        printf("%d",occurance[0]);

}




int search(char *searchKey,char *buff)
{
    char *p;
    if ((p = strstr(buff,searchKey))!=NULL)
        return 1;
    else
        return -1;

}

