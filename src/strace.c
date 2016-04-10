/*
** strace.c for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Mon Apr  4 22:19:02 2016 Arch Kureuil
** Last update Sun Apr 10 16:23:20 2016 Arch Kureuil
*/

#define _GNU_SOURCE
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <fcntl.h>
#include "strace.h"

int	strace_print_hexa(unsigned long long int value,
			  pid_t child,
			  const struct user_regs_struct *regs)
{
  (void) child;
  (void) regs;
  return (fprintf(stderr, "0x%llx", value));
}

int	strace_print_integer(unsigned long long int value,
			     pid_t child,
			     const struct user_regs_struct *regs)
{
  (void) child;
  (void) regs;
  return (fprintf(stderr, "%d", (int) value));
}

int	strace_print_pointer(unsigned long long int value,
			     pid_t child,
			     const struct user_regs_struct *regs)
{
  (void) child;
  (void) regs;
  if (value == 0)
    return (fprintf(stderr, "NULL"));
  else
    return (fprintf(stderr, "%#llx", value));
}

int	strace_print_long(unsigned long long int value,
			  pid_t child,
			  const struct user_regs_struct *regs)
{
  (void) child;
  (void) regs;
  return (fprintf(stderr, "%ld", (long) value));
}

int	strace_print_ulong(unsigned long long int value,
			   pid_t child,
			   const struct user_regs_struct *regs)
{
  (void) child;
  (void) regs;
  return (fprintf(stderr, "%lu", (unsigned long) value));
}

void	strace_string_read(char **strp,
			   unsigned long long int addr,
			   pid_t child)
{
  size_t	allocated;
  size_t	readb;
  unsigned long	tmp;

  allocated = 16;
  readb = 0;
  if ((*strp = realloc(*strp, allocated)) == NULL)
    return ;
  while (true)
    {
      if ((readb + sizeof(tmp)) > allocated)
	{
	  allocated <<= 1;
	  if ((*strp = realloc(*strp, allocated)) == NULL)
	    return ;
	}
      errno = 0;
      tmp = ptrace(PTRACE_PEEKDATA, child, addr + readb);
      if (errno)
	{
	  (*strp)[readb] = '\0';
	  return ;
	}
      memcpy(*strp + readb, &tmp, sizeof(tmp));
      if (memchr(&tmp, 0, sizeof(tmp)) != NULL)
	return ;
      readb += sizeof(tmp);
    }
}

int	strace_print_string(unsigned long long int value,
			    pid_t child,
			    const struct user_regs_struct *regs)
{
  char	*str;
  int	ret;

  (void) regs;
  if (value == 0)
    return (fprintf(stderr, "NULL"));
  else
    {
      str = NULL;
      strace_string_read(&str, value, child);
      ret = fprintf(stderr, "\"%s\"", str);
      free(str);
      return (ret);
    }
}

int	strace_print_size_t(unsigned long long int value,
			    pid_t child,
			    const struct user_regs_struct *regs)
{
  (void) child;
  (void) regs;
  return (fprintf(stderr, "%zu", (size_t) value));
}

int	strace_print_ssize_t(unsigned long long int value,
			     pid_t child,
			     const struct user_regs_struct *regs)
{
  (void) child;
  (void) regs;
  return (fprintf(stderr, "%zu", (ssize_t) value));
}

static const struct s_flag g_open_flags[] = {
  { .value = O_APPEND, .name = "O_APPEND" },
  { .value = O_ASYNC, .name = "O_ASYNC" },
  { .value = O_CLOEXEC, .name = "O_CLOEXEC" },
  { .value = O_CREAT, .name = "O_CREAT" },
  { .value = O_DIRECT, .name = "O_DIRECT" },
  { .value = O_DIRECTORY, .name = "O_DIRECTORY" },
  { .value = O_EXCL, .name = "O_EXCL" },
  { .value = O_NOATIME, .name = "O_NOATIME" },
  { .value = O_NOCTTY, .name = "O_NOCTTY" },
  { .value = O_NOFOLLOW, .name = "O_NOFOLLOW" },
  { .value = O_NONBLOCK, .name = "O_NONBLOCK" },
  { .value = O_PATH, .name = "O_PATH" },
  { .value = O_SYNC, .name = "O_SYNC" },
  { .value = O_TRUNC, .name = "O_TRUNC" },
  { .value = O_RDONLY, .name = "O_RDONLY" },
  { .value = O_WRONLY, .name = "O_WRONLY" },
  { .value = O_RDWR, .name = "O_RDWR" },
};

int
strace_print_flags(unsigned long long int value,
		   size_t size,
		   const struct s_flag *flags)
{
  size_t	i;
  size_t	j;
  int		printed;
  long long int	cdb;

  i = j = 0;
  printed = 0;
  cdb = (long long int) value;
  while (i < size)
    {
      if ((cdb & flags[i].value) == flags[i].value)
	{
	  if (j > 0)
	    printed += fprintf(stderr, "|");
	  printed += fprintf(stderr, "%s", flags[i].name);
	  j++;
	}
      i++;
    }
  return (printed);
}

int
strace_print_flags_open(unsigned long long int value,
			pid_t child,
			const struct user_regs_struct *regs)
{
  (void) child;
  (void) regs;
  return (strace_print_flags(value, ARRAYSIZE(g_open_flags), g_open_flags));
}

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
  (void) opts;
  if (!scall->noreturn)
    {
      if (opts->compliant)
	fprintf(stderr, ")%*s= 0x%llx\n", MAX(40 - printed, 0), " ", regs->rax);
      else
	fprintf(stderr, ") = 0x%llx\n", regs->rax);
    }
  else
    {
      if (opts->compliant)
	fprintf(stderr, ")%*s= ?\n", MAX(40 - printed, 0), " ");
      else
	fprintf(stderr, ") = ?\n");
    }
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
  int				printed;

  if (strace_syscall_get_by_id(regs->rax, &scall))
    {
      fprintf(stderr, "Unknown syscall no: %llu\n", regs->rax);
      return (0);
    }
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
