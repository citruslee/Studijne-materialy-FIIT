;
;---- Angabe zur Übung aus Rechnerarchitektur SS 97 ----
;---- Pipeline-Simulation WinDLX 		    ----
;---- Beispiel					    ----
;---- Reihenentwicklung für Sinus		    ----
;---- sin(x) = x^1/1! - (x^3)/3! + (x^5)/5! - ... - (x^11)/11! ----
;
; C-Code:
;	main()
;	{
;	  float x, res;
;	  int i, sign;
;	  int w[6] = [1,6,120,5040,362880,39916800];
;
;	    x = 0.56;
;	    res = -(x * x / w[5]);
;	    sign = 1;
;
;	    for (i = 5; i > 0; i--)
;	    {
;		res = (res + sign * 1/w[i-1]) * x * x;
;		sign = -sign;
;	    }
;	    res = res / x;
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
	.global w
w:	.double 1,6,120,5040,362880,39916800
	.align 4

	.text

	.global main
main:

;-- res = -(x**2/ w[5]);

	addi r12,r0,#5
	sll r12,r12,#3
	ld f0,w(r12)
	ld f2,x
	multd f4,f2,f2
	divd f2,f4,f0

	ld f10,sign
	multd f2,f2,f10

	multd f8,f10,f10

;-- Schleife Index

	addi r10,r0,#5
	sw i, r10

L2:	lw r10,i
	bnez r10, L3
	nop
	beqz r10,L1
	nop

L3:	

;-- sign * 1 / w[i-1]

	addi r11,r0,#1
	movi2fp f4,r11
	cvti2d f0,f4
	subi r12,r10,#1
	sll r12,r12,#3
	ld f10,w(r12)
	divd f4,f0,f10
	multd f10,f4,f8

;-- res + sign * 1/ w[i]

	addd f2,f2,f10

;-- (res + sign * 1/w[i]) * x * x

	ld f4,x
	multd f2,f2,f4
	multd f2,f2,f4

;-- sign = -sign

	ld f10, sign
	multd f8,f8,f10

;-- i--

	subi r10,r10,#1
	sw i,r10
	j L2
	nop

L1:	ld f4,x
	divd f2,f2,f4
	sd res,f2
	trap #0
	nop