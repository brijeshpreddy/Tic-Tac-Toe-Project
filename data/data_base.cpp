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

  void mark_position(int x, int y, char ch)
  {
    int i, j;
    if (!((x >= 0) && (x <= 2) && (y >= 0) && (y <= 2) && ((ch != 'x') || (ch != 'o'))))
      cout << "Wrong Position Jackass !!!!" << endl;
    else
      database[x][y] = ch;
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
};


class tic_tac_agent
{
  char present_game_state[3][3];

  public :
    tic_tac_agent(tic_tac_database x)
    {
      int i, j;
      for (i=0; i<3; i++)
   	for (j=0; j<3; j++)
	  present_game_state[i][j] = x.database[i][j];      
    }

    int winning_position()
    {
      int i, j, win_b;
      for (i=0; i<2; i++)
      {
	if ((present_game_state[i][0] == present_game_state[i][1]) && (present_game_state[i][1] == present_game_state[i][2]))
	{
	  return 1;
	}
	else if ((present_game_state[0][i] == present_game_state[1][i]) && (present_game_state[2][i] == present_game_state[i][2]))
	{
	  return 1;
	}
	else if ((present_game_state[0][0] == present_game_state[1][1]) && (present_game_state[1][1] == present_game_state[2][2]))
	{
	  return 1;
	}
	else if ((present_game_state[0][2] == present_game_state[1][1]) && (present_game_state[1][1] == present_game_state[2][0]))
	{
	  return 1;
	}
      }
      return 0;
    }
};

int main()
{
  tic_tac_database game;
  tic_tac_agent player(game);
  game.reset_game();
  game.mark_position(1,1, 'o');
  game.display();
  return 0;
}
