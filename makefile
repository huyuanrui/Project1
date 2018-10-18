main:main.o libstudent.a libcourse.a libchoose_course.a
	gcc ./RELEASE/main.o -L./RELEASE -lchoose_course -lstudent -lcourse -o main
main.o:main.c
	gcc main.c -I./Include -c -o ./RELEASE/main.o
libstudent.a:./ModuleA/student.c
	cd ./ModuleA; make
libcourse.a:./ModuleB/course.c
	cd ./ModuleB; make
libchoose_course.a:./ModuleC/choose_course.c
	cd ./ModuleC; make
clean:
	cd ./ModuleA; make clean;
	cd ./ModuleB; make clean;
	cd ./ModuleC; make clean;
	cd ./RELEASE; rm main.o
