import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

public class Start {

	private FileInputStream mFileInputStream;
	private InputStreamReader mInputStreamReader;
	private BufferedReader mBufferedReader;
	private Map<String, Integer> mVersionMap;
	private Graph mGraph;

	/**
	 * Creeaza o mapa de versiuni pe baza unui linii cititie din fisierul de
	 * comenzi
	 * 
	 * @param line
	 *            linia citita din fisierul de comenzi
	 * @return mapa de versiuni ce specifica modul cum fiecare tip de nod isi
	 *         retine vecinii
	 */
	private Map<String, Integer> createVersionMap(String line) {
		String[] mapValues = line.split(" ");
		Map<String, Integer> map = new HashMap<String, Integer>();
		mGraph = new Graph();

		map.put("NodA", Integer.parseInt(mapValues[1]));
		map.put("NodB", Integer.parseInt(mapValues[2]));
		map.put("NodC", Integer.parseInt(mapValues[3]));

		return map;
	}

	/**
	 * Executa comenzile citite din fiserul de comenzi
	 * 
	 * @param inputFileName
	 *            numele fisierului de intrare
	 * @throws IOException
	 */
	private void executeCommands(String inputFileName) throws IOException {
		String line;
		String[] lineCommands;
		Serializer serializer;
		Deserializer deserializer;
		
		mFileInputStream = new FileInputStream(inputFileName);
		mInputStreamReader = new InputStreamReader(mFileInputStream);
		mBufferedReader = new BufferedReader(mInputStreamReader);

		while ((line = mBufferedReader.readLine()) != null) {
			lineCommands = line.split(" ");

			if (lineCommands[0].compareTo("Settings") == 0) {
				mVersionMap = createVersionMap(line);
				mGraph.setVersionMap(mVersionMap);
			} else if (lineCommands[0].compareTo("Add") == 0) {
				mGraph.addNode(lineCommands);
			} else if (lineCommands[0].compareTo("Del") == 0) {
				mGraph.removeNode(lineCommands);
			} else if (lineCommands[0].compareTo("AddM") == 0) {
				mGraph.addEdge(lineCommands);
			} else if (lineCommands[0].compareTo("DelM") == 0) {
				mGraph.removeEdge(lineCommands);
			} else if (lineCommands[0].compareTo("Serialize") == 0) {
				serializer = Singleton.getSerializerInstance(lineCommands[2]);
				serializer.serialize(mGraph, lineCommands[1]);
				mGraph = new Graph(mVersionMap);
			} else if (lineCommands[0].compareTo("Deserialize") == 0) {
				try {
					deserializer = Singleton.getDeserializerInstance(lineCommands[1], mVersionMap);
					mGraph = deserializer.deserialize();
				} catch (IOException ioe) {
					ioe.printStackTrace();
				}
			}
		}

		myclose();
	}

	/**
	 * Produce resultatele in urma executarii comenzilor din fisierul de intrare
	 * 
	 * @param inputFileName
	 *            numele fisierului de intrare ce contine comenzile
	 */
	public void produceResults(String inputFileName) {
		try {
			executeCommands(inputFileName);
		} catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}

	/**
	 * icnhide stream-urile de intrare
	 * @throws IOException
	 */
	private void myclose() throws IOException {
		mFileInputStream.close();
		mInputStreamReader.close();
		mBufferedReader.close();
	}
}