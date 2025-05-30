// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "version.h"
#include "i18n.h"
#include "features/achordion.h"
#include "keymap_steno.h"
#include "snip/snip.h"
#include "print.h"
#include "debug.h"
#include "oryx.h"
#include <string.h>         // For string functions (memcpy, strcpy, etc.)
#define MOON_LED_LEVEL LED_LEVEL
#define REP_SFT LT(1, QK_REP)
#define AREP_SYM MT(MOD_LSFT, QK_AREP)
#define REP_MEH MT(MOD_MEH, QK_REP)
// #define RGB_WHITE 255, 255, 255
// #define RGB_SOFT_DARK_GREEN 0, 100, 50 // Adjust these values to get the exact shade you want
#define BUFFER_SIZE 10
#define DEBUG

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  HSV_0_255_255,
  HSV_74_255_255,
  HSV_169_255_255,
  ST_MACRO_0,
  ST_MACRO_1,
  ST_MACRO_2,
  M_ION,
  M_ING,
  SCRNSHT,
  THORN,
  QUICK_CLICK,
  CLICK_END,
  ERR_NIL,
  FMT_ERR,
  PR_ERR,
  NV_SAVE,
  KC_SNIP,

  MG_ION,
  MG_NG,
  MG_ENT,
  MG_UE,
  MG_TION,
};

#define L_HR_1 LT(2, KC_N)
#define L_HR_2 MT(MOD_LALT, KC_R)
#define L_HR_3 KC_T
#define L_HR_4 KC_S
#define R_HR_1 KC_H
#define R_HR_2 KC_A
#define R_HR_3 KC_E
#define R_HR_4 KC_I

enum tap_dance_codes {
  DANCE_0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Main Keyboard
  [0] = LAYOUT_voyager(
    KC_ESCAPE,      SCRNSHT,     KC_DEL,      KC_PC_COPY,     KC_PC_PASTE,      TG(4),                                          KC_F13,     KC_F14,          KC_MINUS,          KC_EQL,      KC_F15,     KC_F16,
    KC_TAB,    KC_Q,        KC_X,        KC_M,           KC_W,             KC_V,                                           KC_J,           KC_F,           KC_O,           KC_U,        KC_SCLN,     CW_TOGG,
    KC_LEFT_CTRL,         L_HR_1,      L_HR_2,      L_HR_3,         L_HR_4,           KC_G,                                           KC_Y,           R_HR_1,      R_HR_2,            R_HR_3,      R_HR_4,  KC_BSPC,
    KC_LEFT_SHIFT,  LT(3,KC_B),  KC_L,               KC_D,        KC_C,           KC_Z,                                         KC_K,           KC_P,           KC_COMMA,    KC_DOT,      KC_SLASH, MOD_MEH,
                                                    OSL(1),       OSM(MOD_LSFT),                                     MT(MOD_LEFT_GUI, KC_ENTER), LT(5,KC_SPACE)
  ),

  // Symbols
  [1] = LAYOUT_voyager(
    KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                          KC_AUDIO_MUTE,          KC_AUDIO_VOL_UP,          KC_AUDIO_VOL_DOWN,          KC_F9,          KC_F10,         KC_F11,
    KC_TRANSPARENT, KC_GRAVE,       KC_LABK,        KC_RABK,        KC_AT,          KC_AMPR,                                         KC_DQUO,        KC_QUOTE,       KC_LBRC,        KC_RBRC,        KC_PERC,        KC_F12,
    KC_LEFT_CTRL, KC_EXLM,        KC_MINUS,       KC_PLUS,        KC_EQUAL,       KC_NONUS_HASH,                                    KC_CIRC,        KC_COLN,        KC_LCBR,        KC_RCBR,        KC_QUES,        KC_BSPC,
    KC_HASH,        LSFT(KC_NUBS),  KC_SLASH,       KC_ASTR,        KC_NUBS,        KC_DLR,                                         LSFT(KC_NONUS_HASH),KC_UNDS,        KC_LPRN,        KC_RPRN,        KC_DQUO,        KC_ENTER,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT,          KC_SPACE
                                                    // KC_HASH IS GBP!!!
  ),


