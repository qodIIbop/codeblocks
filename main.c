#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <locale.h>
#include <sys/ioctl.h>
#include <math.h>
#define ARRAYSIZE 50
#define CHARCOUNT 16

int space=0, word=0, nl=0, letter=0,letternumsum[ARRAYSIZE],wordletternum=0,i=0,sum=0;
char actual_char=' ';
float rounded_graph_length[ARRAYSIZE];

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
//calculate average
float avrcalc()
{
    int j=0,counter=0;
    float avr=0;

    i=0;sum=0;
//    printf("letternumsum[0]=%d counter=%d\n",letternumsum[0],counter);
    for(j=0;j<50;j++)
    {
        sum+=letternumsum[++i];
        if(letternumsum[i]!=0)
        {
/*            printf("i=%d  ",i);
            printf("sum=%d\n",sum);*/
        }
        if(letternumsum[i]!=0)
        {
            counter++;
//            printf("counter=%d\n",counter);
        }
    }
    avr=(float)counter/sum;
//    printf("avr=%f\n",avr);
    return avr;
}
//get terminal param
int term_win_size()
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

//    printf ("lines %d\n", w.ws_row);
//    printf ("columns %d\n", w.ws_col);
    return w.ws_col;
}
//give back the display size
int display_size()
{
    int display_size=0;

    display_size=term_win_size()-CHARCOUNT;
    return display_size;
}
//calculate 1% of the sum
float onepercent()
{
    float percent=0;

    percent=(float)display_size()/100;
    return percent;
}
//tells you how long each element of the graph should be
int make_graph()
{
    int j,k,total=0,graph_string_toggle=0;
    float graph_i_length[ARRAYSIZE],a=0;

    i=0;
    a=(float)display_size()/sum;
//    printf("a=%.3f\n",a);
    for(j=0;j<ARRAYSIZE;j++)
    {
        if(letternumsum[i]!=0)
        {
//            printf("letternumsum[%d]\n",i);
            graph_i_length[j]=a*letternumsum[i]*onepercent();
            rounded_graph_length[j]=ceilf(graph_i_length[j]);
//            printf("The number of \"=\" in %d letter words is %f\n",i,rounded_graph_length[j]);
            total+=rounded_graph_length[j];
            //graphical part
            do
            {
                printf("%d letter words: ",i);
                graph_string_toggle=1;
            }while(graph_string_toggle==0);
            for(k=0;k<=rounded_graph_length[j];k++)
            {
                printf("=");
                if(k==rounded_graph_length[j])
                {
                    printf("\n");
                }
            }
        }
        i++;
    }
//    printf("total=%d\n",total);

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
    avrcalc();
    term_win_size();
    onepercent();

    printf("The number of letters in the text is:%d\n",letter);
    printf("The number of words is:%d\n",word);
    printf("The number of spaces is:%d\n",space);
    printf("The number of new lines is:%d\n",nl);
    printf("\n\n");

/*    for(i=0;i<ARRAYSIZE;i++)
    {
        if(letternumsum[i]!='\0')
        {
            printf("The number of %d letter words is=%d\n",i,letternumsum[i]);
        }
    }*/

    make_graph();
//    printf("terminal width is:%d",term_win_size());
//    printf("1 percent is:%.3f\n",onepercent());
    printf("display size is %d\n",display_size());
    return 0;
}
