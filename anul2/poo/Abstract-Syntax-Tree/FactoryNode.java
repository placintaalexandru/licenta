import java.util.Map;

/**
 * Aceasta clasa implementeaza design pattern-ul factory, cu ajutorul unei Mape
 * de variabile si a unui parametru, in functie de care se creeaza un nod pentru
 * arbore
 */
public class FactoryNode {

	private Map<String, Object> mVariableMap;

	public FactoryNode(Map<String, Object> variableMap) {
		mVariableMap = variableMap;
	}

	public void setVariableMap(Map<String, Object> variableMap) {
		mVariableMap = variableMap;
	}

	/**
	 * Creeaza un nod din arbore pe baza unui parametru, sau a unei conditii
	 */
	public TreeNode createNode(String type) {
		if (type.compareTo("+") == 0) {
			return new PlusNode();
		} else if (type.compareTo("-") == 0) {
			return new MinusNode();
		} else if (type.compareTo("*") == 0) {
			return new MultiplyNode();
		} else if (type.compareTo("/") == 0) {
			return new DivisionNode();
		} else if (mVariableMap.get(type).toString().equals(mVariableMap.get(type))) {
			return new StringNode((String) mVariableMap.get(type));
		} else if (mVariableMap.get(type).toString().contains(".")) {
			return new DoubleNode((Double) mVariableMap.get(type));
		} else if (!mVariableMap.get(type).toString().contains(".")) {
			return new IntegerNode((Integer) mVariableMap.get(type));
		}
		return null;
	}
}