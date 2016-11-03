

///redbear etarts

SYSTEM_MODE(MANUAL);//do not connect to cloud


///redbear ends



void setup() {
// initialize both serial ports:
//Serial.begin(57600);
Serial.begin(115200);
Serial1.begin(115200);
//Serial.begin(230400);
//Serial1.begin(230400);
Serial.write("Start0.");
Serial1.write("Start1.");
}
void loop() {
// read from port 1, send to port 0:
if (Serial1.available()) {
int inByte = Serial1.read();
Serial.write(inByte);
}
// read from port 0, send to port 1:
if (Serial.available()) {
int inByte = Serial.read();
Serial1.write(inByte);
}
}