  // Numbers
  [2] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_CALCULATOR, KC_COMMA,       KC_SLASH,       KC_ASTR,        KC_CALC,         TO(4),
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,           KC_TRANSPARENT,           KC_PERC,                                        KC_TRANSPARENT, KC_7,           KC_8,           KC_9,           KC_MINUS,       KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,           KC_TRANSPARENT,           KC_CIRC,                                        KC_DOT,         KC_4,           KC_5,           KC_6,           KC_PLUS,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,           KC_TRANSPARENT,           KC_DOT,                                         KC_DOT,         KC_1,           KC_2,           KC_3,           KC_ENTER,       KC_TRANSPARENT,
                                                                     KC_SPACE,            OSM(MOD_LSFT),                               KC_ENTER,           KC_0
  ),

  // [F] Keys
  [3] = LAYOUT_voyager(
    RGB_TOG,        TOGGLE_LAYER_COLOR,RGB_MODE_FORWARD,RGB_SLD,        RGB_VAD,        KC_TRANSPARENT,                            KC_TRANSPARENT, KC_F10,        KC_F11,         KC_F12,         KC_F13, QK_BOOT,
    KC_TRANSPARENT, KC_MY_COMPUTER, KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,  KC_TRANSPARENT,                               KC_PAGE_UP,     KC_F7,        KC_F8,          KC_F9,         KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_LEFT_ALT,KC_LEFT_CTRL,  KC_LEFT_SHIFT,KC_TRANSPARENT,                                    KC_PGDN,        KC_F4,        KC_F5,        KC_F6,       KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT,                                KC_TRANSPARENT, KC_F1, KC_F2,   KC_F3, KC_TRANSPARENT, KC_TRANSPARENT,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),

  // Gaming Layout
  [4] = LAYOUT_voyager(
    KC_ESCAPE,      KC_1,           KC_2,           KC_3,           KC_4,           TG(4),                                           KC_6,           KC_7,           KC_8,           KC_9 ,           KC_0,           TO(1),
    KC_GRAVE,       KC_T,           KC_Q,           KC_W,           KC_E,           KC_R,                                           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLS,
    KC_TAB,           KC_LEFT_SHIFT,  KC_A,           KC_S,           KC_D,           KC_F,                                           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        MT(MOD_RSFT, KC_QUOTE),
    KC_LEFT_GUI,    KC_LEFT_CTRL,   KC_Z,           KC_X,           KC_C,           KC_V,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         MT(MOD_RALT, KC_SLASH),KC_RIGHT_CTRL,
                                                    KC_SPACE,       KC_G,                                         KC_ENTER,KC_SPACE
  ),

  // Navigation & Macros
  [5] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP, LALT(KC_F4),    KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, ST_MACRO_2,     ERR_NIL,        KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_WWW_HOME,    KC_HOME,        KC_UP,          KC_END,         KC_PAGE_UP,     KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LEFT_GUI,    KC_LEFT_ALT,    KC_LEFT_CTRL,   KC_LEFT_SHIFT,  KC_TRANSPARENT,                                 KC_WWW_BACK,    KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_PAGE_DOWN,     KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, FMT_ERR,        PR_ERR,         KC_TRANSPARENT,                                 KC_WWW_FORWARD, ST_MACRO_1,   ST_MACRO_0,     KC_TRANSPARENT, KC_APP, KC_TRANSPARENT,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),

  // Mouse layer
  [6] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 TG(6), KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP, LALT(KC_F4),    KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, ST_MACRO_2, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                     KC_WWW_HOME,    KC_MS_BTN3,        KC_MS_UP,          KC_MS_BTN4,         KC_MS_WH_UP,     TG(6),
    KC_TRANSPARENT, KC_LEFT_GUI,    KC_LEFT_ALT,    KC_LEFT_CTRL,   KC_LEFT_SHIFT,  KC_TRANSPARENT,                                 KC_WWW_BACK,    KC_MS_LEFT,        KC_MS_DOWN,        KC_MS_RIGHT,       KC_MS_WH_DOWN,     KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TG(6),          KC_MS_BTN2, KC_TRANSPARENT,                                     KC_WWW_FORWARD, CLICK_END,        KC_MS_BTN1,     CLICK_END,           QUICK_CLICK,                TG(6),
                                                       KC_TRANSPARENT,         KC_TRANSPARENT,                                 KC_MS_BTN1, KC_MS_BTN1
  ),
  // steno layer
  // [7] = LAYOUT_voyager(
  //   KC_ESCAPE,      KC_1,           KC_2,           LALT(KC_TAB),           KC_4,           KC_5,                                           KC_6,           KC_7,           KC_UNDO,           KC_9 ,           KC_0,           TG(7),
  //   KC_TAB,         STN_NUM,        STN_TL,         STN_PL,         STN_HL,         STN_STR,                                        STN_STR,        STN_FR,         STN_PR,         STN_LR,         STN_TR,          STN_DR,
  //   KC_TAB,  STN_S2,         STN_KL,         STN_WL,         STN_RL,         STN_STR,                                        STN_STR,        STN_RR,         STN_BR,         STN_GR,         STN_SR,          STN_ZR,
  //   KC_TAB,   OSL(2),         OSL(1),         TG(7),          KC_BSPC,        KC_DEL,                                        KC_ENTER,       KC_SPACE,         KC_COMMA,       KC_DOT,         KC_SLASH,          STN_ZR,
  //                                                                           STN_A,       STN_O,              STN_E,   STN_U
  // ),

  // Full QWERTY
  //   [7] = LAYOUT_voyager(
  //   KC_ESCAPE,      SCRNSHT,     KC_DEL,      KC_PC_COPY,     KC_PC_PASTE,      TG(4),                                          KC_UNDO,     LCTL(KC_Y),          KC_DEL,          TG(7),   SCRNSHT,     TG(7),
  //   KC_LEFT_GUI,    KC_Q,           KC_W,           KC_E,           KC_R,         KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,       KC_P,     TG(6),
  //   KC_TAB,         LT(2, KC_A),MT(MOD_LALT,KC_S),MT(MOD_LCTL, KC_D), MT(MOD_LSFT,KC_F),  KC_G,                                   KC_H,           MT(MOD_LSFT,KC_J),MT(MOD_LCTL,KC_K),MT(MOD_LALT,KC_L),      KC_SCLN,  KC_BSPC,
  //   KC_LEFT_SHIFT,  LT(3,KC_Z),  KC_X,               KC_C,        KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,    KC_DOT,      KC_SLASH, CW_TOGG,
  //                                                   OSL(1),       OSM(MOD_LSFT),                                     MT(MOD_MEH, KC_ENTER), LT(5, KC_SPACE)
};


