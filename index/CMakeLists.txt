add_library(index STATIC super_feature_index.cpp palantir_index.cpp
                            best_fit_index.cpp roll_index.cpp)
target_link_libraries(index glog gflags feature)