#include "signal_handlers.h"
#include <signal.h>
#include <stdio.h>

void catch_sigint(int signalNo)
{
  printf("Ctrl-C is inserted \n");
  signal(SIGINT,CTRLC);
}

void catch_sigtstp(int signalNo)
{
  printf("Ctrl-Z is inserted \n");
  signal(SIGTSTP,CTRLZ);
}
