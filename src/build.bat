@echo off

goto argparse

:distorm
pushd .
cd ..\decoders && call build-distorm.bat
popd
set libs=..\decoders\distorm\distorm
set inc=..\decoders\distorm\distorm\include
cl.exe /Zi /O0 /I %inc% distorm-benchmark.c /link /LIBPATH:%libs% distorm.lib 
EXIT /B 

:beaengine
REM Build BeaEngine
pushd .
cd ..\decoders && call build-beaengine.bat
popd 
set libs=..\decoders\beaengine\beaengine\lib\Windows.msvc.RelWithDebInfo.64\Release
set inc=..\decoders\beaengine\beaengine\headers
cl.exe /Ox /I %inc% beaengine-benchmark.c /link /NODEFAULTLIB:msvcrt /LIBPATH:%libs% beaengine_s_l_64.lib
EXIT /B 


:xed
REM Build XED benchmark with latest build of xed kit
pushd . 
cd ..\decoders && call build-xed.bat
popd
FOR /f "tokens=2-4 delims=/ " %%a in ('date /t') do (set tdate=%%c-%%a-%%b)
set xed=..\decoders\xed\xed
set libs=%xed%\kits\xed-install-base-%tdate%-win-x86-64\lib
set inc=%xed%\kits\xed-install-base-%tdate%-win-x86-64\include
cl.exe /Ox /I %inc% xed-benchmark.c /link /LIBPATH:%libs% xed.lib xed-ild.lib
EXIT /B 

:capstone
REM Build Capstone
pushd .
cd ..\decoders && call build-capstone.bat
popd
set libs=..\decoders\capstone\capstone\msvc\x64\Release
set inc=..\decoders\capstone\capstone\include
cl.exe /Ox /I %inc% capstone-benchmark.c /link /LTCG /LIBPATH:%libs% capstone.lib
EXIT /B 

:all
call :distorm
call :beaengine
call :xed
call :capstone
goto END

:test
distorm-benchmark.exe
beaengine-benchmark.exe
xed-benchmark.exe
capstone-benchmark.exe
goto END

:usage
echo usage: %0 [decoder] or %0 all
goto END

:argparse 

if "%1"=="" goto usage
if "%1"=="all" goto all

call :%1


:END
