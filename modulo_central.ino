#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial SIM800L(10, 11);
String Comando;
String textSms, numberSms;
bool error;
String _buffer;

void setup(){
  Serial.begin(9600);
  SIM800L.begin(9600);
  SIM800L.println("AT+CMGF=1");
  delay(1000); //Pausa de 1 segundo
  SIM800L.println("AT+CNMI=1,2,0,0,0");
  delay(1000);
  SIM800L.println("ATX4");
  delay(1000);
  SIM800L.println("AT+COLP=1");
  Serial.println("AGUARDANDO SMS...");
}

void loop(){
  
  if (SIM800L.available()){
    Comando = SIM800L.readString();
    if (Comando.length() > 10) //avoid empty sms
    {
       //Serial.println(Comando.indexOf("lat"));
      
        //forca 1
        uint8_t _idx1_4=Comando.indexOf("forca");
        _idx1_4=Comando.indexOf(":",_idx1_4);
        String forcaString = Comando.substring(_idx1_4+1,Comando.indexOf(".",_idx1_4));
        //Serial.print("forca 1: ");
        //Serial.println(forcaString);
        
      if(Comando.indexOf("lat") != -1 && forcaString.toInt() < 170){
        Serial.println("HOUVE UM ACIDENTE: " + Comando);
        Serial.println(":::::INFORMACOES DO IMPACTO::::: ");
        //numero
        uint8_t _idx1=Comando.indexOf(":");
        _idx1=Comando.indexOf("+",_idx1+1);
        String numeroString = Comando.substring(_idx1,Comando.indexOf("\",\""));
        //Serial.print("numero que enviou: ");
        //Serial.println(numeroString);
  
        //latitude
        uint8_t _idx1_2=Comando.indexOf("lat");
        _idx1_2=Comando.indexOf(":",_idx1_2);
        String latitudeString = Comando.substring(_idx1_2+1,Comando.indexOf(",",_idx1_2));
        Serial.print("latitude: ");
        Serial.println(latitudeString);
  
        //longitude
        uint8_t _idx1_3=Comando.indexOf("lon");
        _idx1_3=Comando.indexOf(":",_idx1_3);
        String longitudeString = Comando.substring(_idx1_3+1,Comando.indexOf(",",_idx1_3));
        Serial.print("longitude: ");
        Serial.println(longitudeString);

        //forca 2
        Serial.print("forca ( G ): ");
        Serial.println(forcaString);
        
      }else{
        Serial.println("SMS NAO FORMATADO: " + Comando);
      }
    }
  }
}
