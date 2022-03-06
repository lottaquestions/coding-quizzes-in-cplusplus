#ifndef _DISK_H
#define _DISK_H
#include <cstddef>
class Disk{
public:
  Disk(int size_d): size (size_d){next = NULL;}
  ~Disk(){};
  int size;
  Disk *next;
};
#endif