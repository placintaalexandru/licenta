import java.util.Map;

/**
 * Created by ALEX on 3/14/2017.
 */
public class Evaluator implements Visitor {

    private Map<String, Integer> mVariableMap;
    private InterpretorTree mInterpretorTree;

    public Evaluator(Map<String, Integer> variableMap, InterpretorTree interpretorTree) {
        this.mVariableMap = variableMap;
        this.mInterpretorTree = interpretorTree;
    }

    InterpretorTree getInterpretorTree() {
        return mInterpretorTree;
    }

    boolean checkForStopping(InterpretorTree interpretorTree) {
        return (InterpretorTree.CHECK_FAILED.equals(interpretorTree.getResult())) ||
                (InterpretorTree.ASSRERT_FAILED.equals(interpretorTree.getResult())) ||
                (InterpretorTree.MISSING_RETURN.equals(interpretorTree.getResult()));
    }

    protected Integer getParameter(TreeNode treeNode, int index) {
        String name;
        Integer value;

        if (treeNode.getChildren().get(index).getResult() instanceof String) {
            name = (String)treeNode.getChildren().get(index).getResult();
            value = mVariableMap.get(name);
        } else {
            value = (Integer)treeNode.getChildren().get(index).getResult();
        }

        return value;
    }

    @Override
    public void visit(IntegerNode integerNode) {
        integerNode.setResult(integerNode.getParameter1());
    }

    @Override
    public void visit(VariableNode variableNode) {
        variableNode.setResult(variableNode.getParameter1());
    }

    @Override
    public void visit(ProgramNode programNode) {
        programNode.universalAccept(this);
    }

    @Override
    public void visit(AsignmentNode asignmentNode) {
        String name;
        Integer value;

        asignmentNode.universalAccept(this);
        if (checkForStopping(mInterpretorTree)) {
            return;
        }

        name = (String)asignmentNode.getChildren().get(0).getResult();
        value = (Integer)asignmentNode.getChildren().get(1).getResult();
        asignmentNode.makeOperation();
    }

    @Override
    public void visit(AssertNode assertNode) {
        assertNode.universalAccept(this);
        if (checkForStopping(mInterpretorTree)) {
            return;
        }

        if (!(Boolean)(assertNode.getChildren().get(0).getResult())) {
            mInterpretorTree.setResult(InterpretorTree.ASSRERT_FAILED);
        }
    }

    @Override
    public void visit(DivisionNode divisionNode) {
        Integer param1, param2;

        divisionNode.universalAccept(this);
        if (checkForStopping(mInterpretorTree)) {
            return;
        }

        param1 = getParameter(divisionNode, 0);
        param2 = getParameter(divisionNode, 1);
        if ((param1 == null) || (param2 == null)) {
            mInterpretorTree.setResult(InterpretorTree.CHECK_FAILED);
            return;
        }

        divisionNode.setResult(param1 / param2);
    }

    @Override
    public void visit(EqualNode equalNode) {
        Integer param1, param2;

        equalNode.universalAccept(this);
        if (checkForStopping(mInterpretorTree)) {
            return;
        }

        param1 = getParameter(equalNode, 0);
        param2 = getParameter(equalNode, 1);

        if ((param1 == null) || (param2 == null)) {
            mInterpretorTree.setResult(InterpretorTree.CHECK_FAILED);
            return;
        }

        equalNode.setResult(param1 == param2);
    }

    @Override
    public void visit(GreaterOrEqualNode greaterOrEqualNode) {
        Integer param1, param2;

        greaterOrEqualNode.universalAccept(this);
        if (checkForStopping(mInterpretorTree)) {
            return;
        }

        param1 = getParameter(greaterOrEqualNode, 0);
        param2 = getParameter(greaterOrEqualNode, 1);
        if ((param1 == null) || (param2 == null)) {
            mInterpretorTree.setResult(InterpretorTree.CHECK_FAILED);
            return;
        }

        greaterOrEqualNode.setResult(param1 >= param2);
    }

    @Override
    public void visit(GreaterNode greaterNode) {
        Integer param1, param2;

        greaterNode.universalAccept(this);
        if (checkForStopping(mInterpretorTree)) {
            return;
        }

        param1 = getParameter(greaterNode, 0);
        param2 = getParameter(greaterNode, 1);

        if ((param1 == 1) || (param2 == null)) {
            mInterpretorTree.setResult(InterpretorTree.CHECK_FAILED);
            return;
        }
        
        greaterNode.setResult(param1 > param2);
    }

