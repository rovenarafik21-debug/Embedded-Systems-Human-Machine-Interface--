### Test Case 1: Startup Display and Default Limits

**Objective:** Verify that the system starts correctly and shows the default limits.

**Test Steps:**

1. Connect the Arduino Uno to the computer (or press the reset button).
2. Wait about one second for the LCD to initialize.
3. Observe the LCD.

**Expected Result:** The first row shows the temperature in the format `T:xxx.xC` followed by `OK` or `ALERT`. The second row shows `LL:020 LH:027`.

---

### Test Case 2: Temperature Reading

**Objective:** Verify that the displayed temperature matches the real temperature.

**Test Steps:**

1. Place a reference thermometer next to the LM35 sensor.
2. Wait until both readings are stable.
3. Compare the temperature on the LCD with the reference thermometer.

**Expected Result:** The displayed temperature is approximately equal to the reference value (within about 1 degree Celsius).

---

### Test Case 3: Temperature Follows Changes

**Objective:** Verify that the displayed temperature changes when the sensor temperature changes.

**Test Steps:**

1. Hold the LM35 sensor between two fingers for about 20 seconds.
2. Observe the temperature on the LCD.
3. Release the sensor and wait for it to cool down.
4. Observe the temperature on the LCD again.

**Expected Result:** The displayed temperature rises while the sensor is warmed and falls back toward the room temperature after it is released.

---

### Test Case 4: No Alert Inside the Limits

**Objective:** Verify that the alert LED stays off when the temperature is between LL and LH.

**Test Steps:**

1. Reset the Arduino so that the default limits (LL = 20, LH = 27) are used.
2. Make sure the temperature shown on the LCD is between 20 and 27 degrees.
3. Observe the LED and the status text on the LCD.

**Expected Result:** The LED is off and the LCD shows `OK`.

---

### Test Case 5: Alert Above the High Limit

**Objective:** Verify that the alert turns on when the temperature is above LH.

**Test Steps:**

1. Reset the Arduino so that the default limits are used.
2. Warm the LM35 sensor with fingers until the displayed temperature is above 27 degrees.
3. Observe the LED and the status text on the LCD.
4. Let the sensor cool down below 27 degrees.

**Expected Result:** The LED turns on and the LCD shows `ALERT` while the temperature is above LH. After cooling down, the LED turns off and the LCD shows `OK`.

---

### Test Case 6: Alert Below the Low Limit

**Objective:** Verify that the alert turns on when the temperature is below LL.

**Test Steps:**

1. Reset the Arduino so that the default limits are used. The room temperature must be below 26 degrees for this test.
2. Press the low-limit button (D10) repeatedly until LL is higher than the displayed temperature (LL can be increased up to 26).
3. Observe the LED and the status text on the LCD.

**Expected Result:** The LED turns on and the LCD shows `ALERT` as soon as the temperature is below LL.

---

### Test Case 7: Increase the High Limit

**Objective:** Verify that the high-limit button increases LH by one degree.

**Test Steps:**

1. Reset the Arduino (LH = 27).
2. Press and release the high-limit button (D9) once.
3. Observe the second row of the LCD.

**Expected Result:** LH changes from `027` to `028`, LL stays `020`, and the display updates immediately after the press.

---

### Test Case 8: High Limit Wrap-Around

**Objective:** Verify that LH wraps around after 100.

**Test Steps:**

1. Reset the Arduino (LL = 20, LH = 27).
2. Press the high-limit button (D9) repeatedly until the LCD shows `LH:100` (73 presses from the default value).
3. Press the high-limit button once more.

**Expected Result:** LH changes from `100` to `021` (LL + 1), and LL stays `020`.

---

### Test Case 9: Increase the Low Limit

**Objective:** Verify that the low-limit button increases LL by one degree.

**Test Steps:**

1. Reset the Arduino (LL = 20).
2. Press and release the low-limit button (D10) once.
3. Observe the second row of the LCD.

**Expected Result:** LL changes from `020` to `021`, LH stays `027`, and the display updates immediately after the press.

---

### Test Case 10: Low Limit Wrap-Around

**Objective:** Verify that LL never reaches LH and wraps around to zero.

**Test Steps:**

1. Reset the Arduino (LL = 20, LH = 27).
2. Press the low-limit button (D10) six times and check that LL shows `026`.
3. Press the low-limit button once more.

**Expected Result:** LL stops at `026` (one below LH) and the next press changes it to `000`. LH stays `027`.

---

### Test Case 11: One Change per Button Press

**Objective:** Verify that holding a button down changes the limit only once.

**Test Steps:**

1. Reset the Arduino (LH = 27).
2. Press and hold the high-limit button (D9) for about 3 seconds.
3. Release the button and observe the LCD.
4. Press and release the button once more.

**Expected Result:** LH is `028` after the long press (increased only once) and `029` after the second press.

---

### Test Case 12: Reset Restores Default Limits

**Objective:** Verify that the limits return to their defaults after a reset.

**Test Steps:**

1. Change both limits with the buttons (for example LH = 35 and LL = 23).
2. Press the reset button on the Arduino.
3. Observe the second row of the LCD.

**Expected Result:** The LCD shows `LL:020 LH:027` again.

---

### Test Case 13: Clean Display Update

**Objective:** Verify that no old characters stay on the LCD when the status text changes.

**Test Steps:**

1. Reset the Arduino and warm the sensor above 27 degrees so that `ALERT` is shown.
2. Let the sensor cool down so that the status changes to `OK`.
3. Observe the first row of the LCD.

**Expected Result:** The first row shows `OK` with no leftover characters from `ALERT`, and both rows keep their normal format.
