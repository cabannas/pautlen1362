; Manejo de secciones de datos y código
segment .data
	_x dd 10

segment .bss
	_y resd 1
	__esp resd 1

segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float

  _init :
    mov dword [__esp] , esp ; Guarda el puntero de la pila
    ret
  _quit :
    mov dword esp, [__esp]  ; Restauración de puntero de pila
    ret


main:
    call _init


	mov dword [_y], 9

	push dword [_x]
	call print_int
	add esp, 4
	call print_endofline


	push dword 100
	call print_int
	add esp, 4
	call print_endofline


	push dword [_y]
	call print_int
	add esp, 4
	call print_endofline


    call _quit
    ret
