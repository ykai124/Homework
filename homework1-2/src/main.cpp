#include <iostream>

using namespace std;

void PowerSet(char set[], char subset[], int n, int index, int size)
{
    if (index == n)
    {
        cout << "{";

        for (int i = 0; i < size; i++)
        {
            cout << subset[i];

            if (i < size - 1)
            {
                cout << ",";
            }
        }

        cout << "}" << endl;

        return;
    }

    // 不選目前的元素
    PowerSet(set, subset, n, index + 1, size);

    // 選目前的元素
    subset[size] = set[index];
    PowerSet(set, subset, n, index + 1, size + 1);
}

int main()
{
    char set[] = {'a', 'b', 'c'};
    char subset[10];

    int n = 3;

    PowerSet(set, subset, n, 0, 0);

    return 0;
}
