#pragma once
#include "chunk/chunk.h"
namespace Delta {
class Filter {
public:
  virtual bool IsDeltaCompressible(std::shared_ptr<Chunk> base_chunk,
                                   std::shared_ptr<Chunk> chunk) = 0;
};


class YesFilter : public Filter {
public:
  bool IsDeltaCompressible(std::shared_ptr<Chunk> base_chunk,
                           std::shared_ptr<Chunk> chunk) override {
    return true;
  }
};


class HFilter : public Filter {
  bool IsDeltaCompressible(std::shared_ptr<Chunk> base_chunk,
                           std::shared_ptr<Chunk> chunk) override;

};

} // namespace Delta