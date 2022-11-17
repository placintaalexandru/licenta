/**
 * Created by ALEX on 3/14/2017.
 */
public class IntegerNode extends TreeNode {

    public IntegerNode(Integer integer, TreeNode parent) {
        this.setParent(parent);
        this.setParameter1(integer);
    }

    @Override
    public void accept(Visitor visitor) {
        visitor.visit(this);
    }
}