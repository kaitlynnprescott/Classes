import java.util.Random;

/** A class to represent a passenger.*/
public class Passenger
{
	//Data fields
	/** The ID number for this passenger.*/
	private int passengerID;
	/** The time needed to process this passenger.*/
	private float processingTime;
	/** The time this passenger Arrives.*/
	private float arrivalTime;
	/** The maximum time to process a passenger.*/
	private static float maxProcessingTime;
	/** The sequence number for passengers.*/
	private static int idNum = 0;

	/** Create a new passenger.
		@param arrivalTime The time this passenger arrives.*/
	public Passenger(int passengerID, float arrivalTime, boolean frquentFlyer, float processingTime)
	{
		passengerID = idNum++;
		this.arrivalTime = arrivalTime;
		processingTime = clock - log(1 - randArrival.nextFloat())/LAMBDA;
		
	}

	/** Get the arrival time.
		@return The arrival time*/
	public int getArrivalTime()
	{return arrivalTime;}

	/** Get the processing time.
		@return the processing time.*/
	public int getProcessingTime()
	{return processingTime;}

	/** Get the passenger ID.
		@return the passenger ID.*/
	public int getID()
	{return passengerID;}

	/** Set the maximum processing time
		@param maxProcessingTime the new value.*/
	public static void setMaxProcessingTime(int maxProcessTime)
	{maxProcessingTime = maxProcessTime;}
}