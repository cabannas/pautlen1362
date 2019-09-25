; Hello World Program NSAM
%include '01-library.asm'

segment .data
  _msg db 'Hello World!', 0Ah     ; Constante de cadena
 
segment .text
  global  main

    _hello_world: 	
      mov edx, 13     ; Número de bytes a escribir
      mov ecx, _msg   ; Mover de memoria a ecx
      mov ebx, 1      ; Escribir a STDOUT
      mov eax, 4      ; Invocar SYS_WRITE
      int        80h
      ret
	
	main:
      call _hello_world
      call _quit