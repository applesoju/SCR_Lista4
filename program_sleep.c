#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(){
  struct timespec t, tim;

  t.tv_sec = 0;
  t.tv_nsec = 500000;

  tim.tv_sec = 0;
  tim.tv_nsec = 500000;
  
  int i = 0;
  while(1){
    ++i;
    nanosleep(&t, &tim);
  }
  return 0;
}
