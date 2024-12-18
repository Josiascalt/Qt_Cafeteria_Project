#ifndef ENCODER_H
#define ENCODER_H

#pragma once

#include <string>
#include <cmath>
#include <cstdint>
#include <iterator>
#include <utility>
#include <memory>

namespace encoder {
namespace ascii {
class Item {
public:
    using Type = uint64_t;

    static const int CAPACITY = 9;
    static const int RELATIVE_POSITION = 31;

    Item() = default;

    template <typename InputIter>
    Item(InputIter beg, InputIter end) {
        int step = 0;
        for (; beg != end; beg++) {
            value_ += static_cast<Type>(std::pow(100, step++) * (static_cast<int>(*beg) - RELATIVE_POSITION));
        }
    }

    inline Type GetValue() const {
        return value_;
    }

    inline std::string Decode() const {
        std::string result;
        auto encoded_value = this->GetValue();

        for (int step = 0; step < Item::CAPACITY && encoded_value != 0;) {
            Type step_coeficient = std::pow(100, ++step);
            Type stepped_encoded_char = (encoded_value % step_coeficient);

            result += static_cast<char>(stepped_encoded_char / (step_coeficient / 100) + Item::RELATIVE_POSITION);

            encoded_value -= stepped_encoded_char;
        }

        return result;
    }

private:
    Type value_ = 0;
};

class ItemArray {
public:
    using Data = std::unique_ptr<Item[]>;

    ItemArray() = default;
    ItemArray(Data&& data, size_t size)
        : data_(std::move(data))
        , size_(size)
    {

    }

    inline const Data& GetData() const {
        return data_;
    }

    inline size_t GetSize() const {
        return size_;
    }

    inline std::string Decode() const {
        std::string result;
        result.reserve(size_ * Item::CAPACITY);

        std::string buffer;
        for (size_t index = 0; index < size_; index++) {
            buffer = data_[index].Decode();
            result += buffer;
        }

        return result;
    }

private:
    Data data_ = nullptr;
    size_t size_ = 0;
};


inline static size_t CalcDataSizeInItems(size_t data_size) {
    return std::ceil(data_size / double(Item::CAPACITY));
}

template <typename InputIter>
inline static ItemArray EncodeData(InputIter data_beg, InputIter data_end) {
    if (data_beg == data_end) {
        return ItemArray{};
    }

    const auto items_count = CalcDataSizeInItems(std::distance(data_beg, data_end));
    ItemArray::Data data(new Item[items_count]);

    auto beg = data_beg;
    for (size_t i = 0; i < items_count - 1; i++) {
        auto end = beg + Item::CAPACITY;
        data[i] = Item{ beg, end };
        beg = end;
    }

    data[items_count - 1] = Item{ beg, data_end };

    return ItemArray{ std::move(data), items_count };
}

template <typename InputIter, typename OutputIter>
inline static void EncodeDataInIterable(InputIter data_beg
                                        , InputIter data_end
                                        , OutputIter target
                                        , const size_t target_size) {

    if (data_beg == data_end || target_size == 0) {
        return;
    }

    const auto items_count = CalcDataSizeInItems(std::distance(data_beg, data_end));

    const auto size = std::min(items_count, target_size);

    auto beg = data_beg;
    for (size_t i = 0; i < size - 1; i++) {
        auto end = beg + Item::CAPACITY;
        *target++ = Item{ beg, end };
        beg = end;
    }

    *target = Item{ beg, data_end };
}

template <typename InputIter>
inline static std::string DecodeDataFromIterable(InputIter data_beg, InputIter data_end) {
    std::string result;

    if (data_beg == data_end) {
        return result;
    }

    const auto items_count = std::distance(data_beg, data_end);
    result.reserve(items_count * Item::CAPACITY);

    std::string buffer;
    for (; data_beg != data_end; data_beg++) {
        buffer = data_beg->Decode();
        result += buffer;
    }

    return result;
}
} // namespace ascii
} // namespace encoder
#endif // ENCODER_H
