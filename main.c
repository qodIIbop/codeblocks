#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <locale.h>
#define ARRAYSIZE 50

int space=0, word=0, nl=0, letter=0,letternumsum[ARRAYSIZE],wordletternum=0,i=0;
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
//fill an array with how many words are in the text with that number of letters
void lettersumarrayfiller()
{
    for(i=1;i<ARRAYSIZE;i++)
    {
        if(i==wordletternum)
        {
            letternumsum[i]=letternumsum[i]+1;
            break;
        }
    }
}
//errorhandling for ekezet and words larger than 50 letters
int qerror()
{
    if(wordletternum>=ARRAYSIZE)
    {
        printf("ERROR:\nThe input file contains to large text!\n");
        return -1;
    }
    else if(actual_char<0)
    {
        printf("ERROR:\nThe input file contains invalid characters!\n");
        return -2;
    }
    else
    {
        return 0;
    }
}
//calculate average and draw
void drawsumcalc()
{
    int j=0,k=0;
    float sumarray[ARRAYSIZE],sum=0;
    i=0;
    for(j=0;j<ARRAYSIZE;j++)
    {
        printf("array=%d i=%d\n",letternumsum[i],i);
        sum+=letternumsum[i++];
        printf("sum=%d\n",sum);
    }
    sum=sum/i;
    printf("sum=%f",sum);
    sumarray[k]=sum*letternumsum[i];
    for(k=0;k<ARRAYSIZE;k++)
    {
        for(j=0;j<=i;j++)
        {
            printf("=");
            if(j==i)
            {
                printf("\n");
            }
        }
    }
}

int main()
{
    int inword_toggle=0;
    char previous_char=' ';

    setlocale(LC_ALL,"hun_HU.iso88592");

    FILE *txt;
    txt=fopen("test","r");
    if(txt==0)
    {
        printf("errno=%d",errno);
        return 0;
    }
    while((actual_char=fgetc(txt))!=EOF)
    {
        if(qerror()<0)
        {
            qerror();
            return -1;
        }
//        printf("%c",actual_char);
//        printf("\tvalue is=%d\n",actual_char);
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
//            printf("%d\n",wordletternum);
            lettersumarrayfiller();
//            printf("%d=%d\n",i,letternumsum[i]);

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
    lettersumarrayfiller();
    fclose(txt);
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
    drawsumcalc();
    return 0;
}
