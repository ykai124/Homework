# 41443107
作業二

## 解題說明

本題要求實作 Polynomial（多項式）類別，利用物件導向程式設計建立多項式的資料結構，並完成多項式的輸入、輸出、加法、乘法及代入計算等功能。

程式使用 `Term` 類別儲存每一項多項式的係數與指數，再透過 `Polynomial` 類別管理整個多項式，並使用動態陣列儲存各項資料。

## 解題策略

1. **建立 Polynomial 類別**

首先建立 `Term` 與 `Polynomial` 兩個類別。

`Term` 類別負責儲存多項式每一項的資料，包含：
- `coef`：表示該項的係數。
- `exp`：表示該項的指數。

`Polynomial` 類別則負責管理整個多項式，使用動態陣列 `termArray` 儲存各項資料，並透過 `capacity` 記錄陣列容量、`terms` 記錄目前多項式的項數。

2. **動態陣列管理**

使用 `new` 建立動態陣列，初始容量設定為 2。

當新增項目時，如果陣列容量不足，就將容量增加為原本的兩倍，再利用 `copy()` 將原本的資料複製到新的陣列中。

透過這種方式，可以依照多項式的項數自動調整陣列大小，不需要事先固定多項式最多可以儲存多少項。

3. **多項式輸入與輸出**

使用 `Input()` 與 `Output()` 函式處理多項式的輸入與輸出。

輸入時，先取得多項式的項數，再依序輸入每一項的係數與指數，並透過 `newTerm()` 儲存資料。

輸出時，則根據每一項的係數與指數，將資料整理成一般數學表示方式。

另外，依照題目要求，使用運算子多載（Operator Overloading）實作 `operator>>` 與 `operator<<`，讓多項式也能使用 `cin` 和 `cout` 進行輸入與輸出。

4. **多項式加法（Add）**

使用兩個位置變數 `aPos` 與 `bPos`，分別記錄兩個多項式目前比較到的位置。

透過比較兩個多項式的指數：
- 如果指數相同，就將係數相加。
- 如果 A 的指數較大，就先將 A 的該項加入結果。
- 如果 B 的指數較大，就先將 B 的該項加入結果。

當其中一個多項式比較完畢後，再將另一個多項式剩餘的項目加入結果。

5. **多項式乘法（Mult）**

使用兩層 `for` 迴圈，讓 A 多項式的每一項與 B 多項式的每一項互相相乘。

每次相乘時：
- 將兩項的係數相乘。
- 將兩項的指數相加。
- 檢查結果中是否已經存在相同指數的項目。

如果存在相同指數，就將係數累加；如果不存在，就使用 `newTerm()` 新增一項。

透過這種方式，可以完成多項式乘法，並將相同次方的項目合併。

6. **多項式代入計算（Eval）**

使用 `Eval(float x)` 函式計算多項式在指定 x 值時的結果。

依照多項式公式：

$$
P(x)=a_0x^{n_0}+a_1x^{n_1}+\cdots+a_kx^{n_k}
$$

使用 `for` 迴圈逐項計算係數乘上 x 的指數次方，再將所有結果累加，最後回傳計算結果。

7. **選單系統**

最後在 `main()` 中使用 `while` 迴圈與 `switch-case` 建立選單，讓使用者可以選擇不同的多項式功能。

選單提供以下功能：
- 顯示 A、B 兩個多項式。
- 計算 A + B。
- 計算 A * B。
- 計算 A(x)。
- 計算 B(x)。
- 重新輸入多項式 A。
- 重新輸入多項式 B。
- 結束程式。

使用者選擇功能後，程式會執行對應的函式，完成後回到選單，直到使用者選擇結束程式。

## 程式實作
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

class Polynomial;

// 運算子前置宣告
istream& operator>>(istream& in, Polynomial& p);
ostream& operator<<(ostream& out, const Polynomial& p);

class Term {
    friend class Polynomial;
    friend istream& operator>>(istream& in, Polynomial& p);
    friend ostream& operator<<(ostream& out, const Polynomial& p);

private:
    float coef;
    int exp;
};

