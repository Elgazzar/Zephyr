@echo off
REM Get the directory where this script is located
set "SCRIPT_DIR=%~dp0"
REM Activate the workspace first
call "%SCRIPT_DIR%activate_workspace.bat"
REM Build the Zephyr application
call "%SCRIPT_DIR%zephyr_build.bat"