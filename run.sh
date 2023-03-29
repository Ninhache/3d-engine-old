#Checks for cmake build in assimp
[ -d "dependency/assimp-5.2.5/bin/libassimp.so.5.2.4" ] || cd dependency/assimp-5.2.5 && cmake CMakeLists.txt && cmake --build . && cd ../../

#Checks for buid folder
[ -d "build/" ] ||  mkdir build

#Checks for cmake build 
[ -d "build/CMakeCache.txt" ] || cmake CMakeLists.txt -B build/ -G "Unix Makefiles"

cd build/ && make && cd .. && ./build/3d-engine
