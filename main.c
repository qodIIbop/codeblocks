#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>


int space=0, word=0, nl=0, letter=0,letternumsum[1000],wordletternum=0;
char actual_char=' ';

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
//array not working correctly need to fix so wordletternum is filled into correct array slot!!
void lettersumarrayfiller()
{
    int i,counter;
    for(i=0;i<1000;i++)
    {
        if(i==wordletternum)
        {
            counter++;
        }
        i++;
    }
}
int main()
{
    int inword_toggle=0;
    char previous_char=' ';
    FILE *txt;
    txt=fopen("test","r");
/*    if(txt==0)
    {
        printf("%d",errno);  //there is no errno global variable
    }*/
    while((actual_char=fgetc(txt))!=EOF)
    {
        if(isalpha(actual_char))
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
            printf("%d\n",wordletternum);
        }
        //adds one to wordletternum value if still in word or resets counter if not
        if(inword_toggle==1)
        {
            wordletternum++;
        }
        else
        {
            wordletternum=0;
        }
        previous_char=actual_char;
    }
    fclose(txt);
    printf("\n");
    printf("The number of letters in the text is:%d\n",letter);
    printf("The number of words is:%d\n",word);
    printf("The number of spaces is:%d\n",space);
    printf("The number of new lines is:%d\n",nl);
    return 0;
}
