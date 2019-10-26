#include <ESP8266WiFi.h>
#include <Wire.h> // responsável pela comunicação com a interface i2c
#include <LiquidCrystal_I2C.h> // responsável pela comunicação com o display LCD
#include <ESP8266HTTPClient.h>  // Client

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

// Nome do seu wifi
const char* ssid = "Pinheiro"; 
// Senha do seu wifi
const char* password = "P32983013";

String request;
 
WiFiServer server(80); // Porto 80
WiFiServer sv(555);//Cria o objeto servidor na porta 555
WiFiClient cl;//Cria o objeto cliente.

void setup() {

    WiFi.mode(WIFI_AP);//Define o WiFi como Acess_Point.
    WiFi.softAP("NodeMCU", "");//Cria a rede de Acess_Point.

    sv.begin();//Inicia o servidor TCP na porta declarada no começo.

    //inicializa o display (16 colunas x 2 linhas)
    lcd.begin (16,2); // ou 20,4 se for o display 20x4
 
    Serial.begin(115200);
    delay(10);



    // Comunicação com a rede WiFi
    Serial.print("\n\nConnecting to "); // Mensagem apresentada no monitor série
    Serial.println(ssid); // Apresenta o nome da rede no monitor série

    WiFi.begin(ssid, password); // Inicia a ligação a rede

    int cont = 0;
    while (WiFi.status() != WL_CONNECTED) {
        cont += 1;
        delay(500);
        Serial.print("."); // Enquanto a ligação não for efectuada com sucesso é apresentado no monitor série uma sucessão de “.”

        if(cont == 20)
          break;
    }
    Serial.println("\nWiFi connected"); // Se a ligação é efectuada com sucesso apresenta esta mensagem no monitor série

    // Servidor
    server.begin(); // Comunicação com o servidor
    Serial.println("Servidor iniciado"); //é apresentado no monitor série que o  servidor foi iniciado

    // Impressão do endereço IP
    Serial.print("Use o seguinte URL para a comunicação: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP()); //Abrindo o Brower com este IP acedemos á pagina HTML de controlo dos LED´s, sendo que este IP só está disponível na rede à qual o ESP8266 se encontra ligado
    Serial.println("/");

    if(cont == 20)
        WiFi.mode(WIFI_AP);//Define o WiFi como Acess_Point.
        WiFi.softAP("NodeMCU", "");//Cria a rede de Acess_Point.
    
        sv.begin();//Inicia o servidor TCP na porta declarada no começo.
}

 
void loop() {
 
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://192.168.25.18:8080/usuario");      //Specify request destination
   http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
   int httpCode = http.POST("{\"nome\": \"Teste\", \"tagRFID\": \"12345678\"}");   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(30000);  //Send a request every 30 seconds
 
}
