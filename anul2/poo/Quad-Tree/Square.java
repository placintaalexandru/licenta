
public class Square extends GeometricObject {

	private Point mLeftDown;
	private Point mRightUp;

	public Square() {
	}

	public Square(Point mLeftDown, Point mRightUp, int mID) {
		
		super(mID);
		this.mLeftDown = mLeftDown;
		this.mRightUp = mRightUp;
	}

	public Point getmLeftDown() {
		
		return mLeftDown;
	}

	public Point getmRightUp() {
		
		return mRightUp;
	}

	/**
	 * Aceasta metoda creeaza dreptunghiul incadrator, care pentru un patrat dreptunghi e chiar el insusi
	 * @return Square el insusi
	 */
	@Override
	public Square getSurroundRectangle() {
		
		return this;
	}
	
	/**
	 * Aceasta metoda verifica daca patratul contine un punct
	 * @param p punctul primit ca parametru
	 * @return valoarea de adevar
	 */
	@Override
	public boolean contains(Point p) {
		
		return !(p.isLeftTo(mLeftDown) | p.isLowerThan(mLeftDown) | p.isHigherThan(mRightUp) | p.isRightTo(mRightUp));
	}

	/**
	 * Aceasta metoda verifica daca patratul se intersecteaza cu o figura geoemetrica
	 * Pentru a testa coliziunea verific daca cele 2 dreptunghiuri incadratoare se ating in vreun fel
	 * @param geometricObject figura eometrica cu care se verifica coliziunea
	 * @return valaorea de adevar
	 */
	@Override
	public boolean collidesWith(GeometricObject geometricObject) {
		
		return getSurroundRectangle().touches(geometricObject.getSurroundRectangle());
	}

	/**
	 * Aceasta metoda verifica daca 2 patrate/ dreptunghiuri se ating
	 * Pentru a face aceasta verificare este mai usor sa verific daca nu se ating si neg valoare rezultatului
	 * Pentru a verifica daca 2 dreptunghiuri/ patrate nu se ating verifica daca unul e mai sus/ mai jos decat celalalt sau in stanga/ dreapta celuilalt
	 * Daca punctul din dreapta primului patrat e in stanga punctului din stanga celuilalt patrat, atunci primul patrat e in stanga, analog pt celelalte 3 cazuri
	 * @param square dreptunghiu/ patratul incadrator al celeilalte figuri
	 * @return valoarea de adevar
	 */
	public boolean touches(Square square) {
		
		return !(mRightUp.isLeftTo(square.getmLeftDown()) | mRightUp.isLowerThan(square.mLeftDown)
				| mLeftDown.isHigherThan(square.mRightUp) | mLeftDown.isRightTo(square.getmRightUp()));
	}
}
