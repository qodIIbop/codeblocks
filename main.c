#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>


int space=0, word=0, nl=0, letter=0,letternumsum[50],wordletternum=0,i=0;
char actual_char=' ';
//if the actual char is a space returns with 1, if not returns with 0
int ifspace()
{
    if(actual_char==' ')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//if the actual char is a new line char returns with 1, if not returns with 0
int ifnl()
{
    if(actual_char=='\n')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//if the actual char is a letter with apostrophe
int ifekezet(fromtext)
{
    if(fromtext=='á' || fromtext=='é' || fromtext=='í' || fromtext=='ó' || fromtext=='ö' || fromtext=='ő' || fromtext=='ú' || fromtext=='ü' || fromtext=='ű')
    {
        return 1;
    }
}
//fill an array with how many words are in the text with that number of letters
void lettersumarrayfiller()
{
    for(i=1;i<50;i++)
    {
        if(i==wordletternum)
        {
            letternumsum[i]=letternumsum[i]+1;
            break;
        }
    }
}

int qerror()
{
    if(wordletternum>=50)
    {
        return -1;
    }
    else if(actual_char<0)
    {
        return -2;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int inword_toggle=0;
    char previous_char=' '/*,input_filename=0*/;
    FILE *txt;
/*    printf("Please enter full path of file: ");
    scanf("%s",&input_filename);*/
    txt=fopen("test","r");
    if(txt==0)
    {
        perror("Error");
        printf("\n");
        printf("errno=%d\n",errno);
        return 0;
    }
    while((actual_char=fgetc(txt))!=EOF)
    {
/*        printf("%lc",actual_char);
        printf("\t char value=%d\n",actual_char);*/
        if(qerror()==0);
        else if(qerror()==-1)
        {
            printf("The file contains text with invalid length!\n");
            return 0;
        }
        else if(qerror()==-2)
        {
            printf("The file contains text with invalid input!\n");
            return 0;
        }
        if(isalpha(actual_char)|| ifekezet(actual_char))
        {
            letter++;
        }
        else
        {
            if(ifspace()==1)
            {
                space++;
            }
            if(ifnl()==1)
            {
                nl++;
            }
        }
        //sets inword_toggle to 1 if at start of word
        if((actual_char!=' ' && actual_char!='\n') && isspace(previous_char))
        {
            word++;
            inword_toggle=1;
        }
        //sets inword_toggle to 0 if at the end of a word
        if((actual_char==' ' || actual_char=='\n') && isalpha(previous_char))
        {
            inword_toggle=0;
//            printf("%d\n",wordletternum);
            lettersumarrayfiller();
//            printf("%d=%d\n",i,letternumsum[i]);

        }
        //adds one to wordletternum value if still in word or resets counter if not
        if(inword_toggle==1)
        {
            wordletternum++;
 //           printf("Size=%d\n",wordletternum);
        }
        else
        {
            wordletternum=0;
        }
        previous_char=actual_char;
    }
    lettersumarrayfiller();
    fclose(txt);
    printf("\n");
    printf("The number of letters in the text is:%d\n",letter);
    printf("The number of words is:%d\n",word);
    printf("The number of spaces is:%d\n",space);
    printf("The number of new lines is:%d\n",nl);
    printf("\n\n");
    for(i=0;i<50;i++)
    {
        if(letternumsum[i]!='\0')
        {
            printf("The number of %d letter words is=%d\n",i,letternumsum[i]);
        }
    }
    return 0;
}
