#include <iostream>
#include <vector>
#include <map>

template <typename T>
struct GroupInfo {
    int key;
    int count;
    T minElem;
    T maxElem;
};

template <typename T>
void groupStats(const std::vector<T>& arr) {
    std::map<int, GroupInfo<T>> groups;

    for (const T& x : arr) {
        int key = x % 10;

        auto it = groups.find(key);
        if (it == groups.end()) {
            groups[key] = GroupInfo<T>{key, 1, x, x};
        } else {
            GroupInfo<T>& g = it->second;
            g.count++;

            if (x < g.minElem) g.minElem = x;
            if (g.maxElem < x) g.maxElem = x;
        }
    }

    for (const auto& pair : groups) {
        const auto& g = pair.second;

        std::cout << "Key: " << g.key << "\n";
        std::cout << "Count: " << g.count << "\n";
        std::cout << "Min: " << g.minElem << "\n";
        std::cout << "Max: " << g.maxElem << "\n";
        std::cout << "-----\n";
    }
}

int main() {
    std::vector<int> arr = {12, 34, 56, 12};
    groupStats(arr);
    return 0;
}
