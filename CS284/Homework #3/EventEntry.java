import java.util.*;

public class EventEntry
{
	// Data fields
	private float eventTime;
	private int eventType;

	public static void eventEntry(float eventTime, int eventType)
	{
		this.eventTime = eventTime;
		this.eventType = eventType;
	}

	public float theTime()
	{return eventTime;}

	public int theType()
	{return eventType;}
}