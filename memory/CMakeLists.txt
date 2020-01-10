cmake_minimum_required(VERSION 3.0.2)

project(memory)

option(ENABLE_ASAN "Enable Address Sanitizers" ON)
option(ENABLE_TSAN "Enable Thread Sanitizers" OFF)
option(ENABLE_MSAN "Enable Memory Sanitizers" OFF)

if (NOT "!${CMAKE_CXX_COMPILER_ID}" STREQUAL "!Clang")
	message(FATAL_ERROR "The demo is only tested with clang")
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -g -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath='\$ORIGIN' -Wl,--no-undefined")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")

if ("!${CMAKE_CXX_COMPILER_ID}" STREQUAL "!Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
endif()

if (ENABLE_ASAN)
	add_definitions(-D_USING_ASAN=1)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -shared-libasan -fno-omit-frame-pointer ")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

	execute_process(
		COMMAND ${CMAKE_CXX_COMPILER} -print-file-name=libclang_rt.asan-x86_64.so
		OUTPUT_VARIABLE asan_dso
		)

	string(STRIP "${asan_dso}" asan_dso)
	file(COPY "${asan_dso}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin")
elseif (ENABLE_TSAN)
	add_definitions(-D_USING_TSAN=1)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -fno-omit-frame-pointer")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread")
elseif (ENABLE_MSAN)
	add_definitions(-D_USING_MSAN=1)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory -fsanitize-memory-track-origins -fno-omit-frame-pointer")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=memory")
endif()

set(common_src
	src/common.cpp
	src/common.h
	)

# ------------------Overflow-----------------------------

add_executable(HeapBufferOverflow
	${common_src}
	src/heap-buffer-overflow.cpp
	)

add_executable(StackBufferOverflow
	${common_src}
	src/stack-buffer-overflow.cpp
	)

add_executable(GlobalBufferOverflow
	${common_src}
	src/global-buffer-overflow.cpp
	)

# -----------------Access-------------------------------

add_executable(UseAfterReturn
	${common_src}
	src/use-after-return.cpp
	)

add_executable(UseAfterFree
	${common_src}
	src/use-after-free.cpp
	)

add_executable(UseAfterScope
	${common_src}
	src/use-after-scope.cpp
	)

add_executable(InitializationOrderFiasco
	${common_src}
	src/init-order-fiasco.cpp
	)

# ----------------Races-----------------------

add_executable(ThreadRace
	src/thread-race.cpp
	)

target_link_libraries(ThreadRace
	pthread)

# ----------------Races-----------------------

add_executable(VarInit
	src/var-init.cpp
	)

# ----------------Leaks-----------------------

add_executable(Leaks
	${common_src}
	src/leaks.cpp
	)

add_executable(LeaksOpt
	${common_src}
	src/leaks-opt.cpp
	)

add_executable(HeapProfiler
	src/heap-profiler.cpp
	)

if (NOT ENABLE_ASAN AND NOT ENABLE_TSAN AND NOT ENABLE_MSAN)
	file(GLOB _tcmalloc "${CMAKE_CURRENT_SOURCE_DIR}/gperftools/.libs/libtcmalloc.so*")
	file(COPY ${_tcmalloc} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin")

	target_include_directories(LeaksOpt
		PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/gperftools/src"
		)
	target_link_directories(LeaksOpt
		PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/bin")
	target_link_libraries(LeaksOpt
		tcmalloc
		)

	target_include_directories(LeaksOpt
		PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/gperftools/src"
		)
	target_link_directories(LeaksOpt
		PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/bin")
	target_link_libraries(HeapProfiler
		tcmalloc)
endif()

add_subdirectory(odr)
