srcdir	= srcs
objdir	= objs
incdir	= utils

vector_n	= vector
vector_s	= $(srcdir)/ft_vector.cpp $(srcdir)/std_vector.cpp $(srcdir)/main_vector.cpp \
			  $(srcdir)/utils.cpp
vector_h	= vector.hpp
vector_o	= $(vector_s:$(srcdir)/%.cpp=$(objdir)/%.o)
vector_d	= $(vector_o:%.o=%.d)

map_n	= map
map_s	= $(srcdir)/map_main.cpp $(srcdir)/map_test.cpp $(srcdir)/utils.cpp
map_h	= map.hpp
map_o	= $(map_s:$(srcdir)/%.cpp=$(objdir)/%.o)
map_d	= $(map_o:%.o=%.d)

set_n	= set
set_s	= $(srcdir)/set_main.cpp $(srcdir)/utils.cpp
set_h	= set.hpp
set_o	= $(set_s:$(srcdir)/%.cpp=$(objdir)/%.o)
set_d	= $(set_o:%.o=%.d)


# inclds	= vector.hpp, map.hpp, stack.hpp,
# srcs	= main.cpp
# sources = $(addprefix $(srcdir)/, $(srcs))
# incld	= $(addprefix $(incdir)/, $(inclds))

# objects	= $(sources:$(srcdir)/%.cpp=$(objdir)/%.o)
# deps	= $(objects:%.o=%.d)

sanit 	= -fsanitize=address
linker	= clang++
flags	= -Wall -Wextra -Werror -g -std=c++98 #$(sanit)
sanit	= -fsanitize=address
std		= -std=c++98


# VECTOR
$(vector_n):	$(vector_o)
		@$(linker) $(flags) $^ -o $(vector_n)
		@echo "\033[0;32m"$@" compiled"

-include $(vector_d)
$(objdir)/%.o:	$(srcdir)/%.cpp Makefile
		@mkdir -p $(objdir)
		@$(linker) $(flags) -MMD -c $< -o $@
		@echo "Compiled "$<" successfully!"

# MAP
$(map_n):	$(map_o)
		@$(linker) $(flags) $^ -o $(map_n)
		@echo "\033[0;32m"$@" compiled"

-include $(map_d)
$(objdir)/%.o:	$(srcdir)/%.cpp Makefile
		@mkdir -p $(objdir)
		@$(linker) $(flags) -MMD -c $< -o $@
		@echo "Compiled "$<" successfully!"

# set
$(set_n):	$(set_o)
		@$(linker) $(flags) $^ -o $(set_n)
		@echo "\033[0;32m"$@" compiled"

-include $(set_d)
$(objdir)/%.o:	$(srcdir)/%.cpp Makefile
		@mkdir -p $(objdir)
		@$(linker) $(flags) -MMD -c $< -o $@
		@echo "Compiled "$<" successfully!"


# all:	$(name)

# $(name):	$(objects)
# 		@$(linker) $(flags) $^ -o $@
# 		@echo "\033[0;32m"$@" compiled"

# -include $(deps)
# $(objdir)/%.o:	$(srcdir)/%.cpp Makefile
# 		@mkdir -p $(objdir)
# 		@$(linker) $(flags) -MMD -c $< -o $@
# 		@echo "Compiled "$<" successfully!"

clean:
		rm -rf $(objdir)

fclean:	clean
		rm -f $(vector_n) $(map_n) $(set_n)

re:		fclean all

leaks:
	@leaks --atExit -- ./$(name)
