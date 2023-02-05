#ifndef knn_hpp
#define knn_hpp

#include <map>
#include <vector>
#include <concepts>
#include <algorithm>

namespace knn {
  using namespace std;

  template <typename Classification, typename Neighbors, typename Value, typename DistanceCalculator>
  Classification classify(const Neighbors& neighbors, int k, const Value& value, DistanceCalculator distance)
  {
    auto distances = vector<pair<Classification, int>>{};

    for(auto neighbor : neighbors) {
      distances.emplace_back(neighbor.first, distance(neighbor.second, value));
    }

    sort(distances.begin(), distances.end(), [](const auto& lhs, const auto& rhs) {
      return lhs.second < rhs.second;
    });

    auto votes = map<Classification, int>();
    auto it = distances.begin();
    for(auto i = 0; i < k; ++i) {
      ++votes[(*it).first];
      ++it;
    }

    return (*max_element(votes.begin(), votes.end(), [](const auto& lhs, const auto& rhs) {
      return lhs.second < rhs.second;
    }))
      .first;
  }
}

#endif
