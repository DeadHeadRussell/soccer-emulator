#include "dec.h"

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil) {
    /* Here messages to the application are saved */
    MSG messages;

    /* Data structure for the windowclass */
    WNDCLASSEX wincl;

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);

    /* Register the window class, and if  it fails quit the program */
    if (!RegisterClassEx (&wincl)) {
        return 0;
    }

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "ISL - Emulator",    /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           400,                 /* The programs width */
           350,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           ); 
   
    ShowWindow (hwnd, nFunsterStil);

    readTeamFiles();
    
    frameOneDec();
    frameTwoDec();
    frameThreeDec();
    frameFourDec();
    multFrameDec();

    frame = 1;
    inProg = false;

    while (GetMessage (&messages, NULL, 0, 0)) {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
        
        if (frame == 1) {
            ShowWindow(stat_percent,SW_HIDE);
            ShowWindow(stat_score,SW_HIDE);
            ShowWindow(btn_back,SW_HIDE);
            ShowWindow(btn_start,SW_SHOW);
            ShowWindow(btn_close,SW_SHOW);
        } else if (frame == 2) {
            ShowWindow(btn_start,SW_HIDE);
            ShowWindow(btn_close,SW_HIDE);
            ShowWindow(lbox_teamsOne,SW_SHOW);
            ShowWindow(lbox_teamsTwo,SW_SHOW);
            ShowWindow(btn_continue,SW_SHOW);
            ShowWindow(cb_ot,SW_SHOW);
            ShowWindow(cb_so,SW_SHOW);
            ShowWindow(stat_teamsOne,SW_SHOW);
            ShowWindow(stat_teamsTwo,SW_SHOW);
        } else if (frame == 3) {
            ShowWindow(lbox_teamsOne,SW_HIDE);
            ShowWindow(lbox_teamsTwo,SW_HIDE);
            ShowWindow(cb_ot,SW_HIDE);
            ShowWindow(cb_so,SW_HIDE);
            ShowWindow(stat_teamsOne,SW_HIDE);
            ShowWindow(stat_teamsTwo,SW_HIDE);
            ShowWindow(btn_continue,SW_HIDE);
            ShowWindow(stat_percent,SW_SHOW);
            if (!inProg) {
              inProg = true;
              pregame();  //the game
              game();
              postgame(); //ending of the game
              frame = 4;
            }
        } else if (frame == 4) {
            ShowWindow(stat_score,SW_SHOW);
            ShowWindow(btn_back,SW_SHOW);
            inProg = false;
        }
    }
    return messages.wParam;
}

void readTeamFiles() {
    system ("MD teams games rounds");
    system ("dir /O:N /B /A:-D teams > atemp.txt ");
    FILE * listFile;
    listFile = fopen("atemp.txt","r");
    num = -1;
    char s[256];
    while (!feof(listFile)) {
        fscanf(listFile,"%*s",s);
        num++;
    }
    clearerr(listFile);
    fseek(listFile,0,SEEK_SET);
    
    teams = new league[num];
    
    FILE * teamFile;
    char teamName[MAX_PATH];
    char teamFileName[MAX_PATH];
    
    for(int i=0;i<num;i++) {
        fscanf(listFile,"%s",teamName);
        strcpy(teamFileName,"teams\\");
        strcat(teamFileName,teamName);
        teamFile = fopen(teamFileName, "r");
        fscanf(teamFile,"%s%f%f%f%f%f%f%i%i%i%i",
            teams[i].teamName, &teams[i].off, &teams[i].mid,
            &teams[i].def, &teams[i].goal, &teams[i].coach,
            &teams[i].agg, &teams[i].gamesPlayed, &teams[i].gamesWon,
            &teams[i].yf, &teams[i].rf);
        fclose(teamFile);
    }
    fclose(listFile);
    system("del atemp.txt");
}

void frameOneDec() {
    btn_start = CreateWindowEx (0,"BUTTON","Start",WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP
                                ,160,150,80,30,hwnd,(HMENU)BTN_START,NULL,0);
   
    btn_close = CreateWindowEx (0,"BUTTON","Close",WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP
                                ,160,200,80,30,hwnd,(HMENU)BTN_CLOSE,NULL,0);
}

