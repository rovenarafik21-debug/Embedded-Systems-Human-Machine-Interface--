*** Settings ***
Documentation    Assignment 2 - LM35 temperature monitor: 13 human-assisted hardware tests.
...              Uno: LM35=A0, LED=D8, LH button=D9, LL button=D10; defaults 20/27 C.
...              Perform each test on the real board, then choose PASS or FAIL.
...              Robot records operator-confirmed outcomes; it does not automatically measure hardware.
Library          Dialogs
Test Tags        manual    hardware

*** Test Cases ***
TC01 Startup Display and Default Limits
    [Documentation]    The first row shows the temperature in the format `T:xxx.xC` followed by `OK` or `ALERT`. The second row shows `LL:020 LH:027`.
    # Arrange and Act: follow the numbered instructions in the dialog.
    # Assert: compare your observation with every expected result.
    Manual Hardware Check    TC01    1. Connect the Arduino Uno to the computer (or press the reset button).\n2. Wait about one second for the LCD to initialize.\n3. Observe the LCD.    The first row shows the temperature in the format `T:xxx.xC` followed by `OK` or `ALERT`. The second row shows `LL:020 LH:027`.

TC02 Temperature Reading
    [Documentation]    The displayed temperature is approximately equal to the reference value (within about 1 degree Celsius). This 1 C tolerance is a proposed acceptance target, not a guaranteed sensor/system accuracy.
    # Arrange and Act: follow the numbered instructions in the dialog.
    # Assert: compare your observation with every expected result.
    Manual Hardware Check    TC02    1. Place a reference thermometer next to the LM35 sensor.\n2. Wait until both readings are stable.\n3. Compare the temperature on the LCD with the reference thermometer.    The displayed temperature is approximately equal to the reference value (within about 1 degree Celsius). This 1 C tolerance is a proposed acceptance target, not a guaranteed sensor/system accuracy.

TC03 Temperature Follows Changes
    [Documentation]    The displayed temperature rises while the sensor is warmed and falls back toward the room temperature after it is released.
    # Arrange and Act: follow the numbered instructions in the dialog.
    # Assert: compare your observation with every expected result.
    Manual Hardware Check    TC03    1. Hold the LM35 sensor by its plastic body between two fingers, without touching exposed leads for about 20 seconds.\n2. Observe the temperature on the LCD.\n3. Release the sensor and wait for it to cool down.\n4. Observe the temperature on the LCD again.    The displayed temperature rises while the sensor is warmed and falls back toward the room temperature after it is released.

TC04 No Alert Inside the Limits
    [Documentation]    The LED is off and the LCD shows `OK`.
    # Arrange and Act: follow the numbered instructions in the dialog.
    # Assert: compare your observation with every expected result.
    Manual Hardware Check    TC04    1. Reset the Arduino so that the default limits (LL = 20, LH = 27) are used.\n2. Make sure the temperature shown on the LCD is between 20 and 27 degrees.\n3. Observe the LED and the status text on the LCD.    The LED is off and the LCD shows `OK`.

TC05 Alert Above the High Limit
    [Documentation]    The LED turns on and the LCD shows `ALERT` while the temperature is above LH. After cooling into the valid LL-to-LH range, the LED turns off and the LCD shows `OK`.
    # Arrange and Act: follow the numbered instructions in the dialog.
    # Assert: compare your observation with every expected result.
    Manual Hardware Check    TC05    1. Reset the Arduino so that the default limits are used.\n2. Warm the LM35 sensor with fingers until the displayed temperature is above 27 degrees.\n3. Observe the LED and the status text on the LCD.\n4. Let the sensor cool down to between LL and LH (20 to 27 degrees inclusive).\nIf fingers cannot raise the temperature above LH, do not use a flame; report the unmet test condition as the failure reason.    The LED turns on and the LCD shows `ALERT` while the temperature is above LH. After cooling into the valid LL-to-LH range, the LED turns off and the LCD shows `OK`.

TC06 Alert Below the Low Limit
    [Documentation]    The LED turns on and the LCD shows `ALERT` as soon as the temperature is below LL.
    # Arrange and Act: follow the numbered instructions in the dialog.
    # Assert: compare your observation with every expected result.
    Manual Hardware Check    TC06    1. Reset the Arduino so that the default limits are used. The room temperature must be below 26 degrees for this test.\n2. Press the low-limit button (D10) repeatedly until LL is higher than the displayed temperature (LL can be increased up to 26).\n3. Observe the LED and the status text on the LCD.\nIf the room temperature cannot satisfy this precondition, report the unmet test condition as the failure reason.    The LED turns on and the LCD shows `ALERT` as soon as the temperature is below LL.

