import java.io.IOException;

/**
 * Aceasta clasa citeste operatiile dinfisierul de intrare si la final scrie
 * rezultatele in fisierul de iesire
 */
public class Start {

	/**
	 * Efectueaza operatiile din fisierul de intrare si screi rezultatele in
	 * fisierul de iesire
	 */
	public static void start(String inputFileName, String outputFileName) {
		MyReader myReader = new MyReader();
		MyWriter myWriter = new MyWriter();

		try {
			myReader.read(inputFileName);
		} catch (IOException e) {
			e.printStackTrace();
		}

		try {
			myWriter.write(myReader.getResultList(), outputFileName);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}