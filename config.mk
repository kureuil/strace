##
## config.mk for philo in /home/louis/work/sysunix/PSU_2015_philo
##
## Made by Louis Person
## Login   <person_l@epitech.net>
##
## Started on  Tue Mar 01 19:25:03 2016 Louis Person
## Last update Sun Apr 10 18:02:43 2016 Arch Kureuil
##

NAME	= strace

SRCS	= \
	src/main.c \
	src/optparser.c \
	src/strace.c \
	src/syscalls.c \
	src/syscall.c \
	src/peek.c \
	src/registers.c \
	src/printers/base.c \
	src/printers/advanced.c \
	src/printers/open.c \
	src/printers/stat.c

TSTSRCS	= \
	utests/main.c

LIBS	= lib/libarray.a
