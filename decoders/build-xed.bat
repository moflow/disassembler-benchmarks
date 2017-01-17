REM build-xed.bat

@echo off

pushd .
mkdir xed && cd xed && ^
git clone https://github.com/intelxed/xed.git xed && ^
git clone https://github.com/intelxed/mbuild.git mbuild && ^
cd xed && python mfile.py --no-encoder install
popd


