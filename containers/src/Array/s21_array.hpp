#ifndef S21_CONTAINERS_EXTRA_ARRAY
#define S21_CONTAINERS_EXTRA_ARRAY

#include <initializer_list>
#include <iostream>
#include <stdexcept>

namespace s21 {
template <class T, std::size_t N> class array {
private:
  // Опр типов
  using value_type = T;
  using size_type = std::size_t;

  value_type elements_[N] = {};
  size_type size_ = N;

public:
  // для работы с элементами массива
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;

  // конструкторы, деструктор и оператор присваивания
  array();                                               //
  array(std::initializer_list<value_type> const &items); //
  array(const array &a);                                 //
  array(array &&a) noexcept;                             //
  ~array() = default;                                    //
  array &operator=(const array &a);                      //
  array &operator=(array &&a) noexcept;                  //

  // иетоды для доступа к элементам
  reference at(size_type pos);                     //
  const_reference at(size_type pos) const;         //
  reference operator[](size_type pos);             //
  const_reference operator[](size_type pos) const; //
  const_reference front() const;                   //
  const_reference back() const;                    //
  iterator data();

  // методы для итераторов
  iterator begin();             //
  iterator end();               //
  const_iterator begin() const; //
  const_iterator end() const;   //

  // методы для информации о состоянии контейнера
  bool empty() const noexcept;         //
  size_type size() const noexcept;     //
  size_type max_size() const noexcept; //
};
} // namespace s21

#include "s21_array.tpp"

#endif