void frameTwoDec() {
    lbox_teamsOne = CreateWindowEx (0,"LISTBOX",NULL,WS_CHILD|WS_BORDER|LBS_DISABLENOSCROLL
                                  ,100,110,100,170,hwnd,(HMENU)LBOX_TEAMONE,NULL,0);
    
    lbox_teamsTwo = CreateWindowEx (0,"LISTBOX",NULL,WS_CHILD|WS_BORDER|WS_TABSTOP
                                  ,250,110,100,170,hwnd,(HMENU)LBOX_TEAMTWO,NULL,0);
    
    stat_teamsOne = CreateWindowEx (0,"STATIC","Home:",WS_CHILD
                                  ,55,110,45,20,hwnd,(HMENU)STAT_TEAMONE,NULL,0);

    stat_teamsTwo = CreateWindowEx (0,"STATIC","Away:",WS_CHILD
                                  ,210,110,40,20,hwnd,(HMENU)STAT_TEAMTWO,NULL,0);
    
    btn_continue = CreateWindowEx (0, "BUTTON","Continue",WS_CHILD|WS_BORDER|WS_TABSTOP
                                  ,310,280,75,25,hwnd,(HMENU)BTN_CONT,NULL,0);
    
    cb_ot = CreateWindowEx (0, "BUTTON","Over Time",WS_CHILD|WS_TABSTOP|BS_AUTOCHECKBOX
                                  ,20,280,100,25,hwnd,(HMENU)CB_OT,NULL,0);
    
    cb_so = CreateWindowEx (0, "BUTTON","Shoot Out",WS_CHILD|WS_TABSTOP|BS_AUTOCHECKBOX
                                  ,150,280,100,25,hwnd,(HMENU)CB_SO,NULL,0);
    
    int pos;  
    int pos2;                            
    for (int i = 0; i < num; i++) {
        pos = (int)SendMessage(lbox_teamsOne, LB_ADDSTRING, 0, 
                    (LPARAM) teams[i].teamName); 
        pos2 = (int)SendMessage(lbox_teamsTwo, LB_ADDSTRING, 0, 
                    (LPARAM) teams[i].teamName); 
                    
        SendMessage(lbox_teamsOne, LB_SETITEMDATA, pos, (LPARAM) i); 
        SendMessage(lbox_teamsTwo, LB_SETITEMDATA, pos2, (LPARAM) i); 
    }
}

void frameThreeDec() {
    stat_percent = CreateWindowEx (0,"STATIC","Game in progress...",WS_CHILD,50,150,300,30
                                  ,hwnd,(HMENU)STAT_PERC,NULL,0);
}

void frameFourDec() {
    stat_score = CreateWindowEx (0,"STATIC","",WS_CHILD,50,180,200,40
                                  ,hwnd,(HMENU)STAT_SCORE,NULL,0);
                                  
    btn_back = CreateWindowEx (0,"BUTTON","Main Menu",WS_CHILD|WS_BORDER|WS_TABSTOP
                                ,160,230,80,30,hwnd,(HMENU)BTN_BACK,NULL,0);
}

void multFrameDec() {
    stat_ISL = CreateWindowEx (0,"STATIC","Soccer Emulator",
                              WS_CHILD|WS_VISIBLE,15,20,340,25,hwnd,(HMENU)STAT_ISL,NULL,0);

    setFont(stat_ISL,14,600);
    setFont(stat_GE,12,400);
    setFont(stat_credits,12,400);
}

void setFont(HWND cnt_hwnd,int size,int bold) {
    HFONT hfont;
    HDC hdc;
    long lfHeight;
    
    hdc = GetDC(NULL);
    lfHeight = -MulDiv(size, GetDeviceCaps(hdc, LOGPIXELSY), 72);
    ReleaseDC(NULL, hdc);

    hfont = CreateFont(
          lfHeight,               // height of font
          0,                // average character width
          0,           // angle of escapement
          0,          // base-line orientation angle
          bold,              // font weight
          FALSE,           // italic attribute option
          FALSE,        // underline attribute option
          FALSE,        // strikeout attribute option
          DEFAULT_CHARSET,          // character set identif ier
          OUT_CHARACTER_PRECIS,  // output precision
          CLIP_CHARACTER_PRECIS,    // clipping precision
          ANTIALIASED_QUALITY,          // output quality
          FF_DONTCARE,   // pitch and family
          "Comic Sans MS"           // typeface name
    ); 

    SendMessage(cnt_hwnd, WM_SETFONT, (WPARAM)hfont, TRUE);
    DeleteObject(hfont);
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_SETFONT:
        break;
        case WM_ACTIVATE:
            setFont(stat_ISL,14,600);
            setFont(stat_GE,12,400);
            setFont(stat_credits,12,400);
        break;
        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case BTN_START:
                    frame++;
                break;
                case BTN_CLOSE:
                    PostQuitMessage(0);
                break;
                case BTN_CONT:
                    if (SendMessage (lbox_teamsOne,LB_GETCURSEL,0,0) == LB_ERR ||
                       SendMessage (lbox_teamsTwo,LB_GETCURSEL,0,0) == LB_ERR ){
                        MessageBox(hwnd,"You have not selected two teams","Error",MB_OK);
                        break;
                    } else {
                        teamOne = SendMessage (lbox_teamsOne,LB_GETCURSEL,0,0);
                        teamTwo = SendMessage (lbox_teamsTwo,LB_GETCURSEL,0,0);
                        if (teamOne == teamTwo) {
                            MessageBox(hwnd,"Both teams you have selected are the same","Error",MB_OK);
                            break;
                        } else {
                            frame++;
                        }
                    }
                break;
                case BTN_BACK:
                    frame = 1;
                break;
            }
        break;
        case WM_DESTROY:
            PostQuitMessage (0);
            break;
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

double random(double low, double high, double divide) {
    double rands;
    float range;
    range = (high - low);
    rands = (low + ((int) (10 * (range * rand() / (RAND_MAX + 1.0)))) / 10) / divide;
    return rands;
} 

double abs(double x) {
    if (x < 0){
        x *= -1;
    }
    return x;
}
