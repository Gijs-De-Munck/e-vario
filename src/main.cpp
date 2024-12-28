#include <MCUFRIEND_kbv.h>
#include <math.h>

MCUFRIEND_kbv tft;

int angle_degrees = 180; // Initial angle

float temperature = 30;
float previous_temperature = 0;

void drawArrow(int angle);

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
    static int delta = 2;
    angle_degrees += delta;
    if(angle_degrees >= 360) {
        delta = -abs(delta);
    }
    if(angle_degrees <= 180) {
        delta = abs(delta);
    }
    // Increment angle

    //angle_degrees = (angle_degrees + 2) % 360; // Keep angle within 0-359 degrees
    drawArrow(angle_degrees);
    delay(100); // Adjust delay for desired update speed
    //end of vario needle

    //begin of temperature indicator
    if(temperature != previous_temperature) {
        tft.setCursor(10, 10);
        tft.setTextSize(2);
        tft.setTextColor(TFT_BLACK);
        tft.print(previous_temperature);
        tft.write('C');
        tft.setCursor(10, 10);
        tft.setTextColor(TFT_WHITE);
        tft.print(temperature);
        tft.write('C');
        previous_temperature = temperature;
    }
}

void drawArrow(int angle_degrees) {
    const int cx = 160;       // Center of the clock
    const int cy = 160;
    const int length = 50;    // Length of the hand
    const int width = 5; 
    const int start_offset = 85; // Distance from the center to start the line

    static int old_start_x_1, old_start_y_1, old_start_x_2, old_start_y_2, old_end_x, old_end_y; // To track previous hand position

    float angle_radians = angle_degrees * PI / 180.0;
    float cos_angle = cos(angle_radians);
    float sin_angle = sin(angle_radians);

    int start_x_1 = cx + start_offset * sin_angle - width * cos_angle;
    int start_y_1 = cy - start_offset * cos_angle - width * sin_angle;
    int start_x_2 = cx + start_offset * sin_angle + width * cos_angle;
    int start_y_2 = cy - start_offset * cos_angle + width * sin_angle;
    int end_x = cx + (start_offset + length) * sin_angle;
    int end_y = cy - (start_offset + length) * cos_angle;

    // Erase old hand
    if (old_end_x != 0 || old_end_y != 0) { // Only erase if an old hand exists
        tft.fillTriangle(old_start_x_1, old_start_y_1, old_start_x_2, old_start_y_2, old_end_x, old_end_y, TFT_BLACK);
    }

    tft.fillTriangle(start_x_1, start_y_1, start_x_2, start_y_2, end_x, end_y, TFT_RED);

    old_start_x_1 = start_x_1;
    old_start_y_1 = start_y_1;
    old_start_x_2 = start_x_2;
    old_start_y_2 = start_y_2;
    old_end_x = end_x;
    old_end_y = end_y;
}
