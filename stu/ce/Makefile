CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS=addce.cgi delce.cgi modce.cgi selce.cgi addse.cgi delse.cgi modse.cgi selse.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi
install:
		cp *.cgi /usr/lib/cgi-bin/sx
