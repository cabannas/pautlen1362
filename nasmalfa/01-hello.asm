; Hello World Program NSAM (Usando alfalib.o)
segment .data
  _msg db 'Hello World!', 0 ; Constante de cadena
	
segment .bss
  __esp    resd 1
	
segment .text
  global main
  extern print_endofline, print_string
  _init :
    mov dword [__esp] , esp ; Guarda el puntero de la pila
    ret
  _quit :
    mov dword esp, [__esp]  ; Restauración de puntero de pila
    ret

  main:
    call _init
    push dword _msg  ; Mover de memoria a dword
    call print_string
    add esp, 4	
    call print_endofline
    call _quit
    ret
   