/*
** strace.h for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Mon Apr  4 21:50:50 2016 Arch Kureuil
** Last update Sun Apr 10 22:25:13 2016 Arch Kureuil
*/

#ifndef STRACE_H_
# define STRACE_H_

# include <stdbool.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/user.h>

# define MANAGED(dtor)			__attribute__((__cleanup__(dtor)))
# define STRACE_IS_SYSCALL(instr)	((instr & 0xffff) == 0x50f)
# define MAX(x, y)			((x) ^ (((x) ^ (y)) & -((x) < (y))))
# define ARRAYSIZE(arr)			(sizeof(arr) / sizeof(arr[0]))

# define STRACE_SYSCALL_ARGS_MAX	6

enum e_output_type
  {
    O_INNATE,
    O_FILE,
    O_COMMAND
  };

enum e_timestamp_type
  {
    TS_NONE,
    TS_TIME,
    TS_MILLISECOND
  };

struct s_strace_opts
{
  pid_t			pid;
  char			**command;
  bool			compliant;
  long			align;
  FILE			*output;
  enum e_output_type	output_type;
  enum e_timestamp_type	timestamp_type;
};

typedef int (*t_printer)(unsigned long long int,
			 pid_t,
			 const struct user_regs_struct *,
			 const struct s_strace_opts *);

struct s_flag
{
  const char	*name;
  int		value;
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

/*
** Handle a syscall.
**
** @param child the pid of the tracee
** @param regs the registers of the tracee
** @param opts the options geiven to strace
*/
int
strace_syscall_handle(pid_t child,
		      const struct user_regs_struct *regs,
		      const struct s_strace_opts *opts);

unsigned long long int
strace_registers_get_by_idx(const struct user_regs_struct *regs,
			    size_t idx);

int
strace_peek_registers(pid_t child,
		      struct user_regs_struct *regsp);

int
strace_peek_instruction(pid_t child,
			const struct user_regs_struct *regs,
			long *instrp);

/*
** Read a string pointed by addr
**
** @param strp pointer to a string. Will be allocated with malloc
** @param addr the address to peek at
** @param child pid of the tracee
*/
void
strace_read_string(char **strp,
		   unsigned long long int addr,
		   pid_t child);

/*
** Read n bytes pointed by addr
**
** @param addr the address to peek at
** @param child the pid of the tracee
** @param nbytes number of bytes to read
** @param buffer the resulting buffer
*/
int
strace_read_buf(unsigned long long addr,
		pid_t child,
		size_t nbytes,
		void *buffer);

/*
** Function printing flags found in a value.
**
** @param value the flagged value
** @param size the size of the flags array
** @param flags the flags array
** @return the number of printed characters
*/
int
strace_print_flags(unsigned long long int value,
                   size_t size,
                   const struct s_flag *flags,
		   const struct s_strace_opts *opts);

/*
** Print the string pointed by value
**
** @param value the address of the NUL-terminated string
** @param child the pid of the tracee
** @param regs the registers of the tracee
** @return the number of printed characters
*/
int
strace_print_string(unsigned long long int value,
		    pid_t child,
		    const struct user_regs_struct *regs,
		    const struct s_strace_opts *opts);

/*
** Print value as a size_t
**
** @return the number of printed characters
*/
int
strace_print_size_t(unsigned long long int value,
		    pid_t child,
		    const struct user_regs_struct *regs,
		    const struct s_strace_opts *opts);

/*
** Print value as a ssize_t
**
** @return the number of printed characters
*/
int
strace_print_ssize_t(unsigned long long int value,
		     pid_t child,
		     const struct user_regs_struct *regs,
		     const struct s_strace_opts *opts);

/*
** Print value as errno (if value is negative)
**
** @return the number of printed characters
*/
int
strace_print_errno(unsigned long long int value,
		   pid_t child,
		   const struct user_regs_struct *regs,
		   const struct s_strace_opts *opts);

/*
** Print value as a hexadecimal number
**
** @return the number of printed characters
*/
int
strace_print_hexa(unsigned long long int value,
		  pid_t child,
		  const struct user_regs_struct *regs,
		  const struct s_strace_opts *opts);

/*
** Print value as a decimal integer
**
** @return the number of printed characters
*/
int
strace_print_integer(unsigned long long int value,
		     pid_t child,
		     const struct user_regs_struct *regs,
		     const struct s_strace_opts *opts);

/*
** Print value as a pointer
**
** @return the number of printed characters
*/
int
strace_print_pointer(unsigned long long int value,
		     pid_t child,
		     const struct user_regs_struct *regs,
		     const struct s_strace_opts *opts);

/*
** Print value as a long int
**
** @return the number of printed characters
*/
int
strace_print_long(unsigned long long int value,
		  pid_t child,
		  const struct user_regs_struct *regs,
		  const struct s_strace_opts *opts);

/*
** Print value as an unsigned long int
**
** @return the number of printed characters
*/
int
strace_print_ulong(unsigned long long int value,
		   pid_t child,
		   const struct user_regs_struct *regs,
		   const struct s_strace_opts *opts);

/*
** Print flags given to open(2)
*/
int
strace_print_flags_open(unsigned long long int value,
			pid_t child,
			const struct user_regs_struct *regs,
			const struct s_strace_opts *opts);

/*
** Print flags given to stat(2)
*/
int
strace_print_stat_struct(unsigned long long int value,
			 pid_t child,
			 const struct user_regs_struct *regs,
			 const struct s_strace_opts *opts);

/*
** Print flages given to mmap(2)
*/
int
strace_print_mmap_flags(unsigned long long int value,
			pid_t child,
			const struct user_regs_struct *regs,
			const struct s_strace_opts *opts);

#endif
