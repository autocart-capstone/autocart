#include <SPI.h>
#include <SPISlave.h>

// Requires installation of Arduino Pico board library, add the JSON release link below to preferences and then install board in board manager
// https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json

// Wiring:
// Master RX  <->  Slave TX
// Master CS  <->  Slave CS
// Master CK  <->  Slave CK
// Master TX  <->  Slave RX

#define MOSI_PIN (4)
#define MISO_PIN (3)
#define SCK_PIN (2)
#define CSn_PIN (5)

#define REQUEST_OBJECT_DETECTION (0)
#define REQUEST_ANGLE            (1)

#define REQUEST_TYPE(c) ((c) ? REQUEST_OBJECT_DETECTION : REQUEST_ANGLE)

SPISettings spisettings(1000000, MSBFIRST, SPI_MODE0);

/*
- Ideal scenario is to setup pico as a slave, but until Earle fixes his slave library, workaround would be a Req and Response master->SPI and slave->RPI architecture.

volatile bool recvBuffReady = false;
char recvBuff[2] = "";
int recvIdx = 0;

void recvCallback(uint8_t *data, size_t len) {
  memcpy(recvBuff + recvIdx, data, len);
  recvIdx += len;
  if (recvIdx == sizeof(recvBuff)) {
    recvBuffReady = true;
    recvIdx = 0;
  }
}

bool getRecvBuffReady()
{
  return recvBuffReady;
}

void clearRecvBuffReady()
{
  recvBuffRead = false;
}

char * getRecvBuffer()
{
  char *r = (char *)malloc(strlen(recvBuff) * sizeof(char));
  strcpy(r, recvBuff);
  //Remember to free after done on recv. 
  return recvBuffer;
}

void spi_slave_setup()
{
  SPISlave.setRX(MOSI_PIN);
  SPISlave.setCS(CSn_PIN);
  SPISlave.setSCK(SCK_PIN);
  SPISlave.setTX(MISO_PIN);

  sentCallback();
  
  SPISlave.onDataRecv(recvCallback);
  SPISlave.onDataSent(sentCallback);
  SPISlave.begin(spisettings);

  Serial.begin(9600);

  Serial.println("S-INFO: SPISlave started"); 
}

SLAVE WOULD LOOK SOMETHING LIKE THIS IN MAIN:

  if (getRecvBuffReady) {
    char * recv = getRecvBuffer();
    //Handle recv (i.e stop cart, chagne direction, etc)
    free(recv);
    clearRecvBuffReady = false;
  }
   delay(1000);
*/

/*Temporary workaround for slave not working + earle which might not work with TimerInterrupt since other board is now required..
void spi_master_setup()
{
  SPI.setRX(MOSI_PIN);
  SPI.setCS(CSn_PIN);
  SPI.setSCK(SCK_PIN);
  SPI.setTX(MISO_PIN);  

  SPI.begin(true);
}

uint8_t send_data_request(bool objectDetection)
{
  uint8_t response = 0;

  SPI.beginTransaction(spisettings);
  response = SPI.transfer(REQUEST_TYPE(objectDetection), 1);
  Serial.println("Requesting %c", REQUEST_TYPE(objectDetection));
  SPI.endTransaction();

  return response;
}
*/

arduino::MbedSPI masterSPI(MOSI_PIN, MISO_PIN, SCK_PIN);

void spi_master_setup()
{
  masterSPI.begin();
}

uint8_t send_data_request(bool objectDetection)
{
  uint8_t response = 0;

  masterSPI.beginTransaction(spisettings);
  /*response = masterSPI.transfer(REQUEST_TYPE(objectDetection));*/
  /*SCAFFOLDING*/ response = 20; /*SCAFFOLDING*/
  Serial.print(response);
  masterSPI.endTransaction();

  return response;
}
