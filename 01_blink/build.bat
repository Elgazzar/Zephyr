cd ..\..
call .venv\Scripts\activate.bat
cd apps\01_blink
west build -p always -b stm32f429i_disc1 -- -DDTC_OVERLAY_FILE="boards/stm32f429i_disc1.overlay"