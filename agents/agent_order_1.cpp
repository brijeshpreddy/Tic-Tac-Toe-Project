#include "agent_order_1.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

  tic_tac_agent_order_1::tic_tac_agent_order_1(tic_tac_database x) {
    present_game_state = x;
  }

  int tic_tac_agent_order_1::compute_next_move() {
    int x, y, i, j, k, utility, opt_pos, redundant, break_count;
    int cost[MAX_PATHS];
    int m[MAX_PATHS][MAX_LOOK_AHEAD], n[MAX_PATHS][MAX_LOOK_AHEAD];
    bool skip_computing(false);
    for (j=0; j<MAX_PATHS; j++) {
      tmp = present_game_state;
      tmp.mute_display();
      tic_tac_agent_order_0 player_0(tmp);
      tic_tac_agent_order_0 player_1(tmp);	// Create Two Sample Zero order players to compete (to see further)
      player_0.marker = marker;
      player_1.marker = (marker == 'x')? 'o':'x';
      break_count = 0;
      skip_computing = false;
  /*
	for (j=0; j<2; j++) {
	  for (k=0; k<2; k++) {
	cout << "true_3" << endl;
	    tmp_1 = tmp;
	    if ((tmp_1.mark_position(j, k, player_1.marker)) && (tmp_1.winning_position())) { 
	cout << "true" << endl;
	      skip_computing = true;
	      tmp.mark
	    }
	  }
	}
  */
      for (i=0; ((i<MAX_LOOK_AHEAD) && (break_count <MAX_LOOK_AHEAD)); i++) {
	player_0.load_game_state(tmp);
	tmp_1 = tmp;
	do {
	  redundant = 0;
	  x = rand()%3;
	  y = rand()%3;
	  m[j][i] = x;
	  n[j][i] = y;	
	  if ((i == 0) && (j != 0) && (tmp_1.slots() != 1)) {
	    for (k=0; (k<j) && (k < tmp_1.slots()); k++) {
	      if ((m[j][0] == m[k][0]) && (n[j][0] == n[k][0])) {
		redundant = 1;
		break;
	      }
	    }
	  }
	} while ((!tmp_1.mark_position(x, y, marker)) && (!tmp_1.winning_position()) && (!redundant));
	tmp = tmp_1;

	if(!tmp.completion_status()) {
	  player_1.load_game_state(tmp);
	  player_1.compute_next_move();
	  tmp = player_1.present_game_state;
	  tmp.mute_display();
	}

	//for (j=0; j<=i; j++) cout << "(" << m[j] << "," << n[j] << ")";
	//cout << endl;
	if (compute_cost(player_0, player_1) == NEG_COST) {
	  break_count++;
	  i = -1;
	//cout << "I = " << i << endl;
	  tmp = present_game_state;
	  tmp.mute_display();
	}
	else if (compute_cost(player_0, player_1) == POS_COST) break;
	else {
	  if (tmp.completion_status()) break;
	  else continue;
	}
      }
      cost[j] = (MAX_LOOK_AHEAD - i)*compute_cost(player_0, player_1);
    }
    utility = cost[0];
    opt_pos = 0;
    for (i=0;i<j;i++) {
      if (cost[i] > utility) {
	opt_pos = i;
	utility = cost[i];
      }
    }
    present_game_state.mark_position(m[opt_pos][0], n[opt_pos][0], marker);
  }

  int tic_tac_agent_order_1::compute_cost(tic_tac_agent_order_0 player_0, tic_tac_agent_order_0 player_1) {
    char winner;
    winner = tmp.winner();
    if (winner == player_0.marker) return POS_COST;
    else if (winner == player_1.marker) return NEG_COST;
    else return DRAW_COST;
  }

  int tic_tac_agent_order_1::load_game_state(tic_tac_database x) {
     present_game_state = x;
     tmp = x;
     tmp.mute_display();
  }

