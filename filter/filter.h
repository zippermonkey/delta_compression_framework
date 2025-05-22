#pragma once
#include "chunk/chunk.h"
#include "utils/fixed_queue.h"
namespace Delta {
class Filter {
public:
  virtual bool IsDeltaCompressible(std::shared_ptr<Chunk> base_chunk,
                                   std::shared_ptr<Chunk> chunk) = 0;
  virtual void add_hist_ratio(double ratio) = 0;
};

class PalantirFilter : public Filter {
public:
  PalantirFilter(std::shared_ptr<FixedQueue<double>> hist_compress_ratio)
      : hist_compress_ratio_(hist_compress_ratio) {}
  bool IsDeltaCompressible(std::shared_ptr<Chunk> base_chunk,
                           std::shared_ptr<Chunk> chunk) override;
  void add_hist_ratio(double ratio) override;

private:
  std::shared_ptr<FixedQueue<double>> hist_compress_ratio_;
};

class YesFilter : public Filter {
public:
  bool IsDeltaCompressible(std::shared_ptr<Chunk> base_chunk,
                           std::shared_ptr<Chunk> chunk) {
    return true;
  }
  void add_hist_ratio(double ratio) {}
};

} // namespace Delta
