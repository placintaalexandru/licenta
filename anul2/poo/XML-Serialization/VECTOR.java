import java.util.ArrayList;
import java.util.Collection;

public class VECTOR extends MyCollection {

	private ArrayList<Integer> mIntegerArrayList;

	public VECTOR() {

		mIntegerArrayList = new ArrayList<Integer>();
	}

	@Override
	public void add(int element) {
		mIntegerArrayList.add(element);
	}

	@Override
	public void remove(int element) {
		for (Integer integer : mIntegerArrayList) {
			if (integer == element) {
				mIntegerArrayList.remove((Object) integer);
				break;
			}
		}
	}

	@Override
	public Collection<Integer> getNeighboursList() {

		return mIntegerArrayList;
	}
}