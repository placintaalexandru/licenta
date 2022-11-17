import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

/**
 * Clasa responsabila cu crearea Revrse Polish Form-ului pentru o expresie de
 * evaluat
 */
public class ReversePolishMaker {

	private Stack<String> mFinalStack;
	private Stack<String> mStack;
	private Map<String, Integer> mPriorityMap;

	public ReversePolishMaker() {
		mFinalStack = new Stack<String>();
		mStack = new Stack<String>();
		mPriorityMap = new HashMap<String, Integer>();
		initializePriorityMap();
	}

	/**
	 * Initializeaza prioritatile conform ordinii din enunt
	 */
	private void initializePriorityMap() {
		this.mPriorityMap.put("+", 0);
		this.mPriorityMap.put("-", 0);
		this.mPriorityMap.put("*", 1);
		this.mPriorityMap.put("/", 1);
	}

	/**
	 * Verifica daca un token din expresie este operator
	 */
	private boolean isOperator(String token) {
		return ((token.compareTo("*") == 0) || (token.compareTo("+") == 0) || (token.compareTo("-") == 0)
				|| (token.compareTo("/") == 0));
	}

	/**
	 * Verifica daca un token din expresie este paranteza dreapta
	 */
	private boolean isRightParenthesis(String token) {
		return (token.compareTo(")") == 0);
	}

	/**
	 * Verifica daca un token din expresie este paranteza stanga
	 */
	private boolean isLeftParenthesis(String token) {
		return (token.compareTo("(") == 0);
	}

	/**
	 * Verifica daca un token din expresie este operand, prin simpla verificare
	 * daca nu este operator sau paranteza
	 */
	private boolean isOperand(String token) {
		return ((!isOperator(token)) && (!isRightParenthesis(token)) && (!isLeftParenthesis(token)));
	}

	/**
	 * Creeaza o stiva in care sunt retinute simbolurile expresiei, in ordine
	 * inversa, ultimul simbol din expresie e la varful stivei, ultimul simbol
	 * in sensul ca el reprezinta operatia ce se va efectua ultima la evelauarea
	 * expresiei Pentru implementare am urmat algoritmul prezentat in resursele
	 * temei Folosesc 2 stive, stive, cea finala este cea in care retin
	 * simbolurile pentru a construi arborele Daca dau de o variabila o bag in
	 * stiva finala, iar daca dau de un operator, cat timp prioritatea din
	 * varful stivei auxiliare e mai mare decat cea de introdus, extrag din stva
	 * auxiliara si introduc in stiva finala, iar la final introduc simbolul nou
	 * in stiva auxiliara Daca dau de o paranteza stanga, efectuez ce am spus
	 * mai sus, iar cand am dat de o paranteza dreapta extrag din stiva
	 * auxiliara si bag in cea finala cat timp nu dau de paranteza stanga La
	 * final extrag din stiva auxiliara si bag in cea finala cat timp cea
	 * auxiliara nu e vida
	 */
	public Stack<String> makeReversePolish(String evaluatedExpression) {
		String[] tokens = evaluatedExpression.split("[\" \"] *");

		for (int i = 0; i < tokens.length; i++) {
			if (isOperand(tokens[i])) {
				mFinalStack.push(tokens[i]);
			} else if (isOperator(tokens[i])) {
				if (mStack.isEmpty()) {
					mStack.push(tokens[i]);
				} else {
					if ((!mStack.isEmpty()) && (isOperator(mStack.peek()))) {
						if (mPriorityMap.get(mStack.peek()) >= mPriorityMap.get(tokens[i])) {
							while ((!mStack.isEmpty()) && (isOperator(mStack.peek()))
									&& (mPriorityMap.get(mStack.peek()) >= mPriorityMap.get(tokens[i]))) {
								mFinalStack.push(mStack.pop());
							}
						}
					}

					mStack.push(tokens[i]);
				}
			} else if (isLeftParenthesis(tokens[i])) {
				mStack.push(tokens[i]);
			} else if (isRightParenthesis(tokens[i])) {
				while (isOperator(mStack.peek())) {
					mFinalStack.push(mStack.pop());
				}

				mStack.pop();
			}
		}

		while (!mStack.isEmpty()) {
			mFinalStack.push(mStack.pop());
		}

		return mFinalStack;
	}

	/**
	 * Curata cele 2 stive, pentru a fi folosite si alte evaluari
	 */
	public void clear() {
		mFinalStack.clear();
		mStack.clear();
	}
}