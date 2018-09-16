/*
 * Authors: Chris Rudel, Meng Qiu, Katie Prescott
 * Pledge: We pledge our honor that we have abided by the Stevens Honor System.
 * File: MAWT.java
 * Date: 4/30/2018
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class MAWT 
{
	public static void main(String[] args) 
	{
		// scanning the input
		Scanner sc = new Scanner(System.in);

		// number of lines
		int n = sc.nextInt();
		// array of customers from input
		Customer[] c = new Customer[n];
		// get each new line of input and save it as a customer in the array
		for (int i = 0; i < c.length; i++) 
		{
			int orderTime = sc.nextInt();
			int cookTime = sc.nextInt();
			c[i] = new Customer(orderTime, cookTime);
		}

		// sort the array based on order time
		Arrays.sort(c, (c1, c2) -> c1.orderTime - c2.orderTime);


		MinHeap waitings = new MinHeap();
		long currentTime = 0;
		long totalWaitingTime = 0;
		int index = 0;
		// heap not empty or index within range
		while (!waitings.isEmpty() || index < c.length) 
		{
			// index within range and the order time has already occured
			while (index < c.length && c[index].orderTime <= currentTime) 
			{
				// add it to the heap and increase index
				waitings.add(c[index]);
				index++;
			}
			if (waitings.isEmpty()) 
			{
				// heap is empty, so current time is set to last order time
				currentTime = c[index].orderTime;
				continue;
			}

			// serve the customers
			Customer served = waitings.removeTop();
			// increase current time to be when the current pizza will be finished
			currentTime += served.cookTime;
			// get the total wait time
			totalWaitingTime += currentTime - served.orderTime;
		}
		// print out the minimum average waiting time for this set of customers
		System.out.println(totalWaitingTime / c.length);

		sc.close();
	}
}

class Customer 
{
	// each customer has an order time and a cook time
	int orderTime;
	int cookTime;

	Customer(int orderT, int cookT) 
	{
		this.orderTime = orderT;
		this.cookTime = cookT;
	}
}

class MinHeap 
{
	// make a min heap using an arraylist of customers
	ArrayList<Customer> customers = new ArrayList<Customer>();

	void swap(int fst, int snd) 
	{
		Customer temp = customers.get(fst);
		customers.set(fst, customers.get(snd));
		customers.set(snd, temp);
	}

	void add(Customer c) 
	{
		// add the customer to array list
		customers.add(c);

		// get new index (last one in arraylist)
		int childIndex = customers.size() - 1;
		while (true) 
		{
			// get the parent index
			int parentIndex = (childIndex - 1) / 2;

			// get the cook time of the child
			if (parentIndex < 0 || customers.get(parentIndex).cookTime <= customers.get(childIndex).cookTime) {
				break;
			}

			// swap the parent and child 
			swap(parentIndex, childIndex);
			childIndex = parentIndex;
		}
	}

	Customer removeTop() 
	{
		// get first customer 
		Customer top = customers.get(0);

		// swap it with the last customer and remove it
		swap(0, customers.size()-1);
		customers.remove(customers.size() - 1);

		int parentIndex = 0;
		while (true) 
		{
			// re-order heap after removal to restore heap properties
			int leftChildIndex = parentIndex * 2 + 1;
			int rightChildIndex = parentIndex * 2 + 2;

			if ((leftChildIndex >= customers.size() || customers.get(parentIndex).cookTime <= customers.get(leftChildIndex).cookTime) && (rightChildIndex >= customers.size() || customers.get(parentIndex).cookTime <= customers.get(rightChildIndex).cookTime)) {
				break;
			}

			int childIndex;
			if (rightChildIndex >= customers.size() || customers.get(leftChildIndex).cookTime <= customers.get(rightChildIndex).cookTime) {
				childIndex = leftChildIndex;
			} else {
				childIndex = rightChildIndex;
			}
			swap(parentIndex, childIndex);
			parentIndex = childIndex;
		}

		// return the one removed
		return top;
	}

	boolean isEmpty() {
		// checks if heap is empty
		return customers.isEmpty();
	}
}
