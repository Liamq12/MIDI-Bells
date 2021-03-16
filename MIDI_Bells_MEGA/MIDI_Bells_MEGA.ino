#define startNote 48
#define numberSolenoids 32
#define startPin 22
#define extendTime 50

unsigned long noteStatus[numberSolenoids];

void setup() {
  Serial.begin(115200);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(52, OUTPUT);
  pinMode(53, OUTPUT);

// Did not work, for whatever reason
//  for(int i = startPin; i < numberSolenoids; i++){
//    pinMode(i, OUTPUT);
//  }
}

void loop() {
  if(Serial.available() >= 3){
    uint16_t note = Serial.read();
    uint16_t period = Serial.read() << 8 | Serial.read();
    
    Serial.print("Time: ");
    Serial.print(note);
    Serial.println();
    Serial.print(" Period: ");
    Serial.print(period);
    Serial.println();
    if(note == 0 && period > 255){ 
      note = period/256;
    }else if(note == 0){
      note = period;
    }

for(int i = startNote; i < numberSolenoids + startNote; i++){
  if(note == i){
    noteStatus[i-startNote] = millis();
    digitalWrite((i-startNote)+startPin, LOW);
    Serial.print("Going LOW Pin: ");
    Serial.println((i-startNote)+startPin);
  }
}
  }
  unsigned long mils = millis();

  for(int i = startNote; i < numberSolenoids + startNote; i++){
    if(noteStatus[i-startNote] < mils-extendTime){
      digitalWrite((i-startNote)+startPin, HIGH);
      Serial.print("Going HIGH ");
      Serial.println((i-startNote)+startPin);
      noteStatus[i-startNote] = -1;
    }
  }
}
