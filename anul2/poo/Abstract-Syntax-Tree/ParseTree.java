import java.util.Map;
import java.util.Stack;

/**
 * Contine arborele aferent unei expresii ce urmeaza a fi evaluata
 */
public class ParseTree {

	private TreeNode mRoot;
	private Map<String, Object> mVariableMap;

	public ParseTree(Map<String, Object> variableMap, String evaluateExpression) {
		this.mVariableMap = variableMap;
		buildTree(Singleton.getMakerInstance().makeReversePolish(evaluateExpression));
	}

	public void setVariableMap(Map<String, Object> variableMap) {
		mVariableMap = variableMap;
	}

	/**
	 * Construiest un arbore pornind de la un nod curent, daca acel nod nu este
	 * nod ce contine variabila Pentru implementare verific daca stiva de
	 * simboluri ete vida, caz in care ma opresc, iar daca nu verific daca nodul
	 * curent este nod ce contine variabila, deoarece nodurile ce contin
	 * variabile nu au cum sa contina copii Daca nodul curent are ambii fii
	 * nenuli ma opres, deoarece nu mai am de ce sa il completez Pentru umplerea
	 * fiilor verific daca fiul drept este nul, deoarece simbolurile expresiei
	 * sunt in ordine inversa in stiva, cel mai din stanga se afla la baza
	 * stivei, iar daca fiul drept e nul, creez un nod de arbore folosind
	 * pattern-ul Singleton si Factory Pentru a asigura umplerea si celuluilalt
	 * fiu, dupa ce am terminat de umplut fiul drept, trec din nou prin nodul
	 * curent, unde se va verifica daca fiul drept e nul, iar daca nu se va
	 * verifica fiul stang si se va umple acela
	 */
	private void build(Stack<String> expression, TreeNode startingNode) {
		if (expression.isEmpty()) {
			return;
		}

		if (startingNode.isParameterNode()) {
			return;
		}

		if ((startingNode.getLeft() != null) && (startingNode.getRight() != null)) {
			return;
		}

		if (startingNode.getRight() == null) {
			startingNode.setRight(Singleton.getFactoryInstance(mVariableMap).createNode(expression.pop()));
			startingNode.getRight().setParent(startingNode);
		} else if (startingNode.getLeft() == null) {
			startingNode.setLeft(Singleton.getFactoryInstance(mVariableMap).createNode(expression.pop()));
			startingNode.getLeft().setParent(startingNode);
		}

		build(expression, startingNode.getRight());
		build(expression, startingNode);
		build(expression, startingNode.getLeft());

	}

	/**
	 * Construiest un arbore pornind de la radacina acestuia Pentru implementare
	 * construiesc radacina arborelui, avand ca simbol simbolul cel mai sus din
	 * stiva, iar daca acest simbol reprezinta o variabila, functia build se va
	 * opri, nemaiconstruind arborele, va ramane doar un nod, acest lucru fiind
	 * realizat prin verificarea de nod de tip parametru
	 */
	public void buildTree(Stack<String> expression) {
		mRoot = Singleton.getFactoryInstance(mVariableMap).createNode(expression.pop());
		build(expression, mRoot);
		build(expression, mRoot);
	}

	/**
	 * Curata arborele, prin facerea radacinii nule si a mapei de variabile
	 */
	public void clear() {
		this.mRoot = null;
		this.mVariableMap = null;
	}

	/**
	 * Intoarce un obiect ce reprezinta rezultatul evaluarii expresiei
	 */
	public Object getResult() {
		mRoot.accept(Singleton.getVisitorInstance());

		if (mRoot.getResult() instanceof Double) {
			if ((Double) mRoot.getResult() == Double.MAX_VALUE) {
				return "NaN";
			} else {
				return Calculator.twoZecimalRound((Double) mRoot.getResult());
			}
		} else if (mRoot.getResult() instanceof Integer) {
			if ((Integer) mRoot.getResult() == Integer.MAX_VALUE) {
				return "NaN";
			}
		}

		return mRoot.getResult();
	}
}