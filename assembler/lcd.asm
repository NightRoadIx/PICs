;Programa para LCD
	LIST P=16F84A
	INCLUDE <P16F84A.INC>
	__CONFIG _CP_OFF & _WDT_OFF & _PWRTE_ON & _XT_OSC
	CBLOCK 0x0C
	ENDC

;Organizar a partir de 00
	ORG 00
Inicio
	Call LCD_INICIALIZA
	movlw 'H'
	call LCD_Caracter
	movlw '0'
	call LCD_Caracter
	movlw '1'
	call LCD_Caracter
	movlw 'a'
	call LCD_Caracter
	Sleep
	;Llamar a las librerias
	;INCLUDE <LCD_8BIT.inc>
	INCLUDE <LCD_4BIT3.inc>
	INCLUDE <RETARDOS.inc>
	END
