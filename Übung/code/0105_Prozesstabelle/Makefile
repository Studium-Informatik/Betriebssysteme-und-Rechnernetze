CC=gcc
AR=ar
TARGET=proctable
CFLAGS= -Wall -pedantic -Wextra

# create the final program
all: proctable.o dl_proc_list.o
	${CC} ${CFLAGS} $^ -o ${TARGET}

# create the static library libtest
%.a: %.o
	${AR} rc $@ $^

# This is a pattern rule.
# create an object file for each c file
%.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

# remove all object files static librarys and the final program
clean:
	rm -f *.o *.a ${TARGET}
