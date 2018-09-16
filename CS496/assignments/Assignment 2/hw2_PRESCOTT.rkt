#lang racket
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; assignment 2
;; Author: Kaitlynn Prescott
;; Date: 1/27/17
;; Pledge: I pledge my honor that I have abided by the Stevens honor system.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; --------------------------------------------------------------------
; ---------------------------- Section 3: ----------------------------
; --------------------------------------------------------------------

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;     Exercise 1: Define dTree
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(require eopl/eopl)

(define-datatype dTree dTree?
  (leaf-t (n number?))
  (node-t (d symbol?)
          (l dTree?)
          (r dTree?)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;     Exercise 2: Define the two trees in Fig. 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; dTree
(define tLeft
  (node-t 'w
        (node-t 'x (leaf-t 2) (leaf-t 5))
        (leaf-t 8)))

;; dTree
(define tRight
  (node-t 'w
        (node-t 'x (leaf-t 2) (leaf-t 5))
        (node-t 'y (leaf-t 7) (leaf-t 5))))


;; testing
(define print-trees
  '(--- Print tLeft and tRight ---))
print-trees
(define left
  '(- tLeft -))
(define right
  '(- tRight -))

left
tLeft

right
tRight

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;     Exercise 3a: dTree-height
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; dTree -> num
(define (dTree-height t)
  (cases dTree t
    (leaf-t (n) 0)
    (node-t (d l r) (max (+ 1 (dTree-height l))
                         (+ 1 (dTree-height r))))))


;; testing
(define test-height
  '(--- Test dTree-height ---))
test-height

left
(dTree-height tLeft)
right
(dTree-height tRight)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;     Exercise 3b: dTree-size
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; dTree -> num
(define (dTree-size t)
  (cases dTree t
    (leaf-t (n) 1)
    (node-t (d l r) (+ 1 (dTree-size l) (dTree-size r)))))

;; testing
(define test-size
  '(--- Test dTree-size ---))
test-size

left
(dTree-size tLeft)
right
(dTree-size tRight)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;     Exercise 3c: dTree-paths  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; dTree -> [[num]]
(define (dTree-paths t)
  (cases dTree t
    (leaf-t (n) '(()))
    (node-t (d l r) (append (helper 0 (dTree-paths l))
                            (helper 1 (dTree-paths r))))))

; {num, [[num]]} -> [num]
(define (helper x xs)
  (map (lambda (lst) (cons x lst)) xs))

;; testing
(define test-path
  '(--- Test dTree-paths ---))
test-path

left
(dTree-paths tLeft)
right
(dTree-paths tRight)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;     Exercise 3d: dTree-perfect?
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; dTree -> bool
(define (dTree-perfect? t)
  (cases dTree t
    (leaf-t (n) 1)
    (node-t (d l r) (equal? (dTree-perfect? l) (dTree-perfect? r)))))

;; testing
(define test-perfect
  '(--- Test dTree-perfect ---))
test-perfect

left
(dTree-perfect? tLeft)
right
(dTree-perfect? tRight)

  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;     Exercise 3e: dTree-map 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; {symbol? -> symbol?, number? -> number?, dTree} -> dTree
(define (dTree-map f g t)
  (cases dTree t
    (leaf-t (n) (leaf-t (g n)))
    (node-t (d l r) (node-t (f d) (dTree-map f g l) (dTree-map f g r)))))

;; symbol? -> symbol?
(define symbol-upcase
  (compose string->symbol (compose string-upcase symbol->string)))

;; num -> num
(define (succ n)
  (+ n 1))

;; testing
(define test-map
  '(--- Test dTree-map ---))
test-map

left
(dTree-map symbol-upcase succ tLeft)
right
(dTree-map symbol-upcase succ tRight)

; --------------------------------------------------------------------
; ---------------------------- Section 4: ----------------------------
; --------------------------------------------------------------------
  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;     Exercise 4: list->tree
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; bf
(define bf '( (x y z) .
                      (((0 0 0) . 0)
                       ((0 0 1) . 1)
                       ((0 1 0) . 1)
                       ((0 1 1) . 0)
                       ((1 0 0) . 1)
                       ((1 0 1) . 0)
                       ((1 1 0) . 0)
                       ((1 1 1) . 1))))

;; [a]
(define l1 (cdr bf))

;; [a] -> dTree
(define (list->tree l)
  (cond
    [(empty? l) (leaf-t 0)]
    [else (node-t (car l) (list->tree (cdr l)) (list->tree (cdr l)))]))

;; testing
(define test-list
  '(--- Test list->tree ---))
test-list

(list->tree '(x y z))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;     Exercise 5: replaceLeafAt
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; {[a], dTree} -> dTree
(define (replaceLeafAt lst t)
  (cases dTree t
    (leaf-t (n) (leaf-t (cdr lst)))
    (node-t (d l r) (if (= (caar lst) 0)
                        (node-t d (replaceLeafAt (cons (cdar lst) (cdr lst)) l) r)
                        (node-t d l (replaceLeafAt (cons (cdar lst) (cdr lst)) r))))))

;; testing
(define test-replace
  '(--- Test replaceLeafAt ---))
test-replace

left
(replaceLeafAt '((0 1) . 25) tLeft)
right
(replaceLeafAt '((1 0) . 25) tRight)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;     Exercise 6: bf->tree 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; {[a], dTree} -> dTree
(define (help l t)
  (if (empty? l)
      t
      (help (cdr l) (replaceLeafAt (car l) t))))

;; [a] -> dTree
(define (bf->tree bf)
  (define t (list->tree (car bf)))
  (help (cdr bf) t))

;; testing
(define test-bf
  '(--- Test bf->tree ---))
test-bf
(bf->tree bf)