#ifndef CPP2_S21_CONTAINERS_STACK_HPP
#define CPP2_S21_CONTAINERS_STACK_HPP

#include "../List/s21_list.hpp" // Используем стандартный вектор как контейнер

namespace s21 {

template <typename T> class stack {
public:
  using value_type = T; // параметр шаблона T
  using reference = T &; // T &определяет тип ссылки на элемент
  using const_reference =
      const T &; // const T &определяет тип константной ссылки
  using size_type = size_t; // size_tопределяет тип размера контейнера
                            // (стандартный тип — size_t)
  using Container = list<T>;

  ////конструкторы
  stack(); // empty stack
  stack(std::initializer_list<value_type> const
            &items);           // construktor c zadanimi dannimi
  stack(const stack &s);       // copy
  stack(stack &&s);            // constr peremeshenia
  ~stack();                    // destructor
  stack &operator=(stack &&s); // perehruzka dla peremeshenia

  //// доступ
  const_reference top(); // доступ к верхнему элементу

  bool empty();     // проверка на suck
  size_type size(); // возврат колво элементов

  void push(const_reference value); // вставляет элемент вверху
  void pop();              // удаляет верхний элемент
  void swap(stack &other); // меняет местами содержимое

  template <typename... Args>
  void insert_many_back(
      Args &&...args); // Добавляет новые элементы в конец контейнера.

private:
  Container container_;
};

} // namespace s21

#include "s21_stack.tpp"
#endif // CPP2_S21_CONTAINERS_STACK_HPP
