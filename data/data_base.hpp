#ifndef DATABASE
#define DATABASE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

class tic_tac_database {
  
  private :
    bool disp_m;

  public :
    tic_tac_database(bool disp);
    tic_tac_database();
    char database[3][3];
    void reset_game();
    void mute_display();
    void set_display();
    int pos_occupied(int x, int y);
    int mark_position(int x, int y, char ch);
    void display();
    int winning_position();
    char winner();
    int completion_status();
    int slots();
    void declare_result();

};

#endif

