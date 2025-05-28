#include <homekit/homekit.h>
#include <homekit/characteristics.h>

homekit_characteristic_t cha_motion_detected = HOMEKIT_CHARACTERISTIC_(MOTION_DETECTED, false);

homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(
            .id = 1,
            .category = homekit_accessory_category_sensor,
            .services = (homekit_service_t *[]){
                HOMEKIT_SERVICE(
                    ACCESSORY_INFORMATION,
                    .characteristics = (homekit_characteristic_t *[]){
                        HOMEKIT_CHARACTERISTIC(NAME, "Motion Sensor"),
                        HOMEKIT_CHARACTERISTIC(MANUFACTURER, "YourCompany"),
                        HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "12345678"),
                        HOMEKIT_CHARACTERISTIC(MODEL, "MyMotionSensor"),
                        HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
                        HOMEKIT_CHARACTERISTIC(IDENTIFY, NULL),
                        NULL}),
                HOMEKIT_SERVICE(MOTION_SENSOR, .primary = true, .characteristics = (homekit_characteristic_t *[]){&cha_motion_detected, NULL}), NULL}),
    NULL};

homekit_server_config_t config = {
    .accessories = accessories,
    .password = "111-11-111"};