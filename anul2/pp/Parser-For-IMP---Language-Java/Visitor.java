/**
 * Created by ALEX on 3/14/2017.
 */
public interface Visitor {

    void visit(AsignmentNode asignmentNode);
    void visit(AssertNode assertNode);
    void visit(DivisionNode divisionNode);
    void visit(EqualNode equalNode);
    void visit(GreaterOrEqualNode greaterOrEqualNode);
    void visit(GreaterNode greaterNode);
    void visit(IfNode ifNode);
    void visit(ForNode forNode);
    void visit(LessOrEqualNode lessOrEqualNode);
    void visit(LessNode lessNode);
    void visit(MinusNode minusNode);
    void visit(MultiplyNode multiplyNode);
    void visit(PlusNode plusNode);
    void visit(ReturnNode returnNode);
    void visit(ProgramNode programNode);
    void visit(IntegerNode integerNode);
    void visit(VariableNode variableNode);
}