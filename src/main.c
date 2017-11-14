#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include "commands.h"
#include "built_in.h"
#include "utils.h"
#include "signal_handlers.h"

void(*CTRLC)(int);
void(*CTRLZ)(int);

int main()
{
  char buf[8096];
  

  while (1) {
    CTRLC=signal(SIGINT,catch_sigint);
    CTRLZ=signal(SIGTSTP,catch_sigtstp);
    fgets(buf, 8096, stdin);
    
    struct single_command commands[512]; // argc,argv
    int n_commands = 0;

    mysh_parse_command(buf, &n_commands, &commands);
    
    int ret = evaluate_command(n_commands, &commands);

    memset(buf,0,sizeof(char)*8096);

    free_commands(n_commands, &commands);

    n_commands = 0;

    if (ret == 1) {
      break;
    }
  }

  return 0;
}
