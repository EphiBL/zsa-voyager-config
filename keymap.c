// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "version.h"
#include "i18n.h"
#include "features/achordion.h"
#include "keymap_steno.h"
#define MOON_LED_LEVEL LED_LEVEL
#define REP_SFT LT(1, QK_REP)
#define AREP_SYM MT(MOD_LSFT, QK_AREP)
#define REP_MEH MT(MOD_MEH, QK_REP)
// #define RGB_WHITE 255, 255, 255
// #define RGB_SOFT_DARK_GREEN 0, 100, 50 // Adjust these values to get the exact shade you want
#define BUFFER_SIZE 10

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
  BR,
  SM_FILL,

  MG_ION,
  MG_NG,
  MG_ENT,
  MG_UE,
  MG_TION,
};

enum tap_dance_codes {
  DANCE_0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =

  // Main Keyboard
  [0] = LAYOUT_voyager(
    KC_ESCAPE,      SCRNSHT,     KC_DEL,      KC_PC_COPY,     KC_PC_PASTE,      TG(4),                                          KC_UNDO,     LCTL(KC_Y),          SM_FILL,          TG(7),   SCRNSHT,     KC_ENTER,
    KC_LEFT_GUI,    KC_Q,           KC_X,           KC_M,           KC_W,         KC_V,                                           KC_J,           KC_F,           KC_O,           KC_U,          KC_SCLN,     TG(6),
    KC_TAB,         LT(2, KC_N),MT(MOD_LALT,KC_R),MT(MOD_LCTL, KC_T), MT(MOD_LSFT,KC_S),  KC_G,                                   KC_Y,           MT(MOD_LSFT,KC_H),MT(MOD_LCTL,KC_A),MT(MOD_LALT,KC_E),      KC_I,  KC_BSPC,
    KC_LEFT_SHIFT,  LT(3,KC_B),  KC_L,               KC_D,        KC_C,           KC_Z,                                           KC_K,           KC_P,           KC_COMMA,    KC_DOT,      KC_SLASH, CW_TOGG,
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
    RGB_TOG,        TOGGLE_LAYER_COLOR,RGB_MODE_FORWARD,RGB_SLD,        RGB_VAD,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F10, KC_F11, KC_F12, KC_F13, QK_BOOT,
    KC_TRANSPARENT, KC_MY_COMPUTER, KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,  KC_TRANSPARENT,                                 KC_PAGE_UP,     KC_F7,        KC_F8,          KC_F9,         KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_LEFT_ALT,KC_LEFT_CTRL,  KC_LEFT_SHIFT,KC_TRANSPARENT,                                 KC_PGDN,        KC_F4,        KC_F5,        KC_F6,       KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, HSV_0_255_255,  HSV_74_255_255, HSV_169_255_255,                                KC_TRANSPARENT, KC_F1, KC_F2,   KC_F3, KC_TRANSPARENT, KC_TRANSPARENT,
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
    KC_TRANSPARENT, KC_TRANSPARENT, ST_MACRO_2, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_WWW_HOME,    KC_HOME,        KC_UP,          KC_END,         ST_MACRO_0,     KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LEFT_GUI,    KC_LEFT_ALT,    KC_LEFT_CTRL,   KC_LEFT_SHIFT,  KC_TRANSPARENT,                                 KC_WWW_BACK,    KC_LEFT,        KC_DOWN,        KC_RIGHT,       ST_MACRO_1,     KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_WWW_FORWARD, KC_PAGE_DOWN,        KC_PAGE_UP,     KC_TRANSPARENT, KC_APP, KC_TRANSPARENT,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),

  // Mouse layer
  [6] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP, LALT(KC_F4),    KC_TRANSPARENT, KC_TRANSPARENT,
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

  // Old Graphite
  // [7] = LAYOUT_voyager(
  //   KC_ESCAPE,      SCRNSHT,     KC_DEL,      KC_PC_COPY,     KC_PC_PASTE,      TG(4),                                          KC_UNDO,     LCTL(KC_Y),          SM_FILL,          TG(7),   SCRNSHT,     KC_ENTER,
  //   KC_LEFT_GUI,    KC_B,           KC_L,           KC_D,           KC_W,         KC_Z,                                           KC_SCLN,           KC_F,           KC_O,           KC_U,          KC_J,     TG(6),
  //   KC_TAB,         LT(2, KC_N),MT(MOD_LALT,KC_R),MT(MOD_LCTL, KC_T), MT(MOD_LSFT,KC_S),  KC_G,                                   KC_Y,           MT(MOD_LSFT,KC_H),MT(MOD_LCTL,KC_A),MT(MOD_LALT,KC_E),      KC_I,  KC_BSPC,
  //   KC_LEFT_SHIFT,  LT(3,KC_Q),  KC_X,               KC_M,        KC_C,           KC_V,                                           KC_K,           KC_P,           KC_COMMA,    KC_DOT,      KC_SLASH, CW_TOGG,
  //                                                   OSL(1),       OSM(MOD_LSFT),                                     MT(MOD_MEH, KC_ENTER), LT(5,KC_SPACE)
  // ),

