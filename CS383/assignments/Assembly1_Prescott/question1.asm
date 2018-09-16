;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  Author: Kaitlynn Prescott						;;
;;  Assignment: Assembly1						;;
;;  File: question1.asm							;;
;;  Pledge: I pledge my honor that I have abided by			;;
;;          the Stevens Honor System.					;;
;;  Date: 24 Oct 2017							;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 1. Write an assembly language program to add up the numbers from	;;
;; 1 to 15 (inclusive) and output the result to Port B (Points 15)	;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
.include "m328Pdef.inc"
init: // defining variables
	.def i = r16
	.def sum = r17
	.def n = r18
main: // loading variables
	ldi i, 1
	ldi n, 16
	clr sum
loop:
	cp i, n // compare i to n
	breq end // if i = n, go to end
	add sum, i // otherwise add i to sum
	inc i // and increment i
	rjmp loop
end: // return results and end program
	out  PortB, sum // print the sum
	ret
