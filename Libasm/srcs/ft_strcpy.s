section .text
	global	_ft_strcpy

_ft_strcpy:
	xor		rax, rax
	xor		cl, cl
	jmp		_begin

_begin:
	mov 	cl, byte [rsi + rax]
	mov 	byte [rdi + rax], cl
	cmp		cl, 0x0
	je		_end
	inc 	rax
	jmp 	_begin

_end:
	mov 	rax, rdi
	ret
