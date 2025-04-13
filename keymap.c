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

enum tap_dance_codes {
  DANCE_0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Main Keyboard
  [0] = LAYOUT_voyager(
    KC_ESCAPE,      SCRNSHT,     KC_DEL,      KC_PC_COPY,     KC_PC_PASTE,      TG(4),                                          TG(6),     NV_SAVE,          KC_MINUS,          KC_EQL,   KC_SNIP,     KC_MS_BTN1,
    KC_LEFT_GUI,    KC_Q,           KC_X,           KC_M,       KC_W,         KC_V,                                           KC_J,           KC_F,           KC_O,           KC_U,          KC_SCLN,     CW_TOGG,
    KC_TAB,         LT(2, KC_N),MT(MOD_LALT,KC_R),MT(MOD_LCTL, KC_T), MT(MOD_LSFT,KC_S),  KC_G,                                   KC_Y,           MT(MOD_LSFT,KC_H),MT(MOD_LCTL,KC_A),MT(MOD_LALT,KC_E),      KC_I,  KC_BSPC,
    KC_LEFT_SHIFT,  LT(3,KC_B),  KC_L,               KC_D,        KC_C,           KC_Z,                                           KC_K,           KC_P,           KC_COMMA,    KC_DOT,      KC_SLASH, KC_ENTER,
                                                    OSL(1),       OSM(MOD_LSFT),                                     MT(MOD_MEH, KC_ENTER), LT(5,KC_SPACE)
  ),

  // Symbols
  [1] = LAYOUT_voyager(
    KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                          KC_AUDIO_MUTE,          KC_AUDIO_VOL_UP,          KC_AUDIO_VOL_DOWN,          KC_F9,          KC_F10,         KC_F11,
    KC_TRANSPARENT, KC_GRAVE,       KC_LABK,        KC_RABK,        KC_AT,          KC_DOT,                                         KC_AMPR,        KC_QUOTE,       KC_LBRC,        KC_RBRC,        KC_PERC,        KC_F12,
    KC_LEFT_CTRL, KC_EXLM,        KC_MINUS,       KC_PLUS,        KC_EQUAL,       KC_NONUS_HASH,                                    KC_CIRC,        KC_COLN,        KC_LCBR,        KC_RCBR,        KC_QUES,        KC_BSPC,
    KC_HASH,        LSFT(KC_NUBS),  KC_SLASH,       KC_ASTR,        KC_NUBS,        KC_DLR,                                         LSFT(KC_NONUS_HASH),KC_UNDS,        KC_LPRN,        KC_RPRN,        KC_DQUO,        KC_ENTER,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT,          KC_SPACE
                                                    // KC_HASH IS GBP!!!
  ),

  // Numbers
  [2] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_CALCULATOR, KC_COMMA,       KC_SLASH,       KC_ASTR,        KC_CALC,         TO(4),
    KC_TRANSPARENT, KC_TRANSPARENT, KC_7,           KC_8,           KC_9,           KC_PERC,                                        KC_TRANSPARENT, KC_7,           KC_8,           KC_9,           KC_MINUS,       KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_4,           KC_5,           KC_6,           KC_CIRC,                                        KC_DOT,         KC_4,           KC_5,           KC_6,           KC_PLUS,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_1,           KC_2,           KC_3,           KC_DOT,                                         KC_DOT,         KC_1,           KC_2,           KC_3,           KC_ENTER,       KC_TRANSPARENT,
                                                                     KC_0,       KC_SPACE,                               KC_ENTER,           KC_0
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
    KC_TRANSPARENT, KC_TRANSPARENT, ST_MACRO_2, ERR_NIL, KC_TRANSPARENT, KC_TRANSPARENT,                                     KC_WWW_HOME,    KC_HOME,        KC_UP,          KC_END,         ST_MACRO_0,     KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LEFT_GUI,    KC_LEFT_ALT,    KC_LEFT_CTRL,   KC_LEFT_SHIFT,  KC_TRANSPARENT,                                 KC_WWW_BACK,    KC_LEFT,        KC_DOWN,        KC_RIGHT,       ST_MACRO_1,     KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, FMT_ERR, PR_ERR, KC_TRANSPARENT,                                 KC_WWW_FORWARD, KC_PAGE_DOWN,        KC_PAGE_UP,     KC_TRANSPARENT, KC_APP, KC_TRANSPARENT,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),

  // Mouse layer
  [6] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 TG(6), KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP, LALT(KC_F4),    KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, ST_MACRO_2, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                     KC_WWW_HOME,    KC_MS_BTN3,        KC_MS_UP,          KC_MS_BTN4,         KC_MS_WH_UP,     TG(6),
    KC_TRANSPARENT, KC_LEFT_GUI,    KC_LEFT_ALT,    KC_LEFT_CTRL,   KC_LEFT_SHIFT,  KC_TRANSPARENT,                                 KC_WWW_BACK,    KC_MS_LEFT,        KC_MS_DOWN,        KC_MS_RIGHT,       KC_MS_WH_DOWN,     KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TG(6),          KC_MS_BTN2, KC_TRANSPARENT,                                     KC_WWW_FORWARD, CLICK_END,        KC_MS_BTN1,     CLICK_END,           QUICK_CLICK,                TG(6),
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_MS_BTN2, KC_MS_BTN1
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
};

