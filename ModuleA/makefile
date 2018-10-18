libstudent.a:student.o
	ar rsv ../RELEASE/libstudent.a ../RELEASE/student.o
student.o:student.c
	gcc student.c -I ../Include -c -o ../RELEASE/student.o
clean:
	cd ../RELEASE; rm student.o libstudent.a
