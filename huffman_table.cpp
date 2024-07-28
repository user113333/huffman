#include "huffman_table.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Leaf
{
    unsigned int occ;
    char ascii;
    string huffman;
};

struct Node
{
    int weight;
    vector<Leaf> leaves;
};

struct NodeCmp
{
    bool operator()(const Node& l, const Node& r) {
        if (l.weight == r.weight) {
            return l.leaves.size() < r.leaves.size();
        }
        return l.weight > r.weight;
    }
};

// is valid char
static bool isvchr(int chr)
{
    return isprint(chr) || chr == '\n';
}

// ===== HuffmanCode ==========

HuffmanCode::HuffmanCode(const string& s)
{
    length = s.length();
    code = 0;
    for (char c : s) {
        code = code << 1;
        if (c == '1') code |= 1;
    }
}

// returns: bit representation of code in string format
string HuffmanCode::String() const
{
    string s;
    for (int i = length; i > 0; i--) {
        if ((code & (1 << (i - 1))) > 0) s += "1";
        else s += "0";
    }
    return s;
}

const unsigned int uint_size = 8*sizeof(unsigned int); // int bits

// returns: number of bits that fit
int HuffmanCode::PushToUInt(unsigned int& x, int x_len, int skip) const
{
    unsigned int tcode = code; // temporary code
	int n = length - skip; // current length
	if (n > uint_size - x_len) {
		n = uint_size - x_len; // take as many bits as you can
	}
    // clear the start bits that are requested to be skipped
    {
        unsigned int skipand = 1 << skip;
        skipand--;
        skipand = skipand << (length - skip);
        skipand = ~skipand;
        tcode |= skipand;
    }
    tcode |= (((1 << skip) - 1) << (length - skip));
    tcode = tcode >> (length - n); // squash the end unused end bits
    tcode = tcode << (uint_size - (n + x_len)); // position for AND operation right of x bits
    x |= tcode; // AND operation
    return n;
}

// ===== HuffmanChar ==========

bool HuffmanChar::operator<(const HuffmanChar& r) const
{
    if (occurrence == r.occurrence) {
        if (code.length == r.code.length) {
            return ascii < r.ascii;
        }
        return code.length > r.code.length;
    }
    return occurrence < r.occurrence;
}

// ===== HuffmanTable ==========

HuffmanTable::HuffmanTable(istream& is)
{
    unordered_map<char, unsigned int> occ;
    char input;
    while (is.get(input)) {
        if (!isvchr(input)) continue;
        occ[input]++;
    }

    priority_queue<Node, vector<Node>, NodeCmp> pq;
    for (auto const& [chr, occ] : occ) {
        Leaf l = { occ, chr, "" };
        Node n;
        n.weight = occ;
        n.leaves.push_back(l);
        pq.push(n);
    }
    while (pq.size() > 1) {
        Node r = pq.top();
        pq.pop();
        Node l = pq.top();
        pq.pop();
        Node n;
        n.weight = r.weight + l.weight;
        for (auto x : r.leaves) {
            x.huffman.insert(0, "0");
            n.leaves.push_back(x);
        }
        for (auto x : l.leaves) {
            x.huffman.insert(0, "1");
            n.leaves.push_back(x);
        }
        pq.push(n);
    }
    const vector<Leaf>& leaves = pq.top().leaves;
    for (const auto& x : leaves) {
        table[x.ascii] = { x.occ, x.ascii, HuffmanCode(x.huffman) };
    }
}

void HuffmanTable::Print() const
{
    cout << "ascii | occurrence | huffman code" << endl;
    cout << "------|------------|-------------" << endl;
    vector<HuffmanChar> hcs;
    for (const auto& [key, hc] : table) {
        hcs.push_back(hc);
    }
    sort(hcs.begin(), hcs.end());
    reverse(hcs.begin(), hcs.end());
    for (const auto& hc : hcs) {
        cout << setw(5) << left;

        if (hc.ascii == '\n') cout << "\\n";
        else if (hc.ascii == ' ') cout << "' '";
        else cout << hc.ascii;

        cout << " | ";
        cout << setw(10) << hc.occurrence;
        cout << " | ";
        cout << hc.code.String() << endl;
    }
}
