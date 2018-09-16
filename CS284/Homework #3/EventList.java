import java.util.*;

public class EventList
{
	// Data fields
	private float eventTime;
	private int eventType;
	public EventList next;

	java.util.LinkedList newEventList = new java.util.LinkedList();

	public static EventEntry nextEvent()
	{
		newEventList.remove();

	}
	public void insertEvent(EventEntry l)
	{
		if (newEventList == null) 
		{
			newEventList.offer(l);
		}
		else
		{
			for (int i = 0; i <= ; i++) 
			{
				if (i.eventTime >= l.eventTime) 
				{
					newEventList.add(i, l);	
				}
			}
		}
	}
}