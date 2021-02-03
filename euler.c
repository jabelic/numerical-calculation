#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 1000
#define EPS pow(10.0, -2.2)
#define DT  0.01
#define XLIM 50

double f(double x){ return  x*x; }
double df(double x){ return 2*x; }
double euler(double *x){ 
    x[0] = 0.001;
    int times = 0;
    int oldx = 0;
    while (x[times] < XLIM && times < N){
        times++;
        x[times] = x[times-1] + df(x[times-1]) * DT;
        printf("%f\n",x[times]);
    }
    return x[times];
}

int main(int argc, int **argv){
    FILE *f;
    FILE *gid;
    char name[32];
    double *x = calloc(N, sizeof(double));
    double *t = calloc(N, sizeof(double));
    for(int i = 0; i <= N; i++){
        t[i] = DT*i;
    }
    printf("%f\n", euler(x));
    sprintf(name,"data.txt");
    f=fopen(name,"w");
    int plot_size = 0;
    fprintf(f,"%lf\t%lf\n",t[plot_size],x[plot_size]);
    while (plot_size < N && x[plot_size] != 0.0){
        plot_size++;
        fprintf(f,"%lf\t%lf\n",t[plot_size],x[plot_size]);
    }
    fclose(f);
    gid=popen("gnuplot -persist","w");
    fprintf(gid,"set terminal png\n");
    fprintf(gid,"set xrange [0:%f] \n", plot_size*DT); // fix me
    fprintf(gid,"set yrange [-1.2:%f] \n", XLIM+0.1); // fix me
    fprintf(gid,"set output 'init.png' \n");
    fprintf(gid,"plot 'data.txt' w l \n");
    pclose(gid);
    return 0;
}