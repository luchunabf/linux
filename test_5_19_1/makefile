code_5_19_1:code_5_19_1.o
	gcc code_5_19_1.o -o code_5_19_1
code_5_19_1.o:code_5_19_1.s
	gcc -c code_5_19_1.s -o code_5_19_1.o
code_5_19_1.s:code_5_19_1.i
	gcc -S code_5_19_1.i -o code_5_19_1.s
code_5_19_1.i:code_5_19_1.c
	gcc -E code_5_19_1.c -o code_5_19_1.i
.PHONY:clean
clean:
	rm -f code_5_19_1.i code_5_19_1.s code_5_19_1.o code_5_19_1
