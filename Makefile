# list all binaries in this next line
BINARIES = vol1 vol1_look vol1_bit
CCOPTS = -g -O3

all:	${BINARIES}

vol1:	vol1.c vol.h
	gcc ${CCOPTS} vol1.c -o vol1

vol1_look:	vol1_look.c vol.h
		gcc ${CCOPTS} vol1_look.c -o vol1_look

vol1_bit:	vol1_bit.c vol.h
		gcc ${CCOPTS} vol1_bit.c -o vol_bit

test1:	vol1
	bash -c "time ./vol1"

# target to test all binaries
test:	test1 

gdb1:	vol1
	gdb vol1

clean:	
	rm ${BINARIES} || true


