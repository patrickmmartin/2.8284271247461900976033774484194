Eight Rooty Pieces
===


Interview Questions
---

_Sigh_ Some things we have to deal with...

Like Interview Questions...

Recently I've been interviewing candidates a bit more and naturally some old coding exercises I've collected over time have come to the fore, along with some impressions I've developed.

Let's assume it's that time in the interview when the candidate shows signs of being suitable to step up to the next level.
At this point it really starts to matter whether the interviewer has prepared sufficiently well for this eventuality.
Therefore, a question that has several such plateaus to provide some good challenge for the candidates who are on a roll would be very useful. 
I'm also suggesting the topic should generate _discussion points_ so that in the _initial 15 minutes_ that the candidate and I are forming a mutual opinion, I will get (and generate) as representative an impression as possible.
Remember, the candidate is interviewing you also, and they might well form an opinion if all you're asking them to do is regurgitate facts. 

So are there interview questions that have genuine "breadth and depth"? [1]

Well, here's a little fun question I've been carting around for some time that I aim to persuade you will generate _discussion points_, and my personal notes have grown to either being
* a significant number of sheets of paper
* or one page of an entirely unusable font size

So, without further ado.

The Question
---

"please implement the square root function"
[wikipedia_sqrt]
[monkeys_sqrt]

One thing I like about this question as that it's really quite easy to run and test even in some minimal web based online coding tool.

### What one learns in asking this question

#### First up: some people are really, quite wary of sqrt() in this context.
I am not judging, let us be clear.

#### There is a giant range in the comfort level for working through the issues in implementing this _deceptively simple_ function.

#### People are generally wrong to be frightened of the problem.
They often surprise themselves when they reach the end.
 
#### There's quite a few approaches that are recognisable.

#### 5.000000 stages of shock
It would be a fair point that there is a sneaky element of testing character and resilience with this question.
I am going to argue this is both legitimate and worthwhile, based on my assertion that [i] it's not that hard and [ii] there is so much to discuss that running out of steam / time is not that much of an issue in the wider scheme of things.

Nevertheless it seems people pass through shock and a number of other stages when presented with this challenge: Denial, Anger, Bargaining, Depression.
I would like to think we can short-circuit this and skip straight to Acceptance (and perhaps a little Fun?)- let's dive in and see what I'm talking about.


### Initial Unstructured points 

The exercise typically goes through a number of phases, sometimes the first of which is something like scoping out the problem.
 
This can be a very revealing phase: demonstrating the candidates' process for collecting information. 
Amusingly, some make adequate assumptions and plough on, because as we will see later: _"double is just fine"_ [domain_and_range], whereas some might ask about which arbitrary precision packages we're allowed to use.

Assuming we're here though: here's an incomplete list of things one might want to touch upon

* what is the return type? 
  * _discussion points_ might be considering arbitrary precision  
* what's the input type?
    * _discussion points_ - is it the same as the return type, what bit size is the range, compared to the domain? [domain_and_range]
* what happens for inputs of 1?, > 1?, < 1? negative values?
    * is this going to influence your thinking on the approach you take?
* what is your criterion for accuracy?
* how about float denormal values inputs, results [float_denormal]      
* what about NAN?
* "oh hey, what do CPUs do"? _discussion points_ [cpu_sqrt]
    * you may want to keep your powder dry when asked, so push it, and pop it later 	
* finally, $bright_spark may well know the POSIX prototypes: [posix_sqrt_proto]  
	this answers a lot of the above questions
  
		#include <math.h>
		double sqrt(double x);
		float sqrtf(float x);
		long double sqrtl(long double x);

Eight approaches
===

So, having got past the initial stage of get to know the question, it's probably time to start writing code.
Here follow 8 implementations of varying quality, nominally in c++. 

Code demonstrating c++ implementations with tests of all the following are available at  

http://www.github.com/patrickmmartin/2.8284271247461900976033774484194

### Caveat

