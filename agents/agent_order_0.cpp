#include "agent_order_0.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;
//typedef tic_tac_database;

  tic_tac_agent_order_0::tic_tac_agent_order_0(tic_tac_database x) {
    present_game_state = x;
  }

  int tic_tac_agent_order_0::winning_position() {
    int i, j, win_b;
    if (((present_game_state.database[0][0] == present_game_state.database[1][1]) && (present_game_state.database[1][1] == present_game_state.database[2][2])) || ((present_game_state.database[0][2] == present_game_state.database[1][1]) && (present_game_state.database[1][1] == present_game_state.database[2][0]))) {
      if (present_game_state.database[1][1] != 'b') return 1;
    }
    for (i=0; i<2; i++) {
      if ((present_game_state.database[i][0] == present_game_state.database[i][1]) && (present_game_state.database[i][1] == present_game_state.database[i][2])) {
	if (present_game_state.database[i][1] != 'b') return 1;
      }
      else if ((present_game_state.database[0][i] == present_game_state.database[1][i]) && (present_game_state.database[1][i] == present_game_state.database[2][i])) {
	if (present_game_state.database[1][i] != 'b') return 1;
      }
    }
    return 0;
  }

  int tic_tac_agent_order_0::load_game_state(tic_tac_database x) {
     present_game_state = x;
     tmp = x;
  }

  int tic_tac_agent_order_0::mark_position(tic_tac_database x, int m, int n, int cost) {
    int i, j, win_b;
    char ch;
    for (i=0; i<2; i++) {
      for (j=0; j<2 ; j++) {
	if (x.winning_position()) {
	  cout << "Game Over!" << endl;
	  return 1;
	}
	else if (x.pos_occupied(i, j)) continue;
	else {
	  x.mark_position(i, j, ch);
	  cost++;
	  mark_position(x, i, j, cost);
	}
      }
    }	
  }

  int tic_tac_agent_order_0::compute_next_move() {
    int x, y;
    do {
    x = rand()%3;
    y = rand()%3;
    } while ((!tmp.mark_position(x, y, marker)) && !(tmp.winning_position()));
    present_game_state = tmp;
  }

