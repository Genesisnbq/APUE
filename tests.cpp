#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

//假设这n个数的序号依次为0,1,2,...,n-1,数组名为num
void knuth1(vector< int > pNum, int m, int n)
{
    srand((unsigned int)time(0));
    for (int i = 1; i <= n; i++) {
        if (rand() % (n - i) < m)  // rand()%(n-i)的取值范围是[0, n-i）
        {
            std::cout << pNum[i] << std::endl;
            m--;
        }
    }
}
int main(int argc, char* argv[])
{
    std::vector< int > iv;
    generate_n(std::back_inserter(iv), 5, [] { return rand() % 10; });
    knuth1(iv, 10, 10);
    return 0;
}
