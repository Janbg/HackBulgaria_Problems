#lang racket

;;#######################==-- The Main Function --==#######################;;

(define (point-func x y str)
  (cond
    [(= (string-length str) 0) (print-result x y)]
    [(equal? ">" (get-first str)) (point-func (+ x 1) y (remove-first str))]
    [(equal? "<" (get-first str)) (point-func (- x 1) y (remove-first str))]
    [(equal? "^" (get-first str)) (point-func x (- y 1) (remove-first str))]
    [(equal? "v" (get-first str)) (point-func x (+ y 1) (remove-first str))]
    [(equal? "~" (get-first str)) (point-func x y (inversion str))]
    [else (display "Error with introduced string!")])
)


; ============================  Example:  ================================
;
;  > (point-func 0 0 ">>><<<~>>>~^^^")
;
; (-3, -3)
; ========================================================================



;;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% HELPERS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

;;---Reverse String:
(define (rev-string str)
  (list->string (reverse (string->list str)))
)


;;---Remove First Char From String:
(define (remove-first str)
  (rev-string (~a (rev-string str) #:max-width (- (string-length str) 1)))
)


;;---Get First Chat from String:
(define (get-first str)
  (~a str #:max-width 1)
)


;;---Print Result:
(define (print-result x y)
  (begin
    [display "("]
    [display x]
    [display ", "]
    [display y]
    [display ")"])
)


;;---Inverse Coordinate System
(define (inversion str)
  (define (helper str)
    (string-replace
     (string-replace
      (string-replace
       (string-replace
        (string-replace
         (string-replace
          (string-replace
           (string-replace str "v" "4")"^" "3")"<" "2")">" "1")"4" "^")"3" "v")"2" ">")"1" "<")
    )

  (helper (remove-first str))
  )


;;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%