#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
const int switchPin = 6;
const int temperaturePin = A0;
int switchState = 0; 
int prevSwitchState = 0;
int reply;
int currentPosition = (1);
int hour = 0;
int minute = 0;
int second = 0;
int tempSensorValue = 0;
float voltage = 0;
int temp = 0;

void setup (){
    int prevPosition = (-1);
    lcd.begin(16,   2);
    pinMode(switchPin, INPUT);
    lcd.clear();
    lcd.setCursor(0,0);
}

void mode0TempDisplay(){
    lcd.setCursor(0,0);
    lcd.print("Temp:");
    lcd.setCursor(0,1);
    tempSensorValue = analogRead(temperaturePin);
    temp = ((((tempSensorValue / 1024.0) * 5) - 0.5 ) * 100);
    lcd.print(temp);
    lcd.print(" *");
    delay(100);
}

void mode1HourDisplay(){

    lcd.setCursor(0,0);
    lcd.print("Time passed:");
    lcd.setCursor(0,1);
    second++;
    if (second >= 60){
        minute++;
        second = 0;
    }
    if (minute >= 60){
        hour++;
        minute = 0;
    }
    if (hour >= 24)
    {
        hour = 0;
    }

    lcd.print(hour);
    lcd.print(":");
    lcd.print(minute);
    lcd.print(":");
    lcd.print(second);
    delay(1000);
    lcd.clear();
}

void loop (){
    switchState = digitalRead(switchPin);
    
    if (switchState != prevSwitchState){
        if(switchState == HIGH){
            currentPosition++;
            lcd.clear();
        }
    }
    prevSwitchState = switchState;
    switch (currentPosition)
    {
    case 0:
        mode0TempDisplay();

    break;
    case 1:
        mode1HourDisplay();

    break;
    default:
        currentPosition = (-1);
        lcd.clear();

        break;
    }
}