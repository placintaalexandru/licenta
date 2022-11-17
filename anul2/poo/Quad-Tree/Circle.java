
public class Circle extends GeometricObject {

	private Point mCenter;
	private double mRadius;
	private GeometricObject mCharacteristicSquare;

	public Circle() {
	}

	public Circle(Point mCenter, double mRadius, int mID) {

		super(mID);
		double x, y;

		x = mCenter.getmX();
		y = mCenter.getmY();

		this.mCharacteristicSquare = (GeometricObject) new Square(new Point(x - mRadius, y - mRadius),
																	new Point(x + mRadius, y + mRadius), -1);
		this.mCenter = mCenter;
		this.mRadius = mRadius;
	}

	/**
	 * Aceasta metoda creeaza dreptunghiu incadrator pentru un cerc
	 * 
	 * @return Square dreptunghiul incadrator cercului
	 */
	@Override
	public Square getSurroundRectangle() {

		return (Square) mCharacteristicSquare;
	}

	/**
	 * Aceasta metoda verifica daca un punct se afla in interiorul cercului
	 * Pentru a verifica acest lucru am calculat distanta dintre punct si centru
	 * si am comparat-o cu raza cercului
	 * 
	 * @param p
	 *            punctul care se verifica
	 * @return valoarea de adevar
	 */
	@Override
	public boolean contains(Point p) {
		
		return (Point.distanceBetween(p, mCenter) <= mRadius);
	}

	/**
	 * Aceasta metoda verifica coliziunea cu o figura geometrica Coliziunea se
	 * face prin atingerea dreptunghiurilor incadratoare ale celor 2 figuri
	 * 
	 * @param geometricObject
	 *            figura cu care se testeaza coliziunea
	 * @return valoarea de adevar
	 */
	@Override
	public boolean collidesWith(GeometricObject geometricObject) {
		
		return getSurroundRectangle().touches(geometricObject.getSurroundRectangle());
	}
}
