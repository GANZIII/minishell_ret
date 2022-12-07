NAME := minishell

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# LIBS        libraries to be used
# LIBS_TARGET libraries to be built
#
# INCS        header file locations
#
# SRC_DIR     source directory
# SRCS        source files
#
# BUILD_DIR   build directory
# OBJS        object files
# DEPS        dependency files
#
# CC          compiler
# CFLAGS      compiler flags
# CPPFLAGS    preprocessor flags
# LDFLAGS     linker flags
# LDLIBS      libraries name

LIBS        := ft readline
LIBS_TARGET :=            \
    lib/libft/libft.a

INCS        := include    \
    lib/libft/ \

SRC_DIR     := src
SRCS        := main.c signal.c \
	tokenize/list.c tokenize/tokenize.c tokenize/quote.c \
	tokenize/tokenize2.c \
	tokenize/utils_str.c tokenize/quote2.c tokenize/envp.c \
	tokenize/utils_str3.c tokenize/utils_str4.c tokenize/str.c \
	eval/eval.c eval/eval_io_redirection.c eval/eval_io_redirection_utils.c \
	eval/eval_builtin.c eval/eval_builtin_env.c eval/eval_simple_command.c \
	eval/eval_builtin_export.c \
	ast/ast_utils.c ast/ast.c ast/ast_io_redirect.c ast/ast_simple_command.c \
	ast/ast_wwkaxhd.c \
	msh_utils/exit.c msh_utils/msh_utils.c
SRCS        := $(SRCS:%=$(SRC_DIR)/%)


BUILD_DIR   := .build
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g
CPPFLAGS    += $(addprefix -I,$(INCS)) -MMD -MP 
LDFLAGS     += $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      := $(addprefix -l,$(LIBS))

# LDFLAGS += -L/goinfre/seonghyk/homebrew/opt/readline/lib
# CPPFLAGS += "-I/goinfre/seonghyk/homebrew/opt/readline/include

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKEFLAGS make flags
# DIR_DUP   duplicate directory tree

RM          := rm -f
MAKEFLAGS   += --silent --no-print-directory
DIR_DUP     = mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   link .o -> archive
# $(LIBS)   build libraries
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal
# run       run the program
# info      print the default goal recipe

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(info CREATED $(NAME))

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<	 
	$(info CREATED $@)

-include $(DEPS)

clean:
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: compile_commands.json
compile_commands.json:
	-$(MAKE) --always-make --keep-going all
	(echo '[' && find ./ -name '*.part.json' -exec cat {} \;  && echo ']') > $@