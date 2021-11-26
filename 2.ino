#include<Servo.h>

Servo alt, az; // Defenir les variable des tensions controlant le servo.
int alt_Deg, az_Deg;  // Les angles des servo en degre.
const byte left=A0, right=A1, top=A2, bottom=A3;  // Introduire les pins des diviseurs de tension controle par les LDRs.
int L_value, R_value, T_value, B_value; // La valeur des diviseurs de tension causé par les LDRs.

int x,y;

void setup()
{
  Serial.begin(9600);
  az.attach(9);  // C'est le pin du servo controlant le mouvement horizental.
  alt.attach(10); // C'est le pin du servo controlant le mouvement vertical.
  
  // initialisation du servo to a une position initiale (90,30).
  Serial.println("SETTING UP SERVO");
  alt_Deg=20; az_Deg=20;
  az.write(90);
  alt.write(30);
  delay(1000);
}

void loop() {
  // Impose les variation maximale des servo par mesure de securite.
  if(az_Deg<=5)
    az_Deg=5;
  if(az_Deg>=175)
    az_Deg=175;
  if(alt_Deg<=5)
    alt_Deg=30;
  if(alt_Deg>=150)
    alt_Deg=150;
    
  // Lecture des valeurs de tension des pont des LDRs.
  L_value=analogRead(left);
  R_value=analogRead(right);
  T_value=analogRead(top);
  B_value=analogRead(bottom);
  
  // Identifier les différence de tension de sorte de trouve la luminaunité la plus importante.
  x=L_value-R_value;
  y=B_value-T_value;

  // La variation de position si la résolution est de 10.
  if(x<-7)
    az_Deg+=1;
  if(x>7)
    az_Deg-=1;
  if(y<-7)
    alt_Deg+=1;
  if(y>7)
    alt_Deg-=1;
  az.write(az_Deg);
  alt.write(alt_Deg);
  delay(70); // S'il retrouve bien la position optimale sinon il reprend l'algorithme.
}
