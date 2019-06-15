#include <iostream>

template <typename T>
void PrintMemoryLayout(const std::string& name, const T& object, size_t n_cols = 8) {
  unsigned char* ptr = (unsigned char*)(&object);
  const size_t size = sizeof(T);
  bool end_of_line = false;
  std::cout << "The layout of type \"" << name << "\" with size " << std::dec << size << ":\n";
  for (size_t byte_index = 0; byte_index < size; ++byte_index) {
    auto byte_ptr = ptr + byte_index;
    std::cout << std::setw(2) << std::setfill('0') << std::uppercase << std::hex
              << static_cast<int>(*byte_ptr) << " ";
    if ((byte_index + 1) % n_cols == 0) {
      std::cout << '\n';
      end_of_line = true;
    } else {
      end_of_line = false;
    }
  }
  if (end_of_line) {
    std::cout << std::dec << std::endl;
  } else {
    std::cout << std::dec << std::flush;
  }
}

template <typename T>
uintptr_t GetVtableAddress(const T& object) {
  // Probably very-very bad platform/compilator dependent implementation
  // Using C-style to avoid paired const_cast and reinterpret_cast
  return *((uintptr_t*)(&object));
}

template <typename T>
void ChangeVtableAddress(T& object, uintptr_t vtable_ptr) {
  *((uintptr_t*)(&object)) = vtable_ptr;
}
