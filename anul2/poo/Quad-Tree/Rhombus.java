
public class Rhombus extends GeometricObject {

	private Point mLow;
	private Point mUp;
	private Point mLeft;
	private Point mRight;
	private Square mCharacteristicSquare;

	public Rhombus() {
	}

	public Rhombus(Point mUp, Point mLeft, Point mLow, Point mRight, int mID) {
		
		super(mID);
		double xLeft, yLeft, xRight, yRight;

		xLeft = mLeft.getmX();
		yLeft = mLow.getmY();
		xRight = mRight.getmX();
		yRight = mUp.getmY();

		this.mCharacteristicSquare = new Square(new Point(xLeft, yLeft), new Point(xRight, yRight), -1);
		this.mLow = mLow;
		this.mUp = mUp;
		this.mLeft = mLeft;
		this.mRight = mRight;
	}

	/**
	 * Aceasta metoda returneaza dreptunghiul incadrator pentru un romb
	 * 
	 * @return Square dreptunghiul incadrator pentru romb
	 */
	@Override
	public Square getSurroundRectangle() {
		return mCharacteristicSquare;
	}

	/**
	 * Aceasta metoda verifica daca un punct se afla in interiorul rombului
	 * Pentru a verifica acest calculez cele 4 arii, determinate de punct cu 2
	 * dintre varfurile rombuilui, iar la final compar suma lor cu aria rombului
	 * 
	 * @param p
	 *            punctul cu care se verifica
	 * @return valoarea de adeavar
	 */
	@Override
	public boolean contains(Point p) {

		double area1, area2, area3, area4;
		double lungimeDiag1, lungimeDiag2;

		area1 = 0.5 * Math.abs(Calculator.determinant(p, mLeft, mUp));
		area2 = 0.5 * Math.abs(Calculator.determinant(p, mUp, mRight));
		area3 = 0.5 * Math.abs(Calculator.determinant(p, mLow, mRight));
		area4 = 0.5 * Math.abs(Calculator.determinant(p, mLeft, mLow));
		lungimeDiag1 = mRight.getmX() - mLeft.getmX();
		lungimeDiag2 = mUp.getmY() - mLow.getmY();

		return (lungimeDiag1 * lungimeDiag2 / 2 == area1 + area2 + area3 + area4);
	}

	/**
	 * Aceasta metoda verifica daca un rombg se ciocneste cu o figura geoemtrica
	 * Coliziunea se realizeaza prin verificarea atingerii dreptunghiurilor
	 * incadratoare
	 * 
	 * @param geoemtricObject
	 *            figrua cu care se testeaza coliziunea
	 * @return valoarea de adevar
	 */
	@Override
	public boolean collidesWith(GeometricObject geometricObject) {
		
		return getSurroundRectangle().touches(geometricObject.getSurroundRectangle());
	}
}
