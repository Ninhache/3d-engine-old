#Checks for buid folder
[ -d "build/" ] ||  mkdir build

#Checks for cmake build 
[ -d "build/CMakeCache.txt" ] || cmake CMakeLists.txt -B build/ -G "Unix Makefiles"

cd build/ && make && cd .. && ./build/3d-engine-test