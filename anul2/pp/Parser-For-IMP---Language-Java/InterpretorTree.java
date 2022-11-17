
import java.util.HashMap;
import java.util.Map;

/**
 * Created by ALEX on 3/14/2017.
 */
public class InterpretorTree {

    public static final String ASSRERT_FAILED = "Assert failed";
    public static final String CHECK_FAILED = "Check failed";
    public static final String MISSING_RETURN = "Missing return";

    private TreeNode mRoot;
    private Map<String, Integer> mVariableMap;
    private StringWorker mStringWorker;
    private Object mResult;

    public InterpretorTree(String programToInterpret) {
        this.mRoot = new ProgramNode(null);
        this.mVariableMap = new HashMap<>();
        this.mStringWorker = new StringWorker(programToInterpret);
        buildTree();
    }

    public Object getResult() {
        return mResult;
    }

    public TreeNode getRoot() {
        return mRoot;
    }

    public void setResult(Object result) {
        mResult = result;
    }

    private void buildTree() {
        TreeNode currentNode = mRoot;
        TreeNode nodeToCreate;
        String nodeType;

        for (int i = 0; i < mStringWorker.getProgram().length(); i++) {
            if (mStringWorker.getProgram().charAt(i) == '[') {
                nodeType = mStringWorker.getNodeTypeFrom(i + 1);
                nodeToCreate = FactoryNode.createNode(nodeType, mVariableMap, currentNode);
                currentNode.addChild(nodeToCreate);
                currentNode = nodeToCreate;
            } else if (mStringWorker.getProgram().charAt(i) == ']') {
                currentNode = currentNode.getParent();
            } else if (((Character.isAlphabetic(mStringWorker.getProgram().charAt(i))) ||
                        (Character.isDigit(mStringWorker.getProgram().charAt(i))) ||
                        (mStringWorker.getProgram().charAt(i) == '-')) &&
                        (mStringWorker.getProgram().charAt(i - 1) == ' ')) {
                nodeType = mStringWorker.getNodeTypeFrom(i);
                nodeToCreate = FactoryNode.createNode(nodeType, mVariableMap, currentNode);
                currentNode.addChild(nodeToCreate);
            }
        }
    }
    
    public void evaluateProgram() {
    	Evaluator evaluator = new Evaluator(mVariableMap, this);
    	
    	mRoot.accept(evaluator);
    	if (mResult == null) {
    		mResult = MISSING_RETURN;
    	} else {
    		if (CHECK_FAILED.equals(mResult)) {
    			return;
    		} else if (ASSRERT_FAILED.equals(mResult)) {
    			if (!evaluator.hasReturn()) {
    				mResult = MISSING_RETURN;
    			}
    			
    			return;
    		}
    		
    		if (mResult instanceof Boolean) {
    			return;
    		}
    		
    		final String result = mResult.toString();
    		if (Character.isLetter(result.charAt(0))) {
    			if (mVariableMap.get(result) != null) {
    				mResult = mVariableMap.get(result);
    			} else {
    				mResult = CHECK_FAILED;
    			}
    		}
    	}
    }
}