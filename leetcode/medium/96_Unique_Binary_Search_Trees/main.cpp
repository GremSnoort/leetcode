// std
#include <iostream>
#include <format>
#include <map>

class Solution {
    
    std::map<int, std::map<int, std::map<int, int>>> cache;
    
    auto build(int n, int lb, int rb) -> int {
        if (auto it = cache.find(n); it != cache.end()) {
            if (auto itl = it->second.find(lb); itl != it->second.end()) {
               if (auto itr = itl->second.find(rb); itr != itl->second.end()) {
                    return itr->second;
                }
            }
        }
        int vl = 0, vr = 0;
        for (auto i = lb+1; i < n; ++i) {
            vl += build(i, lb, n);
        }
        for (auto i = n+1; i < rb; ++i) {
            vr += build(i, n, rb);
        }
        if (vl == 0) vl = 1;
        if (vr == 0) vr = 1;
        auto value = vl * vr;
        cache[n][lb][rb] = value;
        return value;
    }
    
public:
    int numTrees(int n) {
        int value = 0;
        for (auto i = 1; i <= n; ++i) {
            value += build(i, 0, n+1);
        }
        return value;
    }
};

int main() {
    std::printf("%s\n", std::format("{}", Solution().numTrees(3)).data());
    return 0;
}
