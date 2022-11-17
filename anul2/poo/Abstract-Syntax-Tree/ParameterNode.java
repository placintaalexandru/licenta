/**
 * Reprezinta clasa cea mai de baza pentru un nod care are o valoare la
 * vizitarea lui
 */
public abstract class ParameterNode extends TreeNode {

	protected OperatorNode mParent;

	public abstract Object getValue();

	public ParameterNode() {
		this.identifier = "parameter";
	}
}