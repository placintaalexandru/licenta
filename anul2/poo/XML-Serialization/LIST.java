import java.util.Collection;
import java.util.LinkedList;

public class LIST extends MyCollection {

	private LinkedList<Integer> mIntegerLinkedList;

	public LIST() {

		this.mIntegerLinkedList = new LinkedList<Integer>();
	}

	@Override
	public void add(int element) {
		mIntegerLinkedList.add(element);
	}

	@Override
	public void remove(int element) {
		for (Integer integer : mIntegerLinkedList) {
			if (integer == element) {
				mIntegerLinkedList.remove((Object) integer);
				break;
			}
		}
	}

	@Override
	public Collection<Integer> getNeighboursList() {
		return mIntegerLinkedList;
	}
}