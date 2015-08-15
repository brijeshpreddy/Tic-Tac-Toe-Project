#ifndef AGENT_GRAPH_SEARCH
#define AGENT_GRAPH_SEARCH

#define MAX_PATHS 50
#define MAX_LOOK_AHEAD 4 
#define POS_COST 1
#define NEG_COST -2
#define DRAW_COST 0
#define WINNING_COST 100
#define LOSING_COST -200
#define TRAVERSE_COST 2

#include "../data/data_base.hpp"
#include "agent_order_0.hpp"

using namespace std;

class tic_tac_graph_search {

  private :
    tic_tac_database tmp, tmp_1;  //tmp, tmp_1 represent tmp(n), tmp(n-1)

  public :
    //Constructor
    tic_tac_graph_search(tic_tac_database x);
    //Variables
    char marker;
    tic_tac_database present_game_state;
    //Functions
    int compute_next_move();
    int compute_cost(tic_tac_agent_order_0 player_0, tic_tac_agent_order_0 player_1);
    int load_game_state(tic_tac_database x);
    int build_graph(tic_tac_database x, char marker);
    int search_graph();
};

class graph_edge;

class graph_node {

  private :
    tic_tac_database tmp;
  
  public :
    //Constructor
    graph_node(tic_tac_database x);
    //Variables
    int cost;
    graph_edge *edge_table_backward;
    graph_edge *edge_table_forward;
    //Functions
    void connect_edge(graph_node next);
    graph_edge add_edge();	//Adds edge
};


class graph_edge {

  private :
    int cost;

  public :
    //Constructor
    graph_edge ();
    //Variables
    graph_edge *next_edge;
    graph_edge *prev_edge;
    graph_node *original_node;
    graph_node *destination_node;
    //Functions
    void set_cost(tic_tac_database x, char marker);
};

#endif
