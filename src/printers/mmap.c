/*
** mmap.c for  in /home/vagrant/Projects/insru/strace/PSU_2015_strace
** 
** Made by 
** Login   <vagrant@epitech.net>
** 
** Started on  Sun Apr 10 17:36:04 2016 
** Last update Sun Apr 10 21:12:59 2016 Arch Kureuil
*/

#define _GNU_SOURCE
#include <sys/user.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "strace.h"

static const struct s_flag g_mmap_flags[] = {
  { .value = PROT_EXEC, .name = "PROT_EXEC" },
  { .value = PROT_READ, .name = "PROT_READ" },
  { .value = PROT_WRITE, .name = "PROT_WRITE" },
  { .value = PROT_NONE, .name = "PROT_NONE" },
  { .value = MAP_SHARED, .name = "MAP_SHARED" },
  { .value = MAP_PRIVATE, .name = "MAP_PRIVATE" }
    };

int
strace_print_mmap_flags(unsigned long long int value,
			pid_t child,
			const struct user_regs_struct *regs,
			const struct s_strace_opts *opts)
{
  (void) child;
  (void) regs;
  return (strace_print_flags(value, ARRAYSIZE(g_mmap_flags),
			     g_mmap_flags, opts));
}
