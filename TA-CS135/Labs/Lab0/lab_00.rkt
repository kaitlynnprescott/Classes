#lang eopl ;This tells your interpreter which version of Scheme to use

;; Lab 0 assignment

;; Objectives: Get familiar with using DrRacket to edit definitions and 
;; interpret expressions.  

;; Scheme comments begin with a semicolon, like this: ;
;; To compile code press the "Run" button in the top right corner

;; If you haven't downloaded Dr. Racket, get the installer
;; at this link: https://download.racket-lang.org/

;; Scheme code is written in PREFIX notation.  That means that instead of 
;; writing "3 + 5", we'll write "+ 3 5" to add three and five.
;; Furthermore, in order to tell Scheme you mean it, you must put the 
;; expression in parentheses


;; Type the following expressions into the prompt to see what they return

;; (+ 3 5)
;; (/ 3 5)
;; (+ 1 2 3 4)
;; (= 3 5)
;; (< 3 5)
;; (not (equal? 3 5))
;; (sqrt 100)
;; (log 100)
;; (exp 1)
;; (exp 2)
;; (and #t (equal? 3 3))

;; defn: Predicate: an expression/function that evaluates to TRUE/FALSE
;; many predicates have a "?" at the end

;; Try these predicate calls:

;; (zero? 0)
;; (number? "asdf")
;; (equal? 12 's17)

;; NOTE: there are multiple functions to test equality in Racket,
;; the two main ones are `equal?` and `=`. In this class, use `equal?`
;; because `=` can only compare numeric values.

;; We'll deal mostly with integers and Booleans and lists and pairs
;; Each type has a predicate associated with it:  (Try these.)

;; defn: Procedure: functions and operators

;; Example definition/function

(define (log10 num)
  (/ (log num) (log 10)))
;; all definitions start with (define followed by a (
;; the first word in the parenthesis will be the definition name and all following
;; words in the parenthesis will be parameters, then close that that parenthesis
;; the following line will start the body
;; whenever a procedure is called wrap it in parenthesis
;; once the body is completed close off the initial parenthesis


;; January 2018
;; Samuel Kraus and Edward Minnix
;; Stevens Institute of Technology
;; CS 135  Discrete Structures
