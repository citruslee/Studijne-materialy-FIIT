;
;---- Angabe zur Übung aus Rechnerarchitektur SS 97 ----
;---- Pipeline-Simulation WinDLX 		    ----
;---- Beispiel					    ----
;---- Reihenentwicklung für Logarithmus		    ----
;---- ln(1+x) = x - (x^2)/2 + (x^3)/3 - (x^4)/4 + ... - (x^12)/12 ----
;
; C-Code:
;	main()
;	{
;	  float x, res;
;	  int i, sign;
;
;	    x = 0.56;
;	    res = x / 12;
;	    sign = 1;
;
;	    for (i = 11; i > 0; i--)
;	    {
;		res = (res + sign * 1/i) * x;
;		sign = -sign;
;	    }
;	}
;

	.data

	.global i
i:	.word 0
	.global x
x:	.double 0.56
	.global res
res:	.word 0
	.global sign
sign:	.double -1
	.align 4

	.text

	.global main
main:

;-- res = -(x/12);

	addi r12,r0,#12
	movi2fp f0,r12
	cvti2d f4,f0
	ld f2,x
	divd f2,f2,f4

	ld f10,sign
	multd f2,f2,f10

	multd f8,f10,f10

;-- Schleife Index

	addi r10,r0,#11
	sw i, r10

L2:	lw r10,i
	bnez r10, L3
	nop
	beqz r10,L1
	nop

L3:	

;-- sign * 1 /i

	addi r11,r0,#1
	movi2fp f4,r11
	cvti2d f0,f4
	movi2fp f6,r10
	cvti2d f10,f6
	divd f4,f0,f10
	multd f10,f4,f8

;-- res + sign * 1/i

	addd f2,f2,f10

;-- (res + sign * 1/i) * x

	ld f4,x
	multd f2,f2,f4

;-- sign = -sign

	ld f10, sign
	multd f8,f8,f10

;-- i--

	subi r10,r10,#1
	sw i,r10
	j L2
	nop

L1:	sd res,f2
	trap #0
	nop