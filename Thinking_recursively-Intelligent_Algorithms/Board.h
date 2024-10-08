#ifndef _NIM_BOARD_H
#define _NIM_BOARD_H
class Board
{
public:
  int& operator[] (const int nIndex)
  {
    return position[nIndex];
  }
private:
  int position[3];
}
#endif
