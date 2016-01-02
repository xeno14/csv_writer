#include "csv_writer.h"

#include <cassert>
#include <sstream>
#include <vector>


void write_iterator_test() {
  std::stringstream ss;

  csv_writer::CSVWriter writer(&ss);

  std::vector<int> v = {1, 2, 3};
  writer.write_iterator(v.begin(), v.end());

  assert(ss.str() == "1,2,3\n");
}

void write_range_test() {
  std::stringstream ss;

  csv_writer::CSVWriter writer(&ss);

  std::vector<int> v = {1, 2, 3};
  writer.write_range(v);

  assert(ss.str() == "1,2,3\n");
}

void write_range_solo_test() {
  std::stringstream ss;

  csv_writer::CSVWriter writer(&ss);

  std::vector<int> v = {1};
  writer.write_range(v);

  assert(ss.str() == "1\n");
}

void write_impl_test() {
  std::stringstream ss;
  csv_writer::internal::write_impl(&ss, ",", 1, 2, 3);

  assert(ss.str() == "1,2,3\n");
}

void write_impl_solo_test() {
  std::stringstream ss;
  csv_writer::internal::write_impl(&ss, ",", 1);

  assert(ss.str() == "1\n");
}

void write_test() {
  std::stringstream ss;
  csv_writer::CSVWriter writer(&ss);
  writer.write(1, 2, 3);
  writer.write(4, 5, 6);
  assert(ss.str() == "1,2,3\n4,5,6\n");
}

int main() {
  write_iterator_test();
  write_range_test();
  write_range_solo_test();
  write_impl_test();
  write_impl_solo_test();
  write_test();
  return 0;
}
