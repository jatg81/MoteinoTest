#include <EmonLib.h>


#define FILTERSETTLETIME 5000                                           //  Time (ms) to allow the filters to settle before sending data
#define RF_freq RF12_433MHZ                                                // Frequency of RF12B module can be RF12_433MHZ, RF12_868MHZ or RF12_915MHZ. You should use the one matching the module you have.
const int nodeID = 13;                                                  // emonTx RFM12B node ID
const int networkGroup = 210;                                           // emonTx RFM12B wireless network group - needs to be same as emonBase and emonGLCD                                                 
#define RF69_COMPAT 1 // set to 1 to use RFM69CW 
#include <JeeLib.h>   // make sure V12 (latest) is used if using RFM69CW


typedef struct { int dat0, dat1,dat2;} PayloadTX;      // create structure - a neat way of packaging data for RF comms 
PayloadTX emontx;                                                        

boolean settled = false;

void setup() 
{
  rf12_initialize(nodeID, RF_freq, networkGroup);                          // initialize RFM12B
  rf12_sleep(RF12_SLEEP);                                             
}

void loop() 
{ 
 
   
  // because millis() returns to zero after 50 days ! 
  if (!settled && millis() > FILTERSETTLETIME) settled = true;

  if (settled)                                                            // send data only after filters have settled
  { 
    emontx.dat0=123;
    emontx.dat1=456;
    emontx.dat2=789;
    digitalWrite(7,HIGH);
    send_rf_data();                                                     // *SEND RF DATA* - see emontx_lib
    delay (300);
    digitalWrite(7,LOW);
    delay(1000);    
}
}
