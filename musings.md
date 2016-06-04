      x = 0.5 * (x + (value / x));
      
      ===
      
      x = x - ((x * x - value) / (2 * x));

      x = x - ((x - value / x) / (2));
      
      x = 0.5 * (2x - (x - (value /x)))
     
      x = 0.5 * (x + (value / x)) 
      
      


	seed values
	value < 10:  2 * 10^n
	value >= 10: 6 * 10^n
	where n is value of mantissa 