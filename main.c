#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>


int space=0, word=0, nl=0, letter=0;

int main()
{
    char actual_char=' ',previous_char=' ';
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
            if(actual_char==' ')
            {
                space++;
            }
            if(actual_char=='\n')
            {
                nl++;
            }
        }
        if((actual_char!=' ' || actual_char!='\n') && isspace(previous_char))
        {
            word++;
        }
        previous_char=actual_char;
    }
    fclose(txt);
//    read_file();
//    numberofwords=wordcount();
    printf("The number of letters in the text is:%d\n",letter);
    printf("The number of words is:%d\n",word);
    printf("The number of spaces is:%d\n",space);
    printf("The number of new lines is:%d\n",nl);
    return 0;
}
