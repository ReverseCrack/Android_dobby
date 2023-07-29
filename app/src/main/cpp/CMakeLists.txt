# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.22.1)

# Declares and names the project.

project("dobby_study")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# 这里指定静态链接，生成一个so;默认为 ON，生成两个so
set(GENERATE_SHARED OFF)
set(DDOBBY_DEBUG OFF)
# 指定 dobby 库目录
set(DOBBY_SOURCE_DIR Dobby)
add_subdirectory(${DOBBY_SOURCE_DIR} dobby.out)
#end

add_library( # Sets the name of the library.
        test_for_hook

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        test_for_hook

        dobby  # 新增dobby引用
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})
