;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  Author: Kaitlynn Prescott						;;
;;  Assignment: Assembly1						;;
;;  File: question5.asm							;;
;;  Pledge: I pledge my honor that I have abided by			;;
;;          the Stevens Honor System.					;;
;;  Date: 24 Oct 2017							;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 5. Write an assembly language program to find the largest number	;;
;; in 15 binary numbers read from Data Space. Get the numbers from	;;
;; the Data Space starts from 0x0100. Output the result to Port B.	;;
;; (use register z to get number) (Points 20)				;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.include "m328Pdef.inc"
init: // defining variables
	.def maxNum = r16
	.def largestNum = r17
	.def count = r18
main: // loading variables
	ldi maxNum, 15
	ldi zh, 0x01
	ldi zl, 0x00
	ldi largestNum, 0
	ldi count, 0
loop:
	cpc count, maxNum // compare the count to the bound
	brge end // if count >= maxNum, skip to end of program
	inc count // increase count
	ld r22, z+
	cpc r22, largestNum // compare r22 to the largest number
	brge found // if r22 >= largestNum, go to found
	rjmp loop
found: // have new largest number
	mov largestNum, r22 // set largestNum to be what is at r22
	rjmp loop // go back to loop
end: // return the result and end the program
	out PortB, largestNum
	ret
