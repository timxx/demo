find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

set(CMAKE_AUTOMOC ON)

add_library(odr SHARED
	src/kfilewidget.cpp
	src/kfilewidget.h
	)

target_link_libraries(odr
	Qt5::Core
	Qt5::Widgets
	)

add_executable(OdrDemo
	src/odr-demo.cpp
	../src/common.cpp
	)

target_link_libraries(OdrDemo
	odr)
