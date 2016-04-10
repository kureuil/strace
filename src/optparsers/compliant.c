/*
** compliant.c for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Sun Apr 10 20:37:04 2016 Arch Kureuil
** Last update Sun Apr 10 20:37:24 2016 Arch Kureuil
*/

#include "strace.h"

int
strace_option_compliant(struct s_strace_opts *opts)
{
  opts->compliant = true;
  return (0);
}
