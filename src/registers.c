/*
** registers.c for strace in /home/kureuil/Work/strace/src
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Sun Apr 10 17:26:36 2016 Arch Kureuil
** Last update Sun Apr 10 21:42:23 2016 Arch Kureuil
*/

#include <sys/types.h>
#include <sys/ptrace.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include "strace.h"

unsigned long long int
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
strace_read_string_slice(pid_t child,
			 unsigned long long int addr,
			 size_t readb,
			 char **strp)
{
  unsigned long	tmp;

  errno = 0;
  tmp = ptrace(PTRACE_PEEKDATA, child, addr + readb);
  if (errno)
    {
      (*strp)[readb] = '\0';
      return (-1);
    }
  memcpy(*strp + readb, &tmp, sizeof(tmp));
  if (memchr(&tmp, 0, sizeof(tmp)) != NULL)
    return (1);
  return (0);
}

void
strace_read_string(char **strp,
		   unsigned long long int addr,
		   pid_t child)
{
  size_t	allocated;
  size_t	readb;

  allocated = 16;
  readb = 0;
  if ((*strp = realloc(*strp, allocated)) == NULL)
    return ;
  while (true)
    {
      if ((readb + sizeof(unsigned long)) > allocated)
	{
	  allocated <<= 1;
	  if ((*strp = realloc(*strp, allocated)) == NULL)
	    return ;
	}
      if (strace_read_string_slice(child, addr, readb, strp))
	return ;
      readb += sizeof(unsigned long);
    }
}

int
strace_read_buf(unsigned long long addr,
		pid_t child,
		size_t nbytes,
		void *buffer)
{
  unsigned long tmp;
  size_t        readb;
  size_t	written;

  readb = 0;
  while (readb < nbytes)
    {
      errno = 0;
      tmp = ptrace(PTRACE_PEEKDATA, child, addr + readb);
      if (errno)
	return (-1);
      if ((nbytes - readb) / sizeof(tmp))
	written = sizeof(tmp);
      else
	written = nbytes % sizeof(tmp);
      memcpy((void *)((uintptr_t)buffer + readb), &tmp, written);
      readb += written;
    }
  return (0);
}

