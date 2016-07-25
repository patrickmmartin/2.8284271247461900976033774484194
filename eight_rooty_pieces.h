/*
 * eight_rooty_pieces.h
 *
 *  Created on: 19 Mar 2016
 *      Author: Patrick
 */

#ifndef EIGHT_ROOTY_PIECES_H_
#define EIGHT_ROOTY_PIECES_H_

/*
 *
 *
 * a mixed bag of hand-crafted square root implementations as an aide memoire:
 *
 * aside from the closed form, or the version that simply doesn't bother with
 converging (fun example),
 * one discussion point allows us to touch upon epsilon comparisons (absolute
 value of epsilon) versus (eventually)
 * bits of precision - the latter being more what the user would expect
 * another follow on discussion point is - should the functions return double or
 float?
 * another discussion point is around convergence: is it guaranteed?
 * follow on point is : should the # of iteration strategies / precision be a
 parameter?
 *
 *
 * about the error handling...
 * negative numbers are not handled
 * and exploring the esoterica of the extremes of double are overlooked
 *
 * testing the sqrt functions - barring the deliberately terrible scan -
 * all the approaches converge and track each other well over the range of
 exp(80),
 * yes even the "Carmack" version...
 *
 *
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
 *
 *
 */

/**
 * explanation: closed form for the win!
 *
 * ok ... log x^y = y log x
 */
double my_sqrt(double val);

/**
 * graphical explanation: iterative search for square root by successive
 * reduction of difference
 * between the 2 sides of a shape with the area of val.
 * pick one side, -  derive the other - split the difference for the next guess
 * Note the expression reduces to 2*x = 2*x when x*x = val
 */
double my_sqrt_bablyonian(double val);

/**
 * explanation: NR search for x^2 - value is 0
 * - note this relies upon knowing dy/dx is 2*x
 *   to avoid having to implement the full numerical gradient
 * graphical explanation: search for the zero by building a triangle from the
 * current guess value
 *  and the gradient at that point, for which the prior factoid is handy, else a
 * numerically estimated gradient
 *  will do, with the usual caveats about loss of precision - suggest this is a
 * good discussion point
 */
double my_sqrt_newtonraphson(double val);

/**
 * explanation: range reduction approach (does not rely upon good initial guess)
 * note that in contrast to techniques making use of the gradient of the
 * function,
 * the initial guesses need to cater for the value 1.
 * Note: rarely found in the wild as other better sqrt approaches are so well
 * known.
 */
double my_sqrt_range(double val);

/**
 * explanation: very naive guess step and scan approach, reversing and
 * decreasing step on each transition
 * vulnerable to overshoot if the transition is missed
 * discussion point: an improvement the step could always be adjusted to head
 * "the right way",
 * but the magnitude would only be adjusted upon a crossing
 * other discussion point - it turns out that the convergence is
 *  sensitive to the accuracy of the function near the roots - if loss of
 * precision leads to jagged
 *  behaviour convergence may be be poor
 *
 */
double my_sqrt_naive(double val);

/**
 *
 * a one-sided binary search version -
 * double successively to obtain the upper range, use zero for the lower
 * note starting with 1, upper will be found in zero passes for y < 1
 *
 */
double my_sqrt_binary(double val);

/**
 *
 * a one-sided binary search version that will find seek the edge-
 * double successively to obtain the upper range, use zero for the lower
 *
 */
double my_sqrt_binary_for_joao(double val);

/**
 * explanation: just for fun, old example of a very fast approximate inverse
 * square root,
 * still works on Intel
 */
double my_sqrt_homage_to_carmack(float x);


/**
 * explanation: just for fun, update of alleged Quake inverse square root,
 * still works on Intel
 */
double my_sqrt_quake_64(double x);

#endif /* EIGHT_ROOTY_PIECES_H_ */
