/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
#define USB_SUSPEND_WAKEUP_DELAY 200
#define FIRMWARE_VERSION u8"dAA/M7l"
#define RAW_USAGE_PAGE 0xFF60
#define RAW_USAGE_ID 0x61
#define LAYER_STATE_8BIT
#define COMBO_COUNT 1
#define PERMISSIVE_HOLD
#define TAPPING_TERM 160
#define ONESHOT_TIMEOUT 3500
#define DYNAMIC_MACRO_SIZE 192
#define DYNAMIC_MACRO_NO_NESTING
#define FORCE_NKRO
#define HAL_USE_SERIAL FALSE
// #define DEBUG_ENABLE
// #define DEBUG_MATRIX_SCAN_RATE
#define RGB_MATRIX_STARTUP_SPD 60
#define COMBO_TERM 16
// #define EECONFIG_USER_DATA_SIZE 8192
// #define MK_KINETIC_SPEED
// #define MOUSEKEY_DELAY 8
// #define MOUSEKEY_MAX_SPEED 5
