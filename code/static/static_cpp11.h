class S {
  public:
    static int S_uninit_a;               // Declaration. Requires definition.
    // static int b = 2;        // In-class initialization of not const static is forbidden
    // inline static int c;     // Inline static variables only in C++14?
    // inline static int d = 4; // Inline static variables only in C++14?
    static const int S_const_uninit_e;         // Declaration. Requires definition.
    static const int S_const_init_f = 6;
    // static constexpr int g;  // Constexpr must be initialized
    static constexpr int S_constexpr_init_h = 8;

    static void PrintValues();
};
