segment .data

segment .bss
	__esp resd 1
	_x resd 1
	_y resd 1
	_z resd 1

segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float

then:
	mov dword [_z], 1
	call continue

else:
	mov dword [_z], 2
	call continue

main:
	mov dword [__esp], esp

	;SCAN_FUNCTION
	push dword _x
	call scan_int
	add esp, 4
	push dword [_x]

	;SCAN_FUNCTION
	push dword _y
	call scan_int
	add esp, 4
	push dword [_y]

	;IF_STATEMENT
	push dword [_x]
	pop eax
	push dword [_y]
	pop ebx
	cmp eax, ebx
	jge then
	call else
continue:
	;PRINT_FUNCTION
	push dword [_z]
	call print_int
	add esp, 4
	push dword [_z]

quit:
	mov dword esp, [__esp]
	ret