Please remember that for some of these implementations it may be hard to find canonical examples "out there" of some of these algorithms.
This is because they are in fact, a bit rubbish.
The more "recognisable versions" are pretty much shadows of the many already thoroughly written-up versions already available for research.
Remember though, the name of the game here is to get _discussion points_, any and all means are acceptable.

### Alien Technology

An additional benefit of these discussions is when a _novel looking implementation_ arises, having some preparation under your belt will serve you well in recognising a variant of one of the following principles and steering the code/conversation in a more productive direction for _discussion points_.

## "One liners"
### Closed form FOR THE WIN

Explanation: closed form for the win!

	```c++
	return exp(0.5 * log(val));
	```

This hinges on the identity

	log x^y = y log x

Search Algorithms
---

This class of solutions hinge on iterating upon a trial value until convergence is attained - I've introduced a ```seed_root()``` function with no explanation that returns a "good initial guess" for sqrt() in order to concentrate on the details.
We'll come back to ```seed_root()``` later on.
 
### The Babylonian method or Hero's method [babylonian]
The graphical explanation of this algorithm is: iterative search for square root by successive reduction of difference in length between the 2 sides of a rectangle with the area of the input value.

	pick side
	derive other_side by A / side 
	if side == other_side - return side
	else split the difference for the next side and loop

and hence:

	double my_sqrt_bablyonian(double val) {

	  double x = seed_root();

	  while (fabs((x * x) - val) > (val * TOLERANCE)) {
	    x = 0.5 * (x + (val / x));
	  }
	  return x;
	}


The loop is controlled by a test on whether we're "near enough" to the answer which may be a _discussion points_.

Finally, note the mechanism for generating a new trial value always narrows the difference between the trial and trial / input.
 
Notable points:
* it's quite possibly the only algorithm to be presented here that you can implement using a piece of rope and a setsquare.
* this algorithm is somewhat unique in that it can handle findng the negative root if that's the trial value generated
* there is one more interesting fact we will discover shortly

### Finding the root using Newton Raphson
Explanation: Newton Raphson [newton_raphson] searches for the value of x yielding zero for (x^2 - value) 
 
Graphical explanation:

	pick a trial value
	search for the zero by building the line passing through
	the current trial input and output at the gradient of the function at that point
		- a numerically estimated gradient will do, for _discussion points_.
	the intersection of that triangle with zero is the new trial
	exit when desired accuracy attained
	
here's one interpretation:	
	
	```c++
	double my_sqrt_newtonraphson(double val) {
	
        double x = seed_root();
          
	  while (fabs((x * x) - val) > (val * TOLERANCE)) {
          // x * x - value is the function for which we seek the root
          double gradient = (((x * 1.5) * (x * 1.5)) - ((x * 0.5) * (x * 0.5))) / (x);
          x = x - ((x * x - value) / gradient);
	  }
	  return x;
	}
	```
  
For _discussion points_ see also related to the Householder methods [wikipedia_householder_methods]

### Newton Raphson With a closed form identity for the gradient 
Now, some may know that there is a very simple result `d(x^2)/x = 2x` for the gradient that is needed for Newton Raphson and hence plugging in the closed form result for dy/dx, we can skip some typing to yield this.

	```c++
	double my_sqrt_newtonraphson(double val) {
	
          double x = seed_root();
          
	  while (fabs((x * x) - val) > (val * TOLERANCE)) {
	    // x * x - val is the function for which we seek the root
	    x = x - ((x * x - val) / _(2 * x)_);
	  }
	  return x;
	}
	```
  
Note that original expression containing the gradient: 
  
    	      ```c++
    	      double gradient = (((x * 1.5) * (x * 1.5)) - ((x * 0.5) * (x * 0.5)))
    	      ```

This is the lazy man's version of calculating the gradient around the domain value ```x``` using the values at ```x +/- b``` 				
					      
      (x + b)^2 - (x - b)^2 / 2b
      =>
      x^2 + 2bx + b^2 - x^2 + 2bx - b^2 / 2b!
      =>
      2x!
		      
		      
