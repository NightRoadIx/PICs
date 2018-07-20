;***********************************************************
;LCD_4BIT.INC libreria para el control del LCD usando 4 bits
;***********************************************************
;Define a Constant Block
	CBLOCK
		LCD_Dato
		LCD_GuardaDato
		LCD_GuardaTRISB
		LCD_Auxiliar1
		LCD_Auxiliar2
	ENDC

;definiciones para utilizar
#define LCD_PinRS PORTA,0
#define LCD_PinRW PORTA,1
#define LCD_PinE PORTA,2
#define LCD_BusDatos PORTB

;Rutina para la Inicialización del LCD
LCD_INICIALIZA
	;Apagar los registros de PORTA0,1,2
	bsf STATUS,RP0
	;Lectura/Escritura y habilitar
	bcf LCD_PinRS
	;Inhabilita el LCD
	bcf LCD_PinE
	bcf LCD_PinRW
	;Apagar los registros de PORTA0,1,2
	bcf STATUS,RP0
	;Indica que se va a escribir en el LCD
	bcf LCD_PinRW
	bcf LCD_PinE
	;Coloca RS a cero para Modo Comando
	bcf LCD_PinRS
	call Retardo_20ms
	movlw b'00110000'
	;Escribe el dato en el LCD
	call LCD_EscribeLCD
	call Retardo_5ms
	movlw b'00110000'

	call LCD_Envia
	call Retardo_200micros
	movlw b'00110000'
	call LCD_EscribeLCD
	call Retardo_20micros
	;Intefase de 4 bits
	movlw b'00100000'
	call LCD_EscribeLCD
	call Retardo_20micros
	;LCD de 2 lineas y 5x7 pts
	call LCD_2Lineas4bits5x7
	;Pantalla limpia
	call LCD_Borra
	;Apagar Cursor
	call LCD_OFF
	;Cursor en Modo Incrementar
	call LCD_CursorIncr
	RETURN

;Rutina para escribir en el LCD de 4 bits realizando un enmascaramiento
LCD_EscribeLCD
	;Nibble superior
	andlw b'11110000'
	movwf LCD_Dato
	movf LCD_BusDatos,W
	;Nibble inferior
	andlw b'00001111'
	iorwf LCD_Dato,F
	;Accesar al banco de memoria 1
	bsf STATUS,RP0
	;Guardar configuración de TRISB
	movf TRISB,W
	movwf LCD_GuardaTRISB
	;Mover las 4 lineas superiores como salida, las inferiores quedan como entrada
	movlw b'00001111'
	andwf PORTB,F
	;Acceso al banco de memoria 0
	bcf STATUS,RP0
	;Recupera el dato a enviar
	movf LCD_Dato,W
	;Envia el dato al bsus del LCD
	movwf LCD_BusDatos
	;Permite envio de datos
	bsf LCD_PinE
	;Accesar al banco 1
	bsf STATUS,RP0
	movf LCD_GuardaTRISB,W
	movwf TRISB
	bcf	STATUS,RP0
	RETURN

;Rutina para desplegar el cursor en modo incrementar
LCD_CursorIncr
	movlw b'00000110'
	goto LCD_EnviaComando
;Rutna para colocar el cursor en la línea 1
LCD_Linea1				
	movlw	b'10000000'		
	goto	LCD_EnviaComando
;Rutna para colocar el cursor en la línea 1
LCD_Linea2				
	movlw	b'11000000'		
	goto	LCD_EnviaComando
;Rutina para colocar el cursor en la línea 1
LCD_PosicionLinea1			
	iorlw	b'10000000'		
	goto	LCD_EnviaComando
;Rutina para colocar el cursor en la línea 1	
LCD_PosicionLinea2			
	iorlw	b'11000000'		
	goto	LCD_EnviaComando	
;Rutina para apagar el display del LCD
LCD_OFF
	movlw b'00001100'
	goto LCD_EnviaComando
;Rutina para encender la pantalla con el cursor
LCD_CursorON				
	movlw	b'00001110'
	goto	LCD_EnviaComando
;Rutina para encender la pantalla sin el cursor
LCD_CursorOFF				
	movlw	b'00001100'
	goto	LCD_EnviaComando
;Rutina para borrar el LCD
LCD_Borra
	movlw b'00000001'
;Rutina para colocar el LCD a 2 lineas 8 bits 5x7
LCD_2Lineas4bits5x7
	movlw b'00101000'
	goto LCD_EnviaComando

