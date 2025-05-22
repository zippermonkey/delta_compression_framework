#include "chunk/chunk.h"
#include "index/roll_index.h"
#include "feature/features.h"
#include <assert.h>
#include <fstream>
#include <glog/logging.h>
namespace Delta {
using chunk_id = uint32_t;
std::optional<chunk_id>
RollFeatureIndex::GetBaseChunkID(const Feature &feat) {
  const auto &super_feature = std::get<std::vector<uint64_t>>(feat);
  std::optional<chunk_id> result = std::nullopt;
  for (int i = 0; i < super_feature_count_; i++) {
    // get a matched super feature
    if (index_[i].count(super_feature[i])) {
      // first fit
      result = index_[i][super_feature[i]];
      break;
    }
  }
  return result;
}

void RollFeatureIndex::AddFeature(const Feature &feat, chunk_id id) {
  const auto &super_feature = std::get<std::vector<uint64_t>>(feat);
  for (int i = 0; i < super_feature_count_; i++) {
    index_[i][super_feature[i]] = id;
  }
}

} // namespace Delta