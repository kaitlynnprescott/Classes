/************************************************************************************
 * Name        : LargeSum.java
 * Author      : Kaitlynn Prescott, Christopher Rudel, Meng Qiu
 * Date        : Jan 26, 2018
 * Description : Project Euler #13
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

import java.util.*;
import java.lang.*;
import java.io.*;

class LargeSum {

	public static void main(String[] args) {
		// scan in the test file
		try {
			File file = new File("input1.txt");
			Scanner reader = new Scanner(file);
		
			// there are 0 numbers in the file
			if (!reader.hasNext()) {
				System.out.println("Full sum: 0");
				System.out.println("First 10 digits: 0");
			}
			// there is only 1 number in the file
			// get first line
			String str1 = reader.nextLine();
			if (!reader.hasNext()) {
				System.out.println("Full sum: " + str1);
				System.out.println("First 10 digits: " + first10String(string2int(str1)));
			}
			// at least 2 numbers in the file
			else {
				// get second line
				String str2 = reader.nextLine();
				// add first 2 lines together
				int[] result = add2num(string2int(str1), string2int(str2));
				// 
				while (reader.hasNext()) {
					String nxt = reader.nextLine();
					result = add2num(result, string2int(nxt));
				}
				System.out.println("Full sum: " + result);
				System.out.println("First 10 digits: " + first10String(result));
			}
			// problem 13 should be 5537376230 for first 10
			reader.close();
		} catch (FileNotFoundException e) {
			System.out.println(e);
			System.exit(1);
		}
	}




	// gets first 10 digits of a number
	public static String first10String(int[] x) {
		String result = "";
		for (int i = 0; i < 10; i++) {
			result = result + Integer.toString(i);
		}
		return result;
	}


	// takes in 2 integer arrays and adds them starting with index 0
	public static int[] add2num(int[] x, int[] y) {
		int xlen = x.length;
		int ylen = y.length;
		int size;
		if (xlen >= ylen) {
			size = xlen + 1;
		} else {
			size = ylen + 1;
		}
		int[] result = new int[size];
		int carryover = 0;
		for (int i = 0; i < size + 1; i++) {
			int j = x[i] + y[i] + carryover;
			// goes over 10
			if (j > 9) {
				result[i] = j%10;
				carryover = 1;
			}
			// not over 10
			else {
				result[i] = j;
				carryover = 0;
			}
		}
		reverseArray(result);
		return result;

	}

	// reverses the int array so it has the correct direction
	private static void reverseArray(int[] x) {
		for (int i = 0; i < x.length/2; i++) {
			int temp = x[i];
			x[i] = x[x.length-i-1];
			x[x.length-i-1] = temp;
		}
	}


	// takes in a string and makes it an integer array with number reversed
	public static int[] string2int(String str) {
		char[] strr = str.toCharArray();
		int[] res = new int[50];
		int ind = 0;
		for (int i = (strr.length-1); i >= 0; i--) {
			res[ind] = Character.getNumericValue(strr[i]);
			ind++;
		}
		return res;
	}
}
