section .text
	global	_ft_strlen

_ft_strlen:
	xor 	rax, rax
	jmp		_begin

_begin:
	cmp 	byte [rdi + rax], 0x0
	je 		_end
	inc 	rax
	jmp 	_begin

_end:
	ret
