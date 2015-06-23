#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

class tic_tac_database {
  public :
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

  int pos_occupied(int x, int y) {
    if (database[x][y] == 'b') return 0;
    else return 1;
  }

  int mark_position(int x, int y, char ch) {
    int i, j;
    if (pos_occupied(x, y)) {
      cout << "Position Taken Jackass !!!!" << endl;
      return 0;
    }
    else if (!((x >= 0) && (x <= 2) && (y >= 0) && (y <= 2) && ((ch != 'x') || (ch != 'o')))) {
      cout << "Wrong Position Jackass !!!!" << endl;
      return 0;
    }
    else {
      if (!winning_position()) {
	database[x][y] = ch;
	display();
	return 1;
      }
      else {
	cout << "Your Game is Done Man - Reset" << endl;
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
    int i, j, win_b;
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
    int i, j, win_b;
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

};


class tic_tac_agent {
  tic_tac_database tmp;

  public :
    tic_tac_agent(tic_tac_database x) {
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

int main() {
  srand (time(NULL));
  int x, y;
  int i;
  x = rand()%3;
  y = rand()%3;
  static tic_tac_database game;
  tic_tac_agent player_o(game);
  tic_tac_agent player_x(game);

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

  player_x.load_game_state(game);
  player_o.load_game_state(game);

  if (game.winning_position())
    cout << "Winner -------- " << game.winner() << endl;
  else if (game.winner() == 'd')
    cout << "Draw Dude... Bluh" << endl;

  return 0;
}
