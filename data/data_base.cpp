#define MAX_PATHS 50
#define MAX_LOOK_AHEAD 4 
#define POS_COST 1
#define NEG_COST -2
#define DRAW_COST 0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

class tic_tac_database {
  bool disp_m;

  public :
  tic_tac_database(bool disp) {
    disp_m = disp;
  }
  char database[3][3];

  tic_tac_database() {
    int i, j;
    for (i=0; i<3; i++)
      for (j=0; j<3; j++)  database[i][j] = 'b';
  }

  void reset_game() {
    int i, j;
    for (i=0; i<3; i++)
      for (j=0; j<3; j++)  database[i][j] = 'b';
  }

  void mute_display() {
    disp_m = 0;
  }

  void set_display() {
    disp_m = 1;
  }

  int pos_occupied(int x, int y) {
    if (database[x][y] == 'b') return 0;
    else return 1;
  }

  int mark_position(int x, int y, char ch) {
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

  void display() {
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
  
  int winning_position() {
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

  char winner() {
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

  int completion_status() {
    int i, j;
    for (i=0; i<3; i++) 
      for (j=0; j<3; j++) 
	if (database[i][j] == 'b') return 0;
    return 1;
  }

  int slots() {
    int i, j, count;
    count = 0;
    for (i=0; i<3; i++) 
      for (j=0; j<3; j++) 
	if (database[i][j] == 'b') count++;
    return count; 
  }

  void declare_result() {
    if (winning_position())
      if (disp_m) cout << "Winner -------- " << winner() << endl;
    else if (winner() == 'd')
      if (disp_m) cout << "Draw Dude... Bluh" << endl;
  }

};


class tic_tac_agent_order_0 {
  tic_tac_database tmp;

  public :
    tic_tac_agent_order_0(tic_tac_database x) {
      present_game_state = x;
    }
    char marker;
    tic_tac_database present_game_state;

    int winning_position() {
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

    int load_game_state(tic_tac_database x) {
       present_game_state = x;
       tmp = x;
    }

    int mark_position(tic_tac_database x, int m, int n, int cost) {
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

    int compute_next_move() {
      int x, y;
      do {
      x = rand()%3;
      y = rand()%3;
      } while ((!tmp.mark_position(x, y, marker)) && !(tmp.winning_position()));
      present_game_state = tmp;
    }

};

class tic_tac_agent_order_1 {
  tic_tac_database tmp, tmp_1;

  public :
    tic_tac_agent_order_1(tic_tac_database x) {
      present_game_state = x;
    }
    char marker;
    tic_tac_database present_game_state;

    int compute_next_move() {
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

    int compute_cost(tic_tac_agent_order_0 player_0, tic_tac_agent_order_0 player_1) {
      char winner;
      winner = tmp.winner();
      if (winner == player_0.marker) return POS_COST;
      else if (winner == player_1.marker) return NEG_COST;
      else return DRAW_COST;
    }

    int load_game_state(tic_tac_database x) {
       present_game_state = x;
       tmp = x;
       tmp.mute_display();
    }
};

class tic_tac_agent_improved_1 {
  tic_tac_database tmp, tmp_1;

  public :
    tic_tac_agent_improved_1(tic_tac_database x) {
      present_game_state = x;
    }
    char marker;
    tic_tac_database present_game_state;

    int compute_next_move() {
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


    int compute_cost(tic_tac_agent_order_0 player_0, tic_tac_agent_order_0 player_1) {
      char winner;
      winner = tmp.winner();
      if (winner == player_0.marker) return POS_COST;
      else if (winner == player_1.marker) return NEG_COST;
      else return DRAW_COST;
    }

    int load_game_state(tic_tac_database x) {
       present_game_state = x;
       tmp = x;
       tmp.mute_display();
    }
};

class tic_tac_agent_recursive {
  tic_tac_database tmp;

  public :
    tic_tac_agent_recursive(tic_tac_database x) {
      present_game_state = x;
    }
    char marker;
    tic_tac_database present_game_state;

    int compute_next_move() {
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

    int compute_cost(tic_tac_agent_order_1 player_0, tic_tac_agent_order_1 player_1) {
      char winner;
      winner = tmp.winner();
      if (winner == player_0.marker) return POS_COST;
      else if (winner == player_1.marker) return NEG_COST;
      else return DRAW_COST;
    }

    int load_game_state(tic_tac_database x) {
       present_game_state = x;
       tmp = x;
       tmp.mute_display();
    }
};

int main() {
  srand (time(NULL));
  bool display(true);
  int i, m, n;
  int p1, p2, d, iter;
  char ch;
  p1 = 0;
  p2 = 0;
  d = 0;
  tic_tac_database game(display);
  tic_tac_agent_order_0 player_o(game);
  tic_tac_agent_improved_1 player_x(game);
  cout << "Wanna Play --------------- (Y/n) ?" << endl;
  cin >> ch;
  if ((ch == 'Y') || (ch == 'y')) {
    for (iter=0; ((iter<1000) && ((ch == 'Y') || (ch == 'y'))); iter++) {
      game.reset_game();
      player_o.marker = 'o';
      player_x.marker = 'x';
      for (i=1; i<5; i++) {
	player_x.load_game_state(game);
	player_x.compute_next_move();
	game = player_x.present_game_state;
	if (game.winning_position()) break;
	cout << "Enter Row - ";
	cin >> m;
	cout << endl;
	cout << "Enter Col - ";
	cin >> n;
	cout << endl;
	game.mark_position(m, n, 'o');
	if (game.winning_position()) break;
      }
      if (!game.winning_position()) {
      player_x.load_game_state(game);
      player_x.compute_next_move();
      game = player_x.present_game_state;
      }

      if (game.winner() == 'x') p1++;
      else if (game.winner() == 'o') p2++;
      else d++;
      game.declare_result();
      cout << "Wanna Continue --------------- (Y/n) ?" << endl;
      cin >> ch;
    }
  }
  else {
    for (iter=0; iter<1000; iter++) {
      game.reset_game();
      player_o.marker = 'o';
      player_x.marker = 'x';
      for (i=1; i<5; i++) {
	player_x.load_game_state(game);
	player_x.compute_next_move();
	game = player_x.present_game_state;
	if (game.winning_position()) break;
	player_o.load_game_state(game);
	player_o.compute_next_move();
	game = player_o.present_game_state;
	if (game.winning_position()) break;
      }
      if (!game.winning_position()) {
      player_x.load_game_state(game);
      player_x.compute_next_move();
      game = player_x.present_game_state;
      }

      if (game.winner() == 'x') p1++;
      else if (game.winner() == 'o') p2++;
      else d++;
      game.declare_result();
    }
  }
  cout << "P1 -- " << p1 << endl;
  cout << "P2 -- " << p2 << endl;
  cout << "D -- " << d << endl;
  return 0;
}
