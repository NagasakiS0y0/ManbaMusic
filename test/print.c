#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>

int main()
{
    char n[50];
    while(1)
    {
        scanf("%s",&n);
        printf("%s",n);
    }
}