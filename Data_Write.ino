/*
 * This code will be uploaded to arduino on the payload. It will convert an ASCII message into binary, then write a 9 bit key, 
 * followed by a 7 bit character in the message. If the message is more than one character, the 9 bit key will be repeated 
 * inbetween each 7 bit character until the message is finished. Once the message is sent, the program loops back to the first
 * character in the message. 
 */
int outPin = 7;   //sets the output pin to 7 (this pin should be connected to a copper pad)
int delayTime = 125;     //send each bit 1/8 of a second after the last message
char message[] = "LTF>UTF"; //Enter the message here to send to the copper pads

void setup() {
  pinMode(outPin, OUTPUT);    // sets the output pin
}

/*
 * This function writes the message to the copper pads. Inbetween each character in the message is the 9 bit key (000000001).
 * The message is converted to binary using the bitRead function and then written to the copper pads using digitalWrite.
 */
void loop() {
  //Loop through all the characters in the message
  for(int j=0;j<sizeof(message)-1;j++){
    writeKey();   //Inbetween each character in the message, write the 9 bit key
    //Loop through the 7 bits in the binary representation of the message character
    for(int i=6;i>=0;i--){
      byte a = bitRead(message[j],i);  //Convert the ASCII character into binary and store the binary bit in variable a
      if(a==1){
        digitalWrite(outPin, HIGH);    //Send a ONE
        delay(delayTime);
      }
      else{
        digitalWrite(outPin, LOW);    //Send a ZERO
        delay(delayTime);
      }
    }
  }
}

/*
 * This function writes the key that indicates a new character from the message is coming. The key is 8 zeros followed by a 1 (000000001).
 */
void writeKey(){
  //Send 8 ZEROS
  for(int i=0;i<8;i++){
    digitalWrite(outPin,LOW);      //Send a ZERO
    delay(delayTime);
  }
  digitalWrite(outPin,HIGH);       //Send a ONE
  delay(delayTime);
}


