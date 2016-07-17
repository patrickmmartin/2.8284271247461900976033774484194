Eight Rooty Pieces
===

Interview Questions
===

_Sigh_ Some things we have to deal with.
Interview Questions.

People are _always talking about interview techniques_, let rarely _talking about how awful they are at interviewing_.
TODO(PMM) ref. Yegge blog rant, many, many others  

Open question for discussion: how many of these "questions" have genuine "breadth and depth"? [1]

I suspect that's a genuinely tough attribute to imbue such a question with.
My personal leaning is that my role as a technical interviewer is to generate _extra discussion fuel_ so that in the _initial 15 minutes_ * that the candidate and I are forming a mutual opinion, I will get as representative a sampling as possible.

I tend to leave "rooting out the axe murderers" etc. to other stages in the process.    

* because yes, we're all grown ups here, right? Feel free to continue with the "endurance race" if you wish, if it makes you happy, though.   

So, anyhoo .... In the interest of proselytising for discussion topics that will generate _extra discussion fuel_, here's a little fun question I've been carting around for some time and it's grown to either 
* a number of sheets of paper, or
* one page of an entirely unusable font size

"implement the square root function"
---

https://en.wikipedia.org/wiki/Methods_of_computing_square_roots

### What one learns in asking this question

* Some people are really, really, frightened of sqrt() in this context. I am not judging, by the way.
* There is a giant range in the comfort level for working through the issues in implementing this _deceptively simple_ function.
* People are generally wrong to be frightened of the problem.
* There's a very large number of approaches that are recognisable.

It seems people pass through shock and a number of other stages when presented with this challenge: Denial, Anger, Bargaining, Depression.
I would like to think we can short-circuit this and skip straight to Acceptance (and a little Fun?).


### Unstructured points that may arise

* what is the return type? [return_type]
  * _extra discussion fuel_ for any proposals for arbitrary precision - oh, wait, is there a problem there? _extra discussion fuel_  
* ok, what's the input type? [input_type]
    * same as the return type? _extra discussion fuel_ why? [types_in_expressions] 
* ok, now what happens to the domain and range ? [domain_and_range]
	* _extra discussion fuel_ what's happened to the _number_ of bits of information we have in the input?
* what happens to 1?, > 1?, < 1? _extra discussion fuel_
    * is this going to influence your thinking on the approach you take?
* what is your criterion for accuracy?
    * how about sqrt(x) == sqrt(x) _extra discussion fuel_
    * how about float denormal [float_denormal]      
* TODO any more remaining unstructured points?
* what will we get for sqrt(2.0) [sqrt_unintuitive]
   * oh, that rabbit hole goes deep!
* "hey, what do CPUs do"? _extra discussion fuel_ [cpu_sqrt]
    * you may want to keep your powder dry when asked, so push it, and pop it later 	
* finally, $bright_spark may well know the POSIX proto: [posix_sqrt_proto]
  
		#include <math.h>
		double sqrt(double x);
		float sqrtf(float x);
		long double sqrtl(long double x);


Eight (or so) approaches
===

Caveat
---

Please remember it may be hard to find canonical examples "out there" of some of these algorithms.
This is because they are in fact, completely rubbish.
I'll try to point out the most egregious transgressions. 
The others are pretty much the Gold Standard, so I should really only direct anyone to other people's more considered knowledge on the topic.
Remember though, the name of the game here is to get _extra discussion fuel_, any and all means are acceptable.

Alien Technology
---

An additional benefit of these discussions is when a _novel implementation_ arises, having a little preparation will serve you well in recognising a variant of one of the following principles and steering the code/conversation in a more productive direction for _extra discussion fuel_.



Closed form FOR THE WIN
--

explanation: closed form for the win!

	return exp(0.5 * log(val));

This hinges on the identity

	log x^y = y log x

So we get	
	
	log x^0.5 = 0.5 * log x
	
