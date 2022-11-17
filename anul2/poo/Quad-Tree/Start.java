
import java.io.*;
import java.util.Collections;
import java.util.ArrayList;
import java.util.List;

public class Start {

	String inputFileName;
	String outputFileName;
	FileInputStream fis;
	FileOutputStream fos;
	InputStreamReader isr;
	OutputStreamWriter osw;
	BufferedReader br;
	BufferedWriter bw;
	List<List<Integer>> resultList;

	public Start() {
	}

	/**
	 * Prin acest constructor imi deschid un buffer pentru citirea textului si
	 * unul pentru scrierea textului Initializez lista de liste, pe care o foi
	 * scrie in fisier la final
	 * 
	 * @param inputFileName
	 *            numele fisierului de intrare
	 * @param outputFile
	 *            numele fisierului de iesire
	 */
	public Start(String inputFileName, String outputFileName) throws IOException {
		
		this.inputFileName = inputFileName;
		this.outputFileName = outputFileName;

		fis = new FileInputStream(inputFileName);
		fos = new FileOutputStream(outputFileName);
		isr = new InputStreamReader(fis);
		osw = new OutputStreamWriter(fos);
		br = new BufferedReader(isr);
		bw = new BufferedWriter(osw);
		resultList = new ArrayList<>();
	}

	/**
	 * Aceasta metoda produce rezultatele in urma operatiilor facute pe quadtree
	 * Citesc din fisierul de intrare cate o linie si o prelucrez cu split, iar
	 * apoi verific ce cod are prima valoare din vectorul de stringuri de valori
	 * In functie de acea valoare apelez una din functiile create mai jos La
	 * final afisez rezultatele in fisier si inchid stream-urile deschise
	 */
	public void produceResults() throws IOException {
		
		String line;
		String[] values;
		QuadTree quadTree;

		line = br.readLine();
		values = line.split(" ");
		quadTree = getQuadTree(values);

		while ((line = br.readLine()) != null) {
			values = line.split(" ");

			switch (values[0]) {
			case "11":

				insertion(quadTree, values);
				break;

			case "22":

				quadTree.remove(Integer.parseInt(values[1]));
				break;

			case "33":

				pointCollision(quadTree, values, resultList);
				break;

			case "44":

				objectCollision(quadTree, values, resultList);
				break;
			}
		}

		printResult();

		br.close();
		bw.close();
		isr.close();
		osw.close();
		fis.close();
		fos.close();
	}

	/**
	 * Aceasta metoda creeaza initalizeaza un arbore cu coorodnatele planului de
	 * desenare Pentru a realiza acest lucru am citit o linie, apoi am folsit
	 * metoda split pentru a creeaz un vector de string-uri in care fiecare
	 * string retinea o coordonata Am creat convertit din string in double
	 * folosind metoda statica parseDouble si am construit parametri pentru a
	 * initializa quadtree-ul, cele 2 puncte care reprezentau patratul de
	 * desenare, centru planului de desenare si lungimea unei alturi a planului
	 * de desenare
	 * 
	 * @param values
	 *            vectorul de string-uri care contine valorile necesare
	 *            initializarii quadtree-ului
	 * @return QuadTree quadtree-ul initializat
	 */
	private QuadTree getQuadTree(String[] values) {
		
		double x1, y1, x2, y2, xCenter, yCenter;
		QuadTreeCell quadTreeCell;

		x1 = Double.parseDouble(values[0]);
		y1 = Double.parseDouble(values[1]);
		x2 = Double.parseDouble(values[2]);
		y2 = Double.parseDouble(values[3]);
		xCenter = (x1 + x2) / 2;
		yCenter = (y1 + y2) / 2;

		quadTreeCell = new QuadTreeCell(new Point(xCenter, yCenter), x2 - x1);

		return new QuadTree(quadTreeCell);
	}

	/**
	 * Aceasta metoda creeaza un patrat din valorile pe care le contine
	 * string-ul de valori Am folosit metodele statice parseInt si parseDouble
	 * pentru a culege informatiile necesare iar apoi cu coordonatele
	 * initializate, am creat punctele, iar apoi patratul
	 * 
	 * @param vectorul
	 *            de stringuri de valori
	 * @return Square un patrat
	 */
	private Square createSquare(String[] values) {
		
		double x1, y1, x2, y2;
		int id;
		Point leftDown, rightUp;

		id = Integer.parseInt(values[2]);
		x1 = Double.parseDouble(values[3]);
		y1 = Double.parseDouble(values[4]);
		x2 = Double.parseDouble(values[5]);
		y2 = Double.parseDouble(values[6]);

		leftDown = new Point(x1, y1);
		rightUp = new Point(x2, y2);

		return new Square(leftDown, rightUp, id);
	}

