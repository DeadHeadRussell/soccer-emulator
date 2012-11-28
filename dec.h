#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>

#define BTN_START       101
#define BTN_CLOSE       102
#define STAT_ISL        103
#define STAT_GE         104
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
void readTeamFiles();
void frameOneDec();
void frameTwoDec();
void frameThreeDec();
void frameFourDec();
void multFrameDec();
void setFont(HWND cnt_hwnd, int size, int bold);
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
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
league *teams;
team home,away;

//windows and controls
HWND hwnd;
HWND btn_start,btn_close,btn_continue,btn_back;
HWND stat_ISL,stat_GE,stat_credits,stat_percent,stat_score,stat_teamsOne,stat_teamsTwo;
HWND lbox_teamsOne,lbox_teamsTwo;
HWND cb_ot,cb_so;

//files
FILE * gameFile;

//varialbes
int frame,teamOne,teamTwo,round,totRounds,totRoundsm;
double test,test2,pos;
bool inProg,otb,sob,sobb;
int num;
char gameFileName[MAX_PATH];
char szClassName[ ] = "Soccer Emulator";
