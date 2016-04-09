/*
** strace.h for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Mon Apr  4 21:50:50 2016 Arch Kureuil
** Last update Sat Apr  9 23:04:17 2016 Arch Kureuil
*/

#ifndef STRACE_H_
# define STRACE_H_

# include <stdbool.h>
# include <sys/types.h>

# define MANAGED(dtor)			__attribute__((__cleanup__(dtor)))
# define STRACE_IS_SYSCALL(instr)	((instr & 0xffff) == 0x50f)

# define STRACE_SYSCALL_ARGS_MAX	6

typedef void (*t_printer)(unsigned long long int);

struct s_strace_opts
{
  pid_t	pid;
  char	**command;
  bool	compliant;
};

enum e_type
  {
    T_DEFAULT,
    T_INTEGER,
    T_POINTER,
    T_STRING,
    T_LONG,
    T_ULONG,
    T_SIZE_T,
    T_SSIZE_T,
  };

struct s_syscall_arg
{
  bool	custom;
  union
  {
    enum e_type	type;
    t_printer	callback;
  }	printer;
};

struct s_syscall
{
  unsigned long long	id;
  const char		*name;
  bool			noreturn;
  enum e_type		retval;
  size_t		argc;
  struct s_syscall_arg	args[STRACE_SYSCALL_ARGS_MAX];
};

extern struct s_syscall g_syscalls[];

/*
** Trace all system calls made by the given PID.
**
** @param pid the traced program id
** @param opts the options given to strace
** @return 0 in case of success, -1 in case of failure
*/
int strace(pid_t pid, const struct s_strace_opts *opts);

#endif
