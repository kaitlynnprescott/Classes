;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  Author: Kaitlynn Prescott						;;
;;  Assignment: Assembly1						;;
;;  File: question3.asm							;;
;;  Pledge: I pledge my honor that I have abided by			;;
;;          the Stevens Honor System.					;;
;;  Date: 24 Oct 2017							;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 3. Write an assembly language program to take the next two numbers	;;
;; in memory starting at data space 0x0100. Compare them and output	;;
;; the greater number (if the numbers are equal, output that number).	;;
;; (Points 15)								;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.include "m328Pdef.inc"
init:
	.def i = r16
	.def n = r17
main:
	ldi n, 1
	ldi zh, 0x01
	ldi zl, 0x00
	ld r22, z+
	ld r23, z
	cpc r22, r23 // compares r22 and r23
	brlo printL // if r22 < r23, go to printL
	out PortB, r22 // print r22 otherwise
	rjmp end
printL: 
	out PortB, r23 // if r22 < r23, print r23
	rjmp end
end: // end program
	ret
