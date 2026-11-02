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
