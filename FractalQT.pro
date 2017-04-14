#-------------------------------------------------
#
# Project created by QtCreator 2016-02-10T11:15:30
#
#-------------------------------------------------

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT
CXXFLAGS += /MDd

QT       += core gui opengl


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FractalQT
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    cuda_helper.cpp \
    colorspectrumpicker.cpp \
    colorspectrumchannelpicker.cpp \
    gradient.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    cuda_helper.h \
    fractal.h \
    colorspectrumpicker.h \
    colorspectrumchannelpicker.h \
    gradient.h

CUDA_SOURCES += compute.cu

FORMS    += mainwindow.ui \
    colorspectrumpicker.ui \
    colorspectrumchannelpicker.ui

LIBS += -lcuda -lcudart glew32s.lib msvcrt.lib libcmtd.lib

CUDA_LIBS += -lcuda -lcudart

MSVCRT_LINK_FLAG_DEBUG = "/MDd"
MSVCRT_LINK_FLAG_RELEASE = "/MD"

# CUDA settings
CUDA_SOURCES += compute.cu
CUDA_DIR = "D:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v8.0"
SYSTEM_NAME = Win64         # Depending on your system either 'Win32', 'x64', or 'Win64'
SYSTEM_TYPE = 64            # '32' or '64', depending on your system
#CUDA_ARCH = sm_11           # Type of CUDA architecture, for example 'compute_10', 'compute_11', 'sm_10'
NVCC_OPTIONS = --use_fast_math

# The following library conflicts with something in Cuda
QMAKE_LFLAGS_RELEASE = /NODEFAULTLIB:msvcrt.lib
QMAKE_LFLAGS_DEBUG   = /NODEFAULTLIB:msvcrtd.lib

# Path to Visual Studio 2012 for CUDA
NVCC_OPTIONS += --cl-version 2015 -ccbin '"D:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\cl.exe"'

#CUDA_INC += "D:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v7.5\include"

# The following makes sure all path names (which often include spaces) are put between quotation marks
#CUDA_INC = $$join(INCLUDEPATH,'" -I"','-I"','"')

# Configuration of the Cuda compiler
CONFIG(debug, debug|release) {
    # Debug mode
    cuda_d.input = CUDA_SOURCES
    cuda_d.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
    #cuda_d.commands = $$CUDA_DIR/bin/nvcc.exe -D_DEBUG $$NVCC_OPTIONS $$CUDA_INC $$CUDA_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda_d.commands = $$CUDA_DIR/bin/nvcc.exe -D_DEBUG $$NVCC_OPTIONS $$CUDA_INC $$CUDA_LIBS --machine $$SYSTEM_TYPE \
        --compile -cudart static -DWIN32 -D_MBCS\
        -Xcompiler $$MSVCRT_LINK_FLAG_DEBUG \
        -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda_d.dependency_type = TYPE_C
    QMAKE_EXTRA_COMPILERS += cuda_d
}
else {
    # Release mode
    cuda.input = CUDA_SOURCES
    cuda.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
    #cuda.commands = $$CUDA_DIR/bin/nvcc.exe $$NVCC_OPTIONS $$CUDA_INC $$CUDA_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda.commands = $$CUDA_DIR/bin/nvcc.exe $$NVCC_OPTIONS $$CUDA_INC $$CUDA_LIBS --machine $$SYSTEM_TYPE \
        --compile -cudart static -DWIN32 -D_MBCS\
        -Xcompiler $$MSVCRT_LINK_FLAG_RELEASE \
        -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda.dependency_type = TYPE_C
    QMAKE_EXTRA_COMPILERS += cuda
}
