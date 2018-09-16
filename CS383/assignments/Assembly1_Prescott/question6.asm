;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  Author: Kaitlynn Prescott						;;
;;  Assignment: Assembly1						;;
;;  File: question6.asm							;;
;;  Pledge: I pledge my honor that I have abided by			;;
;;          the Stevens Honor System.					;;
;;  Date: 24 Oct 2017							;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 6. Write an assembly language program to do the following: get the	;;
;; number N from Data Space at 0x0100, add all numbers in [1, N],	;;
;; Output the lower byte of the result to Port B and the high byte of	;;
;; the result to Port C. (use register z to get number)			;;
;; (For example: if N is 5, do the adding 1+2+3+4+5) (Points 20)	;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.include "m328Pdef.inc"
init: // defining variables
	.def maxNum = r16
	.def lowSum = r17
	.def highSum = r18
	.def count = r19
main: // loading variables
	ldi count, 1
	ldi zh, 0x01
	ldi zl, 0x00
	ldi r30, 0
	ld maxNum, z
	inc maxNum
	clr lowSum
	clr highSum
loop:
	cpc count, maxNum // compare count to maxNum
	brge end // if count >= maxNum, skip to end of program
	add lowSum, count // add count the sums
	adc highSum, r30 
	inc count // increase the count
	rjmp loop
end: // return results and end program
	out PortB, lowSum
	out PortC, highSum
	ret
