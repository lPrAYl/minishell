NAME			= 	minishell

SRCS			=	./sources/builtins/minishell.c	\
					./sources/builtins/echo.c	./sources/builtins/pwd.c\
					./sources/builtins/exit.c	./sources/builtins/env.c\
					./sources/builtins/export.c	./sources/builtins/unset.c\
					./sources/builtins/cd.c\
					./sources/builtins/utils.c\
					./sources/builtins/list_to_array.c\
					./parsing/changeLetter.c	./parsing/parser_red.c	\
					./parsing/parser_split.c	./parsing/parser_str.c\
					./parsing/parser_token.c\
					./parsing/parser_urils1.c	./parsing/parser.c	\
					./parsing/preparser.c	./parsing/token.c \
					./parsing/signals_interactive_shell.c	./parsing/signals_non_interactive_shell.c

OBJS			=	$(SRCS:.c=.o)

HEADERS			=	-I./includes/ -I./libft/

CC				=	gcc

RM				=	rm -rfv

CFLAGS			=	-Wall -Wextra -Werror -I ~/.brew/opt/readline/include/

LIBS			=	./libft/libft.a
RDL				= 	-lreadline
RDL_MAC			= 	-lreadline -L ~/.brew/opt/readline/lib

all:			$(NAME)

%.o:			%.c
				$(CC) $(CFLAGS) -c -g $< -o $@ $(HEADERS)

$(NAME):		$(OBJS) ./includes/minishell.h ./includes/parser.h ./libft/libft.h
				cd ./libft/ && $(MAKE)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(HEADERS) $(RDL_MAC)

clean:
				$(MAKE) clean -C ./libft/
				$(RM) $(OBJS)
				@echo "\033[36;1m\nCleaning succeed\n\033[0m"

fclean:			clean
				$(MAKE) fclean -C ./libft/
				$(RM) $(NAME)
				@echo "\033[32;1m\nAll created files were deleted\n\033[0m"

re:				fclean $(NAME)
				@echo "\033[35;1m\nRemake done\n\033[0m"

.PHONY:			all clean fclean r





# NAME					=	minishell
# NAME_BONUS				=

# GCC						=	gcc -Wall -Wextra -Werror -g
# INCLUDES				=	-I$(HEADERS_DIRECTORY)
# INCLUDES_BONUS			=	-I$(HEADERS_DIRECTORY)

# HEADERS_LIST			=	minishell.h parsing.h
# HEADERS_BONUS_LIST		=
# HEADERS_DIRECTORY		= 	./includes/
# HEADERS_DIRECTORY_BONUS	=	./includes/
# HEADERS					=	$(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))
# HEADERS_BONUS			=	$(addprefix $(HEADERS_DIRECTORY_BONUS), $(HEADERS_BONUS_LIST))

# SOURCES_LIST			=	sourses/builtins/minishell.c	\
# 							sourses/builtins/echo.c	sourses/builtins/pwd.c\
# 							sourses/builtins/exit.c	sourses/builtins/env.c\
# 							sourses/builtins/export.c	sourses/builtins/unset.c\
# 							sourses/builtins/cd.c\
# 							sourses/builtins/utils.c\
# 							sourses/builtins/list_to_array.c\
# 							parsing/changeLetter.c	parsing/parser_red.c	\
# 							parsing/parser_split.c	parsing/parser_str.c\
# 							parsing/parser_urils1.c	parsing/parser.c	\
# 							parsing/preparser.c	token.c
				
# #SOURCES_DIRECTORY		=	
# #SOURCES_LIST_BONUS		=
# #SOURCES_DIRECTORY_BONUS	=	./bonus/
# #SOURCES					=	$(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))
# #SOURCES_BONUS			=	$(addprefix $(SOURCES_DIRECTORY_BONUS), $(SOURCES_LIST_BONUS))

