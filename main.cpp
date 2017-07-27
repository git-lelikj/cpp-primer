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
#if 0
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
#endif

// --------------------------------------------------------------------------------------------
// auto/decltype
// --------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <utility>

template<typename T>
class Type_display;

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

    auto a_i = i;
    auto a_ci = ci;
    auto a_li = l_i;
    auto a_l_ci = l_ci;
    auto a_pi = p_i;
    auto a_arr = a;

    auto &a_lr_i = i;
    auto &a_lr_arr = a;

    auto a_parentheses = (i);

    auto a_literal = 123;
    auto a_str_literal = "ladenzon";
    auto &&a_rr_literal = 123;
    auto &a_lr_str_literal = "ladenzon";

    Type_display<decltype(a_i)> type_a_i;
    Type_display<decltype(a_ci)> type_a_ci;
    Type_display<decltype(a_li)> type_a_li;
    Type_display<decltype(a_l_ci)> type_a_l_ci;
    Type_display<decltype(a_pi)> type_a_pi;
    Type_display<decltype(a_arr)> type_a_arr;

    Type_display<decltype(a_lr_i)> type_a_lr_i;
    Type_display<decltype(a_lr_arr)> type_a_lr_arr;

    Type_display<decltype(a_parentheses)> type_a_parenth;
    Type_display<decltype((i))> type_d_parenth;

    Type_display<decltype(a_literal)> type_a_literal;
    Type_display<decltype(a_str_literal)> type_a_str_literal;
    Type_display<decltype(a_rr_literal)> type_a_rr_literal;
    Type_display<decltype(a_lr_str_literal)> type_a_lr_str_literal;
    Type_display<decltype(123)> type_d_literal;
    Type_display<decltype("ladenzon")> type_d_str_literal;

    return 0;
}
#endif

// --------------------------------------------------------------------------------------------
// 10 proven interview questions: #1
// --------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <memory>

std::unique_ptr<int> f(std::unique_ptr<int> u_i_arg)
{
    *u_i_arg = 456;
    return u_i_arg;
}

int main(int argc, char *argv[])
{
    std::unique_ptr<int> u_i = std::unique_ptr<int>(new int(123));

    f(std::move(u_i));

    return 0;
}
#endif
#if 0
// --------------------------------------------------------------------------------------------
// 10 proven interview questions: #2
// --------------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <string>

class SearchQuery
{
public:
    SearchQuery()
    {}

    SearchQuery(const SearchQuery& sq)
    {}
};

class DirectorySearchResult {
public:
  DirectorySearchResult(
    std::vector<std::string> const& files,
    size_t attributes,
    SearchQuery const* query)
    : files_(files),
      attributes_(attributes),
      query_(new SearchQuery(*query))
  {}

  ~DirectorySearchResult() { delete query_; }

  DirectorySearchResult(const DirectorySearchResult& rhs)
    : files_(rhs.files_),
      attributes_(rhs.attributes_),
      query_(new SearchQuery(*rhs.query_))
  {}

  DirectorySearchResult(DirectorySearchResult&& rhs)
      : files_(std::move(rhs.files_)),
        attributes_(rhs.attributes_),
        query_(rhs.query_)
  {
      rhs.query_ = nullptr;
  }

  DirectorySearchResult& operator=(const DirectorySearchResult& rhs)
  {
      if (&rhs != this) {
          this->files_ = rhs.files_;
          this->attributes_ = rhs.attributes_;
          *this->query_ = *rhs.query_;
      }
      return *this;
  }

  DirectorySearchResult& operator=(DirectorySearchResult&& rhs)
  {
      if (&rhs != this) {
          this->files_ = std::move(rhs.files_);
          this->attributes_ = rhs.attributes_;
          this->query_ = rhs.query_;
          rhs.query_ = nullptr;
      }
      return *this;
  }

private:
  std::vector<std::string> files_;
  size_t attributes_;
  SearchQuery* query_;
};

int main(int argc, char *argv[])
{
    std::vector<std::string> vs;
    DirectorySearchResult sr(vs, 0, 0);

    return 0;
}
#endif
#if 0
// --------------------------------------------------------------------------------------------
// special member functions generation
// --------------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

struct A
{
    int i_ = 1;
    string s_ = "amsterdam";

    A() { cout << "A::A()\n"; }
    ~A() { cout << "A::~A()\n"; }
};

struct B
{
    int i_ = 2;
    string s_ = "boston";

