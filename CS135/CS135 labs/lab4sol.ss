#lang eopl

(define aStringList '("stevens" "in" "the" "news") )
(define anIntList '(1 2 3 4 5) )
(define anAtomeList '(stevens in the news) )
(define aPairList '((thing 1) (thing 2) (duckbills 17)) )
(define aMixedList '("stevens" (thing 2) (3) () 4) )

(define (second x)
  (car (cdr x)))

(define (has2 x)
  (cond
    ((or (null? x) (null? (cdr x))) #f)
    (else #t)))

(define atom?
  (lambda (x)
    (and (not (pair? x)) (not (null? x)))))
(define member?
  (lambda (a lat)
    (cond
      ((null? lat) #f)
      (else (or (eqv? (car lat) a)
                (member? (a (cdr lat))))))))
(define lgth
  (lambda (lst)
    (if (null? lst)
        0
        (+ 1 (lgth (cdr lst))))))

(define (sum lst)
  (if (null? lst)
      0
      (+ (car lst) (sum (cdr lst)))))

(define univ '(a b c d e))

(define R1 '( (a b) (b b) (c b) (d b) (e b) ))
(define R2 '( (a b) (b c) (c d) (d e) (e a) ))
(define R3 '( (a c) (b c) (a b) (c b) (e e) ))
(define R4 '( (a a) (b b) (c c) (d d) (e e) ))

(define (ident lst)
  (if (null? lst)
      '()
      (cons (list (car lst) (car lst)) (ident (cdr lst)))))