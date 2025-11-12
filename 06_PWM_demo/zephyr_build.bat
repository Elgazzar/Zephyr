@echo off
cd %~dp0
where west >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo Error: West tool not found. Make sure Zephyr environment is activated.
    exit /b 1
)
west build -p always -b stm32f429i_disc1 -- -DDTC_OVERLAY_FILE="boards/stm32f429i_disc1.overlay"