	/**
	 * Aceasta metoda creeaza un triunghi din valorile pe care le contine
	 * string-ul de valori Am folosit metodele statice parseInt si parseDouble
	 * pentru a culege informatiile necesare iar apoi cu coordonatele
	 * initializate, am creat punctele, iar apoi triunghiul
	 * 
	 * @param vectorul
	 *            de stringuri de valori
	 * @return Triangle un tringhi
	 */
	private Triangle createTriangle(String[] values) {
		
		double x1, y1, x2, y2, x3, y3;
		int id;
		Point leftLow, rightLow, up;

		id = Integer.parseInt(values[2]);
		x1 = Double.parseDouble(values[3]);
		y1 = Double.parseDouble(values[4]);
		x2 = Double.parseDouble(values[5]);
		y2 = Double.parseDouble(values[6]);
		x3 = Double.parseDouble(values[7]);
		y3 = Double.parseDouble(values[8]);

		up = new Point(x1, y1);
		leftLow = new Point(x2, y2);
		rightLow = new Point(x3, y3);

		return new Triangle(up, leftLow, rightLow, id);
	}

	/**
	 * Aceasta metoda creeaza un cerc din valorile pe care le contine string-ul
	 * de valori Am folosit metodele statice parseInt si parseDouble pentru a
	 * culege informatiile necesare iar apoi cu coordonatele initializate, am
	 * creat punctele, iar apoi cerc
	 * 
	 * @param vectorul
	 *            de stringuri de valori
	 * @return Circle un cerc
	 */
	private Circle createCircle(String[] values) {
		
		double xCenter, yCenter, radius;
		int id;
		Point center;

		id = Integer.parseInt(values[2]);
		radius = Double.parseDouble(values[3]);
		xCenter = Double.parseDouble(values[4]);
		yCenter = Double.parseDouble(values[5]);

		center = new Point(xCenter, yCenter);

		return new Circle(center, radius, id);
	}

	/**
	 * Aceasta metoda creeaza un romb din valorile pe care le contine string-ul
	 * de valori Am folosit metodele statice parseInt si parseDouble pentru a
	 * culege informatiile necesare iar apoi cu coordonatele initializate, am
	 * creat punctele, iar apoi romb
	 * 
	 * @param vectorul
	 *            de stringuri de valori
	 * @return Rhombus un romb
	 */
	private Rhombus createRhombus(String[] values) {
		
		double x1, y1, x2, y2, x3, y3, x4, y4;
		int id;
		Point up, left, low, right;

		id = Integer.parseInt(values[2]);
		x1 = Double.parseDouble(values[3]);
		y1 = Double.parseDouble(values[4]);
		x2 = Double.parseDouble(values[5]);
		y2 = Double.parseDouble(values[6]);
		x3 = Double.parseDouble(values[7]);
		y3 = Double.parseDouble(values[8]);
		x4 = Double.parseDouble(values[9]);
		y4 = Double.parseDouble(values[10]);

		low = new Point(x1, y1);
		left = new Point(x2, y2);
		up = new Point(x3, y3);
		right = new Point(x4, y4);

		return new Rhombus(up, left, low, right, id);
	}

	/**
	 * Aceasta metoda insereaza in quadtree figura care se afla in vectorul de
	 * valori Pentru a verifica ce figura se afla in vectorul de valori am
	 * verificat numarul figurii( 1, 2, 3 sau 4) si am inserat figura creata cu
	 * metodele de mai sus
	 * 
	 * @param quadtree
	 *            arborele in care se insereaza
	 * @param values
	 *            vectorul de stringrui in care sun pastrate valorile
	 */
	private void insertion(QuadTree quadTree, String[] values) {
		
		switch (values[1]) {
		case "1":

			quadTree.insert(createSquare(values));
			break;

		case "2":

			quadTree.insert(createTriangle(values));
			break;

		case "3":

			quadTree.insert(createCircle(values));
			break;

		case "4":

			quadTree.insert(createRhombus(values));
			break;
		}
	}

	/**
	 * Aceasta metoda creeaza o lista de ID-uri si o adauga la lista de liste in
	 * care sunt retinute rezultatele ce vor fi scrise in fisier Creez o lista
	 * noua( list1) care va fi lista returnata dupa testarea coliziunilor, iar
	 * la final o adaug in lista re rezultate
	 * 
	 * @param quadTree
	 *            arborele in care se cauta coliziuniea
	 * @param values
	 *            string-ul de valori in care se afloa cooronatele punctului
	 * @param list
	 *            lista de lista in care retin rezultatul fiecarei interogari de
	 *            coliziune
	 */
	private void pointCollision(QuadTree quadTree, String[] values, List<List<Integer>> list) {
		
		double x, y;
		List<Integer> list1;

		x = Double.parseDouble(values[1]);
		y = Double.parseDouble(values[2]);

		list1 = quadTree.findCollisionsWithPoint(new Point(x, y));
		list.add(list1);
	}

