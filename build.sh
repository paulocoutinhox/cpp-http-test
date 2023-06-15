export CPM_SOURCE_CACHE=$HOME/.cache/CPM
export OPENSSL_ROOT_DIR="/opt/homebrew/opt/openssl@3"

rm -rf build/
mkdir -p build
cd build && cmake ../ && cmake --build . --config Release
