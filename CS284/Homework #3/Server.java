public class Server
{
	// Data fields
	/** If the server is Idle. */
	private boolean idle;
	/** Keeps track of the FF entries that have been processed.*/
	private int currFF;

	// Constructor
	public server()
	{
		idle = true;
		currFF = 0;
	}

	public boolean isIdle()
	{return idle;}

	public void setIdle()
	{idle = true;}

	public void setBusy()
	{idle = false;}
	
}