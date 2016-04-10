/*
** hexa.c for strace in /home/kureuil/Work/strace/src
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Sun Apr 10 17:22:46 2016 Arch Kureuil
** Last update Sun Apr 10 17:24:51 2016 Arch Kureuil
*/

#include <sys/types.h>
#include <sys/user.h>
#include <stdio.h>

int
strace_print_hexa(unsigned long long int value,
		  pid_t child,
		  const struct user_regs_struct *regs)
{
  (void) child;
  (void) regs;
  return (fprintf(stderr, "0x%llx", value));
}

int
strace_print_integer(unsigned long long int value,
		     pid_t child,
		     const struct user_regs_struct *regs)
{
  (void) child;
  (void) regs;
  return (fprintf(stderr, "%d", (int) value));
}

int
strace_print_pointer(unsigned long long int value,
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

int
strace_print_long(unsigned long long int value,
		  pid_t child,
		  const struct user_regs_struct *regs)
{
  (void) child;
  (void) regs;
  return (fprintf(stderr, "%ld", (long) value));
}

int
strace_print_ulong(unsigned long long int value,
		   pid_t child,
		   const struct user_regs_struct *regs)
{
  (void) child;
  (void) regs;
  return (fprintf(stderr, "%lu", (unsigned long) value));
}

