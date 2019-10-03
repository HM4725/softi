.SUFFIXES: .cpp .o

CC=g++

SRCDIR=./src/
INC=./include/
LIBS=./lib/
BIN=./bin/

# main source file
TARGET_SRC:=$(SRCDIR)main.cpp
TARGET_OBJ:=$(SRCDIR)main.o
STATIC_LIB:=$(LIBS)libbpt.a
DYNAMIC_LIB:=$(LIBS)libbpt.so

# Include more files if you write another source file.
SRCS_FOR_LIB:= \
	$(SRCDIR)find_node.cpp \
	$(SRCDIR)global_vars.cpp \
	$(SRCDIR)delete.cpp \
	$(SRCDIR)insert.cpp \
	$(SRCDIR)api_ext.cpp \
	$(SRCDIR)db.cpp \
	$(SRCDIR)buffer.cpp \
	$(SRCDIR)file.cpp \
	$(SRCDIR)single_join.cpp \
	$(SRCDIR)join.cpp

OBJS_FOR_LIB:=$(SRCS_FOR_LIB:.cpp=.o)

CFLAGS+= -g -fPIC -std=c++11 -I $(INC)

TARGET=$(BIN)dbms

all: $(TARGET)

$(TARGET): $(TARGET_OBJ) $(STATIC_LIB)
	$(CC) $(CFLAGS) $< -o $@ -L $(LIBS) -lbpt

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -c -o $@

clean:
	rm -rf $(TARGET) $(TARGET_OBJ) $(OBJS_FOR_LIB) $(LIBS)*

$(DYNAMIC_LIB):	$(OBJS_FOR_LIB)
	g++ -shared -Wl,-soname,libbpt.so -o $@ $(OBJS_FOR_LIB)

$(STATIC_LIB):	$(OBJS_FOR_LIB)
	ar cr $@ $^

