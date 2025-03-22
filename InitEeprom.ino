//-----------------------------------------//
//                                         //
//             InitEeprom V0.13             //  
//                                         //
//-----------------------------------------//
#include <stdio.h>
#include <string.h>
#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define PINALIMLCD A2                     // Patte de commande de l'alimentation du LCD



#define EEPROMLONGDEGRE            0x00
#define EEPROMLONGMINUTE           0x02
#define EEPROMLONGSECONDE          0x04
#define EEPROMLATDEGRE             0x06
#define EEPROMLATMINUTE            0x08
#define EEPROMLATSECONDE           0x0A
#define EEPROMDELAISOUVERTURE      0x0C
#define EEPROMDELAISFERMETURE      0x0E
#define EEPROMHAUTEUROUVERTURE     0X10
#define EEPROMPASMOTEUR            0x12
#define EEPROMRTIMEOUTTRAPPE       0x14
#define EEPROMDELAISALLUMAGE       0x16
#define EEPROMTEMPSALLUMAGE        0x18
#define EEPROMDUREEALLUMAGE        0x1A
#define EEPROMHEUREOUVERTURE       0x1C
#define EEPROMMINUTEOUVERTURE      0x1E
#define EEPROMHEUREFERMETURE       0x20
#define EEPROMMINUTEFERMETURE      0x22
#define EEPROMLUMINOSITEBASSE      0x24
#define EEPROMLUMINOSITEHAUTE      0x26
#define EEPROMDELAISLUX            40
#define EEPROMVMINMOTEUR           42
#define EEPROMVMAXMOTEUR           44
#define EEPROMDUREEMINUTERIE       46
#define EEPROMPRESENCEFDC          48
#define EEPROMBoutonMenu           100
#define EEPROMBoutonVide           106
#define EEPROMBoutonMode           112
#define EEPROMBoutonPrecedent      118
#define EEPROMBoutonSuivant        124
#define EEPROMBoutonModifier       130
#define EEPROMBoutonQuitter        136
#define EEPROMBoutonAnnuler        142
#define EEPROMBoutonMoins          148
#define EEPROMBoutonPlus           154
#define EEPROMBoutonValider        160
#define EEPROMBoutonTrappe         166
#define EEPROMBoutonLumiere        172
#define EEPROMBoutonInfo           178
#define EEPROMBoutonFdc            184
#define EEPROMMenu9_L1             200
#define EEPROMMenu9_L2             222
#define EEPROMMenu10_L1            244
#define EEPROMMenu10_L2            266
#define EEPROMMenu11_L1            288
#define EEPROMMenu11_L2            310
#define EEPROMMenu12_L1            332
#define EEPROMMenu12_L2            354
#define EEPROMMenu13_L1            376
#define EEPROMMenu13_L2            398
#define EEPROMMenu14_L1            420
#define EEPROMMenu14_L2            442
#define EEPROMMenu15_L1            464
#define EEPROMMenu15_L2            486
#define EEPROMMenu16_L1            508
#define EEPROMMenu16_L2            530
#define EEPROMMenu17_L1            552
#define EEPROMMenu17_L2            574
#define EEPROMMenu18_L1            596
#define EEPROMMenu18_L2            618
#define EEPROMMenu19_L1            640
#define EEPROMMenu19_L2            662
#define EEPROMMenu20_L1            684
#define EEPROMMenu20_L2            706
#define EEPROMMenu21_L1            728
#define EEPROMMenu21_L2            750
#define EEPROMMenu22_L1            772
#define EEPROMMenu22_L2            794
#define EEPROMMenu23_L1            816
#define EEPROMMenu23_L2            838


