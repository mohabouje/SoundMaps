#!/bin/sh

export LIB_NAME=fftw
export CROSS_COMPILE=arm-linux-androideabi


export DEV_PREFIX=$HOME/Documents/Developer
export PKG_CONFIG_PATH=${PREFIX}/lib/pkgconfig
export PREFIX=${DEV_PREFIX}/android/${LIB_NAME}/${CROSS_COMPILE}

SRC_DIR="$(pwd)/../fftw-3.3.6-pl2"

# Add the toolchain to the system PATH variable 
export PATH=$PATH:$TOOLCHAINS_ROOT
export ANDROID_NDK=/home/mohabb/Android/android-ndk-r15b
export ANDROID_PREFIX=${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64
export SYSROOT=${ANDROID_NDK}/platforms/android-9/arch-arm
export CROSS_PATH=${ANDROID_PREFIX}/bin/${CROSS_COMPILE}

# Non-exhaustive lists of compiler + binutils
# Depending on what you compile, you might need more binutils than that
export CPP=${CROSS_PATH}-cpp
export AR=${CROSS_PATH}-ar
export AS=${CROSS_PATH}-as
export NM=${CROSS_PATH}-nm
export CC=${CROSS_PATH}-gcc
export CXX=${CROSS_PATH}-g++
export LD=${CROSS_PATH}-ld
export RANLIB=${CROSS_PATH}-ranlib

mkdir -p $PREFIX
cd $SRC_DIR

# You can clone the full Android sources to get bionic if you want.. I didn't
# want to so I just got linker.h from here: http://gitorious.org/0xdroid/bionic
# Note that this was only required to build boehm-gc with dynamic linking support.
export CFLAGS="${CFLAGS} --sysroot=${SYSROOT} -I${SYSROOT}/usr/include -I${ANDROID_PREFIX}/include -I${DEV_PREFIX}/android/bionic"
export CPPFLAGS="${CFLAGS}"
export LDFLAGS="${LDFLAGS} -L${SYSROOT}/usr/lib -L${ANDROID_PREFIX}/lib"

./configure --host=${CROSS_COMPILE} \
--with-sysroot=${SYSROOT} \
-prefix=${PREFIX} "$@"

make -j4
make install
