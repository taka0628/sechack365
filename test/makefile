CXX = g++

TARGET	= test.out

SRCDIR = ../src/

SRCS	= key_list_c.cpp\
	dynamic_mem_c.cpp\
	file_ptr_c.cpp\
	sha_c.cpp\
	file_enc.cpp\
	aes_c.cpp

TESTSRC	= test.cpp

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

${OBJS}: ${addprefix ${SRCDIR},${SRCS}} ${TESTSRC}
	mkdir -p build
	cd build;\
	${CXX} ../${TESTSRC} -c ${addprefix ../${SRCDIR},${SRCS}} ${CFLAGS}

run: ${TARGET}
	./${TARGET}

clean:
	rm -rf ${OBJDIR}/*.o ${TARGET}