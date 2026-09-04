/*
 * Autonomous Object Detection Drone
 * ESP32-CAM + Edge Impulse
 *
 * Purpose:
 * - Capture images using ESP32-CAM
 * - Run Edge Impulse inference locally
 * - Report detected objects and confidence
 *
 * Project:
 * ESP-32 based Object Detection Drone with AI Model
 */

#include <Arduino.h>
#include "esp_camera.h"

// Edge Impulse inference library
#include <edge-impulse-sdk/classifier/ei_run_classifier.h>

// --------------------------------------------------
// ESP32-CAM CAMERA PINS
// AI Thinker ESP32-CAM configuration
// --------------------------------------------------

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5

#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// --------------------------------------------------
// CAMERA INITIALIZATION
// --------------------------------------------------

bool initializeCamera()
{
    camera_config_t config;

    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer   = LEDC_TIMER_0;

    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;

    config.pin_xclk  = XCLK_GPIO_NUM;
    config.pin_pclk  = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href  = HREF_GPIO_NUM;

    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;

    config.pin_pwdn  = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;

    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_RGB565;

    config.frame_size   = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count     = 1;

    esp_err_t result = esp_camera_init(&config);

    if (result != ESP_OK)
    {
        Serial.print("Camera initialization failed. Error: 0x");
        Serial.println(result, HEX);
        return false;
    }

    Serial.println("Camera initialized successfully.");
    return true;
}

// --------------------------------------------------
// IMAGE DATA CALLBACK FOR EDGE IMPULSE
// --------------------------------------------------

static int getImageData(size_t offset, size_t length, float *out_ptr)
{
    camera_fb_t *fb = esp_camera_fb_get();

    if (!fb)
    {
        Serial.println("Camera capture failed.");
        return -1;
    }

    size_t pixels = fb->width * fb->height;

    for (size_t i = 0; i < length; i++)
    {
        size_t index = offset + i;

        if (index >= pixels)
            break;

        uint16_t pixel = ((uint16_t *)fb->buf)[index];

        uint8_t r = ((pixel >> 11) & 0x1F) << 3;
        uint8_t g = ((pixel >> 5)  & 0x3F) << 2;
        uint8_t b = (pixel & 0x1F) << 3;

        out_ptr[i] = (r << 16) | (g << 8) | b;
    }

    esp_camera_fb_return(fb);

    return 0;
}

// --------------------------------------------------
// SETUP
// --------------------------------------------------

void setup()
{
    Serial.begin(115200);
    delay(2000);

    Serial.println();
    Serial.println("====================================");
    Serial.println(" ESP32-CAM OBJECT DETECTION SYSTEM ");
    Serial.println(" Edge Impulse Embedded AI");
    Serial.println("====================================");

    if (!initializeCamera())
    {
        Serial.println("Camera setup failed.");
        while (true)
        {
            delay(1000);
        }
    }

    Serial.println("System ready.");
}

// --------------------------------------------------
// MAIN LOOP
// --------------------------------------------------

void loop()
{
    Serial.println();
    Serial.println("Capturing image...");

    // Edge Impulse signal structure
    ei::signal_t signal;

    signal.total_length = EI_CLASSIFIER_INPUT_WIDTH *
                          EI_CLASSIFIER_INPUT_HEIGHT;

    signal.get_data = getImageData;

    ei_impulse_result_t result = {};

    Serial.println("Running Edge Impulse inference...");

    EI_IMPULSE_ERROR error =
        run_classifier(&signal, &result, false);

    if (error != EI_IMPULSE_OK)
    {
        Serial.print("Inference error: ");
        Serial.println(error);
        delay(2000);
        return;
    }

    Serial.println("Inference completed.");

    // --------------------------------------------------
    // OBJECT DETECTION RESULTS
    // --------------------------------------------------

#if EI_CLASSIFIER_OBJECT_DETECTION == 1

    bool objectDetected = false;

    for (size_t i = 0;
         i < EI_CLASSIFIER_OBJECT_DETECTION_COUNT;
         i++)
    {
        auto bb = result.bounding_boxes[i];

        if (bb.value == 0)
            continue;

        objectDetected = true;

        Serial.print("Object: ");
        Serial.print(bb.label);

        Serial.print(" | Confidence: ");
        Serial.print(bb.value * 100.0);

        Serial.print("% | X: ");
        Serial.print(bb.x);

        Serial.print(" | Y: ");
        Serial.print(bb.y);

        Serial.print(" | Width: ");
        Serial.print(bb.width);

        Serial.print(" | Height: ");
        Serial.println(bb.height);
    }

    if (objectDetected)
    {
        Serial.println(">>> TARGET OBJECT DETECTED <<<");

        /*
         * Future integration:
         *
         * Detection result can be sent to
         * Pixhawk through MAVLink/UART.
         *
         * Example:
         * ESP32-CAM -> ESP32 -> Pixhawk
         */

    }
    else
    {
        Serial.println("No target object detected.");
    }

#else

    Serial.println("Model is not configured for object detection.");

#endif

    // --------------------------------------------------
    // INFERENCE PERFORMANCE
    // --------------------------------------------------

    Serial.print("DSP: ");
    Serial.print(result.timing.dsp);

    Serial.print(" ms | Classification: ");
    Serial.print(result.timing.classification);

    Serial.print(" ms | Anomaly: ");
    Serial.print(result.timing.anomaly);

    Serial.println(" ms");

    delay(1000);
}