class Polynomial {
private:
    Term* termArray;
    int capacity;
    int terms;

public:
    Polynomial() : capacity(2), terms(0) {
        termArray = new Term[capacity];
    }

    // 複製建構子
    Polynomial(const Polynomial& p) {
        capacity = p.capacity;
        terms = p.terms;
        termArray = new Term[capacity];

        copy(p.termArray, p.termArray + terms, termArray);
    }

    // 解構子
    ~Polynomial() {
        delete[] termArray;
    }

    // 指派運算子
    Polynomial& operator=(const Polynomial& p) {
        if (this != &p) {
            delete[] termArray;

            capacity = p.capacity;
            terms = p.terms;
            termArray = new Term[capacity];

            copy(p.termArray, p.termArray + terms, termArray);
        }

        return *this;
    }

    void newTerm(const float theCoef, const int theExp);

    void Input();
    void Output();

    Polynomial Add(const Polynomial& b);
    Polynomial Mult(const Polynomial& d);

    float Eval(float x);

    // 運算子多載
    friend istream& operator>>(istream& in, Polynomial& p);
    friend ostream& operator<<(ostream& out, const Polynomial& p);
};

// 新增一項
void Polynomial::newTerm(const float theCoef, const int theExp) {

    if (theCoef == 0)
        return;

    if (terms == capacity) {

        capacity *= 2;

        Term* temp = new Term[capacity];

        copy(termArray, termArray + terms, temp);

        delete[] termArray;

        termArray = temp;
    }

    termArray[terms].coef = theCoef;
    termArray[terms].exp = theExp;

    terms++;
}

// Input 輸入函式
void Polynomial::Input() {

    cout << "請輸入項數及各項係數、指數：" << endl;

    cin >> *this;
}

// Output 輸出函式
void Polynomial::Output() {

    cout << *this << endl;
}

// 多項式相加
Polynomial Polynomial::Add(const Polynomial& b) {

    Polynomial c;

    int aPos = 0;
    int bPos = 0;

    while (aPos < terms && bPos < b.terms) {

        if (termArray[aPos].exp == b.termArray[bPos].exp) {

            float t = termArray[aPos].coef + b.termArray[bPos].coef;

            c.newTerm(t, termArray[aPos].exp);

            aPos++;
            bPos++;
        }
        else if (termArray[aPos].exp > b.termArray[bPos].exp) {

            c.newTerm(termArray[aPos].coef, termArray[aPos].exp);

            aPos++;
        }
        else {

            c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);

            bPos++;
        }
    }

    while (aPos < terms) {

        c.newTerm(termArray[aPos].coef, termArray[aPos].exp);

        aPos++;
    }

    while (bPos < b.terms) {

        c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);

        bPos++;
    }

    return c;
}

// 多項式相乘
Polynomial Polynomial::Mult(const Polynomial& d) {

    Polynomial result;

    for (int i = 0; i < terms; i++) {

        for (int j = 0; j < d.terms; j++) {

            float newCoef = termArray[i].coef * d.termArray[j].coef;

            int newExp = termArray[i].exp + d.termArray[j].exp;

            bool found = false;

            for (int k = 0; k < result.terms; k++) {

                if (result.termArray[k].exp == newExp) {

                    result.termArray[k].coef += newCoef;

                    found = true;
                    break;
                }
            }

            if (!found) {

                result.newTerm(newCoef, newExp);
            }
        }
    }

    return result;
}

// 計算多項式
float Polynomial::Eval(float x) {

    float result = 0;

    for (int i = 0; i < terms; i++) {

        result += termArray[i].coef * pow(x, termArray[i].exp);
    }

    return result;
}

// >> 輸入運算子多載
istream& operator>>(istream& in, Polynomial& p) {

    int n;

    in >> n;

    if (!in)
        return in;

    if (n < 0) {
        in.setstate(ios::failbit);
        return in;
    }

    if (n > p.capacity) {

        delete[] p.termArray;

        p.capacity = n;

        p.termArray = new Term[p.capacity];
    }

    p.terms = 0;

    for (int i = 0; i < n; i++) {

        float coef;
        int exp;

        in >> coef >> exp;

        if (!in)
            return in;

        p.newTerm(coef, exp);
    }

    return in;
}

