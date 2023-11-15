# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/07 14:11:40 by npaolett          #+#    #+#              #
#    Updated: 2023/11/02 14:52:43 by npaolett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
# BONUS = philo_bonus
CC = cc

RM = rm -fr

CFLAGS = -g3 -Wall -Wextra -Werror 

# INCL = -I -I./libft 

# SRC =	src/init_datas.c   \
# 		src/philo_utils.c   \
# 		src/philo_utils2.c   \
# 		src/ft_action.c		  \
# 		src/ft_creat_pthread.c \
# 		src/main.c 			    \
		
		
SRC_BONUS = src/init_philo.c \
			src/utils_bonus.c \
			src/print_utils.c  \
			src/exit_program.c  \
			src/routine_philo.c  \
			src/main.c 		      \

OBJ = $(SRC_BONUS:.c=.o)
# OBJ_BONUS = $(SRC_BONUS:.c=.o)
#	cc -o $(NAME) $(OBJ)

# LIBFT = ./libft/libft.a


$(NAME): $(OBJ)
	cc -o $(NAME) $(OBJ)

# $(BONUS): $(OBJ_BONUS)
# 	cc -o $(BONUS) $(OBJ_BONUS) 

all : $(NAME)

# bonus : $(BONUS)

%.o: %.c
	cc $(INCL) $(CFLAGS) -o $@ -c $<


# lib:
# 	make -C ./libft/ all
	
clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean 
	make all

# rebonus: fclean
# 		make bonus 

.PHONY: all clean fclean re