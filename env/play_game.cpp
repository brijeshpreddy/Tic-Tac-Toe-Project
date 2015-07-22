/*
#define MAX_PATHS 50
#define MAX_LOOK_AHEAD 4
#define POS_COST 1
#define NEG_COST -2
#define DRAW_COST 0
*/
#include "../data/data_base.hpp"
#include "../agents/agent_order_0.hpp"
#include "../agents/agent_order_1.hpp"
#include "../agents/agent_improved.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;
//typedef tic_tac_database game;

int main()
{
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
  tic_tac_agent_improved player_x(game);
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

