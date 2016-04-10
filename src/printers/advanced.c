/*
** advanced.c for strace in /home/kureuil/Work/strace/src
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Sun Apr 10 17:24:59 2016 Arch Kureuil
** Last update Sun Apr 10 18:03:11 2016 Arch Kureuil
*/

#include <sys/types.h>
#include <sys/user.h>
#include <stdio.h>
#include <stdlib.h>
#include "strace.h"

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
strace_print_string(unsigned long long int value,
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
      strace_read_string(&str, value, child);
      ret = fprintf(stderr, "\"%s\"", str);
      free(str);
      return (ret);
    }
}

int
strace_print_size_t(unsigned long long int value,
		    pid_t child,
		    const struct user_regs_struct *regs)
{
  (void) child;
  (void) regs;
  return (fprintf(stderr, "%zu", (size_t) value));
}

int
strace_print_ssize_t(unsigned long long int value,
		     pid_t child,
		     const struct user_regs_struct *regs)
{
  (void) child;
  (void) regs;
  return (fprintf(stderr, "%zu", (ssize_t) value));
}