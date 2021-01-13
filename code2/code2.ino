void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  for (int i = 0; i < 5; i++)
  {
    if (i % 2 == 0)
      Serial.println(i);
  }

  int p = 0;

  //condition
  while (p < 5)
  {
    Serial.println(p);
    p++;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
