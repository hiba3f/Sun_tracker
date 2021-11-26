#include <Servo.h>

Servo horizontal; // Le servo horizental
int servoh = 180;
int servohLimitHigh = 175;
int servohLimitLow = 5;
// 65 degrees MAX

Servo vertical; // Le servo vertical
int servov = 45;
int servovLimitHigh = 50;
int servovLimitLow = 5;

// Connection des pins
// nom de la pin = analog pin;
int ldrlt = A0; //LDR haut gauche
int ldrrt = A2; //LDR haut droit
int ldrld = A1; //LDR bas gauche
int ldrrd = A3; //LDR bas droit

void setup(){
horizontal.attach(9); // Pin relie au servo horizontal
horizontal.write(180); // Angle maximale de rotation du moteur horizontal

vertical.attach(10); // Pin relie au servo horizontal
vertical.write(45); // Angle maximale de rotation du moteur vertical
delay(2500);
}

void loop() {
int lt = analogRead(ldrlt); // La propotion de tension cause par les variation de la resistance de la LDR haut gauche
int rt = analogRead(ldrrt); // La propotion de tension cause par les variation de la resistance de la LDR haut droit
int ld = analogRead(ldrld); // La propotion de tension cause par les variation de la resistance de la LDR bas gauche
int rd = analogRead(ldrrd); // La propotion de tension cause par les variation de la resistance de la LDR bas droit

int dtime = 10; // Résolution temporelle
int tol = 50; // Tolerance pour laquelle les moteurs changent de rotation

int avt = (lt + rt) / 2; // La moyenne de la proportion de tension cause par les LDR en haut
int avd = (ld + rd) / 2; // La moyenne de la proportion de tension cause par les LDR en bas
int avl = (lt + ld) / 2; // La moyenne de la proportion de tension cause par les LDR de gauche
int avr = (rt + rd) / 2; // La moyenne de la proportion de tension cause par les LDR de droite

int dvert = avt - avd; // La difference de moyenne entre le haut et le bas, si c'est positif la rotation en haut sinon la rotation en bas.
int dhoriz = avl - avr;// La difference de moyenne entre le droit et le gauche, si c'est positif la rotation a gauche sinon la rotation a droit.

if (-1*tol > dvert || dvert > tol) // Verification la tolerence angulaire dans le mouvement vertical, si elle est atteinte on change d'angle
 {
 if (avt > avd) // Il y a plus de luminosité en haut qu'en bas
 { servov = ++servov; // Servo doit avoir une rotation negative
   if (servov > servovLimitHigh)
   { servov = servovLimitHigh;} // Limite la rotation du servo pour des raisons de securite
  }
 else if (avt < avd) // Il y a plus de luminosité en bas qu'en haut
 { servov= --servov; // Servo doit avoir une rotation negative
   if (servov < servovLimitLow)
   { servov = servovLimitLow;} // Limite la rotation du servo pour des raisons de securite
 }
 vertical.write(servov);}

if (-1*tol > dhoriz || dhoriz > tol) // Verification la tolerence angulaire dans le mouvement vertical, si elle est atteinte on change d'angle
 {
 if (avl > avr) // Il y a plus de luminosité a gauche qu'a droite
 { servoh = --servoh; // Servo doit avoir une rotation negative
   if (servoh < servohLimitLow)
   { servoh = servohLimitLow; } // Limite la rotation du servo pour des raisons de securite
 }
 else if (avl < avr) // Il y a plus de luminosité a droite qu'a gauche
 { servoh = ++servoh; // Servo doit avoir une rotation positif
   if (servoh > servohLimitHigh)
   { servoh = servohLimitHigh; } // Limite la rotation du servo pour des raisons de securite
 }
 else if (avl = avr)
 { delay(5000); } // Si la luminosité de part et d'autre est la meme donc le tracker est bien centralisé, un delais de 5s avant de reverifier
 horizontal.write(servoh);
 }
 
 delay(dtime);}
