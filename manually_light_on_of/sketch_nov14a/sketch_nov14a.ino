void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
//  while(!Serial);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    int output = Serial.read();
    Serial.write(output);
    if(output == '0'){
      digitalWrite(LED_BUILTIN, LOW);
      Serial.write("\nLED OFF!\n");
    }else if(output == '1'){
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.write("\nLED ON!\n");
    }
  }
}
