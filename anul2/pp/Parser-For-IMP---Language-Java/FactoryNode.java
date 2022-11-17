import java.util.Map;

/**
 * Created by ALEX on 3/14/2017.
 */
public class FactoryNode {

    public static TreeNode createNode(String indicator, Map<String, Integer> variableMap, TreeNode parent) {
        switch (indicator) {
            case "+":
                return new PlusNode(parent);

            case  "-":
                return new MinusNode(parent);

            case "*":
                return new MultiplyNode(parent);

            case "/":
                return new DivisionNode(parent);

            case "=":
                return new AsignmentNode(variableMap, parent);

            case "==":
                return new EqualNode(parent);

            case "<":
                return new LessNode(parent);

            case "<=":
                return new LessOrEqualNode(parent);

            case ">":
                return new GreaterNode(parent);

            case ">=":
                return new GreaterOrEqualNode(parent);

            case "if":
                return new IfNode(parent);

            case "for":
                return new ForNode(parent);

            case "assert":
                return new AssertNode(parent);

            case "return":
                return new ReturnNode(parent);

            case ";":
                return new ProgramNode(parent);
        }

        if (Character.isDigit(indicator.charAt(0))) {
            return new IntegerNode(Integer.parseInt(indicator), parent);
        } else if (Character.isLetter(indicator.charAt(0))) {
            return new VariableNode(indicator, parent);
        } else if ((indicator.length() > 1) && (indicator.charAt(0) == '-')) {
            return new IntegerNode(Integer.parseInt(indicator), parent);
        }

        return null;
    }
}