Now full disclosure - I don't _miss_ slide rules in the classroom - (yes, that did in fact happen), but as a consequence of using this identity with a physical device this result does feel perfectly intuitive to me.
So much so I feel odd having to write the proof. 	
	
ooh ooh! _extra discussion fuel_ - which base might be better? TODO(PMM) I have no idea


Moving onto Search Algorithms
---

To go completely "in depth" on this would require a discussion of convergence criteria and how one would guarantee an iterative solution actually completes.  
TODO(PMM) - convergence tests and rules of thumbs
 

### Babylonian or Hero's method [babylonian]
The graphical explanation: iterative search for square root by successive reduction of difference in length between the 2 sides of a rectangle with the area of val.

	pick side
	derive other_side by A / side 
	if the same - stop!
	else split the difference for the next side and loop


and hence:

	double my_sqrt_bablyonian(double val) {

	  double x = seed_root();

	  while (fabs((x * x) - val) > (val * TOLERANCE)) {
	    x = 0.5 * (x + (val / x));
	  }
	  return x;
	}


You know, I wrote an explanation of the arithmetic when I was clearly off form (i.e. in the same slightly stunned state as the candidate), but now I am engrossed in writing this it seems slightly obvious...
In this case, it's best to press on.
The loop is controlled by a test on whether we're "near enough" to the answer _extra discussion fuel_ TODO(PMM) which alogorithm start starts taking forever for smaller inputs?

Note the new root guess reduces to x = 0.5 * 2 * x when x * x = val.

Finally, note the mechanism for generating a new input always narrows the difference between the input and value / input. TODO(PMM) - why is this enough for convergence?

  
Notable points:
* possibly the only algorithm that you can implement using a piece of rope and a setsquare.
* one fact I had not appreciated about this *bronze age* technique is that it reduces to one implementation of the following:- Newtown Raphson

### Newton Raphson
Explanation: Newton Raphson [newton_raphson] search for the root of (x^2 - value) 
  
	double my_sqrt_newtonraphson(double val) {
	
          double x = seed_root();
          
	  while (fabs((x * x) - val) > (val * TOLERANCE)) {
          // x * x - value is the function for which we seek the root
          double gradient = (((x * 1.5) * (x * 1.5)) - ((x * 0.5) * (x * 0.5))) / (x);
          x = x - ((x * x - value) / gradient);
	  }
	  return x;
	}
  
Graphical explanation:

	pick a trial value
	search for the zero by building a triangle from the current trial input and output and the gradient at that point, (for which the prior factoid is handy).
		- a numerically estimated gradient will do, for _extra discussion fuel_.
	the intersection of that triangle with zero is the new trial
	
For _extra discussion fuel_ see also related to the Householder methods [householder_methods]





### With Closed form for the gradient 
This implementation relies upon knowing the result `d(x^2)/x = 2x` and hence plugging in the closed form result for dy/dx as 2*x, so we can skip the noise of having to numerically estimate the gradient.

	double my_sqrt_newtonraphson(double val) {
	
          double x = seed_root();
          
	  while (fabs((x * x) - val) > (val * TOLERANCE)) {
	    // x * x - val is the function for which we seek the root
	    x = x - ((x * x - val) / _(2 * x)_);
	  }
	  return x;
	}
  

So far all the loops have used identical loops, merely with different expressions in the middle.
Let's take a closed look at that expression: that with the closed form for the gradient we get this expression:
      
      x = x - ((x * x - value) / (2 * x));

      factoring out 2 * x we get
      x = 0.5 * (2x - (x - (value /x)))
     
      and there we are: Hero's method from previously
      x = 0.5 * (x + (value / x)) 
      
So confession time - having encountered the two methods (Bablyonian and Newton Raphson) independently, I missed the equivalence between them until I printed out the iteration values.

Yet another confession - even with the mathematical equivalence there was still a difference as the version just shown has an issue - it fails to locate values roots above sqrt(std::numeric_limits<double>::max()). 

