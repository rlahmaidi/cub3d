NAME = cub3d

FLAGS = -Werror -Wextra -Wall

SRCS =  srcs/cub3d.c \
		errors/errors_map.c \
		errors/errors_map_1.c \
		errors/check/check.c \
		errors/check/check_1.c \
		errors/check/check_2.c \
		srcs/lexer/lexer_collection_map.c \
		srcs/lexer/lexer_collection_texture.c \
		srcs/lexer/lexer_tools.c \
		srcs/syntax/check_for_syntax_map.c \
		srcs/syntax/check_syntax.c \
		srcs/lexer/lexer.c \
		srcs/token/token.c \
		srcs/start/start.c \
		srcs/start/reycasting/tools_1.c \
		srcs/start/reycasting/ray_cast.c \
		srcs/start/tools/tools_mlx.c \
		srcs/start/tools/tools_change_player_position.c \
		srcs/start/tools/tools_move_position_player.c \
		tools/tool_1.c \
		tools/tool_2.c \
		tools/tool_3.c \
		tools/get_next_line.c \


OBJS = $(SRCS:.c=.o)

MLX_FLAGS = -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -I /usr/local/include

OBJS	= 	$(SRCS:.c=.o)

HEADER = includes/cub3d.h

all: lib $(NAME)
	@make -C ./libft 

lib: 
	@make -C ./libft 

$(NAME): $(OBJS)
		@gcc ${FLAGS} $(OBJS) ./libft/libft.a $(MLX_FLAGS) -o ${NAME}

.c.o: $(SRCS)
	@gcc ${FLAGS} -I $(HEADER) -c $< -o $@

start:
	@make run && make clean
run:
	@make re && ./cub3d maps/no_map.cub

run_1:
	@make re && make clean && ./cub3d maps/test.cub

run_2:
	@make re && make clean && ./cub3d maps/test.cub

clean:
	@rm -rf $(OBJS)

fclean: clean
	@make -C ./libft fclean
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re