char Initialisation[]       = "Initialisation";
char Version[]              = "memoire V2.00";
char MessageCoordonnees[]   = "Coordonnee Reims";
char ValeurCoordonnees[]    = "49 15 00 N 4 01 59 E";
int  LongitudeDegre         = 4;
int  LongitudeMinute        = 1;
int  LongitudeSeconde       = 59;
int  LatitudeDegre          = 49;
int  LatitudeMinute         = 15;
int  LatitudeSeconde        = 59;
int  DelaisOuverture        = 20;
int  DelaisFermeture        = 15;
int  HauteurOuverture       = 25;
int  PasMoteur              = 167;
int  TimeoutTrappe          = 15;
int  DelaisAllumage         = -5;
int  TempsAllumage          = 5;
int  DureeAllumage          = 10;
int  HeureOuverture         = 8;
int  MinuteOuverture        = 0;
int  HeureFermeture         = 20;
int  MinuteFermeture        = 0;
int  LuminositeBasse        = 50;
int  LiminositeHautte       = 150;
int  DelaisLux              = 60;
int  VMinMoteur             = 50;
int  VMaxMoteur             = 150;
int  DureeMinuterie         = 15;
int  PresenceFdc            = 0;
 
char Bouton[]               = "Bouton";
char BoutonMenu[]           = "Menu";
char BoutonVide[]           = "    ";
char BoutonMode[]           = "Mode ";
char BoutonPrecedent[]      = "Prec";
char BoutonSuivant[]        = "Suiv ";
char BoutonModifier[]       = "Modif";
char BoutonQuitter[]        = "Quit";
char BoutonAnnuler[]        = "Annu";
char BoutonMoins[]          = "Moin";
char BoutonPlus[]           = "Plus";
char BoutonValider[]        = "Valid";
char BoutonTrappe[]         = "Trap";
char BoutonLumiere[]        = "Lumi";
char BoutonInfo[]           = "Info";
char BoutonFdc[]            = "Fdc ";

char Menu9_L1[]             = "   Date  et  Heure  ";
char Menu9_L2[]             = "   /  /        :    ";
char Menu10_L1[]            = " Longitude Latitude ";
char Menu10_L2[]            = "   \1  '  \"   \1  '  \"";
char Menu11_L1[]            = "  Delais ouverture  ";
char Menu11_L2[]            = "         minutes    ";
char Menu12_L1[]            = "  Delais fermeture  ";
char Menu12_L2[]            = "         minutes    ";
char Menu13_L1[]            = "Course de la trappe ";
char Menu13_L2[]            = "           cm       ";
char Menu14_L1[]            = "  Pas moteur trappe ";
char Menu14_L2[]            = "     par centimetre ";
char Menu15_L1[]            = "   Timeout trappe   ";
char Menu15_L2[]            = "       secondes     ";
char Menu16_L1[]            = "  Delais allumage   ";
char Menu16_L2[]            = "        minutes     ";
char Menu17_L1[]            = "   Temps allumage   "; 
char Menu17_L2[]            = "        minutes     ";
char Menu18_L1[]            = "   Duree allumage   ";
char Menu18_L2[]            = "        minutes     ";
char Menu19_L1[]            = "    Mode horaire    ";
char Menu19_L2[]            = "Ouv:  :   Ferm:  :  ";
char Menu20_L1[]            = "    Mode Nature     ";
char Menu20_L2[]            = "Ouv:    L Ferm:    L";
char Menu21_L1[]            = " Delais mode Nature ";
char Menu21_L2[]            = "      0 secondes    ";
char Menu22_L1[]            = "   Vitesse moteur   ";
char Menu22_L2[]            = "  Max:     Min:     ";
char Menu23_L1[]            = "   Duree minuterie  ";
char Menu23_L2[]            = "        minutes     ";

LiquidCrystal_I2C lcd(0x27,20,4);; 

int LireEepromInt(int adresse)
  {
  unsigned int retour = 0;
  char i;

  for (i=0; i<2; i++)
    {
    retour <<=8;
    retour +=eeprom_read_byte((unsigned char *)adresse+i);
    }
  return retour;
  }