const uint16_t PROGMEM sw_steno[] = {KC_PLUS, KC_SLASH, COMBO_END};
const uint16_t PROGMEM snip[] = {MT(MOD_LSFT,KC_H), MT(MOD_LCTL,KC_A), COMBO_END};

combo_t key_combos[] = {
    [SW_STENO] = COMBO_ACTION(sw_steno),
    [SNIP] = COMBO_ACTION(snip),
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
  switch(combo_index) {
    // case SW_STENO:
    // if (pressed) {
    //   layer_invert(7);
    // }
    // break;
       case SNIP:
       if (pressed)
                force_match_attempt();
       break;
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

char snippet_string[256];

// Custom function to handle your raw HID packets
bool ephi_raw_hid_receive(uint8_t *data, uint8_t length) {
    // Log the raw HID packet
#ifdef DEBUG
    dprintf("Ephi parser checking HID packet. Length: %d\n", length);
    if (data[0] == 0x01) {
        dprintf("Command packet received\n");
    } else if (data[0] == 0x05) {
        dprintf("Trigger packet received\n");
            if (data[1] != 0x04)
                dprintf("Trigger packet with SEQ != SINGLE\n");
    } else if (data[0] == 0x06) {
        dprintf("Snippet packet received\n");
        switch(data[1]) {
            case 0x01:
                dprintf("SEQ: Start\n");
                for (uint8_t i = 0; i < length; i++) {
                    dprintf("0x%02X ", data[i]);
                    if ((i + 1) % 8 == 0) {
                        dprintf("\n");
                    }
                }
                    break;
            case 0x02:
                dprintf("SEQ: Cont\n");
                for (uint8_t i = 0; i < length; i++) {
                    dprintf("0x%02X ", data[i]);
                    if ((i + 1) % 8 == 0) {
                        dprintf("\n");
                    }
                }
                    break;
            case 0x03:
                dprintf("SEQ: End\n");
                    break;
            case 0x04:
                dprintf("SEQ: SINGLE\n");
                for (uint8_t i = 0; i < length; i++) {
                    dprintf("0x%02X ", data[i]);
                    if ((i + 1) % 8 == 0) {
                        dprintf("\n");
                        snippet_string[i+1] = '\0';
                    }
                    snippet_string[i] = (char)data[i];
                }
                dprintf("Snippet: %s\n", snippet_string);
                    break;
        }
    } else if (data[0] == 0x07) {
        dprintf("End-code packet received\n");
            if (data[1] != 0x04)
                dprintf("Trigger packet with SEQ != SINGLE\n");
    }
#endif
    // Handle your custom packet here
    // Example: data[1] could be a subcommand
    // switch(data[0]) {
    //     case 0x01:
    //         // Process snippet tool specific command here
    //         break;
    //     case 0x02:
    //         // Process another command
    //         break;
    //     default:
    //         break;
    // }

    // // Optional: Send a response back to the host
    // uint8_t response[RAW_EPSIZE] = {0};
    // response[0] = data[1]; // Echo the subcommand
    // response[1] = 0x01;  // Status code: success
    // raw_hid_send(response, sizeof(response));

    // Return true to indicate we've handled this packet
    return true;

    // Return false to indicate this packet should be processed by the Oryx handler
    return false;
}

// The main raw_hid_receive function that QMK calls
void raw_hid_receive(uint8_t *data, uint8_t length) {
    // First, try to handle the packet with our custom handler
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
