/*Sketch de prueba de envio de datos desde NodeRed hacia arduino Moteino a traves del Emonhub
 * 
 * Importar a node red:
 * [{"id":"1f59d6eb.2e0c29","type":"inject","z":"5bd3a543.84eedc","name":"Actualizar Hora","topic":"setUnixTime","payload":"","payloadType":"date","repeat":"","crontab":"00 00 * * *","once":false,"x":180,"y":60,"wires":[["a91bb2cc.db737"]]},{"id":"a396a6ed.491d48","type":"mqtt out","z":"5bd3a543.84eedc","name":"","topic":"emonhub/tx/13/values","qos":"","retain":"","broker":"1de9005b.9113a","x":940,"y":100,"wires":[]},{"id":"a91bb2cc.db737","type":"function","z":"5bd3a543.84eedc","name":"Tx a EmonTx02","func":"var dataPos=0,setTempMax=0,setVolumenAgua=0,setUnixTime=0;\n\nif(msg.topic=='setTempMax'){\n    setTempMax=msg.payload;\n    dataPos=1;\n}\n\nif(msg.topic=='setVolumenAgua'){\n    setVolumenAgua=msg.payload;\n    dataPos=2;\n}\n\nif(msg.topic=='setUnixTime'){\n    setUnixTime=parseInt((msg.payload/1000)-18000);\n    dataPos=3;\n}\nmsg.payload =dataPos+\",\"+setTempMax+\",\"+setVolumenAgua+\",\"+setUnixTime;\nreturn msg;","outputs":1,"noerr":0,"x":660,"y":100,"wires":[["a396a6ed.491d48"]]},{"id":"6ca98868.f62cb8","type":"inject","z":"5bd3a543.84eedc","name":"Actualizar Totalizador Agua","topic":"setVolumenAgua","payload":"","payloadType":"date","repeat":"","crontab":"","once":false,"x":210,"y":180,"wires":[["7ec16818.b96c68"]]},{"id":"7ec16818.b96c68","type":"emoncms in","z":"5bd3a543.84eedc","name":"Emoncms","emonServer":"756bc1b7.a75fb","feedid":"226","x":420,"y":180,"wires":[["a91bb2cc.db737"]]},{"id":"1b04cf49.fd34c1","type":"inject","z":"5bd3a543.84eedc","name":"Actualizar Maxima Temp","topic":"setTempMax","payload":"56","payloadType":"num","repeat":"","crontab":"","once":false,"x":210,"y":120,"wires":[["a91bb2cc.db737"]]},{"id":"1de9005b.9113a","type":"mqtt-broker","z":"5bd3a543.84eedc","broker":"localhost","port":"1883","clientid":"","usetls":false,"verifyservercert":true,"compatmode":true,"keepalive":"60","cleansession":true,"willTopic":"","willQos":"0","willRetain":null,"willPayload":"","birthTopic":"","birthQos":"0","birthRetain":null,"birthPayload":""},{"id":"756bc1b7.a75fb","type":"emoncms-server","z":"5bd3a543.84eedc","server":"http://localhost/emoncms","name":""}]
 * 
 * Adicionar al archivo de configuracion de EmonHub
 *  [[13]]
 *   nodename = EmonTx03
 *   [[[tx]]]
 *      datacodes = b,b,L,L
*/



#include <RF69Mod.h>
#define RF_freq           RF69_433MHZ           //Frecuencia de transmision 433Mhz

const int nodeId = 16;
const int netGroup = 210;
const int nodeIdEmonPi=15;  
typedef struct {byte dataMod,setTempMax;unsigned long setVolumenAgua,setUnixTime;} PayloadRX;       
PayloadRX emonrx; 

void setup() {
Serial.begin(9600);
rf69_initialize(nodeId, RF_freq, netGroup);
}

void loop() {
  if (rf69_recvDone()){
    Serial.print(rf69_hdr&31);
    Serial.print(" - ");
    Serial.println(rf69_hdr);
    /*
    if(rf69_receiveStart(nodeIdEmonPi,&emonrx,sizeof(emonrx))){
      Serial.println("Recibi algo!!");
      switch(emonrx.dataMod){
      case 1:
        Serial.println(emonrx.setTempMax);
        break;
      case 2:    
        Serial.println(emonrx.setVolumenAgua);
        break;
      case 3:
        Serial.println(emonrx.setUnixTime);
        break;
      }
    }*/
  }
}