void EcrireEepromInt(int adresse, unsigned int valeur)
    {
    char c;
    char i;
    for (i=0; i<2;i++)
      {
      c=valeur & 0xFF;
      eeprom_write_byte((unsigned char *)adresse + 1 - i,c);
      valeur >>=8;
      }
    }

void EffaceLigne(int8_t ligne)
  {
   uint8_t Colonne;
   for (Colonne = 0; Colonne<20; Colonne++)
     {
      lcd.setCursor(Colonne, ligne);
      lcd.print(" "); 
     }
  }

void Message(int8_t Colonne, int8_t Ligne,  char *Mes)
   {
   lcd.setCursor(Colonne, Ligne);
   lcd.print(Mes);
   }

void Message(int8_t Colonne, int8_t Ligne,  int Mes)
   {
   lcd.setCursor(Colonne, Ligne);
   lcd.print(Mes);
   }

void Ok ()
   {
    delay(300);
   lcd.setCursor(9, 3);
   lcd.print("OK");
   }
void Tempo()
  {
    delay(1000);
  }

/*****
 * EcrireEepromString : permet d'écriree une chaine de caractères en Eeprom.
 *     adresse : adresse du début de la chaine en Eeprom
 *     valeur  : contenu de la chaine de caractère
 *     la longueur de la chaine est limitée à 20 caractères
 */
void EcrireEepromString(int adresse, char *valeur)
    {
  int i=adresse;
  
    while ( (*valeur != 0) && ( (adresse-i) < 20) )
      {
      EEPROM.write(adresse,*valeur);
      adresse+=1;
      valeur++;
      }
    //adresse++;
//    eeprom_write_byte(adresse,0);
    EEPROM.write(adresse,0);
    }

    
