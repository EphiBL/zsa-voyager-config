#include "snippets.h"

// Example snippets here
//
/**
* const snippet entry_t snippets[] = {
  * // Single line snippets
  * {"addr", "your.email@example.com"},
  * // Multi-line snippets
  * {"sig", "Best regards,\nYour Name"},
  * // Multi-line string snippets
  * {"lorem", "Lorem ipsum dolor sit amet,"
  * " consectetur adipiscing elit."},
* };
*/

/**
 * On some systems you may have to swap @ to \" and vice versa symbols
    */
const snippet_entry_t snippets[] = {
    {"email", "rj_aguirre94\"outlook.com"},
    {"st", "std::"},
    {"con", "constexpr"},
    {"cout", "std::cout << "},
    {"cin", "std::cin >> "},
    {"endl", "std::endl"},
    {"vec", "std::vector<"},
    {"str", "std::string"},
    {"for", "for (int i = 0; i < ; i++) {"},
    {"arr", "std::array<"},
};

const uint8_t NUM_SNIPPETS = sizeof(snippets) / sizeof(snippets[0]);
