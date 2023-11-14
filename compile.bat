echo off
g++.exe ^
    src/*.cpp include/*.cpp ^
    info.res icon.res ^
    -I include/ ^
    -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -L"C:\Program Files\mingw-w64\lib" -lcomdlg32 -lole32 ^
    -static-libstdc++ -static-libgcc -O3 -mwindows -m64 -static -o RICOcHet.exe ^
    
ricochet

echo on