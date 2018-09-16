import java.util.List;

import org.openqa.selenium.By;
import org.openqa.selenium.Point;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;

public class TestCase2 {

	
	//Test Case 2: 
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
		
		queryBox.click();
		queryBox.sendKeys("inception");
		Thread.sleep(4000);
		
		options = driver.findElements(By.className("ui-menu-item"));
		
		if (options.size() < 10){
			System.err.println("Test failure: Autocomplete options did not load");
			System.exit(1);
		}
		
		options.get(0).click();
		
		Thread.sleep(5000);
		
		List<WebElement> winners = driver.findElements(By.className("winner"));
		
		boolean foundWinner = false;
		for (int i = 0; i < winners.size(); i++){
			if (!winners.get(i).getCssValue("display").equals("none")){
				foundWinner = true;
			}
		}
		
		if (!foundWinner){
			System.err.println("Test failure: No movie is winner");
			System.exit(1);
		}
		
		System.out.println("Test successful");
		
		driver.quit();
	}

}
