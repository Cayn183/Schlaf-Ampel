/*******************************************Veränderbare Variablen************************************************/

int Time_green = 8;		//Zeit ab welcher grüne LED angeschalten werden soll
int Time_yellow = 10;	//Zeit ab welcher gelbe LED angeschalten werden soll
int Time_red = 12; 		//Zeit ab welcher rote LED angeschalten werden soll
int Statuszeit = 2000 ;	//Zeit LED aktiv in Millisekunden
int LED_Zeit = 5000 ;	//Zeit LED/Anzeige aktiv in Millisekunden

/**************************************************Libarys********************************************************/
// Time - Version: Latest 
#include <Time.h>
#include <TimeLib.h>
// LiquidCrystal I2C - Version: Latest 
#include <Wire.h>
#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

#define GPIO_ADDR   0x27
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);    // set the LCD I2C address

/*********************************************feste Variablen******************************************************/

int Schalter = 4;
int LED_green = 6;
int LED_yellow = 8;
int LED_red = 10;
int Backlight = 2;

int aktuellerSchalterzustand = 0;
int letzterSchalterzustand = 0;
int Zeitmessung = 0;

long startTime ;
float elapsedTime ;
float elapsedHours ;
float elapsedMinutes ;
float elapsedSeconds ;
int seconds ;

/*****************************************************Setup********************************************************/

void setup()
{
pinMode(Schalter, INPUT);
pinMode(LED_green, OUTPUT);
pinMode(LED_yellow, OUTPUT);
pinMode(LED_red, OUTPUT);
pinMode(Backlight, OUTPUT);

Serial.begin(9600);
lcd.begin(16, 2);
digitalWrite(Backlight, LOW);
}

/**************************************************LOOP************************************************************/
void loop()
{
	aktuellerSchalterzustand = digitalRead(Schalter);

	
	if (aktuellerSchalterzustand == 1 && letzterSchalterzustand == 0 && Zeitmessung == false)
	{
		startTime = millis();
		setTime(0);
		Zeitmessung = true;
    
    digitalWrite(Backlight, HIGH);
    lcd.begin(16, 2);
		Serial.println("Timer gestartet");
		lcd.setCursor(0,0);
    lcd.print("Timer gestartet");
		lcd.setCursor(0,2);
		lcd.print("Gute Nacht :)");
		
		digitalWrite(LED_green, HIGH);
		digitalWrite(LED_yellow, HIGH);		//Zeige start der Messung durch aufblinken der Lichter an
		digitalWrite(LED_red, HIGH);	
		delay(Statuszeit);
		
		digitalWrite(LED_green, LOW);
		digitalWrite(LED_yellow, LOW);		//Zeige start der Messung durch aufblinken der Lichter an
		digitalWrite(LED_red, LOW);
		
		letzterSchalterzustand = 1;
		
		delay(5000);
		lcd.clear();
		digitalWrite(Backlight, LOW);
	}

	else if (aktuellerSchalterzustand == 0 && letzterSchalterzustand == 1 && Zeitmessung == true)
	{
		elapsedTime = millis() - startTime;
		elapsedHours = elapsedTime / 3600000;
		elapsedMinutes = elapsedTime / 60000;
		elapsedSeconds = elapsedTime / 1000;
		Zeitmessung = false;
		
    digitalWrite(Backlight, HIGH);
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("Schlafenszeit: ");
		lcd.setCursor(0,1);
		lcd.print(hour()) && lcd.print("h ") && lcd.print(minute()) && lcd.print("m ") && lcd.print(second()) && lcd.print("s ");
		
		if (elapsedSeconds <= Time_green)
		{
			digitalWrite(LED_green, HIGH);
			delay(LED_Zeit);
			digitalWrite(LED_green, LOW);
			lcd.clear();
			digitalWrite(Backlight, LOW);
		}
		
		if (elapsedSeconds > Time_green && elapsedSeconds <= Time_yellow)
		{
			digitalWrite(LED_yellow, HIGH);
			delay(LED_Zeit);
			digitalWrite(LED_yellow, LOW);
			lcd.clear();
			digitalWrite(Backlight, LOW);			
		}
		
		if (elapsedSeconds > Time_yellow)
		{
			digitalWrite(LED_red, HIGH);
			delay(LED_Zeit);
			digitalWrite(LED_red, LOW);
			lcd.clear();
			digitalWrite(Backlight, LOW);
		}
		
		letzterSchalterzustand = 0;

		
	}
	
	else if (aktuellerSchalterzustand == 0 && letzterSchalterzustand == 0 && Zeitmessung == false)
	{

		
	}
}


