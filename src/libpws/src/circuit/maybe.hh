#pragma once

#include <utility>

template<class T>
class Maybe
{
  bool valid;
  T val;

public:
  Maybe() : valid(false), val() { }
  Maybe(const T& value) : valid(true), val(value) { }

  // Move constructors needed for the use of unique_ptr in the mips package.
#if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L
  Maybe(const Maybe<T>& other) : valid(other.valid), val(other.val) { }
  Maybe(Maybe<T>&& other) : valid(other.valid), val(std::move(other.val)) { }
#endif

  void invalidate()
  {
    if (isValid())
    {
      valid = false;
      val = T();
    }
  }

  void validate() {
    valid = true;
  }

  Maybe<T>& operator= (const T& valu)
  {
    validate();
    this->val = valu;
    return *this;
  }

#if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L
  Maybe<T>& operator= (T&& valu)
  {
    validate();
    this->val = std::move(valu);
    return *this;
  }

  Maybe<T>& operator= (const Maybe<T>& other)
  {
    if (this != &other)
    {
      valid = other.valid;
      val = other.val;
    }
    return *this;
  }

  Maybe<T>& operator= (Maybe<T>&& other)
  {
    if (this != &other)
    {
      valid = other.valid;
      val = std::move(other.val);
    }
    return *this;
  }
#endif

  const T& value() const { return val; }
  T& value()             { return val; }
  bool isValid() const { return valid; }

  operator T() const
  {
    return value();
  }
};
