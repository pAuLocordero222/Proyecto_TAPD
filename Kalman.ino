const int trigPin = 13;
const int echoPin = 12;

float duration, distance;
float kal_data;

double kalman(double U){
  static const double R = 40;
  static const double H = 1.00;
  static double Q = 10;
  static double P = 0;
  static double U_hat = 0;
  static double K = 0;
  K = P*H/(H*P*H+R);
  U_hat += + K*(U-H*U_hat);
  P = (1-K*H)*P+Q;
  return U_hat;
}


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

}

void loop() {
  //Pulso de disparo
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); //Lectura del pin echo
  distance = (duration*0.034)/2; //Conversion
  kal_data = kalman(distance); //Distancia filtrada

  //Resultados
  Serial.println(distance);
  Serial.print(",");
  Serial.println(kal_data);

  delay(0.01);//Frecuencia

}
