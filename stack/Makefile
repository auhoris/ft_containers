name	= stack

srcdir	= srcs
objdir	= objs
incdir	= $(srcdir)/includes

inclds	= stack.hpp
srcs	= main.cpp
sources = $(addprefix $(srcdir)/, $(srcs))
incld	= $(addprefix $(incdir)/, $(inclds))

objects	= $(sources:$(srcdir)/%.cpp=$(objdir)/%.o)
deps		=  $(objects:%.o=%.d)

linker	= clang++
flags	= -Wall -Wextra -Werror -g -std=c++98
sanit	= -fsanitize=address
std		= -std=c++98

all:	$(name)

$(name):	$(objects)
		@$(linker) $(flags) $^ -o $@
		@echo "\033[0;32m"$@" compiled"

-include $(deps)
$(objdir)/%.o:	$(srcdir)/%.cpp Makefile
		@mkdir -p $(objdir)
		@$(linker) $(flags) -MMD -c $< -o $@
		@echo "Compiled "$<" successfully!"

clean:
		rm -rf $(objdir)

fclean:	clean
		rm -f $(name)

re:		fclean all

leaks:
	@leaks --atExit -- ./$(name)
