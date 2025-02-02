cmake_minimum_required(VERSION 3.23)

project("chibihash_cpp")

option(CHIBIHASH_CPP_INSTALL "Enable install target for ${PROJECT_NAME}" ${PROJECT_IS_TOP_LEVEL})
option(CHIBIHASH_CPP_TESTING "Enable test target for ${PROJECT_NAME}" ${PROJECT_IS_TOP_LEVEL})

add_library(${PROJECT_NAME} INTERFACE)
add_library(chibihash::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_sources(${PROJECT_NAME} INTERFACE FILE_SET HEADERS BASE_DIRS "include" FILES
	"include/chibihash/chibihash64.hh"
)
target_include_directories(${PROJECT_NAME} INTERFACE
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

if(CHIBIHASH_CPP_INSTALL)
	include(GNUInstallDirs)
	install(TARGETS ${PROJECT_NAME} EXPORT "${PROJECT_NAME}-config" FILE_SET HEADERS)
	install(EXPORT "${PROJECT_NAME}-config" NAMESPACE "chibihash::" DESTINATION "lib/cmake/${PROJECT_NAME}")
	export(EXPORT "${PROJECT_NAME}-config" FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Targets.cmake" NAMESPACE "chibihash::")
endif()

if(CHIBIHASH_CPP_TESTING)
	enable_testing()
	add_executable("${PROJECT_NAME}_test" "test.cpp")
	target_link_libraries("${PROJECT_NAME}_test" PRIVATE ${PROJECT_NAME})
	add_test("${PROJECT_NAME}_test" COMMAND chibihash64_cpp_test)
endif()