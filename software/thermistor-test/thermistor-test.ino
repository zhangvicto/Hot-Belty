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

//TIMING
const int delayTime = 10000;
int prevTime = 0;

int bangCycleTime = 1000; //DEFAULT cycle time
int bangPrevTime = 0;



//HEATER
const int heaterPin = 22;
const int buttonPin = 30;
int buttonState = 0;

//BANG BANG
const int goalTemp = 150;


//-----------------------------------------------------------------------------------------//


void setup(void) {
  pinMode(heaterPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  analogReference(EXTERNAL);
}

void loop(void) {
  float temperature1;
  float temperature2;

  int time_now = millis();
  if (time_now - prevTime > delayTime) {

    temperature1 = convert(takeSamples(thermPin1));
    temperature2 = convert(takeSamples(thermPin2));

    Serial.print("T1 ");
    Serial.print(temperature1);
    Serial.println(" C");

    //IS INSTALLED?
    Serial.print("T2 ");
    Serial.print(temperature2);
    Serial.println(" C");

    prevTime = time_now;
  }


  //-----------------------------------------------------------------------------------------//

  //BANG BANG CONTROL
  int bangTimeNow = millis();
  if ((bangTimeNow - bangPrevTime > bangCycleTime) && buttonState == 1) {

    //TAKE AVERAGE TEMP

    int currentTemp;
    if (temperature1 > 0 && temperature2 > 0) {
      currentTemp = (convert(takeSamples(thermPin1)) + convert(takeSamples(thermPin2))) / 2;
      Serial.print(currentTemp);
      Serial.println("C");
    }

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
    }
    delay(200);
  }
}


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
