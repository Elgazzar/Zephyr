# Zephyr Project Examples for STM32F429I Discovery Board

This folder contains example applications for the STM32F429I Discovery board using the Zephyr RTOS.

## Project Structure

Place your examples in the `apps` directory of your Zephyr project workspace. Each example should be in its own directory with the following structure:

```
apps/
├── your_example_name/
│   ├── CMakeLists.txt
│   ├── prj.conf
│   ├── src/
│   │   └── main.c
│   └── boards/
│       └── stm32f429i_disc1.overlay
```

## Building an Example

1. Open a PowerShell terminal and navigate to your example directory:
   ```powershell
   cd \path\to\zephyrproject\apps\your_example_name
   ```

2. Build the application using one of these methods:

   a. Using the build script (if available):
   ```powershell
   .\build.bat
   ```

   b. Using west directly:
   ```powershell
   west build -p always -b stm32f429i_disc1 -- -DDTC_OVERLAY_FILE="boards/stm32f429i_disc1.overlay"
   ```

   The `-p always` flag ensures a pristine build
   The `-b stm32f429i_disc1` specifies our target board
   The overlay file is optional and only needed if you have custom pin configurations

## Flashing the Board

1. Connect the STM32F429I Discovery board to your computer via USB

2. Flash the application using:
   ```powershell
   west flash
   ```

## Debugging

1. To debug your application, use:
   ```powershell
   west debug
   ```

2. For logging output, use:
   ```powershell
   west attach
   ```

## Common Issues

1. If build fails with CMake cache errors:
   - Delete the `build` directory
   - Try building again

2. If flash fails:
   - Check USB connection
   - Ensure board is powered
   - Try unplugging and replugging the board

## Board Features

The STM32F429I Discovery board includes:
- STM32F429ZIT6 microcontroller
- 2 user LEDs
- 1 user button
- 2.4" QVGA TFT LCD
- 64Mbit SDRAM
- USB OTG
- ST-LINK/V2-B debugger/programmer

## Device Tree Overlays

When creating custom pin configurations, add them to `boards/stm32f429i_disc1.overlay`. Example:

```dts
/ {
    leds {
        compatible = "gpio-leds";
        external_led: led {
            gpios = <&gpiog 14 GPIO_ACTIVE_HIGH>;
            label = "User LED";
        };
    };
};
```

## Additional Resources

- [Zephyr Project Documentation](https://docs.zephyrproject.org/)
- [STM32F429I Discovery Board Manual](https://www.st.com/resource/en/user_manual/dm00093903-discovery-kit-with-stm32f429zi-mcu-stmicroelectronics.pdf)
- [STM32F429ZI Reference Manual](https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf)