TC07 Increase the High Limit
    [Documentation]    LH changes from `027` to `028`, LL stays `020`, and the display updates on the next display update.
    # Arrange and Act: follow the numbered instructions in the dialog.
    # Assert: compare your observation with every expected result.
    Manual Hardware Check    TC07    1. Reset the Arduino (LH = 27).\n2. Press and release the high-limit button (D9) once.\n3. Observe the second row of the LCD.\nHold each press for about half a second and fully release before the next press.    LH changes from `027` to `028`, LL stays `020`, and the display updates on the next display update.

TC08 High Limit Wrap-Around
    [Documentation]    LH changes from `100` to `021` (LL + 1), and LL stays `020`.
    # Arrange and Act: follow the numbered instructions in the dialog.
    # Assert: compare your observation with every expected result.
    Manual Hardware Check    TC08    1. Reset the Arduino (LL = 20, LH = 27).\n2. Press the high-limit button (D9) repeatedly until the LCD shows `LH:100` (73 presses from the default value).\n3. Press the high-limit button once more.\nUse complete presses and releases; allow the LCD time to update.    LH changes from `100` to `021` (LL + 1), and LL stays `020`.

TC09 Increase the Low Limit
    [Documentation]    LL changes from `020` to `021`, LH stays `027`, and the display updates on the next display update.
    # Arrange and Act: follow the numbered instructions in the dialog.
    # Assert: compare your observation with every expected result.
    Manual Hardware Check    TC09    1. Reset the Arduino (LL = 20).\n2. Press and release the low-limit button (D10) once.\n3. Observe the second row of the LCD.\nHold each press for about half a second and fully release before the next press.    LL changes from `020` to `021`, LH stays `027`, and the display updates on the next display update.

TC10 Low Limit Wrap-Around
    [Documentation]    LL stops at `026` (one below LH) and the next press changes it to `000`. LH stays `027`.
    # Arrange and Act: follow the numbered instructions in the dialog.
    # Assert: compare your observation with every expected result.
    Manual Hardware Check    TC10    1. Reset the Arduino (LL = 20, LH = 27).\n2. Press the low-limit button (D10) six times and check that LL shows `026`.\n3. Press the low-limit button once more.\nUse complete presses and releases; allow the LCD time to update.    LL stops at `026` (one below LH) and the next press changes it to `000`. LH stays `027`.

TC11 One Change per Button Press
    [Documentation]    LH is `028` after the long press (increased only once) and `029` after the second press.
    # Arrange and Act: follow the numbered instructions in the dialog.
    # Assert: compare your observation with every expected result.
    Manual Hardware Check    TC11    1. Reset the Arduino (LH = 27).\n2. Press and hold the high-limit button (D9) for about 3 seconds.\n3. Release the button and observe the LCD.\n4. Press and release the button once more.\nUse complete presses and releases; allow the LCD time to update.    LH is `028` after the long press (increased only once) and `029` after the second press.

TC12 Reset Restores Default Limits
    [Documentation]    The LCD shows `LL:020 LH:027` again.
    # Arrange and Act: follow the numbered instructions in the dialog.
    # Assert: compare your observation with every expected result.
    Manual Hardware Check    TC12    1. Change both limits with the buttons (for example LH = 35 and LL = 23).\n2. Press the reset button on the Arduino.\n3. Observe the second row of the LCD.\nUse complete presses and releases; allow the LCD time to update.    The LCD shows `LL:020 LH:027` again.

TC13 Clean Display Update
    [Documentation]    The first row shows `OK` with no leftover characters from `ALERT`, and both rows keep their normal format.
    # Arrange and Act: follow the numbered instructions in the dialog.
    # Assert: compare your observation with every expected result.
    Manual Hardware Check    TC13    1. Reset the Arduino and warm the sensor above 27 degrees so that `ALERT` is shown.\n2. Let the sensor cool down so that the status changes to `OK`.\n3. Observe the first row of the LCD.    The first row shows `OK` with no leftover characters from `ALERT`, and both rows keep their normal format.

*** Keywords ***
Manual Hardware Check
    [Arguments]    ${test_id}    ${steps}    ${expected}
    Execute Manual Step
    ...    ${test_id} - Perform this test on your board.\n\n${steps}\n\nEXPECTED:\n${expected}\n\nClick PASS only if you observed every expected result. Otherwise click FAIL and explain what happened. If you cannot perform the test, explain that in the failure reason; this does not prove a firmware defect.
    ...    Expected result was not confirmed. Enter the actual observation or unmet test condition.
