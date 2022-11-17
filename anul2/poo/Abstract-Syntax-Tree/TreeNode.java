
/**
 * Reprezinta clasa cea mai de baza, fiind situata cel mai sus pe lantul de
 * osteniri pentru un nod din arbore
 */
public abstract class TreeNode implements Visitable {

	private TreeNode mLeft;
	private TreeNode mRight;
	private TreeNode mParent;
	private Object mResult;
	protected String identifier;

	public TreeNode getLeft() {
		return mLeft;
	}

	public TreeNode getRight() {
		return mRight;
	}

	public Object getResult() {
		return mResult;
	}

	public OperatorNode getParent() {
		return (OperatorNode) mParent;
	}

	public void setLeft(TreeNode left) {
		mLeft = left;
	}

	public void setRight(TreeNode right) {
		mRight = right;
	}

	public void setParent(TreeNode parent) {
		mParent = parent;
	}

	public void setResult(Object o) {
		this.mResult = o;
	}

	public boolean isParameterNode() {
		return (identifier.compareTo("parameter") == 0);
	}
}