/*
 * Playstation Joystick Meet Arduino UNO
 * Created by Catur Pebriandani
 * 06-01-2019
 * Please visit My Blog caturcreativeproject.com
 * My Youtube Channel Catur Pebriandani
 * My IG catur_pebriandani
 * Thanks a Lot
 */
 
#include <SPI.h>

// Global Variable 
uint8_t stick_ready, stick_type, byte4, byte5, byte6, byte7, byte8, byte9;


void setup() {
    // put your setup code here, to run once:
    
    // Port B initialization 
    DDRB=(0<<DDB7) | (0<<DDB6) | (1<<DDB5) | (0<<DDB4) | (1<<DDB3) | (1<<DDB2) | (0<<DDB1) | (0<<DDB0);
    PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (1<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);
  
    // SPI initialization = SPI Type: Master, SPI Clock Rate: 125.000 kHz, SPI Clock Phase: Cycle Half, SPI Clock Polarity: High, SPI Data Order: LSB First
    SPCR=(0<<SPIE) | (1<<SPE) | (1<<DORD) | (1<<MSTR) | (1<<CPOL) | (1<<CPHA) | (1<<SPR1) | (1<<SPR0);
    SPSR=(0<<SPI2X);  

    // Open Serial Communication to PC
    Serial.begin(9600);
    while(!Serial);
    
    pinMode(10, OUTPUT);                  //Set pin 10 Arduino UNO as OUTPUT
    digitalWrite(10, HIGH); delay(200);   //Set pin 10 HIGH 
    
}

void loop() {
  // put your main code here, to run repeatedly:

  //*GET THE DATA
  digitalWrite(10, LOW);                    // Activate the Slave 
      SPI.transfer(0x01);                   // Start Communication
      stick_type=SPI.transfer(0x42);        // Get Data (Stick Type one of 65 for "Digital" or 115 for "Analog" or 255 if no Joystick Plugged)
      stick_ready=SPI.transfer(0);          // Get Data (Stick Status either 90 for "Ready" or 255 for "Not Ready"
      byte4=SPI.transfer(0);                // Get Joystick Data (up, down, left, right, start, select, joy-L/L3, joy-R/R3)
      byte5=SPI.transfer(0);                // Get Joystick Data (triangle, square, circle, x, R1, R2, L1, L2)
      byte6=SPI.transfer(0);                // Get Joystick Data (Analog Right Side x Axis - Analog Move Right or Left)
      byte7=SPI.transfer(0);                // Get Joystick Data (Analog Right Side y Axis - Analog Move Up or Down)
      byte8=SPI.transfer(0);                // Get Joystick Data (Analog Left Side x Axis - Analog Move Right or Left)
      byte9=SPI.transfer(0);                // Get Joystick Data (Analog Left Side y Axis - Analog Move Up or Down)
  digitalWrite(10, HIGH);                   // Disconnect the slave

  //*SHOW THE DATA
  Serial.print("byte4=" + (String)byte4);   Serial.print("\t");   //Show Byte 4 Data
  Serial.print("byte5=" + (String)byte5);   Serial.print("\t");   //Show Byte 5 Data
  Serial.print("byte6=" + (String)byte6);   Serial.print("\t");   //Show Byte 6 Data
  Serial.print("byte7=" + (String)byte7);   Serial.print("\t");   //Show Byte 7 Data
  Serial.print("byte8=" + (String)byte8);   Serial.print("\t");   //Show Byte 8 Data
  Serial.print("byte9=" + (String)byte9);   Serial.print("\t");   //Show Byte 9 Data
  
  Serial.print("Stick Type= " + (String)stick_type);              //Show Stick Type Data either 65 or 115
  Serial.print("\t");                                             //Give one Tab   
    if(stick_type==65)        { Serial.println("(Digital)"); }    //Show "Digital" if Data equal 65
    else if(stick_type==115)  { Serial.println("(Analog)");  }    //Show "Analog" if Data equal 115
  
  Serial.println("\n\n"); //Give Two enter 

  
  delay(1000); // Relative Value, this show the data 1 time for a second 

}
