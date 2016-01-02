#include "csv_writer.h"

#include <iostream>
#include <vector>

int main() {
  csv_writer::CSVWriter writer(&std::cout, "\t");

  // vriable argument
  writer.write("x", "y");

  // range
  std::vector<int> u {1, 2};
  writer.write_range(u);

  // iterator
  std::vector<int> v {3, 4};
  writer.write_iterator(std::begin(v), std::end(v));

  writer.flush();

  return 0;
}
