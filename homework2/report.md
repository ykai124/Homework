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



## 效能分析

1. **時間複雜度：**程式的時間複雜度為 $O(A(m,n))$。
2. **空間複雜度：**程式的空間複雜度為 $O(D(m,n))$（遞迴版本）與 $O(1)$（非遞迴版本）。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $m$ | 輸入參數 $n$ | 預期輸出 | 遞迴實際輸出 | 非遞迴實際輸出 |
| ---- | -------- | -------- | ---- | ------ | ------- |
| 測試一  | $m=0$    | $n=0$    | 1    | 1      | 1       |
| 測試二  | $m=0$    | $n=5$    | 6    | 6      | 6       |
| 測試三  | $m=1$    | $n=3$    | 5    | 5      | 5       |
| 測試四  | $m=2$    | $n=3$    | 9    | 9      | 9       |
| 測試五  | $m=3$    | $n=4$    | 125  | 125    | 125     |

### 驗證結果

由測試結果可以確認，遞迴版本與非遞迴版本在相同輸入參數下皆得到相同的結果，表示非遞迴版本使用 Stack 模擬遞迴的方式正確。
其中 $A(3,4)=125$，可以用來驗證兩種實作方式在較複雜的遞迴情況下仍能得到相同結果。

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o ackermann ackermann.cpp
$ ./ackermann
3 4
遞迴結果：125
非遞迴結果：125
```


### 結論

1. 程式能正確計算 Ackermann 函數 $A(m,n)$，並得到正確結果。
2. 遞迴版本與非遞迴版本在相同輸入參數下皆能得到相同結果，表示兩種實作方式皆符合預期。
3. 測試案例涵蓋了 $m=0$、$n=0$ 以及一般遞迴情況，驗證程式的正確性。
4. 非遞迴版本透過 Stack 模擬遞迴過程，可以在不使用函數遞迴的情況下完成 Ackermann 函數的計算。

## 申論及開發報告

### 選擇遞迴與非遞迴兩種方法的原因

本程式同時使用遞迴與非遞迴兩種方式計算 Ackermann 函數，主要是為了比較兩種不同的實作方式。

#### 1. 遞迴版本的優點

**程式邏輯簡單直觀**

Ackermann 函數本身就是以遞迴方式定義，因此可以直接依照數學公式撰寫程式。

例如：

$$
A(m,n)=A(m-1,A(m,n-1))
$$

可以直接對應到程式：

```cpp
return AckermannRecursive(m - 1,
                          AckermannRecursive(m, n - 1));
```

這種寫法與數學定義非常接近，因此程式碼較容易理解。

**容易表達遞迴的概念**

每一次函數呼叫都會將原本的問題拆解成更小的問題，直到符合基本條件後再逐層返回結果，因此適合用來學習遞迴的運作方式。

#### 2. 非遞迴版本的優點

非遞迴版本不直接呼叫自己，而是利用陣列建立 Stack，模擬遞迴過程中系統所使用的 Call Stack。

這種方法可以讓程式自行管理尚未完成的計算工作，了解遞迴背後實際的堆疊運作方式。

例如，原本由系統自動管理的函數呼叫：

```text
Ackermann
    ↓
Ackermann
    ↓
Ackermann
```

在非遞迴版本中改由：

```text
Stack Push
    ↓
Stack Pop
    ↓
Stack Push
    ↓
Stack Pop
```

進行模擬。

#### 3. 兩種方法的比較

遞迴版本的程式碼較簡潔，而且與 Ackermann 函數的數學定義直接對應，因此容易理解與實作。

非遞迴版本雖然程式較複雜，但可以了解如何利用 Stack 將遞迴轉換成迭代方式，並避免直接使用系統的遞迴 Call Stack。

兩種方法的時間複雜度皆非常高，因為 Ackermann 函數本身具有極快的成長速度。因此實際測試時只能使用較小的 $m$ 與 $n$ 值。

透過本次實作，可以了解遞迴函數的運作方式，以及如何利用 Stack 將遞迴演算法轉換成非遞迴演算法。

