
public class Point extends GeometricObject {

	private double mX;
	private double mY;

	public Point() {
	}

	public Point(double mX, double mY) {
		
		this.mX = mX;
		this.mY = mY;
	}

	/**
	 * Aceasta metoda intoarce dreptunghiul incadrator pentru un punct
	 * Metoda nu primeste niciun parametru, deoarece totul se refera la instanta obiectului respectiv
	 * @return dreptunghiul incadrator
	 */
	@Override
	public Square getSurroundRectangle() {
		
		return new Square(this, this, -1);
	}
	
	/**
	 * Aceasta metoda verifica daca un punct contine alt punct, daca sunt identice
	 * @param p punctul care se verifica daca este inclus sau nu acelasi cu punctul din instanta curenta
	 * @return valoarea de adevar
	 */
	@Override
	public boolean contains(Point p) {
		
		return isTheSameAs(p);
	}
	
	/**
	 * Aceasta metoda verifica daca instanta curenta a punctului este inclusa in figura geometrica
	 * @param geometricObject figura care este verificata daca contine punctul
	 * @return valoarea de adevar
	 */
	@Override
	public boolean collidesWith(GeometricObject geometricObject) {
		
		return geometricObject.contains(this);
	}

	public double getmX() {
		
		return mX;
	}

	public double getmY() {
		
		return mY;
	}

	/**
	 * Aceasta metoda verifica daca 2 puncte sunt identica
	 * @param p punctul cu care se verifica
	 * @return valoarea de adevar
	 */
	public boolean isTheSameAs(Point p) {
		
		return ((mX == p.getmX()) && (mY == p.getmY()));
	}

	public boolean isLeftTo(Point p) {
		
		return (mX < p.getmX());
	}

	public boolean isRightTo(Point p) {
		
		return (mX > p.getmX());
	}

	public boolean isLowerThan(Point p) {
		
		return (mY < p.getmY());
	}

	public boolean isHigherThan(Point p) {
		
		return (mY > p.getmY());
	}

	/**
	 * Aceasta metoda calculeaza distanta dintre 2 puncte
	 * @param p1 primul punct
	 * @param p2 al 2 lea punct
	 * @return distanta dintre cele 2 puncte
	 */
	public static double distanceBetween(Point p1, Point p2) {
		
		double x1, x2, y1, y2;

		x1 = p1.getmX();
		y1 = p1.getmY();
		x2 = p2.getmX();
		y2 = p2.getmY();

		return Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	}
}
