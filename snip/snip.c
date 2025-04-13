#include "snip.h"
#include "snippets.h"
#include <string.h>

//#define DEBUG

static snip_buffer_t key_buffer = { .head = 0, .count = 0 };

static char buffer_string[SNIP_BUFFER_SIZE + 1]; // +1 for null terminator

static void buffer_add_char(char c) {
    // Only store printable characters
    if (c == 0) {
        return;
    }

    uint8_t insert_pos = key_buffer.head;
    key_buffer.buffer[insert_pos] = c;
    key_buffer.head = (key_buffer.head + 1) % SNIP_BUFFER_SIZE;

    if (key_buffer.count < SNIP_BUFFER_SIZE) {
        key_buffer.count++;
    }
}


// Check if shift is currently active
static bool is_shifted(void) {
    return (get_mods() & MOD_MASK_SHIFT) || (get_oneshot_mods() & MOD_MASK_SHIFT);
}

// Convert keycode to a character based on shift state
static char keycode_to_char(uint16_t keycode, bool shifted) {
    // Handle special key types - extract the base keycode from mod-tap and layer-tap keys
    if (IS_QK_MOD_TAP(keycode)) {
        keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_LAYER_TAP(keycode)) {
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    }

    switch (keycode) {
        // Letters
        case KC_A: return shifted ? 'A' : 'a';
        case KC_B: return shifted ? 'B' : 'b';
        case KC_C: return shifted ? 'C' : 'c';
        case KC_D: return shifted ? 'D' : 'd';
        case KC_E: return shifted ? 'E' : 'e';
        case KC_F: return shifted ? 'F' : 'f';
        case KC_G: return shifted ? 'G' : 'g';
        case KC_H: return shifted ? 'H' : 'h';
        case KC_I: return shifted ? 'I' : 'i';
        case KC_J: return shifted ? 'J' : 'j';
        case KC_K: return shifted ? 'K' : 'k';
        case KC_L: return shifted ? 'L' : 'l';
        case KC_M: return shifted ? 'M' : 'm';
        case KC_N: return shifted ? 'N' : 'n';
        case KC_O: return shifted ? 'O' : 'o';
        case KC_P: return shifted ? 'P' : 'p';
        case KC_Q: return shifted ? 'Q' : 'q';
        case KC_R: return shifted ? 'R' : 'r';
        case KC_S: return shifted ? 'S' : 's';
        case KC_T: return shifted ? 'T' : 't';
        case KC_U: return shifted ? 'U' : 'u';
        case KC_V: return shifted ? 'V' : 'v';
        case KC_W: return shifted ? 'W' : 'w';
        case KC_X: return shifted ? 'X' : 'x';
        case KC_Y: return shifted ? 'Y' : 'y';
        case KC_Z: return shifted ? 'Z' : 'z';

        // Numbers
        case KC_1: return shifted ? '!' : '1';
        case KC_2: return shifted ? '@' : '2';
        case KC_3: return shifted ? '#' : '3';
        case KC_4: return shifted ? '$' : '4';
        case KC_5: return shifted ? '%' : '5';
        case KC_6: return shifted ? '^' : '6';
        case KC_7: return shifted ? '&' : '7';
        case KC_8: return shifted ? '*' : '8';
        case KC_9: return shifted ? '(' : '9';
        case KC_0: return shifted ? ')' : '0';

        // Punctuation and symbols
        case KC_MINS: return shifted ? '_' : '-';
        case KC_EQL: return shifted ? '+' : '=';
        case KC_LBRC: return shifted ? '{' : '[';
        case KC_RBRC: return shifted ? '}' : ']';
        case KC_BSLS: return shifted ? '|' : '\\';
        case KC_SCLN: return shifted ? ':' : ';';
        case KC_QUOT: return shifted ? '"' : '\'';
        case KC_GRV: return shifted ? '~' : '`';
        case KC_COMM: return shifted ? '<' : ',';
        case KC_DOT: return shifted ? '>' : '.';
        case KC_SLSH: return shifted ? '?' : '/';

        // Space and special keys
        case KC_SPC: return ' ';
        case KC_TAB: return '\t';
        case KC_ENT: return '\n';

        // Default - key doesn't map to a printable ASCII character
        default: return 0;
    }
}

/**
 * @brief Reads the contents of the buffer chronologically from oldest to newest
 * (from the head)
 * @note Returns a string that we can match against to see if we should print a snippet
 */
