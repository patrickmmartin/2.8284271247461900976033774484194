//============================================================================
// Name        : 2.8284271247461900976033774484194.cpp
// Author      : Patrick Martin
// Version     :
// Copyright   : Patrick Martin
// Description : find that root!
//============================================================================

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <iostream>

#include "eight_rooty_pieces.h"

int main(void) {


	 for (int i = -40 ; i < 40 ; i++)
	 {
	 double arg = exp(i);
	 std::cout << sqrt(arg) << ", "
	 << my_sqrt(arg) << ", "
	 << my_sqrt_bablyonian(arg) << ", "
	 << my_sqrt_newtonraphson(arg) << ", "
	 << my_sqrt_range(arg) << ", "
	 << my_sqrt_naive(arg) << ", "
	 << my_sqrt_homage_to_carmack(arg) << ", "
	 << std::endl;
	 }

	return EXIT_SUCCESS;


}