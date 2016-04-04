/*
** optparser.h for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Mon Apr  4 21:54:10 2016 Arch Kureuil
** Last update Mon Apr  4 21:57:17 2016 Arch Kureuil
*/

#ifndef OPTPARSER_H_
# define OPTPARSER_H_

struct s_strace_opts;

int optparse(int argc, char *av[], struct s_strace_opts *opts);

#endif
