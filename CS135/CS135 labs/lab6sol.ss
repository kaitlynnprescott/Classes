#lang eopl

(define (all-pos? lon)
  (cond
    [(null? lon) #t]
    [else (and (<= 0 (car lon)) (all-pos? (cdr lon)))]))
    

(define test-all-pos
  (and (all-pos? '(2 1 9 1))
       (all-pos? '(0 0 0))
       (all-pos? '())
       (not (all-pos? '(-1 2 -5)))
       (not (all-pos? '(1 2 -3 4)))
       ))

(define (make-ones n)
  (cond [(eqv? n 0) '()]
        [else (cons 1 (make-ones (- n 1)))]))

;Base Case: (all-pos? (make-ones 0))
;Proof of Base Case:
;(all-pos? (make-ones 0)) = (all-pos '())   *Def of make-ones
;= #t    *Def of all-pos?
;Inductive Case: (all-pos? (make-ones n))
;Inductive Hypothesis: (all-pos? (make-ones (- n 1)))
;Proof of Inductive Case:
;(all-pos? (make-ones n)) = (all-pos? (cons 1 (make-ones (- n 1))))    *Def make-ones
;= (and (<= 0 (car (cons 1 (make-ones (- n 1)))))
;       (all-pos? (cdr (cons 1 (make-ones (- n 1))))))    *Simplification
;= (and (<= 0 1)
;       (all-pos? (make-ones (- n 1))))     *Simplification
;= (and #t (all-pos? (make-ones (- n 1))))
;= (and #t #t)     *Induction Hypothesis
;= #t              *Def of and

(define (take n xs)
  (cond
    [(eqv? n 0) '()]
    [else (cons (car xs) (take (- n 1) (cdr xs)))]))

(define test-take
  (and (equal? (take 0 '(1 2 3 4 5)) '())
       (equal? (take 2 '(1 2 3 4 5)) '(1 2))
       (equal? (take 5 '(a b c d e)) '(a b c d e))
       ))

(define (drop n xs)
  (cond
    [(eqv? 0 n) xs]
    [else (drop (- n 1) (cdr xs))]))

(define test-drop
    (and (equal? (drop 0 '(a b c d e)) '(a b c d e))
         (equal? (drop 2 '(a b c d e)) '(c d e))
         (equal? (drop 5 '(a b c d e)) '())
         ))

(define (ascend? lon)
  (cond
    [(null? lon) #t]
    [(eqv? (cdr lon) '()) #t]
    [else (and (<= (car lon) (car (cdr lon))) (ascend? (cdr lon)))]))

(define test-ascend
  (and (ascend? '())
       (not (ascend? '(3 2 1)))
       (ascend? '(1 2 3))
       (ascend? '(-17 -3 -3 -3 2.04 5008.6))
       (not (ascend? '(1 2 3 4 5 6 7 6 7 8 9 10)))
       (ascend? '(1 20 20 30 30 30 40 50 51 52 53 54 55 56 57))
       ))

(define (merge xs ys)
  (cond
    [(and (null? xs) (null? ys)) '()]
    [(null? xs) ys]
    [(null? ys) xs]
    [(< (car xs) (car ys)) (cons (car xs) (merge (cdr xs) ys))]
    [else (cons (car ys) (merge (cdr ys) xs))]))
    

(define test-merge
  (and (equal? (merge '(1 2 3) '(0 4)) '(0 1 2 3 4))
       (equal? (merge '() '(1 2 3)) '(1 2 3))
       (equal? (merge '(1 2 3) '(100 200 300 400)) '(1 2 3 100 200 300 400))
       (equal? (merge '(100 200 300 400) '(1 2 3)) '(1 2 3 100 200 300 400))
       ))