//################################################################################################################################
// Combos, Macros, and Custom Keycodes
//################################################################################################################################

enum combo_events {
  SW_STENO,
  SNIP,
  TAB,
  ENTER,
  ESCAPE,
};

const uint16_t PROGMEM sw_steno[] = {KC_PLUS, KC_SLASH, COMBO_END};
const uint16_t PROGMEM snip[] = {MT(MOD_LSFT,KC_H), MT(MOD_LCTL,KC_A), COMBO_END};
const uint16_t PROGMEM tab[] = {R_HR_1, R_HR_2, COMBO_END};
const uint16_t PROGMEM enter[] = {KC_P, KC_COMMA, COMBO_END};
const uint16_t PROGMEM escape[] = {KC_F, KC_O, COMBO_END};

combo_t key_combos[] = {
    [SW_STENO] = COMBO_ACTION(sw_steno),
    [SNIP] = COMBO_ACTION(snip),
    [TAB] = COMBO_ACTION(tab),
    [ENTER] = COMBO_ACTION(enter),
    [ESCAPE] = COMBO_ACTION(escape),
};

void matrix_scan_user(void) {
  achordion_task();
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
  switch (keycode) {
    case REP_SFT:
      return false;
    case REP_MEH:
      return false;
  }
  return keycode != AREP_SYM;
  return true;
}

// bool process_record_magic(uint16_t keycode, keyrecord_t *record) {
//     // clang-format off
//     switch (keycode) {
//         case MG_NG: SEND_MAGIC("ng");
//         case MG_ENT: SEND_MAGIC("ent");
//         case MG_ION: SEND_MAGIC("ion");
//         case MG_UE: SEND_MAGIC("ue");
//         case MG_TION: SEND_MAGIC("tion");
//     }
//     // clang-format on

