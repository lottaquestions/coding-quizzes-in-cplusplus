#include "Board.h"

bool BadPosition(position &pos)
{
  int number_of_pennies,row;
  bool retval;
  
  if (pos[0] + pos[1] + pos[2] == 0)
  {
    retval = 0;
  }
  else 
  {
    FindGoodMove(pos, number_of_pennies, row);
    retval = (number_of_pennies == 0);
  }
}

void FindGoodMove(position &pos, int &number_of_pennies, int &row)
{
  for (int row_count = 0; row_count < row; row_count++)
  {
    for (int no_of_pennies = 1; no_of_pennies <= pos[row_count]; no_of_pennies++)
    {
      pos[row_count] = pos[row_count] - no_of_pennies;
      /* Check if the move above will cause our opponent to loose.
       * If it will, then return, having already made the move
       */
      if (BadPosition(pos))
      {
	number_of_pennies = no_of_pennies;
	row = row_count;
	return
      }
      pos[row_count] = pos[row_count] + no_of_pennies;
    }
  }
  //No good move was found. Set the number of pennies removed to zero to indicate that
  number_of_pennies = 0;
}