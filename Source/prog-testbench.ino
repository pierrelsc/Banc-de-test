//**************************************************************
//Commande de moteur pas-à-pas unipolaire 4 fils
//tiptopboards.com 05/12/2013
// Driver ULN2003 et moteur réducté au 1:64
//
//**************************************************************
//Inclure la librairie stepper.h
 #include <Stepper.h>
 #define STEPS 100
 #define Fin_C_Bas 5
 #define CapteurBasOn digitalRead (Fin_C_Bas)  //capteur fermé au repos, donc actif LOW

 int state = 1;
 int cpt =0;
 int trig = 2;
 int echo = 3;
 long dist;

  //Créer une instance de la classe stepper
  //Le moteur (fils 1 2 3 4) est branché sur les sorties 8 9 10 11 de l'Arduino (et sur GND, +V)
  Stepper small_stepper(STEPS, 8, 10, 9, 11);     // Sens horaire
 
  Stepper small_stepper_back(STEPS, 11, 9, 10, 8);  // Sens anti-horaire en inversant 8 et 11 (si on préfère)
  int  Steps2Take = 0;  //Nombre de pas de rotation demandé au moteur
  long temps =0;          //Durée de rotation pour un tour
  //************************************************************
  // 64 pas par tour, 4 phases, angle de 5.625° selon les spécifications du moteur
  // Démultiplication 1:64 pour ce moteur réducté mécaniquement
  //   360° / 5.625° * 64 = 4096 angles avec la démultiplication
  //   360° / 5.625° * 64  * 4 bobines / 2 bipolaire = 2048 step / tour
 

void setup()
 {
                 
  Serial.begin(9600);     // 9600 bps
  pinMode(Fin_C_Bas, INPUT_PULLUP); // Capt est une broche d'entree
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  Serial.begin(9600);

  }

long mesure(){

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long lecture_echo = pulseIn(echo,HIGH);
  long cm = lecture_echo /58;
  Serial.print("Distance en cm :");
  Serial.println(cm);
  delay(1500);
  return cm;
}
void loop()
  {
    
    if(state==1){
     if (CapteurBasOn == HIGH)
      {
        small_stepper_back.setSpeed(300);
        Steps2Take  = 1;
        small_stepper_back.step(Steps2Take);
      }
     else {
        state=2;
      }
    }
    
    else {
        //Serial.println(Fin_C_Bas);
        //Faire tourner le moteur
        small_stepper.setSpeed(300); //Vitesse de 300 (max) réduire ce chiffre pour un mouvement plus lent
        //100 permet d'éavoir un couple élevé >300 le moteur vibre sans tourner
       
        Steps2Take  = 1;  // Une rotation complète avec 2048 pas (1 tour environ 4.5sec)
        small_stepper.step(Steps2Take);  //Ca tourne
        cpt++;
    }
    if(cpt==4000) {
      dist=mesure();
      if (dist >=9 && dist<=11){
        Serial.println("At 10cm : past");
        Serial.println(dist);
      }
        else{
          Serial.println("At 10cm : false");
          Serial.println(dist);
        }
      }

       if(cpt==12000) {
      dist=mesure();
      if (dist >=29 && dist<=31){
        Serial.println("At 30cm : past");
        Serial.println(dist);
      }
        else{
          Serial.println("At 30cm : false");
          Serial.println(dist);
        }
      }
    
       if(cpt==8000) {
      dist=mesure();
      if (dist>=19 && dist<=21){
        Serial.println("At 20cm : past");
        Serial.println(dist);
      }
        else{
          Serial.println("At 20cm : false");
          Serial.println(dist);
        }
      }
    
    if (cpt==12000){
      
    }

    delay(2);
  }