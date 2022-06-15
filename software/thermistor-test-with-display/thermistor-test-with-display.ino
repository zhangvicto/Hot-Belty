//-----------------------------------------------------------------------------------------//

//THERM SETUP - B3950
// resistance at 25 degrees C
#define THERMISTORNOMINAL 100000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 100000

const int thermPin1 = A0;
const int thermPin2 = A1;
const int thermPin3 = A2;
const int thermPin4 = A3;


//TIMING
const int delayTime = 5000;
int prevTime = 0;

int bangPrevTime = 0;


//HEATER
const int heaterPin = 22;
const int buttonPin = 3; //30 for mega
int buttonState = 0;

//SWITCH
const int switchPin = 40;
int switchState = 0;

//DEBOUNCE
//unsigned long lastDebounceTime = 0;
//unsigned long debounceDelay = 50;


//MOTOR
const int motorPWM = 4;
const int motorIn1 = 23;
const int motorIn2 = 24;
int motorSpeed = 8;


//DISPLAY
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Arduino SPI library

//ST7789 TFT module connections
#define TFT_CS    10  // define chip select pin
#define TFT_DC     9  // define data/command pin
#define TFT_RST    8  // define reset pin, or set to -1 and connect to Arduino RESET pin

//Initialize Adafruit ST7789 TFT library
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
float p = 3.1415926;

//BANG BANG
const int goalTemp = 80;
const int hysteresis = 4;
int lastTemp = 0;
int isRising = 0;
int isDropping = 0;
int cooling = 0;


//-----------------------------------------------------------------------------------------//


void setup(void) {
  //heater
  pinMode(heaterPin, OUTPUT);
  digitalWrite(heaterPin, LOW);


  //button
  pinMode(buttonPin, INPUT_PULLUP);

  //switch
  pinMode(switchPin, INPUT);


  //Motor - remember to ground power supply with arduino
  pinMode(motorPWM, OUTPUT);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  //stop motor
  analogWrite(motorPWM, 0);
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);


  //DISPLAY
  tft.init(240, 240, SPI_MODE2);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);


  //Serial.begin(9600);
  analogReference(EXTERNAL);
}

