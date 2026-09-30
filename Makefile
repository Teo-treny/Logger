# Compilateur et options
CC = gcc
CC_WIN = x86_64-w64-mingw32-gcc
AR = ar
AR_WIN = x86_64-w64-mingw32-ar
AR_NAME = logger
CFLAGS = -Wall -Wextra -fPIC -I./include -I./include/logger

# Chemins
DIR_SRC 	= src
DIR_BUILD	= build
DIR_EXAMPLE = examples
DIR_INCLUDE = include/logger
DIR_TEST 	= tests

# Fichiers cibles
SRCS = $(DIR_SRC)/logger.c
OBJS = $(DIR_BUILD)/logger.o

LIB_NAME 		= liblogger
STATIC_LIB 		= $(DIR_BUILD)/$(LIB_NAME).a
STATIC_LIB_WIN 	= $(DIR_BUILD)/$(LIB_NAME)_win.a
SHARED_LIB 		= $(DIR_BUILD)/$(LIB_NAME).so
EXAMPLES 		= $(DIR_BUILD)/example1.e
TEST 			= 

# Règles
.PHONY: all clean prebuild

all : prebuild $(STATIC_LIB) $(SHARED_LIB) $(EXAMPLES)

windows : clean prebuild
	$(MAKE) CC=$(CC_WIN) AR=$(AR_WIN) STATIC_LIB=$(STATIC_LIB_WIN) $(STATIC_LIB_WIN)
	@mkdir -p $(DIR_BUILD)/win/logger
	@mkdir -p $(DIR_BUILD)/win/logger/lib
	@mkdir -p $(DIR_BUILD)/win/logger/include
	@mv $(STATIC_LIB_WIN) $(DIR_BUILD)/win/logger/lib
	@cp $(DIR_INCLUDE)/logger.h $(DIR_BUILD)/win/logger/include

linux : clean prebuild $(STATIC_LIB) $(SHARED_LIB)
	@mkdir -p $(DIR_BUILD)/linux/logger
	@mkdir -p $(DIR_BUILD)/linux/logger/lib
	@mkdir -p $(DIR_BUILD)/linux/logger/include
	@mv $(STATIC_LIB) $(DIR_BUILD)/linux/logger/lib
	@mv $(SHARED_LIB) $(DIR_BUILD)/linux/logger/lib
	@cp $(DIR_INCLUDE)/logger.h $(DIR_BUILD)/linux/logger/include


package : clean
	zip -r $(AR_NAME).zip *

test : prebuild $(TEST)

prebuild :
	@mkdir -p $(DIR_BUILD)

$(DIR_BUILD)/%.o : $(DIR_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(STATIC_LIB) : $(OBJS)
	$(AR) rcs $@ $^

$(SHARED_LIB) : $(OBJS)
	$(CC) -shared -o $@ $^

$(DIR_BUILD)/example1.e : $(DIR_EXAMPLE)/example1.c $(STATIC_LIB)
	$(CC) $(CFLAGS) $^ -o $@

clean :
	rm -rf $(DIR_BUILD)
	rm -rf $(AR_NAME).zip