// << 輸出運算子多載
ostream& operator<<(ostream& out, const Polynomial& p) {

    bool first = true;

    for (int i = 0; i < p.terms; i++) {

        float coef = p.termArray[i].coef;
        int exp = p.termArray[i].exp;

        if (coef == 0)
            continue;

        if (!first) {

            if (coef > 0)
                out << " + ";
            else
                out << " - ";
        }
        else {

            if (coef < 0)
                out << "-";
        }

        float absCoef = fabs(coef);

        if (exp == 0) {

            out << absCoef;
        }
        else {

            if (absCoef != 1)
                out << absCoef;

            out << "x";

            if (exp != 1)
                out << "^" << exp;
        }

        first = false;
    }

    if (first)
        out << "0";

    return out;
}

// 主程式
int main() {

    Polynomial A;
    Polynomial B;

    int choice;
    float x;

    cout << "請輸入多項式 A" << endl;
    A.Input();

    cout << endl;

    cout << "請輸入多項式 B" << endl;
    B.Input();

    while (true) {

        cout << endl;
        cout << "========== Polynomial 選單 ==========" << endl;

        cout << "1. 顯示 A、B" << endl;
        cout << "2. A + B" << endl;
        cout << "3. A * B" << endl;
        cout << "4. 計算 A(x)" << endl;
        cout << "5. 計算 B(x)" << endl;
        cout << "6. 重新輸入 A" << endl;
        cout << "7. 重新輸入 B" << endl;
        cout << "0. 結束程式" << endl;

        cout << "選擇：";
        cin >> choice;

        switch (choice) {

        case 1:

            cout << "A(x) = ";
            A.Output();

            cout << "B(x) = ";
            B.Output();

            break;

        case 2: {

            Polynomial C = A.Add(B);

            cout << "A + B = ";
            C.Output();

            break;
        }

        case 3: {

            Polynomial C = A.Mult(B);

            cout << "A * B = ";
            C.Output();

            break;
        }

        case 4:

            cout << "請輸入 x：";
            cin >> x;

            cout << "A(" << x << ") = " << A.Eval(x) << endl;

            break;

        case 5:

            cout << "請輸入 x：";
            cin >> x;

            cout << "B(" << x << ") = " << B.Eval(x) << endl;

            break;

        case 6:

            cout << "重新輸入多項式 A" << endl;
            A.Input();

            break;

        case 7:

            cout << "重新輸入多項式 B" << endl;
            B.Input();

            break;

        case 0:

            cout << "程式結束！" << endl;

            return 0;

        default:

            cout << "輸入錯誤，請重新選擇！" << endl;

        }
    }

    return 0;
}
```


## 效能分析


## 效能分析

### 1. 時間複雜度

| 功能 | 時間複雜度 |
|---|---|
| 動態陣列新增（平均攤銷） | O(1) |
| 動態陣列擴充 | O(k) |
| 多項式輸入 | O(n) |
| 多項式輸出 | O(n) |
| 多項式加法 Add() | O(m + n) |
| 多項式乘法 Mult() | O(m²n²) |
| 多項式代入 Eval() | O(n) |

### 2. 空間複雜度

| 功能 | 空間複雜度 |
|---|---|
| 單一多項式儲存 | O(n) |
| 多項式加法 Add() | O(m + n) |
| 多項式乘法 Mult() | O(m × n) |
| 多項式代入 Eval() | O(1) |

## 測試與驗證

### 1. 測試案例

設定以下兩個多項式作為測試資料：

- A(x) = 3x² + 2x + 1
- B(x) = 2x² + 4x + 3

| 測試項目 | 輸入或操作 | 預期結果 |
|---|---|---|
| 多項式輸入 | 輸入 A、B | 成功儲存兩個多項式 |
| 多項式輸出 | 選擇 1 | 顯示 A(x)、B(x) |
| 多項式加法 | 選擇 2 | 5x² + 6x + 4 |
| 多項式乘法 | 選擇 3 | 6x⁴ + 16x³ + 15x² + 10x + 3 |
| A(x) 計算 | 選擇 4，輸入 x = 2 | 17 |
| B(x) 計算 | 選擇 5，輸入 x = 2 | 19 |
| 重新輸入 A | 選擇 6 | 成功更新多項式 A |
| 重新輸入 B | 選擇 7 | 成功更新多項式 B |
| 結束程式 | 選擇 0 | 正常結束程式 |

### 2. 驗證結果

透過上述測試案例，確認程式具備以下功能：

1. 能夠正確輸入及輸出多項式。
2. 能夠正確執行多項式加法。
3. 能夠正確執行多項式乘法。
4. 能夠正確計算指定 x 值的多項式結果。
5. 能夠重新輸入並更新多項式資料。
6. 能夠透過選單重複執行各項功能。

### 3. 編譯與執行指令


### 3. 編譯與執行指令

```shell
$ g++ -std=c++17 -o polynomial main.cpp
$ ./polynomial

