#include <cstdlib>
#include <elf.h>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " FILENAME" << std::endl;
    return EXIT_FAILURE;
  }
  return 0;
}
