#include<EEPROM.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);




int btn1 = 3;
int btn2 = 5;
int btn3 = 7;
int led1 = 10;
int led2 = 11;

int menu_select = 0;
int menu_select_value = 0;

int btn_count = 0;
int led1_address = 4;
int led2_address = 5;
byte btn_value;

byte led1_value;
byte led2_value;

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  led1_value = EEPROM.read(led1_address);//EEPROM.read(ADDRESS 0-255);
  led2_value = EEPROM.read(led2_address);//EEPROM.read(ADDRESS 0-255);


  Serial.println("Device restarted");
  Serial.println("Reading memory");
  Serial.print("LED1 :"); Serial.println(led1_value);
  Serial.print("LED2 :"); Serial.println(led2_value);
  delay(2000);

  // initialize the OLED object
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  // Clear the buffer.
  display.clearDisplay();

}

void loop() {

  String led1_state = (led1_value == 10) ? "LOW" : ((led1_value == 127) ? "MEDIUM" : "HIGH");
  String led2_state = (led2_value == 1) ? "ON" : "OFF";

  analogWrite(led1, led1_value);
  analogWrite(led2, led2_value);

  // Display Text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 1);
  display.print("LED1:"); display.print(led1_state);
  display.setCursor(70, 1);
  display.print(",LED2:"); display.println(led2_state);
  display.display();





  /**************Select menu start***************************/
  int menu_select_button = digitalRead(btn3);
  if (menu_select_button == LOW) {
    menu_select++;
    Serial.println(menu_select);
  }
  if (menu_select == 3) {
    menu_select = 1;
  }
  /************select menu end****************************/

  /*************select menu value start*******************/
  int button1 = digitalRead(btn1);
  if (button1 == LOW) {
    menu_select_value++;
    //    Serial.println(mode_select_value);
  }
  if (menu_select_value == 4) {
    menu_select_value = 1;
  }
  /*************select menu value start end***************/


  int back_button = digitalRead(btn2);
  if (back_button == LOW) {
    menu_select_value = 0;
    resetFunc();  //call reset
  }


  delay(150);



  switch (menu_select) {
    case 0:
      menu_select = 1;
      break;

    case 1:    // your hand is on the sensor
      Serial.print("****LED1**********:");
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 1);
      display.print("LED1:"); display.print(led1_state);
      display.setCursor(70, 1);
      display.print(",LED2:"); display.println(led2_state);
      display.setCursor(0, 15);
      display.setTextSize(1);
      display.println("--------LED1---------");
      display.setTextColor(WHITE);
      display.print("");
      display.print(">LED1 :"); display.print("  10"); display.print("  127"); display.println("  255");
      display.print(" LED2 :"); display.print("  ON"); display.println("  OFF");


      switch (menu_select_value) {
        case 0:
          Serial.println("please select value");
          break;
        case 1:
          Serial.println("10");
          EEPROM.update(led1_address, 10);
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0, 1);
          display.print("LED1:"); display.print(led1_state);
          display.setCursor(70, 1);
          display.print(",LED2:"); display.println(led2_state);
          display.setCursor(0, 15);
          display.println("--------LED1---------");
          display.setTextColor(WHITE);
          display.print("");
          display.print(">LED1 :"); display.print(" >10"); display.print("  127"); display.println("  255");
          display.print(" LED2 :"); display.print("  ON"); display.println("  OFF");

          display.setCursor(0, 45);
          display.println("Brightness LOW");
          break;

        case 2:
          Serial.println("127");
          EEPROM.update(led1_address, 127);
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0, 1);
          display.print("LED1:"); display.print(led1_state);
          display.setCursor(70, 1);
          display.print(",LED2:"); display.println(led2_state);
          display.setCursor(0, 15);
          display.println("--------LED1---------");
          display.setTextColor(WHITE);
          display.print("");
          display.print(">LED1 :"); display.print("  10"); display.print(" >127"); display.println("  255");
          display.print(" LED2 :"); display.print("  ON"); display.println("  OFF");

          display.setCursor(0, 45);
          display.println("Brightness MEDIUM");
          break;

        case 3:
          Serial.println("255");
          EEPROM.update(led1_address, 255);
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0, 1);
          display.print("LED1:"); display.print(led1_state);
          display.setCursor(70, 1);
          display.print(",LED2:"); display.println(led2_state);
          display.setCursor(0, 15);
          display.println("--------LED1---------");
          display.setTextColor(WHITE);
          display.print("");
          display.print(">LED1 :"); display.print("  10"); display.print("  127"); display.println(" >255");
          display.print(" LED2 :"); display.print("  ON"); display.println("  OFF");

          display.setCursor(0, 45);
          display.println("Brightness HIGH");
          break;
      }
      display.display();
      break;


    case 2:    // your hand is on the sensor
      Serial.print("****LED2**********:");
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0, 1);
      display.print("LED1:"); display.print(led1_state);
      display.setCursor(70, 1);
      display.print(",LED2:"); display.println(led2_state);
      display.setCursor(0, 15);
      display.setTextSize(1);
      display.println("--------LED2---------");
      display.setTextColor(WHITE);
      display.print("");
      display.print(" LED1 :"); display.print("  10"); display.print("  127"); display.println("  255");
      display.print(">LED2 :"); display.print("  ON"); display.println("  OFF");


      switch (menu_select_value) {
        case 0:
          Serial.println("please select value");
          break;
        case 1:
          Serial.println("1");
          EEPROM.update(led2_address, 1);
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0, 1);
          display.print("LED1:"); display.print(led1_state);
          display.setCursor(70, 1);
          display.print(",LED2:"); display.println(led2_state);
          display.setCursor(0, 15);
          display.println("--------LED2---------");
          display.setTextColor(WHITE);
          display.print("");
          display.print(" LED1 :"); display.print("  10"); display.print("  127"); display.println("  255");
          display.print(">LED2 :"); display.print(" >ON"); display.println("  OFF");
          display.display();
          break;
        case 2:
          Serial.println("0");
          EEPROM.update(led2_address, 0);
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0, 1);
          display.print("LED1:"); display.print(led1_state);
          display.setCursor(70, 1);
          display.print(",LED2:"); display.println(led2_state);
          display.setCursor(0, 15);
          display.println("--------LED2---------");
          display.setTextColor(WHITE);
          display.print("");
          display.print(" LED1 :"); display.print("  10"); display.print("  127"); display.println("  255");
          display.print(">LED2 :"); display.print("  ON"); display.println(" >OFF");
          display.display();
          break;
        case 3:
          menu_select_value = 1;
          break;
      }
      display.display();
      break;

  }
}
