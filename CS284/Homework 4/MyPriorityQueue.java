/*  @Author Katie Prescott
	@pledge I pledge my honor that I have abided by the Stevens 
	Honor System. 
	*/
import java.util.*;
import java.io.*;

public class MyPriorityQueue
{
	private MyMaxHeap the_queue;
	// creates an empty priority queue
	public MyPriorityQueue(double monthlyExpenses)
	{
		the_queue = new MyMaxHeap();
	}
	//creates a priority queue out of an array of n credit offer nodes
	public MyPriorityQueue(creditOffer[] arr, int n, double monthlyExpenses) 
	{
		the_queue = new MyMaxHeap(arr, n, monthlyExpenses);
	}
	//adds a new element to the queue and returns true
	public boolean offer(creditOffer newOffer)
	{
		return the_queue.add(newOffer);
	}
	// removes first node in queue and returns it or 
	//returns null if empty
	public void remove() 
	{
		the_queue.removeMax();
	}
	// returns the item in the front of the queue 
	//without removing it or null if empty
	public Object peek()
	{
		if (the_queue.isEmpty())
		{
			return null;
		}
		else
		{
			return the_queue.peek();
		}
	}
	//returns true if the queue is empty
	public boolean isEmpty()
	{
		if (the_queue.size <= 0)
		{
			return true;
		}
		return false;
	}
	// prints all the elements in the queue in the order they are stored
	public void showList()
	{
		the_queue.showList();
	}

	public static void main(String[] args) 
	{
		// declare local variables here
		double number;
		try
		{
			BufferedReader in= new BufferedReader(new
				FileReader(new File("offers.txt")));
			for(String inputLine= in.readLine();
				inputLine!=null; inputLine=in.readLine())
			{
				// split string and only process first number read
				String[] splits = inputLine.split(" ");
				System.out.println("Read: "+ inputLine);
				if(splits[0].length()!=0)
				{
					for(int j=0;j<splits.length; j++)
					{
						number = Double.parseDouble(splits[j]);
						System.out.println("Next int: "+ number);
					}
				}
			}
			in.close();
		}
		catch(IOException e)
		{
			System.out.println("File I/O error");
			System.exit(1);
		}
	}
}