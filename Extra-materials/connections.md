# Arduino Circuit Connection Table (Without Stepper Motor)

| Component | Arduino Pin | Component Pin / Signal | Notes |
|---|---|---|---|
| OLED Display (SSD1306 I2C) | A4 | SDA | I2C data line |
| OLED Display (SSD1306 I2C) | A5 | SCL | I2C clock line |
| OLED Display (SSD1306 I2C) | 5V | VCC | Power |
| OLED Display (SSD1306 I2C) | GND | GND | Ground |
| Servo Motor | 9 | Signal | PWM control pin |
| Servo Motor | 5V | VCC | Power |
| Servo Motor | GND | GND | Ground |
| Keypad Row 1 | 8 | R1 | 4x4 keypad |
| Keypad Row 2 | 7 | R2 |  |
| Keypad Row 3 | 6 | R3 |  |
| Keypad Row 4 | 5 | R4 |  |
| Keypad Column 1 | 4 | C1 |  |
| Keypad Column 2 | 3 | C2 |  |
| Keypad Column 3 | 2 | C3 |  |
| Keypad Column 4 | A3 | C4 | Analog pin used as digital |
| Buzzer (+) | A2 | Positive terminal | Active buzzer recommended |
| Buzzer (-) | GND | Negative terminal | Ground |

# Pin Usage Summary

| Arduino Pin | Connected Device |
|---|---|
| A2 | Buzzer |
| A3 | Keypad C4 |
| A4 | OLED SDA |
| A5 | OLED SCL |
| 2 | Keypad C3 |
| 3 | Keypad C2 |
| 4 | Keypad C1 |
| 5 | Keypad R4 |
| 6 | Keypad R3 |
| 7 | Keypad R2 |
| 8 | Keypad R1 |
| 9 | Servo Signal |

# Components Needed

- Arduino Uno
- 4x4 Matrix Keypad
- SSD1306 OLED Display (I2C, 128x32)
- SG90
- Active Buzzer
- Jumper wires
- Breadboard
- 14x 9v battery
- High guage wire
- Push button

  # Bomb Wiring
  Wire all the 9v batteries in serial and connect a button to positive, then connect the other end of the button to an LED.
