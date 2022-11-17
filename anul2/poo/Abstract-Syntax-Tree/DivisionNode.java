public class DivisionNode extends OperatorNode {

	public DivisionNode() {
		this.mOperator = "/";
	}

	@Override
	public void accept(Visitor visitor) {
		visitor.visit(this);
	}
}