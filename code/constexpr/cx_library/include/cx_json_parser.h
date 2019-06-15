#include "cx_json_value.h"

namespace cx {

namespace json {

constexpr double StringToNumber(const cx::StaticString& str) {
  return 0;
}

template <std::size_t MaxDepth>
struct JsonParser {
  static constexpr JsonValue<MaxDepth> Parse(const cx::StaticString& str) {
  }
};

template <>
struct JsonParser<0> {

};

enum class ParserState { kBoolean, kNumber, kString, kNull };

template <std::size_t MaxDepth>
constexpr cx::Pair<std::size_t, JsonValue<MaxDepth>> ParseUnknown(std::size_t init_pos,
                                                                  const cx::StaticString& str) {
  static_assert(MaxDepth > 0, "");
  if (str[init_pos] != '"') {
    throw std::runtime_error("Unknown json value must start with \"");
  }
  std::size_t curr_pos = init_pos + 1;
  ParserState curr_state{ParserState::kNumber};
  while (curr_pos < str.Size()) {
    char c = str[curr_pos];
    if (curr_state == ParserState::kNumber && (c >= '0' && c <= '9')) {
    } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
      curr_state = ParserState::kString;
    } else if (c == '"') {
      break;
    }
    ++curr_pos;
  }

  if (curr_pos == str.Size()) {
    throw std::runtime_error("End of value not found");
  }

  cx::StaticString value = str.GetSubString(init_pos + 1, curr_pos - init_pos - 1);
  JsonValue<MaxDepth> json;
  if (curr_state == ParserState::kNumber) {
    json.ToNumber() = StringToNumber(value);
  } else {
    if (value == "true") {
      json.ToBoolean() = true;
    } else if (value == "false") {
      json.ToBoolean() = false;
    } else if (value != "null") {
      json.ToString() = value;
    }
  }
  return cx::MakePair(curr_pos + 1, json);
}

template <std::size_t MaxDepth>
constexpr cx::Pair<std::size_t, JsonValue<MaxDepth>> ParseJsonObject(std::size_t pos,
                                                                     const cx::StaticString& str) {
  if (str[pos] != '{') {
    throw std::runtime_error("Json object must start with {");
  }
  JsonValue<MaxDepth> json;
  std::size_t opened_braces_count = 1u;
  while (++pos < str.Size()) {
    if (str[pos] == '{') {
      ++opened_braces_count;
    } else if (str[pos] == '}') {
      --opened_braces_count;
    }
    if (opened_braces_count == 0u) {
      break;
    }
  }
  if (opened_braces_count != 0) {
    throw std::runtime_error("Unbalanced curly braces in json object");
  }
  return cx::MakePair(pos + 1, json);
}

template <std::size_t MaxDepth>
constexpr cx::Pair<std::size_t, JsonValue<MaxDepth>> ParseJsonArray(std::size_t pos,
                                                                    const cx::StaticString& str) {
  if (str[pos] != '[') {
    throw std::runtime_error("The json array must start with [");
  }
  JsonValue<MaxDepth> json;
  bool expect_delimeter = false;
  ++pos;
  while (pos < str.Size()) {
    char c = str[pos];
    if (c == ' ' || c == '\n' || c == '\t' || c == '\r') {
      ++pos;
      continue;
    } else if (expect_delimeter) {
      expect_delimeter = false;
      if (c == ',') {
        ++pos;
        continue;
      } else {
        throw std::runtime_error("The separate values in json array must be comma separated");
      }
    } else if (c == '[') {
      auto pos_and_json = ParseJsonArray<MaxDepth - 1>(pos, str);
      pos = pos_and_json.first;
      pos_and_json.AssertArray();
      json.ToArray().PushBack(pos_and_json.second);
      expect_delimeter = true;
    } else if (c == '{') {
      auto pos_and_json = ParseJsonObject<MaxDepth - 1>(pos, str);
      pos = pos_and_json.first;
      pos_and_json.AssertObject();
      json.ToArray().PushBack(pos_and_json.second);
      expect_delimeter = true;
    } else if (c == '"') {
      auto pos_and_json = ParseUnknown<MaxDepth - 1>(pos, str);
      pos = pos_and_json.first;
      json.ToArray().PushBack(pos_and_json.second);
      expect_delimeter = true;
    } else if (c == ']') {
      break;
    } else {
      throw std::runtime_error("Unexpected value");
    }
  }
  return cx::MakePair(pos + 1, json);
}

template <std::size_t MaxDepth>
constexpr JsonValue<MaxDepth> ParseString(const cx::StaticString& str) {
  return {};
}

}  // namespace json

constexpr cx::StaticString operator"" _ss(const char* str, std::size_t size) {
  return cx::StaticString(str, size);
}

constexpr JsonValue<5> operator"" _json(const char* str, std::size_t size) {
  return json::ParseString<5>(cx::StaticString(str, size));
}

}  // namespace cx
