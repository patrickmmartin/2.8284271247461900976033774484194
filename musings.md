## So, what's with the title ?
    It's cube root of 8 - next installment (just kidding)

## So, the hero solution is actually better in some ways, in not requiring long double.
        So, what dissuades people from hitting on this solution? Convergence anxiety?

## Numerical differentiation NR version
            Also, geometric versus arithmetic mean?

	      double gradient = (((x * 1.5) * (x * 1.5)) - ((x * 0.5) * (x * 0.5))) / (x);

		my first instinct was to pick a smaller delta, which requires one more multiplication
		      (((x * 1.1) * (x * 1.1)) - ((x * 0.9) * (x * 0.9))) / (0.2 * x)
		      but no discernible difference! (even for the denorm)






## Hero vs NR (closed form)


      x = 0.5 * (x + (value / x));
      
      ===
      
      x = x - ((x * x - value) / (2 * x));

      x = x - ((x - value / x) / (2));
      
      x = 0.5 * (2x - (x - (value /x)))
     
      x = 0.5 * (x + (value / x)) 
      
      

DONE maybe swap the order of the NR examples to illustrate the difference?


	seed values
	value < 10:  2 * 10^n
	value >= 10: 6 * 10^n
	where n is value of mantissa
	
	or... use the !Carmack "magic number(s)" to seed - as noted in the Wikipedia article  


## Don't fear the denorm! They're here to help!
Note the range is handled separately, and so far, all the approaches handle it fine


## the quick integer solution?
- doesn't cover the full double range

## is there anything in <algorithm> to help?
- not for a real number domain...

