;**********************pendulo.asm****************************
;
;				SIMULADOR DE UN PENDULO
;
;El programa simula el movimiento de un péndulo colgado a una 
;cuerda de 4 m de longitud, el péndulo pesa 20 kg, se 
;desprecian los efectos de la fricción sobre el cuerpo
;
; Optimizado para PIC16F84
;*************************************************************
;ORGanizar datos a partir de la dirección 040H
ORG 040H
;Inicia Programa
Inicio:
	;Mueve un 128 al acumulador, pone el primer led encendido
	MOV A,#80H
	;Lo saca por el puerto 1
	MOV P1,A
;*************************************************************
;Secuencia de Retardo
Retardo: MOV R0,#03EH
UNO:   	MOV R1,#03BH
DOS:  	MOV R2,#03DH
CYCL:
	DJNZ R2,CYCL
	DJNZ R1,DOS
	DJNZ R0,UNO
;*************************************************************
;Secuencia a la derecha
Der:
	RR A
	MOV P1,A
	CJNE A,#01H,Retardo
;*************************************************************
;Segunda Secuencia de Retardo
Retardob: MOV R0,#03EH
UNOb:     MOV R1,#03BH
DOSb:  	 MOV R2,#03DH
CYCLb:
	DJNZ R2,CYCLb
	DJNZ R1,DOSb
	DJNZ R0,UNOb
;Secuencia a la izquierda
Izq:
	RL A
	MOV P1,A
	CJNE A,#80H,Retardob
	ACALL Inicio ;Ciclo infinito
END
;FIN DE CODIGO
