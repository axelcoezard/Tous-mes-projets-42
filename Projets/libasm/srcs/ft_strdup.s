section .text
	global	_ft_strdup
	extern	_ft_strlen
	extern	_ft_strcpy
	extern	_malloc

_ft_strdup:
	jmp		_begin

_begin:
	call	_ft_strlen
	add		rax, 0x1	; rax = strlen(str) + 1
	push	rdi			;
	mov		rdi, rax	; ajoute la taille +0 a rdi
	call	_malloc
	pop		r8			; recupere le string dans r8
	mov		rdi, rax	; copie rax (buffer) dans rdi (destination)
	mov		rsi, r8		; copie r8 (string) dans rsi (source)
	call	_ft_strcpy
	jmp 	_end

_end:
	ret
