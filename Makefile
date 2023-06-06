NAME = webserv


SRCDIR = src

INCDIR = inc

OBJDIR = obj


SRCS = main.cpp	\

OBJS = $(OBJDIR)/$(SRCS:.cpp=.o)

CC = c++

FLAGS = -Wall -Werror -Wextra -std=98 -pedantic # -g3 -fsanitize


all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCDIR)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
