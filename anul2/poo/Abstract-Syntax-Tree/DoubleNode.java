public class DoubleNode extends ParameterNode {

	public DoubleNode(Double doubleVariable) {
		setResult(doubleVariable);
	}

	@Override
	public Double getValue() {
		return (Double) getResult();
	}

	@Override
	public void accept(Visitor visitor) {
		visitor.visit(this);
	}
}