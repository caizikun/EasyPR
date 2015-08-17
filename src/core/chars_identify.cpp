#include "easypr/core/chars_identify.h"
#include "easypr/core/core_func.h"
#include "easypr/train/ann_train.h"
#include "easypr/config.h"

namespace easypr {

CharsIdentify* CharsIdentify::instance_ = nullptr;

CharsIdentify* CharsIdentify::instance() {
  if (!instance_) {
    instance_ = new CharsIdentify;
  }
  return instance_;
}

CharsIdentify::CharsIdentify() {
  ann_ = ml::ANN_MLP::load<ml::ANN_MLP>(kDefaultAnnPath);
}

std::pair<std::string, std::string> CharsIdentify::identify(cv::Mat input) {
  cv::Mat feature = features(input, kPredictSize);
  auto index = static_cast<int>(ann_->predict(feature));
  if (index < 34) {
    return std::make_pair(kChars[index], kChars[index]);
  } else {
    const char* key = kChars[index];
    return std::make_pair(key, kCharsMap.at(key));
  }
}
}
