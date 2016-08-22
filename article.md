Eight Rooty Pieces
===

Interview Questions
===

_Sigh_ Some things we have to deal with.

Like Interview Questions.

I've been interviewing candidates a bit more recently and naturally some old questions I had have come to the fore on this activity.
To me it feels like there is a lot of advice on technical interviewing floating around. One outcome is the "well practiced interviewee" although I must observe many interviews ask questions bearing no relation to the final work.
This is not necessarily a bad idea: if the questions are not treated as an exercise in accumulating points, but instead designed to illuminate the candidate's specific domain expertise, breadth of experience or ability to work through a problem, one can learn effectively about the candidate.
Finally, if we want to hire people from whom we will learn something, how much will we glean from asking them to reproduce the answer we want to hear?

So are there interview questions that have genuine "breadth and depth"? [1]

My impression is that technical interview questions inherently are somewhat barren and will run out of steam quite quickly.
Having avoided the latter type of question, the next hurdle is when the candidate shows signs of being suitable for the next level of productive discussions, whether the interviewer has prepared sufficiently well.
Remember, the candidate is interviewing you simultaneously!

My entirely personal unscientific preference for my role in technical interviews is to generate _extra discussion fuel_ so that in the _initial 15 minutes_ that the candidate and I are forming a mutual opinion, I will get (and generate) as representative a sample as possible.
The candidate doesn't know what we know, and we don't know what they know and they will be on the spectrum of ability when it comes to blowing their own trumpet. 

In the interest of proselytising for discussion topics that will generate _extra discussion fuel_, here's a little fun question I've been carting around for some time and it's grown to being either
* a significant number of sheets of paper
* or one page of an entirely unusable font size


The Question
---

"please implement the square root function"
[wikipedia_sqrt]
[monkeys_sqrt]

### What one learns in asking this question

* First up: some people are really, really, frightened of sqrt() in this context. I am not judging, by the way.
* There is a giant range in the comfort level for working through the issues in implementing this _deceptively simple_ function.
* People are generally wrong to be frightened of the problem and often surprise themselves when they reach the end.
* There's a very large number of approaches that are recognisable.

So yes, it would be a fair point that there is a sneaky element of testing character and resilience with this question.
I am going to argue this is legitimate and worthwhile on my assertion that [i] it's not that hard and [ii] there is so much to discuss that running out of steam / time is not that much of an issue in the wider scheme of things.

Nevertheless it seems people pass through shock and a number of other stages when presented with this challenge: Denial, Anger, Bargaining, Depression.
I would like to think we can short-circuit this and skip straight to Acceptance (and perhaps a little Fun?).


### Initial Unstructured points 

The exercise typically goes through a number of phases, among the first of which should be something like scoping out the problem.
 
This can be a very revealing phase: testing the candidates' process for collecting information. 
Some make adequate assumptions and plough on, some ask about which arbitrary precision packages we're allowed to use.

Here's a list of things one might want to touch upon

* what is the return type? 
  * _extra discussion fuel_ for any proposals for arbitrary precision - oh, wait, is there a problem there? _extra discussion fuel_  
* what's the input type?
    * same as the return type? _extra discussion fuel_ why? [domain_and_range]
* ok, now what happens to the domain and range? [domain_and_range] 
	* _extra discussion fuel_ what's happened to the _number_ of bits of information we have in the input?
* what happens for inputs of 1?, > 1?, < 1? _extra discussion fuel_
    * is this going to influence your thinking on the approach you take?
* what is your criterion for accuracy?
    * how about sqrt(x) == sqrt(x) _extra discussion fuel_
    * how about float denormal [float_denormal]      
* assuming your input is a binary FP number, what about NAN?
* "oh hey, what do CPUs do"? _extra discussion fuel_ [cpu_sqrt]
    * you may want to keep your powder dry when asked, so push it, and pop it later 	
* finally, $bright_spark may well know the POSIX prototypes: [posix_sqrt_proto]
  
		#include <math.h>
		double sqrt(double x);
		float sqrtf(float x);
		long double sqrtl(long double x);


Eight approaches
===

Code demonstrating testable implementations of all the following is available at 

http://www.github.com/patrickmmartin/2.8284271247461900976033774484194

Caveat
---

Please remember that for some of the later implementations it may be hard to find canonical examples "out there" of some of these algorithms.
This is because they are in fact, completely rubbish.
I'll try to point out the most egregious transgressions. 
The others are pretty much shadows of the many Gold Standard, so I should really only direct anyone to other people's more considered knowledge on the topic.
Remember though, the name of the game here is to get _extra discussion fuel_, any and all means are acceptable.

