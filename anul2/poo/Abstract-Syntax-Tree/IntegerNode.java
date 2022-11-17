public class IntegerNode extends ParameterNode {

	public IntegerNode(Integer integer) {
		setResult(integer);
	}

	@Override
	public Integer getValue() {
		return (Integer) getResult();
	}

	@Override
	public void accept(Visitor visitor) {
		visitor.visit(this);
	}
}