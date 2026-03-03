makefile: main.c
	gcc -o main main.c
	./main
	cat student_grades
	rm -f main	

