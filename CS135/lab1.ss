#lang eopl

;; lab1 assignment 2015 

;; Objectives of lab:  
;; Install drRacket and get familiar with interactive interpreter.
;; Get quick glimpse at basic values and expressions in Scheme.

;; Step 1
;; ------

;; Do the tutorial here, which begins with downloading DrRacket
;;   http://docs.racket-lang.org/quick/
;; Do it through the 4th topic, i.e., stop when you get to 'Local Binding'.

;; Step 2
;; ------

;; Under menu Language -> Choose Language,
;; select "Use the language declared in the source..."
;; Leave it that way for the rest of the semester.

;; Step 3
;; ------

;; Type the following expressions at the prompt, one at a time.  
;; Explain the result in each case. 
;; (TA may lead this as a group discussion.)

1
2.0
"hi"
#t
#f
(+ 1 1)
(and #t #f)
(equal? 2 2)
(> 2 1)
(equal? (> 2 1) #t)
(define two 1)  ; deliberately confusing
(define three (+ two 1))
two
three
four 
(+ #t f)  ; which shows Scheme has strong, dynamic typing like JS and python
(and 0 1)
number?
(number? 2)
(number? "two")
(number? #t)
(boolean? #t)
(boolean? 2)
(string? "two")
(atom? 'two)
(atom? 2)
(atom? "two")
(atom? atom?)
(procedure? +)
(procedure? 2)
(procedure? "two")
; be careful to type the next one exactly, including the leading quote mark
'(html (body (h1 "my home page") (a (href "http://www.stevens.edu") "click here")))
(define (impl p q) (or (not p) q))
(impl #f #f)
(impl #f #t)
(impl #t #f)
(impl #t #t)
(define funny '(define funny #f))
funny
fancy
