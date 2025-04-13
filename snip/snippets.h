#pragma once

#include "snip.h"

// Function to add a snippet to the dynamic collection
void add_snippet(snippet_entry_t snippet);

// Expose the snippet collection
extern snippets_collection_t snippet_collection;
