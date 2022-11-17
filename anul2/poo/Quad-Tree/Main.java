
import java.io.IOException;
import java.util.*;

public class Main {

	public static void main(String[] args) {
		// write your code here

		Start start;

		try {
			
			start = new Start("quadtree.in", "quadtree.out");
			start.produceResults();
		} catch (IOException ioe) {
			
			ioe.printStackTrace();
		}
	}
}
