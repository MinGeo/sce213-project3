CC = gcc
CFLAGS = -g -c
CFLAGS += -Wall -Wextra -Wno-unused-parameter -Werror -std=gnu99
TARGET = pa3
LDFLAGS =
OBJS = malloc.o parser.o pa3.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	gcc $(CFLAGS) $< -o $@

.PHONY : clean
clean :
	rm -rf $(OBJS) $(TARGET)

test: $(TARGET) test-short1 test-short2 test-coalescing test-realloc1 test-realloc2

test-short1: $(TARGET) test-first-short1 test-best-short1
test-short2: $(TARGET) test-first-short2 test-best-short2
test-coalescing: $(TARGET) test-first-coalescing test-best-coalescing
test-realloc1: $(TARGET) test-first-realloc1 test-best-realloc1
test-realloc2: $(TARGET) test-first-realloc2 test-best-realloc2


test-first-short1: $(TARGET)
	@echo "Test short1 on first fit"; \
	./$(TARGET) first < test_cases/short1.rep > outputs/short1-first-answer.txt; \
	diff -Naur outputs/short1-first-answer.txt reference_outputs/short1-first-reference.txt; \
	if [ $$? -eq 0 ]; then echo "\tTest seems correct\n";\
	else echo "\tResults not identical, check the diff output\n";\
	fi

test-best-short1: $(TARGET)
	@echo "Test short1 on best fit"; \
  ./$(TARGET) best < test_cases/short1.rep > outputs/short1-best-answer.txt; \
  diff -Naur outputs/short1-best-answer.txt reference_outputs/short1-best-reference.txt; \
  if [ $$? -eq 0 ]; then echo "\tTest seems correct\n";\
  else echo "\tResults not identical, check the diff output\n";\
  fi

test-first-short2: $(TARGET)
	@echo "Test short2 on first fit"; \
	./$(TARGET) first < test_cases/short2.rep > outputs/short2-first-answer.txt; \
	diff -Naur outputs/short2-first-answer.txt reference_outputs/short2-first-reference.txt; \
	if [ $$? -eq 0 ]; then echo "\tTest seems correct\n";\
	else echo "\tResults not identical, check the diff output\n";\
	fi

test-best-short2: $(TARGET)
	@echo "Test short2 on best fit"; \
  ./$(TARGET) best < test_cases/short2.rep > outputs/short2-best-answer.txt; \
  diff -Naur outputs/short2-best-answer.txt reference_outputs/short2-best-reference.txt; \
  if [ $$? -eq 0 ]; then echo "\tTest seems correct\n";\
  else echo "\tResults not identical, check the diff output\n";\
  fi

test-first-coalescing: $(TARGET)
	@echo "Test coalescing on first fit"; \
	./$(TARGET) first < test_cases/coalescing.rep > outputs/coalescing-first-answer.txt; \
	diff -Naur outputs/coalescing-first-answer.txt reference_outputs/coalescing-first-reference.txt; \
	if [ $$? -eq 0 ]; then echo "\tTest seems correct\n";\
	else echo "\tResults not identical, check the diff output\n";\
	fi

test-best-coalescing: $(TARGET)
	@echo "Test coalescing on best fit"; \
  ./$(TARGET) best < test_cases/coalescing.rep > outputs/coalescing-best-answer.txt; \
  diff -Naur outputs/coalescing-best-answer.txt reference_outputs/coalescing-best-reference.txt; \
  if [ $$? -eq 0 ]; then echo "\tTest seems correct\n";\
  else echo "\tResults not identical, check the diff output\n";\
  fi

test-first-realloc1: $(TARGET)
	@echo "Test realloc1 on first fit"; \
	./$(TARGET) first < test_cases/realloc1.rep > outputs/realloc1-first-answer.txt; \
	diff -Naur outputs/realloc1-first-answer.txt reference_outputs/realloc1-first-reference.txt; \
	if [ $$? -eq 0 ]; then echo "\tTest seems correct\n";\
	else echo "\tResults not identical, check the diff output\n";\
	fi

test-best-realloc1: $(TARGET)
	@echo "Test realloc1 on best fit"; \
  ./$(TARGET) best < test_cases/realloc1.rep > outputs/realloc1-best-answer.txt; \
  diff -Naur outputs/realloc1-best-answer.txt reference_outputs/realloc1-best-reference.txt; \
  if [ $$? -eq 0 ]; then echo "\tTest seems correct\n";\
  else echo "\tResults not identical, check the diff output\n";\
  fi

test-first-realloc2: $(TARGET)
	@echo "Test realloc2 on first fit"; \
	./$(TARGET) first < test_cases/realloc2.rep > outputs/realloc2-first-answer.txt; \
	diff -Naur outputs/realloc2-first-answer.txt reference_outputs/realloc2-first-reference.txt; \
	if [ $$? -eq 0 ]; then echo "\tTest seems correct\n";\
	else echo "\tResults not identical, check the diff output\n";\
	fi

test-best-realloc2: $(TARGET)
	@echo "Test realloc2 on best fit"; \
  ./$(TARGET) best < test_cases/realloc2.rep > outputs/realloc2-best-answer.txt; \
  diff -Naur outputs/realloc2-best-answer.txt reference_outputs/realloc2-best-reference.txt; \
  if [ $$? -eq 0 ]; then echo "\tTest seems correct\n";\
  else echo "\tResults not identical, check the diff output\n";\
  fi
