import java.util.Scanner;
import java.util.Stack;

class largest_rectangle {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = Integer.parseInt(sc.nextLine());
		String[] str = sc.nextLine().split(" ");
		int[] heights = new int[n];
		for (int i = 0; i < n; i++) {
			heights[i] = Integer.parseInt(str[i]);
		}
		System.out.println(maxArea(heights, n));
	}

	static int maxArea(int heights[], int n){
		Stack<Integer> stack = new Stack<>();
		
		int maxx = 0;
		int top;
		int top_area;

		int i = 0;
		while (i < n) {
			if (stack.empty() || heights[stack.peek()] <= heights[i]) {
				stack.push(i++);
			} else {
				// save top of stack and pop it off
				top = stack.peek();
				stack.pop();
				// if that's it, multiply height by i
				if (stack.empty()) {
					top_area = heights[top]*i;
				} else {
					// otherwise subtract top of stack from i - 1 and multiply by min height
					top_area = heights[top]*(i - 1 - stack.peek());
				}
				if (maxx < top_area) {
					// update maxx
					maxx = top_area;
				}
			}
		}
		while (stack.empty() == false) {
			// get top of stack and pop
			top = stack.peek();
			stack.pop();
			// if its empty, multiply it by i
			if (stack.empty()) {
				top_area = heights[top]*i;
			} else {
				// otherwise subtract top of stack from i - 1 and multiply by min height
				top_area = heights[top]*(i - 1 - stack.peek());
			}
			if (maxx < top_area) {
				// update max
				maxx = top_area;
			}
		}
		return maxx;
	}
}