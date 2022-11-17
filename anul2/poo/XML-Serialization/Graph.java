import java.util.*;

public class Graph {

	private Integer maxID;
	private Map<String, Integer> mVersionMap;
	private Map<String, Integer> mNameMap;
	private Map<Integer, String> mIDMap;
	private List<Node> mNodeList;

	/**
	 * Creeaza un obiect de tipul Graph atribuindu-i o un id maxim setat initial
	 * pe 0, o mapare de la nume la id-uri, o mapare de la id-uri la nume si o
	 * lista de oduri ce initial e vida
	 */
	public Graph() {
		this.maxID = new Integer(0);
		this.mNameMap = new HashMap<String, Integer>();
		this.mIDMap = new HashMap<Integer, String>();
		this.mNodeList = new ArrayList<Node>();
	}

	/**
	 * Creeaza un obiect de tipul Graph atribuindu-i o un id maxim setat initial
	 * pe 0, o mapare de la nume la id-uri, o mapare de la id-uri la nume, o
	 * mapa de versiuni si o lista de oduri ce initial e vida
	 * 
	 * @param versionMap
	 *            reprezinta mapa de versiuni a grafului, ajutand la adaugarea
	 *            unui nod in lista de noduri prin indicarea modului cum isi
	 *            retine acesta vecinii
	 */
	public Graph(Map<String, Integer> versionMap) {

		this.maxID = new Integer(0);
		this.mVersionMap = versionMap;
		this.mNameMap = new HashMap<String, Integer>();
		this.mIDMap = new HashMap<Integer, String>();
		this.mNodeList = new ArrayList<Node>();
	}

	/**
	 * Schimba mapa de versiune aca in mijlocul citirii operatiilor aceasta se
	 * schimba
	 */
	public void setVersionMap(Map<String, Integer> versionMap) {
		this.mVersionMap = versionMap;
	}

	/**
	 * Retruneaza lista de noduri din graf
	 * 
	 * @return lista alcatuita din toate nodurile
	 */
	public List<Node> getNodeList() {
		return mNodeList;
	}

	/**
	 * Returneaza maparea de la nume la id-urile nodurilor din graf
	 * 
	 * @return un obiect de tip Map<String, Integer>
	 */
	public Map<String, Integer> getNameMap() {
		return mNameMap;
	}

	/**
	 * Returneaza maparea de la id-uri la numele nodurilor din graf
	 * 
	 * @return un obiect de tip Map<Integer, String>
	 */
	public Map<Integer, String> getIDMap() {
		return mIDMap;
	}

	/**
	 * Returneaza id-ul maxim din graf
	 * 
	 * @return id-ul maxim
	 */
	public Integer getMaxID() {
		return maxID;
	}

	/**
	 * Cauta in lista de nodurile nodul are id-ul identic cu parametrul functiei
	 * 
	 * @param id
	 *            id-ul nodului dorit
	 * @return nodul cautat
	 */
	public Node getNode(int id) {
		Node foundNode = null;

		for (Node node : mNodeList) {
			if (node.getID() == id) {
				foundNode = node;
			}
		}

		return foundNode;
	}

	/**
	 * Adauga in graf un nod pe baza unor detalii legate de acel nod Pentru
	 * implementare am creat un nod, iar apoi am cautat in lista nodurilor
	 * vecine pentru a crea legaturia intre cele 2 si faceam ca cele 2 sa fie
	 * vecine prin adaugarea id-ului unuia in lista de vecini a celuilalt
	 * 
	 * @param nodeDetails
	 *            detaliile legate de nodul de inserat
	 */
	public void addNode(String[] nodeDetails) {
		Node node = new Node(maxID, nodeDetails[1], nodeDetails[2], mVersionMap);

		mNameMap.put(node.getName(), node.getID());
		mIDMap.put(node.getID(), node.getName());
		mNodeList.add(node);
		maxID++;

		for (int i = 3; i < nodeDetails.length; i++) {
			for (Node node1 : mNodeList) {
				if (node1.getName().compareTo(nodeDetails[i]) == 0) {
					node1.addNeighbour(node.getID());
					node.addNeighbour(node1.getID());
				}
			}
		}
	}

	/**
	 * Sterge un nod din graf pe baza detaliilor furnizate in instructiune
	 * Pentru implementare cau nodul ce are acel nume si il setrg din lista de
	 * noduri a graului, iar apoi parcurg nodurile ramase pentru a sterge din
	 * lista lor de vecini id-ul nodului de sters
	 * 
	 * @param nodeDetails
	 *            detaliile legate de nodul care trebuie sters
	 */
	public void removeNode(String[] nodeDetails) {
		Integer nodeID = mNameMap.get(nodeDetails[2]);

		mNameMap.remove(nodeDetails[2]);
		mIDMap.remove(nodeID);

		if (nodeID == null) {
			return;
		}

		for (Node node : mNodeList) {
			if (node.getName().compareTo(nodeDetails[2]) == 0) {
				mNodeList.remove(node);
				break;
			}
		}

		for (Node node : mNodeList) {
			node.removeNeighbour(nodeID);
		}
	}

	/**
	 * Adauga o muchie pe baze detaliilor ce definesc acea muchie Pentru
	 * implementarea acestei fuctii am determinat id-urile celor 2 noduri, iar
	 * daca unul dintre ele nu exista ma opresc Daca ambele noduri exista aduag
	 * in lista de vecini ai unui pe celelalt, procedez la fel pentru ambele
	 * noduri, doar daca unul nu il contine deja pe celalalt
	 * 
	 * @param edgeDetails
	 *            reprezinta detaliile ce definesc muchia ce trebuie adaugata,
	 *            operatia de adaugare a muchiei, numele nodului 1 si numele
	 *            nodului 2
	 */
	public void addEdge(String[] edgeDetails) {
		Integer id1, id2;

		id1 = mNameMap.get(edgeDetails[1]);
		id2 = mNameMap.get(edgeDetails[2]);

		if ((id1 == null) || (id2 == null)) {
			return;
		}

		if (getNode(id1).getNeighboursList().contains(id2)) {
			return;
		}

		for (Node node : mNodeList) {
			if (node.getID() == id1) {
				node.addNeighbour(id2);
			} else if (node.getID() == id2) {
				node.addNeighbour(id1);
			}
		}
	}

	/**
	 * Sterge o muchie ce leaga 2 noduri Pentru implementare am determinat
	 * id-urile nodurilor care au acelel id-uri, iar daca un nod era null,
	 * inseamna ca nu exista unul din noduri si nu execut nico operatie Daca
	 * cele 2 noduri exista atunci din lista de id-uri vecine a unui sterg id-ul
	 * celuilalt, procedez la fel pentru ambele noduri
	 * 
	 * @param edgeDetails
	 *            reprezinta detaliile muchiei, operatia ce indica stergerea
	 *            muchiei, numele nodului 1 si a nodului 2
	 */
	public void removeEdge(String[] edgeDetails) {
		Integer id1, id2;

		id1 = mNameMap.get(edgeDetails[1]);
		id2 = mNameMap.get(edgeDetails[2]);

		if ((id1 == null) || (id2 == null)) {
			return;
		}

		for (Node node : mNodeList) {
			if (node.getID() == id1) {
				node.removeNeighbour(id2);
			} else if (node.getID() == id2) {
				node.removeNeighbour(id1);
			}
		}
	}
}