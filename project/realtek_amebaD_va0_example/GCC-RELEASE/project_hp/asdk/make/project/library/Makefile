
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean lib clean_lib

CUSTOM_SRC_DIR := $(BASEDIR)/../../src
USER_BUILD_DIR := $(BASEDIR)/../../build/amebad_user
USER_CACHE     := $(USER_BUILD_DIR)/init-cache.cmake

# User libraries get staged into lib/application/user/ instead of being a
# single hard-coded lib_user.a. Whatever lib*.a CMake produces from
# $(CUSTOM_SRC_DIR) lands here, and asdk/Makefile wildcard-globs them
# into LINK_APP_LIB (wrapped in --start-group). This lets the user CMake
# project add new add_library() targets without having to touch the
# SDK Makefiles.
USER_LIB_DIR   := $(ROOTDIR)/lib/application/user

clean_lib:
	rm -rf $(USER_LIB_DIR)
	rm -rf $(USER_BUILD_DIR)

# Emit a CMake init-cache that pins the cross toolchain and forwards the SDK's
# C/C++ flag sets (which already contain -I/-D from $(IFLAGS)).
$(USER_CACHE): $(MAKEFILE_LIST)
	mkdir -p $(USER_BUILD_DIR)
	@echo 'set(CMAKE_SYSTEM_NAME Generic CACHE STRING "")'                                            >  $@
	@echo 'set(CMAKE_SYSTEM_PROCESSOR arm CACHE STRING "")'                                           >> $@
	@echo 'set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY CACHE STRING "")'                         >> $@
	@echo 'set(CMAKE_C_COMPILER "$(CC)" CACHE FILEPATH "")'                                           >> $@
	@echo 'set(CMAKE_CXX_COMPILER "$(CC)" CACHE FILEPATH "")'                                         >> $@
	@echo 'set(CMAKE_AR "$(AR)" CACHE FILEPATH "")'                                                   >> $@
	@echo 'set(CMAKE_C_FLAGS_INIT "$(GLOBAL_CFLAGS)" CACHE STRING "")'                                >> $@
	@echo 'set(CMAKE_CXX_FLAGS_INIT "$(CPPFLAGS)" CACHE STRING "")'                                   >> $@

lib: $(USER_CACHE)
	cmake -S $(CUSTOM_SRC_DIR) -B $(USER_BUILD_DIR) -G "Unix Makefiles" -C $(USER_CACHE)
	cmake --build $(USER_BUILD_DIR) --parallel
	mkdir -p $(USER_LIB_DIR)
	rm -f $(USER_LIB_DIR)/*.a
	find $(USER_BUILD_DIR) -name 'lib*.a' -exec cp {} $(USER_LIB_DIR)/ \;

all: lib

clean:
	rm -rf $(USER_BUILD_DIR)
