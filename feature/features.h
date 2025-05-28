#pragma once
#include <memory>
#include <variant>
#include <vector>
#include <cstdint>

namespace Delta {
constexpr int default_finesse_sf_cnt = 3;
// every super feature is grouped with 4 sub-features by default
constexpr int default_finesse_sf_subf = 4;

constexpr int default_odess_sf_cnt = 3;
constexpr int default_odess_sf_subf = 4;
constexpr int default_roll_stride = 1;
constexpr uint64_t default_odess_mask = (1 << 7) - 1;
class Chunk;
using Feature = std::variant<std::vector<std::vector<uint64_t>>,
                             std::vector<uint64_t>,
                             std::vector<uint32_t>
                             >;

std::vector<uint64_t> group(int sf_cnt, int sf_subf,
              const std::vector<uint32_t> &sub_features);

// roll group feature as super feature
std::vector<uint64_t> rollgroup(int sf_subf, int stride,
                                const std::vector<uint32_t> &sub_features);

class FeatureCalculator {
public:
  virtual Feature operator()(std::shared_ptr<Chunk> chunk) = 0;
};

class FinesseFeature : public FeatureCalculator {
public:
  FinesseFeature(const int sf_cnt = default_finesse_sf_cnt,
                 const int sf_subf = default_finesse_sf_subf)
      : sf_cnt_(sf_cnt), sf_subf_(sf_subf) {}

  Feature operator()(std::shared_ptr<Chunk> chunk) override;

private:
  // grouped super features count
  const int sf_cnt_;
  // how much sub feature does a one super feature contain
  const int sf_subf_;
};

class NTransformFeature : public FeatureCalculator {
public:
  NTransformFeature(const int sf_cnt = 3, const int sf_subf = 4)
      : sf_cnt_(sf_cnt), sf_subf_(sf_subf) {}

  Feature operator()(std::shared_ptr<Chunk> chunk) override;

private:
  // grouped super features count
  const int sf_cnt_;
  // how much sub feature does a one super feature contain
  const int sf_subf_;
};

class OdessFeature : public FeatureCalculator {
public:
  OdessFeature(const int sf_cnt = default_odess_sf_cnt,
               const int sf_subf = default_odess_sf_subf,
               const int mask = default_odess_mask)
      : sf_cnt_(sf_cnt), sf_subf_(sf_subf), mask_(mask) {}

  Feature operator()(std::shared_ptr<Chunk> chunk) override;

private:
  // grouped super features count
  const int sf_cnt_;
  // how much sub feature does a one super feature contain
  const int sf_subf_;

  const int mask_;
};

class OdessSubfeatures : public FeatureCalculator {
public:
  Feature operator()(std::shared_ptr<Chunk> chunk);
};

class PalantirFeature : public FeatureCalculator {
public:
  Feature operator()(std::shared_ptr<Chunk> chunk);
private:
  OdessSubfeatures get_sub_features_;
};

class RollFeature : public FeatureCalculator {
public:
  RollFeature(const int sf_subf = default_odess_sf_subf,
              const int stride = default_roll_stride)
      : sf_subf_(sf_subf), stride_(stride) {}
  Feature operator()(std::shared_ptr<Chunk> chunk) override;

private:
  OdessSubfeatures get_sub_features_;
  const int sf_subf_;
  const int stride_;
};

class HFMHVFeature : public FeatureCalculator {
public:
  HFMHVFeature() {}
  Feature operator()(std::shared_ptr<Chunk> chunk) override;

private:
  OdessSubfeatures odess_feature_;
  RollFeature roll_feature_;

};
} // namespace Delta