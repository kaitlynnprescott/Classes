#lang eopl ; (keep this line, it tells DrRacket which version of Scheme to use)

; lab2 assignment 2015

; Objectives: Get familiar with using DrRacket to edit definitions and interpret
; expressions.  Get familiar with the built-in boolean operators.  

; Step 0: In the drRacket edit window, make a file lab2sol.ss.  Put your name and
; the lab assignment in a comment.  The very first line of the file should be 
; the mysterious incantation "#lang eopl", just like this file has.  Following that, 
; paste the definition of the "atom?" function.  Don't worry what it means.
; You will need to include it in your DrRacket files when trying things from the Little Schemer.

(define atom?
  (lambda (x) 
    (and (not (pair? x)) (not (null? x)))))

; Step 1: Read through the rest of this file -- and from now on, do try to understand what 
; things mean. As you go, add the definitions to your file, one at a time.  Click 'run' 
; for each one, an fix syntax errors before proceeding to the next.  
; Additional instructions appear in *** comments below. 

; Note: Rather than cut-and-paste, it may help your learning if you type everything yourself.
; You don't need to type in the comments, but do use menu Racket/reindent to
; keep the indentation neat.

; Some basic logic operators, defined in terms of Racket's built-in and,or,not
; Remember that Racket uses prefix notation, e.g., "x /\ y" gets written "(and x y)".
(define (xor x y)
  (and (or x y) (not (and x y))))
(define (impl x y)
  (or (not x) y))

; Here's a function for checking the commutative law for xor.
; The 'eqv?' function tests the equality of two values.
(define (test-xor-commute x y)
  (eqv? (xor x y) (xor y x)))

; *** Now try some tests in the interaction window, like this:
;   > (test-xor-commute #t #t) 
; This is a valid law about xor, so it should return true no
; matter what arguments you try. 

; Let's do another law, and automate the testing.
(define (test-and-absorp x y)  ;  (x /\ (x \/ y)) === x
  (eqv? (and x (or x y)) x))
(define t1
  (test-and-absorp #f #f))
(define t2
  (test-and-absorp #f #t))
(define t3
  (test-and-absorp #t #f))
(define t4
  (test-and-absorp #t #t))

; *** Now try entering just t1 at the interactive prompt, like this:
;   > t1
; It should return true.  Each of them should.  

; A single test
(define t1234 
  (and t1 t2 t3 t4))
; *** Try it.



; Onward to another law
(define (test-or-idem x)
  (eqv? (or x x) x))
; *** Now define u1, u2, and u12 similar to t1,...t1234 for test-or-idem
; and try it.

; Yet another law (?) 
(define (test-impl-commute x y)
  (eqv? (impl x y) (impl y x)))
; *** Define tests w1, w2, ... w1234 similar to t1234, and try it.

; Finally, define ternary operator f that's true iff exactly two arguments are.
; And test f.
; You are only allowed to use and, or, and not.  
; Hint: in scheme, 'and' takes multiple arguments
(define (f x y z) "your definition will go here")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

