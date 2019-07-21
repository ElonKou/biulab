//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// File Name: roby.cpp
// Author   : ElonKou
// Email    : elonkou@ktime.cc
// Date     : 2019年05月04日 星期六 21时14分36秒
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ROW 30
#define COL 30
#define P 0.5
#define PER_DO_TIMES 200
#define SOLU_DIM 243
#define POP_SIZE 200
#define CL_TIMES 100
#define P_CROSS 0.7
#define P_MUT 0.005
#define GEN_NUM 1000

int move(int x, int y, int dire);

/**产生０～１的伪随机数**/
double rand_zo() {
    return (double)rand() / (double)(RAND_MAX);
}

/**初始化罗比的世界，以概率ｐ在它的世界中放置垃圾**/
void init_world(int world[][COL], double p) {
    int i, j;
    //初始每个格子为空，用０表示
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            world[i][j] = 0;
        }
    }

    //放置墙壁,2代表墙壁
    for (i = 0; i < ROW; i++) {
        world[0][i] = 2;
        world[i][0] = 2;
        world[ROW - 1][i] = 2;
        world[i][COL - 1] = 2;
    }

    //放置垃圾
    for (i = 1; i < ROW - 1; i++) {
        for (j = 1; j < COL - 1; j++) {
            if (rand_zo() < p)
                world[i][j] = 1;
        }
    }
}

/**打印罗比的世界**/
void print_world(int m[][COL]) {
    int i, j;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++)
            printf("%4d", m[i][j]);
        printf("\n");
    }
}

/**根据罗比当前的情况，返回对应的策略编号**/
int get_stra(int m[]) {
    //约定：m是有五个元素的数组，分别表示北，东，南，西，中，数组的元素可以为0,1,2,分别表示空，有罐子，墙壁
    int i, num = 0;
    for (i = 0; i < 5; i++) {
        num += m[i] * (pow(3, 4 - i));
    }
    return num;
}

/**根据策略表ST,执行清扫动作,返回对应的分数**/
double do_clean(int wor[][COL], int ST[]) {
    //约定：可以执行的动作有：
    //              向北移动　０
    //              向东移动　１
    //              向南移动　２
    //              向西移动　３
    //              随机移动　４
    //              　不动　　５
    //              清理罐子　６
    //计分规则：
    //  如果罗比所在的格子中有罐子，并且打扫了罐子，+10分
    //  如果执行打扫的动作而当前格子中没有罐子, -1分
    //  如果撞到了墙，-5分，并且弹回原来的格子

    //从左上角开始打扫
    int pos[2] = {1, 1};
    double sc = 0;
    int i;

    for (i = 0; i < PER_DO_TIMES; i++) {
        // 得到当前位置的情况
        int situ[5];
        situ[0] = wor[pos[0] - 1][pos[1]];
        situ[1] = wor[pos[0]][pos[1] + 1];
        situ[2] = wor[pos[0] + 1][pos[1]];
        situ[3] = wor[pos[0]][pos[1] - 1];
        situ[4] = wor[pos[0]][pos[1]];
        // 得到此情况下的策略编号
        int str_num = get_stra(situ);
        // 按照此策略进行行动，并对wor和sc进行对应更新

        int dire;
        int rand_num;
        switch (ST[str_num]) {
            case 0:
                //向北移动
            N:
                if (move(pos[0], pos[1], 0))
                    sc -= 5;
                else
                    pos[0]--;
                break;
            case 1:
                //向东移动
            E:
                if (move(pos[0], pos[1], 1))
                    sc -= 5;
                else
                    pos[1]++;
                break;
            case 2:
                //向南移动
            S:
                if (move(pos[0], pos[1], 2))
                    sc -= 5;
                else
                    pos[0]++;
                break;
            case 3:
                //向西移动
            W:
                if (move(pos[0], pos[1], 3))
                    sc -= 5;
                else
                    pos[1]--;
                break;
            case 4:
                //随机移动
                rand_num = rand_zo();
                if (rand_num < 0.25)
                    goto N;
                else if (rand_num < 0.50)
                    goto E;
                else if (rand_num < 0.75)
                    goto S;
                else
                    goto W;
                break;
            case 5:
                //不动
                break;
            case 6:
                //清理罐子
                if (wor[pos[0]][pos[1]] == 1)
                    sc += 10;
                else
                    sc -= 1;
                break;
        }
    }
    return sc;
}

//罗比移动,返回是否撞墙(1表示撞墙),随机移动时返回移动方向
int move(int x, int y, int dire) {
    //约定:
    //      dire == 0,向北
    //      dire == 1,向东
    //      dire == 2,向南
    //      dire == 3,向西
    //      dire == 4,随机移动

    int rand_num;
    switch (dire) {
        case 0:
            if (--x == 0)
                return 1;
        case 1:
            if (++y == (COL - 1))
                return 1;
        case 2:
            if (++x == (ROW - 1))
                return 1;
        case 3:
            if (--y == 0)
                return 1;
    }
    return 0;
}

