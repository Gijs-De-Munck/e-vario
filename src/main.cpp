#include <MCUFRIEND_kbv.h>
#include <math.h>

#include <vario.hpp>

MCUFRIEND_kbv tft;

float temperature = 30;
float previous_temperature = 0;


void setup() {
    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(0); // Portrait

    // Draw a static clock face for reference (if needed)
    tft.fillScreen(TFT_BLACK);
    tft.drawCircle(160, 160, 140, TFT_WHITE);
    tft.fillRect(160, 0, 180, 320, TFT_BLACK);
}

void loop() {
    static float sink = 0;
    static float delta_sink = 0.1;
    sink += delta_sink;
    if(abs(sink) >= 5.)
        delta_sink = -delta_sink;

    updateVario(tft, sink);
    delay(50);

    //end of vario needle

    //begin of temperature indicator
    if(temperature != previous_temperature) {
        tft.setCursor(10, 10);
        tft.setTextSize(2);
        tft.setTextColor(TFT_BLACK);
        tft.print(previous_temperature, 1);
        tft.write('C');
        tft.setCursor(10, 10);
        tft.setTextColor(TFT_WHITE);
        tft.print(temperature, 1);
        tft.write('C');
        previous_temperature = temperature;
    }
}