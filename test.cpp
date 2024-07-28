#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include "huffman_table.h"

using namespace std;

#define ASSERT_EQ(A, B) if (A != B) { cout << "fail: " << A << " != " << B << endl; \
    assert(false); }
#define TEST(X) { X(); }

void TestTableConversion1()
{
    string s = "this is an example of a huffman tree";
    istringstream ss(s);
    HuffmanTable ht(ss);
    struct HFCode { char c; unsigned int occ; string code; };
    vector<HFCode> cmp = { { ' ', 7, "111" },
        { 'a', 4, "010" }, { 'e', 4, "000" }, { 'f', 3, "1101" }, { 'h', 2, "1010" },
        { 'i', 2, "1000" }, { 'm', 2, "0111" }, { 'n', 2, "0010" }, { 's', 2, "1011" },
        { 't', 2, "0110" }, { 'l', 1, "11001" }, { 'o', 1, "00110" }, { 'p', 1, "10011" },
        { 'r', 1, "11000" }, { 'u', 1, "00111" }, { 'x', 1, "10010" } };

    ASSERT_EQ(ht.table.size(), cmp.size()) // number of characters is wrong

    unsigned int cmp_len_sum = 0;
    for (auto &c : cmp) cmp_len_sum += c.code.length();
    unsigned int ht_len_sum = 0;
    for (const auto& line : ht.table) {
        const HuffmanChar hc = line.second;
        ht_len_sum += hc.code.length;
    }
    ASSERT_EQ(cmp_len_sum, ht_len_sum) // sum of all code bits count is wrong

    for (const auto &c : cmp) {
        ASSERT_EQ(c.code.length(), ht.table[c.c].code.length); // count of code bits of some character is wrong
        ASSERT_EQ(c.occ, ht.table[c.c].occurrence); // count of some character occurrence is wrong
    }

    // TODO: test hf.PushToUInt()
}

int main()
{
    TEST(TestTableConversion1)

    cout << "success" << endl;
    return 0;
}
