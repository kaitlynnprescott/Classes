import javaz.swing.JOptionPane;
import java.io.File;
import java.io.FileReader;
import java.util.Properties;
import java.util.Queue;
import java.util.Random;
import java.util.ArrayDeque;
import java.util.Scanner;


public class BLUSAcheckin 
{
	//Data Fields
	/** Queue of frequent flyers.*/
	private PassengerQueue frequentFlyerQueue 
					= new PassengerQueue("Frequent Flyer");
	/** Queue of regular passengers.*/
	private PassengerQueue regularPassengerQueue 
					= new PassengerQueue("Regular Passenger");
	/** Maximum number of frequent flyers to be served before a regular passenger gets served.*/
	private int frequentFlyerMax;
	/** Maximum time to service a passenger.*/
	private int maxProcessingTime;
	/** Total simulated time.*/
	private int totalTime;
	/** If set true, print additional output.*/
	private boolean showAll;
	/** Simulated clock.*/
	private float clock = 0;
	/** Time that the agent will be done with the current passenger.*/
	private int timeDone;
	/** Number of frequent flyers served since the last regular passenger was served.*/
	private int frequentFlyersSinceRP;
	/** Random Arrival. */
	
	
	private void enterData()
	{
		System.out.print("Expected number of frequent flyer arrivals per hour: ");
		double freqFlyers = input.nextDouble();
		frequentFlyerQueue.setArrivalRate(freqFlyers);
		System.out.print("Expected number of regular passenger arrivals per hour: ");
		double regPass = input.nextDouble();
		regularPassengerQueue.setArrivalRate(regPass);
		System.out.print("Max number of frequent flyers served between regular passengers: ");
		frequentFlyerMax = input.next();
		System.out.print("Max service time in minutes: ");
		maxProcessingTime = input.next();
		Passenger.setMaxProcessingTime(maxProcessingTime);
		System.out.print("Total simulation time in minutes: ");
		totalTime = input.next();
		System.out.print("Display Simulation? (Y or N): ");
		String show = input.next();
		if (show.equalsIgnoreCase("y")) 
		{
			showAll = true;
		}
		else
		{
			showAll = false;
		}
	}	

	private void runSimulation()
	{
		for (clock = 0; clock < totalTime; clock++) 
		{
			frequentFlyerQueue.checkNewArrival(clock, showAll);
			regularPassengerQueue.checkNewArrival(clock, showAll);
			if (clock >= timeDone) 
			{startServe();}
		}
	}

	private void startServe()
	{
		if (!frequentFlyerQueue.isEmpty() && ((frequentFlyersSinceRP <= frequentFlyerMax) || regularPassengerQueue.isEmpty())) 
		{
			frequentFlyersSinceRP++;
			timeDone = frequentFlyerQueue.update(clock, showAll);
		}
		else if (!regularPassengerQueue.isEmpty()) 
		{
			frequentFlyersSinceRP = 0;
			timeDone = regularPassengerQueue.update(clock, showAll);
		}
		else if (showAll) 
		{
			System.out.println("Time is: " + clock + ", server is idle.");
		}
	}

	private void showStats()
	{
		System.out.println("\nThe number of regular passengers served was " + regularPassengerQueue.getNumServed());
		double averageWaitTimeR = (double) regularPassengerQueue.getTotalWait() / (double) regularPassengerQueue.getNumServed();
		System.out.println(" with and average waiting time of " + averageWaitTimeR + ".");
		System.out.println("The number of frequent flyers served was " + frequentFlyerQueue.getNumServed());
		double averageWaitTimeF = (double) frequentFlyerQueue.getTotalWait() / (double) frequentFlyerQueue.getNumServed();
		System.out.println(" with an average waiting time of " + averageWaitTimeF + ".");
		System.out.println("Passengers in frequent flyer queue: " + frequentFlyerQueue.size());
		System.out.println("Passengers in regular passenger queue: " + regularPassengerQueue.size());
	}

	/** Main function.
		@param args not used*/
	public static void main(String[] args) 
	{
		BLUSAcheckin sim = new BLUSAcheckin();
		sim.enterData();
		sim.runSimulation();
		sim.showStats();
	}
}