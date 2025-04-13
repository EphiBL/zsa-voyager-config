#include "snippets.h"
#include <string.h>

#define MAX_SNIPPETS 50      // Maximum number of snippets we can store
#define MAX_SNIPPET_LEN 100  // Maximum length of snippet strings

// Static storage for snippet data
static char trigger_storage[MAX_SNIPPETS][SNIP_BUFFER_SIZE];  // Using SNIP_BUFFER_SIZE (7) from snip.h
static char snippet_storage[MAX_SNIPPETS][MAX_SNIPPET_LEN];
static uint8_t end_code_storage[MAX_SNIPPETS];

// Array of pointers to the stored snippets
static snippet_entry_t snippets_arr[MAX_SNIPPETS];

// Collection to keep track of snippets
snippets_collection_t snippet_collection = {
    .snippet_arr = snippets_arr,
    .snippet_count = 0
};

// Add a snippet to the collection
void add_snippet(snippet_entry_t snippet) {
    if (snippet_collection.snippet_count < MAX_SNIPPETS) {
        uint8_t i = snippet_collection.snippet_count;
        
        // Copy the trigger and snippet strings to our static storage
        strncpy(trigger_storage[i], snippet.trigger, SNIP_BUFFER_SIZE - 1);
        trigger_storage[i][SNIP_BUFFER_SIZE - 1] = '\0';  // Ensure null termination
        
        strncpy(snippet_storage[i], snippet.snippet, MAX_SNIPPET_LEN - 1);
        snippet_storage[i][MAX_SNIPPET_LEN - 1] = '\0';  // Ensure null termination
        
        // Store the end code
        end_code_storage[i] = snippet.end_code;
        
        // Update the pointer array
        snippets_arr[i].trigger = trigger_storage[i];
        snippets_arr[i].snippet = snippet_storage[i];
        snippets_arr[i].end_code = end_code_storage[i];
        
        // Increment the counter
        snippet_collection.snippet_count++;
    }
}
