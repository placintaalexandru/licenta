import java.util.List;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

/**
 * Aceasta clasa are rolul de a citi variabilele din fisier, expresiile ce vor
 * trebui evaluate si
 */
public class MyReader {

	private List<Object> mResultList;

	public MyReader() {
		this.mResultList = new ArrayList<Object>();
	}

	public List<Object> getResultList() {
		return mResultList;
	}

	/**
	 * Verifica daca linia citita este o linie de declarare a unei variabile,
	 * prin seimpla verificare daca se contine cuvantul cheie eval, ce indica
	 * evaluarea unei expresii
	 */
	private boolean isVariable(String line) {
		return !line.contains("eval");
	}

	/**
	 * Extrage tipul variabilei din linia in care aceasta este declarata, care
	 * este chiar primul cuvant, pana la intalnirea caracterului de sptiu de pe
	 * acea linie
	 */
	private String getType(String line) {
		return line.split(" ")[0];
	}

	/**
	 * Extrage tipul variabilei din linia in care aceasta este declarata, care
	 * este chiar al 2 lea cuvant, dupa ce se va da split dupa caracterul spatiu
	 */
	private String getName(String line) {
		return line.split(" ")[1];
	}

	/**
	 * Aceasta metoda citeste dintr-un fisier, variabile si expresii pe care le
	 * evalueaza, iar dupa fiecare expresie evaluata se introduce rezultatul in
	 * lista de obiecte, aceasta continand rezultatele tuturor expresiilor ce au
	 * fost evaluate pana acum
	 */
	public void read(String inputFileName) throws IOException {
		FileInputStream fis = new FileInputStream(inputFileName);
		InputStreamReader isr = new InputStreamReader(fis);
		BufferedReader br = new BufferedReader(isr);
		String line;
		String valueAsString;
		ParseTree parseTree;
		Map<String, Object> variableMap = new HashMap<String, Object>();

		while ((line = br.readLine()) != null) {

			if (isVariable(line)) {
				valueAsString = line.split(" ")[3];

				if (getType(line).compareTo("int") == 0) {
					variableMap.put(getName(line),
							Integer.parseInt(valueAsString.substring(0, valueAsString.length() - 1)));
				} else if (getType(line).compareTo("double") == 0) {
					variableMap.put(getName(line),
							Double.parseDouble(valueAsString.substring(0, valueAsString.length() - 1)));
				} else if (getType(line).compareTo("string") == 0) {
					variableMap.put(getName(line), line.split("\"")[1]);
				}
			} else {
				parseTree = Singleton.getParseTreeInstance(variableMap, line.substring(5, line.length() - 1));
				mResultList.add(parseTree.getResult());
			}
		}

		br.close();
		isr.close();
		fis.close();
	}
}