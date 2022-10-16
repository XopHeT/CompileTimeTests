#ifndef INC_E7E26095758F46A3826A264621ED2E3F
#define INC_E7E26095758F46A3826A264621ED2E3F

#include <algorithm>
#include <array>

/**
 * @brief Подсчет математического ожидания в C++-style массиве
 * 
 * предполагаемое использование: math_expectation(std::array{1})
 * @tparam Type - любой из числовых типов данных.
 * @tparam ElementsCount - количество элементов в массиве
 * @param [in] from - массив, для которого необходимо получить матожидание
 * @return матожидание
 */
template <class Type, std::size_t ElementsCount>
constexpr double math_expectation(std::array<Type, ElementsCount> &&from) {
    //static_assert(ElementsCount != 0); // Убрал проверку, чтобы показать что будет если возникнет выход за границы массива в compile-time. См. worksForZeroLengthArray
    static_assert(std::is_arithmetic<Type>().value);
    std::array<Type, ElementsCount> sorted{from};
    std::sort(begin(sorted), end(sorted));
    double expectation{0};
    double current = sorted[0]; // При нулевом размере массива и если тесты выполнять в run-time, то в отладочной сборке нам покажут сообщение. В релизной сборке молча прожуют
    std::size_t count = 0;
    for (Type const &value: sorted) {
      if (value == current) {
        count++;
      } else {
        expectation += current * (double)count / (double)ElementsCount;
        count =  1;
        current = value;
      }
    }
    expectation += current * (double)count / (double)ElementsCount;

    return expectation;
}

/**
 * @brief Подсчет математического ожидания в C-style массиве
 * 
 * предполагаемое использование: math_expectation({10.0F, 6.0F, 8.0F})
 * @tparam Type - любой из числовых типов данных.
 * @tparam ArraySize - количество элементов в массиве
 * @param [in] from - C-style массив
 * @return матожидание
 */
template<typename Type, std::size_t ArraySize>
constexpr double math_expectation(Type const (&from)[ArraySize]){
  return math_expectation(std::to_array(from));
}

extern constexpr bool testMathExpectations(); // Мог бы тут static_assert'ов напихать, но они бы выполнялись каждый раз, когда этот header включался в *.cpp. А так тесты будут выполнятся только при компиляции MathExpectations.cpp

#endif //INC_E7E26095758F46A3826A264621ED2E3F
