COMPIL = gcc
FLAG = -Wall -pthread
NAME = server

all: $(NAME)

$(NAME).o: $(NAME).h $(NAME).c
	$(COMPIL) -c $(FLAG) $(NAME).c

$(NAME): $(NAME).o
	$(COMPIL) $(FLAG) $(NAME).o -o $(NAME)

clean:
	rm $(NAME).o $(NAME)
