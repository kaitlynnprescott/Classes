/************************************************************************************
 * Name        : Assignment2.java
 * Author      : Kaitlynn Prescott && Jennifer Cafiero
 * Date        : Oct 9, 2017
 * Description : CS-511 Assignment2: Gym
 * Pledge      : We pledge our honor that we have abided by the Stevens honor system.
 ************************************************************************************/

public class Assignment2 {
	public static void main(String[] args) {
		Thread thread = new Thread(new Gym());
		thread.start();

		try {
			thread.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}