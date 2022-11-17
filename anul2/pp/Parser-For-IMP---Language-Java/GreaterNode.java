/**
 * Created by ALEX on 3/14/2017.
 */
public class GreaterNode extends TreeNode {

    public GreaterNode(TreeNode parent) {
        this.setParent(parent);
    }

    @Override
    public void accept(Visitor visitor) {
        visitor.visit(this);
    }
}