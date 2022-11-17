import java.util.Map;

/**
 * Created by ALEX on 3/14/2017.
 */
public class AsignmentNode extends TreeNode {

    private Map<String, Integer> mVariableMap;

    public AsignmentNode(Map<String, Integer> variableMap, TreeNode parent) {
        this.mVariableMap = variableMap;
        this.setParent(parent);
    }

    public Object makeOperation() {
        String param1 = (String)getChildren().get(0).getResult();
        Integer param2 = (Integer)getChildren().get(1).getResult();
        mVariableMap.put(param1, param2);
        return true;
    }

    @Override
    public void accept(Visitor visitor) {
        visitor.visit(this);
    }
}