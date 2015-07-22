#include "agent_recursive.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

  tic_tac_agent_recursive::tic_tac_agent_recursive(tic_tac_database x) {
    present_game_state = x;
  }

  int tic_tac_agent_recursive::compute_next_move() {
    int x, y, i, j, utility, opt_pos, redundant;
    int cost[MAX_PATHS];
    int m[MAX_PATHS][MAX_LOOK_AHEAD], n[MAX_PATHS][MAX_LOOK_AHEAD];
    for (j=0; j<MAX_PATHS; j++) {
      tmp = present_game_state;
      tmp.mute_display();
      tic_tac_agent_order_1 player_0(tmp);
      tic_tac_agent_order_1 player_1(tmp);	// Create Two Sample Zero order players to compete (to see further)
      player_0.marker = marker;
      player_1.marker = (marker == 'x')? 'o':'x';
      for (i=0; i<MAX_LOOK_AHEAD; i++) {
	player_0.load_game_state(tmp);
	do {
	x = rand()%3;
	y = rand()%3;
	m[j][i] = x;
	n[j][i] = y;
	if ((i == 0) && (j != 0))
	  redundant = ((m[j-1][0] == m[j][i]) && (n[j-1][0] == n[j][0]))? 1 : 0;
	} while (((!tmp.mark_position(x, y, marker)) && !(tmp.winning_position()) && redundant) || tmp.completion_status());

	if(!tmp.completion_status()) {
	  player_1.load_game_state(tmp);
	  player_1.compute_next_move();
	}

	//for (j=0; j<=i; j++) cout << "(" << m[j] << "," << n[j] << ")";
	//cout << endl;
	if (compute_cost(player_0, player_1) == NEG_COST) {
	  i = 0;
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
    for (i=0;i<MAX_PATHS;i++)
      if (cost[i] > utility) opt_pos = i;
    present_game_state.mark_position(m[opt_pos][0], n[opt_pos][0], marker);
  }

  int tic_tac_agent_recursive::compute_cost(tic_tac_agent_order_1 player_0, tic_tac_agent_order_1 player_1) {
    char winner;
    winner = tmp.winner();
    if (winner == player_0.marker) return POS_COST;
    else if (winner == player_1.marker) return NEG_COST;
    else return DRAW_COST;
  }

  int tic_tac_agent_recursive::load_game_state(tic_tac_database x) {
    present_game_state = x;
    tmp = x;
    tmp.mute_display();
  }
