# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 15:18:15 by olcherno          #+#    #+#              #
#    Updated: 2025/11/03 17:29:37 by olcherno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc # cc 
CFLAGS = -g -Wall -Wextra -Werror
NAME = philo
SRCDIR = src
OBJDIR = obj
LIBFTDIR = libs/libft
FTPRINTF_DIR = libs/libftprintf

SRC= main.c parsing.c philo_init.c table.c  utils.c routine.c monitor_routine.c


OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
SRCS = $(addprefix $(SRCDIR)/, $(SRC))

# Rules of files
$(NAME): $(OBJS) $(LIBFTDIR)/libft.a $(FTPRINTF_DIR)/libftprintf.a
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFTDIR) -lft -L$(FTPRINTF_DIR) -lftprintf -lreadline -o $(NAME)

# Create necessary directories for object files
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(SRCDIR) -I$(LIBFTDIR) -I$(FTPRINTF_DIR) -c $< -o $@

# Rules to build the libraries # making makefile of libft
$(LIBFTDIR)/libft.a:
	$(MAKE) -C $(LIBFTDIR) 

$(FTPRINTF_DIR)/libftprintf.a:    # making makefile of printf
	$(MAKE) -C $(FTPRINTF_DIR)

# Rules of actions
.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(FTPRINTF_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	$(MAKE) -C $(FTPRINTF_DIR) fclean

re: fclean all