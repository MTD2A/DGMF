int arrSensorStatus[26];

void setup() {                
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);
  pinMode(25, INPUT);
  pinMode(26, INPUT);
  pinMode(27, INPUT);
  pinMode(28, INPUT);
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
  pinMode(46, INPUT);
  pinMode(47, INPUT);
  pinMode(48, INPUT);
  pinMode(49, INPUT);
  pinMode(50, INPUT);
  pinMode(51, INPUT);
  pinMode(52, INPUT);
  pinMode(53, OUTPUT);
  //Serial.begin(9600);
}

void loop() {
  readSensors();
  writeDiodes();
  //Serial.println(arrSensorStatus[1]);
}

void readSensors() {
  arrSensorStatus[1] = digitalRead(2);
  arrSensorStatus[2] = digitalRead(3);
  arrSensorStatus[3] = digitalRead(4);
  arrSensorStatus[4] = digitalRead(5);
  arrSensorStatus[5] = digitalRead(6);
  arrSensorStatus[6] = digitalRead(7);
  arrSensorStatus[7] = digitalRead(8);
  arrSensorStatus[8] = digitalRead(9);
  arrSensorStatus[9] = digitalRead(10);
  arrSensorStatus[10] = digitalRead(11);
  arrSensorStatus[11] = digitalRead(12);
  arrSensorStatus[12] = digitalRead(13);
  arrSensorStatus[13] = digitalRead(22);
  arrSensorStatus[14] = digitalRead(23);
  arrSensorStatus[15] = digitalRead(24);
  arrSensorStatus[16] = digitalRead(25);
  arrSensorStatus[17] = digitalRead(26);
  arrSensorStatus[18] = digitalRead(27);
  arrSensorStatus[19] = digitalRead(28);
  arrSensorStatus[20] = digitalRead(46);
  arrSensorStatus[21] = digitalRead(47);
  arrSensorStatus[22] = digitalRead(48);
  arrSensorStatus[23] = digitalRead(49);
  arrSensorStatus[24] = digitalRead(50);
  arrSensorStatus[25] = digitalRead(51);
  arrSensorStatus[26] = digitalRead(52);

}

void writeDiodes() {
  digitalWrite(53, arrSensorStatus[1]);
  digitalWrite(45, arrSensorStatus[2]);
  digitalWrite(44, arrSensorStatus[3]);
  digitalWrite(43, arrSensorStatus[4]);
  digitalWrite(21, arrSensorStatus[5]);
  digitalWrite(20, arrSensorStatus[6]);
  digitalWrite(19, arrSensorStatus[7]);
  digitalWrite(18, arrSensorStatus[8]);
  digitalWrite(17, arrSensorStatus[9]);
  digitalWrite(16, arrSensorStatus[10]);
  digitalWrite(15, arrSensorStatus[11]);
  digitalWrite(14, arrSensorStatus[12]);
  digitalWrite(29, arrSensorStatus[13]);
  digitalWrite(30, arrSensorStatus[14]);
  digitalWrite(31, arrSensorStatus[15]);
  digitalWrite(32, arrSensorStatus[16]);
  digitalWrite(33, arrSensorStatus[17]);
  digitalWrite(34, arrSensorStatus[18]);
  digitalWrite(35, arrSensorStatus[19]);
  digitalWrite(36, arrSensorStatus[20]);
  digitalWrite(37, arrSensorStatus[21]);
  digitalWrite(38, arrSensorStatus[22]);
  digitalWrite(39, arrSensorStatus[23]);
  digitalWrite(40, arrSensorStatus[24]);
  digitalWrite(41, arrSensorStatus[25]);
  digitalWrite(42, arrSensorStatus[26]);
}
