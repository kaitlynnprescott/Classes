#lang eopl
; lab9 assignment 2015 

; Objectives of lab:  
; Learn about role-based access control, RBAC for short. 
; Practice with map/reduce/filter which capture common recursion patterns.

; Note: RBAC is widely used, e.g., in medical informatics; it's also the model
; in the 2010 version of Microsoft Exchange server.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Step 0 
; Study the following functions.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (last lst)
  ; The last element of lst, assuming lst is a non-empty list
  (cond [(null? (cdr lst)) (car lst)]
        [else (last (cdr lst))]))

(define (reduce f ys b)  ; See lecture 17
  (cond [(null? ys) b]
        [else (f (car ys) (reduce f (cdr ys) b))]))

(define (my-or p q) (or p q)) ; hack to get around drScheme treatment of "or"

(define (member? x xs)
  ; Whether x is a member of list xs; implemented using reduce.
  (reduce my-or (map (lambda (y) (equal? y x)) xs) #f))

(define (filter lst pred?)
  ; Assume lst is a list of things and pred? is a function from things to boolean.
  ; Return the sub-set of lst consisting of things that satisfy pred?
  ; For example (filter '(1 2 3 4 5) even?) = '(2 4)
  (cond [(null? lst) '()]
        [(pred? (car lst)) (cons (car lst) (filter (cdr lst) pred?))]
        [else (filter (cdr lst) pred?)]))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Step 1
; Look over the following code carefully.
; It is a toy database of information related to access control in an imaginary
; software development project.  I am representing sets by lists without duplicates,
; and relations by sets of ordered pairs.  For simplicity, I am not distinguishing
; between different kinds of access (read/write/execute/etc).  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define PEOPLE '(Leila Tom Ana Paulo Mike Sue))
(define ROLES '(teammember tester programmer supervisor anyone))
(define OBJECTS '("/Sue/proj/main.ss" "/Sue/personal/contacts" "/Team/source/Snooze.java"
                  "/Team/tests/test1.ss" "/Team/lab9.ss" "/Team/advertising.html"))

(define PERMS ; relates a role to an object the role has permission to access
  '((teammember "/Team/lab9.ss") 
    (tester "/Team/tests/test1.ss") 
    (programmer "/Team/source/Snooze.java")
    (supervisor "/Team/tests/test1.ss")
    (anyone "/Team/advertising.html")
    (supervisor "/Team/source/Snooze.java")
    (supervisor "/Team/admin/Salaries.xls") ))

(define AUTH ; relates a person to a role they are authorized for
  '((Leila supervisor) (Tom tester) (Ana programmer)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Step 2 - to show TA
; 
; Our aim in this lab is to implement the access control interface.  The idea is 
; that when user u tries to access object o, the operating system checks whether 
; u is authorized for some role r that has permission to access o.
; 
; The tables in Step 1 represent configuration files that capture the current policy.
; Over time, PERMS and AUTH might change, but the way they are used should not
; change.  So the access control interface will consist of some predicates (i.e., 
; boolean-valued Scheme functions).
;
; TO DO: Study the code below.  Complete and test the missing code.
; Hint: First write a test function, for each of the functions.  That's a good
; way to be sure you understand the problem.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (role-has-perm? role obj)
  ; Whether role has permission for obj
  ; For example (role-has-perm? 'tester "/Team/tests/test1.ss") = #t 
  ; TO DO: implement this using member?.
  (member? (list role obj) PERMS))

(define (roles-of pers roleList)
  ; List of r in roleList such that (pers,r) is in AUTH 
  ; TO DO: implement this using filter. 
  (filter roleList (lambda (r) (member? (list pers r) AUTH))))

(define (has-perm-any? roleList obj)
  ; whether any r in roleList has permission for obj
  ; TO DO: replace this implementation by another one; instead of using recursion, use reduce.
  ; Hint:  look at the definition of member? above
  ;(cond [(null? roleList) #f]
   ;     [else (or (role-has-perm? (car roleList) obj)
;		  (has-perm-any? (cdr roleList) obj))]))
(reduce (lambda (r b) (or (role-has-perm? r obj) b)) roleList #f))

(define (has-perm? pers obj)
  ; Assume pers is in PEOPLE.  Check whether pers is authorized for some role r such
  ; that r has permission for obj.  
  ; For example, (has-perm? 'Ana "/Team/source/Snooze.java") = #t
  ; because (list 'Ana 'programmer) is in AUTH and (list 'programmer "/Team/source/Snooze.java") 
  ; is in PERMS.
  ; TO DO: implement this using has-perm-any? and roles-of.
  (cond [(eqv? (roles-of pers ROLES) #f) #f]
        [else (has-perm-any? ROLES obj)]))


(define test-has-perm-any ; should be #t
  (and (equal? (has-perm-any? ROLES "cat") (has-perm-any? ROLES "cat"))
       (equal? (has-perm-any? (cdr ROLES) "/Team/lab9.ss") (has-perm-any? (cdr ROLES) "/Team/lab9.ss"))
       (equal? (has-perm-any? (cdr ROLES) "/Team/tests/test1.ss") (has-perm-any? (cdr ROLES) "/Team/tests/test1.ss"))))

