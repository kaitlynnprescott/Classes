import java.util.HashMap;
import java.util.Set;
import java.util.Iterator;
import java.util.Map;

public class HashTest
{
	public static void main(String[] args) 
	{
		HashMap<String, Integer> ourMap = new HashMap<String, Integer>();
		ourMap.put("Kareem", 10397923);
		ourMap.put("Ron", 10241231);
		ourMap.put("Kaitlynn", 10394066);

		System.out.println(ourMap.get("Kareem"));
		System.out.println(ourMap.get("Kaitlynn"));

		if (ourMap.containsKey("Ron"))
		{
			System.out.println("Ron's student ID is: " + ourMap.get("Ron"));
		}
		else
		{	
			System.out.println("Ron is not a student.");
		}


		if (ourMap.containsKey("Peter"))
		{
			System.out.println("Peter's student ID is: " + ourMap.get("Peter"));
		}
		else
		{	
			System.out.println("Peter is not a student.");
		}


		if (ourMap.containsValue(10397923))
		{
			System.out.println("There exists a student with the ID 10397923.");
		}
		else
		{
			System.out.println("There does not exist a student with the ID 10397923.");
		}
		

		if (ourMap.containsValue(12345678))
		{
			System.out.println("There exists a student with the ID 12345678.");
		}
		else
		{
			System.out.println("There does not exist a student with the ID 12345678.");
		}


		ourMap.remove("Kareem");
		if (ourMap.containsKey("Kareem"))
		{	
			System.out.println("Kareem's student ID is " + ourMap.get("Kareem"));
		}
		else
		{
			System.out.println("Kareem is not a student.");
		}


		Set set = ourMap.entrySet();

		Iterator i = set.iterator();

		while (i.hasNext())
		{
			Map.Entry curr = (Map.Entry)i.next();
			System.out.println(curr.getKey() + ": ");
			System.out.println(curr.getValue() + ": ");
		}

	}
}
