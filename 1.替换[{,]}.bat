@echo off
setlocal enabledelayedexpansion

set "input_file=D:\MyFile\input.txt"
set "output_file=D:\MyFile\output.txt"

if exist "%output_file%" del "%output_file%"

for /f "delims=" %%a in ('type "%input_file%"') do (
    set "line=%%a"
    set "line=!line:[={!"
    set "line=!line:]=}!"
    echo !line! >> "%output_file%"
)

echo "替换完成。"
rem pause