	/**
	 * Aceasta metoda testeaza coliziunile cu figuruile din arbore a unei figuri
	 * care se gaseste in vectorul de string-uri de valori Pentru acest lucru
	 * verific nuamrul figurii( 1, 2, 3 sau 4) si creez figura Folosesc metoda
	 * statica parseDouble pentru a initializa coordonatele si apoi testez
	 * coliziunea
	 * 
	 * @param quadTree
	 *            arborle de figuri
	 * @param values
	 *            vectorul de stringuri de valori
	 * @param list
	 *            lista de liste in care retin rezultatele
	 */
	private void objectCollision(QuadTree quadTree, String[] values, List<List<Integer>> list) {
		
		double x1, y1, x2, y2, x3, y3, x4, y4;

		switch (values[1]) {
		case "1":

			Square square;

			x1 = Double.parseDouble(values[2]);
			y1 = Double.parseDouble(values[3]);
			x2 = Double.parseDouble(values[4]);
			y2 = Double.parseDouble(values[5]);

			square = new Square(new Point(x1, y1), new Point(x2, y2), -1);
			list.add(quadTree.findCollisionsWithObject(square));
			break;

		case "2":

			Triangle triangle;
			Point up, left, right;

			x1 = Double.parseDouble(values[2]);
			y1 = Double.parseDouble(values[3]);
			x2 = Double.parseDouble(values[4]);
			y2 = Double.parseDouble(values[5]);
			x3 = Double.parseDouble(values[6]);
			y3 = Double.parseDouble(values[7]);

			up = new Point(x1, y1);
			left = new Point(x2, y2);
			right = new Point(x3, y3);
			triangle = new Triangle(up, left, right, -1);

			list.add(quadTree.findCollisionsWithObject(triangle));
			break;

		case "3":

			Circle circle;

			x1 = Double.parseDouble(values[3]);
			y1 = Double.parseDouble(values[4]);
			x2 = Double.parseDouble(values[2]);

			circle = new Circle(new Point(x1, y1), x2, -1);
			list.add(quadTree.findCollisionsWithObject(circle));
			break;

		case "4":

			Rhombus rhombus;
			Point rUp, rLeft, rLow, rRight;

			x1 = Double.parseDouble(values[2]);
			y1 = Double.parseDouble(values[3]);
			x2 = Double.parseDouble(values[4]);
			y2 = Double.parseDouble(values[5]);
			x3 = Double.parseDouble(values[6]);
			y3 = Double.parseDouble(values[7]);
			x4 = Double.parseDouble(values[8]);
			y4 = Double.parseDouble(values[9]);

			rLow = new Point(x1, y1);
			rLeft = new Point(x2, y2);
			rUp = new Point(x3, y3);
			rRight = new Point(x4, y4);
			rhombus = new Rhombus(rUp, rLeft, rLow, rRight, -1);
			list.add(quadTree.findCollisionsWithObject(rhombus));
			break;
		}
	}

	/**
	 * Aceasta metoda afiseaza o lista Daca aceastae goala afiseaza NIL, iar
	 * daca nu afisez primul element si dupa le fisez pe toate cu spatiu inainte
	 * pentru a nu adauga un saptiu inutil la final Afisarea se face in fisier
	 * folosind un buffered
	 */
	private void printList(List<Integer> list) throws IOException {
		
		if (list.isEmpty()) {
			bw.write("NIL");
		} else {
			
			int firstElement, listSize;

			firstElement = list.get(0);
			listSize = list.size();

			bw.write(Integer.toString(firstElement));
			for (int i = 1; i < listSize; i++) {
				bw.write(" " + list.get(i));
			}
		}
	}

	/**
	 * Aceasta metoda afiseaza fiecare lista din lista de liste in care retin
	 * resultatele interogarilor La fel ca la afisarea unei liste, afisez prima
	 * lista iar dupa ce le afisez pe celelalte
	 */
	private void printResult() throws IOException {
		
		int listSize = resultList.size();
		List<Integer> list = resultList.get(0);

		Collections.sort(list);
		printList(list);

		for (int i = 1; i < listSize; i++) {
			bw.newLine();
			list = resultList.get(i);
			Collections.sort(list);
			printList(list);
		}

		bw.newLine();
	}
}