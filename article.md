Eight Rooty Pieces
===

Interview Questions
---

_Sigh_ Some things we have to deal with.
How many "questions" have "real breadth and depth"? [1]

Here's a little for fun question I've been carting around for some time and it's grown to a large sheet of paper, or an unusable font size.

"implement the square root function"

### What one learns in asking this

* People are frightened of sqrt()
* There is a giant range in the comfort level for working through the issues in implementing this deceptively simple function
* People are generally wrong to be frightened of the problem
* There's a very large number of approaches



### Eight (or so) approaches



#### Closed form
/**
 * explanation: closed form for the win!
 *
 * ok ... log x^y = y log x
 */

#### Babylonian
/**
 * graphical explanation: iterative search for square root by successive
 * reduction of difference
 * between the 2 sides of a shape with the area of val.
 * pick one side, -  derive the other - split the difference for the next guess
 * Note the expression reduces to 2*x = 2*x when x*x = val
 */

Possibly the only algorithm that you can implement using a piece of rope.

#### Newton Raphson
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

#### Range reduction
/**
 * explanation: range reduction approach (does not rely upon good initial guess)
 * note that in contrast to techniques making use of the gradient of the
 * function,
 * the initial guesses need to cater for the value 1.
 * Note: rarely found in the wild as other better sqrt approaches are so well
 * known.
 */

#### Guess, Step and Scan 
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

#### one sided binary search
/**
 *
 * a one-sided binary search version -
 * double successively to obtain the upper range, use zero for the lower
 * note starting with 1, upper will be found in zero passes for y < 1
 *
 */


#### one sided binary search 2
/**
 *
 * a one-sided binary search version that will find seek the edge-
 * double successively to obtain the upper range, use zero for the lower
 *
 */

#### Carmack method
/**
 * explanation: just for fun, old example of a very fast approximate inverse
 * square root,
 * still works on Intel
 */


#### Quantum computer method ( requires 2^64 qbits )
/**
*
* explanation: for each value in double: return value if value ^ 2 == input
*
*/




References
----


[1] why are we using questions?












[questions] also, "questions" ?

 