    B() { cout << "B::B()\n"; }
    B(const B &b)
        : i_(b.i_), s_(b.s_)
    { cout << "B::B(const B&)\n"; }
    B& operator=(const B &b)
    {
        cout << "B::operator=(const B&)\n";
        i_ = b.i_;
        s_ = b.s_;
        return *this;
    }
    B(B &&b) = default;
    B& operator=(B &&b) = default;
    ~B() { cout << "B::~B()\n"; }             //  -> suppress default move constructor generation
//    ~B() { cout << "B::~B()\n"; }             //  -> generate default move constructor
};

int main(int argc, char *argv[])
{

    {
        cout << "Default copy constructor...\n";
        A a1;
        A a2(a1);
        A a3 = a1;
        cout << "a1.s_: " << a1.s_ << ", a2.s_: " << a2.s_ << ", a3.s_: " << a3.s_ << endl;
    }
    cout << endl;

    {
        cout << "Default copy assignment...\n";
        A a1;
        A a2;
        a2 = a1;
        cout << "a1.s_: " << a1.s_ << ", a2.s_: " << a2.s_ << endl;
    }
    cout << endl;

    {
        cout << "Default move constructor...\n";
        B b1;
        B b2(std::move(b1));
        cout << "b1.i_:b1.s_: " << b1.i_ << ":" << b1.s_ << ", b2.i_:b2.s_: " << b2.i_ << ":" << b2.s_ << endl;
    }
    cout << endl;

    {
        cout << "Default move assignment...\n";
        B b1;
        B b2;
        b2 = std::move(b1);
        cout << "b1.i_:b1.s_: " << b1.i_ << ":" << b1.s_ << ", b2.i_:b2.s_: " << b2.i_ << ":" << b2.s_ << endl;
    }
    cout << endl;

    return 0;
}
#endif

// --------------------------------------------------------------------------------------------
// copy/assign/move/swap
// --------------------------------------------------------------------------------------------

#if 0
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <algorithm>
using namespace std;

struct A
{
    int i_ = 1;
    string s_ = "usa";
    vector<string> vs_ = {"boston", "chicago", "new_york"};

    A()
    {
        cout << "A::A()\n";
    }
    ~A() { cout << "A::~A()\n"; }
    A(const A& a) = default;
    A& operator=(const A &a) = default;
    A(A &&a) = default;
    A& operator=(A &&a) = default;

    void foo()
    {
        cout << "A::foo()\n";
    }
};

ostream& operator<<(ostream &os, const A &a)
{
    os  << "i_: " << a.i_ << ", "
        << "s_: " << a.s_ << ", "
//        << "vs_: " << a.vs_
           ;
    os << "vs_: ";
    for (const auto &elem: a.vs_) {
        os << elem << ";";
    }

    return os;
}

void f_val(A a)
{
    cout << "f_val()...\n";
//    cout << a << endl;
}

void f_constref(const A &a)
{
    cout << "f_constref()...\n";
//    cout << a << endl;
}

struct B
{
    unique_ptr<int> up_i_;

    B(int i = 0)
        : up_i_ {unique_ptr<int>(new int {i})}
    {
        cout << "B::B()\n";
    }
    ~B() { cout << "B::~B()\n"; }

    B(const B &b)
        : up_i_ {unique_ptr<int>(new int {*b.up_i_})}
    {
        cout << "B::B(const B &b)\n";
    }

    B& operator=(const B &b)
    {
        cout << "B::operator=(const B &b)\n";
//        up_i_.reset(new int {*b.up_i_});  // same as *up_i_ = *b.up_i_
        *up_i_ = *b.up_i_;
        return *this;
    }

    B(B &&b)
        : up_i_ {std::move(b.up_i_)}
    {
        cout << "B::B(B &&b)\n";
    }

    B& operator=(B &&b)
    {
        up_i_ = std::move(b.up_i_);
        return *this;
    }
};

ostream& operator<<(ostream &os, const B &b)
{
    os  << "up_i_: " << (b.up_i_ != nullptr ? *b.up_i_ : 0)
           ;
    return os;
}

void f_val(B b)
{
    cout << "f_val()...\n";
    cout << b << endl;
}

struct C
{
    std::size_t size_;
    unique_ptr<int[]> array_;

    C(std::size_t size = 0, int default_val = 0)
        : size_{size}, array_{unique_ptr<int[]>(new int[size])}
    {
        cout << "C::C()\n";
        std::fill(&array_[0], &array_[0] + size, default_val);
    }

