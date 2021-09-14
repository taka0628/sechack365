CXX = g++

TARGET	= test.out

SRCDIR = ../src

SRCS	= key_list_c.cpp\
	dynamic_mem_c.cpp\
	file_ptr_c.cpp\
	sha_c.cpp\
	file_enc.cpp\
	aes_c.cpp\
	key_gen_c.cpp

TESTSRC	= test.cpp \
	keyGenTest.cpp

OBJDIR = build

OBJS	= ${SRCS:%.cpp=${OBJDIR}/%.o} ${TESTSRC:%.cpp=${OBJDIR}/%.o}

LDGFLAGS	= -lpthread \
	-lgtest_main \
	-lgtest

LDFLAGS	= -lcrypto \
	-lssl \
	-pthread

CFLAGS	= -Wall\
	-std=c++11


${TARGET}: ${OBJS}
	${CXX} -o $@ $^ ${LDFLAGS} ${LDGFLAGS}

${OBJDIR}/%.o: $(SRCDIR)/%.cpp
	mkdir -p build
	cd build;\
	${CXX} -c ../$^ ${CFLAGS}

${OBJDIR}/%.o: %.cpp
	mkdir -p build
	cd build;\
	${CXX} -c ../$^ ${CFLAGS}

# %.o: ${addprefix ${SRCDIR},${SRCS}} ${TESTSRC}
# 	mkdir -p build
# 	cd build;\
# 	${CXX} ${addprefix ../, ${TESTSRC}} -c ${addprefix ../${SRCDIR},${SRCS}} ${CFLAGS}

run: ${TARGET}
	./${TARGET}

clean:
	rm -rf ${OBJDIR}/*.o ${TARGET}