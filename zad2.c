#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <ucontext.h>
#include <stdlib.h>

void ign_sig(int signum){
  printf("Zignorowano sygnał %d.\n", signum);
}

void catch_a(int signum){
  printf("Odebrano sygnał %d.\n Kończę pracę.\n", signum);
  exit(1);
}

void catch_b(int signum){
  printf("Odebrano sygnał %d.\n Kontynuuję pracę.\n", signum);
}

void catch_c(int signum){
  int i;

  struct timespec t, tim;

  t.tv_sec = 0;
  t.tv_nsec = 5000000;

  tim.tv_sec = 0;
  tim.tv_nsec = 500000;
  
  printf("Odebrano sygnał %d.\n Blokowanie sygnałów przez 1000 iteracji.\n", signum);

  sigset_t mask;
  sigfillset(&mask);
  sigprocmask(SIG_SETMASK, &mask, NULL);

  for(i = 0; i < 1000; i++){
    nanosleep(&t, &tim);
  }
  
}

void catch_d(int signum){
  int i;
  
  printf("Odebrano sygnał %d\n Ignorowanie sygnałów.\n", signum);

  for(i = 1; i <= 31; i++){
    signal(i, ign_sig);
  }
}

int main(){
  
  struct timespec t, tim;

  t.tv_sec = 0;
  t.tv_nsec = 5000000;

  tim.tv_sec = 0;
  tim.tv_nsec = 500000;
  
  int i = 0;

  signal(SIGALRM, catch_a);
  signal(SIGTERM, catch_b);
  signal(SIGUSR1, catch_c);
  signal(SIGUSR2, catch_d);
  
  while(1){
    ++i;
    nanosleep(&t, &tim);
  }
  return 0;
}
