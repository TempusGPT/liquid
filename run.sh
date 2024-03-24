if [[ "$1" == "-d" || "$1" == "--debug" ]]; then
    cmake --build . && lldb build.out
else
    cmake --build . && ./build.out
fi
