/*
** strace.c for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Mon Apr  4 22:19:02 2016 Arch Kureuil
** Last update Tue Apr  5 14:00:04 2016 Arch Kureuil
*/

#include <sys/ptrace.h>
#include "strace.h"

int
strace(pid_t pid)
{
  ptrace(PTRACE_ATTACH, pid, 0, 0);
  return (0);
}
