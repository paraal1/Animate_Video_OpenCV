TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

INCLUDEPATH += $$PWD/../../../../../opencv/build/include
DEPENDPATH += $$PWD/../../../../../opencv/build/include

LIBS += C:\opencv\opencv-build\bin\libopencv_core4100.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_highgui4100.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_imgcodecs4100.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_imgproc4100.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_features2d4100.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_videoio4100.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_video4100.dll
