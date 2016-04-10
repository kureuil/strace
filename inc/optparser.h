/*
** optparser.h for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Mon Apr  4 21:54:10 2016 Arch Kureuil
** Last update Sun Apr 10 21:05:46 2016 Arch Kureuil
*/

#ifndef OPTPARSER_H_
# define OPTPARSER_H_

struct s_strace_opts;

typedef int (*t_optparser)(struct s_strace_opts *opts);

struct s_option
{
  char		flag;
  t_optparser	callback;
};

int optparse(int argc, char *av[], struct s_strace_opts *opts);

int strace_option_compliant(struct s_strace_opts *opts);

int strace_option_pid(struct s_strace_opts *opts);

int strace_option_align(struct s_strace_opts *opts);

int strace_option_file(struct s_strace_opts *opts);

#endif
