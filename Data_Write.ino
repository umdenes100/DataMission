/*
 * This code will be uploaded to arduino on the payload. It will convert an ASCII message into binary, then write a 9 bit key, 
 * followed by a 7 bit character in the message. If the message is more than one character, the 9 bit key will be repeated 
 * inbetween each 7 bit character until the message is finished. Once the message is sent, the program loops back to the first
 * character in the message. 
 */
int outPin = 7;   //sets the output pin to 7 (this pin should be connected to a copper pad)
int pushButton = 13;    //sets the pin of the pushButton
int delayTime = 125;     //send each bit 1/8 of a second after the last message
int tens,ones;
char message = NULL;

void setup() {
  pinMode(outPin, OUTPUT);    // sets the output pin
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(pushButton, INPUT_PULLUP);  //sets the pushbutton pin
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  message = random(65,90); //Enter the message here to send to the copper pads
}

/*
 * This function writes the message to the copper pads. Inbetween each character in the message is the 9 bit key (000000001).
 * The message is converted to binary using the bitRead function and then written to the copper pads using digitalWrite.
 */
void loop() {
   tens = (int)((message/10));
   ones = (int)message%10;
   do{
    displayNumber(0,0,1,1);
    writeKey();   //Inbetween each character in the message, write the 9 bit key
    displayNumber(bitRead(ones,0),bitRead(ones,1),bitRead(ones,2),bitRead(ones,3));
    //Loop through the 7 bits in the binary representation of the message character
    for(int i=6;i>=0;i--){
      byte a = bitRead(message,i);  //Convert the ASCII character into binary and store the binary bit in variable a
      if(a==1){
        digitalWrite(outPin, HIGH);    //Send a ONE
      }
      else{
        digitalWrite(outPin, LOW);    //Send a ZERO
      }
      delay(delayTime);
      if(i==2){
        displayNumber(0,0,1,1);
      }
    }
   } while(digitalRead(pushButton)); //If the pushbutton is pressed, randomize the message
   randomSeed(analogRead(A0));
   message = random(65,90); //reset the message that is being sent
}

/*
 * This function writes the key that indicates a new character from the message is coming. The key is 8 zeros followed by a 1 (000000001).
 */
void writeKey(){
  //Send 8 ZEROS
  for(int i=0;i<8;i++){
    digitalWrite(outPin,LOW);      //Send a ZERO
    delay(delayTime);
    if(i==2){
      displayNumber(bitRead(tens,0),bitRead(tens,1),bitRead(tens,2),bitRead(tens,3));
    }
  }
  displayNumber(1,1,1,1);
  digitalWrite(outPin,HIGH);       //Send a ONE
  delay(delayTime);
}
void displayNumber(byte num1,byte num2,byte num3,byte num4){
    digitalWrite(2,num1);
    digitalWrite(3,num2);
    digitalWrite(4,num3);
    digitalWrite(5,num4);
}
