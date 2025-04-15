#include "snippet_data.h"
#include "snip.h"

// This entire file will be overwritten by the TS frontend
// Default empty state
static const snippet_entry_t default_entries[] = {
    {"example", "This is an example snippet", 0}
};

const snippet_collection_t snippet_collection = {
    .count = 1,
    .entries = {
        {"example", "This is an example snippet", 0}
    }
};
