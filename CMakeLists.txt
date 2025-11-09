# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("AVS35" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
file(GLOB CXX_FILES "src/*.cc")

if (WIN32)
	add_definitions("/W4 /WX") 
	add_compile_options(-D _CRT_SECURE_NO_WARNINGS) 
	add_compile_options(/arch:AVX512f)
	add_compile_options(/arch:AVX512bw)
else()
	add_definitions("-Wall -Wextra -Werror -Wconversion -Wsign-conversion")
	add_definitions("-mavx512f -mavx512bw")
endif(WIN32)

add_executable (${PROJECT_NAME} ${CXX_FILES}) 
