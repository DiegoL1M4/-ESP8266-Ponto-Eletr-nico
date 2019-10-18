// ############### LOOP ############### // ResInfo
#include <SPI.h>
#include <MFRC522.h>           // RFID
#include <Wire.h>              // I2C
#include <LiquidCrystal_I2C.h> // LCD
#include <virtuabotixRTC.h>    // RTC

// Pinos
#define SS_PIN  D3 // RFID
#define RST_PIN A0 // RFID
#define BNT_1   D  // Botão de ação 1

// Objetos
MFRC522 mfrc522(SS_PIN, RST_PIN);                      // Instância RFID.
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); // Instância LCD
virtuabotixRTC myRTC(D4, D8, D9);                      // Instância RTC

// h
int statuss = 0;
int out = 0;

// ############### SETUP ############### //
void setup() 
{
  Serial.begin(115200); // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  
  mfrc522.PCD_Init();   // Inicializa o MFRC522
  lcd.begin (16,2);     // Inicializa o Display (16 colunas x 2 linhas)
  myRTC.setDS1302Time(21, 55, 23, 5, 21, 06, 2018); // Inicializa o RTC

  pinMode(D0, INPUT);
}

// ############### LOOP ############### //
void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  if(digitalRead(D0)==0)
  {
     Serial.println("Botão não pressionado");
  }
  else
  {
     Serial.println("Botão pressionado");
  }
  
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  
  String content= "";
  byte letter;
  
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  content.toUpperCase();
  Serial.println();
  
  if (content.substring(1) == "2C 8F AA 59") {
    lcd.setBacklight(HIGH);

    lcd.setCursor(0,0);
    lcd.print("Parabéns");
    lcd.setCursor(0,1);
    lcd.print("VALEU!!!");

    Serial.print("Correto");
    delay(3000); //intervalo de 1s
    lcd.setBacklight(LOW);
  } else {
    lcd.setBacklight(HIGH);

    lcd.setCursor(0,0);
    lcd.print("Itaa Mah");
    lcd.setCursor(0,1);
    lcd.print("Nao deu!!!");
    
    delay(3000); //intervalo de 1s
    lcd.setBacklight(LOW);

    Serial.print("Erro");
    rtc();
  }
}




void rtc()  
{
  // Le as informacoes do CI
  myRTC.updateTime(); 

  // Imprime as informacoes no serial monitor
  Serial.print("Data : ");
  // Chama a rotina que imprime o dia da semana
  imprime_dia_da_semana(myRTC.dayofweek);
  Serial.print(", ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print("  ");
  Serial.print("Hora : ");
  // Adiciona um 0 caso o valor da hora seja <10
  if (myRTC.hours < 10)
  {
    Serial.print("0");
  }
  Serial.print(myRTC.hours);
  Serial.print(":");
  // Adiciona um 0 caso o valor dos minutos seja <10
  if (myRTC.minutes < 10)
  {
    Serial.print("0");
  }
  Serial.print(myRTC.minutes);
  Serial.print(":");
  // Adiciona um 0 caso o valor dos segundos seja <10
  if (myRTC.seconds < 10)
  {
    Serial.print("0");
  }
  Serial.println(myRTC.seconds);

  delay( 1000);
}

void imprime_dia_da_semana(int dia)
{
  switch (dia)
  {
    case 1:
    Serial.print("Domingo");
    break;
    case 2:
    Serial.print("Segunda");
    break;
    case 3:
    Serial.print("Terca");
    break;
    case 4:
    Serial.print("Quarta");
    break;
    case 5:
    Serial.print("Quinta");
    break;
    case 6:
    Serial.print("Sexta");
    break;
    case 7:
    Serial.print("Sabado");
    break;
  }
}
