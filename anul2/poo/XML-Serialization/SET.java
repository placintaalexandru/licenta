import java.util.*;

public class SET extends MyCollection {

	private HashSet<Integer> mHashSet;

	public SET() {

		this.mHashSet = new HashSet<Integer>();
	}

	@Override
	public void add(int element) {
		mHashSet.add(element);
	}

	@Override
	public void remove(int element) {
		for (Integer integer : mHashSet) {
			if (integer == element) {
				mHashSet.remove((Object) integer);
				break;
			}
		}
	}

	@Override
	public Collection<Integer> getNeighboursList() {
		return new ArrayList<Integer>(mHashSet);
	}
}