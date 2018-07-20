;*************************************************************
;Mensaje en movimiento
;*************************************************************
	LIST 		P=16F84A
	#INCLUDE 	<P16F84A.INC>
	__CONFIG   _CP_OFF &  _WDT_OFF & _PWRTE_ON & _XT_OSC

	CBLOCK 0x0C
	ENDC
	
;Organizar a partir de 00
	ORG 0
Inicio
	call LCD_INICIALIZA			;Inicia la LCD
Principal
	movlw Mensajes0				;Mover mensajes0
	call LCD_MensajeMovimiento	;Llamar a MensajeMovimiento
	goto Principal				;Regresar a Principal para repetir
Mensajes
	addwf PCL,F					;
;Aqui se colocan los mensajes
Mensajes0
	DT "                "
	DT "Cámara Cirio"
	DT "YA VAMONOS!!!"
	DT "                "
	
; -*****-Librerias a incluir-*****-
	INCLUDE <LCD_MENS.INC>
	INCLUDE <LCD_4BIT.INC>
	INCLUDE <RETARDOS.INC>
	END