/**对正数四舍五入取整**/
int m_round(double x) {
    return (int)(x + 0.5);
}

/**生成初始解**/
void init_solu(int solu[][SOLU_DIM]) {
    int i, j;
    for (i = 0; i < POP_SIZE; i++)
        for (j = 0; j < SOLU_DIM; j++)
            solu[i][j] = m_round(rand_zo() * 6);
}

/**适应度**/
void get_fitness(int solu[][SOLU_DIM], double fitness[]) {
    int i, j;

    int ST[SOLU_DIM];  //每个个体对应一张策略表

    for (i = 0; i < POP_SIZE; i++) {
        for (j = 0; j < SOLU_DIM; j++)
            ST[j] = solu[i][j];

        double per_sum = 0;
        /*对于每一个个体，给它CL_TIMES机会打扫,取平均成绩做为它的适应度分数,每一次的世界都不同，但是策略表相同*/
        for (j = 0; j < CL_TIMES; j++) {
            int wor[ROW][COL];
            init_world(wor, P);
            per_sum += do_clean(wor, ST);
        }

        //保证适应度是正数
        fitness[i] = per_sum / CL_TIMES + 5 * PER_DO_TIMES;
    }
}

//选择算子
void ga_sel(int old_pop[][SOLU_DIM]) {
    int new_pop[POP_SIZE][SOLU_DIM];
    double pr[POP_SIZE], cum_pr[POP_SIZE];
    get_fitness(old_pop, pr);

    double pr_sum = 0;
    int i, j, k;
    for (i = 0; i < POP_SIZE; i++)
        pr_sum += pr[i];

    for (i = 0; i < POP_SIZE; i++)
        pr[i] = pr[i] / pr_sum;

    cum_pr[0] = pr[0];

    for (i = 1; i < POP_SIZE; i++)
        cum_pr[i] = cum_pr[i - 1] + pr[i];

    //轮盘赌方法选择
    for (i = 0; i < POP_SIZE; i++) {
        double rand_n = rand_zo();
        for (j = 0; j < POP_SIZE - 1; j++) {
            if (rand_n < cum_pr[0]) {
                for (k = 0; k < SOLU_DIM; k++)
                    new_pop[i][k] = old_pop[0][k];
                break;
            } else if (rand_n >= cum_pr[j] && rand_n <= cum_pr[j + 1]) {
                for (k = 0; k < SOLU_DIM; k++)
                    new_pop[i][k] = old_pop[j + 1][k];
                break;
            }
        }
    }

    for (i = 0; i < POP_SIZE; i++)
        for (j = 0; j < SOLU_DIM; j++)
            old_pop[i][j] = new_pop[i][j];
}

//交叉
void ga_cross(int new_pop[][SOLU_DIM]) {
    //选择需要交叉的个体
    int count = 0;
    int need_cr[POP_SIZE];
    int i, j;

    for (i = 0; i < POP_SIZE; i++) {
        if (rand_zo() < P_CROSS) {
            need_cr[count] = i;
            count++;
        }
    }

    if (count % 2 != 0)
        count++;

    //随机决定一个不为0的交叉点
    int cr_point = 0;
    while (cr_point == 0) {
        cr_point = m_round(rand_zo() * SOLU_DIM);
    }

    int temp[SOLU_DIM];

    //进行交叉
    for (i = 0; i < count; i += 2) {
        for (j = cr_point; j < SOLU_DIM; j++) {
            temp[j] = new_pop[need_cr[i]][j];
            new_pop[need_cr[i]][j] = new_pop[need_cr[i + 1]][j];
            new_pop[need_cr[i + 1]][j] = temp[j];
        }
    }
}

/***变异**/
void ga_mut(int pop[][SOLU_DIM]) {
    int ge_sum = POP_SIZE * SOLU_DIM;
    int i, j, k;
    for (i = 0; i < ge_sum; i++) {
        if (rand_zo() < P_MUT) {
            //定位此基因所在的染色体,此处，染色体即个体，下同
            int chr_loc;
            chr_loc = i / SOLU_DIM;
            //定位此基因所在染色体上的基因位
            int gen_loc;
            gen_loc = i % SOLU_DIM;
            //进行变异
            pop[chr_loc][gen_loc] = m_round(rand_zo() * 6);
        }
    }
}

double max(double h[], int len) {
    double m = h[0];
    int i;
    for (i = 1; i < len; i++) {
        if (h[i] > m)
            m = h[i];
    }
    return m;
}
int main() {
    //随机生成解
    int solu[POP_SIZE][SOLU_DIM];
    init_solu(solu);

    int i;

    double fit[POP_SIZE];

    get_fitness(solu, fit);
    printf("当前的最高分数为:%f  ", max(fit, POP_SIZE));

    printf("\n计算中........\n");

    for (i = 0; i < 5; i++) {
        ga_sel(solu);
        ga_cross(solu);
        ga_mut(solu);
    }

    get_fitness(solu, fit);

    printf("最终的最高分数为:%f  ", max(fit, POP_SIZE));
    printf("\n");
    return 0;
}
