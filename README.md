# ESP_Sauna


esp32; DS 18b20; NTP server; CNMCU1334; TM1637

Projeto de um medidor de temperatura para sauna.
O ESP32 sera usado para medir as condições da sauna usando um sensor de DS 18b20 e mostrar no display TM1637 a temperatura e a hora. Por Wifi é possivel coletar a hora com  um servidor NTP. Tambem usaremos o sinal do Bleutooth do ESP32 para receber audio e envia-lo para a placa de circuito CNMCU1334 que converte o protocolo I2S do ESP32 para sinal analogico atravez de um DAC.

Design of a temperature gauge for a steam room.
ESP32 will be used to measure the steam room conditions using a DS 18b20 sensor and show the temperature and time on the TM1637 display. By Wifi it is possible to collect the time with NTP server. We will also use the ESP32's Bleutooth signal to receive audio and send it to the CNMCU1334 circuit board which converts the ESP32's I2S protocol to an analog signal through a DAC.
