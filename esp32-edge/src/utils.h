#pragma once

#include <CRC32.h>

uint32_t calculateCRC(const String& data) {
  CRC32 crc32;
  crc32.update(data.c_str(), data.length());
  return crc32.finalize();
}