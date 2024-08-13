include_directories(include)


add_executable (miccomp
  miccomp.cpp
  ./lib/Lexer/Lexer.cpp
  ./lib/Parser/Parser.cpp
  )
target_link_libraries(miccomp PRIVATE ${llvm_libs})
