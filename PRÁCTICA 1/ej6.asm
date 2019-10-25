
;escribir_subseccion_data
segment .data
	msj_error_div_0 db "Division por cero", 0
	msj_error_ind_fuera_rango db "Indice fuera de rango", 0
;escribir_cabecera_bss
segment .bss
	__esp resd 1
;declarar_variable
	_m resd 1

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
	push dword 6
;asignar
	pop dword eax
	mov dword [_m], eax
;escribir_operando
	push dword _m
;escribir_operando
	push dword 5
;mayor
	pop dword edx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, edx
	jg _mayor1
	mov eax, 0
	jmp _fin_mayor1
_mayor1:
	mov eax, 1
_fin_mayor1:
	push dword eax
;ifthenelse_inicio
	pop dword eax
	cmp eax, 0
	je near _before_else1
;escribir_operando
	push dword 2
;escribir
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;ifthenelse_fin_then
	jmp near _after_else1
_before_else1:
;escribir_operando
	push dword 3
;escribir
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;ifthenelse_fin
_after_else1:
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
