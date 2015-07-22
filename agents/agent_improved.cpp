#include "agent_improved.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;
//typedef tic_tac_database;

  tic_tac_agent_improved::tic_tac_agent_improved(tic_tac_database x) {
    present_game_state = x;
  }

  int tic_tac_agent_improved::compute_next_move() {
    int x, y, i, j, k, iter, utility, opt_pos, redundant, break_count, check_safeguards;
    int cost[MAX_PATHS + 9];
    int m[MAX_PATHS + 9][MAX_LOOK_AHEAD], n[MAX_PATHS + 9][MAX_LOOK_AHEAD];
    bool skip_computing(false);
    char marker_c;
    marker_c = (marker == 'x')? 'o':'x';
    iter = 0;
    check_safeguards = 1;
    for (j=0; j<MAX_PATHS; j++) {
      tmp = present_game_state;
      tmp.mute_display();
      tic_tac_agent_order_0 player_0(tmp);
      tic_tac_agent_order_0 player_1(tmp);	// Create Two Sample Zero order players to compete (to see further)
      player_0.marker = marker;
      player_1.marker = (marker == 'x')? 'o':'x';
      break_count = 0;
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
      if (cost[j] == MAX_LOOK_AHEAD*POS_COST) check_safeguards = 0;
      iter = j;
    }
    if (check_safeguards) {
      for (i=0; i<2; i++) {
	for (k=0; k<2; k++) {
	  tmp = present_game_state;
	  tmp.mute_display();
	  tic_tac_agent_order_0 player_0(tmp);
	  tic_tac_agent_order_0 player_1(tmp);	// Create Two Sample Zero order players to compete (to see further)
	  player_0.marker = marker;
	  player_1.marker = (marker == 'x')? 'o':'x';
	  if ((tmp.mark_position(i, k, player_1.marker)) && (tmp.winner() == player_1.marker)) {
	    iter = iter + 1;
	    cost[iter] = (-1)*(MAX_LOOK_AHEAD + 1)*NEG_COST;
	    m[iter][0] = i;
	    n[iter][0] = k;
	    cout << "LOST " << m[iter][0] << " " << n[iter][0] << " Cost - " << cost[iter] << " iter = " << iter << endl;
	  }
	}
      }
    }
    utility = cost[0];
    opt_pos = 0;
    for (i=0;i<=iter;i++) {
      if (cost[i] > utility) {
	opt_pos = i;
	utility = cost[i];
      }
    }
    cout << "TRY " << m[opt_pos][0] << " " << n[opt_pos][0] << " Max_Cost - " << cost[opt_pos] << endl;
    present_game_state.mark_position(m[opt_pos][0], n[opt_pos][0], marker);
  }


  int tic_tac_agent_improved::compute_cost(tic_tac_agent_order_0 player_0, tic_tac_agent_order_0 player_1) {
    char winner;
    winner = tmp.winner();
    if (winner == player_0.marker) return POS_COST;
    else if (winner == player_1.marker) return NEG_COST;
    else return DRAW_COST;
  }

  int tic_tac_agent_improved::load_game_state(tic_tac_database x) {
    present_game_state = x;
    tmp = x;
    tmp.mute_display();
  }

