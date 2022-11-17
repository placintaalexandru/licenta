
public abstract class GeometricObject {

	private int mID;

	public GeometricObject() {
	}

	public GeometricObject(int mID) {
		
		this.mID = mID;
	}

	public int getmID() {
		
		return mID;
	}

	public abstract Square getSurroundRectangle();

	public abstract boolean contains(Point p);

	public abstract boolean collidesWith(GeometricObject geometricObject);

   /**
    * Aceasta metoda verifica daca o figura geometrica trebuie inserata in subplanul reprezentat de celula din arbore
    * Pentru acest lucru am verifica daca dreptunghiul incadrator atinge patratul caracteristic al subplanului reprezentat de celula din arbore
    * Patratul caracteristic al unei celule reprezinta, geometric, patratul, bucata din planul de desenare, pe care il reprezinta acea celula
    * Daca dreptunghiul incadrator atinge in vreun fel patratul caracteristic, atunci figura trebuie inserata in acel subplan
    * @param quadTreeCell celula, geometric vorbind subplanul, pentru care se face verificarea de apartenenta
    * @return valoarea de adevar
    */
	public boolean fitsInSubPlanOf(QuadTreeCell quadTreeCell) {
		
		return getSurroundRectangle().touches(quadTreeCell.getCharacteristicSquare());
	}
}
