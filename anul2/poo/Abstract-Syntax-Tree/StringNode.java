public class StringNode extends ParameterNode {

	public StringNode(String string) {
		setResult(string);
	}

	@Override
	public String getValue() {
		return (String) getResult();
	}

	@Override
	public void accept(Visitor visitor) {
		visitor.visit(this);
	}

}