/**
 * Reprezinta clasa cea mai de baza pentru un nod din arbore care are o operatie
 * de efectuat la vizitarea lui
 */
public abstract class OperatorNode extends TreeNode {

	protected String mOperator;
	private Object mOperand1;
	private Object mOperand2;

	public OperatorNode() {
		this.identifier = "operator";
	}

	public Object getOperand1() {
		return mOperand1;
	}

	public Object getOperand2() {
		return mOperand2;
	}

	public void setOperand1(Object operand1) {
		mOperand1 = operand1;
	}

	public void setOperand2(Object operand2) {
		mOperand2 = operand2;
	}
}