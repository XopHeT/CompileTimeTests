#include <iostream>

#include "MathExpectations.hpp"

int main() {
  (void)testMathExpectations(); // Кроме compile-time выполняем тесты в run-time, чтобы построить coverage report
  return 0;
}
