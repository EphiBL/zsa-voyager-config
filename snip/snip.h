#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SNIP_BUFFER_SIZE 7 // Size of ring buffer (5-10 keypresses)

typedef struct {
    char    buffer[SNIP_BUFFER_SIZE];
    uint8_t head;
    uint8_t count;
} snip_buffer_t;

typedef struct {
    const char* snippet_text;
    size_t      trigger_len;
    uint8_t     end_code;
} snippet_match_t;

typedef struct {
    char    trigger[SNIP_BUFFER_SIZE];
    char    snippet[80]; // Using fixed size for flat storage
    uint8_t end_code;
} snippet_entry_t;

// This is the typedef
typedef struct {
    snippet_entry_t snippet_arr[40]; // Hard-coding max size for flat storage
    uint8_t         snippet_count;
} snippets_collection_t;

// This is the actual collection of the type
extern snippets_collection_t snippet_collection;

bool process_snippet_tool(uint16_t keycode, keyrecord_t* record, uint16_t trigger_key);

void force_match_attempt(void);
void snippet_tool_task(void);
void add_snippet(snippet_entry_t snippet);

// Customization points (optional callbacks)
bool snippet_tool_should_record(uint16_t keycode);

#ifdef __cplusplus
}
#endif
