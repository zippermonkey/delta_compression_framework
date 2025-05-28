#include "filter/filter.h"
#include <vector>
namespace Delta {
bool HFilter::IsDeltaCompressible(std::shared_ptr<Chunk> base_chunk,
                                  std::shared_ptr<Chunk> chunk) {

  std::vector<double> base_hf(256, 0);
  std::vector<double> input_hf(256, 0);

  uint8_t *base_content = base_chunk->buf();
  uint8_t *input_content = chunk->buf();

  for (int i = 0; i < base_chunk->len(); ++i) {
    base_hf[base_content[i]] += 1;
  }

  for (int i = 0; i < chunk->len(); ++i) {
    input_hf[input_content[i]] += 1;
  }

  double distance = 0;
  for (int i = 0; i < 256; ++i) {

    if (base_hf[i] > input_hf[i])
      distance += base_hf[i] - input_hf[i];
    else
      distance -= base_hf[i] - input_hf[i];
  }

  distance /= (base_chunk->len() + chunk->len());

  return distance < 0.5;
}
} // namespace Delta