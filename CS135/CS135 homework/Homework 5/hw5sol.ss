#lang eopl
; hw5.ss

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; INSTRUCTIONS
; 
; Make a copy of this file.  Read it step by step.  Add and test code as instructed.
; 
; In this homework, you will practice with recursive definitions of functions that 
; process lists.  In particular, you will use lists of pairs to represent relations.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Step A
; Look at the lists below.
; We can consider R1,..., R4 to be relations on theUniverse.
; 
; For you to do: change the comments to say yes/no about whether 
; each one represents a function with domain and codomain theUniverse.
; And for the functions, say whether it is injective.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define theUniverse '(a b c d e)) 

(define R1 '( (a b) (b b) (c b) (d b) (e b) )) ; function?  Yes  injective?  No
(define R2 '( (a b) (b c) (c d) (d e) (e a) )) ; function?  Yes  injective?  Yes
(define R3 '( (a c) (b c) (a b) (c b) (e e) )) ; function?  No   injective?  No
(define R4 '( (a a) (b b) (c c) (d d) (e e) )) ; function?  Yes  injective?  Yes

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Step B
; Implement lop? below, so that it returns a boolean indicating whether
; its argument xs is a list of pairs (i.e., 2-element lists).  Assume xs is a list.
; For example, (lop? '(a b c)) is #f and (lop? R1) is #t
; Use duple? defined below.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (duple? x) ; is x a 2-element list?
  (and (list? x) (eqv? 2 (length x))))

(define test-duple? (and (duple? '(a b)) 
                         (not (duple? '(a b c))) 
                         (not (duple? '()))))

(define (lop? xs) 
  (cond
    [(null? xs) ]
    [else (and (duple? (car xs)) (lop? (cdr xs)))]))

(define test-lop? (and (lop? R1)
                       (lop? R2)
                       (not (lop? '((a b) c)))
                       (not (lop? '((a b c) (d e))))
                       (lop? '())
                      ))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Step C
; Implement the following function so that lopU? returns a boolean indicating
; whether xs is a list of two-element lists whose elements are in theUniverse.
; The name is mnemonic for "list of pairs".  
; For example, lopU? should be true for R1 but false for '((a b c) d) because
; it is not a list of pairs, and false for '((1 3) (a d)) some elements are
; not in theUniverse.  Your code should work even if we change
; theUniverse to be a different list, but you can assume that theUniverse
; is a list and has no duplicates.
; 
; Assume xs is a list. It doesn't matter what lopU? does when applied to
; a number or an atom, because those are not lists.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  (define (isMember? x)
  (cond
    ((null? x) #t)
    (else
     (and
      (or
      (eqv? (car x) 'a )
      (eqv? (car x) 'b )
      (eqv? (car x) 'c )
      (eqv? (car x) 'd )
      (eqv? (car x) 'e ))
      (isMember? (cdr x))))))

(define (inUniv? xs) 
  (cond
    ((null? xs) #t)  
    (else
     (and (isMember? (car xs)) (inUniv? (cdr xs))))))

(define (lopU? xs)
  (and (lop? xs) (inUniv? xs)))


(define test-lopU?
  (and (lopU? R1)
       (lopU? '())
       (lopU? R2)
       (not (lopU? '(a b)))
       (not (lopU? '((a b) (3 4))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Step D
; Implement member-dom? to meet its specification.
; For example (member-dom? 'a R1) should return #t and
; (member-dom? 'f R1) should return #f
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (member-dom? x lop) ; Whether x is in the domain of the list of pairs lop.
  ; More precisely: assume lop is a list of pairs.  Return #t if x is the first
  ; element of one of those pairs, otherwise #f.  For example,
  ; (member-dom? 'c R3) is #t but (member-dom? 'd R3) is #f.
  (if (null? lop)
      #f
      (if (eq? x (car (car lop)))
          #t
          (member-dom? x (cdr lop)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Step E
; Implement tot? to meet its specification.  The name suggests "total relation".
; For example, (tot? theUniverse R1) is #t but (tot? '(a b c d e f g) R1) is #f.  
; Also (tot? '(h i j) R1) is #f.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (tot? u lop) 
  ; Assume that u is a list and lop is a list of pairs
  ; Return a boolean indicating whether, for every x in u there is a pair (x y) in lop.
  (cond
    ((null? u) #t)
    (else (and
           (member-dom? (car u) lop)
           (tot? (cdr u) lop)))))


