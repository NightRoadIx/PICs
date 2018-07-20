;*************************************************************
;Libreria LCD_MENS.INC
;*************************************************************
;Caracteres a visualizar
	CBLOCK
	LCD_ApuntaCaracter				;Indica la posición del caracter a visualizar
	LCD_ValorCaracter				;Código ASCII del caracter
	ENDC

;Para mostrar el mensaje en el LCD
LCD_Mensaje
	movwf LCD_ApuntaCaracter		;Primer caracter del mensaje
	movlw Mensajes					;Halla la posición relativa del caracter con respecto a
	subwf LCD_ApuntaCaracter,F		;Mensajes
	decf LCD_ApuntaCaracter,F
;El siguiente realiza lo mismo que el anterior pero:
LCD_VisualizaOtroCaracter
	movf LCD_ApuntaCaracter,W
	call Mensajes					;Obtener valor ASCII del caracter
	movwf LCD_ValorCaracter			;Guardar el valor
	movf LCD_ValorCaracter,F		;Posiciona "Z", 
	btfsc STATUS,Z					;En caso de ser 0x00
	goto LCD_FinMensaje				;Sale del programa
;Moverse dentro de los caracteres del mensaje
LCD_NoUltimoCaracter
	call LCD_Caracter
	incf LCD_ApuntaCaracter,F
	goto LCD_VisualizaOtroCaracter
;Volver al principal
LCD_FinMensaje
	return

;Subrutina de movimiento para poder visualizar los caracteres
	CBLOCK
		LCD_CursorPosicion			;Posición del cursor
		LCD_CaracterPorLinea
	ENDC

;Para emular el mensaje en movimiento
LCD_MensajeMovimiento
	movwf LCD_ApuntaCaracter
	movwf Mensajes
	subwf LCD_ApuntaCaracter,F
	decf LCD_ApuntaCaracter,F
;Coloca el cursor en la primera posición del LCD y la borra
LCD_PrimeraPosicion
	clrf LCD_CursorPosicion
	call LCD_Borra
;Ver el caracter
LCD_VisualizaCaracter
	movlw LCD_CaracterPorLinea
	subwf LCD_CursorPosicion,W
	btfss STATUS,Z
	goto LCD_NoEsFinalLinea
;Cuando ya es final de linea
LCD_EsFinalLinea
	call Retardo_200ms				;Mantiene el caracter por este retardo
	call Retardo_200ms
	movlw LCD_CaracterPorLinea-1	;Ir al segundo caracter visualizado
	subwf LCD_ApuntaCaracter,F		;así parece que se "mueve"
	goto LCD_PrimeraPosicion
;Cuando no es final de linea
LCD_NoEsFinalLinea
	movf LCD_ApuntaCaracter,W
	call Mensajes
	movwf LCD_ValorCaracter
	movf LCD_ValorCaracter,F
	btfsc STATUS,Z
	goto LCD_FinMovimiento
;Cuando no es aun el último caracter
LCD_NoUltimoCaracter2
	call LCD_Caracter				;Ver el caracter
	incf LCD_CursorPosicion,F		;Contador del cursor en la LCD
	incf LCD_ApuntaCaracter,F		;Va al siguiente caracter
	goto LCD_VisualizaCaracter		;Se muestra el siguiete caracter
;Cuando todo termina regresa a principal
LCD_FinMovimiento
	return
