#include "huffman_table.h"

#include <iostream>

using namespace std;

int main()
{
    // TODO: cin to string to istream
    HuffmanTable ht = HuffmanTable(cin);
    ht.Print();
    return 0;
}
