;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  Author: Kaitlynn Prescott						;;
;;  Assignment: Assembly1						;;
;;  File: question4.asm							;;
;;  Pledge: I pledge my honor that I have abided by			;;
;;          the Stevens Honor System.					;;
;;  Date: 24 Oct 2017							;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 4. Write an assembly language program to add any 15 binary numbers.	;; 
;; Get the numbers from the Data Space starts from 0x0100. Output the	;;
;; lower byte of the result to Port B and the high byte of the result	;;
;; to Port C. (use register z to get number). (Points 15)		;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.include "m328Pdef.inc"
init: // define variables
	.def maxNum = r16
	.def lowSum = r17
	.def highSum = r18
	.def count = r19
main: // load variables
	ldi maxNum, 15
	ldi count, 0
	ldi zh, 0x01
	ldi zl, 0x00
	ldi lowSum, 0
	ldi highSum, 0
	ldi r23, 0
loop:
	cpc count, maxNum // compare the count to the bound
	brge end // if count >= maxNum, skip to end of program
	ld r22, z+
	add lowSum, r22 // add the low byte to the lowSum
	adc highSum, r23 // add the high byte to the highSum
	inc count // increase count
	rjmp loop
end: // return results and end program
	out PortB, lowSum
	out PortC, highSum
	ret
