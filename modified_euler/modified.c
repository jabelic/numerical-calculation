#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 300
#define EPS pow(10.0, -2.2)
#define DT  0.01
#define XLIM 60

double df(double t){ return 3*t*t - 2; }
double modified(double *t, double *x){
    x[0] = 0.1;
    int i = 0;
    for (i = 1; i <= N; i++){
        double k1 = DT*df(t[i]);
        double k2 = DT*df(t[i]+DT);
        x[i] = x[i-1] + (k1+k2)/2.0;
    }
    return x[i];
}
int main(int argc, char **argv){
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
    printf("%f\n", modified(t,x));
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