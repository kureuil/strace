[BITS 64]			;3409;0c

section .data
	msg     db  'Hello, world!',0xa	;our dear string
	len     equ $ - msg		;length of our dear string
	
section .text
	global _start

_start:
	push rbp
	mov rbp, rsp
	mov rax, 1
	mov rdi, 1
	mov rsi, msg
	mov rdx, len
	syscall
	mov rax, 60
	syscall
