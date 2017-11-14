#include "utils.h"
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void mysh_parse_command(const char* command,
                        int* n_commands,
                        struct single_command (*commands)[])//user input , command gaesu , argc,argv
{ 
  char buf[4096];
  strcpy(buf, command);

  char *saveptr = NULL;
  char *tok = strtok_r(buf, "|", &saveptr); //front tok , rear saveptr

  int ti = 0;

  while (tok != NULL) {
    struct single_command* com = *commands + ti;
    parse_single_command(tok, &com->argc, &com->argv);

    ++ti;

    tok = strtok_r(NULL, "|", &saveptr);
  }

  *n_commands = ti;
}

void parse_single_command(const char* command,
                          int *argc, char*** argv)
{
  const int kMaxArgc = 512;
  *argv = (char**)malloc(kMaxArgc * sizeof(char*));
  for (int i = 0; i < kMaxArgc; ++i)
    (*argv)[i] = NULL;
  
  char buf[4096];
  strcpy(buf, command);

  char *saveptr = NULL;
  char *tok = strtok_r(buf, " \n\t", &saveptr); // one more parse
  	
  int ti = 0;
  while (tok != NULL) {
    (*argv)[ti] = (char*)malloc(strlen(tok));

    strcpy((*argv)[ti], tok); 

    ++ti;
    tok = strtok_r(NULL, " \n\t", &saveptr);
  }
  *argc = ti;
  
  if (*argc == 0) {
    *argc = 1;
    (*argv)[0] = (char*)malloc(1);
    (*argv)[0][0] = '\0';
  }
}

