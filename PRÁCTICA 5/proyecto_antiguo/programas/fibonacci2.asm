;escribir_subseccion_data

segment .data

	_msg_fuera_rango db "****Error de ejecucion: Indice fuera de rango.", 0

	_msg_div_cero db "Error de ejecucion: Division por cero", 0

;escribir_cabecera_bss

segment .bss

__esp resd 1
	_x resd 1
	_resultado resd 1
;escribir_segmento_codigo

segment .text
	global main
	extern scan_int, print_int, scan_float, print_float,
	extern scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float



_fibonacci:
	push ebp
	mov ebp, esp
	sub esp, 4*2
	lea eax, [ebp+8]
	push dword [eax]
; numero_linea 15
	push dword 0
; igual
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
; comparar y apilar el resultado
	cmp eax, edx
	je near igual1
	push dword 0
	jmp near fin_igual1

igual1:
	push dword 1

fin_igual1:

	pop dword eax
	cmp eax, 0
	je near fin_si2
; numero_linea 17
	push dword 0

	pop dword eax

	mov dword esp, ebp
	pop dword ebp
	ret

fin_si2:
	lea eax, [ebp+8]
	push dword [eax]
; numero_linea 19
	push dword 1
; igual
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
; comparar y apilar el resultado
	cmp eax, edx
	je near igual3
	push dword 0
	jmp near fin_igual3

igual3:
	push dword 1

fin_igual3:

	pop dword eax
	cmp eax, 0
	je near fin_si4
; numero_linea 21
	push dword 1

	pop dword eax

	mov dword esp, ebp
	pop dword ebp
	ret

fin_si4:
	lea eax, [ebp+8]
	push dword [eax]
; numero_linea 23
	push dword 1
;restar
; cargar el segundo operando en edx
	pop dword edx
; cargar el primer operando en eax
	pop dword eax
; realizar la resta y dejar el resultado en eax
	sub eax, edx
; apilar el resultado
	push dword eax

	call _fibonacci
	add esp, 4*1
	push dword eax

	pop dword eax
	mov dword [ebp-4], eax
	lea eax, [ebp+8]
	push dword [eax]
; numero_linea 24
	push dword 2
;restar
; cargar el segundo operando en edx
	pop dword edx
; cargar el primer operando en eax
	pop dword eax
; realizar la resta y dejar el resultado en eax
	sub eax, edx
; apilar el resultado
	push dword eax

	call _fibonacci
	add esp, 4*1
	push dword eax

	pop dword eax
	mov dword [ebp-8], eax
	lea eax, [ebp-4]
	push dword [eax]
	lea eax, [ebp-8]
	push dword [eax]
;sumar
; cargar el segundo operando en edx
	pop dword edx
; cargar el primer operando en eax
	pop dword eax
; realizar la suma y dejar el resultado en eax
	add eax, edx
; apilar el resultado
	push dword eax

	pop dword eax

	mov dword esp, ebp
	pop dword ebp
	ret
;escribir_inicio_main
main: 
	mov dword [__esp], esp

;leer
	push dword _x
	call scan_int
	add esp, 4
;escribir_operando
	push dword [_x]

	call _fibonacci
	add esp, 4*1
	push dword eax
	pop dword eax
	mov dword [_resultado], eax
;escribir_operando
	push dword _resultado
; Acceso al valor de exp si es distinto de constante
	pop dword eax
	mov dword eax , [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
	jmp near fin

FUERA_RANGO:
	push dword _msg_fuera_rango
	call print_string
	add esp, 4
	jmp near fin

DIV_CERO:
	push dword _msg_div_cero
	call print_string
	add esp, 4
	jmp near fin
;escribir_fin
	fin:
	mov dword esp, [__esp]
	ret
