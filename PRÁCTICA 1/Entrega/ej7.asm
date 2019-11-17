
;escribir_subseccion_data
segment .data
	msj_error_div_0 db "Division por cero", 0
	msj_error_ind_fuera_rango db "Indice fuera de rango", 0
;escribir_cabecera_bss
segment .bss
	__esp resd 1
;declarar_variable
	_z resd 1

;escribir_segmento_codigo
segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float

;declararFuncion
_doble:
	push ebp
	mov ebp, esp
	sub esp, 4*1
;escribirParametro
	lea eax, [ebp + 8]
	push dword eax
;escribirVariableLocal
	lea eax, [ebp - 4]
	push dword eax
;asignarDestinoEnPila
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	mov dword [ebx], eax
;escribir_operando
	push dword 2
;escribirParametro
	lea eax, [ebp + 8]
	push dword eax
;multiplicar
	pop dword ecx
	mov dword ecx, [ecx]
	pop dword eax
	cdq
	imul ecx
	push dword eax
;retornarFuncion
	pop dword eax
	mov esp, ebp
	pop ebp
	ret
;escribir_inicio_main
main:
	mov dword [__esp], esp

;escribir_operando
	push dword 2
;asignar
	pop dword eax
	mov dword [_z], eax
;escribir_operando
	push dword _z
;operandoEnPilaAArgumento
	pop dword eax
	mov dword eax, [eax]
	push dword eax
;llamarFuncion
	call _doble
;limpiarPila
	add esp, 4*1
	push dword eax
;escribir
	pop dword eax
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;escribir_fin
quit:
	mov dword esp, [__esp]
	ret
error_division_por_cero:
	push dword msj_error_div_0
	call print_string
	add esp, 4
	call print_endofline
	jmp near quit
error_indice_fuera_rango:
	push dword msj_error_ind_fuera_rango
	call print_string
	add esp, 4
	call print_endofline
	jmp near quit
