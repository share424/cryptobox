ALIB=cryptobox.a
SLIB=cryptobox.so
OBJDIR=./obj/
TEST_TARGET=cryptobox

CC=g++
AR=ar
CCFLAGS=-g -Wall
ARFLAGS=rcs

HASH_OBJ=md5.o

TEST_OBJ=main.o

OBJ=$(HASH_OBJ)

HASH_DIR=$(wildcard src/hash/*.cpp)
TEST_DIR=$(wildcard test/*.cpp)
OBJS=$(addprefix $(OBJDIR), $(OBJ))
HASH_OBJS=$(addprefix $(OBJDIR), $(HASH_OBJ))
TEST_OBJS=$(addprefix $(OBJDIR), $(TEST_OBJ))
DEPS=Makefile

test: obj $(TEST_TARGET)

all: obj $(ALIB) $(SLIB)

$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

$(TEST_OBJS): $(TEST_DIR)
	$(CC) $(CCFLAGS) -c $< -o $@

$(SLIB): $(OBJS)
	$(CC) $(CCFLAGS) -shared $^ -o $@

$(ALIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $<

$(HASH_OBJS): $(HASH_DIR)
	$(CC) $(CCFLAGS) -c $< -o $@

obj:
	mkdir -p obj

.PHONY: clean

clean:
	rm -f $(OBJS) $(OBJDIR)/*
