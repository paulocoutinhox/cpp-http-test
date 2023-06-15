export CPM_SOURCE_CACHE=$HOME/.cache/CPM
export OPENSSL_ROOT_DIR="/opt/homebrew/opt/openssl@3"

rm -rf build/
mkdir -p build
cd build && cmake ../ -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK_ROOT}/build/cmake/android.toolchain.cmake -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-21 && cmake --build . --config Debug
