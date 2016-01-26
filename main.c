#include <stdio.h>
#include <stdlib.h>

int space, word, nl, letter;

/*void read_file()
{
    char ch;
    FILE *TXT;
    while((ch=fgetc(TXT))!=EOF)
    {
        if(ch()='a' || ch()='b' || ch()='c' || ch()='d' || ch()='e' || ch()='f' || ch()='g' || ch()='h' || ch()='i' || ch()='j' || ch()='k' || ch()='l' || ch()='m'
        || ch()='n' || ch()='o' || ch()='p' || ch()='q' || ch()='r' || ch()='s' || ch()='t' || ch()='u' || ch()='v' || ch()='w' || ch()='x' || ch()='y' || ch()='z')
        {
            letter++;
        }
        else
        {
            if(ch=' ')
            {
                space++;
            }
            if(ch='\n')
            {
                nl++;
            }
        }
    }
}

void wordcount()
{

    return word;
}*/

int main()
{
    char ch,c;
    FILE *TXT;
    TXT=fopen("/test.txt","r");
    while((ch=fgetc(TXT))!=EOF)
    {
        if(ch=='a' || ch=='b' || ch=='c' || ch=='d' || ch=='e' || ch=='f' || ch=='g' || ch=='h' || ch=='i' || ch=='j' || ch=='k' || ch=='l' || ch=='m' || ch=='n' || ch=='o' || ch=='p' || ch=='q' || ch=='r' || ch=='s' || ch=='t' || ch=='u' || ch=='v' || ch=='w' || ch=='x' || ch=='y' || ch=='z')
        {
            letter++;
        }
        else
        {
            if(ch==' ')
            {
                space++;
            }
            if(ch=='\n')
            {
                nl++;
            }
        }
        c=ch;
        if((ch==' ' || ch=='\n') && (c=='a' || c=='b' || c=='c' || c=='d' || c=='e' || c=='f' || c=='g' || c=='h' || c=='i' || c=='j' || c=='k' || c=='l' || c=='m' || c=='n' || c=='o' || c=='p' || c=='q' || c=='r' || c=='s' || c=='t' || c=='u' || c=='v' || c=='w' || c=='x' || c=='y' || c=='z'))
        {
            word++;
        }
    }
//    read_file();
//    numberofwords=wordcount();
    printf("The number of letters in the text is:%d\nThe number of words is:%d\nThe number of spaces is:%d\nThe number of new lines is:%d",letter,word,space,nl);
    return 0;
}
