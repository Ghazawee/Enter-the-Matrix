CXX      = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -O2 -I include

HEADERS  = include/Vector.hpp include/Matrix.hpp include/lerp.hpp

# One test program per exercise.
SRCS     = ex00/main.cpp ex01/main.cpp ex02/main.cpp ex03/main.cpp ex04/main.cpp ex05/main.cpp ex06/main.cpp ex07/main.cpp ex08/main.cpp ex09/main.cpp ex10/main.cpp ex11/main.cpp ex12/main.cpp ex13/main.cpp
OBJS     = $(SRCS:.cpp=.o)
# ex00/main.cpp -> ex00/test
NAME     = $(SRCS:/main.cpp=/test)

all: $(NAME)

# One rule per binary.
ex00/test: ex00/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

ex01/test: ex01/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

ex02/test: ex02/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

ex03/test: ex03/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

ex04/test: ex04/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

ex05/test: ex05/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

ex06/test: ex06/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

ex07/test: ex07/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

ex08/test: ex08/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

ex09/test: ex09/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

ex10/test: ex10/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

ex11/test: ex11/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

ex12/test: ex12/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

ex13/test: ex13/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
