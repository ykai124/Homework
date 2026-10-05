#include <iostream>
using namespace std;
int AckermannRecursive(int m, int n)// 遞迴版本
{
    if (m == 0)
    {
        return n + 1;
    }
    else if (n == 0)
    {
        return AckermannRecursive(m - 1, 1);
    }
    else
    {
        return AckermannRecursive(m - 1, AckermannRecursive(m, n - 1));
    }
}
int AckermannNonRecursive(int m, int n)// 非遞迴版本
{
    int stack[10000];
    int top = -1;

    stack[++top] = m;

    while (top >= 0)
    {
        m = stack[top--];

        if (m == 0)
        {
            n = n + 1;
        }
        else if (n == 0)
        {
            n = 1;
            stack[++top] = m - 1;
        }
        else
        {
            stack[++top] = m - 1;
            stack[++top] = m;
            n = n - 1;
        }
    }

    return n;
}

int main()
{
    int m, n;
    cout << "請輸入 m 和 n：";
    cin >> m >> n;
    cout << "遞迴結果：" << AckermannRecursive(m, n) << endl;
    cout << "非遞迴結果：" << AckermannNonRecursive(m, n) << endl;
    return 0;
}