The fix - perhaps unsurprisingly enough - is thus:

         - double x = seed_root();
         + _long_ double x = seed_root();
	  
Another discussion point is the necessity of introducing the long version of the type in the algorithm. Is this a maintenance wart, or good numerical analysis?

Also, at this point, the candidate may re-visit their choice of input and output types.

The Bablyonian method is arguably more straightforward due to the simpler expression that eliminates the need to raise intermediate expressions to higher powers that run the risk of overflow. 

But, again all the above are good _extra discussion fuel_

TODO(PMM) work through pros and cons of long double vs. double


### Range reduction
explanation: range reduction approach (does not rely upon a good initial guess, though the bounds do need to be ordered).

	double my_sqrt_range(double val) {
	
    double upper = seed_root(value) * 10;
    double lower = seed_root(value) / 10;

    double x = (lower + upper) / 2;

    int n = 1;

    while ((n < RANGE_ITERATIONS) &&
           (fabs((x * x) - value) > (value * TOLERANCE))) {

      counter(n, lower, upper);

      if (((x * x) > value))
        upper = x;
      else
        lower = x;

      x = (lower + upper) / 2;
      n++;
    }

    return x;
  }



Note: rarely found in the wild as other better sqrt approaches are so well known.


### Guess, Step and Scan 
explanation: very naive guess step and scan approach, reversing and
decreasing step on each transition
vulnerable to overshoot if the transition is missed
discussion point: an improvement the step could always be adjusted to head
"the right way",
but the magnitude would only be adjusted upon a crossing
other discussion point - it turns out that the convergence is
 sensitive to the accuracy of the function near the roots - if loss of
precision leads to jagged
 behaviour convergence may be be poor
 
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
 

### Carmack method
explanation: just for fun, old example of a very fast approximate inverse square root.
Here is the obligatory xkcd reference [carmack_xkcd] still works (on Intel).
There is also a good writeup of how this even works [inverse_sqrt].
Note there are other values for the magic value than 0x5f375a86 - which oddly get more search hits(?!!).

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


TODO(PMM) - how the hell does this work?

### Quantum computer method ( Note: requires 2^64 qbits )

explanation: for each value in double: return value if value ^ 2 == input


## Conclusion

So, let's review what we can get out of "implement sqrt()" in terms of discussion topics: closed form results versus algorithmic solutions - some understanding of complexity analysis, discussion on the many interesting properties of floating point calculations, bronze age mathematical algorithms, consideration of domains and ranges.
I haven't even touched upon error handling, but it's needed. 
 
 

### What didn't make the cut

bogosqrt:
 
	d = random_double()
	while true:
		if (d * d== input) return d
		d = random_double()

run time: stochastically bounded
		
bozosqrt:
 
	d = min_double()
	while true:
		if (d * d== input) return d
		d = next_double(d)

run time: runs in constant time!
just a large constant!


worstsqrt:
	NOT ATTEMPTED


References
----


[TODOREF1] https://en.wikipedia.org/wiki/Methods_of_computing_square_roots
[TODOREF2] http://www.azillionmonkeys.com/qed/sqroot.html


[1] why are we using questions?




[return_type] TODO(PMM)

[input_type] TODO(PMM)

[types_in_expressions] TODO(PMM) 

[domain_and_range] TODO(PMM)

[float_denormal] https://en.wikipedia.org/wiki/Denormal_number      

[cpu_sqrt] TODO(PMM)

[posix_sqrt_proto] http://pubs.opengroup.org/onlinepubs/9699919799/functions/sqrt.html

[questions] also, "questions" ?

[householder_methods] https://en.wikipedia.org/wiki/Householder%27s_method
 
[carmack_xkcd] http://www.xkcd.com/664/ 

[inverse_sqrt] https://en.wikipedia.org/wiki/Fast_inverse_square_root
