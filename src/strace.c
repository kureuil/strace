/*
** strace.c for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Mon Apr  4 22:19:02 2016 Arch Kureuil
** Last update Sun Apr 10 17:59:01 2016 Arch Kureuil
*/

#define _GNU_SOURCE
#include <sys/ptrace.h>
#include <sys/wait.h>
#include "strace.h"

int
strace(pid_t pid,
       const struct s_strace_opts *opts)
{
  int				status;
  struct user_regs_struct	regs;
  long				curinst;

  if (waitpid(pid, &status, 0) == -1)
    return (-1);
  while (WIFSTOPPED(status))
    {
      if (strace_peek_registers(pid, &regs))
	return (-1);
      if (strace_peek_instruction(pid, &regs, &curinst))
	return (-1);
      if (STRACE_IS_SYSCALL(curinst))
	{
	  status = strace_syscall_handle(pid, &regs, opts);
	  if (status < 0)
	    return (-1);
	  else if (status > 0)
	    return (0);
	}
      if (ptrace(PTRACE_SINGLESTEP, pid, 0, 0) == -1)
	return (-1);
      if (waitpid(pid, &status, 0) == -1)
	return (-1);
    }
  return (0);
}
