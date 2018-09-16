#lang racket
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; assignment 1
;; Author: Kaitlynn Prescott
;; Date: 1/27/17
;; Pledge: I pledge my honor that I have abided by the Stevens honor system.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;Exercise 1:
    ;; Question 1:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; a -> num
(define (seven x)
  7)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Question 2:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; num -> num
(define (sign n)
  (cond ((negative? n) -1)
        ((positive? n) 1)
        (else 0)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Question 3:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; num -> num
(define (absolute n)
  (cond ((negative? n) (* n -1))
        ((positive? n) n)
        (else 0)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Question 4:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; {bool, bool} -> bool
(define (andp a b)
  (cond
    [(equal? #t a)
     (cond [(equal? #t b) #t]
           (else #f))]
    (else #f)))
    
;; {bool, bool} -> bool
(define (orp a b)
  (cond ((equal? #t a) #t)
        ((equal? #t b) #t)
        (else #f)))
;; bool -> bool
(define (notp a)
  (cond ((equal? a #t) #f)
        ((equal? a #f) #t)))
;; {bool, bool} -> bool
(define (xorp a b)
  (cond
    [(equal? #t a)
     (cond [(equal? #t b) #f]
           (else #t))]
    [(equal? #f a)
     (cond [(equal? #f b) #f]
           (else #t))]))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Question 5:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; {num, num} -> bool
(define (dividesBy x y)
  (cond ((equal? (remainder x y) 0) #t)
        (else #f)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Question 6:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; [a] -> bool
;; match
(define (singleton1? xs)
  (match xs
    [(list a) #t]
    [_ #f]))
;; cons? and null?
(define (singleton2? xs)
  (cond ((null? (cdr xs)) #t)
        (else #f)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Question 7:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; [a] -> [a]
(define (swap xs)
  (match xs
    [(list a b) (list b a)]))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Question 8:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; {a, b} -> c where a is a function, b is input for the function, and c is the output
(define (app x y)
  (x y))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Question 9:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; {a, b} -> c where a is a function, b is input for the function, and c is the output
(define (twice x y)
  (app x (app x y)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Question 10:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; {a, a, b} -> c where a is a function, b is input for the function, and c is the output
(define (compose x y z)
  (x (y z)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Exercise 2:
    ;; Question 1:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; {num, [a]} -> bool
(define (belongsTo1 n lst)
  ( if (equal? (member n lst) #f)
       #f
       #t))
;; {[a], [a]} -> [a]
(define (intersection1 x y)
  (cond
    [(null? x) y]
    [(belongsTo1 (car x) y) (cons (car x) (intersection1 (cdr x) y))]
    [(not (belongsTo1 (car x) y)) (intersection1 (cdr x) y)]))

;; {[a], [a]} -> [a]
(define (union1 x y)
  (cond
    [(null? x) y]
    [(belongsTo1 (car x) y) (union1 (cdr x) y)]
    [else (cons (car x) (union1 (cdr x) y))]))

;; {(a -> bool), (a -> bool)} -> (a -> bool)
(define (union2 x y)
  (lambda (xs)
    (if (or (x xs) (y xs))
        #t
        #f)))

;; {(a -> bool), (a -> bool)} -> (a -> bool)
(define (intersection2 x y)
  (lambda (xs)
    (if (and (x xs) (y xs))
        #t
        #f)))

;; {(a->bool), num} -> bool
(define (belongsTo2 f x)
  (if (f x)
      #t
      #f))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Question 2:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (remDups xs)
  (cond
    [(equal? (car xs) (cadr xs)) (cons (car xs) (remDups (cddr xs)))]
    [else (cons (car xs) (remDups (cdr xs)))]))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Question 3:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (sublists lst)
  (if (null? lst) '(())
      (append-map (lambda (x)
                    (list x (cons (car lst) x)))
                  (sublists (cdr lst)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Exercise 3:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  ;; E ::= (const num) |(add E E) | (sub E E) | (mult E E) | (div E E)
(define e1
  '(const 2))
(define e2
  '(add (sub (const 2) (const 3)) (const 4)))
(define e3
  '(add (const 2) (const 4)))

(define add
  (lambda (x y) (+ x y)))

(define sub
  (lambda (x y) (- x y)))

(define mult
  (lambda (x y) (* x y)))

(define div
  (lambda (x y) (/ x y)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Question 1:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; {f, [e]} -> [e] where e is a calculator expression
(define (mapC f e)
  (match e
    [(list 'const a) (list 'const (f a))]
    [(list 'add b c) (list 'add (mapC f b) (mapC f c))]
    [(list 'sub b c) (list 'sub (mapC f b) (mapC f c))]
    [(list 'mult b c) (list 'mult (mapC f b) (mapC f c))]
    [(list 'div b c) (list 'div (mapC f b) (mapC f c))]))

;; { num -> b , {b, b} -> b, {b, b} -> b, {b, b} -> b, {b, b} -> b, [e]} -> num
(define foldC
         (lambda (const add sub mult div e)
           (match e
             [(list 'const (? number? a)) a]
             [(list 'add e1 e2) (add (foldC const add sub mult div e1) (foldC const add sub mult div e2))]
             [(list 'sub e1 e2) (sub (foldC const add sub mult div e1) (foldC const add sub mult div e2))]
             [(list 'mult e1 e2) (mult (foldC const add sub mult div e1) (foldC const add sub mult div e2))]
             [(list 'div e1 e2) (div (foldC const add sub mult div e1) (foldC const add sub mult div e2))])))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Question 3:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; [e] -> num
(define (numAddHelp e)
  (foldC (lambda (x) 0) ;; f1
         (lambda (x y) (+ 1 x y)) ;; f2
         (lambda (x y) 0) ;; f3
         (lambda (x y) 0) ;; f4
         (lambda (x y) 0) ;; f5
         e))

;; [e] -> num
(define (numAdd e)
  (sub (numAddHelp e) (evalCf e)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Question 4:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; [e] -> [e] where e is the calculator expression
(define (replace_add_mult e)
  (foldC (lambda (x) (list 'const x)) ;; f1
         (lambda (x y) (list 'mult x y)) ;; f2 -> change add to mult.
         (lambda (x y) (list 'sub x y)) ;; f3
         (lambda (x y) (list 'mult x y)) ;; f4
         (lambda (x y) (list 'div x y)) ;; f5
         e))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Question 5:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; [e] -> num
(define (evalHelp e)
  (match e
    [(list 'const a) a]
    [(list 'add b c) (+ (evalHelp b) (evalHelp c))]
    [(list 'sub b c) (- (evalHelp b) (evalHelp c))]
    [(list 'mult b c) (* (evalHelp b) (evalHelp c))]
    [(list 'div b c) (/ (evalHelp b) (evalHelp c))]))

;; [e] -> [e]
(define (evalC e)
  (list 'const (evalHelp e)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Question 6:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;
(define (evalCf e)
  (foldC (lambda (x) x)
         (lambda (x y) (+ x y))
         (lambda (x y) (- x y))
         (lambda (x y) (* x y))
         (lambda (x y) (/ x y))
         e))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Exercise 4:
    ;; Question 1:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (f xs)
  (let ((g (lambda (x r) (if (even? x) (+ r 1) r))))
    (foldr g 0 xs)))
;; This function counts the number of even numbers in a list.
(define test
  '(Test function f in Exercise 4))
test
'(1 2 3 4 5 6 7 8)
'(The number of evens in this list is:)
  (f '(1 2 3 4 5 6 7 8)) ;; 4
'(2 4 6 8 10 12 14)
'(The number of evens in this list is:)
  (f '(2 4 6 8 10 12 14)) ;; 7
'(1 2 6 4 7 2 9 4 2 84 3)
'(The number of evens in this list is:)
  (f '( 1 2 6 4 7 2 9 4 2 84 3)) ;; 7

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  
    ;; Question 3:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; [a] -> [a]
(define (concat xss)
   (let ((g (lambda (xs h) (append xs h))))
     (foldr g '() xss )))

