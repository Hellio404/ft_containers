NAME    = test
CC      = g++-11
FLAGS   = -Wall -Wextra -Werror -Iincludes -std=c++98 -Wno-unused-parameter -Wno-unused-local-typedefs -Wno-unused-variable
SRCS = test.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(FLAGS_DEBUG) -o $(NAME) $(OBJS)

%.o: %.cpp $(HEADS)
	$(CC) $(FLAGS) $(FLAGS_DEBUG) -c -o $@ $<
clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
re: fclean all
