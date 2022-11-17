/**
 * Created by ALEX on 3/14/2017.
 */
public class ForNode extends TreeNode {

    public ForNode(TreeNode parent) {
        this.setParent(parent);
    }

    @Override
    public void accept(Visitor visitor) {
        visitor.visit(this);
    }
}