import java.util.Map;

/**
 * Aceasta clasa asigura instantierea doar unui singur obiect de tip: ParseTree,
 * Visitor, FactoryNodeCreator si ReversePolishMaker Pentru implementare am
 * considerat cate o variabila membru din fiecare instanta, dar statica si
 * privata, si flosesc instantierea la prima apelare a metodey getInstance,
 * depinzand ce instanta se doreste Daca acea instanta exista deja efectuez o
 * curatare si apoi o returnez, daca nu exista o creez cu datele pe care le am
 * pana la acel moment
 */
public class Singleton {

	private static ReversePolishMaker maker = null;
	private static ParseTree parseTree = null;
	private static FactoryNode nodeCreator = null;
	private static Visitor visitor = null;

	public static ReversePolishMaker getMakerInstance() {
		if (maker == null) {
			maker = new ReversePolishMaker();
		} else {
			maker.clear();
		}

		return maker;
	}

	public static ParseTree getParseTreeInstance(Map<String, Object> variableMap, String expression) {
		if (parseTree == null) {
			parseTree = new ParseTree(variableMap, expression);
		} else {
			parseTree.clear();
			parseTree.setVariableMap(variableMap);
			parseTree.buildTree(maker.makeReversePolish(expression));
		}

		return parseTree;
	}

	public static FactoryNode getFactoryInstance(Map<String, Object> variableMap) {
		if (nodeCreator == null) {
			nodeCreator = new FactoryNode(variableMap);
		} else {
			nodeCreator.setVariableMap(variableMap);
		}

		return nodeCreator;
	}

	public static Visitor getVisitorInstance() {
		if (visitor == null) {
			visitor = new EvaluateVisitor();
		}

		return visitor;
	}
}