    C(const C &c)
        : size_{c.size_}, array_{unique_ptr<int[]>(new int[size_])}
    {
        cout << "C::C(const C&)\n";
        if ((c.array_ != nullptr) && (size_))
            std::copy(&c.array_[0], &c.array_[0]+size_, &array_[0]);
    }

    C& operator=(const C& c)
    {
        cout << "C::operator=(const C&)\n";
        size_ = c.size_;
        if (c.array_ != nullptr) {
            array_.reset(new int[size_]);
            if (size_) {
                std::copy(&c.array_[0], &c.array_[0] + size_, &array_[0]);
            }
        }
        else
            array_.reset(nullptr);
        return *this;
    }

    C(C &&c)
        : size_(c.size_), array_(std::move(c.array_))
    {
        cout << "C::C(C&&)\n";
    }

    C& operator=(C &&c)
    {
        size_ = c.size_;
        array_ = std::move(c.array_);
        return *this;
    }
};

ostream& operator<<(ostream& os, const C &c)
{
    cout << "size: " << c.size_ << ", array: ";
    if (c.array_ != nullptr) {
        for (std::size_t i = 0; i < c.size_; ++i) {
            cout << c.array_[i] << " ";
        }
    }
    else
        cout << "null";
    return os;
}

struct D
{
    int i_ = 0;
    D(int i)
        : i_{i}
    { cout << "D::D(): " << i_ << endl; }
    ~D() { cout << "D::~D(): " << i_ << endl; }
    D(const D &d)
        : i_(d.i_)
    { cout << "D::D(const D&)" << endl; }
    D& operator=(const D &d)
    {
        cout << "D::operator=(const D&)" << endl; return *this;
        i_ = d.i_;
    }
    D(D &&d)
    {
        cout << "D::D(D&&)" << endl;
        i_ = d.i_;
        d.i_ = 0;
    }
    D& operator=(D&&) { cout << "D::D(D&&)" << endl; return *this; }

    void foo() { cout << "D::foo(): " << i_ << endl; }
};

struct E
{
    unique_ptr<D> up_d_;

    E(int i = 0)
        : up_d_{unique_ptr<D>(new D{i})}
    {
        cout << "E::E()" << endl;
    }

    ~E() { cout << "E::~E()" << endl; }

    E(const E& e)
    {
        cout << "E::E(const E&)" << endl;
        if (e.up_d_ != nullptr)
            up_d_ = unique_ptr<D>(new D(*e.up_d_));
        else
            up_d_ = nullptr;
    }

    E& operator=(const E &e)
    {
        cout << "E::operator=(const E&)" << endl;
        if (e.up_d_ != nullptr)
            up_d_.reset(new D{*e.up_d_});
        else
            up_d_.reset(nullptr);
        return *this;
    }

    E(E &&e)
        : up_d_(std::move(e.up_d_))
    {
        cout << "E::E(E&&)" << endl;
    }

    E& operator=(E &&e)
    {
        cout << "E::operator=(E&&)\n";
        up_d_ = std::move(e.up_d_);
        return *this;
    }
};

ostream& operator<<(ostream& os, const D &d)
{
    cout << d.i_;
    return os;
}

ostream& operator<<(ostream& os, const E &e)
{
    if (e.up_d_ != nullptr)
        cout << *e.up_d_;
    else
        cout << "null";
    return os;
}

struct F
{
    vector<unique_ptr<D>> v_upd_;

    F(std::size_t n_elements = 0, int default_val = 0)
        : v_upd_()//, std::move(unique_ptr<D>(new D(default_val))))
    {
        cout << "F::F()" << endl;
        for (std::size_t i=0; i < n_elements; ++i) {
//            v_upd_.push_back(unique_ptr<D>(new D(default_val)));
            v_upd_.emplace_back(new D(default_val));
        }
    }

    ~F() { cout << "F::~F()" << endl; }

    F(const F &f)
        : v_upd_()
    {
        cout << "F::F(const F&)\n";
        for (const auto &f_elem: f.v_upd_)
            v_upd_.emplace_back(new D(*f_elem));
    }

    F& operator=(const F &f)
    {
        cout << "F::operator=(const F&)\n";
        if (this != &f) {
            v_upd_.clear();
            for (const auto &f_elem: f.v_upd_)
                v_upd_.emplace_back(new D(*f_elem));
        }
        return *this;
    }

    F(F &&f)
        : v_upd_(std::move(f.v_upd_))
    {
        cout << "F::F(F&&)\n";
    }

