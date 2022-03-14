#include <Arduino.h>

#define pinHallSensor 7 // Eender welke digitale pin is ok, maar 7 is een cool priemgetal :)
#define pinSolenoid 13 // pin 13 is ook verbonden met een led op de arduino, handig dus om de schakeling te testen, ook als de solenoïd er niet aan hangt

bool isOpen; // variabele om bij te houden of de solenoïd open mag of niet
const int delayOpen = 1000; // tijd dat de solenoïd open is. Is in miliseconden, dus 1000 wil zeggen: 1 seconde

/**
 * Functie om te kijken of de magneet in de buurt van de hall sensor is
 * Als dat zo is, dan wordt de variabele isOpen op true gezet, anders op false
 */
void checkHallSensor() {
    if (digitalRead(pinHallSensor) == 0) {
      Serial.println("magneet gevonden");
      isOpen = true;
    } else {
      isOpen = false;
    }
}

/**
 * Functie om de solenoïd te schakelen, afhankelijk van de waarde in variabele isOpen 
 * als die true is, dan HIGH = stroom naar de tip120 transistor die de solenoïd stroom geeft
 */
void switchSolenoid() {
    if (isOpen) {
        digitalWrite(pinSolenoid, HIGH);
        delay(delayOpen);
        digitalWrite(pinSolenoid, LOW);
    }
}

/**
 * setup() wordt één keer uitgevoerd bij het opstarten van de arduino
 * 
 */
void setup() {
    pinMode(pinHallSensor, INPUT); // de poort van de hall sensor klaar maken om uit te lezen
    pinMode(pinSolenoid, OUTPUT); // de poort van de tip120 klaar maken om stroom naar te sturen
    digitalWrite(pinSolenoid, LOW); // LOW = geen stroom, dus de transistor en solenoïd staan uit

    Serial.begin(115200); // Via de Serial monitor kan je debug info uitlezen
    Serial.println("Magisch slot is opgestart...");
}

void loop() {
    checkHallSensor();
    switchSolenoid();
}