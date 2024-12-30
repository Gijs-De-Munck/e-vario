#include <MCUFRIEND_kbv.h>
#include <math.h>

#include <vario.hpp>

MCUFRIEND_kbv tft;



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
    static float temperature = 30;
    sink += delta_sink;
    if(abs(sink) >= 5.)
        delta_sink = -delta_sink;

    updateVario(tft, sink, temperature);
    delay(50);

    //end of vario needle
}


