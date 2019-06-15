#include <boost/program_options.hpp>
#include <iostream>

namespace opt = boost::program_options;

void OnApples(int apples_number) {
  std::cout << "Apples number = " << apples_number << std::endl;
}

void OnOranges(int oranges_number) {
  std::cout << "Oranges number = " << oranges_number << std::endl;
}

int main(int argc, char *argv[]) {
  try {
    opt::options_description desc{"Options"};
    desc.add_options()
        ("help,h", "Help messages")
        ("apples", opt::value<int>()->default_value(0)->notifier(OnApples), "Number of apples")
        ("oranges", opt::value<int>()->default_value(0)->notifier(OnOranges), "Number of oranages");
    opt::variables_map vm;
    opt::store(opt::parse_command_line(argc, argv, desc), vm);
    std::cout << "Running opt::notify" << std::endl;
    opt::notify(vm);

    if (vm.count("help")) {
      std::cout << desc << '\n';
      return 0;
    }

    int number_of_fruites = 0;
    if (vm.count("apples")) {
      number_of_fruites += vm["apples"].as<int>();
    }
    if (vm.count("oranges")) {
      number_of_fruites += vm["oranges"].as<int>();
    }
    std::cout << "Fruites number = " << number_of_fruites << std::endl;
  } catch (const opt::error &ex) {
    std::cerr << ex.what() << std::endl;
  }
  return 0;
}
