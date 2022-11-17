import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.*;

public class Serializer {

	private Graph mGraph;
	private FileOutputStream mFileOutputStream;
	private OutputStreamWriter mOutputStreamWriter;
	private BufferedWriter mBufferedWriter;

	/**
	 * Creeaza un obiect ce serializeaza un graf plecand dintr-un nod,
	 * parcurgand graful in latime
	 * 
	 * @param graph
	 *            reprezinta graful ce trebuie serializat
	 * @param startingNode
	 *            reprezinta nodul de plecare
	 * @param outputFileName
	 *            reprezinta fisierul in care se scriu nodurile prin care se
	 *            trece
	 * @throws IOException
	 */
	public Serializer(String outputFileName) throws IOException {
		this.mFileOutputStream = new FileOutputStream(outputFileName);
		this.mOutputStreamWriter = new OutputStreamWriter(mFileOutputStream);
		this.mBufferedWriter = new BufferedWriter(mOutputStreamWriter);
	}

	public void setNewStreams(String fileOutputName) throws IOException {
		this.mFileOutputStream = new FileOutputStream(fileOutputName);
		this.mOutputStreamWriter = new OutputStreamWriter(mFileOutputStream);
		this.mBufferedWriter = new BufferedWriter(mOutputStreamWriter);
	}

	/**
	 * Scrie detaliile despre un nod: clasa nodului, versiunea si id-ul
	 * 
	 * @param id
	 *            id-ul nodului pentru a cauta nodul in graf
	 * @return String-ul ce contine aceste detalii
	 */
	private String nodeDetails(int id) {
		String details = "";
		Node node = mGraph.getNode(id);

		details = details + "<Object class=\"" + node.getNodeClass() + "\" Version=\"" + node.getVersion() + "\" id=\""
				+ id + "\">";

		return details;
	}

	/**
	 * Daca se trece printr-un nod prin care s-a mai trecut se scrie o referinta
	 * la acel nod
	 * 
	 * @param id
	 *            id-ul nodului la care se scrie referinta
	 * @return String-ul ce contine acea referinta
	 */
	private String reference(int id) {
		String details = "";
		Node node = mGraph.getNode(id);

		details = details + "<Reference class=\"" + node.getNodeClass() + "\" Version=\"" + node.getVersion()
				+ "\" id=\"" + id + "\">";

		return details;
	}

	/**
	 * Scrie numele unui nod
	 * 
	 * @param id
	 *            reprezinta id-ul nodului caruia ii scriu numele
	 * @return Sring-ul ce contine acel nume in formatul cerut
	 */
	private String printName(int id) {
		Node node = mGraph.getNode(id);
		String name = "";

		name = name + "<Nume>" + node.getName() + "</Nume>";
		return name;
	}

	/**
	 * Scrie inceputul unui nod, modul in care acesta isi retine vecinii
	 * 
	 * @param node
	 *            nodul caruia ii voi scrie vecinii
	 * @return Stringul in formatul cerut
	 */
	private String beginNeighboursType(Node node) {
		return "<" + node.getNeighborsType() + ">";
	}

	/**
	 * Scrie formatul de terminare al vecinilor
	 * 
	 * @param node
	 *            nodul pentru care termin vecinii
	 * @throws IOException
	 */
	private void endNeighboursType(Node node) throws IOException {
		mBufferedWriter.write("\t");
		mBufferedWriter.write("</" + node.getNeighborsType() + ">");
		mBufferedWriter.newLine();
	}

	/**
	 * Scrie toate detaliile despre un vecin
	 * 
	 * @param neighbour
	 *            reprezinta id-ul vecinului
	 * @throws IOException
	 */
	private void printNeighbour(Integer neighbour) throws IOException {
		mBufferedWriter.write(nodeDetails(neighbour));
		mBufferedWriter.newLine();
		mBufferedWriter.write("\t\t\t");
		mBufferedWriter.write(printName(neighbour));
		mBufferedWriter.newLine();
		mBufferedWriter.write("\t\t</Object>");
		mBufferedWriter.newLine();
	}

