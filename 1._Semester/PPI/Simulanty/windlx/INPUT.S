;*********** WINDLX Bsp.1: Einlesen eines positiven Integerwerts *************
;*********** (c) 1991 Günther Raidl                              *************

;-----------------------------------------------------------------------------
;Unterprogrammaufruf bei Symbol InputUnsigned
;Erwartet in R1 die Adresse eines mit 0 abgeschlossenen Prompt-Strings
;Liefert in R1 den eingelesenen, positiven Integerwert zurueck.
;Veraendert die Register R1, R13, R14
;-----------------------------------------------------------------------------

		.data

		;*** Daten für Read-Trap
ReadBuffer:	.space		80
ReadPar:	.word		0,ReadBuffer,80

		;*** Daten für Printf-Trap
PrintfPar:	.space		4

SaveR2:		.space		4
SaveR3:		.space		4
SaveR4:		.space		4
SaveR5:		.space		4


		.text

		.global		InputUnsigned
InputUnsigned:	
		;*** Registerwerte sichern
		sw		SaveR2,r2
		sw		SaveR3,r3
		sw		SaveR4,r4
		sw		SaveR5,r5

		;*** Prompt ausgeben
		sw		PrintfPar,r1
		addi		r14,r0,PrintfPar
		trap		5

		;*** Trap-3 zum Einlesen einer Zeile aufrufen
		addi		r14,r0,ReadPar
		trap		3

		;*** Zahl ermitteln
		addi		r2,r0,ReadBuffer
		addi		r1,r0,0
		addi		r4,r0,10	;Dezimalsystem

Loop:		;*** Bis das Zeilenende erkannt wird Zeichen als Ziffern beh.
		lbu		r3,0(r2)
		seqi		r5,r3,10	;LF -> Exit
		bnez		r5,Finish
		subi		r3,r3,48	;´0´
		multu		r1,r1,r4	;Shift um eine Dezimalstelle
		add		r1,r1,r3	;Neue Einerstelle hinzu
		addi		r2,r2,1		;Zeichenpointer inkrementieren
		j		Loop
		
Finish:		;*** Alte Registerwerte laden und zurueck
		lw		r2,SaveR2
		lw		r3,SaveR3
		lw		r4,SaveR4
		lw		r5,SaveR5
		jr		r31		; Return
		