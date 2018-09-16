// Kaitlynn Prescott
// I pledge my honor that I have abided by the Stevens honor system.
public class Polynomials {
	public int degree;
	public double[] coefficients;
	public Polynomials(double[] coefficients)
	{
		//first check if coefficients is null
		if (coefficients == null)
			{
				System.out.println ("Coefficients cannot be a null array");
				System.exit(1);
			}
		// not null, so store values 
		this.coefficients = coefficients;
		this.degree = coefficients.length - 1;
	}
	public double ComputeValue(double x)	
	// compute the value when given x for the polynomial
	{
		double value = 0;
		for (int i = 0; i < degree; i++)
		{
			value += coefficients[i] * Math.pow(x, i);
		}
		return value;
	}
	public Polynomials add(Polynomials g)
	// add polynomial g to the original polynomial
	{
		int max = Math.max(this.degree, g.degree);
		double[] newPoly = new double[max + 1];
		if (g.coefficients == null)
			// check if coefficients is null
		{
			System.out.println("Coefficiants cannot be a null array.");
			System.exit(1);
		}
		if (coefficients.length == g.coefficients.length)
			// are polynomials the same length?
		{
			for (int i = 0; i < coefficients.length; i++)
			{
				newPoly[i] = coefficients[i] + g.coefficients[i];
			}
		}
		if((coefficients.length - 1) == max)
			// original polynomial is of higher degree than second
		{
			for (int i = 0; i < g.coefficients.length; i++)
			{
				newPoly[i] = coefficients[i] + g.coefficients[i];
				
			}
			for (int i = g.coefficients.length; i < coefficients.length; i++)
			{
				newPoly[i] = coefficients[i];
			}
		}
		if ((g.coefficients.length - 1) == max)
			// second polynomial is of higher degree than original
		{
			for (int i = 0; i < coefficients.length; i++)
			{
				newPoly[i]= coefficients[i] + g.coefficients[i];
				
			}
			for (int i = coefficients.length; i < g.coefficients.length; i++)
			{
				newPoly[i] = g.coefficients[i];
			}
		}
		// store new polynomial
		Polynomials added = new Polynomials(newPoly);
		return added;
	}

	public String toString()
	// print the new polynomial
	{
		String result = "S(x) = ";
		for (int i = this.coefficients.length - 1; i > 0; i--)
		{
			result += (this.coefficients[i] + "x^" + i + " + ");
		}
		result += (this.coefficients[0]);
		return result;
	}
	
	public static void main(String[] args) 
	{
		double[] acoeffs = {1, 2, 3, 4};
		double[] bcoeffs = {5, 6, 7, 8};
		Polynomials a = new Polynomials(acoeffs);
		Polynomials b = new Polynomials(bcoeffs);
		Polynomials c = a.add(b);
		System.out.println(c);
		
		double[] pcoeffs = {5, -4, 3, 6, 10};
		Polynomials p = new Polynomials(pcoeffs);
		double [] qcoeffs = {3, -2.1, .5};
		Polynomials q = new Polynomials(qcoeffs);
		Polynomials z = p.add(q);
		System.out.println(z);
		
		double[] jcoeffs = {6, 3, 1};
		Polynomials j = new Polynomials(jcoeffs);
		double[] kcoeffs = {5, 6, 7, 4, 9};
		Polynomials k = new Polynomials(kcoeffs);
		Polynomials l = j.add(k);
		System.out.println(l);
	}
}