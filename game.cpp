#include "ext.h"

void pregame() {
    // get pos of teams
    int i1 = SendMessage(lbox_teamsOne, LB_GETITEMDATA, teamOne, 0);
    int i2 = SendMessage(lbox_teamsTwo, LB_GETITEMDATA, teamTwo, 0);

    // moral mod
    float mor;
    if (teams[teamOne].gamesPlayed != 0) {
        mor = teams[teamOne].gamesWon / teams[teamOne].gamesPlayed;
    } else {
        mor = 0;
    }

    mor += 1;

    mor *= random(14, 30, 20);

    // declare home team
    team homea = {
      teams[teamOne].teamName, true, 0, 0, 0, 0,
      teams[teamOne].off * 1.1 * mor,
      teams[teamOne].mid * 1.1 * mor,
      teams[teamOne].def * 1.1 * mor,
      teams[teamOne].goal * 1.1 * mor,
      teams[teamOne].agg, 0, 0, 0, false, 0
    };

    // mor mod
    if (teams[teamTwo].gamesPlayed != 0) {
        mor = teams[teamTwo].gamesWon / teams[teamTwo].gamesPlayed;
    } else {
        mor = 0;
    }

    mor += 1;

    mor *= random(14, 30, 20);

    // declare away team
    team awaya = {
      teams[teamTwo].teamName, false, 0, 0, 0, 0,
      teams[teamTwo].off * mor,
      teams[teamTwo].mid * mor,
      teams[teamTwo].def * mor,
      teams[teamTwo].goal * mor,
      teams[teamTwo].agg, 0, 0, 0, false, 1
    };

    // put into global variables
    home = homea;
    away = awaya;

    // open round by round file
    char roundFileName[MAX_PATH];

    strcpy(gameFileName, home.teamname);
    strcat(gameFileName, " vs. ");
    strcat(gameFileName, away.teamname);
    strcat(gameFileName, ".txt");

    strcpy(roundFileName, "rounds\\");
    strcat(roundFileName, gameFileName);

    gameFile = fopen (roundFileName, "w");

    otb = (bool)SendMessage(cb_ot, BM_GETCHECK, 0, 0);
    sob = (bool)SendMessage(cb_so, BM_GETCHECK, 0, 0);
    // set starting variables
    pos = 0;
    round = 1;
    totRounds = 90;
    totRoundsm = 0;
    sobb = false;
    srand((unsigned) time(0));
}