If ```b``` were a constant this would not scale with the value of x, however ```b``` can be substituted by ```x/2``` and we recover the initial gradient calculation, and hence an equivalent expression for the closed form expression.   
		      
[confession time] I first picked ```0.5 * x``` and ```1.5 * x``` intuitively, having been hand-bodging numerical estimates into code for some time now, so I didn't think too hard about it (this time around) and serendipitously hit a solution that can be transformed using simple algebra into the closed form solution.

#### 3.0, 2.0 or 1.0 methods? 

So far the last 3 loops have used identical loops, merely with different expressions for generating new trial values in the middle.
Let's take a closer look at that expression: that with the closed form for the gradient we get this expression:

      x = x - ((x * x - value) / (2 * x));
      =>
      x = 0.5 * (2x - (x - (value /x)))
      =>
      x = 0.5 * (x + (value / x))
      
Which is the Hero's method expression, so the final notable point about Hero's method is that it's a condensed version of the more taxing Newtwon Raphson approach.           

#### Confession Time
          
Having encountered the two methods (Bablyonian and Newton Raphson) independently, I missed the equivalence between them until I took a look at the iteration values.

Another confession - even with the mathematical equivalence there was still a difference as the version just shown has an issue - it fails to locate values for roots above sqrt(std::numeric_limits<float>::max()).
This is due to an overflow in the expression to generate the  

The fix - perhaps unsurprisingly enough - is thus:

         - double x = seed_root();
         + _long_ double x = seed_root();
	  
Another set of _discussion_points_ arise from the necessity of introducing the long version of the type in the algorithm.
Is this choice, leading to an implicit conversion in the return statement a maintenance wart?
What if we need this to be a generic algorithm, parameterised on the input type? 

## Slow but sure (?)

### A Range Reduction approach

Graphical Explanation: a range reduction approach which aims to halve the range [upper, lower] upon each iteration (does not rely upon a particularly good initial guess, though the bounds do need to be ordered).
Newton Raphson / Hero can be proven to converge quadratically [wikipedia_convergence], whereas this approach effectively converges linearly, hence it requires many more iterations.
The algorithm takes 30 iterations for a double sqrt as achieving over 10 digits of decimal precision will typically require approximately 30 halvings of the interval.  

    ```c++
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
    }```

If this is found in the wild. it would probably be best to put it out of its misery.
The possible benefit of this is that candidates less confident of their mathematics will be able to implement this by concentrating purely upon the logic of searching 


### Scan and step reduction 

This is a very naive guess step and scan approach, reversing and decreasing step on each transition.
Feed it a decent enough initial guess and it will work its way towards the solution, as it is another linearly convergent solution.  
 
	 ```c++
	 double my_sqrt_naive(double val) {
	    int n = 1;
	    double x = seed_root(value) / 2;
	    double step = x / 4;
	    double lastdiff = 0;
	    double diff = (x * x) - value;
	
	    while ((n < RANGE_ITERATIONS) && (fabs(diff) > (value * TOLERANCE))) {
	      if (diff > 0)
	        x -= step;
	      else
	        x += step;
	
	      if ((diff > 0) != (lastdiff > 0)) {
	        step = step * 0.5;
	      }
	      lastdiff = diff;
	      diff = (x * x) - value;
	    }
	
	    return x;
	} 
	```
 	

### "Homage to Carmack" method

Finally, the origin of seed_root() can be revealed.
Yes, just for fun, an old example of a very fast approximate inverse square root.
Here is the obligatory xkcd reference [carmack_xkcd].
This still works (on Intel), and there is also a good write-up of how this works [inverse_sqrt].
Note there are other values for the magic value than 0x5f375a86 - which oddly get more search hits in Google(?!!).

