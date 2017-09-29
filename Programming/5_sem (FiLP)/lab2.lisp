; task #7
(defun adding (x l)
	(cond
		((null l)
			(list x)
		)
		((< x (car l)) 
			(append (list x) l)
		)
		(t
			(append (list (car l)) (adding x (cdr l)) )
		)
	)
)
(adding 10 '(0 3 3 6 9))

;task #17
(defun summar (l)
	(cond
		((equal l nil)
			nil
		)
		(T
			(append (list (car l)) (summar (cddr l)))
		)
	)
)
(summar '(-2 6 s -1 4 f 0 z x r))

;task #27
(defun inpredfix (l)
	(cond
		( (null l) 0 )
		( (numberp l) l )
		( (equal (cadr l) '*) (inpredfix (cons (* (inpredfix (car l)) (inpredfix (caddr l))) (cdddr l))) )
		( (equal (cadr l) '/) (inpredfix (cons (/ (inpredfix (car l)) (inpredfix (caddr l))) (cdddr l))) )
		( (equal (cadr l) '+) (+ (inpredfix (car l)) (inpredfix (cddr l))) )
		( (equal (cadr l) '-) (- (inpredfix (car l)) (inpredfix (cddr l))) )
		( (equal (cdr l) nil) (inpredfix (car l)) )
	)
)
(trace inpredfix)
(inpredfix '(8 * 10))