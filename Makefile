.all: ascii
.PHONY: clean
.SUFFIXES:

CFLAGS := -Wall -Wextra -Werror

ascii: ascii.c Makefile
	$(CC) $(CFLAGS) ascii.c -o ascii

clean:
	$(RM) ascii
