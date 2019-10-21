
;escribir_subseccion_data
segment .data
;escribir_cabecera_bss
segment .bss
	__esp resd 1
;declarar_variable
	_x resd 1
;declarar_variable
	_y resd 1
;declarar_variable
	_z resd 1

;escribir_segmento_codigo
segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float

;escribir_inicio_main
main:
	mov dword [__esp], esp

;escribir_operando
	push dword 8
;asignar
	pop dword eax
	mov dword [_x], eax
;leer
	push dword _y
	call scan_int
	add esp, 4
;escribir_operando
	push dword _x
;escribir_operando
	push dword _y
;sumar
	pop dword edx
	mov dword edx, [edx]
	pop dword eax
	mov dword eax, [eax]
	add eax, edx
	push dword eax
;asignar
	pop dword eax
	mov dword [_z], eax
;escribir_operando
	push dword _z
;escribir
	pop dword eax
	mov eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;escribir_operando
	push dword 7
;escribir_operando
	push dword _y
;sumar
	pop dword edx
	mov dword edx, [edx]
	pop dword eax
	add eax, edx
	push dword eax
;asignar
	pop dword eax
	mov dword [_z], eax
;escribir_operando
	push dword _z
;escribir
	pop dword eax
	mov eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;escribir_fin
quit:
	mov dword esp, [__esp]
	ret
