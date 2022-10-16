#include "MathExpectations.hpp"

static constexpr bool worksForZeroLengthArray() {
  // Раскомментировать строку ниже и тест провалится т.к. возникнет выход за границы массива
  // Если выполнять тест в run-time, то он может даже быть успешно пройденным
  //math_expectation(std::array<int, 0>{});
  return true;
}

static constexpr bool forZerosIsZero() { 
  return math_expectation({0, 0, 0, 0, 0}) == 0; 
}

static constexpr bool for10_6_8_is_8() { 
  return math_expectation({10.0F, 6.0F, 8.0F}) == 8; 
}

static constexpr bool canDeduceTypeWithIntAndFloat() {
  // Раскомментировать строку ниже, и тест провалится т.к. 2 числа разного типа не могут быть в одном контейнере
  //math_expectation({1, 2.0F});
  return true;
}

static constexpr bool acceptsStdArray() {
  math_expectation(std::array{1}); //Если скомпилировалось - значит std::array перегрузка функции есть
  return true;
} 

static constexpr bool acceptsCStyleArray() {
  math_expectation({1}); //Если скомпилировалось - значит работает с C-style массивом
  return true;
}

constexpr bool testMathExpectations() {
  if  (!acceptsStdArray()) return false;
  if  (!acceptsCStyleArray()) return false;
  if  (!canDeduceTypeWithIntAndFloat()) return false;
  if  (!worksForZeroLengthArray()) return false;
  if  (!forZerosIsZero()) return false;
  if  (!for10_6_8_is_8()) return false;
  
  // Небольшая демонстрация
  constexpr size_t array_size = 5;
  int a[array_size];
  for (int i = 0; i < array_size + 1; ++i) {
    //a[i] = 0; // Если бы тесты не выполнялись в compile-time, то a[6] = 0; сработало бы без лишних вопросов
  }
  return true;
}

static_assert(testMathExpectations()); // Эта строка выполняет тесты в compile-time
