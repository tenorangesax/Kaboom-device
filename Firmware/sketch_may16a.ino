#include <Stepper.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

// display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// stepper
const int stepsPerRevolution = 2038;
Stepper myStepper = Stepper(stepsPerRevolution, A0, 11, 12, 10);

// servo
Servo myServo;
const int pinSignal = 9;

// keypad
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 8, 7, 6, 5 };
byte colPins[COLS] = { 4, 3, 2, A3 };
Keypad sixteenKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// code logic
const String SECRET_CODE = "1234";
String inputCode = "";
const int BUZZER_PIN = A2;
bool programDone = false;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(100000);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Display not found!");
    for (;;);
  }
  Serial.println("Display OK");

  myServo.attach(pinSignal);
  myServo.write(0);
  pinMode(BUZZER_PIN, OUTPUT);
  myStepper.setSpeed(15);

  showPrompt();
}

void loop() {
  if (programDone) return;

  char key = sixteenKeypad.getKey();
  if (!key) return;

  if (key == '#' || key == '*') {
    if (inputCode.length() == 0) return;
  }

  if (key == '*') {
    inputCode.remove(inputCode.length() - 1);
    showInput();
    return;
  }

  if (key == '#') {
    if (inputCode.length() != 4) {
      showMessage("Need 4 digits!", true);
      delay(1500);
      inputCode = "";
      showPrompt();
      return;
    }
    checkCode();
    return;
  }

  if (inputCode.length() < 4) {
    inputCode += key;
    showInput();
  }
}

void checkCode() {
  if (inputCode == SECRET_CODE) {
    showMessage("ACCESS GRANTED", false);
    Serial.println("Correct code entered.");
    programDone = true;
  } else {
    showMessage("WRONG CODE", true);
    Serial.println("Wrong code: " + inputCode);
    triggerWrongCode();
    inputCode = "";
    showPrompt();
  }
}

void triggerWrongCode() {
  unsigned long buzzerToggle = millis();
  bool buzzerOn = false;

  int stepperStepsLeft = stepsPerRevolution / 2;

  while (stepperStepsLeft > 0) {
    if (millis() - buzzerToggle >= 1000) {
      buzzerOn = !buzzerOn;
      digitalWrite(BUZZER_PIN, buzzerOn ? HIGH : LOW);
      buzzerToggle = millis();
    }

    int chunk = min(4, stepperStepsLeft);
    myStepper.step(chunk);
    stepperStepsLeft -= chunk;
  }

  int servoPos = 0;
  int servoDir = 1;
  unsigned long servoNextMove = millis();
  unsigned long servoStart = millis();

  myServo.write(180);
  delay(500); 

while (servoPos <= 0) {
  if (millis() - buzzerToggle >= 1000) {
    buzzerOn = !buzzerOn;
    digitalWrite(BUZZER_PIN, buzzerOn ? HIGH : LOW);
    buzzerToggle = millis();
  }

  if (millis() >= servoNextMove) {
    myServo.write(servoPos);
    servoPos++;
    servoNextMove = millis() + 50;
  }
}

digitalWrite(BUZZER_PIN, LOW);
myServo.write(180);

  digitalWrite(BUZZER_PIN, LOW);
  myServo.write(0);
}

void showPrompt() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Enter 4-digit code:");
  display.display();
}

void showInput() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Enter code:");
  display.setTextSize(2);
  display.setCursor(0, 20);
  for (int i = 0; i < inputCode.length(); i++) {
    display.print("* ");
  }
  display.display();
}

void showMessage(String msg, bool isError) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(isError ? "!!! ERROR !!!" : ">>> SUCCESS <<<");
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.print(msg);
  display.display();
}