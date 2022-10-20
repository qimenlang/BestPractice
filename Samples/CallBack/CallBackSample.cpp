#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

int double_int(int x) { return 2 * x; }
int square_int(int x) { return x * x; }

void tranform_every_int(int *v, unsigned n, int (*fp)(int))
{
    for (unsigned i = 0; i < n; ++i)
    {
        v[i] = fp(v[i]);
    }
}

int main()
{
    std::cout << "Call Back Sample" << std::endl;
    // 1.One reason to use callbacks is to write **generic** code which is independant from the logic
    // in the called function and can be reused with different callbacks.
    // for example:`for_each` algorithm applies an unary callback to every item in a range of iterators
    auto print_int = [](int num)
    { std::cout << num << ','; };
    std::vector<int> int_arr = {1, 2, 3, 4, 5, 6, 7};
    for_each(int_arr.begin(), int_arr.end(), print_int);
    // 2.Another application of callbacks is the notification of callers of certain events
    // which enables a certain amount of static / compile time flexibility.
    // 3. Furthermore, callbacks can enable dynamic runtime behaviour.

    // example
    int arr[5] = {1, 2, 3, 4, 5};
    tranform_every_int(&arr[0], 5, double_int);
    for (auto v : arr)
    {
        std::cout << v << ',';
    }
    // now a == {2, 4, 6, 8, 10};
    tranform_every_int(&arr[0], 5, square_int);
    // now a == {4, 16, 36, 64, 100};
}