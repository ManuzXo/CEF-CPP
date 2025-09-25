mkdir build
cd build
cmake -G "Visual Studio 17" -A Win32 -DBUILD_AS_DLL=OFF ..
cmake --build . --config Release