void loop(void) {
  float temperature1;
  float temperature2;
  float temperature3;
  float temperature4;

  //Motor start
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, HIGH);
  analogWrite(motorPWM, map(motorSpeed, 0, 100, 75, 255));


  //Temperature Conversion
  int time_now = millis();
  if (time_now - prevTime > delayTime) {

    temperature1 = convert(takeSamples(thermPin1));
    temperature2 = convert(takeSamples(thermPin2));
    temperature3 = convert(takeSamples(thermPin3));
    temperature4 = convert(takeSamples(thermPin4));

    float temperatureAverage = (temperature1+temperature2+temperature3+temperature4)/4;

//    Serial.print("T1 ");
//    Serial.print(temperature1);
//    Serial.println(" C");
//
//    //IS INSTALLED?
//    Serial.print("T2 ");
//    Serial.print(temperature2);
//    Serial.println(" C");
//
//    Serial.print("T3 ");
//    Serial.print(temperature3);
//    Serial.println(" C");
//
//    Serial.print("T4 ");
//    Serial.print(temperature4);
//    Serial.println(" C");

    //Squares
    tft.drawRoundRect(10, 34, 106, 40, 5, ST77XX_WHITE);
    tft.fillRoundRect(10, 34, 106, 40, 5, ST77XX_WHITE);
    tft.drawRoundRect(124, 34, 106, 40, 5, ST77XX_WHITE);
    tft.fillRoundRect(124, 34, 106, 40, 5, ST77XX_WHITE);
    tft.drawRoundRect(10, 82, 106, 40, 5, ST77XX_WHITE);
    tft.fillRoundRect(10, 82, 106, 40, 5, ST77XX_WHITE);
    tft.drawRoundRect(124, 82, 106, 40, 5, ST77XX_WHITE);
    tft.fillRoundRect(124, 82, 106, 40, 5, ST77XX_WHITE);

    //Temperature
    drawtext("Temperature", ST77XX_WHITE, 2.5, 55, 10);
    drawtext("Sensor 1 " , ST77XX_BLACK, 2, 17, 39);
    drawfloat(temperature1, ST77XX_BLACK, 2, 28, 54); //change
    drawtext("C", ST77XX_BLACK, 2, 88, 54);

    drawtext("Sensor 2 " , ST77XX_BLACK, 2, 130, 39);
    drawfloat(temperature2, ST77XX_BLACK, 2, 141, 54); //change
    drawtext("C", ST77XX_BLACK, 2, 201, 54);

    drawtext("Sensor 3 " , ST77XX_BLACK, 2, 17, 87);
    drawfloat(temperature3, ST77XX_BLACK, 2, 28, 102); //change
    drawtext("C", ST77XX_BLACK, 2, 88, 102);

    drawtext("Sensor 4 " , ST77XX_BLACK, 2, 130, 87);
    drawfloat(temperature4, ST77XX_BLACK, 2, 141, 102); //change
    drawtext("C", ST77XX_BLACK, 2, 201, 102);

    //Chamber Status
    drawtext("Chamber Status", ST77XX_WHITE, 2.5, 35, 135);
    
    
    //default
    //if button not pressed
    if (buttonState == 0) {
      tft.fillCircle(40, 175, 15, ST77XX_GREEN);
      tft.drawCircle(40, 175, 15, ST77XX_WHITE);
      tft.drawCircle(40, 175, 14, ST77XX_WHITE);
      tft.drawCircle(40, 175, 13, ST77XX_WHITE);
      drawtext("!", ST77XX_WHITE, 2.5, 36, 168);
      tft.fillRect(80, 192, 140, 40, ST77XX_BLACK);
      drawtext("Idling at", ST77XX_WHITE, 2.5, 68, 168);
      drawfloat(temperatureAverage, ST77XX_WHITE, 2.5, 80, 192);
      drawtext("C", ST77XX_WHITE, 2.5, 150, 192); //use average
    } else if (buttonState == 1) {
      //heating
     tft.fillCircle(40, 175, 15, ST77XX_RED);
     tft.drawCircle(40, 175, 15, ST77XX_WHITE);
     tft.drawCircle(40, 175, 14, ST77XX_WHITE);
     tft.drawCircle(40, 175, 13, ST77XX_WHITE);
     drawtext("!", ST77XX_WHITE, 2.5, 36, 168);
     drawtext("Heating to", ST77XX_WHITE, 2.5, 65, 168);
     drawtext("180", ST77XX_WHITE, 3, 85, 192);
     drawtext("C", ST77XX_WHITE, 3, 145, 192);
    } else if (buttonState == 0 && cooling == 1) {
    //cooling
     tft.fillCircle(40, 175, 15, ST77XX_BLUE);
     tft.drawCircle(40, 175, 15, ST77XX_WHITE);
     tft.drawCircle(40, 175, 14, ST77XX_WHITE);
     tft.drawCircle(40, 175, 13, ST77XX_WHITE);
     drawtext("!", ST77XX_WHITE, 2.5, 36, 168);
     drawtext("Cooling to", ST77XX_WHITE, 2.5, 65, 168);
     drawtext("0", ST77XX_WHITE, 3, 100, 192);
     drawtext("C", ST77XX_WHITE, 3, 125, 192);
    }
    
    prevTime = time_now;
  }


  //-----------------------------------------------------------------------------------------//
  //                           HEATER CONTROL
  //-----------------------------------------------------------------------------------------//

  //BANG BANG CONTROL
  int bangTimeNow = millis();
  int bangCycleTime = 500; //DEFAULT cycle time
  int maxTemp = goalTemp + hysteresis;
  int minTemp = goalTemp - hysteresis;

  if ((bangTimeNow - bangPrevTime > bangCycleTime) && buttonState == 1) {

    //TAKE AVERAGE TEMP

    int currentTemp;
    if (temperature1 > 0 && temperature2 > 0) {
      currentTemp = (convert(takeSamples(thermPin1)) + convert(takeSamples(thermPin2)) + convert(takeSamples(thermPin3)) + convert(takeSamples(thermPin4))) / 2;
      //Serial.print(currentTemp);
      //Serial.println("C");
    }

    //Temp increasing or decreasing
    if (currentTemp - lastTemp > 0) {
      isRising = 1;
    } else {
      isDropping = 1;
    }

    lastTemp = currentTemp;

    //HEAT UP IF TOO LOW
    if (int(currentTemp) < goalTemp && goalTemp > 0) {
      digitalWrite(heaterPin, HIGH);
      Serial.println("Heating...");
    } else { //OFF IF TOO HIGH
      digitalWrite(heaterPin, LOW);
      Serial.println("Cooling...");
    }

    bangPrevTime = bangTimeNow;
  }


  //-----------------------------------------------------------------------------------------//


  //BUTTON

if (digitalRead(buttonPin) == LOW) {
    if (buttonState == 0) {
      //digitalWrite(heaterPin, HIGH);
      buttonState = 1;
      Serial.print("Heater ON");
    } else {
      digitalWrite(heaterPin, LOW);
      buttonState = 0;
      Serial.print("Heater OFF");
      cooling = 0;
    }
    delay(200);
  }

  //SWITCH
  if (digitalRead(switchPin) == HIGH) {
      switchState = 1;
  } else {
    switchState = 0;
  }

  

}
//END OF LOOP




//-----------------------------------------------------------------------------------------//
//                                      FUNCTIONS
//-----------------------------------------------------------------------------------------//

float takeSamples(int THERMISTORPIN) {
  uint8_t i;
  float average;
  int samples[NUMSAMPLES];
  for (i = 0; i < NUMSAMPLES; i++) {
    // take N samples in a row, with a slight delay
    samples[i] = analogRead(THERMISTORPIN);
    delay(10);
  }

  // average all the samples out
  average = 0;
  for (i = 0; i < NUMSAMPLES; i++) {
    average += samples[i];
  }
  average /= NUMSAMPLES;

  // convert the value to resistance
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;

  return average;
}

float convert(float average) {
  float temp = 0.0;

  float steinhart;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert absolute temp to C

  return steinhart;
}

void drawtext(char *text, uint16_t color, uint8_t textSize, int x, int y) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.print(text);
}

void drawfloat(float text, uint16_t color, uint8_t textSize, int x, int y) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.print(text, 2);
}

char floatToChar(float input) {
  String floatString;
  char output[5];
  floatString.toCharArray(output, 5);

  return output;
}
