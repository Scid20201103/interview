#include <vector>
#include <iostream>

std::vector<char*> vs = {
  (char*)"aa",
  (char*)"ccc",
  (char*)"eeeee",
  (char*)"gggggg",
  (char*)"zzzz"
};

// Q1
// 完成用 binary serach 搜尋vector vs, 回傳字串str在vs中的位置, 若未發現則回傳 -1
// 不限使用 C或C++的function
// 但請注意c++ string 與 c char*轉換的消耗, 盡可能以最有效率的方式完成工作,
int bin_search(const std::string& str) {
    const char* cstr = &str[0];
    int left = 0, right = vs.size() - 1, mid, compare_Result;
    while (left <= right) {
        mid = (left + right) / 2;
        compare_Result = strcmp(cstr, vs[mid]);
        if (compare_Result > 0)left = mid + 1;
        else if (compare_Result < 0)right = mid - 1;
        else return mid;
    }
    return -1;
}

int main() {
    std::string key;
    std::cin >> key;
    std::cout << bin_search(key) << std::endl;
    return 0;
}
