#include <iostream>
using namespace std;


class tic_tac_database
{
  public :
  char database[3][3];

  tic_tac_database()
  {
    int i, j;
    for (i=0; i<3; i++)
      for (j=0; j<3; j++)  database[i][j] = 'b';
  }

  void reset_game()
  {
    int i, j;
    for (i=0; i<3; i++)
      for (j=0; j<3; j++)  database[i][j] = 'b';
  }

  int pos_occupied(int x, int y)
  {
    if (database[x][y] == 'b') return 0;
    else return 1;
  }

  void mark_position(int x, int y, char ch)
  {
    int i, j;
    if (!((x >= 0) && (x <= 2) && (y >= 0) && (y <= 2) && ((ch != 'x') || (ch != 'o'))))
      cout << "Wrong Position Jackass !!!!" << endl;
    else
    {
      if (!winning_position()) database[x][y] = ch;
      else cout << "Your Game is Done Man - Reset" << endl;
    }
  }

  void display()
  {
    int i, j;
    for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
      {
        if (database[i][j] == 'b')
      	  cout << " ";
	else if (database[i][j] == 'x')
	  cout << "x";
        else if (database[i][j] == 'o')
	  cout << "o";
	else
	  cout << "\n ERROR in game \n";
      }
      cout << endl;
    }
  } 
  
  int winning_position()
  {
    int i, j, win_b;
    if (((database[0][0] == database[1][1]) && (database[1][1] == database[2][2])) || ((database[0][2] == database[1][1]) && (database[1][1] == database[2][0])))
    {
      if (database[1][1] != 'b') return 1;
    }
    for (i=0; i<2; i++)
    {
      if ((database[i][0] == database[i][1]) && (database[i][1] == database[i][2]))
      {
        if (database[i][1] != 'b') return 1;
      }
      else if ((database[0][i] == database[1][i]) && (database[1][i] == database[2][i]))
      {
        if (database[1][i] != 'b') return 1;
      }
    }
      return 0;
  }

};


class tic_tac_agent
{
  tic_tac_database present_game_state;
  tic_tac_database tmp;

  public :
    tic_tac_agent(tic_tac_database x)
    {
      present_game_state = x;
    }

    int winning_position()
    {
      int i, j, win_b;
      if (((present_game_state.database[0][0] == present_game_state.database[1][1]) && (present_game_state.database[1][1] == present_game_state.database[2][2])) || ((present_game_state.database[0][2] == present_game_state.database[1][1]) && (present_game_state.database[1][1] == present_game_state.database[2][0])))
      {
        if (present_game_state.database[1][1] != 'b') return 1;
      }
      for (i=0; i<2; i++)
      {
	if ((present_game_state.database[i][0] == present_game_state.database[i][1]) && (present_game_state.database[i][1] == present_game_state.database[i][2]))
	{
	  if (present_game_state.database[i][1] != 'b') return 1;
	}
	else if ((present_game_state.database[0][i] == present_game_state.database[1][i]) && (present_game_state.database[1][i] == present_game_state.database[2][i]))
	{
	  if (present_game_state.database[1][i] != 'b') return 1;
	}
      }
      return 0;
    }

    int load_game_state(tic_tac_database x)
    {
       present_game_state = x;
       tmp = x;
    }

    int mark_position(tic_tac_database x, int m, int n, int cost)
    {
      int i, j, win_b;
      char ch;
      for (i=0; i<2; i++) {
	for (j=0; j<2 ; j++) {
     	  if (x.winning_position())
	  {
	    cout << "Game Over!" << endl;
            return 1;
    	  }
	  else if (x.pos_occupied(i, j)) continue;
	  else
	  {
	    x.mark_position(i, j, ch);
	    cost++;
 	    mark_position(x, i, j, cost);
	  }
        }
      }
	
    }

};

int main()
{
  tic_tac_database game;
  tic_tac_agent player(game);
  game.reset_game();
  game.mark_position(1, 1, 'o');
  game.display();
  player.load_game_state(game);
  game.mark_position(1, 2, 'x');
  game.display();
  player.load_game_state(game);
  game.mark_position(2, 2, 'o');
  game.display();
  return 0;
}