void game() {
    int rands;
    char roundc[5];
    while (round <= totRounds) {
      totRoundsm++;
      if (round == (int) (totRounds / 2)) {
          home.poss = false;
          away.poss = true;
          home.status = 1;
          away.status = 0;
          pos = 0;
          fputs ("Half Time:\n\n", gameFile);
          home.off *= (1 + (home.possRounds / totRoundsm));
          home.mid *= (1 + (home.possRounds / totRoundsm));
          home.def *= (1 + (home.possRounds / totRoundsm));
          home.goal *= (1 + (home.possRounds / totRoundsm));
          away.off *= (1 + (away.possRounds / totRoundsm));
          away.mid *= (1 + (away.possRounds / totRoundsm));
          away.def *= (1 + (away.possRounds / totRoundsm));
          away.goal *= (1 + (away.possRounds / totRoundsm));
      }
      itoa(round, roundc, 10);
      fputs("Round: ", gameFile);
      fputs(roundc, gameFile);
      fputs("\n", gameFile);
      if (home.poss) {
          if (home.status == 0) {
              pos -= .5;
              home.status = 1;
              fputs ("Home moved .5\n", gameFile);
          } else {
              rands = (int) random(1, 100, 1);
              home.status = getstatus(rands);
              if (pos >= 0) {
                  home.status = 1;
              }
              if (pos == 5) {
                  test = (home.def * random(7, 60, 20)) / (away.off * random(7, 60, 20));
              } else if (pos > 0) {
                  test = (((home.def + home.mid) / 2) * random(7, 60, 20)) / 
                         (((away.off + away.mid) / 2) * random(7, 60, 20));
              } else if (pos == 0) {
                  test = (home.mid * random(7, 60, 20)) / (away.mid * random(7, 60, 20));
              } else if (pos > -5) {
                  test = (((home.off + home.mid) / 2) * random(7, 60, 20)) / 
                         (((away.def + away.mid) / 2) * random(7, 60, 20));
              } else if (pos == -5) {
                  test = (home.off * random(7, 60, 20)) / (away.def * random(7, 60, 20));
              }
              if (home.status == 1) {
                  if (test >= 2) {
                      pos -= 1.5;
                      fputs ("Home moved 1.5\n", gameFile);
                  } else if (test >= 1.5) {
                      pos -= 1;
                      fputs ("Home moved 1\n", gameFile);
                  } else if (test >= 1.2) {
                      pos -= .5;
                      fputs ("Home moved .5\n", gameFile);
                  } else if (test >= .83) {
                      pos -= 0;
                      fputs ("Home kept possession\n", gameFile);
                  } else if (test >= .75) {
                      home.poss = false;
                      away.poss = true;
                      fputs ("Away took possession from Home\n", gameFile);
                  } else if (test >= .5) {
                      home.poss = false;
                      away.poss = true;
                      pos += .5;
                      fputs ("Away took possession from Home and moved .5\n", gameFile);
                  } else {
                      home.poss = false;
                      away.poss = true;
                      pos += 1;
                      fputs ("Away took possession from Home and moved 1\n", gameFile);
                  }
                  rands = (int) random(1, 10, 1);
                  if (rands == 4) {
                      away.foul += (int) (random(1, 100, 1) * away.agg);
                  } else if (rands == 2 || rands == 8) {
                      away.foul += (int) (random(1, 80, 1) * away.agg);
                  } else {
                      away.foul += (int) (random(1, 60, 1) * away.agg);
                  }
                  rands = (int) random(1, 10, 1);
                  if (rands == 4) {
                      home.foul += (int) (random(1, 80, 1) * home.agg);
                  } else if (rands == 2 || rands == 8) {
                      home.foul += (int) (random(1, 60, 1) * home.agg);
                  } else {
                      home.foul += (int) (random(1, 40, 1) * home.agg);
                  }
              } else {
                  if (test*1.5 > 1) {
                      if  (pos > -2) {
                          test2 = (home.mid * random(7, 60, 20)) / (away.goal * random(7, 60, 20));
                      } else {
                          test2 = (home.off * random(7, 60, 20)) / (away.goal * random(7, 60, 20));
                      }
                      home.shots++;
                      if (test2 > 1.5) {
                          home.goals++;
                          away.status = 0;
                          pos = 0;
                          home.poss = false;
                          away.poss = true;
                          if (totRounds == 90) {
                              fputs ("Home shot and scored\n", gameFile);
                          } else {
                              fputs ("Home shot and won in overtime\n", gameFile);
                              break;
                          }
                      } else {
                          away.status = 1;
                          pos = -4;
                          home.poss = false;
                          away.poss = true;
                          fputs ("Home shot and missed\n", gameFile);
                      }
                  } else {
                      away.status = 1;
                      pos = -5;
                      home.poss = false;
                      away.poss = true;
                      fputs ("Home shot but was blocked\n", gameFile);
                  }
              }
          }
          if (away.foul > 799) {
              away.rf++;
              away.off -= (8 / away.foul);
              away.def -= (8 / away.foul);
              away.mid -= (8 / away.foul);
              away.goal -= (8 / away.foul);
              home.status = 0;
              fputs ("Away got a red card\n", gameFile);
          } else if (away.foul > 750) {
              away.yf++;
              if (away.yfb) {
                  away.off -= (8 / away.foul);
                  away.def -= (8 / away.foul);
                  away.mid -= (8 / away.foul);
                  away.goal -= (8 / away.foul);
              }
              away.yfb = !away.yfb;
              home.status = 0;
              fputs ("Away got a yellow card\n", gameFile);
          } else if (home.foul > 799) {
              home.rf++;
              home.off -= (8 / home.foul);
              home.def -= (8 / home.foul);
              home.mid -= (8 / home.foul);
              home.goal -= (8 / home.foul);
              away.status = 0;
              away.poss = true;
              home.poss = false;
              fputs ("Home got a red card\n", gameFile);
          } else if (home.foul > 750) {
              home.yf++;
              if (home.yfb) {
                  home.off -= (8 / home.foul);
                  home.def -= (8 / home.foul);
                  home.mid -= (8 / home.foul);
                  home.goal -= (8 / home.foul);
              }
              home.yfb = !home.yfb;
              away.status = 0;
              away.poss = true;
              home.poss = false;
              fputs ("Home got a yellow card\n", gameFile);
          }
          home.possRounds++;
      } else {
          if (away.status == 0) {
              pos += .5;
              away.status = 1;
              fputs ("Away moved .5\n", gameFile);
          } else {
              rands = (int) random(1, 100, 1);
              away.status = getstatus(rands);
              if (pos <= 0) {
                  away.status = 1;
              }
              if (pos == 5) {
                  test = (home.def * random(7, 60, 20)) / (away.off * random(7, 60, 20));
              } else if (pos > 0) {
                  test = (((home.def + home.mid) / 2) * random(7, 60, 20)) / 
                         (((away.off + away.mid) / 2) * random(7, 60, 20));
              } else if (pos == 0) {
                  test = (home.mid * random(7, 60, 20)) / (away.mid * random(7, 60, 20));
              } else if (pos > -5) {
                  test = (((home.off + home.mid) / 2) * random(7, 60, 20)) / 
                         (((away.def + away.mid) / 2) * random(7, 60, 20));
              } else if (pos == -5) {
                  test = (home.off * random(7, 60, 20)) / (away.def * random(7, 60, 20));
              }
              if (away.status == 1) {
                  if (test >= 2) {
                      home.poss = true;
                      away.poss = false;
                      pos -= 1;
                      fputs ("Home took possession from Away and moved 1\n", gameFile);
                  } else if (test >= 1.5) {
                      home.poss = true;
                      away.poss = false;
                      pos -= .5;
                      fputs ("Home took possession from Away and moved .5\n", gameFile);
                  } else if (test >= 1.2) {
                      home.poss = true;
                      away.poss = false;
                      fputs ("Home took possession from Away\n", gameFile);
                  } else if (test >= .83) {
                      pos -= 0;
                      fputs ("Away kept possession\n", gameFile);
                  } else if (test >= .75) {
                      pos += .5;
                      fputs ("Away moved .5\n", gameFile);
                  } else if (test >= .5) {
                      pos += 1;
                      fputs ("Away moved 1\n", gameFile);
                  } else {
                      pos += 1.5;
                      fputs ("Away moved 1.5\n", gameFile);
                  }
                  rands = (int) random(1, 10, 1);
                  if (rands == 4) {
                      home.foul += (int) (random(1, 100, 1) * home.agg);
                  } else if (rands == 2 || rands == 8) {
                      home.foul += (int) (random(1, 80, 1) * home.agg);
                  } else {
                      home.foul += (int) (random(1, 60, 1) * home.agg);
                  }
                  rands = (int) random(1, 10, 1);
                  if (rands == 4) {
                      away.foul += (int) (random(1, 80, 1) * away.agg);
                  } else if (rands == 2 || rands == 8) {
                      away.foul += (int) (random(1, 60, 1) * away.agg);
                  } else {
                      away.foul += (int) (random(1, 40, 1) * away.agg);
                  }
              } else {
                  if (test / 1.5 < 1) {
                      if  (pos > -2) {
                          test2 = (away.mid * random(7, 60, 20)) / (home.goal * random(7, 60, 20));
                      } else {
                          test2 = (away.off * random(7, 60, 20)) / (home.goal * random(7, 60, 20));
                      }
                      away.shots++;
                      if (test2 > 1.5) {
                          away.goals++;
                          home.status = 0;
                          pos = 0;
                          away.poss = false;
                          home.poss = true;
                          if (totRounds == 90) {
                              fputs ("Away shot and scored\n", gameFile);
                          } else {
                              fputs ("Away shot and won in overtime\n", gameFile);
                              break;
                          }
                      } else {
                          home.status = 1;
                          pos = 4;
                          away.poss = false;
                          home.poss = true;
                          fputs ("Away shot and missed\n", gameFile);
                      }
                  } else {
                      home.status = 1;
                      pos = 5;
                      away.poss = false;
                      home.poss = true;
                      fputs ("Away shot but was blocked\n", gameFile);
                  }
              }
          }
          if (home.foul > 799) {
              home.rf++;
              home.off -= (8 / home.foul);
              home.def -= (8 / home.foul);
              home.mid -= (8 / home.foul);
              home.goal -= (8 / home.foul);
              away.status = 0;
              fputs ("Home got a red card\n", gameFile);
          } else if (home.foul > 750) {
              home.yf++;
              if (home.yfb) {
                  home.off -= (8 / home.foul);
                  home.def -= (8 / home.foul);
                  home.mid -= (8 / home.foul);
                  home.goal -= (8 / home.foul);
              }
              home.yfb = !home.yfb;
              away.status = 0;
              fputs ("Home got a yellow card\n", gameFile);
          } else if (away.foul > 799) {
              away.rf++;
              away.off -= (8 / away.foul);
              away.def -= (8 / away.foul);
              away.mid -= (8 / away.foul);
              away.goal -= (8 / away.foul);
              home.status = 0;
              home.poss = true;
              away.poss = false;
              fputs ("Away got a red card\n", gameFile);
          } else if (away.foul > 750) {
              away.yf++;
              if (away.yfb) {
                  away.off -= (8 / away.foul);
                  away.def -= (8 / away.foul);
                  away.mid -= (8 / away.foul);
                  away.goal -= (8 / away.foul);
              }
              away.yfb = !away.yfb;
              home.status = 0;
              home.poss = true;
              away.poss = false;
              fputs ("Away got a yellow card\n", gameFile);
          }
          away.possRounds++;
      }
      away.foul = 0;
      home.foul = 0;
      if (pos > 5) {
          pos = 5;
      } else if (pos < -5) {
          pos = -5;
      }

      sprintf(roundc, "%.1f", pos);
      fputs ("Position: ", gameFile);
      fputs (roundc, gameFile);
      fputs ("\n\n", gameFile);
      round++;
      // Overtime
      if (otb && home.goals == away.goals && round > totRounds) {
          round = 1;
          totRounds = 30;
          home.poss = true;
          away.poss = false;
          home.status = 0;
          away.status = 1;
          pos = 0;
          fputs ("Over Time:\n\n", gameFile);
          home.off *= (1 + (home.possRounds / totRoundsm));
          home.mid *= (1 + (home.possRounds / totRoundsm));
          home.def *= (1 + (home.possRounds / totRoundsm));
          home.goal *= (1 + (home.possRounds / totRoundsm));
          away.off *= (1 + (away.possRounds / totRoundsm));
          away.mid *= (1 + (away.possRounds / totRoundsm));
          away.def *= (1 + (away.possRounds / totRoundsm));
          away.goal *= (1 + (away.possRounds / totRoundsm));
          otb = false;
      }
    }

    // end game loop
    // shoot outs
    if (sob && home.goals == away.goals) {
        sobb = true;
        totRounds = 5;
        round = 1;
        float hGoal, vGoal, hShot, vShot, factor;
        bool sd;
        sd = false;
        fputs("Shoot Out:\n\n", gameFile);
        while (round <= totRounds) {
            hShot = random(-4.7, 4.7, 1);
            vShot = random(1, 2.7, 1);
            hGoal = random(-5, 5, 1);
            vGoal = random(1, 3, 1);
            hShot += ((int) (10 * random(-8 / home.off, 8 / home.off, 1))) / (double) 10;
            vShot += ((int) (10 * random(-4 / home.off, 4 / home.off, 1))) / (double) 10;
            if (vShot <= 0) {
                vShot = 1;
            }
            factor = away.goal / 8 * random(2, 8, 4);
            if (hShot <= 5 && hShot >= -5 && vShot <= 3) {
                if (vGoal - vShot <= factor) {
                    if (hGoal - hShot <= factor && hGoal - hShot >= -factor) {
                        fputs ("Home's shot was blocked\n", gameFile);
                    } else {
                        home.sogoals++;
                        fputs ("Home scored shot\n", gameFile);
                    }
                } else {
                    home.sogoals++;
                    fputs ("Home scored shot\n", gameFile);
                }
            } else {
                fputs ("Home's shot missed\n", gameFile);
            }
            hShot = random(-4.7, 4.7, 1);
            factor = random(1, 2.7, 1);
            vShot = factor;
            hGoal = random(-5, 5, 1);
            vGoal = random(1, 3, 1);
            factor = ((int) (10*random(-8 / away.off, 8 / away.off, 1))) / (double) 10;
            hShot += factor;
            factor = ((int) (10*random(-4 / away.off, 4 / away.off, 1))) / (double) 10;
            vShot += factor;
            if (vShot <= 0) {
                vShot = 1;
            }
            factor = (home.goal / 8) * random(2, 8, 4);
            if (hShot <= 5 && hShot >= -5 && vShot <= 3) {
                if (vGoal - vShot <= factor) {
                    if (hGoal - hShot <= factor && hGoal - hShot >= -factor) {
                        fputs ("Away's shot was blocked\n", gameFile);
                    } else {
                        away.sogoals++;
                        fputs ("Away scored shot\n", gameFile);
                    }
                } else {
                    away.sogoals++;
                    fputs ("Away scored shot\n", gameFile);
                }
            } else {
                fputs ("Away's shot missed\n", gameFile);
            }
            if (round == totRounds && away.sogoals == home.sogoals) {
                round = 0;
                sd = true;
            }
            if (sd) {
                round = 0;
                if (home.sogoals != away.sogoals) {
                    break;
                }
            }
            round++;
        }
    }
}

