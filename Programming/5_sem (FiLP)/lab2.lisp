; task #7
(defun adding (x l &optional s)
	(cond
		((null l)
			nil
		)
		((< x (car l)) 
			(append s (list x) l)
		)
		(t
			(adding x (cdr l) (append s (list (car l))) )
		)
	)
)
(adding 7 '(0 3 3 6 9))

;task #17
(defun summar (l &optional s)
	(cond
		((equal l nil)
			0
		)
		(T
			(+ (car l) (summar (cddr l)))
		)
	)
)
(summar '(-2 3 2 5 -6 5 2 1 3))

;task #27
(defun inpredfix (l &optional buf)
	
)