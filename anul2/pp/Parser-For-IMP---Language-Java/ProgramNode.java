/**
 * Created by ALEX on 3/14/2017.
 */
public class ProgramNode extends TreeNode {

    public ProgramNode(TreeNode parent) {
        this.setParent(parent);
    }

    @Override
    public void accept(Visitor visitor) {
        visitor.visit(this);
    }
}