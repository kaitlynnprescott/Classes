import java.util.List;

import org.openqa.selenium.By;
import org.openqa.selenium.Point;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;

public class TestCase1 {

	
	//Test Case 1: Search for a movie, choose the first result, and make sure the ratings loaded
	public static void main(String[] args) throws InterruptedException {
		System.setProperty("webdriver.chrome.driver", "C:\\Users\\Brandon\\Desktop\\chromedriver_win32\\chromedriver.exe");		
		
		WebDriver driver = new ChromeDriver();
		driver.get("file:///D:/Dropbox/Schoolwork/Brandon/Stevens%204/CS%20347/TieBreaker/tie-breaker/index.html");
		
		
		WebElement queryBox = driver.findElement(By.id("query"));
		
		queryBox.click();
		queryBox.sendKeys("batman");
		
		Thread.sleep(4000);
		
		List<WebElement> options = driver.findElements(By.className("ui-menu-item"));
		
		if (options.size() < 10){
			System.err.println("Test failure: Autocomplete options did not load");
			System.exit(1);
		}
		
		options.get(0).click();
		
		Thread.sleep(5000);
		
		WebElement card = driver.findElements(By.className("movie")).get(0);
		WebElement imdb = card.findElement(By.className("rt-score-span"));
		System.out.println("IMDB rating: " + imdb.getText());
		System.out.println("Test successful");
		
		driver.quit();
	}

}
