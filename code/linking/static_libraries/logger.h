class Logger {
  public:
    Logger();
    ~Logger();
};

__attribute__((__used__)) Logger& GetLogger();
