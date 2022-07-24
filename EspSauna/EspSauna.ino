/* Projeto Curto Circuito – ESP32: NTP e ULP */

/* -------- Bibliotecas----------- */
#include <NTPClient.h> /* https://github.com/arduino-libraries/NTPClient */
#include <WiFi.h> /* Biblioteca Wi-Fi. */
#include <DallasTemperature.h>
#include <SevSeg.h>
#include <OneWire.h>
#include <TM1637Display.h>
//#include <BluetoothA2DPSink.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 4
 
// The amount of time (in milliseconds) between tests
#define TEST_DELAY   2000
 
const uint8_t SEG_DONE[] = {
    SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
    SEG_C | SEG_E | SEG_G,                           // n
    SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
    };
 
TM1637Display display(CLK, DIO);

//bluethooth
//BluetoothA2DPSink a2dp_sink;
//bck_io_num = 26
//ws_io_num = 25
//data_out_num = 22

// Pinos de acesso ao Esp32 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Sensor de Temperatura DS18B20

#define DS18B20      14 // OK 

//Instacia o Objeto oneWire e Seta o pino do Sensor para iniciar as leituras
OneWire oneWire(DS18B20);

//Repassa as referencias do oneWire para o Sensor Dallas (DS18B20)
DallasTemperature Sensor(&oneWire);


/* -------- Wi-Fi ----------- */
const char* ssid = "********";
const char* password = "****************";

// Configurações do Servidor NTP
const char* servidorNTP = "a.st1.ntp.br"; // Servidor NTP para pesquisar a hora
const int fusoHorario = -10800; // Fuso horário em segundos (-03h = -10800 seg)

/* -------- Protocolo NTP ----------- */
WiFiUDP ntpUDP; // Declaração do Protocolo UDP
NTPClient timeClient(ntpUDP, servidorNTP, fusoHorario, 60000);

String hora;/*Armazenara o horário na memória RTC. */
float leitura;
String leitura_text;

bool pontim = true;

void setup()
{
  Serial.begin(115200);     /* Inicia a comunicação serial. */
  WiFi.begin(ssid, password);
  // Inicia o Sensor
  Sensor.begin();
  delay(2000);/* Espera a conexão. */
  timeClient.begin();
  //a2dp_sink.start("SteamMusic");//nome bluetooth sauna
}

void loop() {

  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  display.setBrightness(0x0f);

    // Leitura do Hora  Wifi  //////////////
  timeClient.update();
  hora = timeClient.getFormattedTime();

    // Leitura do Sensor  DS18B20  //////////////
  Sensor.requestTemperatures();
  leitura = Sensor.getTempCByIndex(0);
  leitura_text = String(leitura);
  
  for (int temp = 1; temp <= 10; temp++){
  Serial.print(leitura);
  Serial.println("ºC"); 
  Serial.println("--------------------------------------"); 
  
  // Selectively set different digits  
  data[0] = display.encodeDigit(String(leitura_text[0]).toInt()); //digito 1
  data[1] = display.encodeDigit(String(leitura_text[1]).toInt()); //digito 2
  data[2] = B01100011; // "º"; digito 3
  data[3] = B10111001; // "C"; digito 4
  display.setSegments(data);
  
  delay(1000);  /* Mantem o processador 1 em estado ocioso por 1seg */
  }
  
  for (int hr = 1; hr <= 10; hr++){

  if (pontim){
    // mostrar hora
    data[0] = display.encodeDigit(String(hora[0]).toInt()); //digito 1
    data[1] = display.encodeDigit(String(hora[1]).toInt()); //digito 2
    data[2] = display.encodeDigit(String(hora[3]).toInt()); //digito 3
    data[3] = display.encodeDigit(String(hora[4]).toInt()); //digito 4
    display.setSegments(data);
    pontim = false;
    Serial.printf("\n Tempo corrido: ");
    Serial.println(hora);
    }
  else {
    // mostrar hora
//    data[0] = display.encodeDigit(String(hora[0]).toInt()); //digito 1
//    data[1] = display.encodeDigit(String(hora[1]).toInt()); //digito 2
//    data[2] = display.encodeDigit(String(hora[3]).toInt()); //digito 3
//    data[3] = display.encodeDigit(String(hora[4]).toInt()); //digito 4
    data[1] = data[1] + 128; // coloca o ":" no display
    display.setSegments(data);
    pontim = true;
    Serial.printf("\n Tempo corrido: ");
    Serial.println(hora);
    }
  
  delay(1000);  /* Mantem o processador 1 em estado ocioso por 1seg */
  }
}
