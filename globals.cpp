#include "globals.h"
#include <string>
#include <sstream>

bool is_email_valid(std::string const& address) {
    size_t at_index = address.find_first_of('@', 0);
    return at_index != std::string::npos
        && address.find_first_of('.', at_index) != std::string::npos;
}

bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

std::vector<std::string> split(const std::string &text, char sep) {
  std::vector<std::string> tokens;
  std::size_t start = 0, end = 0;
  while ((end = text.find(sep, start)) != std::string::npos) {
    tokens.push_back(text.substr(start, end - start));
    start = end + 1;
  }
  tokens.push_back(text.substr(start));
  return tokens;
}
