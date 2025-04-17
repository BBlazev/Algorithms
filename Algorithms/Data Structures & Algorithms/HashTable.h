#pragma once
#include <vector>
#include <list>
#include <utility>      
#include <functional>   
#include <stdexcept>    
#include <cstddef>      

template<
    typename Key,
    typename Value,
    typename Hasher = std::hash<Key>,
    typename KeyEqual = std::equal_to<Key>
>
class HashTable {
public:
    using KeyValuePair = std::pair<Key, Value>;
    using BucketList = std::list<KeyValuePair>;

    explicit HashTable(
        std::size_t initialBucketCount = 16,
        double      maxLoad = 1.0
    )
        : buckets_(initialBucketCount),
        maxLoad_(maxLoad),
        elementCount_(0)
    {}

    // capacity
    bool IsEmpty() const noexcept { return elementCount_ == 0; } //Complexity: O(1)
    std::size_t Size() const noexcept { return elementCount_; } //Complexity: O(1)

    // insert or update
    // average O(1), worst-case O(n) if all keys collide into one bucket
    void InsertOrUpdate(const Key& key, const Value& value) {
        // resize if load > max
        if (static_cast<double>(elementCount_ + 1) / buckets_.size() > maxLoad_) {
            ResizeBuckets(buckets_.size() * 2);
        }

        BucketList& bucket = GetBucketForKey(key);
        for (auto& kv : bucket) {
            if (keyEquals_(kv.first, key)) {
                kv.second = value;  // update
                return;
            }
        }
        // not found → append
        bucket.emplace_back(key, value);
        ++elementCount_;
    }

    // erase key
    bool RemoveKey(const Key& key) {
        BucketList& bucket = GetBucketForKey(key);
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (keyEquals_(it->first, key)) {
                bucket.erase(it);
                --elementCount_;
                return true;
            }
        }
        return false;
    }

    // lookup (throws if missing)
    Value& GetValue(const Key& key) {
        BucketList& bucket = GetBucketForKey(key);
        for (auto& kv : bucket) {
            if (keyEquals_(kv.first, key))
                return kv.second;
        }
        throw std::out_of_range("Key not found in hash table");
    }
    const Value& GetValue(const Key& key) const {
        return const_cast<HashTable*>(this)->GetValue(key);
    }

    // lookup or default‑insert
    Value& GetOrInsert(const Key& key) {
        BucketList& bucket = GetBucketForKey(key);
        for (auto& kv : bucket) {
            if (keyEquals_(kv.first, key))
                return kv.second;
        }
        // might need to grow before inserting
        if (static_cast<double>(elementCount_ + 1) / buckets_.size() > maxLoad_) {
            ResizeBuckets(buckets_.size() * 2);
        }
        BucketList& newBucket = GetBucketForKey(key);
        newBucket.emplace_back(key, Value{});
        ++elementCount_;
        return newBucket.back().second;
    }

    // existence check
    bool ContainsKey(const Key& key) const {
        const BucketList& bucket = GetBucketForKey(key);
        for (auto& kv : bucket) {
            if (keyEquals_(kv.first, key))
                return true;
        }
        return false;
    }

private:
    std::vector<BucketList> buckets_;
    Hasher                  hasherFunction_;
    KeyEqual                keyEquals_;
    double                  maxLoad_;
    std::size_t             elementCount_;

    std::size_t ComputeBucketIndex(const Key& key) const {
        return hasherFunction_(key) % buckets_.size();
    }
    BucketList& GetBucketForKey(const Key& key) {
        return buckets_[ComputeBucketIndex(key)];
    }
    const BucketList& GetBucketForKey(const Key& key) const {
        return buckets_[ComputeBucketIndex(key)];
    }

    void ResizeBuckets(std::size_t newBucketCount) {
        std::vector<BucketList> newBuckets(newBucketCount);
        for (auto& bucket : buckets_) {
            for (auto& kv : bucket) {
                std::size_t idx = hasherFunction_(kv.first) % newBucketCount;
                newBuckets[idx].emplace_back(std::move(kv));
            }
        }
        buckets_.swap(newBuckets);
    }
};
