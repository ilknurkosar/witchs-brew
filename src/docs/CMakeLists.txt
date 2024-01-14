# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
  message(STATUS "Doxygen found.")

  set(DOXYGEN_GENERATE_HTML YES)
  set(DOXYGEN_HTML_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html)
  set(DOXYGEN_GENERATE_TREEVIEW YES)
  list(APPEND DOXYGEN_EXCLUDE_PATTERNS */dependencies/*)
  set(
    DOXYGEN_FILE_PATTERNS
    *.c
    *.cc
    *.cxx
    *.cpp
    *.c++
    *.ii
    *.ixx
    *.ipp
    *.i++
    *.inl
    *.h
    *.hh
    *.hxx
    *.hpp
    *.h++
    *.inc
    README.md
  )


  # list(APPEND DOXYGEN_HTML_EXTRA_STYLESHEET ${PROJECT_SOURCE_DIR}/docs/doxygen-awesome.css)
  # list(APPEND DOXYGEN_HTML_EXTRA_STYLESHEET ${PROJECT_SOURCE_DIR}/docs/doxygen-awesome-sidebar-only.css)

  doxygen_add_docs(
    documentation
    ${PROJECT_SOURCE_DIR}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Generating documentation"
  )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)