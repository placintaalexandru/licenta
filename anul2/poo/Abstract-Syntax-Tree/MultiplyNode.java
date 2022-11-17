public class MultiplyNode extends OperatorNode {

	public MultiplyNode() {
		this.mOperator = "*";
	}

	@Override
	public void accept(Visitor visitor) {
		visitor.visit(this);
	}
}