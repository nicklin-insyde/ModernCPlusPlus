TARGET=app

ifeq (${OPTION},cross_compile)
	CPP:=${CROSS_COMPILE}g++
else
	CPP:=g++
endif

FILE = sync_queue main tree

SRCS := $(foreach item, $(FILE), $(item).cpp)
OBJS := $(foreach item, $(FILE), $(item).o)

COMP_OPTIONS := -Wall -Wno-unused-result -O0 -fpermissive -std=c++17

LDFLAGS := -pthread

all: compile_hint .depend $(TARGET)

compile_hint:
	# You must "export LD_LIBRARY_PATH=/home/nicklin/sandbox/math/lib/share/"
	# to let AP link to library at run-time.

${TARGET}: ${OBJS}
	${CPP} ${LDFLAGS} ${OBJS} -g -o ${TARGET}
	#@if [ "${OPTION}" = "cross_compile" ]; then \
	#	cp -v ${TARGET} /mnt/nfs; \
	#fi

${OBJS}:
	${CPP} -g -c ${COMP_OPTIONS} ${SRCS}

.depend dep:
	$(CPP) -MM $(SRCS) > .depend
	@chmod 644 .depend

clean:
	@if [ -e ${TARGET} ]; then \
		rm -v ${TARGET}; \
	fi
	@rm -v ${OBJS}

include .depend
