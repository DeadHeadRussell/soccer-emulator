#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>

#define STAT_CREDITS    105
#define LBOX_TEAMONE    106
#define LBOX_TEAMTWO    107
#define BTN_CONT        108
#define STAT_PERC       109
#define STAT_SCORE      110
#define BTN_BACK        111
#define CB_OT           112
#define CB_SO           113
#define STAT_TEAMONE    114
#define STAT_TEAMTWO    115

//functions

void pregame();
void game();
void postgame();
int getstatus (double rands);
double random(double low, double high, double divide);
double abs(double x);

//structs
typedef struct{
    char teamName[256];
    float off;
    float mid;
    float def;
    float goal;
    float coach;
    float agg;
    int gamesPlayed;
    int gamesWon;
    int yf;
    int rf;
} league;

typedef struct{
    char *teamname;
    bool poss;
    int possRounds;
    int goals;
    int shots;
    int sogoals;
    double off;
    double mid;
    double def;
    double goal;
    double agg;
    int yf;
    int rf;
    int foul;
    bool yfb;
    int status;
} team;

//struct variables
extern league *teams;
extern team home,away;

//windows and controls
extern HWND hwnd;
extern HWND btn_start,btn_close,btn_continue,btn_back;
extern HWND stat_ISL,stat_GE,stat_credits,stat_percent,stat_score,stat_teamsOne,stat_teamsTwo;
extern HWND lbox_teamsOne,lbox_teamsTwo;
extern HWND cb_ot,cb_so;

//files
extern FILE * gameFile;

//varialbes
extern int frame,teamOne,teamTwo,round,totRounds,totRoundsm;
extern double test,test2,pos;
extern bool inProg, otb, sob, sobb;
extern int num;
extern char gameFileName[MAX_PATH];
