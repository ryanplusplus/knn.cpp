#ifndef knn_hpp
#define knn_hpp

#include <map>
#include <vector>
#include <concepts>
#include <algorithm>

namespace knn {
  using namespace std;

  template <
    typename NeighborIterator,
    typename Value,
    typename DistanceCalculator>
  auto classify(
    const Value& value,
    int k,
    const NeighborIterator& firstNeighbor,
    const NeighborIterator& lastNeighbor,
    DistanceCalculator distance)
    -> decltype(firstNeighbor->first)
  {
    auto distances = vector<pair<decltype(firstNeighbor->first), int>>{};
    for(auto neighbor = firstNeighbor; neighbor != lastNeighbor; ++neighbor) {
      distances.emplace_back(neighbor->first, distance(neighbor->second, value));
    }

    sort(distances.begin(), distances.end(), [](const auto& lhs, const auto& rhs) {
      return lhs.second < rhs.second;
    });

    auto votes = map<decltype(firstNeighbor->first), int>();
    auto it = distances.begin();
    for(auto i = 0; i < k; ++i) {
      ++votes[(*it).first];
      ++it;
    }

    return max_element(votes.begin(), votes.end(), [](const auto& lhs, const auto& rhs) {
      return lhs.second < rhs.second;
    })->first;
  }
}

#endif
