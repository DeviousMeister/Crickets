/* cricket
 *  
 *  CSE 132 - Assignment 3
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name: Moises
 *  WUSTL Key: 473091
 *  
 *  and if two are partnered together
 *  
 *  Name:
 *  WUSTL Key:
 */
const int light = 5;
const int tempPin = A1;
const int FILTER_COUNTS = 7;
float temperatures[FILTER_COUNTS];
unsigned long count = 0;
 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(light, OUTPUT);
  pinMode(tempPin, INPUT);
  analogReference(INTERNAL);
  
}
unsigned long blinkDuration = 200;
unsigned long next = 0;
boolean isOn = false;

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long time = millis();
  float actualTemp = readTemp();
  float chirpsPerSec = (((actualTemp-10)*7)+40)/60;
  float period = (1/chirpsPerSec)*1000;
     if(time > next){
       if(!isOn){
        next += (period - blinkDuration);
        digitalWrite(light, HIGH);
        isOn = true;     
      } 
      else{
        next += blinkDuration;
        digitalWrite(light, LOW);
        isOn = false;
     }
  }
  
  
}

float readTemp(){
  float val = analogRead(tempPin);
  float input = (1.1/1023.0) * val;
  float temp = 25 + ((input -.75)*100);
  temperatures[count % FILTER_COUNTS] = temp;
  float sum = 0;
  for(int i = 0; i<FILTER_COUNTS; ++i){
    sum = temperatures[i] + sum;
  }
  float avg = sum/FILTER_COUNTS;
  
  if(count >= 7){
     Serial.print(temp);
     Serial.print(", ");
     Serial.print(avg);
     Serial.println();
    }
  count += 1;
  return avg;
}
