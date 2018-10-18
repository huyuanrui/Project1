libcourse.a:course.o
	ar rsv ../RELEASE/libcourse.a ../RELEASE/course.o
course.o:course.c 
	gcc course.c -I ../Include -c -o ../RELEASE/course.o
clean:
	cd ../RELEASE; rm course.o libcourse.a
