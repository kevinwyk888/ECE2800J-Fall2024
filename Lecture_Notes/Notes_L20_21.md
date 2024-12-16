### Introduction

21. Operator Overloading

### Operator Overloading

**Overloaded operators** are functions with special names: the keyword operator followed by the symbol (e.g., +,-, etc.) of the operator being redefined.

```cpp
 A operator+(const A &l, const A &r);
 // returns l “+” r
 A A::operator+(const A &r);
 // returns *this “+” r
```

Overload `operator+=` for a class of complex number.

```cpp
 class Complex {
 // OVERVIEW: a complex number class
 double real;
 double imag;
 public:
 Complex(double r=0, double i=0); // Constructor
 Complex &operator += (const Complex &o);
 // MODIFIES: this
 // EFFECTS: adds this complex number with the
 // complex number o and return a reference
 // to the current object.
 };

 Complex &Complex::operator += (const Complex &o){
 real += o.real;
 imag += o.imag;
 return *this;
 }
```

##### Advantage of `&`

- Support chaining.
- Avoid copy object.

#### Friend

```cpp
class foo {
  friend void baz();
  int f;
};
void baz() { ... }

//The function baz has access to f, which would  otherwise be private to class foo.

class foo {
    friend class bar;
    int f;
};
class bar {
 ...
};

//Then, objects of class bar can access private member f of foo

class Complex {
    // OVERVIEW: a complex number class
    double real;
    double imag;
    public:
    Complex(double r=0, double i=0);
    Complex &operator += (const Complex &o);
    friend Complex operator+(const Complex &o1, 
    const Complex &o2);
};
// Its implementation is the same as before

```

#### Overloading Operator []

```cpp
const int &IntSet::operator[](int i) const {
  if(i >= 0 && i < numElts) return elts[i];
  else throw -1;
}
// const version returning a const reference to int
// first const: reture a const value, can't change.
// second const: can't change the member data.

int &IntSet::operator[](int i) {
  if(i >= 0 && i < numElts) return elts[i];
  else throw -1;
}
// nonconst version returning a reference to int

```

#### Overloading Output Operator <<

**Remark**: operator<< must be a nonmember function!

- The ``operator<<`` should take an ``ostream&`` as its first parameter and a **const reference** to an object of the class type as its second.
-  `operator<<` can be chained together $\Rightarrow$  `operator<<` return a reference
  
```cpp
 ostream &operator<<(ostream &os, const IntSet &is){
 for(int i = 0; i < is.size(); i++)
 os << is[i] << " ";
 return os;
 }
```
-  The ``operator>>`` should take an istream& as its first 
parameter and a **nonconst reference** to a object of the class 
type as its second.