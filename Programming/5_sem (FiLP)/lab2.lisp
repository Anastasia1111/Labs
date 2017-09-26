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