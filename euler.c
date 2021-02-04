#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 300
#define EPS pow(10.0, -2.2)
#define DT  0.01
#define XLIM 60

double f(double x){ return  x*x-2*x; }
double df(double t){ return 3*t*t - 2; }
double euler(double *t, double *x){ 
    x[0] = 0.1;
    int i = 0;
    // int oldx = 0;

    // while (x[i] < XLIM && i < N){
    //     i++;
    //     x[i] = x[i-1] + df(t[i]) * DT;
    //     printf("%f, %f\n",x[i], x[i-1]);
    // }
    printf("%p\n", t);
    
    for (i = 1; i <= N; i++){
        x[i] = x[i-1] + df(t[i]) * DT;
        // printf("%f, %f\n",t[i], x[i]);
        if (x[i] > XLIM || x[i] < -XLIM){ break; }
    }
    return x[i];
}

int main(int argc, int **argv){
    FILE *f;
    FILE *gid;
    char name[32];
    double *x = calloc(N, sizeof(double));
    double *t = calloc(N, sizeof(double));
    printf("%p\n", t);
    int index = 0;
    for(int i = -N/2; i <= N/2; i++){
        t[index] = DT*i;
        index++;
        // printf("%f\n", t[i]);
    }
    printf("%f\n", euler(t,x));
    printf("%p\n", t);
    printf("%f\n", t[1]);
    sprintf(name,"data.txt");
    f=fopen(name,"w");
    int plot_size = 0;
    fprintf(f,"%lf\t%lf\n",t[plot_size],x[plot_size]);
    while (plot_size < N){
        plot_size++;
        fprintf(f,"%lf\t%lf\n",t[plot_size],x[plot_size]);
    }
    fclose(f);
    gid=popen("gnuplot -persist","w");
    fprintf(gid,"set terminal png\n");
    fprintf(gid,"set xrange [-%f:%f] \n", plot_size*DT,plot_size*DT); // fix me
    fprintf(gid,"set yrange [-%f:%f] \n", (XLIM+0.1)/25,(XLIM+0.1)/25); // fix me
    fprintf(gid,"set output 'init.png' \n");
    fprintf(gid,"plot 'data.txt' w l \n");
    pclose(gid);
    return 0;
}