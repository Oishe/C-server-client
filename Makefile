CC = gcc
CFLAGS  = -g -Wall
T1 = client
T2 = server

all: $(T1) $(T2)

$(T1): $(T1).c
	$(CC) $(CFLAGS) -o $(T1) $(T1).c

$(T2): $(T2).c
	$(CC) $(CFLAGS) -o $(T2) $(T2).c

clean:
	$(RM) $(TARGET)