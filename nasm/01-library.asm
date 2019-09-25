; Manejo de librerías
	_quit :
		mov     ebx,  0      ; Devolver Status 0 para salir sin errores
		mov     eax,  1      ; Invocar SYS_EXIT
		int        80h
		ret