CPP = clang++
LOCAL_CPPFLAGS = -DDEBUG -Wall -Wextra -pedantic -std=c++17 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow -Wduplicate-enum -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector -Wno-unknown-warning-option
JUDGE_CPPFLAGS = -DONLINE_JUDGE -W -O2 -std=c++17

local: $(patsubst %.cpp, %.local.out, $(wildcard *.cpp))

judge: $(patsubst %.cpp, %.judge.out, $(wildcard *.cpp))

%.local.out: %.cpp
	@echo "Compiling..."
	@$(CPP) $(LOCAL_CPPFLAGS) $< -o $(@:.out=)
	@echo "Done!"


%.judge.out: %.cpp
	@echo "Compiling... (Using g++ and the judge CodeForces FLAGS)"
	@g++-10 $(JUDGE_CPPFLAGS) $< -o $(@:.out=)
	@echo "Done!"
