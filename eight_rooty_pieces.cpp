#include <limits.h>

#include <math.h>

#include <cmath>
#include <iostream>

/**
 * explanation: closed form for the win!
 *
 * ok ... log x^y = y log x
 */
double my_sqrt(double val) { return exp(0.5 * log(val)); }

/**
 * graphical explanation: iterative search for square root by successive
 * reduction of difference
 * between the 2 sides of a shape with the area of val.
 * pick one side, -  derive the other - split the difference for the next guess
 * Note the expression reduces to 2*x = 2*x when x*x = val
 */
double my_sqrt_bablyonian(double val) {
  double x = val / 2;

  while (fabs((x * x) - val) > (val / 1E9)) {
    x = 0.5 * (x + (val / x));
  }

  return x;
}

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
double my_sqrt_newtonraphson(double val) {

  long double x = val / 2;

  while (fabs((x * x) - val) > (val / 1E9)) {
    // x * x - val is the function for which we seek the root
    x = x - ((x * x - val) / (2 * x));
  }
  return x;
}

/**
 * explanation: range reduction approach (does not rely upon good initial guess)
 * note that in contrast to techniques making use of the gradient of the
 * function,
 * the initial guesses need to cater for the value 1.
 * Note: rarely found in the wild as other better sqrt approaches are so well
 * known.
 */
double my_sqrt_range(double val) {

  double upper = val;
  double lower = 1;
  if (val < 1) {
    upper = 1;
    lower = 0;
  }

  double x = (lower + upper) / 2;

  int iterations = 0;

  while (iterations < 1000) {

    if (((x * x) > val))
      upper = x;
    else
      lower = x;

    x = (lower + upper) / 2;
    iterations++;
  }

  return x;
}

/**
 * explanation: very naive guess step and scan approach, reversing and
 * decreasing step on each transition
 * vulnerable to overshoot if the transition is missed
 * discussion point: as an improvement the step could always be adjusted to head
 * "the right way",
 * but the magnitude would only be adjusted upon a crossing
 * other discussion point - it turns out that the convergence is
 *  sensitive to the accuracy of the function near the roots - if loss of
 * precision leads to jagged
 *  behaviour convergence may be be poor
 *
 */
double my_sqrt_naive(double val) {
  double x = val / 2;
  double step = val / 2;
  double lastdiff = 0;
  double diff = (x * x) - val;

  while (fabs(diff) > (val / 1E9)) {
    if (diff > 0)
      x -= step;
    else
      x += step;

    if ((diff > 0) != (lastdiff > 0)) {
      step = step * 0.5;
    }
    lastdiff = diff;
    diff = (x * x) - val;
  }

  return x;
}

/**
 *
 * a one-sided binary search version -
 * double successively to obtain the upper range, use zero for the lower
 * note starting with 1, upper will be found in zero passes for y < 1
 *
 */
double my_sqrt_binary(double val) {

  double lower = 0;
  double upper = val;

  while ((upper * upper) < val)
    upper *= 2;

  double x = (lower + upper) / 2;

  int iterations = 0;

  while (iterations < 30) {

    if (((x * x) > val))
      upper = x;
    else
      lower = x;

    x = (lower + upper) / 2;
    iterations++;
  }

  return x;
}

/**
 * the point that any monotonically rising function attains a given value can be
 * put in here
 */
int is_one(double guess, double val) { return ((guess * guess) > val) ? 1 : 0; }

/**
 *
 * a one-sided binary search version that will seek the edge-
 * double successively to obtain the upper range, use zero for the lower
 *
 */
double my_sqrt_binary_for_joao(double val) {

  double lower = 0;
  double upper = 0.01; // selecting a good initial guess for the whole domain
                       // is actually worthy of another pub discussion...

  while (!is_one(upper, val))
    upper *= 2;

  double x = (lower + upper) / 2;

  while (fabs(1 - (lower / upper)) > 1e-8) {

    if (is_one(x, val))
      upper = x;
    else
      lower = x;

    x = (lower + upper) / 2;
  }

  return x;
}

/**
 * explanation: just for fun, old example of a very fast approximate inverse
 * square root,
 * still works on Intel
 */
double my_sqrt_homage_to_carmack(float x) {
  // actually Chris Lomont version via SO, allegedly
  // note: are we running on Little-Endian, hmm? :P

  float xhalf = 0.5f * x;
  int i = *(int *)&x;        // get bits for floating value
  i = 0x5f375a86 - (i >> 1); // gives initial guess y0
  x = *(float *)&i;          // convert bits back to float

  // initial guess: to within 10% already!
  x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy

  // gah! no iterations!!!!

  return 1 / x;
}

/**
 * explanation: update of the original to 64-bit types
 */
double my_sqrt_homage_to_carmack64(double x) {
  double xhalf = x * 0.5;
  long long i = *(long long *)&x;    // get bits for floating value
  i = 0x5fe6eb50c7b537a9 - (i >> 1); // gives initial guess y0
  x = *(double *)&i;                 // convert bits back into double

  x = x * (1.5f - xhalf * x * x); // one Newton Raphson step

  return 1 / x;
}

/**
 * explanation: inverse square root algorithm
 */
double my_inverse_sqrt(double x) {
  long long i, r;
  double xhalf = x * 0.5, y = x;
  i = *(long long *)&x;
  i = 0x5fe6eb50c7b537a9 - (i >> 1);
  y = *(double *)&i;
  for (r = 0; r < 10; r++)
    y = y * (1.5 - (xhalf * y * y));
  return x * y;
}
