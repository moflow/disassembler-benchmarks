REM build-xed.bat

@echo off
pushd .

mkdir beaengine 
cd beaengine
git clone https://github.com/BeaEngine/beaengine.git && ^
cmake -G"Visual Studio 14 2015 Win64" -DoptHAS_OPTIMIZED:BOOL=TRUE -DoptBUILD_64BIT:BOOL=TRUE beaengine && ^
cmake --build . --config Release

popd