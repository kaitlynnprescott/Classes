import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    static String super_reduced_string(String s){
        // Complete this function
        
        int len = s.length();
        int i = 0;
        while (i < len-1){
            char curr = s.charAt(i);
            char next = s.charAt(i+1);
            if (curr == next) {
                s = s.substring(0,i)+s.substring(i+2,len);
                len = s.length();
                i = 0;
                continue;
            }
            i++;
        }
        
        if (len == 0) {
            return "Empty String";
        }
        return s;
        
        
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String s = in.next();
        String result = super_reduced_string(s);
        System.out.println(result);
    }
}
