import java.util.ArrayList;
import java.util.List;

/**
 * Created by ALEX on 3/14/2017.
 */
public abstract class TreeNode implements Visitable {

    private Object mParameter1;
    private Object mParameter2;
    private List<TreeNode> mChildren;
    private TreeNode mParent;
    private Object mResult;

    public TreeNode() {
        this.mChildren = new ArrayList<>();
    }

    public Object getParameter1() {
        return mParameter1;
    }

    public Object getParameter2() {
        return mParameter2;
    }

    public TreeNode getParent() {
        return mParent;
    }

    public Object getResult() {
        return mResult;
    }

    public List<TreeNode> getChildren() {
        return mChildren;
    }

    public void setResult(Object result) {
        mResult = result;
    }

    public void setParameter1(Object parameter1) {
        mParameter1 = parameter1;
    }

    public void setParameter2(Object parameter2) {
        mParameter2 = parameter2;
    }

    public void setParent(TreeNode parent) {
        mParent = parent;
    }

    public void addChild(TreeNode treeNode) {
        mChildren.add(treeNode);
    }

    public void universalAccept(Visitor visitor) {
        for (TreeNode child : getChildren()) {
            child.accept(visitor);
        }
    }
}