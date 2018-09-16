#lang eopl

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Step 1: Define a Scheme function expo so that (expo n i) is n^i for natural
;; numbers n and i. Use the standard math definition
;; n^0 = 1 and n^i = n*n^(i-1) for all i>0.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (expo n i)
  (cond [(eq? i 0) 1]
        [else (* n (expo n (- i 1)))]))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Step 2: Using the standard math definition, prove that n^i*n^j=n^(i+j) for all
;; natural numbers i, j, and n. Use induction on i.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Ind. Hyp: P(j) = ∀𝑖 ∈ Z(>= 0)∶ n^(i+j) = n^i * n^j
; 𝑃(0) is true because
; n^(i+0) = n^i * 1 = n^i * n^0
; Base Case:
; 𝑃(1) is true because
; n^(i+1) = n^i * n = n^i * n^1
; Inductive Case:
; n^i * n^(k+1) = n^i * (n^k * n)              Integer Power
; = (n^i * n^k) * n                            Associative Identity
; = n^(i+k) * n                                Induction Hypothesis
; = n^(i+k+1)                                  Integer Power
; Therefore,
; P(k) -> P(k+1) and ∀𝑖,𝑗 ∈ Z(>= 0)∶ n^(i+j) = n^i * n^j

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Step 3:  As a consequence of what you proved, we know that n^(2*i) = n^i ∗ n^i.
;; In other words, if j is even then n^j = n^j/2 ∗ n^j/2. Use this observation to
;; add an additional case in your definition of expo. Call the new Scheme function
;; expo-fast.
;; Is it faster? justify your answer somehow.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (expo-fast n i)
  (cond [(eq? i 0) 1]
        [(even? i) (+ (expo n (/ i 2)) (expo n (/ i 2)))]
        [else (* n (expo n (- i 1)))]))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Step 4: Define another version, expo-trec, that works by calling a tail-recursive
;; helper function. It does not need to use the improvement from expo-fast. The helper
;; function should be called expo-help and it should use an additional parameteras an
;; accumulator, so that (expo-help n i r) accumulates the result in r.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (expo-trec n i) (expo-help n i 1))

(define (expo-help n i r)
  (cond [(eq? i 0) r]
        [else (expo-help n (- i 1) (* r n))]))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Step 5: Our goal is to prove that (expo-trec n i) = (expo n i) for any natural n
;; and i. But (expo-trec n i) probably just calls (expo-help n i 1). So what we really
;; need to come up with is an equation of this form:
;;
;; LEMMA     (expo-help n i r) = ???
;;
;; And it has to be such that if we plug in 1 for r, then the right side simplifies
;; to (expo n i).
;;
;; Your job: figure out that equation and prove it by induction on i. Then use the
;; lemma to prove that (expo-trec n i) = (expo n i) for any n, i.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Theorem: ∀𝑖 (expo-trec n i) = (expo n i)
; Proof: (expo-trec n i)
;      = (expo-help n i 1)           Def expo-trec
;      = (* (expo n i) 1)            LEMMA
;      = (expo n i)                  arithmetic
;
; LEMMA: (expo-help n i r) = (* r (expo n i))
; BASE CASE: (expo-help n 0 r) = (* r (expo n 0))
;     (expo-help n 0 r)
;   = r
;   = (* r (expo n 0))
;
; INDUCTIVE CASE:
; Ind. Hyp.: (expo-help n (- i 1) r) = (expo n (- i 1))
; Ind. Step:
;      (expo-help n i r)
;    = (expo-help n (- i 1) (* r n))     Def expo-help
;    = (* (* r n) (expo n (- i 1)))      Ind. Hyp. / Instantiate r
;    = (* r (* n (expo n (- i 1))))      Commutative / Associative 
;    = (* r (expo n i))                  Def expo
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Step 6: Consider the fucntion below.
;; Write another version, called powsum-trec, that satisfies the same specification
;; but works by calling a tail recursive helper. (it can use the built-in function
;; expt or one of your expo functions, whatever you like.)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (powsum lon)
  ; Takes a list, lon, of natural numbers. Returns the sum of
  ; the powers 2^n where n ranges over elements of lon.
    (cond [(null? lon) 0]
          [else (+ (expt 2 (car lon)) (powsum (cdr lon)))]))

;; example: (powsum '(2 3 1)) returns 2^2 + 2^3 + 2^1 which is 14.

(define (powsum-trec lon) (powsum-help lon 0))

(define (powsum-help lon r)
  (cond [(null? lon) r]
        [else (powsum-help (cdr lon) (+ (expt 2 (car lon)) r))]))

(define test-powsum
  (and (equal? (powsum '(1 2 3)) (powsum-trec '(1 2 3)))
       (equal? (powsum '()) (powsum-trec '()))
       (equal? (powsum '(5 2 49 0)) (powsum-trec '( 5 2 49 0)))))