void setup() {
int i;
int Val;


  pinMode(PINALIMLCD, OUTPUT);            // Gestion de la sortie alimentation du LCD
   digitalWrite(PINALIMLCD, LOW);
//Serial.begin(115200);
lcd.init();                      // initialize the lcd 
lcd.clear();
lcd.backlight();
 
Message(3,1, Initialisation);
Message(4,2, Version);
delay(2000);
lcd.clear();


//
// initialisation des paramètres
//
Message(2,0,MessageCoordonnees);

Message(0,1,ValeurCoordonnees);
EcrireEepromInt(EEPROMLONGDEGRE,LongitudeDegre);
EcrireEepromInt(EEPROMLONGMINUTE,LongitudeMinute);
EcrireEepromInt(EEPROMLONGSECONDE,LongitudeSeconde);
EcrireEepromInt(EEPROMLATDEGRE,LatitudeDegre);
EcrireEepromInt(EEPROMLATMINUTE,LatitudeMinute);
EcrireEepromInt(EEPROMLATSECONDE,LatitudeSeconde);
Ok();
Tempo();
lcd.clear();

Message(2,0,"Delais ouverture");
Message(9,1,DelaisOuverture);
EcrireEepromInt(EEPROMDELAISOUVERTURE,DelaisOuverture);
Ok();
Tempo();
lcd.clear();

Message(2,0,"Delais fermeture");
Message(9,1,DelaisFermeture);
EcrireEepromInt(EEPROMDELAISFERMETURE,DelaisFermeture);
Ok();
Tempo();
lcd.clear();

Message(0,0,"Hauteur d'ouverture");
Message(9,1,HauteurOuverture);
EcrireEepromInt(EEPROMHAUTEUROUVERTURE, HauteurOuverture);
Ok();
Tempo();
lcd.clear();

Message(0,0,"Pas du moteur");
Message(9,1,PasMoteur);
EcrireEepromInt(EEPROMPASMOTEUR, PasMoteur);
Ok();
Tempo();
lcd.clear();

Message(0,0,"Timeout trappe");
Message(9,1,TimeoutTrappe);
EcrireEepromInt(EEPROMRTIMEOUTTRAPPE, TimeoutTrappe);
Ok();
Tempo();
lcd.clear();

Message(2,0,"Delais allumage");
Message(9,1,DelaisAllumage);
EcrireEepromInt(EEPROMDELAISALLUMAGE, DelaisAllumage);
Ok();
Tempo();
lcd.clear();

Message(3,0,"Temps allumage");
Message(9,1,TempsAllumage);
EcrireEepromInt(EEPROMTEMPSALLUMAGE, TempsAllumage);
Ok();
Tempo();
lcd.clear();

Message(3,0,"Duree allumagee");
Message(9,1,DureeAllumage);
EcrireEepromInt(EEPROMDUREEALLUMAGE, DureeAllumage);
Ok();
Tempo();
lcd.clear();

Message(2,0,"Heure ouverture");
Message(9,1,HeureOuverture);
EcrireEepromInt(EEPROMHEUREOUVERTURE, HeureOuverture);
Ok();
Tempo();
lcd.clear();

Message(2,0,"Minute ouverture");
Message(9,1,MinuteOuverture);
EcrireEepromInt(EEPROMMINUTEOUVERTURE, MinuteOuverture);
Ok();
Tempo();
lcd.clear();

Message(2,0,"Heure fermeture");
Message(9,1,HeureFermeture);
EcrireEepromInt(EEPROMHEUREFERMETURE, HeureFermeture);
Ok();
Tempo();
lcd.clear();

Message(2,0,"Minute fermeture");
Message(9,1,MinuteFermeture);
EcrireEepromInt(EEPROMMINUTEFERMETURE, MinuteFermeture);
Ok();
Tempo();
lcd.clear();

Message(2,0,"Luminosite basse");
Message(9,1,LuminositeBasse);
EcrireEepromInt(EEPROMLUMINOSITEBASSE, LuminositeBasse);
Ok();
Tempo();
lcd.clear();

Message(2,0,"Luminosite haute");
Message(9,1,LiminositeHautte);
EcrireEepromInt(EEPROMLUMINOSITEHAUTE, LiminositeHautte);
Ok();
Tempo();
lcd.clear();

Message(2,0,"Delais mode nature");
Message(9,1, DelaisLux);
EcrireEepromInt(EEPROMDELAISLUX, DelaisLux);
Ok();
Tempo();
lcd.clear();

Message(2,0,"Vitesse Min moteur");
Message(9,1, VMinMoteur);
EcrireEepromInt(EEPROMVMINMOTEUR, VMinMoteur);
Ok();
Tempo();
lcd.clear();

Message(2,0,"Vitesse Max moteur");
Message(9,1, VMaxMoteur);
EcrireEepromInt(EEPROMVMAXMOTEUR, VMaxMoteur);
Ok();
Tempo();
lcd.clear();

Message(2,0,"Duree minuterie");
Message(9,1, DureeMinuterie);
EcrireEepromInt(EEPROMDUREEMINUTERIE, DureeMinuterie);
Ok();
Tempo();
lcd.clear();

Message(2,0,"Presence Fdc");
Message(9,1, PresenceFdc);
EcrireEepromInt(EEPROMPRESENCEFDC, PresenceFdc);
Ok();
Tempo();
lcd.clear();

//
// Initialisation des boutons
//
Message(7,0,Bouton);
Message(7,1,BoutonMenu);
EcrireEepromString(EEPROMBoutonMenu, BoutonMenu);
Ok();
Tempo();
lcd.clear();

//Message(7,0,Bouton);
//Message(7,1,BoutonVide);
//Message(7,1,BoutonVide);
EcrireEepromString(EEPROMBoutonVide, BoutonVide);
//Ok();
//Tempo();
//lcd.clear();

Message(7,0,Bouton);
Message(7,1,BoutonVide);
Message(7,1,BoutonMode);
EcrireEepromString(EEPROMBoutonMode, BoutonMode);
Ok();
Tempo();
lcd.clear();

Message(7,0,Bouton);
Message(7,1,BoutonVide);
Message(7,1,BoutonPrecedent);
EcrireEepromString(EEPROMBoutonPrecedent, BoutonPrecedent);
Ok();
Tempo();
lcd.clear();

Message(7,0,Bouton);
Message(7,1,BoutonVide);
Message(7,1,BoutonSuivant);
EcrireEepromString(EEPROMBoutonSuivant, BoutonSuivant);
Ok();
Tempo();
lcd.clear();

Message(7,0,Bouton);
Message(7,1,BoutonVide);
Message(7,1,BoutonModifier);
EcrireEepromString(EEPROMBoutonModifier, BoutonModifier);
Ok();
Tempo();
lcd.clear();

Message(7,0,Bouton);
Message(7,1,BoutonVide);
Message(7,1,BoutonQuitter);
EcrireEepromString(EEPROMBoutonQuitter, BoutonQuitter);
Ok();
Tempo();
lcd.clear();

Message(7,0,Bouton);
Message(7,1,BoutonVide);
Message(7,1,BoutonAnnuler);
EcrireEepromString(EEPROMBoutonAnnuler, BoutonAnnuler);
Ok();
Tempo();
lcd.clear();

Message(7,0,Bouton);
Message(7,1,BoutonVide);
Message(7,1,BoutonMoins);
EcrireEepromString(EEPROMBoutonMoins, BoutonMoins);
Ok();
Tempo();
lcd.clear();

Message(7,0,Bouton);
Message(7,1,BoutonVide);
Message(7,1,BoutonPlus);
EcrireEepromString(EEPROMBoutonPlus, BoutonPlus);
Ok();
Tempo();
lcd.clear();

Message(7,0,Bouton);
Message(7,1,BoutonVide);
Message(7,1,BoutonValider);
EcrireEepromString(EEPROMBoutonValider, BoutonValider);
Ok();
Tempo();
lcd.clear();

Message(7,0,Bouton);
Message(7,1,BoutonVide);
Message(7,1,BoutonTrappe);
EcrireEepromString(EEPROMBoutonTrappe, BoutonTrappe);
Ok();
Tempo();
lcd.clear();

Message(7,0,Bouton);
Message(7,1,BoutonVide);
Message(7,1,BoutonLumiere);
EcrireEepromString(EEPROMBoutonLumiere, BoutonLumiere);
Ok();
Tempo();
lcd.clear();

Message(7,0,Bouton);
Message(7,1,BoutonVide);
Message(7,1,BoutonInfo);
EcrireEepromString(EEPROMBoutonInfo, BoutonInfo);
Ok();
Tempo();
lcd.clear();

Message(7,0,Bouton);
Message(7,1,BoutonVide);
Message(7,1,BoutonFdc);
EcrireEepromString(EEPROMBoutonFdc, BoutonFdc);
Ok();
Tempo();
lcd.clear();

//
// Initialisation des fonds de menu
//

i=9;

Message(7,0,BoutonMenu);
Message(12,0,i++);
Message(0,1,Menu9_L1);
EcrireEepromString(EEPROMMenu9_L1, Menu9_L1);
delay(50);
EcrireEepromString(EEPROMMenu9_L2, Menu9_L2);
Ok();
Tempo();
lcd.clear();

Message(7,0,BoutonMenu);
Message(12,0,i++);
Message(0,1,Menu10_L1);
EcrireEepromString(EEPROMMenu10_L1, Menu10_L1);
delay(50);
EcrireEepromString(EEPROMMenu10_L2, Menu10_L2);
Ok();
Tempo();
lcd.clear();

Message(7,0,BoutonMenu);
Message(12,0,i++);
Message(0,1,Menu11_L1);
EcrireEepromString(EEPROMMenu11_L1, Menu11_L1);
delay(50);
EcrireEepromString(EEPROMMenu11_L2, Menu11_L2);
Ok();
Tempo();
lcd.clear();

Message(7,0,BoutonMenu);
Message(12,0,i++);
Message(0,1,Menu12_L1);
EcrireEepromString(EEPROMMenu12_L1, Menu12_L1);
delay(50);
EcrireEepromString(EEPROMMenu12_L2, Menu12_L2);
Ok();
Tempo();
lcd.clear();

Message(7,0,BoutonMenu);
Message(12,0,i++);
Message(0,1,Menu13_L1);
EcrireEepromString(EEPROMMenu13_L1, Menu13_L1);
delay(50);
EcrireEepromString(EEPROMMenu13_L2, Menu13_L2);
Ok();
Tempo();
lcd.clear();

Message(7,0,BoutonMenu);
Message(12,0,i++);
Message(0,1,Menu14_L1);
EcrireEepromString(EEPROMMenu14_L1, Menu14_L1);
delay(50);
EcrireEepromString(EEPROMMenu14_L2, Menu14_L2);
Ok();
Tempo();
lcd.clear();

Message(7,0,BoutonMenu);
Message(12,0,i++);
Message(0,1,Menu15_L1);
EcrireEepromString(EEPROMMenu15_L1, Menu15_L1);
delay(50);
EcrireEepromString(EEPROMMenu15_L2, Menu15_L2);
Ok();
Tempo();
lcd.clear();

Message(7,0,BoutonMenu);
Message(12,0,i++);
Message(0,1,Menu16_L1);
EcrireEepromString(EEPROMMenu16_L1, Menu16_L1);
delay(50);
EcrireEepromString(EEPROMMenu16_L2, Menu16_L2);
Ok();
Tempo();
lcd.clear();

Message(7,0,BoutonMenu);
Message(12,0,i++);
Message(0,1,Menu17_L1);
EcrireEepromString(EEPROMMenu17_L1, Menu17_L1);
delay(50);
EcrireEepromString(EEPROMMenu17_L2, Menu17_L2);
Ok();
Tempo();
lcd.clear();

Message(7,0,BoutonMenu);
Message(12,0,i++);
Message(0,1,Menu18_L1);
EcrireEepromString(EEPROMMenu18_L1, Menu18_L1);
delay(50);
EcrireEepromString(EEPROMMenu18_L2, Menu18_L2);
Ok();
Tempo();
lcd.clear();

Message(7,0,BoutonMenu);
Message(12,0,i++);
Message(0,1,Menu19_L1);
EcrireEepromString(EEPROMMenu19_L1, Menu19_L1);
delay(50);
EcrireEepromString(EEPROMMenu19_L2, Menu19_L2);
Ok();
Tempo();
lcd.clear();

Message(7,0,BoutonMenu);
Message(12,0,i++);
Message(0,1,Menu20_L1);
EcrireEepromString(EEPROMMenu20_L1, Menu20_L1);
delay(50);
EcrireEepromString(EEPROMMenu20_L2, Menu20_L2);
Ok();
Tempo();
lcd.clear();

Message(7,0,BoutonMenu);
Message(12,0,i++);
Message(0,1,Menu21_L1);
EcrireEepromString(EEPROMMenu21_L1, Menu21_L1);
delay(50);
EcrireEepromString(EEPROMMenu21_L2, Menu21_L2);
Ok();
Tempo();
lcd.clear();

Message(7,0,BoutonMenu);
Message(12,0,i++);
Message(0,1,Menu22_L1);
EcrireEepromString(EEPROMMenu22_L1, Menu22_L1);
delay(50);
EcrireEepromString(EEPROMMenu22_L2, Menu22_L2);
Ok();
Tempo();
lcd.clear();

Message(7,0,BoutonMenu);
Message(12,0,i++);
Message(0,1,Menu23_L1);
EcrireEepromString(EEPROMMenu23_L1, Menu23_L1);
delay(50);
EcrireEepromString(EEPROMMenu23_L2, Menu23_L2);
Ok();
Tempo();
lcd.clear();


 
Message(1,1,"Memoire initialisee");

}

void loop() {
  // put your main code here, to run repeatedly:
}
