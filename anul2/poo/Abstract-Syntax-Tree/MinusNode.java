public class MinusNode extends OperatorNode {

	public MinusNode() {
		this.mOperator = "-";
	}

	@Override
	public void accept(Visitor visitor) {
		visitor.visit(this);
	}
}