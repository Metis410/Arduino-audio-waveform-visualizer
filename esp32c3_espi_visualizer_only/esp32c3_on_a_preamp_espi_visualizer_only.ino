
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


void loop() {
  disaudio();
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
  //int zoom = analogRead(1) / 204.8 + 1.0;  // max 20 states //scale // when you use poten the higher the number ther tighter it will be, it will jump number apply to all pot
  //int adjust_for_max_scale = 20;           // when max scale wave shift out of center
  arr[0] = 68;

  for (int i = -1; i <= 240; i += 2) {
    int posamp = (analogRead(3) - manualadjust);  // manual adjust will reqiure you to read the analog(3) output and put it in manualadjust, note that it should be = to 0
    //or you can replace it with a pot to A2
    // this is for connecting directly to the A3 pin, if it over 3.3v you will need a pot to divide the voltage

    tft.fillRect(i + 1, 0, 2, 135, 0);    //draw clearing line // must be one step ahead
    tft.drawFastHLine(i, 68, 1, 0x9492);  // draw mid line

    arr[1] = posamp;
    tft.drawLine(i, arr[0] + 68, i + 2, arr[1] + 68, 0xfd00);  // draw connecting line from point
    arr[0] = arr[1];

    //this is all it need to visualize waveform
    //do the full setup will get you plenty of benefit, check skematic

    // it may or may not display correct on this one
  }
}