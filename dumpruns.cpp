/*
 * dumpruns.cpp
 *
 *  Created on: 30 May 2016
 *      Author: patrick
 */

#include <iostream>
#include <limits>

#include "root_classes.h"

int main(int argc, char *argv[]) {

  double arg = 100 * sqrt(std::numeric_limits<double>::max());

  std::cout << "std sqrt\n";
  StdSqrt<PrintingCounter>()(arg);
  std::cout << "closed form\n";
  ClosedForm<PrintingCounter>()(arg);
  std::cout << "babylonian\n";
  Bablyonian<PrintingCounter>()(arg);
  std::cout << "Newtown Raphson CF\n";
  NewtonRaphsonCF<PrintingCounter>()(arg);
  std::cout << "Newtown Raphson ND\n";
  NewtonRaphsonND<PrintingCounter>()(arg);
}
