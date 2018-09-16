import java.util.*;

public class MyMaxHeap
{
	public int size;
	public int capacity;
	public creditOffer[] theHeap;

	private static final int FRONT = 1;

	// creates a heap with capacity = 5
	public MyMaxHeap()
	{
		capacity = 5;
		size = 0;

	}
	// creates a heap by inserting the elements of the input array arr
	public MyMaxHeap(creditOffer[] arr, int n, double monthlyExpenses)
	{
		if (arr == null)
		{
			capacity = 5;
			size = 0;
		}
		else
		{
			if (n < 0)
			{
				n = 0;
			}
			else if (n > arr.length)
			{
				n = arr.length;
			}
			theHeap = arr;
			size = n;
			build();
		}
	}
	//returns size of heap
	public int size()
	{
		return size;
	}
	//adds element and reheaps
	public boolean add(creditOffer job)
	{
		theHeap[++size] = job;
		int current = size;

		while (theHeap[current] > theHeap[parent(current)])
		{
			swap(current, parent(current));
			current = parent(current);
		}
	}
	// returns the node with the highest score and reheaps
	public Object removeMax()
	{
		creditOffer pop = theHeap[FRONT];
		theHeap[FRONT] = theHeap[size--];
		adjust(FRONT);
		return pop;

	}
	// prints all the elements in the order they are stored
	public void showList()
	{
		for (int i = 0; i == size; i++) 
		{
			System.out.println(theHeap[i]);
		}
	}
	
	public boolean isEmpty()
	{
		if (theHeap.length <= 0)
		{
			return true;
		}
		return false;
	}
	
	Object peek()
	{
		if(size <= 0)
    {
      return null;
    }
    return theHeap[0];
	}
	// swaps nodes with indices i and j
	private void swap(int i, int j)
	{
		creditOffer temp;
		temp = theHeap[i];
		theHeap[i] = theHeap[j];
		theHeap[j] = temp;
	}
	// compares nodes with indices i and j
	public int compare(int i, int j)
	{
		double score1 = theHeap[i].cbr - theHeap[i].membershipFee - theHeap[i].apr;
		double score2 = theHeap[j].cbr - theHeap[j].membershipFee - theHeap[j].apr;
		if (score1 > score2)
		{
			return 1;
		}
		if (score2 > score1)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}

	private int parent(int c)
	{
		if (c % 2 == 1)
		{
			return (c - 1) / 2;
		}
		else 
		{
			return (c - 2) / 2;
		}
	}

	private int leftChild(int p)
	{
		return (2 * p);
	}

	private int rightChild(int p)
	{
		return (2 * p) + 1;
	}

	private boolean isLeaf(int p)
	{
		if (p >= (size / 2) && p <= size)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	private void adjust(int pos)
	{
		if (!isLeaf(pos))
		{
			if (theHeap[pos] < theHeap[leftChild(pos)] || theHeap[pos] < theHeap[rightChild(pos)])
			{
				if (theHeap[leftChild(pos)] > theHeap[rightChild(pos)])
				{
					swap(pos, leftChild(pos));
					adjust(leftChild(pos));
				}
				else
				{
					swap(pos, rightChild(pos));
					adjust(rightChild(pos));
				}
			}
		}
	}

	private void build()
	{
		for (int i = (size / 2); i >= 1; i--)
		{
			adjust(i);
		}
	}
}