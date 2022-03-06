#include "tower.h"

Tower::Tower (int height_d) :height (height_d){
  //Do not allow towers of negative height. Min height=0
  if (height <= 0){
    height = 0;//Really make sure it is zero
    return;
  }
  
  for (int i = height; i > 0 ; --i){
    Stack::Push(i);
  }
}

bool Tower::PushDisk(int i){
  //Hardy Boys Mysteries: Scourge of the nested if
  //Make sure we cannot Push a disk that is larger than the top most disk onto the tower
  if(top != NULL){
    if (top->size < i)
      return false;
  }
  Stack::Push(i);
  height++;
  return true;
}

int Tower::PopDisk(){
  if (height > 0){
    height--;
    return Stack::Pop();
  }
  return 0; //Technically we should never have a disk with size 0
}

/*Below are tower associated functions*/
bool MoveTop(Tower *src, Tower *dest){
  int disk_val = src->PopDisk();
  
  if(disk_val == 0)
    return false; //We are expecting never to have a zero sized disk
  
  if(dest->PushDisk(disk_val))
    return true;
  
  src->PushDisk(disk_val);//We failed to push disk onto new tower, so we are returning to sender
  return false;
}

void MoveDisk(int n, Tower *src, Tower *dest, Tower *buf){
  if (n <= 0)
    return;
  
  MoveDisk(n-1, src, buf, dest);
  bool ret_val = MoveTop(src, dest);
  MoveDisk(n-1, buf, dest, src);
}