Alien Technology
---

An additional benefit of these discussions is when a _novel implementation_ arises, having some preparation under your belt will serve you well in recognising a variant of one of the following principles and steering the code/conversation in a more productive direction for _extra discussion fuel_.
At this point, for those who are employing online code editors with the ability to run the code, this can be a real force multiplier for those candidates who are so minded, as this function is so easy to test and feed in edge cases. 


Closed form FOR THE WIN
--

Explanation: closed form for the win!

	return exp(0.5 * log(val));

This hinges on the identity

	log x^y = y log x


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

The loop is controlled by a test on whether we're "near enough" to the answer _extra discussion fuel_.

Finally, note the mechanism for generating a new trial value always narrows the difference between the trial and trial / input.
TODO(PMM) - why is this enough for convergence? gradient = 2x -> error proportional to DeltaX, hence reducing DeltaX can only reduce DeltaY

  
Notable points:
* possibly the only algorithm that you can implement using a piece of rope and a setsquare.
* one fact I had not appreciated about this *bronze age* technique is that it reduces to one implementation of the following:- Newton Raphson
* this algorithm is somewhat unique in that it can handle findng the negative root if that's the trial value generated TODO(PMM)

### Newton Raphson
Explanation: Newton Raphson [newton_raphson] searches for the root of (x^2 - value) 
  
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
Let's take a closer look at that expression: that with the closed form for the gradient we get this expression:
      
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
 

### "Homage to Carmack" method
explanation: just for fun, old example of a very fast approximate inverse square root.
Here is the obligatory xkcd reference [carmack_xkcd] still works (on Intel).
There is also a good writeup of how this even works [inverse_sqrt].
Note there are other values for the magic value than 0x5f375a86 - which oddly get more search hits(?!!).

	  // actually Chris Lomont version via SO, allegedly
	
	  float xhalf = 0.5f * x;
	  int i = *(int *)&x;        // get bits for floating value
	  i = 0x5f375a86 - (i >> 1); // gives initial guess y0
	  x = *(float *)&i;          // convert bits back to float
	
	  // initial guess: to within 10% already!
	  x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
	
	  // gah! no iterations!!!!
	
	  return 1 / x;

And the version supporting double

	  double xhalf = x * 0.5;
	  long long i = *(long long *)&x;    // get bits for floating value
	  i = 0x5fe6eb50c7b537a9 - (i >> 1); // gives initial guess y0
	  x = *(double *)&i;                 // convert bits back into double
	
	  x = x * (1.5f - xhalf * x * x);    // one Newton Raphson step
	
	  return 1 / x;


TODO(PMM) - explain how the hell does this work?

### Quantum computer method ( Note: requires up to 2^64 qbits )

explanation: for each value in double: return value if value ^ 2 == input

### "Also Ran"

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

	NOT ATTEMPTED (TODO(PMM) AWARD BONUS POINTS FOR THIS)


## Conclusion

So, let's review what we can get out of "implement sqrt()" in terms of discussion topics: closed form results versus algorithmic solutions - some understanding of complexity analysis, discussion on the many interesting properties of floating point calculations, bronze age mathematical algorithms, consideration of domains and ranges.
I haven't even touched upon error handling, but it's needed. 

## You may have some questions
Here's my attempt to anticipate them.

### What's with the name for the repo?
It's square root of 8 - cube root would have yielded a simpler name, but that article is still in the works. 

### Will the Fast sqrt work on big-endian?
Very funny.

References
----

[1] why are we using questions?

[wikipedia_sqrt] https://en.wikipedia.org/wiki/Methods_of_computing_square_roots

[monkeys_sqrt] http://www.azillionmonkeys.com/qed/sqroot.html

[domain_and_range]
For IEEE 754 double, the maximum sqrt will exceed the maximum value for IEEE 754 float, so this forces us to consider the same return type as the input type 

[float_denormal] https://en.wikipedia.org/wiki/Denormal_number      

[cpu_sqrt]
These might be using optimised hardware, native CPU commands or hand-crafted solutions.
In the silicon, one might find GoldSchmidt's method, or Newton Raphson

[posix_sqrt_proto] http://pubs.opengroup.org/onlinepubs/9699919799/functions/sqrt.html

[householder_methods] https://en.wikipedia.org/wiki/Householder%27s_method
 
[carmack_xkcd] http://www.xkcd.com/664/ 

[inverse_sqrt] https://en.wikipedia.org/wiki/Fast_inverse_square_root