# OBJECTS_LIST			=	$(patsubst %.c, %.o, $(SOURCES_LIST))
# OBJECTS_DIRECTORY		=	
# OBJECTS					=	$(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))
# OBJECTS_LIST_BONUS		=	$(patsubst %.c, %.o, $(SOURCES_LIST_BONUS))
# OBJECTS_DIRECTORY_BONUS	=	./bonus/objects/
# OBJECTS_BONUS			=	$(addprefix $(OBJECTS_DIRECTORY_BONUS), $(OBJECTS_LIST_BONUS))

# LIBFT					=	./libft/libft.a
# LIBFTFLAGS				=	-L ./libft -lft

# #COLORS
# GREEN					=	\033[0;32m
# RED						=	\033[0;31m
# RESET					=	\033[0m

# all						:	$(NAME) $(LIBFT)

# $(LIBFT)				:	./libft/*.c ./libft/*.h
# 							@$(MAKE) -C ./libft/
# 							@$(MAKE) clean -C ./libft

# $(NAME)					:	$(OBJECTS_DIRECTORY) $(OBJECTS) $(HEADER) $(LIBFT)
# 							@$(GCC) $(INCLUDES) $(OBJECTS) $(LIBFTFLAGS) -lreadline -o $(NAME)
# 							@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
# 							@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

# $(OBJECTS_DIRECTORY)	:
# 							@mkdir -p $(OBJECTS_DIRECTORY)
# 							@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

# $(OBJECTS_DIRECTORY)%.o	:	$(SOURCES_DIRECTORY)%.c $(HEADERS) $(LIBFT)
# 							@$(GCC) -c $(INCLUDES) $< -o $@
# 							@echo "$(GREEN).$(RESET)\c"

# bonus					:	$(NAME_BONUS)

# $(NAME_BONUS)			:	$(OBJECTS_DIRECTORY_BONUS) $(OBJECTS_BONUS) $(HEADERS_BONUS)  $(LIBFT)
# 							@$(GCC) $(INCLUDES_BONUS) $(OBJECTS_BONUS) $(LIBFTFLAGS) -lreadline -o $(NAME_BONUS)
# 							@echo "\n$(NAME_BONUS): $(GREEN)object files were created$(RESET)"
# 							@echo "$(NAME_BONUS): $(GREEN)$(NAME_BONUS) was created$(RESET)"

# $(OBJECTS_DIRECTORY_BONUS)		:
# 							@mkdir -p $(OBJECTS_DIRECTORY_BONUS)
# 							@echo "$(NAME_BONUS): $(GREEN)$(OBJECTS_DIRECTORY_BONUS) was created$(RESET)"

# $(OBJECTS_DIRECTORY_BONUS)%.o	:	$(SOURCES_DIRECTORY_BONUS)%.c $(HEADERS_BONUS)
# 							@$(CC) $(FLAGS) -c $(INCLUDES_BONUS) $< -o $@
# 							@echo "$(GREEN).$(RESET)\c"

# clean					:
# 							@rm -rf $(OBJECTS_DIRECTORY)
# 							@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
# 							@echo "$(NAME): $(RED)object files were deleted$(RESET)"
# 							@rm -rf $(OBJECTS_DIRECTORY_BONUS)
# 							@echo "$(NAME_BONUS): $(RED)$(OBJECTS_DIRECTORY_BONUS) was deleted$(RESET)"
# 							@echo "$(NAME_BONUS): $(RED)object files were deleted$(RESET)"

# fclean					:	clean
# 							@rm -f $(NAME)
# 							@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"
# 							@rm -f $(NAME_BONUS)
# 							@echo "$(NAME_BONUS): $(RED)$(NAME_BONUS) was deleted$(RESET)"

# re						:	fclean all

# norm					:
# 							@echo "\033[46m\033[30mNORMINETTE$(RESET)";
# 							norminette *.h *.c;

# .PHONY					:	all clean fclean re	bonus	norm
