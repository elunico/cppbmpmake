
all: test prod

test: prod test/test.cpp
	clang++ -std=gnu++17 -Og -g -o test/test -lcriterion -I/usr/local/Cellar/criterion/2.4.1/include/ color.cpp image.cpp ibmp.cpp test/test.cpp

main: prod main.cpp
	clang++ -std=gnu++17 -Og -g -o main color.cpp image.cpp main.cpp ibmp.cpp


prod: color.h color.cpp image.h image.cpp ibmp.h ibmp.cpp
	clang++ -std=gnu++17 -Og -g -c color.cpp image.cpp ibmp.cpp
