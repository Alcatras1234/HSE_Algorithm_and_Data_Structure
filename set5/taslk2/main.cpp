#include <iostream>
#include <string>
#include <vector>
#include <functional>


class BloomFilter {
public:
    BloomFilter() : hashes_(0), bits_(0), numOfInsertedItems(0), falsePositiveCount(0), totalVerifyRequests(0) {}
    BloomFilter(size_t hashes, size_t maxBits) : hashes_(hashes), numOfInsertedItems(0), falsePositiveCount(0), totalVerifyRequests(0), bitArray(bits_, false) {
    }

    ~BloomFilter() = default;

    void add(const std::string& str) {
        for (size_t i = 0; i < hashes_; ++i) {
            size_t index = hash(str, i) % bitArray.size();
            bitArray[index] = true;
        }
    }

    bool verify(const std::string &obj) {
        ++totalVerifyRequests;
        for (auto h : hashFunctions) {
            size_t index = h(obj);
            if (!bitArray[index]) {
                ++falsePositiveCount;
                return false;
            }
        }
        return true;
    }

    double getFPRate() const {
        if (totalVerifyRequests == 0)
            return 0.0;
        return static_cast<double>(falsePositiveCount) / static_cast<double>(totalVerifyRequests);
    }

    size_t numberOfHashFunctions() const {
        return hashes_;
    }
    size_t numberOfBits() const {
        return bits_;
    }

private:
    size_t hash(const std::string& str, size_t hashNum) const {
        std::hash<std::string> hasher;
        return hasher(str + std::to_string(hashNum));
    }
    std::vector<bool> bitArray;
    std::vector<std::function<size_t(const std::string&)>> hashFunctions;
    size_t numOfInsertedItems;
    size_t falsePositiveCount;
    size_t totalVerifyRequests;
    size_t hashes_;
    size_t bits_;
};