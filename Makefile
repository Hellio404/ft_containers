CC      = c++
FLAGS   = -Wall -Wextra -Werror -Iincludes -std=c++98 
SRCS = utils/utils_tree.cpp 

SRC_MAP = map.spec.cpp
SRC_SET = set.spec.cpp
SRC_VEC = vector.spec.cpp
SRC_STACK = stack.spec.cpp

OBJS = $(SRCS:.cpp=.o)

OBJ_MAP = $(SRC_MAP:.cpp=.o)
OBJ_SET = $(SRC_SET:.cpp=.o)
OBJ_VEC = $(SRC_VEC:.cpp=.o)
OBJ_STACK = $(SRC_STACK:.cpp=.o)


all: map set vector stack

map: $(OBJS) $(OBJ_MAP)
	$(CC) $(FLAGS) $(OBJS) $(OBJ_MAP) -D NAMESPACE=ft -o map
	$(CC) $(FLAGS) $(OBJS) $(OBJ_MAP) -D NAMESPACE=std -o map.std

set: $(OBJS) $(OBJ_SET)
	$(CC) $(FLAGS) $(OBJS) $(OBJ_SET) -D NAMESPACE=ft -o set
	$(CC) $(FLAGS) $(OBJS) $(OBJ_SET) -D NAMESPACE=std -o set.std

vector: $(OBJS) $(OBJ_VEC)
	$(CC) $(FLAGS) $(OBJS) $(OBJ_VEC) -D NAMESPACE=ft -o vector
	$(CC) $(FLAGS) $(OBJS) $(OBJ_VEC) -D NAMESPACE=std -o vector.std

stack: $(OBJS) $(OBJ_STACK)
	$(CC) $(FLAGS) $(OBJS) $(OBJ_STACK) -D NAMESPACE=ft -o stack
	$(CC) $(FLAGS) $(OBJS) $(OBJ_STACK) -D NAMESPACE=std -o stack.std

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(FLAGS_DEBUG) -o $(NAME) $(OBJS)

%.o: %.cpp $(HEADS)
	$(CC) $(FLAGS) $(FLAGS_DEBUG) -c -o $@ $<
clean:
	rm -rf $(OBJS) $(OBJ_MAP) $(OBJ_SET) $(OBJ_VEC) $(OBJ_STACK) 
fclean: clean
	rm -rf $(NAME) map set vector stack map.std set.std vector.std stack.std
re: fclean all
