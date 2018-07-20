;******************************************************************
;Libreria TMATRIX2.INC
;Incluye todo lo necesario para el manajeo de un teclado matricial
;o un arreglo de botones matricial de 3x3, conectado a PORTB
;******************************************************************
;**ZONA DE DATOS**
	CBLOCK
		Tecl_TeclaOrden			;Orden de la tecla
		Tecl_UltimaTecla
	ENDC

;**ZONA DE SUBRUTINAS**
Teclado_LeeHex
	call Teclado_LeeOrden		;lee la tecla
	btfss STATUS,C				;revisa
	goto Tecl_FinLeeHex			;Si no se va a Fin de lectura
	call Tecl_ConvierteOrdenHex	;Lo convierte
	bsf STATUS,C
Tecl_FinLeeHex
	return

;*****************************************
;Configurar el tipo de teclado o arreglo matricial
Tecl_ConvierteOrdenHex
	addwf PCL,F
	;Aqui se colocan las filas del teclado (3 x 3)
	DT 1h,2h,3h,0Fh
	DT 4h,5h,6h,0Eh
	DT 7h,8h,9h,0Dh
	DT 0Ah,0h,0BH,0Ch
;Cuando ya es demasiado grande
Teclado_FinTablaHex
	IF(Teclado_FinTablaHex > 0xFF)
		ERROR"Se supero el tamaño de los"
		MESSG"256 bytes de la ROM. Funcionamiento Incorrecto"
	ENDIF
;Para inciar al teclado
Teclado_Inicializa
	bsf STATUS,RP0					;poner 1 en STATUS
	movlw b'11110000'				;<RB7:RB4> entradas, <RB3:RB0> salidas
	movwf PORTB						;manda orden a PORTB	
	bcf OPTION_REG,NOT_RBPU			;Habilitar las resistencias Pull-Up
	bcf STATUS,RP0					;Ahora limpia el STATUS
;Aqui se queda mientras una tecla este pulsada
Teclado_Comprobacion EQU b'11110000'
Teclado_EspereDejePulsar:
	movlw Teclado_Comprobacion		
	movwf PORTB
Teclado_SigueEsperando
	call Retardo_20ms
	movf PORTB,W
	sublw Teclado_Comprobacion
	btfss STATUS,Z
	goto Teclado_SigueEsperando
	return
;Lee la tecla y obtiene el orden de la misma
Teclado_LeeOrden:
	clrf Tecl_TeclaOrden
	movlw b'11111110'
;Luego checar filas y columnas
Tecl_ChequeoFila
	movwf PORTB						;Acitva la fila que va a checarse
	call Retardo_1ms
;Busca un cero para guardar su valor
;Y sigue checando
Tecl_Columna1
	btfss PORTB,4
	goto Tecl_GuardaValor
	incf Tecl_TeclaOrden,F
Tecl_Columna2
	btfss PORTB,5
	goto Tecl_GuardaValor
	incf Tecl_TeclaOrden,F
Tecl_Columna3
	btfss PORTB,6
	goto Tecl_GuardaValor
	incf Tecl_TeclaOrden,F
Tecl_Columna4
	btfss PORTB,7
	goto Tecl_GuardaValor
	incf Tecl_TeclaOrden,F
;Al temrinar de revisar las teclas
Tecl_TerminaColumnas
	movlw Tecl_UltimaTecla
	subwf Tecl_TeclaOrden,W
	btfsc STATUS,C
	goto Tecl_NoPulsada
	bsf STATUS,C
	rlf PORTB,W
	goto Tecl_ChequeoFila
;Cuando no se ha detectado nada en el teclado
Tecl_NoPulsada
	bcf STATUS,C
	goto Tecl_FinTecladoLee
;Cuando se pulsa una tecla se guarda el valor
Tecl_GuardaValor
	movf Tecl_TeclaOrden,W
	bsf STATUS,C
Tecl_FinTecladoLee
	return
