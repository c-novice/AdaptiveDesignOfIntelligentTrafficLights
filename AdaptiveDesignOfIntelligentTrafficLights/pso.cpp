#include "pso.h"

PSO::PSO()
{

}

double PSO::run()
{
    for(int i=0; i<DIM; i++)//初始化全局最优
        gbestx[i]=randf*(xmax-xmin)+xmin;
    gbestf=100000000000000.0;
    for(int i=0; i<NUM; i++) {//初始化粒子群
        particle* p1=&swarm[i];
        for(int j=0; j<DIM; j++)
            p1->x[j]=randf*(xmax-xmin)+xmin;
        p1->f=f1(p1->x);
        p1->bestf=100000000000000.0;
    }
    for(int t=0; t<5000; t++) {
        for(int i=0; i<NUM; i++) {
            particle* p1=&swarm[i];
            for(int j=0; j<DIM; j++)//进化方程
                p1->x[j]+=c1*randf*(p1->bestx[j]-p1->x[j])
                        +c2*randf*(gbestx[j]-p1->x[j]);
            p1->f=f1(p1->x);
            if(p1->f<p1->bestf) {//改变历史最优
                for(int j=0;j<DIM;j++)
                    p1->bestx[j]=p1->x[j];
                p1->bestf=p1->f;
            }
            if(p1->f<gbestf) {//改变全局最优
                for(int j=0;j<DIM;j++)
                    gbestx[j]=p1->x[j];
                for(int j=0; j<DIM; j++)//把当前全局最优的粒子随机放到另一位置
                    p1->x[j]=randf*(xmax-xmin)+xmin;
                gbestf=p1->f;
            }
        }
    }
}
