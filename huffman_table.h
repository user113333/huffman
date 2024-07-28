#pragma once

#include <istream>
#include <unordered_map>
#include <string>

struct HuffmanCode
{
    unsigned int code;
    int length;

    HuffmanCode() = default;
    HuffmanCode(const std::string& s);

    std::string String() const;
    int PushToUInt(unsigned int& x, int x_len, int skip) const;
};

// TODO: get rid of this struct
struct HuffmanChar
{
    unsigned int occurrence;
    char ascii;
    HuffmanCode code;

    HuffmanChar() = default;
    bool operator<(const HuffmanChar& r) const;
};

struct HuffmanTable
{
    // std::map<uint32_t, uint32_t> input_stats;
    // std::unordered_map<uint32_t, HuffmanCode> table;
    // TODO: transform bottom to top
    std::unordered_map<unsigned int, HuffmanChar> table;

    HuffmanTable() = delete;
    HuffmanTable(std::istream& is);

    void Print() const;
};
