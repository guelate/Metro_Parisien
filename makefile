SHELL = /bin/sh
#definition des commandes utilisees
CC = gcc


CFLAGS = -Wall -g


PROGNAME = main
HEADERS = graph.h
SOURCES = main.c graph.c

OBJ = $(SOURCES:.c=.o)

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROGNAME)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

clean:
	@$(RM) $(PROGNAME) $(OBJ) *~ gmon.out core.*
