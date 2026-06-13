#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_NeoPixel.h>

/* =========================================================================
   HARDWARE CONFIGURATION
   - Brain: ESP32 or Arduino Nano
   - Motors: 12x MG90S Servos via PCA9685 (I2C: SDA, SCL pins)
   - Lights: WS2812B NeoPixel Strip on GPIO 5
   ========================================================================= */

#define LED_PIN 5
#define NUM_LEDS 12 // Number of LEDs for eyes and underglow

// Initialize Servo Driver (Default I2C address 0x40)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Initialize LED Strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Sequencer Configuration
const int bpm = 125; 
const int msPerBeat = 60000 / bpm;
const int msPer16th = msPerBeat / 4; 

unsigned long lastBeatTime = 0;
int beatCount = 0;

// Helper: Convert degrees (0-180) to PCA9685 PWM pulse length
int angleToPulse(int angle) {
    int pulse_wide, analog_value;
    pulse_wide = map(angle, 0, 180, 500, 2500); // Typical micro-servo range in microseconds
    analog_value = int(float(pulse_wide) / 1000000 * 50 * 4096);
    return analog_value;
}

// Helper: Move all 6 legs at once (simplified 12-servo mapping)
// Even pins (0,2,4,6,8,10) = Hips (Forward/Back)
// Odd pins (1,3,5,7,9,11) = Knees (Up/Down)
void setRobotPose(int poseIndex) {
    switch (poseIndex) {
        case 0: // Pose 0: High stance, legs extended
            for (int i = 1; i < 12; i+=2) pwm.setPWM(i, 0, angleToPulse(135)); // Knees down (high stance)
            for (int i = 0; i < 12; i+=2) pwm.setPWM(i, 0, angleToPulse(90));  // Hips neutral
            break;
            
        case 1: // Pose 1: Mid stance, front legs up in the air (Crab Rave!)
            for (int i = 1; i < 12; i+=2) pwm.setPWM(i, 0, angleToPulse(90));  // Knees mid
            pwm.setPWM(1, 0, angleToPulse(30)); // Front left knee UP
            pwm.setPWM(3, 0, angleToPulse(30)); // Front right knee UP
            break;
            
        case 2: // Pose 2: Low stance, raving
            for (int i = 1; i < 12; i+=2) pwm.setPWM(i, 0, angleToPulse(45));  // Knees bent (low to ground)
            for (int i = 0; i < 12; i+=2) pwm.setPWM(i, 0, angleToPulse(90));  // Hips neutral
            break;
            
        case 3: // Pose 3: Side shift 
            for (int i = 1; i < 12; i+=2) pwm.setPWM(i, 0, angleToPulse(90));  // Knees mid
            for (int i = 0; i < 12; i+=2) pwm.setPWM(i, 0, angleToPulse(120)); // All hips shift right
            break;
    }
}

// Helper: Update NeoPixel LED colors
void setDiscoLights(int quarterBeat) {
    uint32_t color;
    switch (quarterBeat % 4) {
        case 0: color = strip.Color(255, 0, 0); break;   // Deep Red
        case 1: color = strip.Color(255, 0, 255); break; // Magenta
        case 2: color = strip.Color(0, 255, 255); break; // Cyan (Stingray style)
        case 3: color = strip.Color(255, 0, 0); break;   // Deep Red
    }
    
    // Set all LEDs to the target color
    for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color);
    }
    strip.show();
}

void setup() {
    Serial.begin(115200);
    Serial.println("Starting Hardware Crab Rave Bot...");

    // Initialize NeoPixels
    strip.begin();
    strip.show(); // Turn off all pixels ASAP
    strip.setBrightness(150); // Set brightness to ~60% (saves battery)

    // Initialize Servo Driver
    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates

    // Move to starting position (Pose 0)
    setRobotPose(0);
    delay(2000); 
}

void loop() {
    // Non-blocking timer loop (crucial for microcontrollers)
    unsigned long currentMillis = millis();
    
    if (currentMillis - lastBeatTime >= msPer16th) {
        lastBeatTime = currentMillis; // Reset timer for next 16th note
        
        // Calculate current beats (0-15 for a full 4-beat measure of 16th notes)
        int current16th = beatCount % 16;
        int quarterBeat = (beatCount / 4) % 4;
        
        // Only trigger major movements/light changes on the quarter beat (every 4th 16th note)
        if (current16th % 4 == 0) {
            setRobotPose(quarterBeat);
            setDiscoLights(quarterBeat);
            
            Serial.print("Beat: ");
            Serial.println(quarterBeat);
        }
        
        beatCount++;
    }
    
    // In the future, you can add code outside the `if` block here to 
    // smoothly interpolate the servos between positions, or read a sound sensor!
}