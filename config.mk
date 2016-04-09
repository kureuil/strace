##
## config.mk for philo in /home/louis/work/sysunix/PSU_2015_philo
##
## Made by Louis Person
## Login   <person_l@epitech.net>
##
## Started on  Tue Mar 01 19:25:03 2016 Louis Person
## Last update Sat Apr  9 19:34:07 2016 
##

NAME	= strace

SRCS	= \
	src/main.c \
	src/optparser.c \
	src/strace.c \
	src/syscalls.c

TSTSRCS	= \
	utests/main.c

LIBS	= lib/libarray.a
