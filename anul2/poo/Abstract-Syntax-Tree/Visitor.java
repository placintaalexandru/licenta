public interface Visitor {

	void visit(PlusNode plusNode);

	void visit(MinusNode minusNode);

	void visit(MultiplyNode multiplyNode);

	void visit(DivisionNode divisionNode);

	void visit(IntegerNode integerNode);

	void visit(DoubleNode doubleNode);

	void visit(StringNode stringNode);
}