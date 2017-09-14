(cadr (caadar '(((1) ((2 *)) (3 (4))))))

(list '(+ 1 2) '() '(+ 1))

(list (list (list 1 2 (list (list 3))))
(cons (cons 1 (cons 2 (cons (cons (cons 3 nil) nil) nil))) nil)

(defun aaaa (l)
	(append
		(list (car l))
		(last l)
		(cddr (butlast l))
		(list (cadr l))
	)
)
(aaaa '(1 2 3 4 5 6 7))