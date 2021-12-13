cmake_minimum_required(VERSION 3.5)

project(zipVeiwer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(MZ_WZAES "Enables WinZIP AES encryption" ON)



find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
if(WIN32)
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        dirtreemodel.h
        dirtreemodel.cpp
        minizip/mz.h
        minizip/mz_crypt.h
        minizip/mz_crypt.cpp
        minizip/mz_crypt_win32.cpp
        minizip/mz_os.h
        minizip/mz_os.cpp
        minizip/mz_strm.h
        minizip/mz_strm.cpp
        minizip/mz_strm_buf.h
        minizip/mz_strm_buf.cpp
        minizip/mz_strm_mem.h
        minizip/mz_strm_mem.cpp
        minizip/mz_strm_os.h        
        minizip/mz_strm_os_win32.cpp
        minizip/mz_strm_split.h
        minizip/mz_strm_split.cpp
        minizip/mz_strm_wzaes.h
        minizip/mz_strm_wzaes.cpp
        minizip/mz_zip.h
        minizip/mz_zip.cpp
        minizip/mz_zip_rw.h
        minizip/mz_zip_rw.cpp
        minizip/some_lib.h
        minizip/some_lib.cpp
        myLib/onedirorfileclass.h
        myLib/onedirorfileclass.cpp
        myLib/filedirdata.h
        myLib/filedirdata.cpp
        myLib/filedirdata_win32.cpp
        myLib/rustextrecoderclass.h
        myLib/rustextrecoderclass.cpp
        minizip/mz_os_win32.cpp

)
ELSEIF(UNIX)
add_compile_definitions(MZ_ZIP_NO_CRYPTO)
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        dirtreemodel.h
        dirtreemodel.cpp
        minizip/mz.h
        #minizip/mz_crypt.h
        #minizip/mz_crypt.cpp
        #minizip/mz_crypt_win32.cpp
        #minizip/mz_crypt_apple.cpp
        minizip/mz_os.h
        minizip/mz_os.cpp
        minizip/mz_strm.h
        minizip/mz_strm.cpp
        minizip/mz_strm_buf.h
        minizip/mz_strm_buf.cpp
        minizip/mz_strm_mem.h
        minizip/mz_strm_mem.cpp
        minizip/mz_strm_os.h
        minizip/mz_strm_os_posix.cpp
        #minizip/mz_strm_os_win32.cpp
        minizip/mz_strm_split.h
        minizip/mz_strm_split.cpp
        #minizip/mz_strm_wzaes.h
        #minizip/mz_strm_wzaes.cpp
        minizip/mz_zip.h
        minizip/mz_zip.cpp
        minizip/mz_zip_rw.h
        minizip/mz_zip_rw.cpp
        minizip/some_lib.h
        minizip/some_lib.cpp
        myLib/onedirorfileclass.h
        myLib/onedirorfileclass.cpp
        myLib/filedirdata.h
        myLib/filedirdata.cpp
        myLib/filedirdata_posix.cpp
        myLib/rustextrecoderclass.h
        myLib/rustextrecoderclass.cpp
        minizip/mz_os_posix.cpp
)
ENDIF()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(zipVeiwer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET zipVeiwer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(zipVeiwer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(zipVeiwer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(zipVeiwer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(zipVeiwer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(zipVeiwer)
endif()
