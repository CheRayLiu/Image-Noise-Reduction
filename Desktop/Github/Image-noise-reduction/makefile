CFLAGS =  -pg -O2
OBJS1 = main.o  timing.o filter_function.o 


denoise : $(OBJS1)	
	$(CC) -o $@ $? -pg

%.o: %.c filter.h
	$(CC) -c $? $(CFLAGS)
clean:
	rm -rf $(OBJS1)  denoise filter.h.gch gmon.out
