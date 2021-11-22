#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

double przybpi(int n){
    double ppi = 0;
    int i;
    for(i = 1; i <= n; i++){
        ppi += pow(-1, (n-1))/(2*n-1);   
    }
    return ppi*4;
}

void Proc(int proc_nr){
	srand(time(NULL));
    pid_t pid;
    int i, n;
    int X = 100, Y = 5000;
    for(i = 1; i <= proc_nr; i++){
        n = X + rand()%(Y - X + 1);
        switch(pid = fork()){
            case 0:
                printf("NR: %d PID = %d N = %d pi = %f \n", i, getpid(), n, przybpi(n));
                break;
            default:
                break;
         }    
    }
}

int main( int argc, char **argv )
{   
    int p;
    printf("Ilosc procesow: ");
    scanf("%d", &p);
    Proc(p);
    return 0;
}