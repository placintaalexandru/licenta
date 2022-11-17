/**
 * Created by ALEX on 3/14/2017.
 */
public class MultiplyNode extends TreeNode {

    public MultiplyNode(TreeNode parent) {
        this.setParent(parent);
    }

    @Override
    public void accept(Visitor visitor) {
        visitor.visit(this);
    }
}