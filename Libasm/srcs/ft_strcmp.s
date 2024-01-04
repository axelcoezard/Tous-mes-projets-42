section .text
	global	_ft_strcmp

_ft_strcmp:
	xor		rax, rax
	xor		rcx, rcx
	xor		rdx, rdx
	xor		al, al
	jmp		_begin

_begin:
	; si *s1 == 0 on termine
	cmp		byte [rdi + rcx], 0x0
	jz		_end
	; si *s2 == 0 on termine
	cmp		byte [rsi + rcx], 0x0
	jz		_end
	; si *s1 != *s2 on termine
	mov		al, byte [rsi + rcx]
	cmp		byte [rdi + rcx], al
	jne		_end
	; sinon s1++ et s2++
	inc		rcx
	jmp		_begin

_end:
	; on retourne *s1 - *s2
	movzx	rax, byte [rdi + rcx]
	movzx	rdx, byte [rsi + rcx]
	sub		rax, rdx
	ret
