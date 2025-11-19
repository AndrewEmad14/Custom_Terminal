#include "CustomString.h"
#include <iostream>

int main() {
    std::cout << "\n--- Testing str_length ---\n";
    char test1[] = "Hello";
    char test2[] = "";
    char test3[] = "A";
    std::cout << "Length of \"Hello\": " << str_length(test1) << " (should be 5)\n";
    std::cout << "Length of \"\": " << str_length(test2) << " (should be 0)\n";
    std::cout << "Length of \"A\": " << str_length(test3) << " (should be 1)\n";

    std::cout << "\n--- Testing str_compare ---\n";
    char a1[] = "abc";
    char a2[] = "abc";
    char b1[] = "ab";
    char c1[] = "abcd";
    char d1[] = "abd"; // same length as "abc" but different letters

    std::cout << "Compare \"abc\" vs \"abc\": " << str_compare(a1, a2) << " (should be 0)\n";
    std::cout << "Compare \"ab\" vs \"abc\": " << str_compare(b1, a1) << " (should be 1)\n";
    std::cout << "Compare \"abc\" vs \"ab\": " << str_compare(a1, b1) << " (should be -1)\n";
    std::cout << "Compare \"abc\" vs \"abcd\": " << str_compare(a1, c1) << " (should be 1)\n";
    std::cout << "Compare \"abc\" vs \"abd\": " << str_compare(a1, d1) << " (depends on sum logic)\n";

    std::cout << "\n--- Testing toLower ---\n";
    char lowerTest[] = "HeLLo!";
    std::cout << "Before toLower: " << lowerTest << "\n";
    toLower(lowerTest);
    std::cout << "After toLower:  " << lowerTest << " (should be \"hello!\")\n";

    std::cout << "\n--- Testing toUpper ---\n";
    char upperTest[] = "WoRlD123";
    std::cout << "Before toUpper: " << upperTest << "\n";
    toUpper(upperTest);
    std::cout << "After toUpper:  " << upperTest << " (should be \"WORLD123\")\n";

    std::cout << "\n--- Testing str_copy ---\n";
    char source[] = "HelloThere";
    char dest1[20] = ""; // big enough
    char dest2[5] = "";  // too small

    bool ok1 = str_copy(source, dest1, 20);
    std::cout<<"The string that will be copied is : HelloThere"<<std::endl;
    std::cout << "Copy to large buffer: " << (ok1 ? "Success" : "Failed") << "\n";
    std::cout << "Copied string: \"" << dest1 << "\" (should be \"HelloThere\")\n";

    bool ok2 = str_copy(source, dest2, 5);
    std::cout << "Copy to small buffer: " << (ok2 ? "Success" : "Failed") << " (should be Failed)\n";

    std::cout << "\n--- Testing str_concatinate ---\n";
    char base1[50] = "Hello";
    char base2[10] = "Hi"; // too small for full concat
    char add[] = " World!";

    bool concat1 = str_concatinate(base1, add, 50);
    std::cout<<"The string that will be concatinate is : Hello , World"<<std::endl;
    std::cout << "Concat (enough space): " << (concat1 ? "Success" : "Failed") << "\n";
    std::cout << "Result: \"" << base1 << "\" (should be \"Hello World!\")\n";


    std::cout<<"The string that will be concatinate is : Hi , World"<<std::endl;

    bool concat2 = str_concatinate(base2, add, 10);
    std::cout << "Concat (not enough space): " << (concat2 ? "Success" : "Failed") << " (should be Failed)\n";

    return 0;
}
