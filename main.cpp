#include <iostream>
#include <vector>
#include <string>

template <typename T, typename Key>
struct GroupInfo {
    Key key;
    int count;
    T minElem;
    T maxElem;
    double sum;
    double avg;
};

template <typename T, typename KeyFunc, typename ValueFunc>
auto groupStats(const T* arr, int n, KeyFunc keyFunc, ValueFunc valueFunc)
    -> std::vector<GroupInfo<T, decltype(keyFunc(arr[0]))>>
{
    typedef decltype(keyFunc(arr[0])) KeyType;
    typedef GroupInfo<T, KeyType> Info;

    std::vector<Info> groups;
    if (n <= 0) return groups;

    for (int i = 0; i < n; ++i) {
        const T& x = arr[i];
        KeyType key = keyFunc(x);
        double val = (double)valueFunc(x);

        int idx = -1;
        for (int j = 0; j < (int)groups.size(); ++j) {
            if (groups[j].key == key) {
                idx = j;
                break;
            }
        }

        if (idx == -1) {
            Info g;
            g.key = key;
            g.count = 1;
            g.minElem = x;
            g.maxElem = x;
            g.sum = val;
            g.avg = 0.0;
            groups.push_back(g);
        } else {
            Info& g = groups[idx];
            g.count++;

            if (x < g.minElem) g.minElem = x;
            if (g.maxElem < x) g.maxElem = x;

            g.sum += val;
        }
    }

    for (int i = 0; i < (int)groups.size(); ++i) {
        groups[i].avg = groups[i].sum / groups[i].count;
    }

    return groups;
}

template <typename Info>
void printGroups(const std::vector<Info>& groups) {
    for (int i = 0; i < (int)groups.size(); ++i) {
        const Info& g = groups[i];
        std::cout << g.key << ", "
                  << g.count << ", "
                  << g.minElem << ", "
                  << g.maxElem << ", "
                  << g.sum << ", "
                  << g.avg << "\n";
    }
}

int main() {
    int a1[] = {12, 27, 34, 56, 41, 12, 19};
    int n1 = (int)(sizeof(a1) / sizeof(a1[0]));

    auto g1 = groupStats(a1, n1,
        [](int x) { return x % 10; },
        [](int x) { return x; }
    );

    std::cout << "int:\n";
    printGroups(g1);

    double a2[] = {-3.7, 0.0, 2.45, 9.99, 10.0, 10.01, 18.6, -0.4};
    int n2 = (int)(sizeof(a2) / sizeof(a2[0]));

    auto g2 = groupStats(a2, n2,
        [](double x) {
            if (x < 0) return 0;
            if (x <= 10) return 1;
            return 2;
        },
        [](double x) { return x; }
    );

    std::cout << "\ndouble:\n";
    printGroups(g2);

    std::string a3[] = {"dota","zhest","chai","son","kod","clion"
    };
    int n3 = (int)(sizeof(a3) / sizeof(a3[0]));

    auto g3 = groupStats(a3, n3,
        [](const std::string& s) { return s[0]; },
        [](const std::string& s) { return (int)s.size(); }
    );

    std::cout << "\nstring:\n";
    printGroups(g3);


    return 0;
}
