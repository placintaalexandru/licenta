
public class Triangle extends GeometricObject {

	private Point mLeftLow;
	private Point mRightLow;
	private Point mUp;
	private Square mCharacteristicSquare;

	public Triangle() {
	}

	public Triangle(Point mUp, Point mLeftLow, Point mRightLow, int mID) {
		
		super(mID);
		double xUp, yUp;

		xUp = mRightLow.getmX();
		yUp = mUp.getmY();

		this.mCharacteristicSquare = new Square(mLeftLow, new Point(xUp, yUp), -1);
		this.mLeftLow = mLeftLow;
		this.mRightLow = mRightLow;
		this.mUp = mUp;
	}

	/**
	 * Aceasta metoda intoarce dreptunghiul incadrator pentru un tringhiu
	 * 
	 * @return Square dreptunghiul incadrator pentru un triunghi
	 */
	@Override
	public Square getSurroundRectangle() {
		
		return mCharacteristicSquare;
	}

	/**
	 * Aceasta metoda verifica daca un punct se gaseste intr-un triunghi Pentru
	 * a verifica acest lucru calculez pe rand cele 3 arii formate de punct cu 2
	 * dintre varfuri, iar la final verific egalitatea dintre suma celor 3 si
	 * aria triunghiului Pentru a calcula aria unui triunghi calculez
	 * determinantul celor 3 puncte
	 * 
	 * @param p
	 *            punctul care se verifica
	 * @return valoarea de adevar
	 */
	@Override
	public boolean contains(Point p) {
		
		double area1, area2, area3;

		area1 = 0.5 * Math.abs(Calculator.determinant(p, mLeftLow, mRightLow));
		area2 = 0.5 * Math.abs(Calculator.determinant(p, mLeftLow, mUp));
		area3 = 0.5 * Math.abs(Calculator.determinant(p, mRightLow, mUp));

		return (getArea() == area1 + area2 + area3);
	}

	/**
	 * Aceasta metoda verifica coliziunea dintre triunghi si o figura geometrica
	 * Folosesc draptunghiurile incadratoare, iar daca el se ating atunci e
	 * coliziune
	 * 
	 * @param geometricObject
	 *            figura cu care se testeaza coliziunea
	 * @return valoarea de adevar
	 */
	@Override
	public boolean collidesWith(GeometricObject geometricObject) {
		
		return getSurroundRectangle().touches(geometricObject.getSurroundRectangle());
	}

	/**
	 * Aceasta metoda calculeaza aria triunghiului folosind formula cu
	 * determinant
	 * 
	 * @return double aria triunghiului
	 */
	public double getArea() {
		return 0.5 * Math.abs(Calculator.determinant(mLeftLow, mRightLow, mUp));
	}
}
