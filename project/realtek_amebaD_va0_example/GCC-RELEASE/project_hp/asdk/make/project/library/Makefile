
include $(MAKE_INCLUDE_GEN)

.PHONY: all clean lib clean_lib

CUSTOM_SRC_DIR := $(BASEDIR)/../../src
USER_BUILD_DIR := $(BASEDIR)/../../build/amebad_user
USER_CACHE     := $(USER_BUILD_DIR)/init-cache.cmake

# No staging copy: CMake writes the authoritative link list to
# $(USER_BUILD_DIR)/user_link.list (see src/CMakeLists.txt). asdk/Makefile
# cats that file at link-recipe time. Whatever STATIC_LIBRARY targets the
# user CMake project declares end up in the list automatically.

clean_lib:
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

all: lib

clean:
	rm -rf $(USER_BUILD_DIR)
