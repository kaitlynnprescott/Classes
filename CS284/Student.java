public class Student implements Comparable<Student>
{
	String name;
	int id;
	float gpa;
	String lname;

	public int compareTo(Student s)
	{
		if (this.id > s.id) 
		{
			return 1;
		}
		if (this.id < s.id) 
		{
			return -1;
		}
		return 0;
	}

	public 
	{

	}
}