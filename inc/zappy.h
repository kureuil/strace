/*
** zappy.h for zappy in /home/kureuil/Work/zappy/server/inc
**
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
**
** Started on  Tue Mar 15 21:41:48 2016 Arch Kureuil
** Last update Sun Mar 20 11:53:28 2016 Arch Kureuil
*/

#ifndef ZAPPY_H_
# define ZAPPY_H_

# include <stdint.h>
# include <stddef.h>
# include "array/array.h"

# ifdef _UTEST_
#  include <setjmp.h>
#  include <stdarg.h>
#  include <cmocka.h>

#  define ASSERT(expr) mock_assert((int)(expr), # expr, __FILE__, __LINE__)
#  define MALLOC       test_malloc
#  define FREE         test_free
#  define REALLOC      test_realloc
#  define CALLOC       test_calloc
# endif /* !_UTEST_ */

# ifndef _UTEST_
#  include <assert.h>
#  define ASSERT       assert
#  define MALLOC       malloc
#  define FREE         free
#  define REALLOC      realloc
#  define CALLOC       calloc
# endif /* !_UTEST_ */

struct            s_server
{
  uint16_t        port;
  size_t          world_width;
  size_t          world_height;
  size_t          clients_per_team;
  struct s_array  teams;
  size_t          delay;
};

int zappy(int argc, const char *argv[]);

#endif /* !ZAPPY_H_ */
