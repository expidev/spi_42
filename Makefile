CC = gcc
CFLAGS = -Wall -Wextra -Werror

CLIENT_SRC = client.c
SERVER_SRC = server.c

CLIENT_OBJ = client.o
SERVER_OBJ = server.o

all: client server

client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o client $(CLIENT_OBJ)

server: $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o server $(SERVER_OBJ)

$(CLIENT_OBJ): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -c $(CLIENT_SRC) -o $(CLIENT_OBJ)

$(SERVER_OBJ): $(SERVER_SRC)
	$(CC) $(CFLAGS) -c $(SERVER_SRC) -o $(SERVER_OBJ)

clean:
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ)

fclean: clean
	rm -f client server

re: fclean all
