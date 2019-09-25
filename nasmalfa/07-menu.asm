segment .data
    _label_menu db "Menú: [1] Suma. [2] Multilpicación. [3] Parte entera de una división. [4] Salir.", 0
    _label_choice db "Su opción: ", 0
    _process1 db "Procesando suma ... ", 0
    _process2 db "Procesando multiplicación ...", 0
    _process3 db "Procesando división ...", 0
    _sumares db "El resultado de la suma es: ", 0
    _multres db "El resultado de la multiplicación es: ", 0
    _divres db "El resultado entero de la división es: ", 0
    _simbsuma db " + ", 0
    _simbmult db " * ", 0
    _simbdiv db " / ", 0
    _simbigual db " = ", 0

    _x dw 0x10
    _y dw 0x11

segment .bss
	__esp    resd 1
	_option  resd 1
	_z resd 1

segment .text
	global main
	extern print_string, print_endofline, scan_int, print_int

main:
	mov dword [__esp], esp

menu:
    ;Mostrar menú
	push dword _label_menu
	call print_string
	add esp, 4
	call print_endofline

    ;Elegir opción
    push dword _label_choice
	call print_string
	add esp, 4
	push dword _option
    call scan_int
	add esp, 4
	push dword [_option]

    ;Ejecutar opción de menú
	pop eax
	cmp eax, 1
	je suma
	cmp eax, 2
	je multiplicacion
	cmp eax,3
	je division
	cmp eax, 4
	je salir
	call menu

suma:

  push dword _x
  call print_int
  call print_endofline
  push dword [_x]
  call print_int
  call print_endofline
  push dword _x
  pop eax
  push dword _y
  pop edx
  mov eax, 10
  mov edx, 11
	add eax, edx

	mov [_z], eax

	push dword _sumares
	call print_string
	add esp, 4
	push dword [_x]
	call print_int
	add esp, 4
	push dword _simbsuma
	call print_string
	add esp, 4
	push dword [_y]
	call print_int
	add esp, 4
	push dword _simbigual
	call print_string
	add esp, 4
	push dword [_z]
	call print_int
	add esp, 4

	call print_endofline
  call menu

multiplicacion:
  push dword _x
  call scan_int
	add esp, 4
	push dword [_x]
  push dword _y
  call scan_int
	add esp, 4
	push dword [_y]

	mov eax, [_x]
	mov edx, [_y]
	imul edx

	mov [_z], eax

	push dword _multres
	call print_string
	add esp, 4
	push dword [_x]
	call print_int
	add esp, 4
	push dword _simbmult
	call print_string
	add esp, 4
	push dword [_y]
	call print_int
	add esp, 4
	push dword _simbigual
	call print_string
	add esp, 4
	push dword [_z]
	call print_int
	add esp, 4

	call print_endofline
  call menu

division:
  push dword _x
  call scan_int
	add esp, 4
	push dword [_x]
  push dword _y
  call scan_int
	add esp, 4
	push dword [_y]

  mov edx, 0
	mov eax, [_x]
	mov ecx, [_y]
	idiv ecx

	mov [_z], eax

	push dword _divres
	call print_string
	add esp, 4
	push dword [_x]
	call print_int
	add esp, 4
	push dword _simbdiv
	call print_string
	add esp, 4
	push dword [_y]
	call print_int
	add esp, 4
	push dword _simbigual
	call print_string
	add esp, 4
	push dword [_z]
	call print_int
	add esp, 4

	call print_endofline
  call menu

salir:
	mov dword esp, [__esp]
	ret
