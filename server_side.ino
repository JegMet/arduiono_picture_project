// nrf24_server

#include <SPI.h>
#include <RH_NRF24.h>

// Singleton instance of the radio driver
RH_NRF24 nrf24;
// RH_NRF24 nrf24(8, 7); // use this to be electrically compatible with Mirf
// RH_NRF24 nrf24(8, 10);// For Leonardo, need explicit SS pin
// RH_NRF24 nrf24(8, 7); // For RFM73 on Anarduino Mini

void setup() 
{

  Serial.begin(9600);
  while (!Serial) 
    ; // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");
}

    int count = 0;

void loop()
{

  if (nrf24.available())
  {

    // Should be a message for us now
    int length = 32;
    uint8_t buf[length];
    uint8_t len = sizeof(buf);
    if (nrf24.recv(buf, &len))
    {
      count++;
      // RH_NRF24::printBuffer("request: ", buf, len);
      // Serial.print("got request: ");

      for(int i = 0; i < len; i++) {
        Serial.print(buf[i], HEX); 
        // Serial.print(" "); 
        if ((buf[i] == 0xD9) && (buf[i - 1] == 0xFF)) {

          Serial.println("count is ");
          Serial.println(count);
          count = 0;
        }
      }
    
    }
    else
    {
      Serial.println("recv failed");
    }
  }
}