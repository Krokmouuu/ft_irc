NAME =		ircserv

COMP =		c++
CFLAGS =	-Wall -Werror -Wextra -fsanitize=address -std=c++98 -lcurl

SRCS =		*.cpp

OBJS =		$(SRCS:%.cpp=%.o)

$(NAME):	$(SRCS)
	$(COMP) $(CFLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY: all clean fclean re