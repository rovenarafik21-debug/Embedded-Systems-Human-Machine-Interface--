## Embedded Systems Project Report: Temperature Monitor with LCD and Alert LED

## 1. Introduction

This project implements a temperature monitor on an Arduino Uno. The firmware is written in C and accesses the ATmega328P registers directly for the digital pins, the ADC and the LCD (no Arduino libraries such as `analogRead`, `digitalRead`, `digitalWrite`, `pinMode` or `LiquidCrystal`). The Arduino reads an LM35 temperature sensor on A0, converts the value to degrees Celsius and shows it on a 16x2 LCD together with a low limit (LL) and a high limit (LH). Two push buttons increase the limits (default LL = 20 C, LH = 27 C), and an alert LED turns on when the temperature is below LL or above LH. The code is split into independent modules: DIO, ADC, LCD and LM35.

## 2. Project Code

**Local Root Directory**
[link_to_local_root_directory](./code/Temperature_Modular/)

Source files:
* [Temperature_Modular.ino](./code/Temperature_Modular/Temperature_Modular.ino) (main program)
* [dio.h](./code/Temperature_Modular/dio.h) and [dio.ino](./code/Temperature_Modular/dio.ino) (DIO module)
* [ADC.h](./code/Temperature_Modular/ADC.h) and [ADC.ino](./code/Temperature_Modular/ADC.ino) (ADC module)
* [LM35.h](./code/Temperature_Modular/LM35.h) and [LM35.ino](./code/Temperature_Modular/LM35.ino) (temperature conversion module)
* [LCD.h](./code/Temperature_Modular/LCD.h) and [LCD.ino](./code/Temperature_Modular/LCD.ino) (LCD module)

## 3. Test Cases

Test cases are written in plain English and are executed manually (visual check of the LCD and the LED, comparison with a reference thermometer).
[test_cases](./test%20cases/assignment_test_cases.md)

## 4. Bill of Materials (BOM)

**BOM**
[bom_file](./BOM/bom.csv)

**Optimized BOM**
[optimized_bom_file](./BOM/optimized_bom.csv)

## 5. Video Demonstration

[recorded_video](./video/demo.mp4)

## 6. Design

[design_document](./project%20design/project_design.md)
