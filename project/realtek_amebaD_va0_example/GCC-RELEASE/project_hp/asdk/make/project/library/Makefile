
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean lib clean_lib

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
#add your include path here
IFLAGS += #-I$(BASEDIR)/component/common/network/coap/include

#set your source code path here
CUSTOM_SRC_DIR = $(BASEDIR)/../../src

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CUSTOM_SRCS_C   := $(shell find $(CUSTOM_SRC_DIR) -name "*.c")
CUSTOM_SRCS_CXX := $(shell find $(CUSTOM_SRC_DIR) -name "*.cpp")
OBJS += $(CUSTOM_SRCS_C:.c=.o) $(CUSTOM_SRCS_CXX:.cpp=.o)

#*****************************************************************************#
#                               Dependency	                              #
#*****************************************************************************#
-include $(OBJS:.o=.d)

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

clean_lib:
	$(REMOVE) $(ROOTDIR)/lib/application/lib_user.a

# Define the Rules to build the core targets
lib: CORE_TARGETS
	$(AR) rvs lib_user.a $(OBJS) $(OBJS_SRAM)
	$(MOVE) -f lib_user.a $(ROOTDIR)/lib/application

all: lib clean

#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS: clean_lib $(OBJS)

#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS 
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.ii
	$(REMOVE) *.s
	$(REMOVE) *.su
	$(REMOVE) *.d
	$(REMOVE) $(CUSTOM_SRC_DIR)/*.o
	$(REMOVE) $(CUSTOM_SRC_DIR)/*.i
	$(REMOVE) $(CUSTOM_SRC_DIR)/*.ii
	$(REMOVE) $(CUSTOM_SRC_DIR)/*.s
	$(REMOVE) $(CUSTOM_SRC_DIR)/*.su
	$(REMOVE) $(CUSTOM_SRC_DIR)/*.d
