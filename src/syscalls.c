/*
** syscalls.c for  in /home/vagrant/Projects/insru/strace/PSU_2015_strace
**
** Made by Babine
** Login   <vagrant@epitech.net>
**
** Started on  Sat Apr  9 19:30:52 2016
** Last update Sat Apr  9 23:48:20 2016 Arch Kureuil
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
    .id = 2,
    .name = "open",
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
    .id = 3,
    .name = "close",
    .noreturn = false,
    .retval = T_INTEGER,
    .argc = 1,
    .args = {
      {
	.custom = false,
	.printer = {
	  .type = T_INTEGER
	}
      }
    }
  },
  {
    .id = 4,
    .name = "stat",
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
	  .type = T_POINTER
	}
      }
    },
  },
  {
    .id = 5,
    .name = "fstat",
    .noreturn = false,
    .retval = T_INTEGER,
    .argc = 2,
    .args = {
      {
	.custom = false,
	.printer = {
	  .type = T_INTEGER,
	}
      },
      {
	.custom = false,
	.printer = {
	  .type = T_POINTER
	}
      },
    }
  },
  {
    .id = 6,
    .name = "lstat",
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
	  .type = T_POINTER
	}
      }
    }
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
    .id = 16,
    .name = "ioctl",
    .noreturn = false,
    .retval = T_INTEGER,
    .argc = 2,
    .args = {
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
      }
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
	  .type = T_POINTER
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
    .id = 78,
    .name = "getdents",
    .noreturn = false,
    .retval = T_INTEGER,
    .argc = 3,
    .args = {
      {
	.custom = false,
	.printer = {
	  .type = T_INTEGER,
	}
      },
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
    },
  },
  {
    .id = 137,
    .name = "statfs",
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
	  .type = T_POINTER
	}
      }
    }
  },
  {
    .id = 158,
    .name = "arch_prctl",
    .noreturn = false,
    .retval = T_INTEGER,
    .argc = 2,
    .args = {
      {
	.custom = false,
	.printer = {
	  .type = T_INTEGER
	}
      },
      {
	.custom = false,
	.printer = {
	  .type = T_ULONG
	}
      }
    }
  },
  {
    .id = 231,
    .name = "exit_group",
    .noreturn = true,
    .retval = T_DEFAULT,
    .argc = 1,
    .args = {
      {
	.custom = false,
	.printer = {
	  .type = T_INTEGER
	}
      }
    },
  },
  {
    .id = 257,
    .name = "openat",
    .noreturn = false,
    .retval = T_INTEGER,
    .argc = 3,
    .args = {
      {
	.custom = false,
	.printer = {
	  .type = T_INTEGER
	}
      },
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
      }
    }
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