//     return true;
// }

void process_combo_event(uint16_t combo_index, bool pressed) {
  if (!pressed) {
    return;
  }

  switch(combo_index) {
        case TAB: {
            tap_code16(KC_TAB);
        } break;
        case ENTER: {
            tap_code16(KC_ENTER);
        } break;
        case ESCAPE: {
            tap_code16(KC_ESCAPE);
        } break;
  }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_achordion(keycode, record)) { return false; }

  if (process_snippet_tool(keycode, record, KC_SNIP)) { return false; }

  switch (keycode) {

    // case AREP_SYM:
    // if (record->tap.count) {
    //   if (get_repeat_key_count()) {
    //     return true;
    //   }
    //   alt_repeat_key_invoke(&record->event);
    // } else if (record->event.pressed) {
    //   layer_on(1);
    // } else {
    //   layer_off(1);
    // }
    // return false;

    case REP_SFT:
    if (record->tap.count) {
      process_repeat_key(QK_REP, record);
      return false;
    }
    return true;

    case REP_MEH:
    if (record->tap.count && record->event.pressed) {
      process_repeat_key(QK_REP, record);
      return false;
    } else if (!record->tap.count) {
      return true;
    }
    return false;

    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL("u"));
    }
    break;

    case NV_SAVE:
    if (record->event.pressed) {
      SEND_STRING(":wa" SS_DOWN(X_ENTER) SS_UP(X_ENTER));
    }


    case QUICK_CLICK:
    if (record->event.pressed) {
      register_code(KC_MS_BTN1);
      wait_ms(1);
      unregister_code(KC_MS_BTN1);
    }
    return false;

    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL("d"));
    }
    break;

    case ST_MACRO_2:
    if (record->event.pressed) {
      SEND_STRING("Debug.Log($""");
    }
    break;

    case ERR_NIL:
    if (record->event.pressed) {
        SEND_STRING("if err != nil {" SS_DOWN(X_ENTER) SS_UP(X_ENTER));
    }
    break;

    case FMT_ERR:
    if (record->event.pressed) {
        SEND_STRING("fmt.Errorf(");
    }
    break;

    case PR_ERR:
    if (record->event.pressed) {
        SEND_STRING("fmt.Println(");
    }
    break;

    case CLICK_END:
    if (record->event.pressed) {
      register_code(KC_MS_BTN1);
      unregister_code(KC_MS_BTN1);
    } else {
      layer_off(6);
    }
    break;

    case THORN:
    if (record->event.pressed) {
      SEND_STRING("th");
    }
    break;

    case SCRNSHT:
    if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_LSFT) SS_TAP(X_S) SS_UP(X_LSFT) SS_UP(X_LGUI));
    }
    return false;


    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case HSV_0_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(0,255,255);
      }
      return false;
    case HSV_74_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(74,255,255);
      }
      return false;
    case HSV_169_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(169,255,255);
      }
      return false;
  }

  // Process magic AFTER the AREP_SYM case
  // if (!process_record_magic(keycode, record)) {
  //   return false;
  // }

  return true;
}

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
      case MT(MOD_LCTL, KC_A): return KC_O;
      case KC_C: return KC_S;
      case KC_D: return KC_T;
      case MT(MOD_LALT, KC_E): return KC_U;
      case KC_F: return KC_Y;
      case KC_G: return KC_S;
      case MT(MOD_LSFT, KC_H): return KC_Y;
      case KC_I: return MG_NG;
      case KC_J: return KC_I;
      case KC_L: return KC_R;
      case KC_M: return MG_ENT;
      case LT(3,KC_N): return MG_ION;
      case KC_O: return KC_A;
      case KC_P: return KC_H;
      case LT(4, KC_Q): return MG_UE;
      case MT(MOD_LALT, KC_R): return KC_L;
      case MT(MOD_LSFT, KC_S): return KC_C;
      case MT(MOD_LCTL, KC_T): return MG_ION;
      case KC_E: return KC_U;
      case KC_U: return KC_E;
      case KC_W: return KC_S;
    }

    return KC_TRNS;
}

//################################################################################################################################
// Raw HID handling for Snippet Tool
//################################################################################################################################
//

