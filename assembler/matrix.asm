;Programa para usar un teclado y el LCD
	__CONFIG _CP_OFF & _WDT_OFF & _PWRTE_ON & _XT_OSC
	LIST P=16F84A
	INCLUDE <P16F84A.INC>

	CBLOCK 0x0C
	ENDC

;Organizar a partir de 00h
	ORG 0
		goto Inicio
;Organizar a partir de 04h
	ORG 4
		goto Interrupcion

Inicio
	call LCD_INICIALIZA					;Inicia el LCD
	call Teclado_Inicializa				;Inicia el Teclado
	movlw b'10001000'					;Habilita la interrupción
	movwf INTCON
Principal
	sleep								;Lo pone a "dormir" para esperar tecla
	goto Principal

;Interrupcion
Interrupcion
	call Teclado_LeeHex					;Obtiene la tecla
	call LCD_Nibble
	call Teclado_EspereDejePulsar		;Esperar a que se deje de pulsar
	bcf	INTCON,RBIF						;Limpiar la flag
	retfie								;Regresar

	;Incluir estas cosas
	INCLUDE <TMATRIX2.INC>	
	INCLUDE <LCD_4BIT3.INC>
	INCLUDE <RETARDOS.INC>
	END
