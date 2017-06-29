// --------------------------------------------------------------------------------------------
// Chapter 13.1.1
// --------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()):
        ps_(new std::string(s)),
        i_(0)
    { cout << "HasPtr::HasPtr()\n"; }

    HasPtr(const HasPtr& rhs):
        ps_ {new std::string(*rhs.ps_)},
        i_ {rhs.i_}
    { cout << "HasPtr::HasPtr(const& HasPtr)\n"; }

    HasPtr& operator=(const HasPtr& rhs)
    {
        { cout << "HasPtr::operator=(const& HasPtr)\n"; }
        if (this != &rhs) {
            if (ps_)
                delete ps_;
            ps_ = new std::string(*rhs.ps_);
            i_ = rhs.i_;
        }
        return *this;
    }

    ~HasPtr()
    {
        { cout << "HasPtr::~HasPtr()\n"; }
        if (ps_)
            delete ps_;
    }

    int i() const
    {
        return i_;
    }

private:
    std::string *ps_;
    int i_;
};

void foo(HasPtr h)
{
    { cout << "HasPtr::foo(): i: " << h.i() << endl; }
}

void goo(const HasPtr& h)
{
    { cout << "HasPtr::goo(): i: " << h.i() << endl; }
}

int main(int argc, char *argv[])
{
#if 0
    HasPtr h1;      // direct initialization

    HasPtr h2 = h1; // copy initialization

    h1 = h2;        // copy assignment
#endif

    HasPtr h1;

//    foo(h1);
//    goo(h1);

    using HpVec = vector<HasPtr>;

    HpVec hv;

    hv.push_back(h1);

    return 0;
}
#endif

// --------------------------------------------------------------------------------------------
// lvalue/rvalue, references
// --------------------------------------------------------------------------------------------
#if 0
#include <vector>
#include <string>
#include <iostream>

template<typename T>
class Type_display;

int global_i = 456;

int f_ret_rval()
{
    return 123;
}

int f1(int i_param)
{
#if 0
    Type_display<decltype(i_param)> type_f_param;                             // lvalue
#endif

    int &i_l_param = i_param;

    return 0;
}

int& f_ret_lval()
{
    return global_i;
}

int main(int argc, char *argv[])
{
    int i = 24;
    const int ci = 42;
    int &r = i;

    int *pi = &i;

    auto x = ci;
    auto y = &ci;
    const auto &z = r;

    std::vector<int> v;
    std::string s;
    auto v_it = v.begin();
    auto s_it = s.begin();
#if 0
    Type_display<decltype(i)> type_var;                             // lvalue
    Type_display<decltype(i+0)> type_arithm_plus;                   // rvalue
    Type_display<decltype(i=33)> type_assignment;                   // lvalue
    Type_display<decltype(*pi)> type_dereference;                   // lvalue
    Type_display<decltype(&i)> type_address_of;                     // rvalue
    Type_display<decltype(v[0])> type_vector_subscript;             // lvalue
    Type_display<decltype(s[0])> type_string_subscript;             // lvalue
    Type_display<decltype(++v_it)> type_vector_prefix;              // lvalue
    Type_display<decltype(++s_it)> type_string_prefix;              // lvalue
    Type_display<decltype(v_it++)> type_vector_postfix;             // rvalue
    Type_display<decltype(s_it++)> type_string_postfix;             // rvalue
    Type_display<decltype(f_ret_rval())> type_f_ret_rval;           // rvalue
    Type_display<decltype(f_ret_lval())> type_f_ret_lval;           // lvalue

    Type_display<decltype(x)> type_x;
    Type_display<decltype(y)> type_y;
    Type_display<decltype(z)> type_z;
#endif

    int &l_assignment = (i = 55);
    std::cout << "i: " << i << ", l_assignment: " << l_assignment << endl;

    int &&r_plus = i + 1;
    std::cout << "r_plus: " << r_plus << endl;

    int &l_deref = *pi;
    std::cout << "l_deref: " << l_deref << endl;

    int &&l_f_ret_rval = f_ret_rval();
    std::cout << "l_f_ret_rval: " << l_f_ret_rval << endl;

    f_ret_lval() = 789;
    int &l_f_ret_lval = f_ret_lval();
    std::cout << "l_f_ret_lval: " << l_f_ret_lval << endl;

    int &&r_address_of = reinterpret_cast<long>(&i);

    return 0;
}
#endif

// --------------------------------------------------------------------------------------------
// template type deduction
// --------------------------------------------------------------------------------------------
#include <iostream>
#include <utility>

template<typename T>
void f(T param);

template<typename T>
void f_ref(T &param);

template<typename T>
void f_constref(const T &param);

template<typename T>
void f_ptr(T *param);

template<typename T>
void f_rref(T &&param);

int main(int argc, char *argv[])
{
    int i;
    const int ci = 123;
    int &l_i = i;
    const int &l_ci = 456;
    int *p_i = &i;
    const int *const cp_ci = &i;
    int a[10];
    const int *p_ci = &i;

    f(i);                   // int,     int
    f(ci);                  // int,     int
    f(l_i);                 // int,     int
    f(l_ci);                // int,     int
    f(p_i);                 // int*,    int*
    f(cp_ci);               // const int*, const int*
    f(*p_i);                // int,     int
    f(a);                   // int*,    int*

    f_ref(i);               // int,         int&
    f_ref(ci);              // const int,   const int&
    f_ref(l_i);             // int,         int&
    f_ref(l_ci);            // const int,   const int&
    f_ref(p_i);             // int*,        int*&
    f_ref(*p_i);            // int,         int&
    f_ref(a);               // int [10],    int (&) [10]    -> ???

    f_constref(i);          // int,         const int&
    f_constref(ci);         // int,         const int&
    f_constref(l_i);        // int,         const int&
    f_constref(l_ci);       // int,         const int&
    f_constref(p_i);        // int*,        int* const&
    f_constref(*p_i);       // int,         const int&
    f_constref(a);          // int [10],    int const (&) [10]
    f_constref(123);        // int,         const int&

    f_ptr(p_i);              // int,         int*
    f_ptr(p_ci);             // const int,   const int*

    f_rref(i);               // int&,        int&
    f_rref(ci);              // const int&,  const int&
    f_rref(l_i);             // int&,        int&
    f_rref(l_ci);            // const int&,  const int&
    f_rref(p_i);             // int*&,       int*&
    f_rref(*p_i);            // int&,        int&
    f_rref(123);             // int,         int&&
    f_rref(std::move(i));    // int,         int&&

    return 0;
}
