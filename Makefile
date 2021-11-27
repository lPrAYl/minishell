NAME			= 	minishell

SRCS			= 	${shell find ./sources ./parsing -name "*.c"}
HDRS			=	${shell find ./includes -name "*.h"}

INCS		=		-I./includes -I./libft/
GCC				=	gcc -Wall -Wextra -Werror

LIBFT			=	./libft/libft.a
LFLAGS			=	-L ./libft -lft

#COLORS
GREEN			=	\033[32;1m
BLUE			=	\033[36;1m
PURPLE			=	\033[35;1m
RESET			=	\033[0m

RDL_INC			=	-I ~/.brew/opt/readline/include/
RDL				=	-lreadline -L ~/.brew/opt/readline/lib $(RDL_INC)

all				:	$(NAME) $(LIBFT)

$(LIBFT)		:	./libft/*.c ./libft/*.h
					@$(MAKE) -C ./libft/
					@$(MAKE) clean -C ./libft

OBJS			=	$(patsubst %.c, %.o, $(SRCS))

%.o:				%.c
					$(GCC) $(RDL_INC) -c -g $< -o $@

$(NAME)			:	$(OBJS) $(HDRS) $(LIBFT)
					@$(GCC) $(INCS) $(OBJS) $(LFLAGS) -o $(NAME) $(RDL)
					@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
					@echo "$(NAME): $(GREEN)project was created$(RESET)\n"

clean			:
					@rm -rvf $(OBJS)
					@echo "\n$(NAME): $(BLUE)object files were deleted$(RESET)\n"

fclean			:	clean
					@rm -f $(NAME)
					@echo "$(NAME): $(PURPLE)project remake done$(RESET)\n"

re				:	fclean all

norm			:
					@echo "\033[46m\033[30mNORMINETTE$(RESET)"
					norminette ${shell find ./ -name "*.c *.h"}

.PHONY			:	all clean fclean re	bonus	norm
