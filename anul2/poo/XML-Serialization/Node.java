import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Node {

	private String mNodeClass;
	private String mName;
	private int mID;
	private int mVersion;
	private MyCollection mNeighbours;

	/**
	 * Creeaza un nod pe baza unui id, clasa nodului, numele nodului si o mapa
	 * de versiune Pentru clasa nod din graf am considerat urmatoarele campuri
	 * utie: clasa nodului(A, B sau C), nume, id, versiune, si id-urile
	 * vecinilor, retinute printr-o colectie Pentru instantierea unui obiect de
	 * tip Nod am folosit Factory Pattern, iar in fucntie de versiunea pe care o
	 * are nodul, instantiez o colectie, colectie care poate fi clasa LIST,
	 * VECTOR, sau SET
	 * 
	 * @param id
	 *            reprezinta id-ul pe care il are nodul
	 * @param nodeClass
	 *            reprezinta tipul nodului, daca e de tip A, B sau C
	 * @param name
	 *            reprezinta numele nodului
	 * @param versionMap
	 *            reprezinta mapa de versiuni in care retin tipurile de noduri
	 *            si modul cum retin acestea vecinii
	 */
	public Node(int id, String nodeClass, String name, Map<String, Integer> versionMap) {

		this.mID = id;
		this.mNodeClass = nodeClass;
		this.mName = name;
		this.mVersion = versionMap.get(nodeClass);

		switch (mVersion) {
		case 1:

			mNeighbours = new LIST();
			break;

		case 2:

			mNeighbours = new VECTOR();
			break;

		case 3:

			mNeighbours = new SET();
			break;
		}
	}

	public String getName() {
		return mName;
	}

	public int getID() {
		return mID;
	}

	public int getVersion() {
		return mVersion;
	}

	/**
	 * Returneaza clasa nodului: NodA, NodB sau NodC
	 * 
	 * @return un nume din cele 3 enumerate mai sus
	 */
	public String getNodeClass() {
		return mNodeClass;
	}

	/**
	 * Returneaza tipul clasei sub care sunt retinuti vecinii nodului: LIST,
	 * VECTOR, SET
	 * 
	 * @return unul din cele 3 tipuri enumerate mai sus
	 */
	public String getNeighborsType() {
		return mNeighbours.getClass().toString().split(" ")[1];
	}

	/**
	 * adauga id-ul unui veci in lista de vecini
	 * 
	 * @param neighbourID
	 *            reprezinta id-ul vecinului de adaugat
	 */
	public void addNeighbour(int neighbourID) {
		mNeighbours.add(neighbourID);
	}

	/**
	 * sterge id-ul unui nod vecin din lista de vecini
	 * 
	 * @param neighbourID
	 *            reprezinta id-ul vecinului ce trebuie sters
	 */
	public void removeNeighbour(int neighbourID) {
		mNeighbours.remove(neighbourID);
	}

	/**
	 * Returneaza o lista avand id-urile vecinilor
	 * @return lista de vecini
	 */
	public List<Integer> getNeighboursList() {
		return new ArrayList<Integer>(mNeighbours.getNeighboursList());
	}
}