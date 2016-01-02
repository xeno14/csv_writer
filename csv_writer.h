/**
 * @file csv_writer.h
 * @brief csv writing interface for iterator, range and various arguments
 */
#pragma once

#include <ostream>
#include <string>


namespace csv_writer {
namespace internal {

template <class T, class... Args>
struct WriteImpl {
  void write(std::ostream* os, const std::string& sep, const T& value,
             const Args&... args) {
    *os << value << sep;

    WriteImpl<Args...>::write(os, sep, args...);
  }
};


template <class T>
struct WriteImpl<T> {
  void write(std::ostream* os, const std::string& sep, const T& value) {
    *os << value << std::endl;
  }
};

template <class T, class... Args>
std::enable_if<(sizeof...(Args) == 0), void> write_impl(std::ostream* os,
                                                        const std::string& sep,
                                                        const T& value) {
  *os << value << std::endl;
}

template <class T, class... Args>
std::enable_if<(sizeof...(Args) > 0), void> write_impl(std::ostream* os,
                                                       const std::string& sep,
                                                       const T& value,
                                                       const Args&... args) {
  *os << value << sep;
  write_impl<Args...>(os, sep, args...);
}

}  // namespace internal

class CSVWriter {
 public:
  CSVWriter(std::ostream* os, const std::string& sep = ",")
      : os_(os), sep_(sep) {}

  template <class InputIterator>
  void write_iterator(InputIterator first, InputIterator last) {
    bool first_flag = true;
    while (first != last) {
      if (first_flag) {
        first_flag = false;
      } else {
        *os_ << sep_;
      }
      *os_ << *first;

      ++first;
    }
    *os_ << std::endl;
  }

  template <class Range>
  void write_range(const Range& range) {
    write_iterator(std::begin(range), std::end(range));
  }

  template <class... Args>
  void write(const Args&... args) {
    internal::write_impl(os_, sep_, args...);
  }

  template <class... Args>
  void write(const std::tuple<Args...>& tup);

  void flush() {
    os_->flush();
  }

 private:
  std::ostream* os_;
  const std::string sep_;
};

}  // namespace csv_writer
