; **************************************************************************
; Prueba del retardo 
; **************************************************************************

; Datos 
; Mover valores a diferentes espacios en memoria
MOV 0030H,#07H
MOV 0031H,#03H
MOV 0032H,#20H
MOV 0033H,#0AH
MOV 0034H,#20H
MOV 0035H,#20H
MOV 0036H,#20H
MOV 0037H,#10H

;ORG 01H
RESET: SJMP Inicio

;ORG 10H
Inicio:
	MOV P1,#00H
	MOV DPTR,#0030H
	MOV A,#01H
Ciclo:
	MOV A,P0
	ANL A,#07H
	MOVC A,@A+DPTR
	MOV P1,A
	ACALL Retardo
	SJMP Ciclo	
	
Retardo:
	mov r0,#01H
uno:
	mov r1,#01H
dos:
	mov r2,#01H
cycl:
	djnz r2,cycl
	djnz r1,dos
	djnz r0,uno
ret             
