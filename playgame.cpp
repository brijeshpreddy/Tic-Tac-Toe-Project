#include <iostream>

using namespace std;
typedef tic_tac_database game;

int main()
{
  tic_tac_database game;
  tic_tac_agent player(game);
  game.reset_game();
  game.mark_position(1,1, 'o');
  game.display();
  return 0;
}

