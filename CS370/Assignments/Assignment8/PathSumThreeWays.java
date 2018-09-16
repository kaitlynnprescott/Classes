import java.util.Arrays;
import java.util.Scanner;
import java.util.ArrayList;
import java.io.File;
public class PathSumThreeWays
{
	public static void main(String[] args)
	{
		try{
			File fp = new File("matrix.txt");
			Scanner sc = new Scanner(fp);
			ArrayList<String> list = new ArrayList<>();
			while(sc.hasNextLine()){
				list.add(sc.nextLine());
			}
			int nums[][] = table(list);//Table as described in the problem
          /*  System.out.println("Initial Array: ");
            for(int i=0; i<nums.length; i++){
             System.out.println(Arrays.toString(nums[i]));
            }*/
			solve(nums);

		}catch (Exception e){
			e.printStackTrace();
		}
	}

	public static void solve(int[][] arr)
	{
		int arr2[][] = new int[arr.length][arr[0].length];
		int arr3[][] = new int[arr.length][arr[0].length];
		if (arr.length == 1){
			System.out.println("Min sum: " + arr[0][0]);
			System.out.println("Values: [" + arr[0][0] + "]");
			return;
		} else {
			for(int i=0; i<arr.length; i++)
				arr2[i][0] = arr[i][0];

			//from the second column to the second rightmost column
			for(int j=1;j<arr.length-1;j++)
			{
				for(int i=0;i<arr.length;i++)
				{
					int min = Integer.MAX_VALUE;
					// reach from its upper left path
					for(int k=0;k<i;k++)
					{
						//start from arr2[k][j-1], going right and down
						arr3[k][j-1] = arr2[k][j-1];
						arr3[k][j]   = arr3[k][j-1]+arr[k][j];
						int l = k+1;
						while(l<i)
						{
							arr3[l][j-1] = arr3[l-1][j-1] + arr[l][j-1];
							arr3[l][j]   = Math.min(arr3[l][j-1], arr3[l-1][j])+arr[l][j];
							l++;
						}
						int temp = Math.min(arr3[i-1][j-1]+arr[i][j-1], arr3[i-1][j]);
						min = Math.min(temp, min);
					}
					// reach from its bottom left path
					for(int k=arr.length-1;k>i;k--)
					{
						//start from arr2[k][j-1], going right and up
						arr3[k][j-1] = arr2[k][j-1];
						arr3[k][j]   = arr3[k][j-1]+arr[k][j];
						int l = k-1;
						while(l>i)
						{
							arr3[l][j-1] = arr3[l+1][j-1] + arr[l][j-1];
							arr3[l][j]   = Math.min(arr3[l][j-1], arr3[l+1][j])+arr[l][j];
							l--;
						}
						int temp = Math.min(arr3[i+1][j-1]+arr[i][j-1], arr3[i+1][j]);
						min = Math.min(temp, min);
					}

					//reach from its left'
					min = Math.min(arr2[i][j-1], min);
					arr2[i][j] = arr[i][j] + min;
				}
			}
			//find min from rightmost column
			int min = Integer.MAX_VALUE;
			int iFlag = 0;
			for(int i=0;i<arr.length;i++)
			{
				arr2[i][arr.length-1] = arr2[i][arr2.length-2] + arr[i][arr.length-1];
				min = Math.min(arr2[i][arr.length-2]+arr[i][arr.length-1], min);
				if(min == arr2[i][arr.length-2]+arr[i][arr.length-1])
					iFlag = i;
			}
			ArrayList<Integer> path = new ArrayList<>();
			path.add(arr[iFlag][arr[0].length-1]);
			//path.add(0,arr[iFlag][arr[0].length-2]);
			int pos = arr[0].length-1;
			while(pos != 0)
			{
				if(iFlag == 0)
				{
					if(arr2[iFlag][pos-1] < arr2[iFlag+1][pos])
					{
						path.add(0,arr[iFlag][pos-1]);
						pos--;
					}
					else{
						path.add(0,arr[iFlag+1][pos]);
						iFlag++;
					}
				}

				else if(iFlag == arr.length-1)
				{
					if(arr2[iFlag][pos-1] < arr2[iFlag-1][pos])
					{
						path.add(0,arr[iFlag][pos-1]);
						pos--;
					}
					else{
						path.add(0,arr[iFlag-1][pos]);
						iFlag--;
					}
				}

				else{
					if(arr2[iFlag][pos-1] < arr2[iFlag+1][pos] && arr2[iFlag][pos-1] < arr2[iFlag-1][pos])
					{
						path.add(0,arr[iFlag][pos-1]);
						pos--;
					}
					else if(arr2[iFlag+1][pos] < arr2[iFlag-1][pos])
					{
						path.add(0,arr[iFlag+1][pos]);
						iFlag++;
					}
					else{
						path.add(0,arr[iFlag-1][pos]);
						iFlag--;
					}
				}
			}
			System.out.println("Min sum: " + min);
			System.out.println("Values: " + Arrays.toString(path.toArray()));
	       /* System.out.println("Array 1: ");
	        for(int i=0; i<arr.length; i++){
	        System.out.println(Arrays.toString(arr2[i]));
	        }
	        System.out.println("Array 2:");
	        for(int i=0; i<arr.length; i++){
	        System.out.println(Arrays.toString(arr3[i]));
	        }*/
        }


	}
	/*Converts a 1D ArrayList of numbers to a 2D array of ints */
	public static int[][] table(ArrayList<String> arr)
	{
		int size = arr.size();
		int ret[][] = new int[size][size];
		for(int i=0; i<size; i++)
		{
			String[] nums = arr.get(i).split(",");
			for(int j=0; j<nums.length; j++)
			{
				ret[i][j] = Integer.parseInt(nums[j]);
			}
		}
		return ret;
	}


}
