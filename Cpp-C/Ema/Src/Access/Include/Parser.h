#pragma once

#include <memory>

namespace refinitiv::ema::access {

class RefreshMsg;
class UpdateMsg;
class StatusMsg;

class Parser {
  struct Impl;
  std::unique_ptr<Impl> impl_;

public:
  Parser(const char *dictionary, const char *enumtable);
  ~Parser();

  void parse(RefreshMsg &msg, const char *buf, size_t len, unsigned char major,
             unsigned char minor);
  void parse(UpdateMsg &msg, const char *buf, size_t len, unsigned char major,
             unsigned char minor);
  void parse(StatusMsg &msg, const char *buf, size_t len, unsigned char major,
             unsigned char minor);
};

} // namespace refinitiv::ema::access