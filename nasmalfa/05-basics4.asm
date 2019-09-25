segment .data
	_b1 dd 1
segment .bss
	_b2 resd 1
	__esp resd 1
segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float

main:
	mov dword [__esp] , esp

    ; ESCRIBIMOS LA VARIABLE b1 QUE VALE 1
	push dword [_b1]
	call print_boolean
	add esp, 4
	call print_endofline

    ; LEEMOS Y ESCRIBIMOS LA VARIABLE BOOL b2
	push dword _b2
	call scan_boolean
	add esp, 4

	push dword [_b2]
	call print_boolean
	add esp, 4
	call print_endofline


; REALIZAMOS EL AND DE AMBOS Y LO MOSTRAMOS
	push dword [_b1]
	push dword [_b2]
	pop dword eax
	pop dword ebx
	and eax, ebx
	push dword eax

	call print_boolean
	add esp, 4
	call print_endofline
	

	mov dword esp, [__esp]
	ret
