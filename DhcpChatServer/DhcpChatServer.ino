
#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>  // Thêm thư viện Servo.h

#define MOTOR_PIN 9  // Định nghĩa chân điều khiển động cơ

Servo esc;  // Khởi tạo đối tượng Servo cho ESC

byte mac[] = {
  0x90, 0xA2, 0xDA, 0x0D, 0x3E, 0x48
};
IPAddress ip(10, 11, 12, 10);
IPAddress myDns(8, 8, 8, 8);
IPAddress gateway(10, 11, 12, 9);
IPAddress subnet(255, 255, 255, 0);

// telnet defaults to port 23
EthernetServer server(23);
bool gotAMessage = false;  // whether or not you got a message from the client yet
char receivedChar;         // Biến lưu trữ ký tự đọc được từ client

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Trying to get an IP address using DHCP");

  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  // }
  // print your local IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());

  esc.attach(MOTOR_PIN);  // Gắn ESC vào chân điều khiển động cơ

  // start listening for clients
  server.begin();
}

// void loop() {

//   EthernetClient client = server.available();

//   if (client) {
//     if (!gotAMessage) {
//       Serial.println("We have a new client");
//       client.println("Hello, client!");
//       gotAMessage = true;
//     }

//     char thisChar = client.read();
//     if (thisChar != -1) { // Kiểm tra xem dữ liệu đọc được có hợp lệ không
//       int value = thisChar - '0'; // Chuyển dữ liệu từ ký tự sang giá trị số
//       int mappedValue = map(value, 0, 9, 1000, 2000); // Chuyển giá trị số từ 0-9 sang giá trị microseconds từ 1000-2000
//       esc.writeMicroseconds(mappedValue); // Ghi giá trị điều khiển vào ESC
//     }

//     server.write(thisChar);
//     Serial.print(thisChar);

//     Ethernet.maintain();
//   }
// }

void loop() {
  EthernetClient client = server.available();

  if (client) {
    if (!gotAMessage) {
      Serial.println("We have a new client");
      client.println("Hello, client!");
      gotAMessage = true;
    }

    if (client.available()) {
      receivedChar = client.read();
      if (receivedChar == '0' || receivedChar == '1' || receivedChar == '2' || receivedChar == '3' || receivedChar == '4' || receivedChar == '5' || receivedChar == '6' || receivedChar == '7' || receivedChar == '8' || receivedChar == '9') {
        int value = receivedChar - '0';
        int mappedValue = map(value, 0, 9, 1000, 2000);
        esc.writeMicroseconds(mappedValue);
      }
    }

    server.write(receivedChar);
    Serial.print(receivedChar);

    Ethernet.maintain();
  }
}