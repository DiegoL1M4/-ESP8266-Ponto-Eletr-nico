# [ESP8266] Ponto Eletrônico
Sistema embarcado para gestão de pessoas em ambientes em que se torna necessário o uso de controle tempo de permanência no local.

## Módulos do Projeto
Existem três módulos distintos que se comunicam e compartilham informações.
* **Sistema Embarcado:** ESP8266
* **Back-End:** API Rest
* **Front-End:** SPA Angular
* **Banco de Dados:** Postgres

## Módulos e Bibliotecas do ESP8266
* Display LCD
* Módulo RTC
* WiFI ESP
* Leitor RFID
* HTTP
* JSON

## Funcionalidades
* Registro de cartões RFID no sistema;
* Registro de quatro tipos de entradas no dia, representando hora de chegada e partida ao trabalho e hora do almoço;
* Registro do nome da empresa;
* Registro de hora local (ESP).
