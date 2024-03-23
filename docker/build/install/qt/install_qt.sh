#!/usr/bin/env bash
# 根据多个开源项目整合一个脚本用于安装QT

set -e

BUILD_TYPE="${1:-download}"

# get current absolute path
CURR_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"

TARGET_ARCH="$(uname -m)"

QT_VERSION_A=5.12
QT_VERSION_B=5.12.9
# 5129
QT_VERSION_Z=$(echo "$QT_VERSION_B" | tr -d '.')

# docker/build/install/qt/qt-opensource-linux-x64-5.12.9.run
QT_INSTALLER=qt-opensource-linux-x64-5.12.9.run
# https://download.qt.io/archive/qt/5.12/5.12.9/qt-opensource-linux-x64-5.12.9.run

MY_DEST_DIR="/usr/local/Qt${QT_VERSION_B}"
# use cuteci install
cuteci --installer /tmp/install/qt/qt-opensource-linux-x64-5.12.9.run \
    install \
    --destdir="$MY_DEST_DIR" \
    --packages "qt.qt5.${QT_VERSION_Z}.gcc_64" \
    --keep-tools

QT5_PATH="/usr/local/qt5"
# Hide qt5 version from end users
ln -s ${MY_DEST_DIR}/${QT_VERSION_B}/gcc_64 "${QT5_PATH}"

# refer to  https://www.cnblogs.com/schips/p/10183111.html
echo "${QT5_PATH}/lib" > /etc/ld.so.conf.d/qt.conf
ldconfig

__mytext="""
export QT5_PATH=\"${QT5_PATH}\"
export QT_QPA_PLATFORM_PLUGIN_PATH=\"\${QT5_PATH}/plugins\"
add_to_path \"\${QT5_PATH}/bin\"
"""

# clean up
rm -f ${QT_INSTALLER}
# Keep License files
rm -rf ${MY_DEST_DIR}/{Docs,Examples,Tools,dist} || true
rm -rf ${MY_DEST_DIR}/MaintenanceTool* || true
rm -rf ${MY_DEST_DIR}/{InstallationLog.txt,installer-changelog} || true
rm -rf ${MY_DEST_DIR}/{components,network}.xml || true
