;escribir_subseccion_data

segment .data

	_msg_fuera_rango db "****Error de ejecucion: Indice fuera de rango.", 0

	_msg_div_cero db "Error de ejecucion: Division por cero", 0

;escribir_cabecera_bss

segment .bss

__esp resd 1
	_x resd 1
	_y resd 1
	_z resd 1
;escribir_segmento_codigo

segment .text
	global main
	extern scan_int, print_int, scan_float, print_float,
	extern scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float


;escribir_inicio_main
main: 
	mov dword [__esp], esp

;leer
	push dword _x
	call scan_int
	add esp, 4
;leer
	push dword _y
	call scan_int
	add esp, 4
;leer
	push dword _z
	call scan_int
	add esp, 4
;escribir_operando
	push dword _x
; numero_linea 9
	push dword 0
; igual
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
	mov dword eax , [eax]
; comparar y apilar el resultado
	cmp eax, edx
	je near igual1
	push dword 0
	jmp near fin_igual1

igual1:
	push dword 1

fin_igual1:
;escribir_operando
	push dword _y
; numero_linea 9
	push dword 0
; igual
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
	mov dword eax , [eax]
; comparar y apilar el resultado
	cmp eax, edx
	je near igual2
	push dword 0
	jmp near fin_igual2

igual2:
	push dword 1

fin_igual2:
;y
; cargar el segundo operando en edx
	pop dword edx
; cargar el primer operando en eax
	pop dword eax
; realizar la conjunción y dejar el resultado en eax
	and eax , edx
; apilar el resultado
	push dword eax
;escribir_operando
	push dword _z
; numero_linea 9
	push dword 0
; igual
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
	mov dword eax , [eax]
; comparar y apilar el resultado
	cmp eax, edx
	je near igual3
	push dword 0
	jmp near fin_igual3

igual3:
	push dword 1

fin_igual3:
;y
; cargar el segundo operando en edx
	pop dword edx
; cargar el primer operando en eax
	pop dword eax
; realizar la conjunción y dejar el resultado en eax
	and eax , edx
; apilar el resultado
	push dword eax

	pop dword eax
	cmp eax, 0
	je near fin_si4
; numero_linea 11
	push dword 0
; Acceso al valor de exp si es distinto de constante
	call print_int
	add esp, 4
	call print_endofline

	jmp near fin_sino4

fin_si4:
;escribir_operando
	push dword _x
; numero_linea 16
	push dword 0
; mayor
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
	mov dword eax , [eax]
; comparar y apilar el resultado
	cmp eax, edx
	jg near mayor5
	push dword 0
	jmp near fin_mayor5

mayor5:
	push dword 1

fin_mayor5:
;escribir_operando
	push dword _y
; numero_linea 16
	push dword 0
; mayor
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
	mov dword eax , [eax]
; comparar y apilar el resultado
	cmp eax, edx
	jg near mayor6
	push dword 0
	jmp near fin_mayor6

mayor6:
	push dword 1

fin_mayor6:
;y
; cargar el segundo operando en edx
	pop dword edx
; cargar el primer operando en eax
	pop dword eax
; realizar la conjunción y dejar el resultado en eax
	and eax , edx
; apilar el resultado
	push dword eax

	pop dword eax
	cmp eax, 0
	je near fin_si7
;escribir_operando
	push dword _z
; numero_linea 18
	push dword 0
; mayor
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
	mov dword eax , [eax]
; comparar y apilar el resultado
	cmp eax, edx
	jg near mayor8
	push dword 0
	jmp near fin_mayor8

mayor8:
	push dword 1

fin_mayor8:

	pop dword eax
	cmp eax, 0
	je near fin_si9
; numero_linea 20
	push dword 1
; Acceso al valor de exp si es distinto de constante
	call print_int
	add esp, 4
	call print_endofline

	jmp near fin_sino9

fin_si9:
; numero_linea 24
	push dword 5
; Acceso al valor de exp si es distinto de constante
	call print_int
	add esp, 4
	call print_endofline

fin_sino9:

fin_si7:
;escribir_operando
	push dword _x
; numero_linea 27
	push dword 0
; menor
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
	mov dword eax , [eax]
; comparar y apilar el resultado
	cmp eax, edx
	jl near menor10
	push dword 0
	jmp near fin_menor10

menor10:
	push dword 1

fin_menor10:
;escribir_operando
	push dword _y
; numero_linea 27
	push dword 0
; mayor
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
	mov dword eax , [eax]
; comparar y apilar el resultado
	cmp eax, edx
	jg near mayor11
	push dword 0
	jmp near fin_mayor11

