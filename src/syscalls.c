/*
** syscalls.c for  in /home/vagrant/Projects/insru/strace/PSU_2015_strace
**
** Made by Babine
** Login   <vagrant@epitech.net>
**
** Started on  Sat Apr  9 19:30:52 2016
** Last update Sat Apr  9 19:36:23 2016 
*/

#include <stdlib.h>
#include "strace.h"

struct s_syscall	g_syscalls[] = {
  {
    .id = 0,
    .name = "read",
    .retval = R_SSIZE_T,
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
    .retval = R_SSIZE_T,
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
    .retval = R_VOID,
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
    .retval = 0,
    .argc = 0,
    .args = {{ 0 }},
  },
};
