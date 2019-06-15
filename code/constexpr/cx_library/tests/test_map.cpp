#include <gtest/gtest.h>
#include "cx_map.h"
#include "cx_static_string.h"

constexpr auto MapCreate() {
  cx::Map<int, double> m;
  m[5] = 1.5;
  m[6] = 2.5;
  m[7] = 3.5;
  return m;
}

constexpr void CheckMapCreate() {
  constexpr auto m = MapCreate();
  static_assert(m.Size() == 3u, "");
  static_assert(m.Find(5) != m.end(), "");
  static_assert(m.Find(6) != m.end(), "");
  static_assert(m.Find(7) != m.end(), "");
  static_assert(m.Find(8) == m.end(), "");
  static_assert(m.Find(9) == m.end(), "");
}

constexpr auto MapErase() {
  cx::Map<int, char, 2> m;
  m[1] = '5';
  m[2] = '7';
  m.Erase(1);
  m[3] = 'e';
  return m;
}

constexpr void CheckMapErase() {
  constexpr auto m = MapErase();
  static_assert(m.Find(1) == m.end(), "");
  static_assert(m.Find(2) != m.end(), "");
  static_assert(m.Find(3) != m.end(), "");
  static_assert(m.Size() == 2u, "");
}

constexpr void CheckMapOrder() {
  constexpr auto m = MapCreate();
  static_assert(m.GetByIndex(0) == cx::MakePair(5, 1.5), "");
  static_assert(m.GetByIndex(1) == cx::MakePair(6, 2.5), "");
  static_assert(m.GetByIndex(2) == cx::MakePair(7, 3.5), "");
}

TEST(MapTestSuite, MapTestSuite) {
  CheckMapCreate();
  CheckMapErase();
  CheckMapOrder();
}

TEST(MapTestSuite, MapConstructors) {
  {
    constexpr cx::Map<int, double> m{{1, 1.0}, {2, 2.0}, {3, 3.0}};
    static_assert(m.Size() == 3u, "");
    static_assert(m.Empty() == false, "");
    static_assert(m.At(1) == 1.0, "");
    static_assert(m.At(2) == 2.0, "");
    static_assert(m.At(3) == 3.0, "");
    static_assert(m.GetByIndex(0) == cx::MakePair(1, 1.0), "");
    static_assert(m.GetByIndex(1) == cx::MakePair(2, 2.0), "");
    static_assert(m.GetByIndex(2) == cx::MakePair(3, 3.0), "");
  }
}

TEST(MapTestSuite, MapEqualityOperators) {
  constexpr cx::Map<int, double> m1{{1, 1.0}, {2, 2.0}, {3, 3.0}};
  constexpr cx::Map<int, double> m2{{1, 1.0}, {2, 2.0}, {3, 3.0}};
  constexpr cx::Map<int, double> m3{{1, 1.0}, {2, 2.0}, {3, 3.00001}};
  static_assert(m1 == m2, "");
  static_assert(m1 != m3, "");
}

constexpr auto GetColorsMap() {
  cx::Map<cx::StaticString, std::uint32_t> colors;
  colors["red"] = 0xFF0000;
  colors["green"] = 0x00FF00;
  colors["blue"] = 0x0000FF;
  return colors;
}

TEST(MapTestSuite, ComplexConstructors) {
  {
    constexpr auto colors = GetColorsMap();
    static_assert(colors.Size() == 3u, "");
    static_assert(colors.Find("red") != colors.end(), "");
    static_assert(colors.Find("green") != colors.end(), "");
    static_assert(colors.Find("blue") != colors.end(), "");
    static_assert(colors.At("red") == 0xFF0000, "");
    static_assert(colors.At("green") == 0x00FF00, "");
    static_assert(colors.At("blue") == 0x0000FF, "");
    static_assert(colors.Find("orange") == colors.end(), "");
    // FindIf(colors.begin(), colors.end(), [](auto& value) { value.first == "red" });
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