    F& operator=(F &&f)
    {
        cout << "F& operator=(F&&)\n";
        v_upd_ = std::move(f.v_upd_);
        return *this;
    }
};

ostream& operator<<(ostream& os, const F &f)
{
    os << "size: " << f.v_upd_.size();
    if (f.v_upd_.size()) {
        os << ", elements: ";
        for (const auto &element: f.v_upd_)
            os << *element << " ";
    }
    return os;
}

int main(int argc, char *argv[])
{

    {
        cout << "Value semantics...\n";
        A a;
        cout << a << endl;
        cout << "Copy construct...\n";
        f_val(a);
        cout << "source: " << a << endl;
        cout << "Move construct...\n";
        f_val(std::move(a));
        cout << "source: " << a << endl;
        A b, c;
        cout << "Move assign...\n";
        b = std::move(c);
        cout << "dest: " << b << endl;
        cout << "source: " << c << endl;
    }
    cout << endl;

    {
        cout << "Value semantics with unique_ptr...\n";
        B b;
        cout << b << endl;
        cout << "Copy construct...\n";
        f_val(b);
        cout << "source: " << b << endl;
        cout << "Copy assign...\n";
        B b1 {5}, b2;
        b2 = b1;
        cout << "source: " << b1 << endl;
        cout << "dest: " << b2 << endl;
        cout << "Move construct...\n";
        B b3 {123}, b4(std::move(b3));
        cout << "dest: " << b4 << endl;
        cout << "source: " << b3 << endl;
        cout << "Move assign...\n";
        B b5 {456}, b6;
        b6  = std::move(b5);
        cout << "dest: " << b6 << endl;
        cout << "source: " << b5 << endl;
    }
    cout << endl;

    {
        cout << "Value semantics with unique_ptr[]...\n";
        C c{10, 5};
        cout << c << endl;
        cout << "Copy construct...\n";
        C c2{c};
        cout << "dest:   " << c2 << endl;
        cout << "source: " << c << endl;
        cout << "Copy assign...\n";
        C c3;
        c3 = c;
        cout << "dest:   " << c3 << endl;
        cout << "source: " << c << endl;
        cout << "Move construct...\n";
        C c4(std::move(c));
        cout << "dest:   " << c4 << endl;
        cout << "source: " << c << endl;
        cout << "Move assign...\n";
        C c5{5, 123};
        C c6;
        c6 = std::move(c5);
        cout << "dest:   " << c6 << endl;
        cout << "source: " << c5 << endl;
    }
    cout << endl;

    {
        cout << "Value semantics with unique_ptr to class...\n";
        E e{5};
        cout << e << endl;
        cout << "Copy construct...\n";
        E e1{e};
        cout << "dest:   " << e1 << endl;
        cout << "source: " << e << endl;
        cout << "Copy assign...\n";
        E e2;
        e2 = e;
        cout << "dest:   " << e2 << endl;
        cout << "source: " << e << endl;
        cout << "Move construct...\n";
        E e3(std::move(e));
        cout << "dest:   " << e3 << endl;
        cout << "source: " << e << endl;
        cout << "Move assign...\n";
        E e4{123};
        E e5{456};
        e5 = std::move(e4);
        cout << "dest:   " << e5 << endl;
        cout << "source: " << e4 << endl;

    }
    cout << endl;

    {
        cout << "Value semantics with vector of unique_ptr to class...\n";
        F f{5, 5};
        cout << f << endl;
        cout << "Copy construct...\n";
        F f1(f);
        cout << "dest:   " << f1 << endl;
        cout << "source: " << f << endl;
        cout << "Copy assign...\n";
        F f2{10, 10};
        f2 = f;
        cout << "dest:   " << f2 << endl;
        cout << "source: " << f << endl;
        cout << "Move construct...\n";
        F f3{3, 3};
        F f4(std::move(f3));
        cout << "dest:   " << f4 << endl;
        cout << "source: " << f3 << endl;
        cout << "Move assign...\n";
        F f5{4, 4};
        F f6;
        f6 = std::move(f5);
        cout << "dest:   " << f6 << endl;
        cout << "source: " << f5 << endl;
    }
    cout << endl;

    return 0;
}
#endif

// --------------------------------------------------------------------------------------------
// 10 proven interview questions: #8
//    Write a templated struct that determines, at compile time, whether its template argument
//    T is a pointer
// --------------------------------------------------------------------------------------------
#if 0

#include <iostream>
using namespace std;

template<typename T>
struct Is_pointer
{
    static constexpr bool result_ = false;
};