;Rutina para enviar el comando que se escribio con anterioridad al PORTA
LCD_EnviaComando
	bcf LCD_PinRS
	goto LCD_Envia
;Rutina para la correcta visualización
LCD_Caracter
	;Activa el modo dato
	bsf LCD_PinRS
	call LCD_CodigoCGROM
;Rutina para enviar información al LCD
LCD_Envia
	;Guarda el dato a enviar
	movwf LCD_GuardaDato
	;Mandar nibble alto
	call LCD_EscribeLCD
	;Movilizar el nibble bajo
	swapf LCD_GuardaDato,W
	;Aqui se manda ese nibble bajo
	call LCD_EscribeLCD
	btfss LCD_PinRS
	call Retardo_2ms
	call Retardo_50micros
	RETURN

;Comprobar los caracteres especiales
LCD_CodigoCGROM
	movwf LCD_Dato
;Código para la "ñ"
LCD_EnheMinuscula
	sublw 'ñ'
	btfss STATUS,Z
	goto LCD_EnheMayuscula
	;Código ñ
	movlw b'11101110'
;Código para la "Ñ"
LCD_EnheMayuscula
	sublw 'Ñ'
	btfss STATUS,Z
	goto LCD_Grado
	;Código Ñ
	movlw b'11101110'
	movwf LCD_Dato
	goto LCD_FinCGROM
;Código para la "°"
LCD_Grado
	movf LCD_Dato,W
	sublw '°'
	btfss STATUS,Z
	goto LCD_FinCGROM
	;Código °
	movlw b'110111'
	movwf LCD_Dato
LCD_FinCGROM
	movf LCD_Dato,W
	RETURN

; Subrutinas "LCD_ByteCompleto" y "LCD_Byte" --------------------------------------------
;
; Subrutina "LCD_ByteCompleto", visualiza el byte que almacena el registro W en el
; lugar actual de la pantalla. Por ejemplo, si (W)=b'10101110' visualiza "AE".
;
; Subrutina "LCD_Byte" igual que la anterior, pero en caso de que el nibble alto sea cero 
; visualiza en su lugar un espacio en blanco. Por ejemplo si (W)=b'10101110' visualiza "AE"
; y si (W)=b'00001110', visualiza " E" (un espacio blanco delante).
;
; Utilizan la subrutina "LCD_Nibble" que se analiza más adelante.
;
LCD_Byte
	movwf	LCD_Auxiliar2		; Guarda el valor de entrada.
	andlw	b'11110000'		; Analiza si el nibble alto es cero.
	btfss	STATUS,Z		; Si es cero lo apaga.
	goto	LCD_VisualizaAlto		; No es cero y lo visualiza.
	movlw	' '			; Visualiza un espacio en blanco.
	call	LCD_Caracter
	goto	LCD_VisualizaBajo

LCD_ByteCompleto
	movwf	LCD_Auxiliar2		; Guarda el valor de entrada.
LCD_VisualizaAlto
	swapf	LCD_Auxiliar2,W		; Pone el nibble alto en la parte baja.
	call	LCD_Nibble		; Lo visualiza.
LCD_VisualizaBajo
	movf	LCD_Auxiliar2,W		; Repite el proceso con el nibble bajo.
;	call	LCD_Nibble		; Lo visualiza.
;	return

; Subrutina "LCD_Nibble" ----------------------------------------------------------------
;
; Visualiza en el lugar actual de la pantalla, el valor hexadecimal que almacena en el nibble
; bajo del registro W. El nibble alto de W no es tenido en cuenta. Ejemplos:
; - Si (W)=b'01010110', se visualizará "6". 
; - Si (W)=b'10101110', se visualizará "E". 
;
LCD_Nibble
	andlw	b'00001111'		; Se queda con la parte baja.
	movwf	LCD_Auxiliar1		; Lo guarda.
	sublw	0x09			; Comprueba si hay que representarlo con letra.
	btfss	STATUS,C	
	goto	LCD_EnviaByteLetra
	movf	LCD_Auxiliar1,W
	addlw	'0'			; El número se pasa a carácter ASCII sumándole
	goto 	LCD_FinVisualizaDigito	; el ASCII del cero y lo visualiza.
LCD_EnviaByteLetra
	movf	LCD_Auxiliar1,W
	addlw	'A'-0x0A			; Sí, por tanto, se le suma el ASCII de la 'A'.
LCD_FinVisualizaDigito
	goto	LCD_Caracter		; Y visualiza el carácter. Se hace con un "goto"
					; para no sobrecargar la pila.
