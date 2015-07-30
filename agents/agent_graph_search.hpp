#ifndef AGENT_GRAPH_SEARCH
#define AGENT_GRAPH_SEARCH

#define MAX_PATHS 50
#define MAX_LOOK_AHEAD 4 
#define POS_COST 1
#define NEG_COST -2
#define DRAW_COST 0

#include "../data/data_base.hpp"
#include "agent_order_0.hpp"

using namespace std;

class tic_tac_graph_search {

  private :
    tic_tac_database tmp, tmp_1;  //tmp, tmp_1 represent tmp(n), tmp(n-1)

  public :
    tic_tac_graph_search(tic_tac_database x);
    char marker;
    tic_tac_database present_game_state;
    int compute_next_move();
    int compute_cost(tic_tac_agent_order_0 player_0, tic_tac_agent_order_0 player_1);
    int load_game_state(tic_tac_database x);
    int build_graph();
    int search_graph();
};

class graph_node {

  private :
    tic_tac_data_base tmp;
  
  public :
    graph_node(tic_tac_database x);
    int cost;
    graph_edge *edge_table_backward;
    graph_edge *edge_table_forward;
    void connect_edge();
    graph_edge add_edge();	//Adds edge
};

class graph_edge {

  private :
    int cost;

  public :
    graph_edge ();
    graph_edge *next_edge;
    graph_edge *prev_edge;
    graph_node *original_node;
    graph_node *destination_node;

};

#endif