template<typename T>
struct Is_pointer<T*>
{
    static constexpr bool result_ = true;
};

class A {};

int main(int argc, char *argv[])
{
    cout << "int:        " << (Is_pointer<int>::result_==true ? "pointer" : "not a pointer") << endl;
    cout << "int*:       " << (Is_pointer<int*>::result_==true ? "pointer" : "not a pointer") << endl;
    cout << "A:          " << (Is_pointer<A>::result_==true ? "pointer" : "not a pointer") << endl;
    cout << "A*:         " << (Is_pointer<A*>::result_==true ? "pointer" : "not a pointer") << endl;
    cout << "A&:         " << (Is_pointer<A&>::result_==true ? "pointer" : "not a pointer") << endl;
    cout << "const A*:   " << (Is_pointer<const A*>::result_==true ? "pointer" : "not a pointer") << endl;
    return 0;
}
#endif
// --------------------------------------------------------------------------------------------
// std::enable_if
// --------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <array>
#include <type_traits>
using namespace std;

struct A
{
    int i_ = 0;
    A(int i = 0)
        : i_{i}
    {}
};

ostream& operator<<(ostream& os, const A &a)
{
    os << "A::i_: " <<  a.i_;
    return os;
}

template <typename T,
          typename enable_if<is_integral<T>::value, T>::type* = nullptr>
void display(const T &t)
{
    cout << "integral: " << t << endl;
}

template <typename T,
          typename enable_if<is_floating_point<T>::value, T>::type* = nullptr>
void display(const T &t)
{
    cout << "floating point: " << t << endl;
}

template <typename T,
          typename enable_if<is_class<T>::value, T>::type* = nullptr>
void display(const T &t)
{
    cout << "struct or class: " << t << endl;
}

int main(int argc, char *argv[])
{
//    array<int, 10> arr_int_10;

//    insertion_sort<int, 10>(arr_int_10);

    A a(123);
    display(5);
    display(5.5);
    display(a);

    return 0;
}
#endif

// --------------------------------------------------------------------------------------------
// 10 proven interview questions: #9
//    Define a function insertion_sort which accepts as first and only argument a reference to an
//    std::array only if the element types are integral (the trait std::is_integral might be of help)
//    and the size of the array is less than 128 elements, and sorts it using insertion sort
// --------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <array>
#include <type_traits>
using namespace std;

template<typename T, size_t size,
         typename enable_if< is_integral<T>::value &&
                             (size < 128),
                             T >::type* = nullptr>
void insertion_sort(array<T, size> &arr)
{
    cout << "insertion_sort: integral, array size: " << arr.size() << endl;

    for (size_t i = 1; i < arr.size(); ++i) {
        for (size_t j = (i); (j > 0) && (arr[j] < arr[j-1]); --j) {
            swap(arr[j], arr[j-1]);
        }
    }
}

template<typename Array>
void display_array(const Array &a)
{
  for (size_t i = 0; i < a.size(); ++i) {
    cout << a[i] << " ";
  }
}

int main(int argc, char *argv[])
{
    array<int, 10> arr_int_10 = {{10, 2, 5, 6, 8 ,9, 1, 3, 4, 7}};
//    array<double, 10> arr_double_10;

    display_array(arr_int_10); cout << endl;

    insertion_sort(arr_int_10);

    display_array(arr_int_10); cout << endl;
//    insertion_sort(arr_double_10);

    return 0;
}
#endif

#include <iostream>
#include <array>
#include <type_traits>
using namespace std;

template<typename T, size_t size,
      typename enable_if< is_integral<T>::value &&
                          (size < 128),
                          T >::type* = nullptr>
void insertion_sort(array<T, size> &arr)
{
 cout << "insertion_sort: integral, array size: " << arr.size() << endl;

 for (size_t i = 1; i < arr.size(); ++i) {
     for (size_t j = (i); (j > 0) && (arr[j] < arr[j-1]); --j) {
         swap(arr[j], arr[j-1]);
     }
 }
}

template<typename Array>
void display_array(const Array &a)
{
for (size_t i = 0; i < a.size(); ++i) {
 cout << a[i] << " ";
}
}

int main(int argc, char *argv[])
{
 array<int, 10> arr_int_10 = {{10, 2, 5, 6, 8 ,9, 1, 3, 4, 7}};
//    array<double, 10> arr_double_10;

 display_array(arr_int_10); cout << endl;

 insertion_sort(arr_int_10);

 display_array(arr_int_10); cout << endl;
//    insertion_sort(arr_double_10);

 return 0;
}
