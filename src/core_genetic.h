#ifndef CORE_GENETIC
#define CORE_GENETIC

#define STR_CNT 8        // 基因密码子长度
#define MUTATE_ALL 1000  //突变总数值
#define MUTATE_VAL 40    //突变率
#define CLIP_CNT 1       // 剪切数量
#define GENE_CLEAR -1    // 清除基因

#define LOOP_ONE 100    // 循环次数(随机多个位置开始执行多遍数)
#define LOOP_CNT 200    // 循环次数(每个Robbie的轮数)
#define ROBBIE_CNT 100  // 代际数量(每一代数量)
#define NAME_LEN 16     // 名字长度
#define PARENT_CNT 2    // 双亲数量
#define GENE_LEN 243    // 基因长度

#define MAP_WIDTH 20     // 地图宽度
#define MAP_HEIGHT 16    // 地图长度
#define RUBBISH_CNT 160  // 垃圾数量
#define EDGE 2           // 边界标志
#define RUBBISH 1        // 物体标志
#define EMPTY 0          // 空的标志

#define BEST_CNT 2             // 最好的长度
#define LOOP_CONTROLLER 10000  // 代数
#define PUNISHMENT_EDGE -5     // 撞墙惩罚
#define PUNISHMENT_PICK -1     // 无效捡东西惩罚
#define REWARD 10              //奖励

typedef struct vec_2i {
    int x;
    int y;
    vec_2i();
    vec_2i(int a, int b);
} vec_2i;

typedef struct Cell {
    int index;
    float score;
    Cell();
} cell;

typedef struct Strategy {
    int key;
    int wmove;
    int hmove;
} Strategy;
void print_strategy();
int randomInt();
// Gene

class Gene {
   private:
    int len;
    int genes[GENE_LEN];

   public:
    Gene();
    Gene create();
    Gene create(Gene other);
    Gene clone();
    void init();
    void clear();
    void clip(Gene other);
    void clip2(Gene other);
    void mutate();
    void print();
    void compare(Gene other);
    int getAction(int hash);
    ~Gene();
};

// Map
class Map {
   private:
    vec_2i size;
    int map[MAP_HEIGHT][MAP_WIDTH];
    int target[MAP_HEIGHT][MAP_WIDTH];

   public:
    Map();
    ~Map();
    vec_2i getSize();
    void print(vec_2i pos);
    void cleanTarget();
    void init();
    int inline getValue(vec_2i pos);
    int inline operator[](vec_2i pos);
    int getHash(vec_2i pos);
    int getTarget(vec_2i pos);
    void setTarget(vec_2i pos, int key);
    int doAction(vec_2i start, vec_2i offset);
};

// Robbie robot
class Robbie {
   private:
    int id;
    float score;
    // float value;
    int generation;
    int state[LOOP_CNT];
    char name[NAME_LEN];
    int parentId[PARENT_CNT];
    vec_2i pos;
    vec_2i start;
    Gene genes;

   public:
    Robbie();
    ~Robbie();
    Robbie marray();
    Robbie marray(Robbie spouse);
    vec_2i getPos();
    void randomPos();
    void cleanState();
    void print();
    void createName();
    void randomGene();
    void createGene();
    void compare(Robbie spouse);
    int move(int action, vec_2i pos, Map map);
    int pick(int action, vec_2i pos, Map& map);
    float getScore();
    void play(Map& map);
};

// Controller
class Controller {
   private:
    // int idPool;
    int loopCnt;
    int robbieCnt;
    int generation;
    Cell scores[ROBBIE_CNT];
    Robbie robbies[ROBBIE_CNT];
    Robbie temps[ROBBIE_CNT];
    Map map;

   public:
    Controller();
    ~Controller();
    void init();
    void loop();
    void run();
    void generate();
    void select();
    void print();
};

#endif