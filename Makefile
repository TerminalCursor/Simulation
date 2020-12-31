# $@ = target file
# $< = first dependency
# $^ = all dependencies

C_SOURCES = $(wildcard Physics/*.c *.c)
C_HEADERS = $(wildcard Physics/*.h *.h)
C_OBJECTS = ${C_SOURCES:.c=.o}

CC = gcc
CFLAGS=-lm

# FIRST RULE IS RUN BY DEFAULT
build: ${C_OBJECTS}
	${CC} -o $@ $^ ${CFLAGS}

%.o: %.c ${C_HEADERS}
	${CC} -c $< -o $@

.PHONY: clean

clean: cleanobj
	rm -rf build

cleanobj:
	rm -rf ${C_OBJECTS}
