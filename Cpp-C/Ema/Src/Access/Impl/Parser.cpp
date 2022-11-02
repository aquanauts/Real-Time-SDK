#include "Parser.h"
#include "RefreshMsg.h"
#include "StaticDecoder.h"
#include "StatusMsg.h"
#include "UpdateMsg.h"
#include "rtr/rsslDataDictionary.h"

using namespace refinitiv::ema::access;

namespace {
RsslBuffer from(const char *buf, size_t len) {
  return {static_cast<uint32_t>(len), const_cast<char *>(buf)};
}
} // namespace

struct Parser::Impl {
  RsslDataDictionary dictionary{};

  Impl(const char *dictFilename, const char *enumtable) {
    char errTxt[256];
    RsslBuffer errorText = {sizeof(errTxt) - 1, errTxt};

    if (rsslLoadFieldDictionary(dictFilename, &dictionary, &errorText) < 0)
      throw std::runtime_error("Unable to load field dictionary: " +
                               std::string(errTxt));

    if (rsslLoadEnumTypeDictionary(enumtable, &dictionary, &errorText) < 0)
      throw std::runtime_error("Unable to load enum type dictionary: " +
                               std::string(errTxt));
  }
  ~Impl() { rsslDeleteDataDictionary(&dictionary); }

  template <typename MsgType>
  void parse(MsgType &msg, RsslBuffer buffer, unsigned char major,
             unsigned char minor) {
    const auto type = msg.getDataType();
    StaticDecoder::setRsslData(&msg, &buffer, type, major, minor, &dictionary);
    const auto decodedType = static_cast<Data &>(msg).getDataType();
    if (decodedType != type) {
      if (decodedType == DataType::ErrorEnum) {
        auto &err =
            static_cast<const OmmError &>(static_cast<const Data &>(msg));
        throw std::runtime_error("Failed to decode message: " +
                                 std::string(err.toString()));
      } else {
        throw std::runtime_error(
            "Failed to decode message - it changed to an unknown type?!");
      }
    }
  }
};

Parser::Parser(const char *dictionary, const char *enumtable)
    : impl_(std::make_unique<Impl>(dictionary, enumtable)) {}
Parser::~Parser() = default;

void Parser::parse(RefreshMsg &msg, const char *buf, size_t len,
                   unsigned char major, unsigned char minor) {
  impl_->parse(msg, from(buf, len), major, minor);
}
void Parser::parse(UpdateMsg &msg, const char *buf, size_t len,
                   unsigned char major, unsigned char minor) {
  impl_->parse(msg, from(buf, len), major, minor);
}
void Parser::parse(StatusMsg &msg, const char *buf, size_t len,
                   unsigned char major, unsigned char minor) {
  impl_->parse(msg, from(buf, len), major, minor);
}
