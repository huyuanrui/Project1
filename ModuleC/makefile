libchoose_course.a:choose_course.o
	ar rsv ../RELEASE/libchoose_course.a ../RELEASE/choose_course.o
choose_course.o:choose_course.c
	gcc choose_course.c -I../Include -c -o ../RELEASE/choose_course.o
clean:
	cd ../RELEASE; rm libchoose_course.a choose_course.o
