#lang eopl

(define (sq n) (* n n))
(define (squares xs)
  (cond [(null? xs) '()]
        [else (cons (sq (car xs)) (squares (cdr xs)))]))

(define test-squares
  (and (equal? (squares '(3 2 7 5 2))
               '(9 4 49 25 4))
       (equal? (squares '(2 -1))
               '(4 1))))

(define (pair-sums lint)
  (cond [(null? lint) '()]
        [else (cons (+ (car (car lint)) (car (cdr (car lint)))) (pair-sums (cdr lint)))]))

(define test-pair-sums
  (and (equal? (pair-sums '((1 9) (6 2)) )
               '(10 8) )
      (equal? (pair-sums '((-1 9) (2 2) (0 0)) )
               '(8 4 0)) ))

(define (rev-triples lot)
  (cond [(null? lot) '()]
        [else (cons (reverse (car lot)) (rev-triples (cdr lot)))]))

(define test-rev-triples
  (and (equal? (rev-triples '((a b c) (d e f) (g h i)))
               '((c b a) (f e d) (i h g)))
       (equal? (rev-triples '((1 2 3) (4 5 6)))
               '((3 2 1) (6 5 4)))
       (equal? (rev-triples '())
               '()) ))

(define (adj-pair-sums lint)
  (cond [(or (null? lint) (null? (cdr lint))) '()]
        [else (cons (+ (car lint) (car (cdr lint))) (adj-pair-sums (cdr lint)))]))

(define test-adj-pair-sums
  (and (equal? (adj-pair-sums '(1 1 1))
               '(2 2) )
       (equal? (adj-pair-sums '(1 2 3 4))
               '(3 5 7) )
       (equal? (adj-pair-sums '(-2 7))
               '(5) )))

(define (max-of-lists xss)
  (cond [(null? xss) '()]
        [else (cons (apply max (car xss)) (max-of-lists (cdr xss)))]))

(define test-max-of-lists
  (and (equal? (max-of-lists '((1 2 3) (100) (100 200)))
               '(3 100 200))
       (equal? (max-of-lists '())
       '()) ))

(define (ints? lst)
  (cond [(null? lst) #t]
        [(not (integer? (car lst))) #f]
        [else (ints? (cdr lst))]))

(define (empty? lst)
  (cond [(null? lst) #t]
        [(not (list? (car lst))) #f]
        [else (empty? (cdr lst))]))

(define (ints2? lst)
  (cond [(null? lst) #t]
        [(not (list? (car lst))) #f]
        [(ints? (car lst)) (ints2? (cdr lst))]
        [else #f]))
  
(define (max-of-all xss)
  (cond [(null? xss) 'max-of-all-error]
        [(not (empty? xss)) 'max-of-all-error]
        [(not (ints2? xss)) 'max-of-all-error]
        [else (apply max (max-of-lists xss))]))


(define test-max-of-all
  (and (equal? (max-of-all '((1 2 3) (100) (100 200)))
               200 )
       (equal? (max-of-all '())
               'max-of-all-error)
       (equal? (max-of-all '((1 2 3) ()) )
               'max-of-all-error)
       (equal? (max-of-all '((1 2 3) x))
               'max-of-all-error)
       (equal? (max-of-all '((1 2 3) (1 x 3)))
               'max-of-all-error)
       (equal? (max-of-all '((1)))
               1) ))