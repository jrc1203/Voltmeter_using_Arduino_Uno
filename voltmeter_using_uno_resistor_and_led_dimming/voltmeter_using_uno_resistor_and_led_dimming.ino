int led=3;
// Total number of readings to take for voltage measure
const int numReadings = 10;

// Function to get stable voltage reading
float getSmoothedVoltage() 
  {
    float sum = 0;
    for(int i = 0; i < numReadings; i++) {
      int sensorValue = analogRead(A0);
      float voltage = sensorValue * (5.0 / 1023.0);
      sum += voltage;
      delay(1);  // Small delay between the readings
    }
    return sum / numReadings;
  }

void setup() 
  {
    Serial.begin(9600);
    pinMode(led, OUTPUT);
  }

void loop() 
  {
    // store the voltage values in a variable
    float voltage = getSmoothedVoltage();
    
    // Calculate input voltage using the formula [ Vin  = Vout * ( (R1 + R2) / R2 )]
    // Here R1 = 10kΩ, R2 = 2.2kΩ
    float Vin = voltage * 12.2 / 2.2;
    Vin = 1.25 * Vin;// here the 1.25 is the scaling factor set by testing with multimeter
    
    // Print voltage readings to serial monitor
    Serial.print("Voltage: ");
    Serial.print(Vin);
    Serial.println("V");
    
    // Calculate and constrain the PWM value (0-255) so that it does not damage the led by going above 255
    int pwmValue = constrain((int)(Vin * 10), 0, 255); //here scaling factor 10 is given according to the required brightness of led
    analogWrite(led, pwmValue);
    
    delay(500);
  }









/*
More simplar code easy to understand but the above one is taking average of 10 values and giving the output so stable output coming 

int led=3;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.println("Voltage : ");
  float Vin = voltage * 12.2 / 2.2;
  Vin = 1.25 * Vin;
  Serial.println(Vin);
  
 // analogWrite(3,Vin*7);
  // Constrain PWM value between 0 and 255
  int pwmValue = constrain((int)(Vin*10), 0, 255);
  analogWrite(led, pwmValue);

  delay(500);
}
*/