static char* read_buffer(void) {
#ifdef DEBUG
        SEND_STRING("Reading Buffer");
#endif
  if (key_buffer.count == 0) {
      buffer_string[0] = '\0';
      return buffer_string;
#ifdef DEBUG
        SEND_STRING("Buffer Empty");
#endif
  }

  uint8_t start = 0;
  if (key_buffer.count == SNIP_BUFFER_SIZE) {
      start = key_buffer.head;
  } else {
      start = (key_buffer.head + SNIP_BUFFER_SIZE - key_buffer.count) % SNIP_BUFFER_SIZE;
  }

  for (uint8_t i = 0; i < key_buffer.count; i++) {
      uint8_t pos = (start + i) % SNIP_BUFFER_SIZE;
      buffer_string[i] = key_buffer.buffer[pos];
  }

  buffer_string[key_buffer.count] = '\0';

#ifdef DEBUG
    SEND_STRING("Buffer Read");
#endif
  return buffer_string;
}

/**
 * @brief Searches for a match from the full buffer contents, then from
 * shorter and shorter substrings of the buffer.
 * @param buffer The string buffer to match against
 * @return A snippet_match_t with the matched snippet and trigger length, or NULL snippet_text if no match
 */
static snippet_match_t match_snippet(const char* buffer) {
#ifdef DEBUG
    SEND_STRING("Matching Snippet");
#endif

    snippet_match_t result = {NULL, 0}; // Initialize with no match
    size_t buffer_len = strlen(buffer);

    if (buffer_len == 0) {
        return result; // Nothing to match
#ifdef DEBUG
        SEND_STRING("Buffer Empty");
#endif
    }

    // Start with the longest possible match (full buffer, limited to buffer size)
    // Then try progressively shorter matches from the end
    for (size_t substr_len = buffer_len; substr_len > 0; substr_len--) {
        // Calculate the starting position for this substring
        size_t start_pos = buffer_len - substr_len;
        const char* substr = buffer + start_pos;

        // Check the dynamic snippet collection
        for (uint8_t i = 0; i < snippet_collection.snippet_count; i++) {
            if (strcmp(substr, snippet_collection.snippet_arr[i].trigger) == 0) {
                result.snippet_text = snippet_collection.snippet_arr[i].snippet;
                result.trigger_len = substr_len;
                result.end_code = snippet_collection.snippet_arr[i].end_code;
#ifdef DEBUG
                SEND_STRING("Match Found in Collection");
#endif
                return result;
            }
        }
    }

    // No match found
#ifdef DEBUG
    SEND_STRING("No Match Found");
#endif
    return result;
}

/** @brief Customizable function to determine if the keycode should be recorded
 * @note Currently used to filter out characters not in the keycode map
*/
bool snippet_tool_should_record(uint16_t keycode) {
    return true;
}


/**
* @brief May be the only way to match a snippet from a combo, still testing.
*/
void force_match_attempt(void) {
    char *buffer = read_buffer();
    snippet_match_t match = match_snippet(buffer);

    if (match.snippet_text != NULL) {
        for (size_t i = 0; i < match.trigger_len; i++) {
            tap_code(KC_BSPC);
        }
        SEND_STRING(match.snippet_text);
        tap_code16(match.end_code);
        key_buffer.count = 0;
    }
}

/**
* @brief Call this from process_record_user to do work on keypresses
* @note For every keypress, if the keycode is our activation keycode, then flush
* the buffer and SEND_STRING the correct snippet.
* If the keycode is not our activation keycode and is in our table, then add it
* to the ring buffer.
*/
bool process_snippet_tool(uint16_t keycode, keyrecord_t* record, uint16_t trigger_key) {
    if (keycode == trigger_key && record->event.pressed) {
#ifdef DEBUG
        SEND_STRING("Trigger Key Recognized");
#endif

        char *buffer = read_buffer();
        snippet_match_t match = match_snippet(buffer);

        if (match.snippet_text != NULL) {
#ifdef DEBUG
            SEND_STRING("Match Not NULL");
#endif

            // Backspace the trigger characters
            for (size_t i = 0; i < match.trigger_len; i++) {
                tap_code(KC_BSPC);
            }

            SEND_STRING(match.snippet_text);
            tap_code16(match.end_code);

            key_buffer.count = 0;

            return true;
        }
        return false;
    } else {
        if (record->event.pressed && snippet_tool_should_record(keycode)) {
#ifdef DEBUG
            SEND_STRING("Recording");
#endif
            char c = keycode_to_char(keycode, is_shifted());

            if (c != 0) {
#ifdef DEBUG
                SEND_STRING("Adding Char");
#endif
                buffer_add_char(c);
            }
        }
        return false;
    }
}

/**
* @brief Call this from matrix_scan_user to do work every tick
* @note Currently unused but may be required for checking shift states / modal sampling
*/
void snippet_tool_task(void) {

}
