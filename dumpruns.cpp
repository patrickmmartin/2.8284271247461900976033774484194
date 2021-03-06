/*
 * dumpruns.cpp
 *
 *  Created on: 30 May 2016
 *      Author: patrick
 */

#include <iostream>
#include <iomanip>
#include <limits>

#include "root_classes.h"

int main(int argc, char *argv[]) {

  double arg = 1 * sqrt(std::numeric_limits<float>::max());

  std::cout << "std sqrt\n";
  StdSqrt<PrintingCounter>()(arg);
  std::cout << "\nclosed form\n";
  ClosedForm<PrintingCounter>()(arg);
  std::cout << "\nbabylonian\n";
  Bablyonian<PrintingCounter>()(arg);
  std::cout << "\nNewtown Raphson\n";
  NewtonRaphsonND<PrintingCounter>()(arg);
  std::cout << "\nBisection\n";
  BisectionSearch<PrintingCounter>()(arg);

  std::cout << "\nScan\n";
  ScanAndStep<PrintingCounter>()(arg);

  std::cout << "\nQuake64\n";
  Inverse<PrintingCounter>()(arg);
  std::cout << "\n";

  std::cout << "input, closed form,closed form result,std sqrt,std sqrt "
               "result,Hero,Hero result, NR, NR result, BS, BS result, SS, SS "
               "result, Quake64, Quake64 "
               "result\n";
  for (double arg = std::numeric_limits<double>::min();
       arg < std::numeric_limits<double>::max(); arg *= 1e100) {
    std::cout << arg << ",\t";
    ClosedForm<SummaryCounter>()(arg);
    std::cout << ",\t";
    StdSqrt<SummaryCounter>()(arg);
    std::cout << ",\t";
    Bablyonian<SummaryCounter>()(arg);
    std::cout << ",\t";
    NewtonRaphsonND<SummaryCounter>()(arg);
    std::cout << ",\t";
    BisectionSearch<SummaryRangeCounter>()(arg);
    std::cout << ",\t";
    ScanAndStep<SummaryRangeCounter>()(arg);
    std::cout << ",\t";
    Inverse<SummaryCounter>()(arg);
    std::cout << "\n";
  }

  return 0;
}
