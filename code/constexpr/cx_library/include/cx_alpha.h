namespace cx {
namespace alpha {

constexpr bool IsNumber(char c) {
  return (c >= '0' && c <= '9');
}

constexpr bool IsLetter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

constexpr bool IsWhitespace(char c) {
  return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

}  // namespace alpha
}  // namespace cx
