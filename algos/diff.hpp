#ifndef MCPP_DIFF_H
#define MCPP_DIFF_H

/*! mcpp::diff 实现一种比较diff算法。
  
  diff算法的Policy如下：

  ```C++
  struct Policy {
    using key_type = <user-defined>;
    using view_type = <user-defined>;
    using data_type = <user-defined>;

    key_type viewKey(const view_type&);
    key_type modelKey(const view_type&);
    view_type createView(const data_type&);
  };
  ```
*/

#include <unordered_map>
#include <algorithm>

namespace mcpp {

template<typename Policy, typename V, typename ViewIter, typename ModelIter>
void diff(V& view, ViewIter vBegin, ViewIter vEnd, ModelIter mBegin, ModelIter mEnd)
{
    auto vDiffStart = vBegin;
    auto mDiffStart = mBegin;
    for (; vDiffStart != vEnd && mDiffStart != mEnd; ++vDiffStart, ++mDiffStart) {
        if (Policy::viewKey(*vDiffStart) != Policy::modelKey(*mDiffStart)) {
            break;
        }
    }

    if (std::distance(vDiffStart, vEnd) > 0 && std::distance(mDiffStart, mEnd) > 0) {
        auto rVStart = std::make_reverse_iterator(vEnd);
        auto rVEnd = std::make_reverse_iterator(vDiffStart);
        auto rMStart = std::make_reverse_iterator(mEnd);
        auto rMEnd = std::make_reverse_iterator(mDiffStart);
        for (; rVStart != rVEnd && rMStart != rMEnd; ++rVStart, ++rMStart) {
            if (Policy::viewKey(*rVStart) != Policy::modelKey(*rMStart)) {
                break;
            }
        }

        auto vDiffEnd = rVStart.base();
        auto mDiffEnd = rMStart.base();
        std::unordered_map<typename Policy::key_type, typename std::iterator_traits<ViewIter>::value_type> cache;
        for (auto it = vDiffStart; it != vDiffEnd; ++it) {
            cache.insert({Policy::viewKey(*it), std::move(*it)});
        }

        auto it1 = vDiffStart;
        auto it2 = mDiffStart;
        for (; it1 != vDiffEnd && it2 != mDiffEnd; ++it1, ++it2) {
            if (auto it = cache.find(Policy::modelKey(*it2)); it != cache.end()) {
                *it1 = std::move(it->second);
            } else {
                *it1 = std::move(Policy::createView(*it2));
            }
        }

        const auto diffSize1 = std::distance(it1, vDiffEnd);
        const auto diffSize2 = std::distance(it2, mDiffEnd);
        if (diffSize1 < diffSize2) {
            std::transform(it2, mDiffEnd, std::inserter(view, it1), Policy::createView);
        } else if (diffSize1 > diffSize2) {
            view.erase(it1, vDiffEnd);
        }
    } else if (std::distance(vDiffStart, vEnd) > 0) {
        view.erase(vDiffStart, vEnd);
    } else if (std::distance(mDiffStart, mEnd) > 0) {
        std::transform(mDiffStart, mEnd, std::inserter(view, vDiffStart), Policy::createView);
    }
}

}

#endif // MCPP_DIFF_H