	/**
	 * Scrie inceptul de nod in formatul cerut
	 * 
	 * @param currentNodeID
	 *            reprezinta id-ul nodului pe care incep sa il serializez
	 * @throws IOException
	 */
	private void beginNode(Integer currentNodeID) throws IOException {
		Node node = mGraph.getNode(currentNodeID);

		mBufferedWriter.write(nodeDetails(currentNodeID));
		mBufferedWriter.newLine();
		mBufferedWriter.write("\t");
		mBufferedWriter.write(printName(currentNodeID));
		mBufferedWriter.newLine();
		mBufferedWriter.write("\t");
		mBufferedWriter.write(beginNeighboursType(node));
		mBufferedWriter.newLine();
	}

	/**
	 * Scrie finalul de nod in formatul cerut
	 * 
	 * @param node
	 *            nodul pe care il inchei de serializat
	 * @throws IOException
	 */
	private void endNode(Node node) throws IOException {
		endNeighboursType(node);
		mBufferedWriter.write("</Object>");
		mBufferedWriter.newLine();
	}

	/**
	 * Scrie toti vecinii pentru un nod pe baza cozii si vectorului care imi
	 * spune daca am mai trecut prin acel nod
	 * 
	 * @param node
	 *            nodul curent
	 * @param neighbours
	 *            coada care tine evidenta nodurilor neparcurse
	 * @param visited
	 *            vectorul care indica nodurile in care am fost sau nu
	 * @param comparator
	 *            un comparator care ordoneaza id-urile unui nod in asa fel
	 *            incat sa ii scriu vecinii in ordine alfabetica
	 * @throws IOException
	 */
	private void printAllNeighbours(Node node, Queue<Integer> neighbours, int[] visited, Comparator<Integer> comparator)
			throws IOException {
		List<Integer> list = node.getNeighboursList();
		Collections.sort(list, comparator);

		for (Integer neighbour : list) {
			mBufferedWriter.write("\t\t");

			if (visited[neighbour] == 0) {
				printNeighbour(neighbour);
				neighbours.add(neighbour);
			} else if (visited[neighbour] == 1) {
				mBufferedWriter.write(reference(neighbour));
				mBufferedWriter.newLine();
			}
		}
	}

	/**
	 * Parcurge graful in latime si scrie pentru fiecare nod vecinii acestuia,
	 * iar daca printr-unul din vecini s-a mai trecut se scrie o referinta la
	 * acel vecin Pentru implementare verific mai intai daca acel nd exista, caz
	 * in care nu exista fisez un mesaj sugestiv si opresc executia functiei
	 * Daca nodul de inceput exista, atunci il introduc intr-o coada, iar cat
	 * timp acea coada este nevida extrag primul element din coada, verific daca
	 * am mai trecut prin el, iar daca nu il serializez si marchez trecerea lui
	 * in vectorul de vizitati
	 * 
	 * @param startingName
	 *            reprezinta numele nodului de incaput
	 * @throws IOException
	 */
	private void breadthFirst(String startingName) throws IOException {
		Comparator<Integer> integerComparator = new Comparator<Integer>() {
			@Override
			public int compare(Integer integer, Integer t1) {

				return mGraph.getIDMap().get(integer).compareTo(mGraph.getIDMap().get(t1));
			}
		};

		int[] visited = new int[mGraph.getMaxID() + 1];
		Node node;
		Queue<Integer> neighbours = new ArrayDeque<Integer>();

		if (mGraph.getNameMap().get(startingName) == null) {
			System.out.println("Nu exista nod");
			return;
		}

		neighbours.add(mGraph.getNameMap().get(startingName));

		while (!neighbours.isEmpty()) {
			Integer currentNodeID = neighbours.poll();
			node = mGraph.getNode(currentNodeID);

			if (visited[currentNodeID] == 0) {
				visited[currentNodeID] = 1;

				beginNode(currentNodeID);
				printAllNeighbours(node, neighbours, visited, integerComparator);
				endNode(node);
			}
		}

		myclose();
	}

	/**
	 * Inchide stream-urile deschise pentru scriere
	 * 
	 * @throws IOException
	 */
	private void myclose() throws IOException {
		mBufferedWriter.close();
		mOutputStreamWriter.close();
		mFileOutputStream.close();
	}

	private void serializeAux(String startingName) {
		try {
			breadthFirst(startingName);
		} catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}

	public void serialize(Graph graph, String startingNode) {
		mGraph = graph;
		serializeAux(startingNode);
	}
}