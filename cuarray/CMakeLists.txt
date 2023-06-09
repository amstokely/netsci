set(CLEAN_FILES_AND_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/*
        ${CMAKE_CURRENT_SOURCE_DIR}/python/build
        ${CMAKE_CURRENT_SOURCE_DIR}/python/cuarray.egg-info
        ${CMAKE_CURRENT_SOURCE_DIR}/python/dist
        ${CMAKE_CURRENT_SOURCE_DIR}/python/cuarray/*.so*
        ${CMAKE_CURRENT_SOURCE_DIR}/python/cuarray/cuarray.py
        ${CMAKE_CURRENT_SOURCE_DIR}/python/cuarray/*.cxx*
        ${CMAKE_CURRENT_SOURCE_DIR}/tcl/*
        )
set_directory_properties(
        PROPERTIES
        ADDITIONAL_CLEAN_FILES "${CLEAN_FILES_AND_DIRS}"
)
set_source_files_properties(
        ${CMAKE_CURRENT_SOURCE_DIR}/swig/python_cuarray.i
        PROPERTIES
        CPLUSPLUS ON
        SWIG_MODULE_NAME cuarray
)

set_source_files_properties(
        ${CMAKE_CURRENT_SOURCE_DIR}/swig/tcl_cuarray.i
        PROPERTIES
        CPLUSPLUS ON
        SWIG_MODULE_NAME cuarray
)

add_library(cuarray SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cuarray.cu
        )
add_dependencies(cuarray cnpy)
set_target_properties(
        cuarray
        PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
        CUDA_ARCHITECTURES ${CUDA_ARCHITECTURE}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
        LINK_LIBRARIES "${CUARRAY_LINK_LIBRARIES}"
)
swig_add_library(python_cuarray
        LANGUAGE python
        OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/python/cuarray
        SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/swig/python_cuarray.i
        )
set_target_properties(
        python_cuarray
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/python/cuarray
        LINK_LIBRARIES "${CUARRAY_PYTHON_LINK_LIBRARIES}"
)
swig_add_library(tcl_cuarray
        LANGUAGE tcl
        OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tcl
        SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/swig/tcl_cuarray.i
        )
set_target_properties(
        tcl_cuarray
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tcl
        LINK_LIBRARIES "${CUARRAY_TCL_LINK_LIBRARIES}"
        PREFIX ""
        OUTPUT_NAME "cuarray"
        SUFFIX ".so"
)
swig_link_libraries(tcl_cuarray cuarray)
IF (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tcl/tcl_cuarrayTCL_wrap.cxx)
    FILE(REMOVE ${CMAKE_CURRENT_SOURCE_DIR}/tcl/tcl_cuarrayTCL_wrap.cxx)
ENDIF ()


set(PIP_UNINSTALL_CUARRAY_ARGS "uninstall" "cuarray" "-y")
set(PYTHON_CUARRAY_INSTALL_ARGS "setup.py" "install")
add_custom_target(PythonCuArrayInstall
        COMMAND pip ${PIP_UNINSTALL_CUARRAY_ARGS}
        COMMAND ${Python3_EXECUTABLE} ${PYTHON_CUARRAY_INSTALL_ARGS}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/cuarray/python
        )
