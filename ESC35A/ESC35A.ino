#include <Servo.h>  // Thêm thư viện Servo.h

#define MOTOR_PIN 9  // Định nghĩa chân điều khiển động cơ

Servo esc;  // Khởi tạo đối tượng Servo cho ESC

void setup() {
  esc.attach(MOTOR_PIN);  // Gắn ESC vào chân điều khiển động cơ
}

void loop() {

  esc.writeMicroseconds(2000);
  delay(2000);

  esc.writeMicroseconds(0);
  delay(3000);

  esc.writeMicroseconds(1000);
  delay(2000);

  esc.writeMicroseconds(0);
  delay(3000);
}