#include <iostream>
#include <vector>
#include <map>

template <typename T>
struct GroupInfo {
    int key;
    int count = 0;
};

template <typename T>
void groupStats(const std::vector<T>& arr) {
    std::map<int, GroupInfo<T>> groups;

    for (T x : arr) {
        int key = x % 10;
        if (groups.find(key) != groups.end()) {
            groups[key].count++;
        } else {
            groups[key] = GroupInfo<T>{key, 1};
        }
    }

    for (const auto& group : groups) {
        std::cout << "Key: " << group.second.key << ", "
                  << "Count: " << group.second.count << std::endl;
    }
}

int main() {
    std::vector<int> arr = {12, 34, 56, 12};
    groupStats(arr);
    return 0;
}