// Buffers and state for building snippets
static char trigger_buffer[SNIP_BUFFER_SIZE] = {0};  // Use SNIP_BUFFER_SIZE from snip.h
static char snippet_buffer[100] = {0};  // Use 100 as specified
static uint8_t current_end_code = 0;
static bool have_trigger = false;
static bool have_snippet = false;
static bool expecting_snippet = false;
static bool writeToEEPROM = false;

// Custom function to handle your raw HID packets
bool ephi_raw_hid_receive(uint8_t *data, uint8_t length) {
    // Actual packet handling (separate from debug)
    // Each packet has a standard header:
    // data[0] = packet type
    // data[1] = sequence type (0x01=start, 0x02=continue, 0x03=end, 0x04=single)
    // data[2+] = payload data

    const uint8_t HEADER_SIZE = 2; // Skip packet type and sequence type
    uint8_t payload_length = length - HEADER_SIZE;
    #ifdef DEBUG
    dprintf("Processing packet\n");
  // dump packet formatted as hex
  for (int i = 0; i < length; i++) {
    dprintf("%02x ", data[i]);
    if (i % 16 == 15) {
      dprintf("\n");
    }
  }
    #endif

    switch (data[0]) {
        case 0x01: // Command packet - RAM storage
            #ifdef DEBUG
            dprintf("Command packet received for RAM storage\n");
            #endif
            // Clear all snippets command
            snippet_collection.snippet_count = 0;

            // Reset state
            have_trigger = false;
            have_snippet = false;
            expecting_snippet = false;
            writeToEEPROM = false;
            memset(trigger_buffer, 0, sizeof(trigger_buffer));
            memset(snippet_buffer, 0, sizeof(snippet_buffer));

            // Start expecting a new sequence
            expecting_snippet = true;

#ifdef DEBUG
            dprintf("Cleared all snippets. Ready for new snippets (RAM storage).\n");
#endif
            break;

        case 0x02: // Command packet - Write to EEPROM
            #ifdef DEBUG
            dprintf("Command packet received for EEPROM storage\n");
            #endif
          // Send a response packet with byte one set to 0xFF
            uint8_t response[32] = {0};
            response[0] = 0xFF; // Confirm end of transmission
            response[1] = 0x01; // Success code
            response[2] = snippet_collection.snippet_count; // Send back total snippets count
            response[3] = 0x55; // Magic test number

            #ifdef DEBUG
            dprintf("Writing %d snippets to EEPROM user data...\n", snippet_collection.snippet_count);
            #endif

            if (sizeof(snippets_collection_t) <= EECONFIG_USER_DATA_SIZE) {
                eeconfig_update_user_datablock(&snippet_collection);
            //
            //     #ifdef DEBUG
            //     dprintf("EEPROM write complete, %d bytes written\n", (int)sizeof(snippets_collection_t));
            //     #endif
            //
                // Success code
                response[1] = 0x02;
            }

                #ifdef DEBUG
                dprintf("ERROR: Snippet collection too large for EEPROM: %d > %d\n",
                       (int)sizeof(snippets_collection_t), EECONFIG_USER_DATA_SIZE);
                #endif

                // // Error code for size issues
                // response[1] = 0xFF;

                raw_hid_send(response, sizeof(response));
            break;

        case 0x05: // Trigger packet
            if (expecting_snippet) {
                // Safety check to ensure we don't overflow buffer
                if (payload_length > SNIP_BUFFER_SIZE-1) {
                    payload_length = SNIP_BUFFER_SIZE-1;
                }

                memcpy(trigger_buffer, &data[HEADER_SIZE+1], payload_length);
                trigger_buffer[payload_length] = '\0'; // Add null terminator
                have_trigger = true;

                #ifdef DEBUG
                dprintf("Trigger captured: '%s'\n", trigger_buffer);
                #endif
            }
            break;

        case 0x06: // Snippet packet
            if (expecting_snippet && have_trigger) {
                switch(data[1]) {
                    case 0x01: // Start snippet
                        memset(snippet_buffer, 0, sizeof(snippet_buffer));

                        // Safety check to avoid overflow
                        if (payload_length >= sizeof(snippet_buffer)) {
                            #ifdef DEBUG
                            dprintf("WARNING: Snippet too long, truncating %d to %d\n",
                                   payload_length, (int)sizeof(snippet_buffer)-1);
                            #endif
                            payload_length = sizeof(snippet_buffer) - 1;
                        }

                        memcpy(snippet_buffer, &data[HEADER_SIZE+1], payload_length);
                        snippet_buffer[payload_length] = '\0';
                        break;

                    case 0x02: // Continue snippet
                        {
                            size_t current_len = strlen(snippet_buffer);
                            size_t remaining = sizeof(snippet_buffer) - current_len - 1;

                            if (payload_length > remaining) {
                                #ifdef DEBUG
                                dprintf("WARNING: Snippet continuation too long, truncating %d to %d\n",
                                       payload_length, (int)remaining);
                                #endif
                                payload_length = remaining;
                            }

                            if (payload_length > 0) {
                                memcpy(&snippet_buffer[current_len], &data[HEADER_SIZE+1], payload_length);
                                snippet_buffer[current_len + payload_length] = '\0';
                            }
                        }
                        break;

                    case 0x03: // End snippet
                        {
                            size_t current_len = strlen(snippet_buffer);
                            size_t remaining = sizeof(snippet_buffer) - current_len - 1;

                            if (payload_length > remaining) {
                                #ifdef DEBUG
                                dprintf("WARNING: Snippet end too long, truncating %d to %d\n",
                                       payload_length, (int)remaining);
                                #endif
                                payload_length = remaining;
                            }

                            if (payload_length > 0) {
                                memcpy(&snippet_buffer[current_len], &data[HEADER_SIZE+1], payload_length);
                                snippet_buffer[current_len + payload_length] = '\0';
                            }

                            have_snippet = true;

                            #ifdef DEBUG
                            dprintf("Completed snippet: '%s'\n", snippet_buffer);
                            #endif
                        }
                        break;

                    case 0x04: // Single packet snippet
                        // Safety check to avoid overflow
                        if (payload_length >= sizeof(snippet_buffer)) {
                            #ifdef DEBUG
                            dprintf("WARNING: Single snippet too long, truncating %d to %d\n",
                                   payload_length, (int)sizeof(snippet_buffer)-1);
                            #endif
                            payload_length = sizeof(snippet_buffer) - 1;
                        }

                        memcpy(snippet_buffer, &data[HEADER_SIZE+1], payload_length);
                        snippet_buffer[payload_length] = '\0';
                        have_snippet = true;

                        #ifdef DEBUG
                        dprintf("Single packet snippet: '%s'\n", snippet_buffer);
                        #endif
                        break;
                }
            }
            break;

        case 0x07: // End-code packet
            if (expecting_snippet && data[1] == 0x04) {
                current_end_code = data[3]; // The end code is in the third byte

#ifdef DEBUG
                dprintf("End code captured: %d\n", current_end_code);
#endif
                if (have_trigger && have_snippet) {
                    // Check if we have room for one more snippet
                    if (snippet_collection.snippet_count < 40) {
                        snippet_entry_t new_snippet;
                        strncpy(new_snippet.trigger, trigger_buffer, SNIP_BUFFER_SIZE - 1);
                        new_snippet.trigger[SNIP_BUFFER_SIZE - 1] = '\0';
                        strncpy(new_snippet.snippet, snippet_buffer, 79);
                        new_snippet.snippet[79] = '\0';
                        new_snippet.end_code = current_end_code;

                        add_snippet(new_snippet);

                        #ifdef DEBUG
                        dprintf("Added snippet: trigger='%s', snippet='%s', end_code=%d\n",
                              trigger_buffer, snippet_buffer, current_end_code);
                        dprintf("Total snippets: %d\n", snippet_collection.snippet_count);
                        #endif
                    } else {
                        #ifdef DEBUG
                        dprintf("ERROR: Maximum snippet count reached (50), cannot add more\n");
                        #endif
                    }

                    // Reset for next snippet
                    have_trigger = false;
                    have_snippet = false;
                    memset(trigger_buffer, 0, sizeof(trigger_buffer));
                    memset(snippet_buffer, 0, sizeof(snippet_buffer));
                }
            }
            break;
        case 0x11: // End of transmission
            {
                // Send a response packet with byte one set to 0xFF
                uint8_t response[32] = {0};
                response[0] = 0xFF; // Confirm end of transmission
                response[1] = 0x01; // Success code
                response[2] = snippet_collection.snippet_count; // Send back total snippets count
                response[3] = 0x55; // Magic test number

                raw_hid_send(response, sizeof(response));
            }
            break;

        default:
#ifdef DEBUG
            dprintf("Unhandled packet type\n");
#endif
            // Handle any other packet types if needed
            break;
    }

    return true; // Indicates we've handled the packet and can skip the Oryx handler
}

