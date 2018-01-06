///////////////////////////////////////////////
int Time_green = 8;		//Zeit ab welcher grüne LED angeschalten werden soll
int Time_yellow = 10;	//Zeit ab welcher gelbe LED angeschalten werden soll
int Time_red = 12; 		//Zeit ab welcher rote LED angeschalten werden soll
int Statuszeit = 2000 ;	//Zeit LED aktiv in Millisekunden
int LED_Zeit = 5000 ;	//Zeit LED aktiv in Millisekunden

///////////////////////////////////////////////





int Schalter = 4;
int LED_green = 6;
int LED_yellow = 8;
int LED_red = 10;

int aktuellerSchalterzustand = 0;
int letzterSchalterzustand = 0;
int Zeitmessung = 0;

long startTime ;
float elapsedTime ;
float elapsedHours ;
float elapsedMinutes ;
float elapsedSeconds ;




void setup()
{
pinMode(Schalter, INPUT);
pinMode(LED_green, OUTPUT);
pinMode(LED_yellow, OUTPUT);
pinMode(LED_red, OUTPUT);

Serial.begin(9600);
	
}

void loop()
{
	aktuellerSchalterzustand = digitalRead(Schalter);
	
	
	if (aktuellerSchalterzustand == 1 && letzterSchalterzustand == 0 && Zeitmessung == false)
	{
		startTime = millis();
		Zeitmessung = true;
		
		digitalWrite(LED_green, HIGH);
		digitalWrite(LED_yellow, HIGH);		//Zeige start der Messung durch aufblinken der Lichter an
		digitalWrite(LED_red, HIGH);	
		delay(Statuszeit);
		
		digitalWrite(LED_green, LOW);
		digitalWrite(LED_yellow, LOW);		//Zeige start der Messung durch aufblinken der Lichter an
		digitalWrite(LED_red, LOW);
		
		letzterSchalterzustand = aktuellerSchalterzustand;

		Serial.println("Timer gestartet");
		

	}

	else if (aktuellerSchalterzustand == 1 && letzterSchalterzustand == 1 && Zeitmessung == true)
	{
		elapsedTime = millis() - startTime;
		elapsedHours = elapsedTime / 3600000;
		elapsedMinutes = elapsedTime / 60000;
		elapsedSeconds = elapsedTime / 1000;
		Zeitmessung = false;
		
		Serial.print("Timer gestoppt bei H/M/S: ");
		Serial.print(elapsedHours, 1);
		Serial.print(" / ");
		Serial.print(elapsedMinutes, 1);
		Serial.print(" / ");
		Serial.println(elapsedSeconds, 1);

		
		if (elapsedSeconds <= Time_green)
		{
			digitalWrite(LED_green, HIGH);
			delay(LED_Zeit);
			digitalWrite(LED_green, LOW);
		}
		
		if (elapsedSeconds > Time_green && elapsedSeconds <= Time_yellow)
		{
			digitalWrite(LED_yellow, HIGH);
			delay(LED_Zeit);
			digitalWrite(LED_yellow, LOW);		
		}
		
		if (elapsedSeconds > Time_yellow && elapsedSeconds <= Time_red)
		{
			digitalWrite(LED_red, HIGH);
			delay(LED_Zeit);
			digitalWrite(LED_red, LOW);		
		}
		
		letzterSchalterzustand = 0;

		
	}
	
	else if (aktuellerSchalterzustand == 0 && letzterSchalterzustand == 0 && Zeitmessung == false)
	{
		digitalWrite(LED_green, HIGH);
		digitalWrite(LED_red, HIGH);
		delay(500);
		digitalWrite(LED_green, LOW);
		digitalWrite(LED_red, LOW);
		delay(500);
		
	}
}


