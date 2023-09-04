#include <bits/stdc++.h>
using namespace std;

void reset(void* arr, size_t size, int value) {
    memset(arr, value, size);
}                                             //a function that takes a void*, a number(indicating a number of bytes), and a value(indicating the value to which each byte should be set) as arguments. 
                                            //该函数作用：重置该数组为全0
int main() {
    int num[3] = {1, 2, 3};
    void* arr = static_cast<void*>(num);
    reset(arr, sizeof(num), 0);          //a function that takes a void*,
                                           //a number(indicating a number of bytes), 
                                           //and a value(indicating the value to which each byte should be set) as arguments. 
    for (int i = 0; i < 3; ++i) {
        cout << num[i] << endl;
    }                                     //输出测试，成功
}