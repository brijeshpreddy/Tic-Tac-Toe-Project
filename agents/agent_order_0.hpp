#ifndef AGENT_ORDER_0
#define AGENT_ORDER_0

#define MAX_PATHS 50
#define MAX_LOOK_AHEAD 4 
#define POS_COST 1
#define NEG_COST -2
#define DRAW_COST 0

#include "../data/data_base.hpp"

class tic_tac_agent_order_0 {

  private :
    tic_tac_database tmp;

  public :
    tic_tac_agent_order_0 (tic_tac_database x);  //Constructor
    char marker;  //Marker of this player
    tic_tac_database present_game_state;  //Stores game state
    int winning_position();  //Computes winning position
    int load_game_state(tic_tac_database x);  //Loads game state
    int mark_position(tic_tac_database x, int m, int n, int cost);  //Mark this position
    int compute_next_move();  //Computes next move

};

#endif
