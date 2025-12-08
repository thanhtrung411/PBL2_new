cmake_minimum_required(VERSION 3.16)

project(pbl2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts Concurrent)

set(PROJECT_SOURCES
        main.cpp
        pbl2.cpp
        pbl2.h
        pbl2.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(pbl2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        dang_ky_dialog.h dang_ky_dialog.cpp dang_ky_dialog.ui
        book.h book.cpp

        accout.h accout.cpp
        tree.h tree.cpp
        my_string.h my_string.cpp
        resource.qrc
        my_file.h my_file.cpp

        card.h card.cpp
        my_time.h my_time.cpp
        global.h




        borrow.h borrow.cpp
        info.h info.cpp info.ui
        book_copies.h book_copies.cpp
        the_loai_chuyen_nganh.h the_loai_chuyen_nganh.cpp
        author.h author.cpp
        library.h library.cpp
        history.h history.cpp
        admin.h admin.cpp admin.ui
        add_book.h add_book.cpp add_book.ui
        info_book.h info_book.cpp info_book.ui

        muon_sach.h muon_sach.cpp muon_sach.ui
        phieu_tra_sach.h phieu_tra_sach.cpp phieu_tra_sach.ui
        settings_file.h settings_file.cpp
        yeu_thich.h yeu_thich.cpp
        info_user.h info_user.cpp info_user.ui
        add_book_copy.h add_book_copy.cpp add_book_copy.ui


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET pbl2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(pbl2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(pbl2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(pbl2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts Qt${QT_VERSION_MAJOR}::Concurrent)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.pbl2)
endif()
set_target_properties(pbl2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS pbl2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(pbl2)
endif()