  // Full QWERTY
  //   [7] = LAYOUT_voyager(
  //   KC_ESCAPE,      SCRNSHT,     KC_DEL,      KC_PC_COPY,     KC_PC_PASTE,      TG(4),                                          KC_UNDO,     LCTL(KC_Y),          KC_DEL,          TG(7),   SCRNSHT,     TG(7),
  //   KC_LEFT_GUI,    KC_Q,           KC_W,           KC_E,           KC_R,         KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,       KC_P,     TG(6),
  //   KC_TAB,         LT(2, KC_A),MT(MOD_LALT,KC_S),MT(MOD_LCTL, KC_D), MT(MOD_LSFT,KC_F),  KC_G,                                   KC_H,           MT(MOD_LSFT,KC_J),MT(MOD_LCTL,KC_K),MT(MOD_LALT,KC_L),      KC_SCLN,  KC_BSPC,
  //   KC_LEFT_SHIFT,  LT(3,KC_Z),  KC_X,               KC_C,        KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,    KC_DOT,      KC_SLASH, CW_TOGG,
  //                                                   OSL(1),       OSM(MOD_LSFT),                                     MT(MOD_MEH, KC_ENTER), LT(5, KC_SPACE)
};

const char PROGMEM simple_code_to_char[128] = {
   [KC_A] = 'a', [KC_B] = 'b', [KC_C] = 'c', [KC_D] = 'd',
   [KC_E] = 'e', [KC_F] = 'f', [KC_G] = 'g', [KC_H] = 'h',
   [KC_I] = 'i', [KC_J] = 'j', [KC_K] = 'k', [KC_L] = 'l',
   [KC_M] = 'm', [KC_N] = 'n', [KC_O] = 'o', [KC_P] = 'p',
   [KC_Q] = 'q', [KC_R] = 'r', [KC_S] = 's', [KC_T] = 't',
   [KC_U] = 'u', [KC_V] = 'v', [KC_W] = 'w', [KC_X] = 'x',
   [KC_Y] = 'y', [KC_Z] = 'z',
   [KC_1] = '1', [KC_2] = '2', [KC_3] = '3', [KC_4] = '4',
   [KC_5] = '5', [KC_6] = '6', [KC_7] = '7', [KC_8] = '8',
   [KC_9] = '9', [KC_0] = '0',
   [KC_NUBS] = '\\', [KC_SCLN] = ';',
   [KC_QUOTE] = '\'', [KC_GRAVE] = '`',
   [KC_COMMA] = ',', [KC_DOT] = '.', [KC_SLASH] = '/',
   [KC_SPACE] = ' ', [KC_ENTER] = '\n',
};

static uint16_t keypress_buffer[BUFFER_SIZE];
static uint8_t buffer_index = 0;
static char char_buffer[BUFFER_SIZE];
static uint8_t char_buffer_index;

enum combo_events {
  KC_BR,
  SW_STENO,
  KC_BR2,
  // SM_FILL,
  // SM_FILL_2,
};

const uint16_t PROGMEM sw_steno[] = {KC_DOT, KC_SLASH, COMBO_END};
const uint16_t PROGMEM br_combo[] = {KC_B, KC_L, COMBO_END};
const uint16_t PROGMEM br2_combo[] = {LT(2, KC_N),MT(MOD_LALT,KC_R), COMBO_END};
// const uint16_t PROGMEM sm_fill[] = {KC_P, KC_COMMA, COMBO_END};
// const uint16_t PROGMEM sm_fill_2[] = {KC_M, KC_C, COMBO_END};

