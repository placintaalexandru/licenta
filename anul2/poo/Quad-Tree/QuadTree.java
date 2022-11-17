
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class QuadTree {

	private QuadTreeCell mRoot;
	private Map<Integer, Square> mMap;

	public QuadTree() {
	}

	public QuadTree(QuadTreeCell root) {
		this.mRoot = root;
		this.mMap = new TreeMap<Integer, Square>();
	}

	/**
	 * Aceasta metoda este una auxiliara, asa cum sugereaza si numele, a metodei
	 * de inserare Aceasta are rolul de insera figura primita ca parametru in
	 * celula curenta, care la inceput va fi radacina arborelui, air apoi se va
	 * apela recursiv unde va fi cazul Pentru a realiza functionarea metodei am
	 * verificat mai intai daca sunt intr-o frunza si daca figura incape in acel
	 * subplan si frunza e goala adaug figura si ma opresc Daca frunza mai
	 * continea forme geoemtrice am verificat daca noua figura se intersecteaza
	 * cu cel putin una din cele existente, caz in care o inserez acolo si ma
	 * opresc Daca figura nu se intersecteaza cu nimic deja existent, imapart
	 * planulin 4 subplane, inserez figurile deja existente in fiii abia creati
	 * si ii sterg din celula curenta Dupa ce am terminat de inserat toate
	 * figurile existente si am golit celula curenta, inserez peste tot, unde se
	 * potrieste noua figura, dar incepand de la fiii abia creati Pentru cazul
	 * in care celula curenta nu este frunza sau figura nu incape in celula
	 * parcurg lista de fii si apelz functia pentru fiecare fiu, pentru a vedea
	 * unde voi insera
	 * 
	 * @param geoemtricObject
	 *            figura care se insereaza
	 * @param quadTreeCell
	 *            celula curenta, la inceput va fi radacina, deoarece de acolo
	 *            plaec
	 */
	private void insertAux(GeometricObject geometricObject, QuadTreeCell quadTreeCell) {
		if ((quadTreeCell.getmSubPlans().isEmpty()) && (geometricObject.fitsInSubPlanOf(quadTreeCell))) {
			if (quadTreeCell.getmFigures().isEmpty()) {
				quadTreeCell.getmFigures().add(geometricObject);
				return;
			} else {
				for (GeometricObject geometricObject1 : quadTreeCell.getmFigures()) {
					if ((geometricObject.collidesWith(geometricObject1))
							&& (geometricObject.getmID() != geometricObject1.getmID())) {
						quadTreeCell.getmFigures().add(geometricObject);
						return;
					}
				}

				quadTreeCell.split();
				int lungime = quadTreeCell.getmFigures().size();

				for (int i = 0; i < lungime; i++) {
					GeometricObject aux = quadTreeCell.getmFigures().get(0);
					for (QuadTreeCell cell : quadTreeCell.getmSubPlans()) {
						if (aux.fitsInSubPlanOf(cell)) {
							insertAux(aux, cell);
						}
					}
					quadTreeCell.getmFigures().remove(aux);
				}
				for (QuadTreeCell cell : quadTreeCell.getmSubPlans()) {
					if (geometricObject.fitsInSubPlanOf(cell)) {
						insertAux(geometricObject, cell);
					}
				}
			}
		} else {
			for (QuadTreeCell cell : quadTreeCell.getmSubPlans()) {
				if (geometricObject.fitsInSubPlanOf(cell)) {
					insertAux(geometricObject, cell);
				}
			}
		}
	}

	/**
	 * Aceasta metoda insereaza o figura geometric in quadtree Pur si simplu
	 * apeleaza functia auxiliara de inserare care incepe din radacina si la
	 * final adaug in Mapa ID-ul figurii si dreptunghiul incadrator
	 * 
	 * @param geoemtricObject
	 *            figura ce se insereaza
	 */
	public void insert(GeometricObject geometricObject) {
		insertAux(geometricObject, mRoot);
		mMap.put(geometricObject.getmID(), geometricObject.getSurroundRectangle());
	}

	/**
	 * Aceasta functie stergere recursiv o figura din subarborele care incepe de
	 * la clula data ca aparametru, daca acea figura se ala acolo Pentru
	 * realizarea acestei functii am realizat o maparae de la ID-uri la
	 * dreptunghiurile incadratoare ale fiecarei figuri din arbore folosind
	 * colectia Map, pentru a sti exact in ce fii sa ma duc la stergere La
	 * stergere ma duc pe nivelurile frunzelor si in fiecare frunza caut in
	 * lista de figuri pentru a verifica daca vreo figura are ID-ul care trebuie
	 * sters Daca celula nu este goala parcurg lista de fii si apelez aceasta
	 * functie recursiv pe fiecare din fii Pana acum am reusit sa folosesc
	 * functia pentru a ma duce cat mai jos in arbore, dar acum va trebui ca
	 * unele frunze sa fie sterse, deoarece fie exista doar o figura in toate,
	 * care e aceeasi, fie sunt frunze goale Pentru a verifica daca trebuie
	 * sterg toti fiii unei celule, verifica mai intai cate frunze goale am, iar
	 * daca am 4 pur si simplu curat lista de fii In cazul in care nu am 4
	 * frunze goale verifica daca am doar o lista de figuri si celelalte sunt
	 * goale, iar daca nu trebuie sa caut cea mai lunga lista pentru a verifica
	 * daca aceea le include pe celelalte, posibil sa fie figuri diferite in
	 * frunza, caz in care nu trebuie sa unec fii in frunza curenta Am cautat
	 * cea mai mare lista de figuri prin fii celului curente, iar daca aceasta
	 * includea listele de figuri din ceilalti fii, atunci adaugam toate
	 * elementele din cea mai mare lista in celula curenta si curatam lista de
	 * fii, operatia inversa de la split
	 * 
	 * @param quadTreeCell
	 *            celula curenta din arbore, la inceput va firadacina arborelui
	 * @param id
	 *            ID-ul figurii care trebuie stearsa
	 * @param itsSquare
	 *            dreptunghiul incadrator al figurii care trebuie stearsa
	 */
	private void removeAux(QuadTreeCell quadTreeCell, int id, Square itsSquare) {
		
		if (quadTreeCell.getmSubPlans().isEmpty()) {
			for (GeometricObject geometricObject : quadTreeCell.getmFigures()) {
				if (geometricObject.getmID() == id) {
					quadTreeCell.getmFigures().remove(geometricObject);
					return;
				}
			}
		} else {
			for (QuadTreeCell cell : quadTreeCell.getmSubPlans()) {
				if (cell.getCharacteristicSquare().touches(itsSquare)) {
					removeAux(cell, id, itsSquare);
				}
			}
		}

		int i = 0;

		for (QuadTreeCell cell : quadTreeCell.getmSubPlans()) {
			if ((cell.getmFigures().isEmpty()) && (cell.getmSubPlans().isEmpty())) {
				i++;
			}
		}

		if (i == 4) {
			
			quadTreeCell.getmSubPlans().clear();
		} else if ((i < 4) && (i > 0) && (quadTreeCell.hasOnlyLeaves())) {
			
			LinkedList<LinkedList<GeometricObject>> linkedLists = new LinkedList<LinkedList<GeometricObject>>();
			for (QuadTreeCell cell : quadTreeCell.getmSubPlans()) {
				if (!cell.getmFigures().isEmpty()) {
					linkedLists.add((LinkedList<GeometricObject>) cell.getmFigures());
				}
			}

			if (linkedLists.size() == 1) {
				quadTreeCell.getmSubPlans().clear();
				quadTreeCell.getmFigures().addAll(linkedLists.get(0));
			} else {
				
				LinkedList<GeometricObject> biggestList = linkedLists.get(0);
				int listSize = linkedLists.size();

				for (i = 1; i < listSize; i++) {
					if (linkedLists.get(i).size() > biggestList.size()) {
						biggestList = linkedLists.get(i);
					}
				}

				for (i = 0; i < listSize; i++) {
					if (!biggestList.containsAll(linkedLists.get(i))) {
						return;
					}
				}

				quadTreeCell.getmSubPlans().clear();
				quadTreeCell.getmFigures().addAll(biggestList);
			}
		}
	}

	/**
	 * Aceasta functie relizeaza stergerea figurii din quadtree prin simplul
	 * apel al functiei auxiliare Mai intai iau din mapare dreptunghiul
	 * incadrator al figurii cu ID-ul de sters, iar daca acel patrat este null
	 * inseamna ca figura nu exista Daca acel patrat nu este null, sterg din
	 * Mapare valoarea pentru key-ul cu ID-ul repsectiv si apelez functia
	 * auxiliara care porneste fix din radacina cu stergerea
	 * @param id ID-ul figurii care se doreste stearsa
	 */
	public void remove(int id) {
		
		Square square = mMap.get(id);

		if (square != null) {
			
			mMap.remove(id);
			removeAux(mRoot, id, square);
		}
	}

	/**
	 * Aceasta metoda creeaza o lista cu toate ID-urile figurilor din quadTree
	 * care se intersecteaza cu figura data ca prametru Mai intai verifica ca
	 * planul de desenare, cel din radacina sa se intersecteze cu dreptunghiul
	 * incadrator al figurii, iar daca nu creez o lista si o intorc goala Apoi
	 * apelez detectorul de coliziuni care creeaza lista cu toate ID-urile
	 * obiectelor care se intersecteaza cu obicectul primit ca parametru
	 * 
	 * @param geometricObject
	 *            figura cu care se testeaza coliziunile in arbore
	 * @return List lista de ID-uri ale caror figuri satisfac coliziunea cu
	 *         obiectul primit ca parametru
	 */
	List<Integer> findCollisionsWithObject(GeometricObject geometricObject) {
		
		List<Integer> list = new ArrayList<Integer>();

		if (!mRoot.getCharacteristicSquare().touches(geometricObject.getSurroundRectangle())) {
			return list;
		}

		CollideDetector.collisionsWithObject(mRoot, geometricObject, list);
		return list;
	}

	/**
	 * Aceasta metoda creeaza o lista cu toate ID-urile figurilor din quadtree
	 * care contin punctu primit ca parametru Mai intaii verifica daca planul de
	 * desenare contine punctul, iar daca nu intorc o lista goala Apoi cpelez
	 * detectorul de coliziuni care testeaza incluziunile punctului in figurie
	 * din arbore, doar in acel/ acele( pentru cazul in care e pe frontiera)
	 * cadran/ cadrane in care este inclus punctul
	 * 
	 * @param p
	 *            punctul cu care se testeaza incluziunile
	 * @return List lista de ID-uri ale caror figuri satisfac coliziunea cu
	 *         obiectul primit ca parametru
	 */
	List<Integer> findCollisionsWithPoint(Point p) {
		
		List<Integer> list = new ArrayList<Integer>();

		if (!mRoot.getCharacteristicSquare().contains(p)) {
			return list;
		}

		CollideDetector.collisionsWithPoint(mRoot, p, list);
		return list;
	}
}