#!/usr/bin/env bash

set -e

cd "$(dirname "${BASH_SOURCE[0]}")"

# https://github.com/abseil/abseil-cpp/archive/refs/tags/20200225.2.tar.gz
# Install abseil.
THREAD_NUM=$(nproc)
VERSION="20200225.2"
PKG_NAME="abseil-cpp-${VERSION}.tar.gz"


#unzip
tar xzf "${PKG_NAME}"
pushd "abseil-cpp-${VERSION}"
    mkdir build && cd build
    #Makefile
    cmake .. \
        -DBUILD_SHARED_LIBS=ON \
        -DCMAKE_CXX_STANDARD=14 \
        -DCMAKE_INSTALL_PREFIX=/usr/local
    # compile
    make -j${THREAD_NUM}
    # install 
    make install
popd

#Update shared libraries
ldconfig

# Clean up
rm -rf "abseil-cpp-${VERSION}" "${PKG_NAME}"