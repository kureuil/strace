/*
** main.c for zappy in /home/kureuil/Work/zappy/server/src
**
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
**
** Started on  Fri Mar 18 08:53:07 2016 Arch Kureuil
** Last update Mon Apr  4 22:45:51 2016 Arch Kureuil
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "optparser.h"
#include "strace.h"

static void
usage(FILE *stream, const char *prgm)
{
  fprintf(stream, "\nUSAGE: %s [-s] [-p PID] COMMAND [ARGS]\n\n", prgm);
  fprintf(stream, "OPTIONS:\n");
  fprintf(stream, "\t-s       Make output more compliant with the system's"
	  " strace\n");
  fprintf(stream, "\t-p PID   Trace program with id = PID instead of launching"
	  " COMMAND\n");
  fprintf(stream, "\tCOMMAND  Program to execute & trace\n");
  fprintf(stream, "\tARGS     Arguments given to the executed program");
}

int
main(int argc, char *argv[])
{
  struct s_strace_opts	opts;

  memset(&opts, 0, sizeof(opts));
  if (optparse(argc, argv, &opts))
    {
      usage(stderr, argv[0]);
      return (EXIT_FAILURE);
    }
  if (opts.pid == 0 && opts.command == NULL)
    {
      usage(stderr, argv[0]);
      return (EXIT_FAILURE);
    }
  if (strace(opts.pid))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
