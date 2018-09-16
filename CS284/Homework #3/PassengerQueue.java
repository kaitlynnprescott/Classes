import java.util.LinkedList;
import java.util.Queue;

public class PassengerQueue
{
	//Data fields
	/* Create the passenger queue. */
	private Queue<Passenger> theQueue;
	/* Number of passengers served. */
	private int numServed;
	/* Total wait time for passengers. */
	private int totalWait;
	/* The name of the queue. */
	private String queueName;
	/* The arrival rate of the passengers. */
	private double arrivalRate;

	// Constructor
	/** Construct a PassengerQueue with the given name.
		@param queueName the name of this queue*/
	public PassengerQueue(String queueName)
	{
		numServed = 0;
		totalWait = 0;
		this.queueName = queueName;
		theQueue = new LinkedList<Passenger>();
	}
	/** Return the number of passengers served.
		@return The number of passengers served. */
	public int getNumServed()
	{return numServed;}

	/** Return the total wait time.
		@return The total wait time. */
	public int getTotalWait()
	{return totalWait;}

	/** Return the queue name.
		@return The queue name. */
	public String getQueueName() 
	{return queueName;}

	/** Set the arrival rate.
		@param arrivalRate the value to set. */
	public void setArrivalRate(double arrivalRate)
	{this.arrivalRate = arrivalRate;}

	/** Determine if the passenger queue is empty.
		@return True if the passenger queue is empty.*/ 
	public boolean isEmpty()
	{return theQueue.isEmpty();}

	/** Determine the size of the passenger queue.
		@return the size of the passenger queue. */
	public int size() 
	{return theQueue.size();}

	/** Check if a new arrival has occurred. 
		@param clock The current simulated time
		@param showAll Flag to indicate that detailed 
						data should be output. */
	public void checkNewArrival(int clock, boolean showAll)
	{
		if (Math.random() < arrivalRate) 
		{
			theQueue.add(new Passenger(clock));
			if (showAll) 
			{
				System.out.println("Time is " + clock + ": " + queueName + " arrival, new queue size is " + theQueue.size());
			}
		}
	}

	/** Update Statistics.
		pre: The Queue is not empty.
		@param clock The current simulated time.
		@param showAll Flag to indicate whether to show details.
		@return Time passenger is done being served.*/
	public int update(int clock, boolean showAll)
	{
		Passenger nextPassenger = theQueue.remove();
		int timeStamp = nextPassenger.getArrivalTime();
		int wait = clock - timeStamp;
		totalWait += wait;
		numServed++;
		if (showAll) 
		{
			System.out.println("Time is " + clock + ": Serving " + queueName + " with time stamp " + timeStamp);
		}
		return clock + nextPassenger.getProcessingTime();
	}
}
