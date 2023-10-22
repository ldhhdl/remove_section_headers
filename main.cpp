#include <cstdlib>
#include <elf.h>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

std::string read_file(const std::string &filename) {
  std::ifstream input_file{filename, std::ifstream::in | std::ifstream::binary};
  if (!input_file.is_open() || !input_file.good()) {
    std::cerr << "Error opening " << filename << std::endl;
    return std::string{};
  }
  std::string file_data{std::istreambuf_iterator<char>(input_file),
                        std::istreambuf_iterator<char>()};
  input_file.close();
  return file_data;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " FILENAME" << std::endl;
    return EXIT_FAILURE;
  }

  const std::string filename{argv[1]};
  if (!fs::is_regular_file(filename)) {
    std::cerr << filename << " does not exist" << std::endl;
    return EXIT_FAILURE;
  }

  auto file_data = read_file(filename);
  if (file_data.length() == 0) {
    std::cerr << "Error reading " << filename << std::endl;
    return EXIT_FAILURE;
  }

  Elf64_Ehdr *ehdr = reinterpret_cast<Elf64_Ehdr *>(&file_data[0]);
  std::cout << std::hex;
  std::cout << "Entrypoint: 0x" << ehdr->e_entry << std::endl;

  return 0;
}