    @Override
    public void visit(IfNode ifNode) {
        ifNode.getChildren().get(0).accept(this);
        if (checkForStopping(mInterpretorTree)) {
            return;
        }

        if (((Boolean)ifNode.getChildren().get(0).getResult())) {
            ifNode.getChildren().get(1).accept(this);
        } else {
            ifNode.getChildren().get(2).accept(this);
        }
    }

    @Override
    public void visit(ForNode forNode) {
        Boolean stopCondition;

        forNode.getChildren().get(0).accept(this);
        forNode.getChildren().get(1).accept(this);
        stopCondition = (Boolean)forNode.getChildren().get(1).getResult();

        if (checkForStopping(mInterpretorTree)) {
            return;
        }

        while (stopCondition) {
            forNode.getChildren().get(3).accept(this);
            if (checkForStopping(mInterpretorTree)) {
                return;
            }
            
            forNode.getChildren().get(2).accept(this);
            if (checkForStopping(mInterpretorTree)) {
                return;
            }
            
            forNode.getChildren().get(1).accept(this);
            if (checkForStopping(mInterpretorTree)) {
                return;
            }
            
            stopCondition = (Boolean)forNode.getChildren().get(1).getResult();
            if (checkForStopping(mInterpretorTree)) {
                return;
            }
        }
    }

    @Override
    public void visit(LessOrEqualNode lessOrEqualNode) {
        Integer param1, param2;

        lessOrEqualNode.universalAccept(this);
        if (checkForStopping(mInterpretorTree)) {
            return;
        }

        param1 = getParameter(lessOrEqualNode, 0);
        param2 = getParameter(lessOrEqualNode, 1);

        if ((param1 == null) || (param2 == null)) {
            mInterpretorTree.setResult(InterpretorTree.CHECK_FAILED);
            return;
        }

        lessOrEqualNode.setResult(param1 < param2);
    }

    @Override
    public void visit(LessNode lessNode) {
        Integer param1, param2;

        lessNode.universalAccept(this);
        if (checkForStopping(mInterpretorTree)) {
            return;
        }

        param1 = getParameter(lessNode, 0);
        param2 = getParameter(lessNode, 1);

        if ((param1 == null) || (param2 == null)) {
            mInterpretorTree.setResult(InterpretorTree.CHECK_FAILED);
            return;
        }

        lessNode.setResult(param1 < param2);
    }

    @Override
    public void visit(MinusNode minusNode) {
        Integer param1, param2;

        minusNode.universalAccept(this);
        if (checkForStopping(mInterpretorTree)) {
            return;
        }

        param1 = getParameter(minusNode, 0);
        param2 = getParameter(minusNode, 1);

        if ((param1 == null) || (param2 == null)) {
            mInterpretorTree.setResult(InterpretorTree.CHECK_FAILED);
            return;
        }

        minusNode.setResult(param1 - param2);
    }

    @Override
    public void visit(MultiplyNode multiplyNode) {
        Integer param1, param2;

        multiplyNode.universalAccept(this);
        if (checkForStopping(mInterpretorTree)) {
            return;
        }

        param1 = getParameter(multiplyNode, 0);
        param2 = getParameter(multiplyNode, 1);
        if ((param1 == null) || (param2 == null)) {
            mInterpretorTree.setResult(InterpretorTree.CHECK_FAILED);
            return;
        }

        multiplyNode.setResult(param1 * param2);
    }

    @Override
    public void visit(PlusNode plusNode) {
        Integer param1, param2;

        plusNode.universalAccept(this);
        if (checkForStopping(mInterpretorTree)) {
            return;
        }

        param1 = getParameter(plusNode, 0);
        param2 = getParameter(plusNode, 1);
        if ((param1 == null) || (param2 == null)) {
            mInterpretorTree.setResult(InterpretorTree.CHECK_FAILED);
            return;
        }

        plusNode.setResult(param1 + param2);
    }

    @Override
    public void visit(ReturnNode returnNode) {
        returnNode.universalAccept(this);
        if (checkForStopping(mInterpretorTree)) {
            return;
        }
        mInterpretorTree.setResult(returnNode.getChildren().get(0).getResult());
    }
    
    public boolean hasReturn() {
        TreeNode treeNode = getInterpretorTree().getRoot();
        TreeNode parent;

        for ( ; treeNode.getChildren().size() > 0; treeNode = treeNode.getChildren().get(treeNode.getChildren().size() - 1));
        for (parent = treeNode; parent != null && !(parent instanceof ReturnNode); parent = parent.getParent());

        if (parent == null) {
            return false;
        }

        return true;
    }
}