/*
** strace.c for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Mon Apr  4 22:19:02 2016 Arch Kureuil
** Last update Sat Apr  9 13:29:11 2016 Arch Kureuil
*/

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <errno.h>
#include "strace.h"

static int
strace_peek_registers(pid_t child, struct user_regs_struct *regsp)
{
  struct user_regs_struct	registers;

  errno = 0;
  if (ptrace(PTRACE_GETREGS, child, 0, &registers) && errno)
    return (-1);
  *regsp = registers;
  return (0);
}

static int
strace_peek_instruction(pid_t child,
			const struct user_regs_struct *regs,
			long *instrp)
{
  long	instruction;

  errno = 0;
  instruction = ptrace(PTRACE_PEEKTEXT, child, regs->rip, 0);
  if (instruction == -1 && errno)
    return (-1);
  *instrp = instruction;
  return (0);
}

static int
strace_handle_syscall(pid_t child,
		      const struct user_regs_struct *regs)
{
  (void) child;
  printf("Syscall %llu au rapport !\n", regs->rax);
  return (0);
}

int
strace(pid_t pid)
{
  int				status;
  struct user_regs_struct	regs;
  long				curinst;

  wait(&status);
  ptrace(PTRACE_ATTACH, pid, 0, 0);
  while (WIFSTOPPED(status))
    {
      if (strace_peek_registers(pid, &regs))
	return (-1);
      if (strace_peek_instruction(pid, &regs, &curinst))
	return (-1);
      if (STRACE_IS_SYSCALL(curinst))
	strace_handle_syscall(pid, &regs);
      if (ptrace(PTRACE_SINGLESTEP, pid, 0, 0) == -1)
	return (-1);
      wait(&status);
    }
  return (0);
}
