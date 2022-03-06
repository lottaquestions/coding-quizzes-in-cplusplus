#ifndef _TOWER_H
#define _TOWER_H
#include "stack.h"
class Tower: public Stack{
public:
  Tower (int height_d);
  ~Tower(){};
  bool PushDisk (int i);
  int PopDisk();
private:
  int height;
};
/*Below are tower associated functions*/
bool MoveTop(Tower *src, Tower *dest);
void MoveDisk(int n, Tower *src, Tower *dest, Tower *buf);
#endif