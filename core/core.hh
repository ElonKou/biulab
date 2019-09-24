#ifndef CORE_GENETIC
#define CORE_GENETIC

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

#define MAP_WIDTH 12    // 地图宽度
#define MAP_HEIGHT 12   // 地图长度
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

#include <string>
using namespace std;

int randomInt(int range);
float randomFloat();

typedef union vec_2i {
    struct {
        int x;
        int y;
    };
    int v[2];
    vec_2i();
    vec_2i(int a, int b);
    vec_2i operator+(vec_2i other);
    void print();
} vec_2i;

struct PlayActions {
    vec_2i positions[LOOP_CNT];
    int actions[LOOP_CNT];
    int hash;
    int step;
};

typedef struct Strategy {
    int key;
    int wmove;
    int hmove;
} Strategy;
struct Map;

class Robbie {
   public:
    Robbie();
    ~Robbie();
    Robbie clone();
    // gene
    int gene_len;
    int str_len;
    int genes[GENE_LEN];
    int mutate_all;
    int mutate_val;

    void init();
    void randomPos();
    void clear();
    void clip(Robbie &other);
    Robbie clip2(Robbie other, int pos);
    void clip3(Robbie other);
    void mutate();
    void compare(Robbie other);
    int move(int action, Map &map);
    int pick(int action, Map &map);
    void play(Map &map);
    void playOne(int cnt);
    void print();
    int getScore();
    int getAction(int hash);
    void save(string fileName);
    void load(string fileName);
    // robbie info
    int id;
    int score;
    int generation;
    int parentId[PARENT_CNT];
    float averScore;
    vec_2i pos;
    vec_2i start;
};

class Map {
   public:
    Map();
    ~Map();
    vec_2i size;
    int **map;
    int **target;
    int **path;
    int rubbish_cnt;
    string map_name;

    vec_2i getSize();
    void randomMap();
    void print(vec_2i pos);
    void drawFrame(PlayActions act, int *gen);
    void cleanTarget();
    void init();

    void loadMap(const string &load_path);
    void saveMap(const string &save_path);
    int inline getValue(vec_2i pos);
    int getHash(vec_2i pos);
    int getTarget(vec_2i pos);
    void setTarget(vec_2i pos, int key);
    int getElem(vec_2i pos);
    void setElem(vec_2i pos, int key);
    int doAction(vec_2i start, vec_2i offset);

    inline int *operator[](int row);
};

class Controller {
   public:
    struct Result {
        int score;
        int robbie_id;
        int map_id;
    };
    Controller();
    Controller(string save_path);
    ~Controller();
    int loop_controller;
    int loop_map;
    int robbie_cnt;
    float mutate_rate;
    float max_histyory;
    char save_path[255];
    char load_path[255];
    // Map map;
    int map_width;
    int map_height;
    // run
    bool save_run;
    bool running;
    bool chanegd;
    bool run_step;

    Robbie robbies[ROBBIE_CNT];
    Robbie robbies_temp[ROBBIE_CNT];
    float scores[ROBBIE_CNT];
    float scores_tf[ROBBIE_CNT];
    // void play(Robbie r, Map &m);
    void init();
    void train();
    void print_str();
    void playScreen(Robbie &rob, Map &map);
    Robbie loadRobbie(string robbie_path);
    void saveRobbie(Robbie &rob, string robbie_path);
    void addRobbie();
    void setMap(Map *map);
    int showHisgram(int num);
    int getIndex(float random_index);
};
#endif