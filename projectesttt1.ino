/*
  LED_Test_All – ET-BASE AVR EASY32U4 (ATmega32U4)
  เลือก "ชุดพิน" ด้านล่างให้ตรงกับที่เสียบจริง
  - USE_A_PINS:   A0..A4
  - USE_DNUM_PINS:D18..D22 (เทียบ A0..A4)
  - USE_D_PINS:   D4..D8 (เผื่อเลี่ยงความสับสนพอร์ต A)
*/

#define USE_A_PINS     1   // <-- ใช้ชุดนี้ (A0..A4) เป็นค่าเริ่ม
#define USE_DNUM_PINS  0   // <-- ตั้งเป็น 1 ถ้าจะใช้ 18,19,20,21,22
#define USE_D_PINS     0   // <-- ตั้งเป็น 1 ถ้าจะย้ายไป 4,5,6,7,8

#if USE_A_PINS
const int   ledPins[]  = {A0, A1, A2, A3, A4};
const char* ledNames[] = {"A0","A1","A2","A3","A4"};
#elif USE_DNUM_PINS
const int   ledPins[]  = {18, 19, 20, 21, 22}; // เทียบ A0..A4 บน 32U4
const char* ledNames[] = {"D18(A0)","D19(A1)","D20(A2)","D21(A3)","D22(A4)"};
#else
const int   ledPins[]  = {4, 5, 6, 7, 8};      // ดิจิทัลชัดเจน
const char* ledNames[] = {"D4","D5","D6","D7","D8"};
#endif

// ถ้าคุณต่อแบบ sink (Anode->+5V, Cathode->Pin) ให้ตั้ง false
const bool ACTIVE_HIGH = true;

inline void LED_WRITE(int pin, bool on){
  digitalWrite(pin, (ACTIVE_HIGH ? (on?HIGH:LOW) : (on?LOW:HIGH)));
}

void all(bool on){ for (unsigned i=0;i<sizeof(ledPins)/sizeof(ledPins[0]); ++i) LED_WRITE(ledPins[i], on); }

void setup(){
  Serial.begin(115200);
  for (unsigned i=0;i<sizeof(ledPins)/sizeof(ledPins[0]); ++i){
    pinMode(ledPins[i], OUTPUT);
    LED_WRITE(ledPins[i], false);
  }
  pinMode(LED_BUILTIN, OUTPUT); // D13 ออนบอร์ด ไว้ยืนยันสเก็ตช์กำลังรัน
}

void loop(){
  // กระพริบ LED ออนบอร์ดเล็กน้อยให้รู้ว่าสเก็ตช์วิ่งอยู่
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  // A) กระพริบ "พร้อมกัน" 3 ครั้ง
  for (int k=0;k<3;k++){
    all(true);  delay(300);
    all(false); delay(300);
  }

  // B) วิ่งไฟไปขวา (ดูชื่อพินใน Serial Monitor)
  for (unsigned i=0;i<sizeof(ledPins)/sizeof(ledPins[0]); ++i){
    all(false);
    LED_WRITE(ledPins[i], true);
    Serial.print("ON "); Serial.println(ledNames[i]);
    delay(500);
  }

  // C) วิ่งกลับ
  for (int i=(int)sizeof(ledPins)/sizeof(ledPins[0])-2; i>=1; --i){
    all(false);
    LED_WRITE(ledPins[i], true);
    Serial.print("ON "); Serial.println(ledNames[i]);
    delay(500);
  }

  // D) ติดทั้งหมด 1 วิ แล้วดับ 1 วิ
  all(true);  delay(1000);
  all(false); delay(1000);
}