combo_t key_combos[] = {
    [SW_STENO] = COMBO_ACTION(sw_steno),
    [KC_BR] = COMBO_ACTION(br_combo),
    [KC_BR2] = COMBO_ACTION(br2_combo),
    // [SM_FILL] = COMBO_ACTION(sm_fill),
    // [SM_FILL_2] = COMBO_ACTION(sm_fill_2),
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
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

char* get_last_word(void) {
   static char word[BUFFER_SIZE + 1] = {0};
   int word_length = 0;
   uint8_t index = char_buffer_index;

   while (word_length < BUFFER_SIZE) {
       index = (index - 1 + BUFFER_SIZE) % BUFFER_SIZE;
       char c = char_buffer[index];

       if (c == ' ' || c == '\n' || c == '.' || c == '/') {
           break;
       }

       if (c != 0) {
           word[word_length++] = c;
       }
   }

   // Reverse the word since we read it backwards
   for (int i = 0; i < word_length / 2; i++) {
       char temp = word[i];
       word[i] = word[word_length - 1 - i];
       word[word_length - 1 - i] = temp;
   }

   word[word_length] = '\0';
   return word;
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

void send_buffer_as_string(void) {
  //  char_buffer_index = (char_buffer_index - 1 + BUFFER_SIZE) % BUFFER_SIZE;
  //  char_buffer[char_buffer_index] = 0;
  //  char_buffer[(char_buffer_index + 1) % BUFFER_SIZE] = 0;

   char* word = get_last_word();
   int word_len = strlen(word);

   for (int i = 0; i < word_len; i++) {
      tap_code(KC_BSPC);
   }

  if (strcmp(word, "if") == 0) {
    SEND_STRING("if () {\n    \n}" SS_TAP(X_UP) SS_TAP(X_UP) SS_TAP(X_RIGHT) SS_TAP(X_RIGHT) SS_TAP(X_RIGHT));
  } else if (strcmp(word, "else") == 0) {
    SEND_STRING("else {\n    \n}" SS_TAP(X_UP));
  }

  for (int i = 0; i < BUFFER_SIZE; i++) {
    char_buffer[i] = 0;
  }

  char_buffer_index = 0;
}

// void send_buffer_as_string(void) {
//     char_buffer_index = (char_buffer_index - 1 + BUFFER_SIZE) % BUFFER_SIZE;
//     char_buffer[char_buffer_index] = 0;
//     char temp_buffer[BUFFER_SIZE + 1] = {0};
//     // char buffer_copy[BUFFER_SIZE];
//     // memcpy(buffer_copy, char_buffer, BUFFER_SIZE);
//     // uint8_t copy_index = char_buffer_index;
//     uint8_t actual_size = 0;

//     // Start from oldest entry, go to newest
//     for (int i = 0; i < BUFFER_SIZE; i++) {
//         int idx = (char_buffer_index - BUFFER_SIZE + i + BUFFER_SIZE) % BUFFER_SIZE;
//         if (char_buffer[idx] != 0) {
//             temp_buffer[actual_size++] = char_buffer[idx];
//         }
//     }
//     // temp_buffer[actual_size] = '\0';
//     SEND_STRING(temp_buffer);
// }

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case SW_STENO:
    if (pressed) {
      layer_invert(7);
    }
    break;

    case KC_BR:
    if (pressed) {
      SEND_STRING("br");
    }
    break;

    case KC_BR2:
    if (pressed) {
      SEND_STRING("br");
    }
    break;

    // case SM_FILL:
    // if (pressed) {
    //   send_buffer_as_string();
    // }
    // break;

    // case SM_FILL_2:
    // if (pressed) {
    //   send_buffer_as_string();
    // }
    // break;

  }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_achordion(keycode, record)) { return false; }

  // if (record->event.pressed) {
  //   keypress_buffer[buffer_index] = keycode;
  //   buffer_index = (buffer_index + 1) % BUFFER_SIZE;

  //   char c = pgm_read_byte(&simple_code_to_char[keycode & 0xFF]);
  //   if (c != 0) {
  //     char_buffer[char_buffer_index] = c;
  //     char_buffer_index = (char_buffer_index + 1) % BUFFER_SIZE;
  //   }
  // }

  if (record->event.pressed) {
    keypress_buffer[buffer_index] = keycode;
    buffer_index = (buffer_index + 1) % BUFFER_SIZE;

    char c = pgm_read_byte(&simple_code_to_char[keycode & 0xFF]);
    if (c != 0) {
      char_buffer[char_buffer_index] = c;
      char_buffer_index = (char_buffer_index + 1) % BUFFER_SIZE;
    }
  }

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

    case SM_FILL:
    if (record->event.pressed) {
      send_buffer_as_string();
    }
    break;

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

    // case BR:
    // if (record->event.pressed) {
    //   // SEND_STRING("br");
    //   tap_code(KC_B);
    //   tap_code(KC_R);
    // }

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

  // if (record->event.pressed) {
  //   keypress_buffer[buffer_index] = keycode;
  //   buffer_index = (buffer_index + 1) % BUFFER_SIZE;

  //   char c = pgm_read_byte(&simple_code_to_char[keycode & 0xFF]);
  //   if (c != 0) {
  //     char_buffer[char_buffer_index] = c;
  //     char_buffer_index = (char_buffer_index + 1) % BUFFER_SIZE;
  //   }
  // }

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
