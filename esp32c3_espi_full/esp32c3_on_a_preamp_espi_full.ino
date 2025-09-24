
#include <TFT_eSPI.h>
#include <SPI.h>


TFT_eSPI tft = TFT_eSPI();

void setup(void) {
  Serial.begin(9600);

  tft.init();
  tft.setRotation(-3);
  tft.fillScreen(0);

  analogReadResolution(12);
  delay(1500);
}

unsigned long snap1;
unsigned long snap2;
int fr = 0;
bool clear = false;
void loop() {

  //if (touch() == true) { // this is for fps reading
  //  snap1 = FR_snapS();
  //}


  disaudio();

 //if (touch() == true) {
 //  snap2 = FR_snapE();
 //  fr = FR_cal(snap1, snap2);
 //}
}




unsigned long FR_snapS() {
  return millis();
}

unsigned long FR_snapE() {
  return millis();
}

int FR_cal(unsigned long snap1, unsigned long snap2) {
  int framerate = (1000.0 / (snap2 - snap1));
  //tft.setTextSize(1); // uncomment this to dispalt fps// it will flicker really hard to better see in serial
  //tft.setCursor(3, 3);
  //tft.setTextColor(0xffff, 0);
  //tft.println(framerate);
  return framerate;
}

unsigned long wait;
unsigned long wait1 = 0;
unsigned long wait2 = 0;
bool stop;
int zoom_d = 0;
int zoom_d2 = 0;
int adjust_d = 0;
int avg = 1;
int adjust = 0;
bool run_once = false;
int analog3;
int scale_state = 20;
int scale = 4095 / scale_state;

void disaudio() {
  int arr[1];
  int zoom = analogRead(1) / 204.8 + 1.0;  // max 20 states //scale // when you use poten the higher the number ther tighter it will be, it will jump number apply to all pot
  int adjust_for_max_scale = 20;           // when max scale wave shift out of center
  arr[0] = 68;

  for (int i = -1 - zoom; i <= 240; i += zoom) {

    if (analogRead(2) / scale_state >= (scale * adjust) / scale_state) {  // /25 are for just scaling, may or may not work
      (adjust++) * scale_state;
    }
    if (analogRead(2) / scale_state <= (scale * adjust) / scale_state) {
      (adjust--) * scale_state;
    }

    //adjust wave scale, +1 to stop it from going to zero
    int posamp = (analogRead(3) - avg - adjust_for_max_scale) / (adjust + 1);


    //auto adjust
    avg = ((analogRead(3) / 20 + avg / 20) / 2) * 20;  // reading avg to find a number for reduction


    tft.fillRect(i + 1, 0, zoom, 135, 0);  //draw clearing line // must be one step ahead
    tft.drawFastHLine(i, 68, 1, 0x9492);   // draw mid line

    arr[1] = posamp;
    tft.drawLine(i, arr[0] + 68, i + zoom, arr[1] + 68, 0xfd00);  // draw connecting line from point
    arr[0] = arr[1];
  }
}
