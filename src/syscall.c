/*
** syscall.c for strace in /home/kureuil/Work/strace/src
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Sun Apr 10 17:37:58 2016 Arch Kureuil
** Last update Sun Apr 10 18:01:40 2016 Arch Kureuil
*/

#include <stddef.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "strace.h"

t_printer g_printers[] = {
  &strace_print_hexa,
  &strace_print_integer,
  &strace_print_pointer,
  &strace_print_string,
  &strace_print_long,
  &strace_print_ulong,
  &strace_print_size_t,
  &strace_print_ssize_t,
  NULL
};

static unsigned long long int
strace_registers_get_by_idx(const struct user_regs_struct *regs,
			    size_t idx)
{
  static const uintptr_t	offsets[STRACE_SYSCALL_ARGS_MAX] = {
    offsetof(struct user_regs_struct, rdi),
    offsetof(struct user_regs_struct, rsi),
    offsetof(struct user_regs_struct, rdx),
    offsetof(struct user_regs_struct, r10),
    offsetof(struct user_regs_struct, r8),
    offsetof(struct user_regs_struct, r9),
  };

  assert(idx < STRACE_SYSCALL_ARGS_MAX);
  return (*((unsigned long long int *)((uintptr_t)regs + offsets[idx])));
}

static int
strace_syscall_get_by_id(unsigned long long id, struct s_syscall *scallp)
{
  size_t	i;

  i = 0;
  while (g_syscalls[i].name != NULL)
    {
      if (g_syscalls[i].id == id)
	{
	  *scallp = g_syscalls[i];
	  return (0);
	}
      i++;
    }
  return (-1);
}

static int
strace_syscall_print_call(const struct s_syscall *scall,
			  const struct user_regs_struct *regs,
			  const struct s_strace_opts *opts,
			  pid_t child)
{
  size_t			i;
  unsigned long long int	value;
  int				printed;

  printed = fprintf(stderr, "%s(", scall->name);
  i = 0;
  while (i < scall->argc)
    {
      if (i > 0)
	printed += fprintf(stderr, ", ");
      value = strace_registers_get_by_idx(regs, i);
      if (opts->compliant)
	{
	  if (scall->args[i].custom)
	    printed += scall->args[i].printer.callback(value, child, regs);
	  else
	    printed += g_printers[scall->args[i].printer.type](value,
							       child, regs);
	}
      else
	printed += strace_print_hexa(value, child, regs);
      i++;
    }
  return (printed);
}

static int
strace_syscall_print_return(const struct s_syscall *scall,
			    const struct user_regs_struct *regs,
			    const struct s_strace_opts *opts,
			    int printed)
{
  int	shift;

  shift = 0;
  if (!scall->noreturn)
    {
      if (opts->compliant)
	shift = MAX(40 - printed, 0);
      fprintf(stderr, ")%*s= ", shift, " ");
      g_printers[scall->retval](regs->rax, opts->pid, regs);
      fprintf(stderr, "\n");
    }
  else
    {
      if (opts->compliant)
	shift = MAX(40 - printed, 0);
      fprintf(stderr, ")%*s= ?\n", shift, " ");
    }
  return (0);
}

int
strace_syscall_handle(pid_t child,
		      const struct user_regs_struct *regs,
		      const struct s_strace_opts *opts)
{
  int				status;
  struct user_regs_struct	registers;
  struct s_syscall		scall;
  int				printed;

  if (strace_syscall_get_by_id(regs->rax, &scall))
    return (0);
  printed = strace_syscall_print_call(&scall, regs, opts, child);
  if (ptrace(PTRACE_SINGLESTEP, child, 0, 0) == -1)
    return (-1);
  wait(&status);
  if (!scall.noreturn)
    {
      if (strace_peek_registers(child, &registers))
	return (-1);
    }
  strace_syscall_print_return(&scall, &registers, opts, printed);
  if (!WIFSTOPPED(status))
    {
      fprintf(stderr, "+++ exited with %d +++\n", WEXITSTATUS(status));
      return (1);
    }
  return (0);
}

