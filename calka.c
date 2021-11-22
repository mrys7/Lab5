#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

double* rollP(int X, int Y){
    double a, b, c;
    a = X + rand()%(Y - X + 1); 
    b = X + rand()%(Y - X + 1);
    if(a>=b){
        c = b;
		b = a;
		a = c;
    }
    double* tab = (double*)malloc(sizeof(double) * 2);
    tab[0] = a;
    tab[1] = b;
    return tab;
}

double funct(double x){
    return pow(4, x)-pow(6, x)+5;
}

double Trapez(double a, double b, int n){
    double result = 0;
	double SUM = 0;
    double x[n+1];
    double y[n+1];
    double h = (b-a)/n;
    x[0] = a;
    x[n] = b;
    y[0] = funct(a);
    y[n] = funct(b);
    for(int i = 1; i < n; i++){
        x[i] = a + (i*(b-a))/n;
    }
    for(int i = 1; i < n; i++){
        y[i] = funct(x[i]);
        SUM += y[i];
    }
    result = h*(y[0]/2 + SUM + y[n]/2);
    return result; 
}

void Proc(int proc_nr){
    srand(time(NULL));
    pid_t pid;
    int i, n;
    double a, b;
    for(i = 1; i <= proc_nr; i++){
        double* tab = rollP(-3, 3);
        a = tab[0];
        b = tab[1];
        n = rand()%100;
        switch(pid = fork()){
                case 0:
				printf("NR: %d PID = %d Trapezy(%f, %f, %d) = %f \n", i, getpid(), a, b, n, Trapez(a, b, n));
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