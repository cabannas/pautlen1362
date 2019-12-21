
;escribir_subseccion_data
segment .data
	msj_error_div_0 db "Division por cero", 0
	msj_error_ind_fuera_rango db "Indice fuera de rango", 0
;escribir_cabecera_bss
segment .bss
	__esp resd 1
;declarar_variable
	_m resd 1
;declarar_variable
	_v resd 4
;declarar_variable
	_vb resd 4

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
	push dword 0
;asignar
	pop dword eax
	mov dword [_m], eax
;while_inicio
_while_inicio0:
;escribir_operando
	push dword _m
;escribir_operando
	push dword 4
;menor
	pop dword edx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, edx
	jl _menor0
	mov eax, 0
	jmp _fin_menor0
_menor0:
	mov eax, 1
_fin_menor0:
	push dword eax
;while_exp_pila
	pop dword eax
	cmp eax, 0
	je near _while_fin0
;escribir_operando
	push dword _m
;escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;escribir_operando
	push dword _m
;escribir_operando
	push dword 10
;multiplicar
	pop dword ecx
	pop dword eax
	mov dword eax, [eax]
	cdq
	imul ecx
	push dword eax
;escribir_operando
	push dword _m
;escribir_elemento_vector
	pop dword eax
	mov dword eax, [eax]
	cmp eax, 0
	jl near error_indice_fuera_rango
	cmp eax, 4
	jge near error_indice_fuera_rango
	mov dword edx, _v
	lea eax, [edx + eax *4]
	push dword eax
;asignarDestinoEnPila
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;escribir_operando
	push dword _m
;escribir_operando
	push dword 2
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
;no
	pop dword eax
	cmp eax, 0
	je _es_cero2
	mov dword eax, 0
	jmp _no_fin2
_es_cero2:
	mov dword eax, 1
_no_fin2:
	push dword eax
;escribir_operando
	push dword _m
;escribir_elemento_vector
	pop dword eax
	mov dword eax, [eax]
	cmp eax, 0
	jl near error_indice_fuera_rango
	cmp eax, 4
	jge near error_indice_fuera_rango
	mov dword edx, _vb
	lea eax, [edx + eax *4]
	push dword eax
;asignarDestinoEnPila
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;escribir_operando
	push dword _m
;escribir_operando
	push dword 1
;sumar
	pop dword edx
	pop dword eax
	mov dword eax, [eax]
	add eax, edx
	push dword eax
;asignar
	pop dword eax
	mov dword [_m], eax
;while_fin
	jmp near _while_inicio0
_while_fin0:
;escribir_operando
	push dword 0
;asignar
	pop dword eax
	mov dword [_m], eax
;while_inicio
_while_inicio1:
;escribir_operando
	push dword _m
;escribir_operando
	push dword 4
;menor
	pop dword edx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, edx
	jl _menor3
	mov eax, 0
	jmp _fin_menor3
_menor3:
	mov eax, 1
_fin_menor3:
	push dword eax
;while_exp_pila
	pop dword eax
	cmp eax, 0
	je near _while_fin1
;escribir_operando
	push dword _m
;escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;escribir_operando
	push dword _m
;escribir_operando
	push dword 2
;menor
	pop dword edx
	pop dword eax
	mov dword eax, [eax]
	cmp eax, edx
	jl _menor4
	mov eax, 0
	jmp _fin_menor4
_menor4:
	mov eax, 1
_fin_menor4:
	push dword eax
;ifthenelse_inicio
	pop dword eax
	cmp eax, 0
	je near _before_else2
;escribir_operando
	push dword _m
;escribir_elemento_vector
	pop dword eax
	mov dword eax, [eax]
	cmp eax, 0
	jl near error_indice_fuera_rango
	cmp eax, 4
	jge near error_indice_fuera_rango
	mov dword edx, _v
	lea eax, [edx + eax *4]
	push dword eax
;escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;ifthenelse_fin_then
	jmp near _after_else2
_before_else2:
;escribir_operando
	push dword _m
;escribir_elemento_vector
	pop dword eax
	mov dword eax, [eax]
	cmp eax, 0
	jl near error_indice_fuera_rango
	cmp eax, 4
	jge near error_indice_fuera_rango
	mov dword edx, _vb
	lea eax, [edx + eax *4]
	push dword eax
;escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_boolean
	add esp, 4
	call print_endofline
;ifthenelse_fin
_after_else2:
;escribir_operando
	push dword _m
;escribir_operando
	push dword 1
;sumar
	pop dword edx
	pop dword eax
	mov dword eax, [eax]
	add eax, edx
	push dword eax
;asignar
	pop dword eax
	mov dword [_m], eax
;while_fin
	jmp near _while_inicio1
_while_fin1:
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
