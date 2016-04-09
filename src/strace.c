/*
** strace.c for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Mon Apr  4 22:19:02 2016 Arch Kureuil
** Last update Sat Apr  9 21:35:01 2016 Arch Kureuil
*/

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <errno.h>
#include <stdint.h>
#include "strace.h"

struct s_syscall	g_syscalls[] = {
  {
    .id = 0,
    .name = "read",
    .noreturn = false,
    .retval = T_SSIZE_T,
    .argc = 3,
    .args = {
      {
	.custom = false,
	.printer = {
	  .type = T_INTEGER
	},
      },
      {
	.custom = false,
	.printer = {
	  .type = T_POINTER
	},
      },
      {
	.custom = false,
	.printer = {
	  .type = T_SIZE_T
	},
      },
    },
  },
  {
    .id = 1,
    .name = "write",
    .noreturn = false,
    .retval = T_SSIZE_T,
    .argc = 3,
    .args = {
      {
	.custom = false,
	.printer = {
	  .type = T_INTEGER
	},
      },
      {
	.custom = false,
	.printer = {
	  .type = T_POINTER,
	},
      },
      {
	.custom = false,
	.printer = {
	  .type = T_SIZE_T
	},
      },
    },
  },
  {
    .id = 60,
    .name = "_exit",
    .noreturn = true,
    .retval = T_DEFAULT,
    .argc = 1,
    .args = {
      {
	.custom = false,
	.printer = {
	  .type = T_INTEGER
	},
      }
    },
  },
  {
    .id = (unsigned long long) -1,
    .name = NULL,
    .noreturn = false,
    .retval = 0,
    .argc = 0,
    .args = {{ 0 }},
  },
};

void	strace_print_hexa(unsigned long long int value)
{
  fprintf(stderr, "0x%llx", value);
}

void	strace_print_integer(unsigned long long int value)
{
  (void) value;
}

void	strace_print_pointer(unsigned long long int value)
{
  (void) value;
}

void	strace_print_string(unsigned long long int value)
{
  (void) value;
}

void	strace_print_size_t(unsigned long long int value)
{
  (void) value;
}

void	strace_print_ssize_t(unsigned long long int value)
{
  (void) value;
}

t_printer g_printers[] = {
  &strace_print_hexa,
  &strace_print_integer,
  &strace_print_pointer,
  &strace_print_string,
  &strace_print_size_t,
  &strace_print_ssize_t,
  NULL
};

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
strace_syscall_print_call(const struct s_syscall *scall,
			  const struct user_regs_struct *regs,
			  const struct s_strace_opts *opts)
{
  size_t			i;
  unsigned long long int	value;

  (void) opts;
  fprintf(stderr, "%s(", scall->name);
  i = 0;
  while (i < scall->argc)
    {
      if (i > 0)
	fprintf(stderr, ", ");
      value = strace_registers_get_by_idx(regs, i);
      if (opts->compliant)
	{
	  if (scall->args[i].custom)
	    scall->args[i].printer.callback(value);
	  else
	    g_printers[scall->args[i].printer.type](value);
	}
      else
	strace_print_hexa(value);
      i++;
    }
  return (0);
}

static int
strace_syscall_print_return(const struct s_syscall *scall,
			    const struct user_regs_struct *regs,
			    const struct s_strace_opts *opts)
{
  (void) opts;
  if (!scall->noreturn)
    fprintf(stderr, ") = 0x%llx\n", regs->rax);
  else
    fprintf(stderr, ") = ?\n");
  return (0);
}

static int
strace_syscall_handle(pid_t child,
		      const struct user_regs_struct *regs,
		      const struct s_strace_opts *opts)
{
  int				status;
  struct user_regs_struct	registers;
  struct s_syscall		scall;

  if (strace_syscall_get_by_id(regs->rax, &scall))
    return (0);
  if (strace_syscall_print_call(&scall, regs, opts))
    return (-1);
  if (ptrace(PTRACE_SINGLESTEP, child, 0, 0) == -1)
    return (-1);
  wait(&status);
  if (!scall.noreturn)
    {
      if (strace_peek_registers(child, &registers))
	return (-1);
    }
  if (strace_syscall_print_return(&scall, &registers, opts))
    return (-1);
  if (!WIFSTOPPED(status))
    {
      fprintf(stderr, "+++ exited with %d +++\n", WEXITSTATUS(status));
      return (1);
    }
  return (0);
}

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
