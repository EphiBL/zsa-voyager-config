#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

// Ring buffer configuration
#define SNIP_BUFFER_SIZE 5 // Size of ring buffer (5-10 keypresses)

// Ring buffer structure definition
typedef struct {
    char    buffer[SNIP_BUFFER_SIZE];
    uint8_t head;
    uint8_t count;
} snip_buffer_t;

typedef struct {
    const char* snippet_text;
    size_t      trigger_len;
} snippet_match_t;

typedef struct {
    const char* trigger;
    const char* snippet;
} snippet_entry_t;

bool process_snippet_tool(uint16_t keycode, keyrecord_t* record, uint16_t trigger_key);

void force_match_attempt(void);
void snippet_tool_task(void);

// Customization points (optional callbacks)
bool snippet_tool_should_record(uint16_t keycode);

#ifdef __cplusplus
}
#endif
