
;escribir_subseccion_data
segment .data
	msj_error_div_0 db "Division por cero", 0
	msj_error_ind_fuera_rango db "Indice fuera de rango", 0
;escribir_cabecera_bss
segment .bss
	__esp resd 1
;declarar_variable
	_ resd 1
