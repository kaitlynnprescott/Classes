public class CreditOffer
{
	public double membershipFee;
	public double cbr;
	public double apr;

	// creates a node storing the input data
	public double creditOffer(double fee, double cbr, double apr)
	{
		membershipFee = fee;
		this.cbr = cbr;
		this.apr = apr;
	}
}