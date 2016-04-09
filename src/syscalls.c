/*
** syscalls.c for  in /home/vagrant/Projects/insru/strace/PSU_2015_strace
**
** Made by Babine
** Login   <vagrant@epitech.net>
**
** Started on  Sat Apr  9 19:30:52 2016
** Last update Sat Apr  9 23:10:48 2016 Arch Kureuil
*/

#include <stdlib.h>
#include "strace.h"

struct s_syscall	g_syscalls[] = {
  {
    .id = 0,
    .name = "read",
    .noreturn = false,
    .retval = T_SSIZE_T,
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
    .noreturn = false,
    .retval = T_SSIZE_T,
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
    .id = 9,
    .name = "mmap",
    .noreturn = false,
    .retval = T_POINTER,
    .argc = 6,
    .args = {
      {
	.custom = false,
	.printer = {
	  .type = T_POINTER
	}
      },
      {
	.custom = false,
	.printer = {
	  .type = T_SIZE_T
	},
      },
      {
	.custom = false,
	.printer = {
	  .type = T_INTEGER
	}
      },
      {
	.custom = false,
	.printer = {
	  .type = T_INTEGER
	}
      },
      {
	.custom = false,
	.printer = {
	  .type = T_INTEGER
	}
      },
      {
	.custom = false,
	.printer = {
	  .type = T_LONG
	}
      },
    }
  },
  {
    .id = 10,
    .name = "mprotect",
    .noreturn = false,
    .retval = T_INTEGER,
    .argc = 3,
    .args = {
      {
	.custom = false,
	.printer = {
	  .type = T_POINTER
	}
      },
      {
	.custom = false,
	.printer = {
	  .type = T_SIZE_T
	}
      },
      {
	.custom = false,
	.printer = {
	  .type = T_INTEGER
	}
      }
    }
  },
  {
    .id = 11,
    .name = "munmap",
    .noreturn = false,
    .retval = T_INTEGER,
    .argc = 2,
    .args = {
      {
	.custom = false,
	.printer = {
	  .type = T_POINTER
	}
      },
      {
	.custom = false,
	.printer = {
	  .type = T_SIZE_T
	}
      }
    }
  },
  {
    .id = 12,
    .name = "brk",
    .noreturn = false,
    .retval = T_POINTER,
    .argc = 1,
    .args = {
      {
	.custom = false,
	.printer = {
	  .type = T_ULONG,
	},
      },
    }
  },
  {
    .id = 21,
    .name = "access",
    .noreturn = false,
    .retval = T_INTEGER,
    .argc = 2,
    .args = {
      {
	.custom = false,
	.printer = {
	  .type = T_STRING
	}
      },
      {
	.custom = false,
	.printer = {
	  .type = T_INTEGER
	}
      },
    }
  },
  {
    .id = 60,
    .name = "_exit",
    .noreturn = true,
    .retval = T_DEFAULT,
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
    .noreturn = false,
    .retval = 0,
    .argc = 0,
    .args = {{ 0 }},
  },
};
