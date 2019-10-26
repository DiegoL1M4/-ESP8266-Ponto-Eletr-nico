// ############### LOOP ############### // ResInfo
#include <SPI.h>
#include <MFRC522.h>           // RFID
#include <Wire.h>              // I2C
#include <LiquidCrystal_I2C.h> // LCD
#include <virtuabotixRTC.h>    // RTC

#include <ArduinoJson.h>       // JSON

#include <ESP8266WiFi.h>       // WiFi
#include <ESP8266HTTPClient.h>  // Client

// Configurações de Rede
const char* ssid = "Pinheiro";       // Rede WiFi
const char* password = "P32983013";  // Senha

// Objetos
MFRC522 mfrc522(D3, A0);                                       // Instância RFID.
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Instância LCD
virtuabotixRTC myRTC(D4, D8, D9);                              // Instância RTC

// Variáveis
int cont = 0;
int found = 0;
int flagChoice = 0;

String nome;
String data =  "";
String tag_RFID;

// ############### SETUP ############### //
void setup() {

  // Conexão Serial
  Serial.begin(115200);
  delay(20);

  // Conexão do Wifi
  Serial.print("\n\nConnecting to "); // Mensagem apresentada no monitor série
  Serial.println(ssid); // Apresenta o nome da rede no monitor série

  WiFi.begin(ssid, password); // Inicia a ligação a rede

  int cont = 0;
  while (WiFi.status() != WL_CONNECTED) {
      cont += 1;
      delay(500);
      Serial.print("."); // Enquanto a ligação não for efectuada com sucesso é apresentado no monitor série uma sucessão de “.”

      if(cont == 50)
        break;
  }
  if(WiFi.status() == WL_CONNECTED)
      Serial.println("\nWiFi connected\n");
  else
      Serial.println("\nWiFi not connected\n");
  
  // Outras Configurações
  SPI.begin();          // Inicializa  SPI bus
  mfrc522.PCD_Init();   // Inicializa o MFRC522
  lcd.begin (16, 2);    // Inicializa o Display (16 colunas x 2 linhas)

  // Botão de ação
  pinMode(D0, INPUT);

  // Nome da empresa
  nome = getHTTP("general/nome");
  
}



// ############### LOOP ############### //
void loop() {
  switch (flagChoice) {
    case 0: // Tela 1
        if (cont == 10) {
          Serial.println(nome);
          cont = 0;
          rtc();
        }
        cont += 1;
        delay(100);
        lcd.setBacklight(LOW);
        break;
    case 1: // Tela 2
        Serial.println("Aproxime o cartão!");
        for (int k = 0; k < 20; k++) {
          rfid(0);
          delay(100);
          if(tag_RFID != ""){
            String json = "{\"tagRFID\": \"" + tag_RFID + "\", \"data\": \"" + data + "\"}";
            int code = postHTTP("registro", json);
            if(code == 700)
              Serial.println("Todos os registros já realizados!");
            break;
          }
        }
        Serial.println("Finalizando");
        delay(1000);
        break;
    case 2: // Tela 3
        Serial.println("Aproxime o cartão!");
        for (int k = 0; k < 20; k++) {
          rfid(1);
          delay(100);
          if(tag_RFID != ""){
            String json = "{\"nome\": \"Novo Usuario\", \"tagRFID\": \"" + tag_RFID + "\"}";
            int code = postHTTP("usuario", json);
            if(code == 700)
              Serial.println("Cartão já cadastrado!");
            else
              Serial.println("Registro efetuado com sucesso!");
            break;
          }
        }
        Serial.println("Finalizando");
        delay(1000);
        break;
    case 3: // Tela 4
        String json = getHTTP("general/data");
        
        if(json == "bad") {
          Serial.println("Deu ruim");
          break;
        }
        StaticJsonDocument<200> doc;
        deserializeJson(doc, json);
        
        int h = doc["h"];
        int m = doc["m"];
        int s = doc["s"];
        int wk = doc["wk"];
        int d = doc["d"];
        int mth = doc["mth"];
        int a = doc["a"];
        
        myRTC.setDS1302Time(s, m, h, wk, d, mth, a); // Inicializa o RTC
        break;
  }

  // Reset de Variáveis
  flagChoice = 0;
  tag_RFID = "";

  // ### Tela 2: Menu 1 -
  if (digitalRead(D0) == 1) {
    lcd.setBacklight(HIGH);
    Serial.println("1 - Registrar Horário");
    lcdPrint("1: Registro", 1, 1, 0);
    flagChoice = 1;
    delay(300);
    for (int k = 0; k < 10; k++) {
      delay(100);

      // ### Tela 3: Menu 2 -
      if (digitalRead(D0) == 1) {
        Serial.println("2 - Cadastrar Usuário");
        lcdPrint("2: Cadastrar", 1, 1, 0);
        flagChoice = 2;
        delay(300);
        for (int k = 0; k < 10; k++) {
          delay(100);

          // ### Tela 4: Menu 3 -
          if (digitalRead(D0) == 1) {
            Serial.println("3 - Atualiza Hora");
            lcdPrint("3: Atualiza Hora", 1, 1, 0);
            flagChoice = 3;
            delay(300);
            for (int k = 0; k < 10; k++) {
              delay(100);

              // ### Tela 5: Menu 4 -
              if (digitalRead(D0) == 1) {
                Serial.println("4 - Voltar");
                lcdPrint("4: Voltar", 1, 0, 0);
                flagChoice = 4;
                delay(300);
                for (int k = 0; k < 1; k++) {
                  delay(100);
                  break;
                }
              } // ### END: Tela 5
            }
          } // ### END: Tela 4
        }
      }// ### END: Tela 3
    }
  } // ### END: Tela 2

}