void postgame() {
     // Setting up the score
    SendMessage(stat_percent, WM_SETTEXT, 0, (LPARAM)"Setting up score...");
    char score[MAX_PATH];
    char num[64];
    strcpy(score, "Score: ");
    strcat(score, home.teamname);
    strcat(score, " ");
    itoa(home.goals, num, 10);
    strcat(score, num);
    strcat(score, "-");
    strcat(score, away.teamname);
    strcat(score, " ");
    itoa(away.goals, num, 10);
    strcat(score, num);
    // if  nescesary,  set up so score
    if (sobb) {
        strcat(score, "\nShootout: ");
        strcat(score, home.teamname);
        strcat(score, " ");
        itoa(home.sogoals, num, 10);
        strcat(score, num);
        strcat(score, "-");
        strcat(score, away.teamname);
        strcat(score, " ");
        itoa(away.sogoals, num, 10);
        strcat(score, num);
    }
    SendMessage(stat_score, WM_SETTEXT, 0, (LPARAM)score);

    // set up cards
    char fouls[MAX_PATH];
    strcpy(fouls, "Fouls: ");
    strcat(fouls, home.teamname);
    strcat(fouls, " Red: ");
    itoa(home.rf, num, 10);
    strcat(fouls, num);
    strcat(fouls, " Yellow: ");
    itoa(home.yf, num, 10);
    strcat(fouls, num);
    strcat(fouls, "-");
    strcat(fouls, away.teamname);
    strcat(fouls, " Red: ");
    itoa(away.rf, num, 10);
    strcat(fouls, num);
    strcat(fouls, " Yellow: ");
    itoa(away.yf, num, 10);
    strcat(fouls, num);

    // Writing to the game file
    SendMessage(stat_percent, WM_SETTEXT, 0, (LPARAM)"Writing to game file...");
    char finishedFileName[MAX_PATH];

    strcpy(finishedFileName, "games\\");
    strcat(finishedFileName, gameFileName);

    fclose(gameFile);
    gameFile = fopen(finishedFileName, "w");

    fputs(score, gameFile);
    fputs("\n", gameFile);
    fputs(fouls, gameFile);
    fputs("\n", gameFile);
    fputs(home.teamname,  gameFile);
    fputs(":\nPossesion: ",  gameFile);
    sprintf(num, "%.2f",  ((float)home.possRounds / totRoundsm));
    fputs(num,  gameFile);
    fputs("\n",  gameFile);
    fputs(away.teamname,  gameFile);
    fputs(":\nPossession: ",  gameFile);
    sprintf(num, "%.2f",  ((float)away.possRounds / totRoundsm));
    fputs(num,  gameFile);
    fclose(gameFile);

    // writing to the team files
    SendMessage(stat_percent, WM_SETTEXT, 0, (LPARAM)"Writing to team files...");

    if (home.goals > away.goals) {
        teams[teamOne].gamesWon++;
    } else if (home.goals < away.goals) {
        teams[teamTwo].gamesWon++;
    } else if (sob) {
        if (home.sogoals > away.sogoals) {
            teams[teamOne].gamesWon++;
        } else if (home.sogoals < away.sogoals) {
            teams[teamTwo].gamesWon++;
        }
    }
    teams[teamOne].gamesPlayed++;
    teams[teamTwo].gamesPlayed++;
    teams[teamOne].off += ((teams[teamOne].coach * home.poss) / 25);
    teams[teamOne].mid += ((teams[teamOne].coach * home.poss) / 25);
    teams[teamOne].def += ((teams[teamOne].coach * home.poss) / 25);
    teams[teamOne].goal += ((teams[teamOne].coach * home.poss) / 25);
    teams[teamOne].rf += home.rf;
    teams[teamOne].yf += home.yf;
    teams[teamTwo].off += ((teams[teamTwo].coach * away.poss) / 25);
    teams[teamTwo].mid += ((teams[teamTwo].coach * away.poss) / 25);
    teams[teamTwo].def += ((teams[teamTwo].coach * away.poss) / 25);
    teams[teamTwo].goal += ((teams[teamTwo].coach * away.poss) / 25);
    teams[teamTwo].rf += away.rf;
    teams[teamTwo].yf += away.yf;

    char tnf[MAX_PATH];

    strcpy(tnf, "teams\\");
    strcat(tnf, teams[teamOne].teamName);
    strcat(tnf, ".txt");

    gameFile = fopen(tnf, "w");

    fprintf(gameFile, "%s %f %f %f %f %f %f %i %i %i %i",
        teams[teamOne].teamName, teams[teamOne].off,
        teams[teamOne].mid, teams[teamOne].def,
        teams[teamOne].goal, teams[teamOne].coach,
        teams[teamOne].agg, teams[teamOne].gamesPlayed,
        teams[teamOne].gamesWon , teams[teamOne].yf,
        teams[teamOne].rf);

    fclose(gameFile);

    strcpy(tnf, "teams\\");
    strcat(tnf, teams[teamTwo].teamName);
    strcat(tnf, ".txt");

    gameFile = fopen(tnf, "w");

    fprintf(gameFile, "%s %f %f %f %f %f %f %i %i %i %i",
        teams[teamTwo].teamName, teams[teamTwo].off,
        teams[teamTwo].mid, teams[teamTwo].def,
        teams[teamTwo].goal, teams[teamTwo].coach,
        teams[teamTwo].agg, teams[teamTwo].gamesPlayed,
        teams[teamTwo].gamesWon, teams[teamOne].yf,
        teams[teamOne].rf);

    fclose(gameFile);
    SendMessage(stat_percent, WM_SETTEXT, 0, (LPARAM)"Game Complete");
}

int getstatus(double rands) {
    if (abs(pos) == 1) {
        if (rands <= 5) {
            return 2;
        } else {
            return 1;
        }
    } else if (abs(pos) == 1.5) {
        if (rands <= 10) {
            return 2;
        } else {
            return 1;
        }
    } else if (abs(pos) == 2) {
        if (rands <= 15) {
            return 2;
        } else {
            return 1;
        }
    } else if (abs(pos) == 2.5) {
        if (rands <= 25) {
            return 2;
        } else {
            return 1;
        }
    } else if (abs(pos) == 3) {
        if (rands <= 35) {
            return 2;
        } else {
            return 1;
        }
    } else if (abs(pos) == 3.5) {
        if (rands <= 55) {
            return 2;
        } else {
            return 1;
        }
    } else if (abs(pos) == 4) {
        if (rands <= 75) {
            return 2;
        } else {
            return 1;
        }
    } else if (abs(pos) == 4.5) {
        if (rands <= 95) {
            return 2;
        } else {
            return 1;
        }
    } else if (abs(pos) == 5) {
        return 2;
    }
    return 1;
}
