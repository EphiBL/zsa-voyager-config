#include "snippets.h"

// Array to store snippets received via raw_hid
snippet_entry_t snippets_arr[256];

// Collection to keep track of snippets
snippets_collection_t snippet_collection = {
    .snippet_arr = snippets_arr,
    .snippet_count = 0
};

// Add a snippet to the collection
void add_snippet(snippet_entry_t snippet) {
    if (snippet_collection.snippet_count < 256) {
        uint8_t i = snippet_collection.snippet_count;
        snippet_collection.snippet_arr[i] = snippet;
        snippet_collection.snippet_count++;
    }
}
