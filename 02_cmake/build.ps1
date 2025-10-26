Push-Location (Split-Path $PSScriptRoot -Parent)
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
if (Test-Path ".venv\Scripts\Activate.ps1") {
    & ".venv\Scripts\Activate.ps1"
}
Set-Location -Path "01_blink"
west build -p always -b stm32f429i_disc1 -- -DDTC_OVERLAY_FILE="boards/stm32f429i_disc1.overlay"