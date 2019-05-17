jindutiao:jindutiao.o
	gcc jindutiao.o -o jindutiao
jindutiao.o:jindutiao.s
	gcc -c jindutiao.s -o jindutiao.o
jindutiao.s:jindutiao.i
	gcc -S jindutiao.i -o jindutiao.s
jindutiao.i:jindutiao.c
	gcc -E jindutiao.c -o jindutiao.i
.PHONY:clean
clean:
	rm -f jindutiao.i jindutiao.s jindutiao.o jindutiao
