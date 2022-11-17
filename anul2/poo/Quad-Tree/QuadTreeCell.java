
import java.util.LinkedList;
import java.util.List;

public class QuadTreeCell {

	private double mLungimePlan;
	private GeometricObject mPlanCenter;
	private GeometricObject mCharacteristicSquare;
	private List<GeometricObject> mFigures;
	private List<QuadTreeCell> mSubPlans;

	public QuadTreeCell() {
	}

	public QuadTreeCell(Point mPlanCenter, double mLungimePlan) {
		
		double xLow, yLow, xUp, yUp;

		xLow = mPlanCenter.getmX() - mLungimePlan / 2;
		yLow = mPlanCenter.getmY() - mLungimePlan / 2;
		xUp = mPlanCenter.getmX() + mLungimePlan / 2;
		yUp = mPlanCenter.getmY() + mLungimePlan / 2;

		this.mPlanCenter = mPlanCenter;
		this.mLungimePlan = mLungimePlan;
		this.mFigures = new LinkedList<GeometricObject>();
		this.mSubPlans = new LinkedList<QuadTreeCell>();
		this.mCharacteristicSquare = (GeometricObject) new Square(new Point(xLow, yLow), new Point(xUp, yUp), -1);
	}

	public List<GeometricObject> getmFigures() {
		
		return mFigures;
	}

	public List<QuadTreeCell> getmSubPlans() {
		
		return mSubPlans;
	}

	public Square getCharacteristicSquare() {
		
		return (Square) mCharacteristicSquare;
	}

	/**
	 * Aceast metoda adauga 4 elemente in lista de fii, geometric imparte planul
	 * celulei curente in 4 subplane Pentru fiecare fiu introduc centrul
	 * planului sau, respectiv lungimea unei laturi a subplanuri la
	 * initializare, prin intermediul constructorului La o impartire, lungimea
	 * planului se injumatateste
	 */
	public void split() {
		
		double x, y;
		Point auxPoint = (Point) mPlanCenter;

		x = auxPoint.getmX();
		y = auxPoint.getmY();

		mSubPlans.add(new QuadTreeCell(new Point(x + mLungimePlan / 4, y + mLungimePlan / 4), mLungimePlan / 2));
		mSubPlans.add(new QuadTreeCell(new Point(x - mLungimePlan / 4, y + mLungimePlan / 4), mLungimePlan / 2));
		mSubPlans.add(new QuadTreeCell(new Point(x - mLungimePlan / 4, y - mLungimePlan / 4), mLungimePlan / 2));
		mSubPlans.add(new QuadTreeCell(new Point(x + mLungimePlan / 4, y - mLungimePlan / 4), mLungimePlan / 2));
	}

	/**
	 * Aceaste metoda verifica daca celula curenta are doar frunze Pentru a
	 * verifica acest lucru am verificat ca toti cei 4 fii ai celulei curente sa
	 * aiba daor frunze
	 */
	public boolean hasOnlyLeaves() {
		return ((mSubPlans.get(0).getmSubPlans().isEmpty()) && (mSubPlans.get(1).getmSubPlans().isEmpty())
				&& (mSubPlans.get(2).getmSubPlans().isEmpty()) && (mSubPlans.get(3).getmSubPlans().isEmpty()));
	}
}