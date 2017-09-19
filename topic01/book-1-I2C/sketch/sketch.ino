/******************************************************************************
I2C Exercise
Sept 15th 2017
~

This sketch configures the TMP102 temperature sensor and prints the
temperature on a Grove-LCD RGB 

Resources:
Wire.h (included with Arduino IDE)
SparkFunTMP102.h
rgb_lcd.h

Development environment specifics:
Arduino 1.8 IDE
Arduino Uno

******************************************************************************/

#include <Wire.h> // Used to establied serial communication on the I2C bus
#include <SparkFunTMP102.h> // Used to send and recieve specific information from our sensor
#include <rgb_lcd.h> // Used to send temp information to LCD

const int ALERT_PIN = A3;

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

TMP102 tmpSensor(0x48); // Initialize sensor at I2C address 0x48


void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud
  pinMode(ALERT_PIN,INPUT);  // Declare alertPin as an input
  tmpSensor.begin();  // Join I2C bus

  // Initialize tmpSensor settings
  // These settings are saved in the sensor, even if it loses power

  // set the number of consecutive faults before triggering alarm.
  // 0-3: 0:1 fault, 1:2 faults, 2:4 faults, 3:6 faults.
  tmpSensor.setFault(0);  // Trigger alarm immediately

  // set the polarity of the Alarm. (0:Active LOW, 1:Active HIGH).
  tmpSensor.setAlertPolarity(1); // Active HIGH

  // set the sensor in Comparator Mode (0) or Interrupt Mode (1).
  tmpSensor.setAlertMode(0); // Comparator Mode.

  // set the Conversion Rate (how quickly the sensor gets a new reading)
  //0-3: 0:0.25Hz, 1:1Hz, 2:4Hz, 3:8Hz
  tmpSensor.setConversionRate(2);

  //set Extended Mode.
  //0:12-bit Temperature(-55C to +128C) 1:13-bit Temperature(-55C to +150C)
  tmpSensor.setExtendedMode(0);

  //set T_HIGH, the upper limit to trigger the alert on
  tmpSensor.setHighTempC(29.4); // set T_HIGH in C

  //set T_LOW, the lower limit to shut turn off the alert
  tmpSensor.setLowTempC(26.67); // set T_LOW in C


   // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    lcd.print("hello, IoT3");

    delay(1000);
}

void loop()
{
  float temperature;
  boolean alertPinState, alertRegisterState;

  // Turn sensor on to start temperature measurement.
  // Current consumtion typically ~10uA.
  tmpSensor.wakeup();

  // read temperature data
  temperature = tmpSensor.readTempC();

  // Check for Alert
  alertPinState = digitalRead(ALERT_PIN); // read the Alert from pin
  alertRegisterState = tmpSensor.alert();   // read the Alert from register

  // Place sensor in sleep mode to save power.
  // Current consumtion typically <0.5uA.
  tmpSensor.sleep();

  // Print temperature and alarm state
  Serial.print("Temp: ");
  Serial.print(temperature);

  Serial.print("\tAlert Pin: ");
  Serial.print(alertPinState);

  Serial.print("\tAlert Register: ");
  Serial.println(alertRegisterState);

   
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print("Temp: ");
  lcd.print(temperature);

  delay(1000);  // Wait 1000ms
}
