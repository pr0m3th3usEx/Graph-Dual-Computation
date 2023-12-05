#
# EPITECH PROJECT, 2020
# .
# File description:
# .
#

CC					=	gcc
CFLAGS				:=	-Wall -Wextra
DEBUG_FLAGS			=	-g3 -ggdb

OBJ_DIR				=	./obj

MKDIR_P				=	mkdir -p
RM					=	rm -rf

EXEC_NAME			=	grapheDual

CPPFLAGS			=	-I./include


REL_SRC				:=	src/mesh.c \
						src/utils/str_split.c \
						# src/vertex.c \

REL_MAIN			:=	src/main.c

REL_OBJ				=	$(addprefix $(OBJ_DIR)/, $(REL_SRC:.c=.o))
REL_MAIN_OBJ		=	$(addprefix $(OBJ_DIR)/, $(REL_MAIN:.c=.o))

all:	$(EXEC_NAME)

$(EXEC_NAME): $(REL_OBJ) $(REL_MAIN_OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(EXEC_NAME) $(REL_MAIN_OBJ) $(REL_OBJ) $(LDFLAGS) && 	\
	echo "\033[32m[OK] Server compilation completed\033[39m" || 			\
	echo "\033[105m\033[35m[KO] Server compilation failed\033[49m\033[39m"

$(OBJ_DIR)/%.o: %.c
	@if [ ! -d "$(dir $@)" ]; then $(MKDIR_P) $(dir $@); fi
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $< $(LDFLAGS) &&		 	\
	echo "\033[32m[OK] $<\033[39m" || echo "\033[31m[KO] $<\033[39m"

debug:	CFLAGS	+=	$(DEBUG_FLAGS)
debug:	all

clean:
	@$(RM) $(REL_OBJ)
	@$(RM) $(REL_MAIN_OBJ)
	@echo "\033[32m[*] Cleaned\033[39m"

fclean:	clean
	@$(RM) $(EXEC_TEST)
	@echo "\033[32m[*] Full cleaned\033[39m"

re: clean all

.PHONY = 	all re clean fclean  \
			$(EXEC_NAME)