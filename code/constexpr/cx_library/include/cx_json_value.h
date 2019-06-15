#include "cx_array.h"
#include "cx_map.h"
#include "cx_vector.h"
#include "cx_static_string.h"

namespace cx {

enum class JsonType { Null, Boolean, Number, String, Array, Object };

template <std::size_t MaxDepth = 5>
class JsonValue {
 private:
  constexpr static std::size_t kMaxVectorSize{6};
  constexpr static std::size_t kMaxMapSize{6};

  using JsonArray = cx::Vector<JsonValue<MaxDepth - 1>, kMaxVectorSize>;
  using JsonObject = cx::Map<cx::StaticString, JsonValue<MaxDepth - 1>, kMaxMapSize>;

  union Data {
    void* null;
    bool boolean;
    double number;
    cx::StaticString string;
    JsonArray array;
    JsonObject object;

    constexpr Data() : null{nullptr} {
    }
    constexpr Data(bool value) : boolean{value} {
    }
    constexpr Data(double value) : number(value) {
    }
    constexpr Data(const cx::StaticString value) : string(value) {
    }
    constexpr Data(const JsonArray& value) : array(value) {
    }
    constexpr Data(const JsonObject& value) : object(value) {
    }
  };

  JsonType type_ = JsonType::Null;
  Data data_{};

 public:
  // Constructors
  constexpr JsonValue() = default;

  constexpr JsonValue(bool value) : type_{JsonType::Boolean}, data_{value} {
  }

  constexpr JsonValue(double value) : type_{JsonType::Number}, data_{value} {
  }

  constexpr JsonValue(const cx::StaticString& value) : type_{JsonType::String}, data_(value) {
  }

  // Types
  constexpr JsonType GetType() const {
    return type_;
  }

  constexpr void AssertType(JsonType t) const {
    if (t != type_) {
      throw std::runtime_error("Incorrect type");
    }
  }

  constexpr void AssertNull() const {
    AssertType(JsonType::Null);
  }

  constexpr void AssertBoolean() const {
    AssertType(JsonType::Boolean);
  }

  constexpr void AssertNumber() const {
    AssertType(JsonType::Number);
  }

  constexpr void AssertString() const {
    AssertType(JsonType::String);
  }

  constexpr void AssertArray() const {
    AssertType(JsonType::Array);
  }

  constexpr void AssertObject() const {
    AssertType(JsonType::Object);
  }

  // Transform and access

  constexpr const bool& ToBoolean() const {
    AssertType(JsonType::Boolean);
    return data_.boolean;
  }

  constexpr bool& ToBoolean() {
    if (type_ != JsonType::Boolean) {
      type_ = JsonType::Boolean;
      data_ = Data{false};
    }
    return data_.boolean;
  }

  constexpr const double& ToNumber() const {
    AssertType(JsonType::Number);
    return data_.number;
  }

  constexpr double& ToNumber() {
    if (type_ != JsonType::Number) {
      type_ = JsonType::Number;
      data_ = Data{0.0};
    }
    return data_.number;
  }

  constexpr const cx::StaticString& ToString() const {
    AssertType(JsonType::String);
    return data_.string;
  }

  constexpr cx::StaticString& ToString() {
    if (type_ != JsonType::String) {
      type_ = JsonType::String;
      data_ = Data{cx::StaticString{}};
    }
    return data_.string;
  }

  constexpr const JsonArray& ToArray() const {
    AssertType(JsonType::Array);
    return data_.array;
  }

  constexpr JsonArray& ToArray() {
    if (type_ != JsonType::Array) {
      type_ = JsonType::Array;
      data_ = Data{JsonArray{}};
    }
    return data_.array;
  }

  constexpr const JsonObject& ToObject() const {
    AssertType(JsonType::Object);
    return data_.object;
  }

  constexpr JsonObject& ToObject() {
    if (type_ != JsonType::Object) {
      type_ = JsonType::Object;
      data_ = Data{JsonObject{}};
    }
    return data_.object;
  }

  // Assignment operators
  constexpr JsonValue& operator=(double value) {
    ToNumber() = value;
    return *this;
  }

  constexpr JsonValue& operator=(bool value) {
    ToBoolean() = value;
    return *this;
  }

  constexpr JsonValue& operator=(const cx::StaticString& str) {
    ToString() = str;
    return *this;
  }

  // TODO: This function is written to resolve ambuguity with "bool" assignment when calling
  // j = "sdfdsf";
  constexpr JsonValue& operator=(const char* value) {
    return (*this = cx::StaticString(value));
  }

  // Conversion operators

  // TODO: converstion to simple type not needed if there is a conversion to const reference
  // TODO: j["a"] resulted in ambiguity if "explicit" is not used below
  constexpr explicit operator bool&() {
    AssertBoolean();
    return data_.boolean;
  }

  constexpr explicit operator const bool&() const {
    AssertBoolean();
    return data_.boolean;
  }

  constexpr explicit operator double&() {
    AssertNumber();
    return data_.number;
  }

  constexpr explicit operator const double&() const {
    AssertNumber();
    return data_.number;
  }

  constexpr explicit operator cx::StaticString&() {
    AssertString();
    return data_.string;
  }

  constexpr explicit operator const cx::StaticString&() const {
    AssertString();
    return data_.string;
  }

  // Access array element
  constexpr JsonValue<MaxDepth - 1>& operator[](std::size_t pos) {
    return ToArray()[pos];
  }

  constexpr const JsonValue<MaxDepth - 1>& operator[](std::size_t pos) const {
    return ToArray()[pos];
  }

  // Access map element
  constexpr JsonValue<MaxDepth - 1>& operator[](const cx::StaticString& str) {
    return ToObject()[str];
  }

  constexpr const JsonValue<MaxDepth - 1>& operator[](const cx::StaticString& str) const {
    return ToObject()[str];
  }

  constexpr std::size_t Size() const {
    if (type_ == JsonType::Array) {
      return data_.array.Size();
    } else if (type_ == JsonType::Object) {
      return data_.object.Size();
    } else {
      throw std::runtime_error("Size is relevant only for array or object");
    }
  }
};

template <>
struct JsonValue<0> {};

}  // namespace cx
