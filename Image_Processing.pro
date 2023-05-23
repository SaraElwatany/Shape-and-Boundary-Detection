QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0





SOURCES += \
    activecontour.cpp \
    filters.cpp \
    frequency.cpp \
    histograms.cpp \
    hough.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    activecontour.h \
    filters.h \
    frequency.h \
    histograms.h \
    hough.h \
    mainwindow.h

FORMS += \
    mainwindow.ui



## Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += D:\Libraries\OpenCV\opencv\release\install\include



win32: LIBS += -LD:/Libraries/OpenCV/opencv/release/lib/ -llibopencv_calib3d470.dll
INCLUDEPATH += D:/Libraries/OpenCV/opencv/release/include
DEPENDPATH += D:/Libraries/OpenCV/opencv/release/include


win32: LIBS += -LD:/Libraries/OpenCV/opencv/release/lib/ -llibopencv_core470.dll
INCLUDEPATH += D:/Libraries/OpenCV/opencv/release/include
DEPENDPATH += D:/Libraries/OpenCV/opencv/release/include



win32: LIBS += -LD:/Libraries/OpenCV/opencv/release/lib/ -llibopencv_highgui470.dll
INCLUDEPATH += D:/Libraries/OpenCV/opencv/release/include
DEPENDPATH += D:/Libraries/OpenCV/opencv/release/include



win32: LIBS += -LD:/Libraries/OpenCV/opencv/release/lib/ -llibopencv_imgcodecs470.dll
INCLUDEPATH += D:/Libraries/OpenCV/opencv/release/include
DEPENDPATH += D:/Libraries/OpenCV/opencv/release/include



win32: LIBS += -LD:/Libraries/OpenCV/opencv/release/lib/ -llibopencv_imgproc470.dll
INCLUDEPATH += D:/Libraries/OpenCV/opencv/release/include
DEPENDPATH += D:/Libraries/OpenCV/opencv/release/include