// The main raw_hid_receive function that QMK calls
void raw_hid_receive(uint8_t *data, uint8_t length) {
    ephi_raw_hid_receive(data, length);

    // If our handler didn't process it, pass to Oryx handler
    // oryx_raw_hid_receive(data, length);
}

//################################################################################################################################
// RGB Matrix
//################################################################################################################################

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();

  // Enable debug mode
  debug_enable = true;
//  debug_matrix = true;
  eeconfig_init_user();

  // Print some debug info about EEPROM and data sizes
  #ifdef DEBUG
  dprintf("EEPROM info: USER_DATA_SIZE=%d, Collection size=%d bytes\n",
          EECONFIG_USER_DATA_SIZE, (int)sizeof(snippets_collection_t));
  dprintf("-----------------------------------\n");
  #endif

  // Load snippets from EEPROM if available
  // if (eeconfig_is_enabled() && eeconfig_is_user_datablock_valid()) {
  //   // Make sure our collection size isn't too large for the defined user data size
  //   if (sizeof(snippets_collection_t) <= EECONFIG_USER_DATA_SIZE) {
  //     // Use the proper QMK function to read user data block
  //     eeconfig_read_user_datablock(&snippet_collection);
  //
  //     // Safety check - ensure the collection count is valid
  //     if (snippet_collection.snippet_count > 50) {
  //       snippet_collection.snippet_count = 0;
  //       #ifdef DEBUG
  //       dprintf("WARNING: Invalid snippet count in EEPROM, resetting to 0\n");
  //       #endif
  //     } else {
  //       #ifdef DEBUG
  //       dprintf("Loaded %d snippets from EEPROM (%d bytes)\n",
  //               snippet_collection.snippet_count, (int)sizeof(snippets_collection_t));
  //       #endif
  //     }
  //   } else {
  //     #ifdef DEBUG
  //     dprintf("ERROR: Snippet collection too large for EEPROM: %d > %d\n",
  //            (int)sizeof(snippets_collection_t), EECONFIG_USER_DATA_SIZE);
  //     #endif
  //     snippet_collection.snippet_count = 0;
  //   }
  // } else {
  //   #ifdef DEBUG
  //   dprintf("No valid snippets found in EEPROM\n");
  //   #endif
  //
  //   // Initialize with empty collection
  //   snippet_collection.snippet_count = 0;
  // }

  // Print startup message
  dprintf("Keyboard initialized. Raw HID logging enabled.\n");
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233}, {74,180,233} },
};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return false; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      rgb_matrix_set_color_all(58, 113, 60);
      break;
    case 6:
      rgb_matrix_set_color_all(58, 113, 60);
      break;
    case 7:
      rgb_matrix_set_color_all(58, 113, 60);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}


//################################################################################################################################
// Tap Dance, I don't really use the feature but I'm leaving this here for future reference
//################################################################################################################################

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[1];

uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void on_dance_0(tap_dance_state_t *state, void *user_data);
void dance_0_finished(tap_dance_state_t *state, void *user_data);
void dance_0_reset(tap_dance_state_t *state, void *user_data);

void on_dance_0(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_ESCAPE);
        tap_code16(KC_ESCAPE);
        tap_code16(KC_ESCAPE);
    }
    if(state->count > 3) {
        tap_code16(KC_ESCAPE);
    }
}

void dance_0_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(KC_ESCAPE); break;
        case DOUBLE_TAP: register_code16(KC_GRAVE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_ESCAPE); register_code16(KC_ESCAPE);
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
        case DOUBLE_TAP: unregister_code16(KC_GRAVE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
    }
    dance_state[0].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
};