// ############### Funções RFID
void rfid(int operation) {

    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) return;
  
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) return;
  
    leitura_tag_RFID();

}

void leitura_tag_RFID() {
  tag_RFID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    tag_RFID.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
    tag_RFID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  tag_RFID.toUpperCase();
  tag_RFID = tag_RFID.substring(1);
}


// ############### Funções HTTP
int postHTTP(String path, String json) {
    HTTPClient http;    //Declare object of class HTTPClient
    
    http.begin("http://192.168.25.18:8080/" + path);      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
    
    int httpCode = http.POST(json);   //Send the request
    String payload = http.getString();                  //Get the response payload
    
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
    
    http.end();  //Close connection

    return httpCode;
}

String getHTTP(String path) {
  
    HTTPClient http;
    String payload;
    
    http.begin("http://192.168.25.18:8080/" + path); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
    
    if (httpCode > 0) { //Check for the returning code
        payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
    } else {
        Serial.println("Error on HTTP request");
        http.end();
        return "bad";
    }
    
    http.end(); //Free the resources

    return payload;

}


// ############### Funções LCD
void lcdPrint(String texto, int pos, int fixo, int tempo) {
    int total = texto.length() - 16;
    if(total < 0) total = 0;
    
    for(int i = 0; i <= total; i++){
      
        lcd.setCursor(0,pos);
        lcd.print("                ");
        lcd.setCursor(0,pos);
        lcd.print(texto);
    
        delay(tempo);
    
        texto.remove(0,1);
    }

    if(!fixo) {
        delay(1000);
        lcd.setCursor(0,1);
        lcd.print("                ");
    }
    
}

// ############### Funções RTC
void rtc() {
  // Le as informacoes do CI
  myRTC.updateTime();

  String fullData = "Data : ";
  data = "";

  data.concat(myRTC.year);
  data.concat(myRTC.month < 10 ? "-0" : "-");
  data.concat(myRTC.month);
  data.concat(myRTC.dayofmonth < 10 ? "-0" : "-");
  data.concat(myRTC.dayofmonth);
  data.concat(myRTC.hours < 10 ? "T0" : "T");
  data.concat(myRTC.hours);
  data.concat(myRTC.minutes < 10 ? ":0" : ":");
  data.concat(myRTC.minutes);
  data.concat(myRTC.seconds < 10 ? ":0" : ":");
  data.concat(myRTC.seconds);
  data.concat(".000");
  
  fullData.concat(imprime_dia_da_semana(myRTC.dayofweek));
  fullData.concat(", ");
  fullData.concat(myRTC.dayofmonth);
  fullData.concat("/");
  fullData.concat(myRTC.month);
  fullData.concat("/");
  fullData.concat(myRTC.year);
  fullData.concat(myRTC.hours < 10 ? ", Hora : 0" : ", Hora : ");
  fullData.concat(myRTC.hours);
  fullData.concat(myRTC.minutes < 10 ? ":0" : ":");
  fullData.concat(myRTC.minutes);
  fullData.concat(myRTC.seconds < 10 ? ":0" : ":");
  fullData.concat(myRTC.seconds);

  Serial.println(fullData + "\n");
}

String imprime_dia_da_semana(int dia) {
  switch(dia) {
    case 1: return "Domingo";
    case 2: return "Segunda";
    case 3: return "Terca";
    case 4: return "Quarta";
    case 5: return "Quinta";
    case 6: return "Sexta";
    case 7: return "Sabado";
  }
}
