# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nflan <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/09 10:58:36 by nflan             #+#    #+#              #
#    Updated: 2022/12/08 14:00:12 by nflan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Container

INC_DIR =		incs/
OBJ_DIR =		obj
OBJ_DIR_STD =		obj_std
SRC_DIR =		srcs

INC =			$(addsuffix .hpp, $(addprefix $(INC_DIR), vector stack viterator tools iterator reverse_viterator rbtree rbiterator))
SRC =			$(SRC_FT:%=$(SRC_DIR)/%.cpp)
OBJ =			$(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
OBJ_STD =			$(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR_STD)%.o)

CXX = c++ $(CXXFLAGS)

RM = rm -fr

CXXFLAGS = -Wall -Wextra -Werror -g -std=c++98

.c.o:
	$(CXX) -c $< -o $(<:.cpp=.o)

#HOW TO LIST .c 
#	ls -l | awk '{print $9}' | grep -E ".cpp$"| sed "s/\.cpp/ \\\/g" | sed '$s/\\$//g'

SRC_FT = main

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $@
$(OBJ_DIR_STD):
	mkdir -p $@

$(OBJ) : $(INC) | $(OBJ_DIR)
$(OBJ_STD) : $(INC) | $(OBJ_DIR_STD)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@
$(OBJ_DIR_STD)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -D NAMESPACE=std -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ_DIR_STR) $(SRC) $(OBJ) $(OBJ_STD)
	$(CXX) $(OBJ) -o $@
	$(CXX) -D NAMESPACE=std $(OBJ_STD) -o $@_std

clean:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(OBJ_DIR_STD)
	@echo "Cleaned object"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME)_std
	@$(RM) tests
	@echo "Cleaned program"

re: fclean all

define print_aligned_coffee
    @t=$(NAME); \
	l=$${#t};\
	i=$$((8 - l / 2));\
	echo "             \0033[1;32m\033[3C\033[$${i}CAnd Your program \"$(NAME)\" "
endef

coffee: all clean
	@echo ""
	@echo "                                {"
	@echo "                             {   }"
	@echo "                              }\0033[1;34m_\0033[1;37m{ \0033[1;34m__\0033[1;37m{"
	@echo "                           \0033[1;34m.-\0033[1;37m{   }   }\0033[1;34m-."
	@echo "                          \0033[1;34m(   \0033[1;37m}     {   \0033[1;34m)"
	@echo "                          \0033[1;34m| -.._____..- |"
	@echo "                          |             ;--."
	@echo "                          |            (__  \ "
	@echo "                          |             | )  )"
	@echo "                          |   \0033[1;96mCOFFEE \0033[1;34m   |/  / "
	@echo "                          |             /  / "
	@echo "                          |            (  / "
	@echo "                          \             | "
	@echo "                            -.._____..- "
	@echo ""
	@echo ""
	@echo "\0033[1;32m\033[3C                    Take Your Coffee"
	$(call print_aligned_coffee)

.SECONDARY: $(OBJ) $(OBJ_DIR) $(OBJ_STD) $(OBJ_DIR_STD)
.PHONY: all clean fclean re coffee
