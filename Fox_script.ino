String alphabet1 = "A.-B-...C-.-.D-..E.F..-.G--.H....I..J.---K-.-L.-..M--N-.O---P.--.Q--.-R.-.S...T-U..-V...-W.--X-..-Y-.--Z--..";
String alphabet2 = "1.----2..---3...--4....-5.....6-....7--...8---..9----.0-----";
String alphabet = alphabet1+alphabet2;

//Parameter which indirectly sets morsing speed. Higher = slower. Defined in milliseconds.
//Rule of thumb I derived: 1250 / this number = WPM.
int dotDuration = 75;
//This message is what will be transmitted in Morse.
String programMessage = "W1XM FOX HUNT AT MIT";
//Amount of time to wait between transmissions. In seconds.
unsigned long transmitDelay = 150;

//Pull low when you want to send a message. Equivalent to PTT button on a radio.
int TXSelectPin = 7;
//Carries our CW message
int TXSignalPin = 3;

int LEDPin = 13;

//Tracks the last time we transmitted, so we can do that automatically.
unsigned long lastTransmissionTime = 0;
//Takes a character and will return symbols. Example: getMorse("A") returns ".-"
String getMorse(char letter)
{
  int letterLocation = alphabet.indexOf(letter);
  String symbols = "";
  bool loadSymbols = true;
  int count = 1;
  while(loadSymbols)
  {
    char charIn = alphabet[letterLocation+count];
    if (charIn == '.' or charIn == '-')
    {
      symbols += charIn;
    }
    else
    {
      return symbols;
    }
    count++;
  } 
}

void transmit(String message)
{
  digitalWrite(TXSelectPin,HIGH);
  //Give a moment for the radio board to turn on
  delay(200);
  message.toUpperCase
  ();
  //Transmit each letter of the message
  for(int i=0; i<message.length(); i++)
  {
    char letter = message[i];
    String morse = "";
    if(letter == ' ')
      //Specified delay between words is 7. Down below we pause for 3 so this is the other 4.
      delay(dotDuration*4);
    morse = getMorse(letter);
    //Transmit each symbol of the current letter
    for(int j=0; j<morse.length();j++)
    {
      if (morse[j] == '.')
        buzz(1);
      if (morse[j] == '-')
        buzz(3);
      delay(dotDuration);
    }
   delay(dotDuration*3);
  }
  digitalWrite(TXSelectPin,LOW);
  //Safety element to make sure everything can shut down after transmitting. Don't want to receive ourselves or anything like that.
  delay(1000);
  lastTransmissionTime = millis();
}
void buzz(int duration)
{
  digitalWrite(LEDPin,HIGH);
  tone(TXSignalPin, 700, duration * dotDuration);
  delay(duration*dotDuration);
  digitalWrite(LEDPin,LOW);
}

void setup() {
  pinMode(TXSelectPin,OUTPUT);
  digitalWrite(TXSelectPin,HIGH);
  pinMode(TXSignalPin,OUTPUT);
  digitalWrite(TXSignalPin,LOW);
  //Want standard state to be receiving.
  pinMode(LEDPin,OUTPUT);
  digitalWrite(LEDPin,LOW);
  //Once we're up and running, first order of business is to do a transmission.
  transmit(programMessage);
}

void loop() {    
    if (millis() > (lastTransmissionTime + 1000*transmitDelay))
    {
      transmit(programMessage);
    }
}
