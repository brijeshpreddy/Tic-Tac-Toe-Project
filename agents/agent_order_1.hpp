#ifndef AGENT_ORDER_1
#define AGENT_ORDER_1

#define MAX_PATHS 50
#define MAX_LOOK_AHEAD 4 
#define POS_COST 1
#define NEG_COST -2
#define DRAW_COST 0

#include "../data/data_base.hpp"
#include "agent_order_0.hpp"

using namespace std;

class tic_tac_agent_order_1 {

  private :
    tic_tac_database tmp, tmp_1;  //tmp, tmp_1 represent tmp(n), tmp(n-1)

  public :
    tic_tac_agent_order_1(tic_tac_database x);
    char marker;
    tic_tac_database present_game_state;
    int compute_next_move();
    int compute_cost(tic_tac_agent_order_0 player_0, tic_tac_agent_order_0 player_1);
    int load_game_state(tic_tac_database x);

};

#endif
