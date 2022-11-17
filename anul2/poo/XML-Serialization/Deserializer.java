import java.io.*;
import java.util.HashMap;
import java.util.Map;

public class Deserializer {

	private FileInputStream mFileInputStream;
	private InputStreamReader mInputStreamReader;
	private BufferedReader mBufferedReader;
	private FileOutputStream mFileOutputStream;
	private OutputStreamWriter mOutputStreamWriter;
	private BufferedWriter mBufferedWriter;
	private Map<Integer, String> mIDMap;
	private Map<String, Integer> mVersionMap;

	/**
	 * Creeaza un obiect ce desrializeaza un graf dintr-un fisier de intrare cu
	 * o anumita mapa de versiuni si scrie in fiserul de iesire operatiile de
	 * cast reusite sau nereusite
	 * 
	 * @param fileInputName
	 * @param mVersionMap
	 * @throws IOException
	 */
	public Deserializer(String fileInputName, Map<String, Integer> mVersionMap) throws IOException {
		String castFile = getCastFileName(fileInputName);

		this.mFileInputStream = new FileInputStream(fileInputName);
		this.mInputStreamReader = new InputStreamReader(mFileInputStream);
		this.mBufferedReader = new BufferedReader(mInputStreamReader);
		this.mFileOutputStream = new FileOutputStream(castFile);
		this.mOutputStreamWriter = new OutputStreamWriter(mFileOutputStream);
		this.mBufferedWriter = new BufferedWriter(mOutputStreamWriter);
		this.mVersionMap = mVersionMap;
		this.mIDMap = new HashMap<Integer, String>();
	}

	public void setNewStreams(String inputFileName, Map<String, Integer> map) throws IOException {
		this.mVersionMap = map;
		this.mFileInputStream = new FileInputStream(inputFileName);
		this.mInputStreamReader = new InputStreamReader(mFileInputStream);
		this.mBufferedReader = new BufferedReader(mInputStreamReader);
		this.mFileOutputStream = new FileOutputStream(getCastFileName(inputFileName));
		this.mOutputStreamWriter = new OutputStreamWriter(mFileOutputStream);
		this.mBufferedWriter = new BufferedWriter(mOutputStreamWriter);
	}
	/**
	 * Creeaza numele fisierului de cast
	 * @param fileInputName reprezinta numele fisierui din care se deserializeaza
	 * @return
	 */
	private String getCastFileName(String fileInputName) {
		String fileName = "";
		int length = fileInputName.length();
		int position = -1;

		for (int i = length - 1; i >= 0; i--) {
			if ((fileInputName.charAt(i) == '\\') || (fileInputName.charAt(i) == '/')) {
				position = i;
				break;
			}
		}

		if (position == -1) {
			fileName = "Deserialize_" + fileName;
		} else {
			fileName = fileName + fileInputName.substring(0, position + 1) + "Deserialize_"
					+ fileInputName.substring(position + 1, length).split("\\.")[0] + "_CAST.log";

		}

		return fileName;
	}

	/**
	 * Extrage id-ul unui nod dintr-o linie citita din fiserul de intrare
	 * @param line reprezinta linia citita
	 * @return
	 */
	private Integer getID(String line) {
		return Integer.parseInt(line.split(" ")[3].split("\"")[1]);
	}

	/**
	 * Extrage versiunea unui nod dintr-o linie citita din fiserul de intrare
	 * @param line reprezinta linia citita
	 * @return
	 */
	private Integer getVersion(String line) {
		return Integer.parseInt(line.split(" ")[2].split("\"")[1]);
	}

	/**
	 * Extrage numele unui nod dintr-o linie citita din fiserul de intrare
	 * @param line reprezinta linia citita
	 * @return
	 */
	private String getName(String line) {
		return line.split(">")[1].split("<")[0];
	}

	/**
	 * Extrage clasa unui nod dintr-o linie citita din fiserul de intrare
	 * @param line reprezinta linia citita
	 * @return
	 */
	private String getNodeClass(String line) {
		return line.split(" ")[1].split("\"")[1];
	}

	/**
	 * Scrie mesajul de cast esuat/realizat prin compararea versiunii vechi cu
	 * cea noua, iar in fucntie de aceasta comparatie scriu mesajul de succes
	 * sau de esuare
	 * 
	 * @param line
	 *            linia citita
	 * @param name
	 *            numele nodului curent
	 * @throws IOException
	 */
	private void writeCastMessage(String line, String name) throws IOException {
		String nodeClass = getNodeClass(line);
		Integer oldVersion = getVersion(line);

		if (mVersionMap.get(nodeClass) > oldVersion) {
			mBufferedWriter.write("OK cast " + nodeClass + " " + name + " from Version=\"" + oldVersion
					+ "\" to Version=\"" + mVersionMap.get(nodeClass) + "\"\n");
		} else if (mVersionMap.get(nodeClass) < oldVersion) {
			mBufferedWriter.write("Fail cast " + nodeClass + " " + name + " from Version=\"" + oldVersion
					+ "\" to Version=\"" + mVersionMap.get(nodeClass) + "\"\n");
		}

		mBufferedWriter.flush();
	}

	/**
	 * Aduna toti vecinii unui nod pentru a reface graful folosind operatia sa de inserare a nodului
	 * @return String-ul ce contine toti vecinii unui nod separati prin cate un spatiu
	 * @throws IOException
	 */
	private String getInsertNeighbours() throws IOException {
		String line, name = "";
		String addStrig = "";
		Integer id;

		while ((line = mBufferedReader.readLine()).compareTo("</Object>") != 0) {
			if (line.contains("<Object")) {
				id = getID(line);
				line = mBufferedReader.readLine();
				name = getName(line);
				mIDMap.put(id, name);
				addStrig = addStrig + " " + name;
			} else if (line.contains("<Reference")) {
				id = getID(line);
				name = mIDMap.get(id);
				addStrig = addStrig + " " + name;
			}
		}

		return addStrig;
	}

	/**
	 * Deserializeaza un graf Pentru implementare am citit din fisierul de
	 * intrare cat timp puteam sa citesc din acesta, iar de fiecare data cand
	 * caracterul de pe pozitia 1 al liniei citite era 'O' atunci inseamna ca
	 * incepeau datele pentru un nod nou Pentru fiecare citesc numele si id-ul,
	 * iar cazul in care citesc o referinta preiau numele din mapa de nume
	 * folosind id-ul acelei referinte
	 * 
	 * @return graful deserializat
	 * @throws IOException
	 */
	public Graph deserialize() throws IOException {
		String addStrig;
		String line, name;
		Graph graph = new Graph(new HashMap<String, Integer>(mVersionMap));

		try {

			while ((line = mBufferedReader.readLine()) != null) {
				if (line.charAt(1) == 'O') {
					addStrig = "Add " + getNodeClass(line);
					name = getName(mBufferedReader.readLine());
					addStrig = addStrig + " " + name;
					addStrig += getInsertNeighbours();

					mIDMap.put(getID(line), name);
					writeCastMessage(line, name);

					graph.addNode(addStrig.split(" "));
				}
			}
		} catch (IOException ioe) {
			ioe.printStackTrace();
		}

		myclose();
		return graph;
	}

	/**
	 * Inchide stream-urile deschise pentru citire, respectiv scriere
	 * 
	 * @throws IOException
	 */
	private void myclose() throws IOException {
		mFileInputStream.close();
		mInputStreamReader.close();
		mBufferedReader.close();
		mFileOutputStream.close();
		mOutputStreamWriter.close();
		mBufferedWriter.close();
	}
}