#pragma once
#ifndef ROBBIE_CONFIG_H_
#define ROBBIE_CONFIG_H_

#include "Vec.hh"

#define START_X 6  // 起始位置
#define START_Y 6  // 起始位置

#define STR_CNT 7        // 基因密码子长度
#define MUTATE_ALL 1000  // 突变总数值
#define MUTATE_VAL 5     // 突变率
#define CLIP_CNT 1       // 剪切数量
#define GENE_CLEAR -1    // 清除基因

#define LOOP_MAP 10     // 执行地图数量
#define LOOP_CNT 200    // 执行步骤数量
#define ROBBIE_CNT 200  // 代际数量(每一代数量)
#define NAME_LEN 16     // 名字长度
#define PARENT_CNT 2    // 双亲数量
#define GENE_LEN 243    // 基因长度

#define MAP_WIDTH 16    // 地图宽度
#define MAP_HEIGHT 16   // 地图长度
#define RUBBISH_CNT 50  // 垃圾数量
#define EDGE 2          // 边界标志
#define RUBBISH 1       // 物体标志
#define EMPTY 0         // 空的标志
#define OUT -1          // 空的标志
#define WALL_CNT 2      // 墙壁数量
#define PATH_EMPTY -1   // 路径空标志

#define LOOP_CONTROLLER 10000  // 代数
#define PUNISHMENT_EDGE -5     // 撞墙惩罚
#define PUNISHMENT_PICK -1     // 无效捡东西惩罚
#define REWARD 10              //奖励

typedef struct PlayActions {
    vec_2i positions[LOOP_CNT];
    int actions[LOOP_CNT];
    int hash;
    int step;
} PlayActions;

typedef struct Strategy {
    int key;
    int wmove;
    int hmove;
    Strategy();
    Strategy(int key, int wmove, int hmove);
    ~Strategy();
} Strategy;


// 移动规则
// 坐标从左到右x++  从上到下y++
// 0:北 4:随机移动
// 1:南 5:不动
// 2:东 6:捡东西(待增加新规则)
// 3:西

typedef enum action { UP, DOWN, RIGHT, LEFT, RANDOM, WAIT, PICK } ACTION;
#endif