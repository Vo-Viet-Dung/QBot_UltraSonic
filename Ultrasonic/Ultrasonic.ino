//-----------------------------------------------------------------------------------------------
//  SỬ DỤNG MODULE ULTRASONIC / SIÊU ÂM ĐỂ ĐO KHOẢNG CÁCH
//  Qbot có 1 module Ultrasonic cắm ở phía trên mặt
//     Chương trình demo này sẽ liên tục lấy khoảng cách và truyền serial về máy tính.
//     Nếu ở trong chương trình Arduino IDE, hãy mở cửa sổ Tools / Serial Monitor để xem kết quả
//-----------------------------------------------------------------------------------------------
#include<Arduino.h>
#include<WMBoard.h>
#include<WMHead.h>
/// Sensor1 Cam bien hong ngoai do line (11)
/// Sensor1 Cam bien hong ngoai do line (12)
WMLineFollower lineFollower1(11,12);     
/// Tạo hanlder điều khiển động cơ trái với 2 pin 8(hướng quay), và 6(công suất PWM)
WMDCMotor motor1(8);
/// Tạo hanlder điều khiển động cơ phải với 2 pin 7(hướng quay), và 5(công suất PWM)
WMDCMotor motor2(7); 

#define ECHOPIN 4
#define TRIGPIN 3

/// @brief  Lây khoảng cách tới vật thể từ cảm biến siêu âm
/// @remark   nên đợi một chút, tầm 100ms trước khi gọi hàm lần nữa
int get_distance(){
  digitalWrite(TRIGPIN, LOW);                    // Set chan Trig xuong muc thap 2uS: ~~__
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);                   //Gui mot xung 10uS muc cao vao chan Trig ~~__----------
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);                    // Gui lai muc thap vao chan Trig         ~~__----------____
  int distance = pulseIn(ECHOPIN, HIGH);        // Đếm thời gian (đơn vị us) cho tới khi chân ECHOPIN có sườn lên
  distance= distance/58;                        // Qui đổi thời gian ra khoảng cách
  delay(100);
  return distance;
}


void setup() {
  Serial.begin(9600);             // Thiết lập giao tiếp serial giữa máy tính và QBot
  
  /// Cấu hình module Ultrasonic kết nối với Qbot
  pinMode(TRIGPIN, OUTPUT);      // Chân sẽ kích hoạt module ultrasonic bắn ra 1 luồng siêu âm
  pinMode(ECHOPIN, INPUT);       // Chân nhận về phản hồi khi module ultrasonic lắng nghe tiếng vọng
}

void loop() {
  Serial.println(get_distance()); // Lấy khoảng cách và hiển thị lên serial
  ///Nếu khoảng cách nhỏ hơn 40cm thì dừng lại đợi 
  if(get_distance()<40){
    motor1.run(0);
    motor2.run(0);
  }
  ///Nếu khoảng cách lớn hơn 40cm thì bắt đầu đi
  else if(get_distance()>40){
   motor1.reverseRun(20);
   motor2.reverseRun(20); 
  }
  
}
