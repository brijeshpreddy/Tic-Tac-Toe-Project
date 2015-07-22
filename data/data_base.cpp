#include "data_base.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

  tic_tac_database::tic_tac_database(bool disp) {
    disp_m = disp;
  }

  tic_tac_database::tic_tac_database() {
    int i, j;
    for (i=0; i<3; i++)
      for (j=0; j<3; j++)  database[i][j] = 'b';
  }

  void tic_tac_database::reset_game() {
    int i, j;
    for (i=0; i<3; i++)
      for (j=0; j<3; j++)  database[i][j] = 'b';
  }

  void tic_tac_database::mute_display() {
    disp_m = 0;
  }

  void tic_tac_database::set_display() {
    disp_m = 1;
  }

  int tic_tac_database::pos_occupied(int x, int y) {
    if (database[x][y] == 'b') return 0;
    else return 1;
  }

  int tic_tac_database::mark_position(int x, int y, char ch) {
    int i, j;
    if (pos_occupied(x, y)) {
      if (disp_m) cout << "Position Taken Jackass !!!!" << endl;
      return 0;
    }
    else if (!((x >= 0) && (x <= 2) && (y >= 0) && (y <= 2) && ((ch != 'x') || (ch != 'o')))) {
      if (disp_m) cout << "Wrong Position Jackass !!!!" << endl;
      return 0;
    }
    else {
      if (!winning_position()) {
	database[x][y] = ch;
	if (disp_m) display();
	return 1;
      }
      else {
	if (disp_m) cout << "Your Game is Done Man - Reset" << endl;
	return 0;
      }
    }
  }

  void tic_tac_database::display() {
    int i, j;
    cout << "_________" << endl;
    for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
      {
	if (database[i][j] == 'b')
	  cout << "   ";
	else if (database[i][j] == 'x')
	  cout << " x ";
	else if (database[i][j] == 'o')
	  cout << " o ";
	else
	  cout << "\n ERROR in game \n";
      }
      cout << endl;
    }
    cout << "_________" << endl;
  } 
    
  int tic_tac_database::winning_position() {
    int i;
    if (((database[0][0] == database[1][1]) && (database[1][1] == database[2][2])) || ((database[0][2] == database[1][1]) && (database[1][1] == database[2][0]))) {
      if (database[1][1] != 'b') return 1;
    }
    for (i=0; i<=2; i++) {
      if ((database[i][0] == database[i][1]) && (database[i][1] == database[i][2])) {
	if (database[i][1] != 'b') return 1;
      }
      else if ((database[0][i] == database[1][i]) && (database[1][i] == database[2][i])) {
	if (database[1][i] != 'b') return 1;
      }
    }
    return 0;
  }

  char tic_tac_database::winner() {
    int i;
    if (((database[0][0] == database[1][1]) && (database[1][1] == database[2][2])) || ((database[0][2] == database[1][1]) && (database[1][1] == database[2][0]))) {
      if (database[1][1] != 'b') return database[1][1];
    }
    for (i=0; i<=2; i++) {
      if ((database[i][0] == database[i][1]) && (database[i][1] == database[i][2])) {
	if (database[i][1] != 'b') return database[i][1];
      }
      else if ((database[0][i] == database[1][i]) && (database[1][i] == database[2][i])) {
	if (database[1][i] != 'b') return database[1][i];
      }
    }
    return 'd';
  }

  int tic_tac_database::completion_status() {
    int i, j;
    for (i=0; i<3; i++) 
      for (j=0; j<3; j++) 
	if (database[i][j] == 'b') return 0;
    return 1;
  }

  int tic_tac_database::slots() {
    int i, j, count;
    count = 0;
    for (i=0; i<3; i++) 
      for (j=0; j<3; j++) 
	if (database[i][j] == 'b') count++;
    return count; 
  }

  void tic_tac_database::declare_result() {
    if (winning_position())
      if (disp_m) cout << "Winner -------- " << winner() << endl;
    else if (winner() == 'd')
      if (disp_m) cout << "Draw Dude... Bluh" << endl;
  }
