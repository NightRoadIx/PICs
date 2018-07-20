;**************************************************************
;Serie.asm
;**************************************************************
RESET: 					;Al dar una interrupción
	SJMP Inicio
;**************************************************************
ORG 0023H
RxSerie:
	ACALL Serie_in		;Recepción por puerto serie
	RETI					;Regresar de una interrupción
;**************************************************************
Inicio:
	ACALL Conf_Serie	;Llamar a la configuración
	SJMP $				;Quedarse aqui un rato
;**************************************************************
Conf_Serie:
	CLR ES			;Poner ES a cero		
	MOV SCON,#50H	;UART Modo 1C
	MOV TMOD,#21H	;Timer 1 en autorecarga	
	MOV TH1,#0FDH 	;Valor del Timer para 9600 bps (High)
	MOV TL1,#0FDH	;(Low)
	SETB ES  		;Habilita interrupción serial
	SETB EA        ;Interrupción global
	SETB TR1			;Pone en marcha el T1 Bit de ctrl de arranque
	RET
;**************************************************************
Serie_in:
	MOV A,SBUF		;Mover de SBuf al Acumulador
	MOV B,A			;Pasar el valor a B
	;Rutina para sumar 10 a B
	MOV R1,#0AH		;Mueve 10 al registro 10
aum_10:
	INC B			;Incrementa B en 1
	DJNZ R1,aum_10		;Hasta que R1 llegue a cero
;**************************************************************
Txs:
	Mov SBUF,A 		;Ahora pasar del acumulador a SBuf
	JNB T1,$			;Salta aqui mismo si no esta habilitado el Timer1
	INC A				;Incrementa el Acumulador
	CJNE A,B,Txs	;Compara si no son iguales A y B
	CLR RI			;Limpia Ring Indicator
	RET
;**************************************************************
