cmake_minimum_required(VERSION 3.23)

project("chibihash_cpp")

option(CHIBIHASH_CPP_INSTALL "Enable install target for ${PROJECT_NAME}" ${PROJECT_IS_TOP_LEVEL})
option(CHIBIHASH_CPP_TESTING "Enable test target for ${PROJECT_NAME}" ${PROJECT_IS_TOP_LEVEL})

add_library(${PROJECT_NAME} INTERFACE)
add_library("chibihash::${PROJECT_NAME}" ALIAS ${PROJECT_NAME})
target_sources(${PROJECT_NAME} PUBLIC FILE_SET HEADERS BASE_DIRS "include" FILES
	"include/chibihash/chibihash64.hh"
)
target_include_directories(${PROJECT_NAME} INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

if(CHIBIHASH_CPP_INSTALL)
    install(
        TARGETS ${PROJECT_NAME}
        EXPORT "${PROJECT_NAME}Targets"
        FILE_SET HEADERS
    )

    install(EXPORT "${PROJECT_NAME}Targets"
        DESTINATION "lib/cmake/${PROJECT_NAME}"
        NAMESPACE chibihash::
    )

    export(EXPORT "${PROJECT_NAME}Targets"
        FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Targets.cmake"
        NAMESPACE chibihash::
    )

    include(CMakePackageConfigHelpers)
    configure_package_config_file("${PROJECT_NAME}Config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
    )
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        DESTINATION "lib/cmake/${PROJECT_NAME}"
    )
endif()

if(CHIBIHASH_CPP_TESTING)
	enable_testing()
	add_executable("${PROJECT_NAME}_test" "test.cpp")
	target_link_libraries("${PROJECT_NAME}_test" PRIVATE ${PROJECT_NAME})
	add_test("${PROJECT_NAME}_test" COMMAND chibihash64_cpp_test)
endif()