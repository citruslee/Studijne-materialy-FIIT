;*********** WINDLX Bsp.3: Faktoriellenberechnung *************
;*********** (c) 1991 Günther Raidl               *************

;--------------------------------------------------------------------------
; Programmanfang bei Symbol main
; Benötigt Modul INPUT
; Liest eine Zahl von stdin ein und berechnet im Typ double die Faktorielle
; Abschließend wird das Ergebnis ausgegeben
;--------------------------------------------------------------------------

		.data
Prompt:		.asciiz		"Ein ganzzahliger Wert >1 : "

PrintfFormat:	.asciiz		"Die Faktorielle = %g\n\n"
		.align		2
PrintfPar:	.word		PrintfFormat
PrintfValue:	.space		8


		.text
		.global	main
main:
		;*** Wert von stdin in R1 einlesen
		addi		r1,r0,Prompt
		jal		InputUnsigned
		
		;*** Werte initialisieren
		movi2fp		f10,r1		;R1 -> D0	D0..Zählregister
		cvti2d		f0,f10
		addi		r2,r0,1		;1 -> D2	D2..Ergebnis
		movi2fp		f11,r2
		cvti2d		f2,f11
		movd		f4,f2		;1-> D4		D4..Konstante 1
		
		;*** Berechnungsschleife abbrechen, wenn D0 1 erreicht
Loop:		led		f0,f4		;D0<=1 ?
		bfpt		Finish
		
		;*** Multiplikation durchführen und nächster Schleifendurchgang
		multd		f2,f2,f0
		subd		f0,f0,f4
		j		Loop

Finish:		;*** Ergebnis ausgeben
		sd		PrintfValue,f2
		addi		r14,r0,PrintfPar
		trap		5
				
		;*** Programmende
		trap		0
		
		
