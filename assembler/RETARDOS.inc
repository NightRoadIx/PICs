;******************************************************************
;Secuencias de Retardo RETARDOS.INC
;******************************************************************

;Definir contadores para los retardos
	CBLOCK
		R_ContA
		R_ContB
		R_ContC
	ENDC

;**********************Retardos microsegundos**********************
;Secuencia de retardo de 500 micros
Retardo_500micros
	nop				
	movlw d'164'			
	goto RetardoMicros		
;Secuencia de retardo de 200 micros
Retardo_200micros
	nop
	movlw d'64'						;1 ciclo máquina y da valor a "k"
	goto RetardoMicros				;2 ciclos mas
;Secuencia de retardo de 50 micros
Retardo_50micros
	nop
	movlw d'14'						;1 ciclo
	goto RetardoMicros
;Secuencia de retardo de 20 micros
Retardo_20micros
	movlw d'5'						;1 ciclo mas
RetardoMicros
	movwf R_ContA					;1 ciclo
Rmicros_Bucle
	decfsz R_ContA,F				;(k-1)x1 ciclos (cuando no sslta) + 2 ciclos (al saltar)
	goto Rmicros_Bucle				;Aporta (k-1)x2 ciclos
	RETURN							;Aporta 2 ciclos
;Secuencia de Retardo de 10 micros
Retardo_10micros					;Call aporta 2 ciclos 
	nop								;nop aporta 1 ciclo
	nop
	nop
	nop
	nop
;Secuencia de retardo de 5 micros
Retardo_5micros
	nop
;Secuencia de retardo de 4 micros
Retardo_4micros
	return				;2 ciclos

;***********************Retardos milisegundos**********************
;Secuencia de retardo de 200 milisegundos
Retardo_200ms
	movlw d'200'					;Este es el valor de "M"
	goto Retardos_ms
;Secuencia de retardo de 100 milisegundos
Retardo_100ms
	movlw d'100'					;Este es el valor de "M"
	goto Retardos_ms
;Secuencia de retardo de 50 milisegundos
Retardo_50ms
	movlw d'50'						;Este es el valor de "M"
	goto Retardos_ms
;Secuencia de retardo de 20 milisegundos
Retardo_20ms
	movlw d'20'						;Este es el valor de "M"
	goto Retardos_ms
;Secuencia de retardo de 10 milisegundos
Retardo_10ms
	movlw d'10'						;Este es el valor de "M"
	goto Retardos_ms
;Secuencia de retardo de 5 milisegundos
Retardo_5ms
	movlw d'5'
	goto Retardos_ms
;Secuencia de retardo de 2 milisegundos
Retardo_2ms
	movlw d'2'
	goto Retardos_ms
;Secuencia de retardo de 1 milisegundos
Retardo_1ms
	movlw d'1'

Retardos_ms
	movwf R_ContB
R1ms_BucleExterno
	movlw d'249'					;Valor de "k", aporta Mx1 ciclos
	movwf R_ContA					;Aporta Mx1 ciclos máquina
R1ms_BucleInterno
	nop								;Aporta kxMx1 ciclos
	decfsz R_ContA,F				;(k-1)xMx1 ciclos (cuando no salta) + Mx2 ciclos (al saltar)
	goto R1ms_BucleInterno			;Aporta (k-1)xMx2 ciclos
	decfsz R_ContB,F				;(M-1)x1 ciclos (cuando no salta) + 2 ciclos (al saltar)
	goto R1ms_BucleExterno			;Aporta (M-1)x2 ciclos
	return							;2 ciclos mas

;*************************Retardos segundos************************
;Secuencia de retardo de 20 segundos
Retardo_20s							; La llamada "call" aporta 2 ciclos máquina
	movlw	d'200'					; Aporta 1 ciclo máquina. Este es el valor de "N"
	goto	Retardo_1Decima			; Aporta 2 ciclos máquina
;Secuencia de retardo de 10 segundos
Retardo_10s					
	movlw	d'100'					; Aporta 1 ciclo máquina. Este es el valor de "N"
	goto	Retardo_1Decima			; Aporta 2 ciclos máquina
;Secuencia de retardo de 5 segundos
Retardo_5s					
	movlw	d'50'					; Aporta 1 ciclo máquina. Este es el valor de "N"
	goto	Retardo_1Decima			; Aporta 2 ciclos máquina
;Secuencia de retardo de 2 segundos
Retardo_2s					
	movlw	d'20'					; Aporta 1 ciclo máquina. Este es el valor de "N"
	goto	Retardo_1Decima			; Aporta 2 ciclos máquina
;Secuencia de retardo de 1 segundo
Retardo_1s					
	movlw	d'10'					; Aporta 1 ciclo máquina. Este es el valor de "N"
	goto	Retardo_1Decima			; Aporta 2 ciclos máquina
;Secuencia de retardo de 1/2 segundo
Retardo_500ms				
	movlw	d'5'					; Aporta 1 ciclo máquina. Este es el valor de "N"

;Secuencia de retardo de 1 decima de segundo para los ciclos de N segundos
Retardo_1Decima
	movwf	R_ContC					; Aporta 1 ciclo máquina
R1Decima_BucleExterno2
	movlw	d'100'					; Aporta Nx1 ciclos máquina. Este es el valor de "M"
	movwf	R_ContB					; Aporta Nx1 ciclos máquina
R1Decima_BucleExterno
	movlw	d'249'					; Aporta MxNx1 ciclos máquina. Este es el valor de "K"
	movwf	R_ContA					; Aporta MxNx1 ciclos máquina
R1Decima_BucleInterno          
	nop								; Aporta KxMxNx1 ciclos máquina
	decfsz	R_ContA,F				; (K-1)xMxNx1 cm (si no salta) + MxNx2 cm (al saltar)
	goto	R1Decima_BucleInterno	; Aporta (K-1)xMxNx2 ciclos máquina
	decfsz	R_ContB,F				; (M-1)xNx1 cm (cuando no salta) + Nx2 cm (al saltar)
	goto	R1Decima_BucleExterno	; Aporta (M-1)xNx2 ciclos máquina
	decfsz	R_ContC,F				; (N-1)x1 cm (cuando no salta) + 2 cm (al saltar)
	goto	R1Decima_BucleExterno2	; Aporta (N-1)x2 ciclos máquina
	return							; El salto del retorno aporta 2 cic
