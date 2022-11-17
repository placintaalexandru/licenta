import java.util.Collection;

public abstract class MyCollection {

	public abstract void add(int element);

	public abstract void remove(int element);

	public abstract Collection<Integer> getNeighboursList();
}