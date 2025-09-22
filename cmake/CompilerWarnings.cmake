# cmake/CompilerWarnings.cmake

# This will define the `set_project_warnings` function
# that takes the interface name.
function(set_project_warnings project_name)
  # I always treat warnings as errors, making my life easier
  # in the long run.
  option(
    WARNINGS_AS_ERRORS
    "Treat compiler warnings as errors" TRUE)
  message(STATUS "Treat compiler warnings as errors")

  set(MSVC_WARNINGS
    # Baseline reasonable warnings
    /W4
    # Whatever other MSVC compiler warnings you want.
    # ...
    )

  set(CLANG_WARNINGS
    # Reasonable and standard
    -Wall
    -Wextra
    # Whatever other CLang compiler warnings you want.
    # ...
    )

  # Stop the build if there are any warnings,
  if (WARNINGS_AS_ERRORS)
    set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
    set(MSVC_WARNINGS ${MSVC_WARNINGS} /WX)
  endif ()

  set(GCC_WARNINGS
    ${CLANG_WARNINGS}
    # Whatever other GCC compiler warnings you want.
    # ...
    )

  # Enable the right set of warnings depending on
  # the used compiler.
  if (MSVC)
    set(PROJECT_WARNINGS ${MSVC_WARNINGS})
  elseif (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(PROJECT_WARNINGS ${CLANG_WARNINGS})
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(PROJECT_WARNINGS ${GCC_WARNINGS})
  else ()
    message(
      AUTHOR_WARNING
      "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  endif ()

  # This will "link" the warnings to the defined
  # project name, in my case "project_warnings".
  target_compile_options(
    ${project_name} INTERFACE ${PROJECT_WARNINGS})
endfunction()