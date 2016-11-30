// 1421
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

File file;
int command = 0;
int inputStatus = -1;

SoftwareSerial mySerial(6,5); // TX, RX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  mySerial.begin(9600);
  while (!Serial) {
    ;
  }

  if (!SD.begin(4)) {
    return;
  }
}

void playMusic(char c) {
  char str[2];
  str[0] = c;
  str[1] = '\0';
  file = SD.open(str);
  Serial.println("file open");
  Serial.println(c);

  while (file.available()) {
    Serial.write(file.read());
  }

  file.close();
}

void loop() {
  if (mySerial.available()) {
    char c = mySerial.read();
//    Serial.write(c);

    if (c == '@') {
      inputStatus = 1;
    }

    // 와이파이에서 들어온 명령 ex)@a, @b, @c, @d
    else if (inputStatus) {
      // play index 받을 때
      if (command == 1) {
        command = 0;
        inputStatus = 0;

        playMusic(c);
      }
      // play
      else if (c == 'a') {
        command = 1;
      }
      // stop
      else if (c == 'b') {
        command = 0;
        inputStatus = 0;
      }
      // next
      else if (c == 'c') {
        command = 0;
        inputStatus = 0;
      }
      // prev
      else if (c == 'd') {
        command = 0;
        inputStatus = 0;
      }
    }
  }
}


