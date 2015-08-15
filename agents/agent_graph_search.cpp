#include "agent_graph_search.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

/********************************************************************
  		    tic_tac_graph_search functions
********************************************************************/
  tic_tac_graph_search::tic_tac_graph_search(tic_tac_database x) {
    present_game_state = x;
    tmp = x;
  }

  int tic_tac_graph_search::build_graph(tic_tac_database x, char marker) {
    tic_tac_database tmp_base(false);
    tmp_base = x;
    graph_node present_node(tmp_base);
    char op_player_marker = (marker == 'x')?'o':'x';
    int i, j;
    if (!tmp_base.completion_status()) {
      for (i=0; i<2; i++) {
	for (j=0; j<2; j++) {
	  if (!tmp_base.pos_occupied(i, j)) {
	    tmp.mark_position(i, j, op_player_marker);
	    build_graph(tmp, op_player_marker);
	  }
	}
      }
    }
    else
      return 1;
  }




/********************************************************************
  			graph_node functions
********************************************************************/
  graph_node::graph_node(tic_tac_database x) {
    tmp = x;
  }

  void graph_node::connect_edge(graph_node next) {
    graph_edge tmp;
    graph_edge *traverse;
    tmp = add_edge();
    tmp.original_node = this;
    tmp.destination_node = &next;
    traverse = edge_table_forward;
    while (traverse->next_edge != NULL)
      traverse = traverse->next_edge;
    traverse->next_edge = &tmp;
    tmp.prev_edge = traverse;
    tmp.next_edge = NULL;
  }

  graph_edge graph_node::add_edge() {
    graph_edge tmp;
    return tmp;
  }

/********************************************************************
  			graph_edge functions
********************************************************************/
  graph_edge::graph_edge() {
    cost = TRAVERSE_COST;
    next_edge = NULL;
    prev_edge = NULL;
    original_node = NULL;
    destination_node = NULL;
  }

  void graph_edge::set_cost(tic_tac_database x, char marker) {
    char opp_marker;
    opp_marker = (marker == 'x')? 'o':'x';
    if (x.winning_position()) {
      if (marker == x.winner()) cost = WINNING_COST;
      else if (opp_marker == x.winner()) cost = LOSING_COST;
      else cost = DRAW_COST;
    }
    else cost = TRAVERSE_COST;
  }
