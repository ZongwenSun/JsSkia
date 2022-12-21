
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

project("js_skia")

cmake_minimum_required(VERSION 3.4.1)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSK_GL -DSK_BUILD_FOR_ANDROID -DFOLLY_NO_CONFIG=1 -DFOLLY_HAVE_CLOCK_GETTIME=1 -DFOLLY_HAVE_MEMRCHR=1 -DFOLLY_USE_LIBCPP=1 -DFOLLY_MOBILE=1 -DON_ANDROID -DONANDROID")

set(PACKAGE_NAME js_skia)

set(SKIA_LIB "skia")
set(SKIA_SVG_LIB "svg")
set(SKIA_SKSHAPER_LIB "skshaper")

add_definitions(-DCONFIG_BIGNUM)

link_directories(../../../libs/android/${ANDROID_ABI}/)

file(GLOB qjs_source "./quickjs/*.c")

add_library( # Sets the name of the library.
        ${PACKAGE_NAME}
        SHARED
        ${qjs_source}
        jsengine.cpp
        jni/skia_render_view.cpp
        jni/js_skia_jni.cpp)

target_include_directories(
        ${PACKAGE_NAME}
        PRIVATE

        skia/include/config/
        skia/include/core/
        skia/include/effects/
        skia/include/utils/
        skia/include/pathops/
        skia/modules/
        #skia/modules/skparagraph/include/
        skia/include/
        skia
)


add_library(${SKIA_LIB} STATIC IMPORTED)
add_library(${SKIA_SVG_LIB} STATIC IMPORTED)
add_library(${SKIA_SKSHAPER_LIB} STATIC IMPORTED)

set(SKIA_LIBS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/android/${ANDROID_ABI}")

set_target_properties(
        ${SKIA_LIB}
        PROPERTIES IMPORTED_LOCATION
        ${SKIA_LIBS_PATH}/libskia.a)
set_target_properties(
        ${SKIA_SKSHAPER_LIB}
        PROPERTIES IMPORTED_LOCATION
        ${SKIA_LIBS_PATH}/libskshaper.a)
set_target_properties(
        ${SKIA_SVG_LIB}
        PROPERTIES IMPORTED_LOCATION
        ${SKIA_LIBS_PATH}/libsvg.a)

find_library(
        log-lib
        log)

target_link_libraries(
        ${PACKAGE_NAME}
        ${SKIA_LIB}
        ${SKIA_SVG_LIB}
        ${SKIA_SKSHAPER_LIB}
        ${log-lib}
        -ljnigraphics
        -lGLESv2
        -lEGL
        -landroid)
