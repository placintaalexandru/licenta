public class PlusNode extends OperatorNode {

	public PlusNode() {
		this.mOperator = "+";
	}

	@Override
	public void accept(Visitor visitor) {
		visitor.visit(this);
	}
}