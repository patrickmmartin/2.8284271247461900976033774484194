/*
 * dumpruns.cpp
 *
 *  Created on: 30 May 2016
 *      Author: patrick
 */

#include <iostream>

#include "root_classes.h"

int main(int argc, char *argv[]) {

  double arg = 100;

  std::cout << "closed form\n";
  ClosedForm<PrintingCounter>()(arg);
  std::cout << "babylonian\n";
  Bablyonian<PrintingCounter>()(arg);
  std::cout << "Newtown Raphson\n";
  NewtonRaphson<PrintingCounter>()(arg);
}
