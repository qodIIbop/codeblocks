#include <stdio.h>
#include <stdlib.h>

/***************************************************************
 *                                                             *
 *  Gives the fibonacci sequence between 2 given whole int num *
 *                                                             *
 ***************************************************************/

int start,stop,num;
unsigned long long int fib[90];
unsigned long long int fib2[90];


//fills up a 90 element array with the fibonacci code
void fibfiller()
{
    int i;
    fib[i=0]=1; //first element of the fibonacci code and the first number in the array
    fib[i=1]=1; //second element of the fibbonacci code and the second element in the array
//Debug    printf("fib[0]=%lli\n",fib[0]);
//Debug    printf("fib[1]=%lli\n",fib[1]);
    for(i=2;i<90;i++)
    {
        fib[i]=fib[i-1]+fib[i-2];  //adds the previous 2 numbers in the array to get the next element of the fib code
//Debug        printf("fib[%d]=%lli\n",i,fib[i]);
    }
}

//fills another array (fib2[j]) with the interested elements of the fibonacci sequence
void interestedfib()
{
    int i=0,j;
//checks for the first interested element
    while(fib[i]<start)
    {
        i++;
//Debug         printf("fib[%d]=%lli\n",i,fib[i]);
    }
//when first interested element is found stores that value into the fib2 array
    if(fib[i]>=start)
    {
        for(j=0;j<90;j++)
        {
            fib2[j]=fib[i++];
//Debug            printf("fib2[%d]=%lli,fib[%d]=%lli\n",j,fib2[j],i,fib[i]);
//Debug            printf("fib2[%d]=%lli\n",j,fib2[j]);
//checks to see if the element is still needed or is greater than the end element given by user
            if(fib[i]==stop)
            {
                fib2[j]=fib[i];
                num=j;
//Debug                printf("fib2[%d]=%lli\n",j,fib2[j]);
                break;
            }
            if(fib[i]>stop)
            {
//stores the size of the fib2 array for use in finding the prime numbers and average
                num=j;
//Debug                printf("num=%d",num);
                break;
            }
        }
    }
}
//function checks the elements of the array and checks for prime numbers
//if the number can be divided by a number greater than 1 and smaller than itself the function stops dividing the number and marks the number as not prime
void primenumberfinder()
{
//    printf("debug\n");
    int i,k,numberofdividers=0;
//    printf("num=%d, array=%lli\n",num,fib[i]);
    for(i=0;i<=num;i++)
    {
//        printf("array=%lli\n",fib[i]);
        for(k=2;k<fib2[i];k++)
        {
            if(fib2[i]%k==0)
            {
                numberofdividers=1;
//                printf("number=%d\n",numberofdividers);
                break;
            }
        }
        if(numberofdividers==0 && fib2[i]!=1)
        {
            printf("%lli is a prime number\n",fib2[i]);
        }
        numberofdividers=0;
    }
}
//Function adds all values of the array to eachother and divides them by the number of elements in the given array (average)
//returns the average, has no direct input
void averagefn()
{
    float averagecounter=0;
    int i;
    long long int value=0;
    float average;
    for(i=0;i<=num;i++)
    {
        averagecounter++;
        value=value+fib2[i];
//        printf("Value=%lli\n",value);
    }
    average=value/averagecounter;
    printf("Average is:%.2f\n",average);
}

int main()
{
    int error1,error2,startchange,stopchange;
    printf("Enter the start value:");
    error1=scanf("%d",&start);
//Debug    printf("error=%d\n",error1);
    printf("Enter the stop value:");
    error2=scanf("%d",&stop);
//Debug    printf("error=%d\n",error2);
//checking errors: If either scanf function doesnt return 1 then display error message and skip to end
    if(error1<=0 || error2<=0)
    {
        printf("Invalid input!\n");
        goto jump;
    }
//if stop if smaller than start then switch the two values and goto the filler functions
    if(stop<start)
    {
        stopchange=stop;
        startchange=start;
        stop=startchange;
        start=stopchange;
        goto here;
    }
//if the two numbers are equal then display an error message and stip to the end
    if(start==stop)
    {
        printf("Invalid input!!\n");
        goto jump;
    }
    here:
    fibfiller();
    interestedfib();
    primenumberfinder();
    averagefn();
    jump:
    return 0;
}

/*******************************************************
 *               Tests Done by Creater:                *
 *  if start and stop are equal                        *
 *  if stop is smaller than start                      *
 *  if stop is larger than start                       *
 *  if start is equal to element of fib seq            *
 *  if stop is equal to element of fib seq             *
 *  if start eq 1 or 0                                 *
 *  if either num is negative                          *
 *  if ether num is a string                           *
 *******************************************************/