The original code, sadly has comments and ```#ifdef``` rendering it unsuitable for printing in a family oriented programming publication, so here is modified version from [SO_chris_lomont].

	```c++
	float my_sqrt_homage_to_carmack(float val) {
		// PMM: adapted from the doubly cleaner Chris Lomont version
		
		float xhalf = 0.5f * x;
		int i = *(int *)&x;        // get bits for floating value
		i = 0x5f375a86 - (i >> 1); // gives initial guess y0
		x = *(float *)&i;          // convert bits back to float
		
		// PMM: initial guess: to within 10% already!
		x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
		
		return 1 / x;
	  }
	  ```

And here is a version supporting double, with the appropriate 64-bit magic value. 

	```c++
	double my_sqrt_homage_to_carmack64(double x) {
		double xhalf = x * 0.5;
		long long i = *(long long *)&x;    // get bits for floating value
		i = 0x5fe6eb50c7b537a9 - (i >> 1); // gives initial guess y0
		x = *(double *)&i;                 // convert bits back into double
		
		x = x * (1.5f - xhalf * x * x); // one Newton Raphson step
		
		return 1 / x;
	}
	```


The result is not super accurate, but works in constant time and can be used as a seed into another algorithm.

For the most condensed explanation as to how that even works, see the closed form solution and consider that the bits of a floating point number when interpreted as an integer can be used to approximate its logarithm.  

## "Also Ran"

In the grand tradition of sort algorithms [wikipedia_bogosort], one could always "break the ice" by discussing solutions that make brute force look cunning.   

### brutesqrt
 
	d = min_double()
	while true:
		if (d * d == input) return d
		d = next_double(d)
		

### bogosqrt (homage to bogosort) 
 
	d = random_double()
	while true:
		if (d * d== input) return d
		d = random_double()

This and the prior approach will need an approach to define the accuracy of match.
And perhaps a rather forgiving user calling that code.

### Quantum computer method

	for value in all_doubles:
		return value if value ^ 2 == input
		
It would be hoped that parallelising this would lead to good wall clock times?		

## Conclusion

So, let's review what we can get out of "implement sqrt()" in terms of discussion topics: closed form results versus algorithmic solutions - discussion on the many interesting properties of floating point calculations, bronze age mathematical algorithms, consideration of domains and ranges.
I haven't even touched upon error handling, but it's needed. 

## You may have some questions
Here's my attempt to anticipate them.

### What's with the name for the repo?
It's the square root of 8, the number of methods, of course cube root would be have yielded a simpler name - presaging the next installment!
Note of course, *there will be no next installment*, as one thing we have learned is that this topic is a *giant nerd trap*.
Merely persuing the references to this article for a short time will show how many areas of exploration exist to be followed. 

### Will the Fast sqrt work on big-endian?
Very funny.

References
----

[1] why are we using questions?

[wikipedia_sqrt] https://en.wikipedia.org/wiki/Methods_of_computing_square_roots

[monkeys_sqrt] http://www.azillionmonkeys.com/qed/sqroot.html

[domain_and_range]
For IEEE 754 double, the maximum sqrt will exceed the maximum value for IEEE 754 float, so this forces us to consider the same return type as the input type

[all_the_nans] https://en.wikipedia.org/wiki/NaN 

[float_denormal] https://en.wikipedia.org/wiki/Denormal_number      

[cpu_sqrt]
These might be using optimised hardware, native CPU commands or hand-crafted solutions.
In the silicon, one might find GoldSchmidt's method, or Newton Raphson

[posix_sqrt_proto] http://pubs.opengroup.org/onlinepubs/9699919799/functions/sqrt.html

[wikipedia_householder_methods] https://en.wikipedia.org/wiki/Householder%27s_method

[wikipedia_convergence] https://en.wikipedia.org/wiki/Rate_of_convergence
 
[carmack_xkcd] http://www.xkcd.com/664/

[SO_chris_lomont] http://stackoverflow.com/questions/1349542/john-carmacks-unusual-fast-inverse-square-root-quake-iii
 
[inverse_sqrt] https://en.wikipedia.org/wiki/Fast_inverse_square_root

[wikipedia_bogosort] https://en.wikipedia.org/wiki/Bogosort

