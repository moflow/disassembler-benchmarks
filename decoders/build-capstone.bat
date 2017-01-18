REM build-xed.bat

@echo off
pushd .

mkdir capstone && cd capstone && ^
git clone https://github.com/aquynh/capstone.git && ^
cd capstone\msvc && devenv /upgrade capstone.sln && msbuild /p:Configuration=Release /p:Platform=x64

popd