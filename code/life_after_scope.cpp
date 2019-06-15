#include <cstdio>
#include <string>

struct Holder {
  public:
    Holder(const std::string& value) : value_(value) {}
    ~Holder() {
      puts(value_.c_str());
    }
    const std::string& value_;
};

std::string GetName() {
  std::string name = "Very strange name";
  Holder holder(name);
  return name;
  // return std::move(name);
}

int main() {
  std::string name = GetName();
  puts(name.c_str());
  return 0;
}
