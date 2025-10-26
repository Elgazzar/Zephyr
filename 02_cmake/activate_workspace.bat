@echo off
cd %~dp0\..\..
if exist .venv\Scripts\activate.bat (
    call .venv\Scripts\activate.bat
) else (
    echo Error: Python virtual environment not found!
    exit /b 1
)