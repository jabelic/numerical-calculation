#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 800
#define EPS pow(10.0, -2.2)
#define DT  0.01
#define XLIM 60
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))


double df(double t, double x){ return x*t; }
double f_true(double t){ return 4.0*exp(t*t/2.0); };
double *range(double *ary);

double euler(double *t, double *x){ 
    x[0] = f_true(t[0]);
    printf("Initial: %f\n", f_true(t[0]));
    int i = 0;
    for (i = 1; i <= N; i++){
        x[i] = x[i-1] + df(t[i], x[i-1]) * DT;
        // if (x[i] > XLIM || x[i] < -XLIM){ break; }
    }
    return x[i];
}

int main(int argc, char **argv){
    FILE *f;
    FILE *gid;
    char name[32];
    double *x = calloc(N, sizeof(double));
    double *t = calloc(N, sizeof(double));
    double *x_t = calloc(N, sizeof(double));
    double *er = calloc(N, sizeof(double));
    int index = 0;
    // 定義域 domain
    for(int i = -N/2; i <= N/2; i++){
        t[index] = DT*i;
        index++;
        // printf("%f\n", t[i]);
    }
    for (int i=0; i < N; i++){
        x_t[i] = f_true(t[i]);
    }
    printf("%f\n", euler(t,x));
    for(int i=0; i<N; i++){
        er[i] = fabs(x[i] - x_t[i]);
    }

    // euler method
    sprintf(name,"data.dat");
    f=fopen(name,"w");
    int plot_size = 0;
    fprintf(f,"%lf\t%lf\n",t[plot_size],x[plot_size]);
    while (plot_size < N){
        plot_size++;
        fprintf(f,"%lf\t%lf\n",t[plot_size],x[plot_size]);
    }
    fclose(f);

    // 厳密解
    sprintf(name,"data_t.dat");
    f=fopen(name,"w");
    plot_size = 0;
    fprintf(f,"%lf\t%lf\n",t[plot_size],x_t[plot_size]);
    while (plot_size < N){
        plot_size++;
        fprintf(f,"%lf\t%lf\n",t[plot_size],x_t[plot_size]);
    }
    fclose(f);

    sprintf(name,"error.dat");
    f=fopen(name,"w");
    plot_size = 0;
    fprintf(f,"%lf\t%lf\n",t[plot_size],er[plot_size]);
    while (plot_size < N){
        plot_size++;
        fprintf(f,"%lf\t%lf\n",t[plot_size],er[plot_size]);
    }
    fclose(f);


    // range size for plotting
    double *rangesize_x = range(x);
    double *rangesize_x_t = range(x_t);
    double *rangesize_er = range(er);

    gid=popen("gnuplot -persist","w");
    fprintf(gid,"set terminal png\n");
    fprintf(gid,"set grid\n");
    fprintf(gid,"set xrange [-%f:%f] \n", plot_size*DT/2+2*DT,plot_size*DT/2+2*DT);
    fprintf(gid,"set yrange [-%f:%f] \n", MIN(rangesize_x[0], rangesize_x_t[0])+1,MAX(rangesize_x[1], rangesize_x_t[1])+1);
    fprintf(gid,"set output 'init.png' \n");
    fprintf(gid,"plot 'data.dat' w l, 'data_t.dat' w l linecolor rgb '#ff0000' \n");
    // pclose(gid);

    fprintf(gid,"set xrange [-%f:%f] \n", plot_size*DT/2+2*DT,plot_size*DT/2+2*DT);
    fprintf(gid,"set yrange [-%f:%f] \n", rangesize_er[0]+(rangesize_er[0]+rangesize_er[1])/10.0,rangesize_er[1]+(rangesize_er[0]+rangesize_er[1])/10.0);
    fprintf(gid,"set output 'error.png' \n");
    fprintf(gid,"plot 'error.dat' w l \n");
    pclose(gid);
    return 0;
}

double* range(double *ary){
    double *tmp = calloc(2, sizeof(double));
    for (int i=1; i<N; i++){
        tmp[0] = MIN(ary[i], tmp[0]);
    }
    for (int i=1; i<N; i++){
        tmp[1] = MAX(ary[i], tmp[1]);
    }
    return tmp;
}