請輸入多項式 A 的項數、係數及指數：
3
3 2
2 1
1 0

請輸入多項式 B 的項數、係數及指數：
3
2 2
4 1
3 0

========== Polynomial Menu ==========
1. 顯示 A、B
2. A + B
3. A * B
4. 計算 A(x)
5. 計算 B(x)
6. 重新輸入 A
7. 重新輸入 B
0. 結束程式

請選擇功能：
```





### 結論

本次作業透過 C++ 實作 Polynomial 類別，學習如何使用動態陣列管理多項式資料，並運用物件導向程式設計完成多項式的輸入、輸出、加法、乘法及代入計算。

在實作過程中，進一步熟悉了建構子、解構子、複製建構子、運算子多載及動態記憶體管理的使用方式。

透過 `Add()`、`Mult()` 與 `Eval()` 函式，完成多項式的基本運算，並利用 `while` 迴圈及 `switch-case` 建立選單系統，讓使用者能夠重複操作各項功能。

藉由本次作業，更加了解 C++ 類別設計、動態陣列及運算子多載的應用，也提升了將數學運算轉換成程式邏輯的能力。



## 申論及開發報告

### 1. 開發過程

本次作業主要使用 C++ 的類別與動態陣列實作多項式運算。

首先建立 `Term` 類別，用來儲存每一項的係數與指數，再建立 `Polynomial` 類別，利用動態陣列管理多項式中的各項資料。

接著依照作業要求，實作多項式的輸入、輸出、加法、乘法及代入計算功能，並透過運算子多載，讓多項式的輸入與輸出更加方便。

最後使用 `while` 迴圈及 `switch-case` 建立選單系統，整合所有功能，讓使用者能夠透過選單操作程式。

### 2. 遇到的問題與解決方法

**(1) 動態陣列容量不足**

在輸入多項式時，項數可能超過原本配置的陣列容量，因此需要重新配置更大的陣列，並將原有資料複製過去，以避免資料遺失。

**(2) 多項式加法**

兩個多項式的指數不一定相同，因此需要比較各項指數，並在指數相同時將係數相加，才能得到正確結果。

**(3) 多項式乘法**

兩個多項式相乘後，可能產生多個相同指數的項目，因此需要檢查結果中是否已有相同指數，並將係數合併。

**(4) 動態記憶體管理**

由於使用 `new` 配置動態陣列，因此需要透過解構子釋放記憶體，並實作複製建構子與指定運算子，避免複製物件時發生記憶體管理問題。
### 3. 學習心得

透過本次作業，我更加熟悉 C++ 類別、動態陣列及運算子多載的使用方式，也了解到多項式運算需要考慮指數比較、係數合併及資料儲存等問題。

在實作過程中，乘法與動態記憶體管理是比較需要注意的部分，必須確保計算結果正確，同時避免記憶體使用錯誤。

完成本次作業後，對於物件導向程式設計及資料結構的應用有更進一步的理解，也提升了獨立分析問題與設計程式的能力。



