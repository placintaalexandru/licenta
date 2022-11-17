
/**
 * Created by ALEX on 3/14/2017.
 */
public class VariableNode extends TreeNode{

    public VariableNode(String variableName, TreeNode parent) {
        this.setParameter1(variableName);
        this.setParent(parent);
    }

    @Override
    public void accept(Visitor visitor) {
        visitor.visit(this);
    }
}