mayor11:
	push dword 1

fin_mayor11:
;y
; cargar el segundo operando en edx
	pop dword edx
; cargar el primer operando en eax
	pop dword eax
; realizar la conjunción y dejar el resultado en eax
	and eax , edx
; apilar el resultado
	push dword eax

	pop dword eax
	cmp eax, 0
	je near fin_si12
;escribir_operando
	push dword _z
; numero_linea 29
	push dword 0
; mayor
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
	mov dword eax , [eax]
; comparar y apilar el resultado
	cmp eax, edx
	jg near mayor13
	push dword 0
	jmp near fin_mayor13

mayor13:
	push dword 1

fin_mayor13:

	pop dword eax
	cmp eax, 0
	je near fin_si14
; numero_linea 31
	push dword 2
; Acceso al valor de exp si es distinto de constante
	call print_int
	add esp, 4
	call print_endofline

	jmp near fin_sino14

fin_si14:
; numero_linea 35
	push dword 6
; Acceso al valor de exp si es distinto de constante
	call print_int
	add esp, 4
	call print_endofline

fin_sino14:

fin_si12:
;escribir_operando
	push dword _x
; numero_linea 38
	push dword 0
; menor
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
	mov dword eax , [eax]
; comparar y apilar el resultado
	cmp eax, edx
	jl near menor15
	push dword 0
	jmp near fin_menor15

menor15:
	push dword 1

fin_menor15:
;escribir_operando
	push dword _y
; numero_linea 38
	push dword 0
; menor
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
	mov dword eax , [eax]
; comparar y apilar el resultado
	cmp eax, edx
	jl near menor16
	push dword 0
	jmp near fin_menor16

menor16:
	push dword 1

fin_menor16:
;y
; cargar el segundo operando en edx
	pop dword edx
; cargar el primer operando en eax
	pop dword eax
; realizar la conjunción y dejar el resultado en eax
	and eax , edx
; apilar el resultado
	push dword eax

	pop dword eax
	cmp eax, 0
	je near fin_si17
;escribir_operando
	push dword _z
; numero_linea 40
	push dword 0
; mayor
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
	mov dword eax , [eax]
; comparar y apilar el resultado
	cmp eax, edx
	jg near mayor18
	push dword 0
	jmp near fin_mayor18

mayor18:
	push dword 1

fin_mayor18:

	pop dword eax
	cmp eax, 0
	je near fin_si19
; numero_linea 42
	push dword 3
; Acceso al valor de exp si es distinto de constante
	call print_int
	add esp, 4
	call print_endofline

	jmp near fin_sino19

fin_si19:
; numero_linea 46
	push dword 7
; Acceso al valor de exp si es distinto de constante
	call print_int
	add esp, 4
	call print_endofline

fin_sino19:

fin_si17:
;escribir_operando
	push dword _x
; numero_linea 49
	push dword 0
; mayor
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
	mov dword eax , [eax]
; comparar y apilar el resultado
	cmp eax, edx
	jg near mayor20
	push dword 0
	jmp near fin_mayor20

mayor20:
	push dword 1

fin_mayor20:
;escribir_operando
	push dword _y
; numero_linea 49
	push dword 0
; menor
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
	mov dword eax , [eax]
; comparar y apilar el resultado
	cmp eax, edx
	jl near menor21
	push dword 0
	jmp near fin_menor21

menor21:
	push dword 1

fin_menor21:
;y
; cargar el segundo operando en edx
	pop dword edx
; cargar el primer operando en eax
	pop dword eax
; realizar la conjunción y dejar el resultado en eax
	and eax , edx
; apilar el resultado
	push dword eax

	pop dword eax
	cmp eax, 0
	je near fin_si22
;escribir_operando
	push dword _z
; numero_linea 51
	push dword 0
; mayor
; cargar la segunda expresión en edx
	pop dword edx
; cargar la primera expresión en eax
	pop dword eax
	mov dword eax , [eax]
; comparar y apilar el resultado
	cmp eax, edx
	jg near mayor23
	push dword 0
	jmp near fin_mayor23

mayor23:
	push dword 1

fin_mayor23:

	pop dword eax
	cmp eax, 0
	je near fin_si24
; numero_linea 53
	push dword 4
; Acceso al valor de exp si es distinto de constante
	call print_int
	add esp, 4
	call print_endofline

	jmp near fin_sino24

fin_si24:
; numero_linea 57
	push dword 8
; Acceso al valor de exp si es distinto de constante
	call print_int
	add esp, 4
	call print_endofline

fin_sino24:

fin_si22:

fin_sino4:
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
