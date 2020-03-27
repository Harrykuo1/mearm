#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(7, 6); // BT TX->D7 , BT RX->D6

//宣告四顆伺服馬達
Servo motor_up;           //夾子馬達
Servo motor_mid_left;     //左側馬達
Servo motor_mid_right;    //右側馬達
Servo motor_down;         //底部馬達

//宣告四顆伺服馬達的角度並賦值初始化角度
int up = 90;
int mid_left = 90;
int mid_right = 30;
int down = 0;

int claw_open = 0;      //設定夾爪開啟的角度
int claw_close = 90;    //設定夾爪關閉的角度

void setup() {
  
  Serial.begin(9600);      //設定串口通信鮑率
  BT.begin(9600);          //設定藍芽鮑率
  BT.println("BT is ready!"); // 藍牙連線成功後，發佈「準備好了」訊息
  motor_up.attach(11);        //連接pin11到夾子馬達
  motor_mid_left.attach(10);  //連接pin10到夾子馬達
  motor_mid_right.attach(9);  //連接pin9到夾子馬達 
  motor_down.attach(8);       //連接pin8到夾子馬達

  //
  motor_up.write(up);                    //一開始爪子全開，0度
  motor_mid_left.write(mid_left);        //一開始先置中，90度
  motor_mid_right.write(mid_right);      //一開始先退到後面，30度
  motor_down.write(down);                //一開始先置中，90度

}

void loop() {
    char input;
    if(BT.available()){                 //判斷是否有藍芽信息
      next:
      input=BT.read();                  //讀取藍芽信息
      switch(input){
        
        //向前(Front)
        case 'F':
          while(mid_right < 150){
            if(BT.available()){
              goto next;
            }
            mid_right++;
            motor_mid_right.write(mid_right); 
            delay(100);
          }
          break;

        //向後(Back)
        case 'B':
          while(mid_right < 30){
            if(BT.available()){
              goto next;
            }
            mid_right--;
            motor_mid_right.write(mid_right); 
            delay(100);
          } 
          break;

        //向左(Left)
        case 'L':
          while(down < 180){
            if(BT.available()){
              goto next;
            }
            down++;
            motor_down.write(down); 
          }   
          break;

        //向右(Right) 
        case 'R':
          while(down > 0){
            if(BT.available()){
              goto next;
            }
            down--;
            motor_down.write(down); 
            delay(100);
          }   
          break;

        //向上(Up)  
        case 'U':
          while(mid_left < 130){
            if(BT.available()){
              goto next;
            }
            mid_left++;
            motor_mid_left.write(mid_left); 
            delay(100);
          }
          break;

        //向下(Down)  
        case 'D':
          while(mid_left > 50){
            if(BT.available()){
              goto next;
            }
            mid_left--;
            motor_mid_left.write(mid_left); 
            delay(100);
          } 
          break;

        //開夾子(Open)
        case 'O':
          motor_up.write(claw_open);
          break;

        //關夾子(Close)  
        case 'C':
          motor_up.write(claw_close);
          break;
        
      }
    }
}
