@echo off
pushd %~dp0\..\
call .\vendor\bin\premake\windows\premake5.exe vs2022
popd