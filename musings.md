## DONE So, what's with the title ?
	    It's cube root of 8 - next installment (just kidding)

## DONE Benefits of contemplating the layout of floating point
		they're sorted if treated bit-wise as integers?


## DONE So, the Hero solution is actually better in some ways, in not requiring long double.
		The long double is an intermediate calculation instead?
		Not having a conversion in the return statement avoids cognitive load or a masked bug
		also in a c++-ism having "long T" as the return value of a a function returning T ... 
       So, what dissuades people from hitting on this solution?
		Convergence anxiety?
		What would be a quick rule of thumb / heuristic for convergence?

## DONE Numerical differentiation NR version
            Also, geometric versus arithmetic mean?

	      double gradient = (((x * 1.5) * (x * 1.5)) - ((x * 0.5) * (x * 0.5))) / (x);

		my first instinct was to pick a smaller delta, which requires one more multiplication
		      (((x * 1.1) * (x * 1.1)) - ((x * 0.9) * (x * 0.9))) / (0.2 * x)
		      but no discernible difference! (even for the denorm)
		      
		      (x + b)^2 - (x-b)^2 / 2b [...]  => 2x!
		      
		      but ... "choice of b" - needs to scale with the value of x to be insensitive to scale 
		      
		      *if* you use x(1 - c) and x(1 + c) you get - x -b and x + b!
		      
		      [confession time] I picked 0.5x and 1.5x intuitively, having been hand-bodging numerical estimates into code since ZX81 days, so I didn't think too hard about it (this time) and hit a solution that can be transformed using simple algebra into the Hero solution.
		      This also resolved by puzzlement as to why the solution looked entirely identical
		      
		      TODO an estimating gradients digression would make a good interview topic
		      
## 	DONE (Yet another) reason why this article took so damn long
			Hopefully a picture is emerging - 
			[i] it's a nerd trap
			[ii] it's a deep topic (same as [i])?
			
			This of course, makes it a great interview topic!
			

## DONE Hero vs NR (closed form)


      x = 0.5 * (x + (value / x));
      
      ===
      
      x = x - ((x * x - value) / (2 * x));

      x = x - ((x - value / x) / (2));
      
      x = 0.5 * (2x - (x - (value /x)))
     
      x = 0.5 * (x + (value / x)) 
      
      

## DONE maybe swap the order of the NR examples to illustrate the difference?


##	DONE seed values
	value < 10:  2 * 10^n
	value >= 10: 6 * 10^n
	where n is value of mantissa
	
	or... use the !Carmack "magic number(s)" to seed - as noted in the Wikipedia article  


## DONE Don't fear the denorm! They're here to help!
Note the range is handled separately, and so far, all the approaches handle it fine


## DONE the quick integer solution?
- doesn't cover the full double range
- ignore

## DONE is there anything in <algorithm> to help?
- not for a real number domain...


## WTF IS THE MD SYNTAX?


``` C++
double gradient = (((x * 1.5) * (x * 1.5)) - ((x * 0.5) * (x * 0.5))) / (x);
```


