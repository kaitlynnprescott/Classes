#lang racket
(require eopl/eopl)
(define-datatype program program?
  (a-program
   (exp1 expression?)))

(define-datatype expression expression?
  (const-exp (num number?)) ;; number
  (var-exp (var symbol?)) ;; identifier
  (diff-exp (exp1 expression?)
            (exp2 expression?));; difference
  (zero?-exp (exp1 expression?)) ;; zero?
  (if-exp (exp1 expression?)
          (exp2 expression?)
          (exp3 expression?));; if then else
  (let-exp (var symbol?)
           (exp1 expression?)
           (body expression?))) ;; let

(define zero
  (a-program
   (zero?-exp
     (diff-exp
      (const-exp 55)
      (diff-exp
       (var-exp 'x)
       (const-exp 11))))))

