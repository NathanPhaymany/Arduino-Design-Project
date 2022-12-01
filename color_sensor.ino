#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

#define BT 10
#define buzzerPin 7

// Stores frequency read by the photodiodes
int red = 0;
int green = 0;
int blue = 0;
int RGB[3];
boolean buttonOn = false;

int getColor(int num[]) {
  int red = num[0];
  if (400 < red && 450 > red)
  {
    return 1;
  }
  else if (450 < red)
  {
    return 0;
  }
  else {
    return 2;
  }
}

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(BT, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
   // Begins serial communication 
  Serial.begin(9600);
}
void loop() {

  buttonOn = digitalRead(BT);

  if (buttonOn == LOW)
  {
    Serial.println("Button pressed");
    // Count red
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);
    red = pulseIn(sensorOut, LOW);
    //delay(100);
  
    // count green
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
    green = pulseIn(sensorOut, LOW);
  
    // count blue 
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    blue = pulseIn(sensorOut, LOW);

    RGB[0] = map(red, 70, 120, 255,0);
    RGB[1] = map(green, 100, 199, 255, 0);;
    RGB[2] = map(blue, 38, 84, 255, 0);
    
    Serial.println(RGB[0]);
    switch (getColor(RGB))
    {
      case 0:
        Serial.println("RED");
        tone(7, 200, 100);
        break;
      case 1:
        Serial.println("YELLOW");
        tone(7, 500, 100);
        break;
      case 2:
        Serial.println("BLUE");
        tone(7, 800, 100);
        break;
    }
  }
}
