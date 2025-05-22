#include "filter/filter.h"
#include "encoder/xdelta.h"
#include <iostream>
#include <numeric> // For std::accumulate
namespace Delta {

bool PalantirFilter::IsDeltaCompressible(std::shared_ptr<Chunk> base_chunk,
                                         std::shared_ptr<Chunk> chunk) {
  double average_compress_ratio = 0;
  auto const &hist_data = hist_compress_ratio_->data();
  double sum = std::accumulate(hist_data.begin(), hist_data.end(), 0.0);
  double avg = sum / hist_compress_ratio_->size();

  // 当前块的delta压缩率
  XDelta xdelta_encoder = XDelta();
  std::shared_ptr<Chunk> delta_chunk = xdelta_encoder.encode(base_chunk, chunk);

  double delta_ratio = 1.0 * delta_chunk->len() / chunk->len();

  return delta_ratio < avg;
}

void PalantirFilter::add_hist_ratio(double ratio) {
  hist_compress_ratio_->push(ratio);
}

} // namespace Delta