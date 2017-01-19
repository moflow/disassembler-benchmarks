REM build distorm 

@echo off
pushd .

mkdir distorm
cd distorm
git clone https://github.com/gdabah/distorm.git && ^
cd distorm\make\win32 && ^
devenv /upgrade distorm.sln && msbuild distorm.sln

popd