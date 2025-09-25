mkdir build
cd build
cmake -G "Visual Studio 17" -A x64 -DBUILD_AS_DLL=ON ..
cmake --build . --config Release
