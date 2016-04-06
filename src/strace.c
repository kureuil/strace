/*
** strace.c for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Mon Apr  4 22:19:02 2016 Arch Kureuil
** Last update Wed Apr  6 14:08:20 2016 
*/

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/reg.h>
#include <sys/user.h>
#include "strace.h"

int
syscall_waiting(pid_t child)
{
  int status;

  while (true)
    {
      ptrace(PTRACE_SYSCALL, child, 0, 0);
      waitpid(child, &status, 0);
      if (WSTOPSIG(status) & 0x80)
	return (0);
      if (WIFEXITED(status))
	return (-1);
    }
  return (0);
}

int
strace(pid_t pid)
{
  int status;
  int syscall;
  int retvalue;

  waitpid(pid, &status, 0);
  ptrace(PTRACE_ATTACH, pid, 0, 0);
  ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);
  while (true)
    {
      if (syscall_waiting(pid) != 0)
	break;
      syscall = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * ORIG_RAX);
      printf("syscall nbr : %d ", syscall);
      if (syscall_waiting(pid) != 0)
        break;
      retvalue = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * RAX);
      printf("ret value : %d\n", retvalue);
    }
  return (0);
}
