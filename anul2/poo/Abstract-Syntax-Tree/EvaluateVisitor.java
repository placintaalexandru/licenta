
/**
 * Aceasta clasa implementeaza interfata Visitor si are rol de a visita fiecare
 * nod din arbore si de a efectua operatia specfica fiecarui tip de nod in parte
 * Acest Visitor parcurge un arbore recursiv si pune rezultatul in radcina
 */
public class EvaluateVisitor implements Visitor {

	/**
	 * Evalueaza adunarea dintre 2 obiecte, depinzand de tipul acestora
	 */
	private Object evaluateAddition(Object o1, Object o2) {
		Object result = null;

		if (o1 instanceof Integer) {
			if (o2 instanceof Integer) {
				result = Calculator.add((Integer) o1, (Integer) o2);
			} else if (o2 instanceof Double) {
				result = Calculator.add((Integer) o1, (Double) o2);
			} else if (o2 instanceof String) {
				result = Calculator.add((Integer) o1, (String) o2);
			}
		} else if (o1 instanceof Double) {
			if (o2 instanceof Integer) {
				result = Calculator.add((Double) o1, (Integer) o2);
			} else if (o2 instanceof Double) {
				result = Calculator.add((Double) o1, (Double) o2);
			} else if (o2 instanceof String) {
				result = Calculator.add((Double) o1, (String) o2);
			}
		} else if (o1 instanceof String) {
			if (o2 instanceof Integer) {
				result = Calculator.add((String) o1, (Integer) o2);
			} else if (o2 instanceof Double) {
				result = Calculator.add((String) o1, (Double) o2);
			} else if (o2 instanceof String) {
				result = Calculator.add((String) o1, (String) o2);
			}
		}

		return result;
	}

	/**
	 * Evalueaza scaderea dintre 2 obiecte, depinzand de tipul acestora
	 */
	private Object evaluateSubstraction(Object o1, Object o2) {
		Object result = null;

		if (o1 instanceof Integer) {
			if (o2 instanceof Integer) {
				result = Calculator.sub((Integer) o1, (Integer) o2);
			} else if (o2 instanceof Double) {
				result = Calculator.sub((Integer) o1, (Double) o2);
			} else if (o2 instanceof String) {
				result = Calculator.sub((Integer) o1, (String) o2);
			}
		} else if (o1 instanceof Double) {
			if (o2 instanceof Integer) {
				result = Calculator.sub((Double) o1, (Integer) o2);
			} else if (o2 instanceof Double) {
				result = Calculator.sub((Double) o1, (Double) o2);
			} else if (o2 instanceof String) {
				result = Calculator.sub((Double) o1, (String) o2);
			}
		} else if (o1 instanceof String) {
			if (o2 instanceof Integer) {
				result = Calculator.sub((String) o1, (Integer) o2);
			} else if (o2 instanceof Double) {
				result = Calculator.sub((String) o1, (Double) o2);
			} else if (o2 instanceof String) {
				result = Calculator.sub((String) o1, (String) o2);
			}
		}

		return result;
	}

	/**
	 * Evalueaza inmultirea dintre 2 obiecte, depinzand de tipul acestora
	 */
	private Object evaluateMultiplication(Object o1, Object o2) {
		Object result = null;

		if (o1 instanceof Integer) {
			if (o2 instanceof Integer) {
				result = Calculator.multiply((Integer) o1, (Integer) o2);
			} else if (o2 instanceof Double) {
				result = Calculator.multiply((Integer) o1, (Double) o2);
			} else if (o2 instanceof String) {
				result = Calculator.multiply((Integer) o1, (String) o2);
			}
		} else if (o1 instanceof Double) {
			if (o2 instanceof Integer) {
				result = Calculator.multiply((Double) o1, (Integer) o2);
			} else if (o2 instanceof Double) {
				result = Calculator.multiply((Double) o1, (Double) o2);
			} else if (o2 instanceof String) {
				result = Calculator.multiply((Double) o1, (String) o2);
			}
		} else if (o1 instanceof String) {
			if (o2 instanceof Integer) {
				result = Calculator.multiply((String) o1, (Integer) o2);
			} else if (o2 instanceof Double) {
				result = Calculator.multiply((String) o1, (Double) o2);
			} else if (o2 instanceof String) {
				result = Calculator.multiply((String) o1, (String) o2);
			}
		}

		return result;
	}

	/**
	 * Evalueaza impartirea dintre 2 obiecte, depinzand de tipul acestora
	 */
	private Object evaluateDivision(Object o1, Object o2) {
		Object result = null;

		if (o1 instanceof Integer) {
			if (o2 instanceof Integer) {
				result = Calculator.divide((Integer) o1, (Integer) o2);
			} else if (o2 instanceof Double) {
				result = Calculator.divide((Integer) o1, (Double) o2);
			} else if (o2 instanceof String) {
				result = Calculator.divide((Integer) o1, (String) o2);
			}
		} else if (o1 instanceof Double) {
			if (o2 instanceof Integer) {
				result = Calculator.divide((Double) o1, (Integer) o2);
			} else if (o2 instanceof Double) {
				result = Calculator.divide((Double) o1, (Double) o2);
			} else if (o2 instanceof String) {
				result = Calculator.divide((Double) o1, (String) o2);
			}
		} else if (o1 instanceof String) {
			if (o2 instanceof Integer) {
				result = Calculator.divide((String) o1, (Integer) o2);
			} else if (o2 instanceof Double) {
				result = Calculator.divide((String) o1, (Double) o2);
			} else if (o2 instanceof String) {
				result = Calculator.divide((String) o1, (String) o2);
			}
		}

		return result;
	}

	/**
	 * Aceasta metoda viziteaza un nod ce contine ca informatie un Integer, iar
	 * apoi se analizeaza daca nodul are parinte, iar daca are se verifica ce
	 * fel de fiu e, stang sau drept, dupa care se seteaza operandul din
	 * parinte, operand 1 daca e fiu stang sau operand 2 daca e fiu drept
	 *
	 */
	@Override
	public void visit(IntegerNode integerNode) {
		if (integerNode.getParent() != null) {
			if (integerNode.getParent().getLeft() == integerNode) {
				integerNode.getParent().setOperand1(integerNode.getValue());
			} else if (integerNode.getParent().getRight() == integerNode) {
				integerNode.getParent().setOperand2(integerNode.getValue());
			}
		}
	}

	/**
	 * Aceasta metoda viziteaza un nod ce contine operatia de adunare in felul
	 * urmator: se viziteaza copii, acest lucru avand rolul de a oferi cei 2
	 * parametri reprezentati de campurile operand(1 si 2), dupa care se
	 * evalueaza adunarea, avand ca parametrii cei 2 operanzi, iar aopi se
	 * verifica daca nodul curent are parinte, caz in care se determina ce fel
	 * de fiu este nodul curent si se seteaza valoraea operandului din parinte
	 */
	@Override
	public void visit(PlusNode plusNode) {
		plusNode.getLeft().accept(this);
		plusNode.getRight().accept(this);

		plusNode.setResult(evaluateAddition(plusNode.getOperand1(), plusNode.getOperand2()));

		if (plusNode.getParent() != null) {
			if (plusNode.getParent().getLeft() == plusNode) {
				plusNode.getParent().setOperand1(plusNode.getResult());
			} else if (plusNode.getParent().getRight() == plusNode) {
				plusNode.getParent().setOperand2(plusNode.getResult());
			}
		}
	}

	/**
	 * Aceasta metoda viziteaza un nod ce contine operatia de scadere in felul
	 * urmator: se viziteaza copii, acest lucru avand rolul de a oferi cei 2
	 * parametri reprezentati de campurile operand(1 si 2), dupa care se
	 * evalueaza scaderea, avand ca parametrii cei 2 operanzi, iar aopi se
	 * verifica daca nodul curent are parinte, caz in care se determina ce fel
	 * de fiu este nodul curent si se seteaza valoraea operandului din parinte
	 */
	@Override
	public void visit(MinusNode minusNode) {
		minusNode.getLeft().accept(this);
		minusNode.getRight().accept(this);

		minusNode.setResult(evaluateSubstraction(minusNode.getOperand1(), minusNode.getOperand2()));

		if (minusNode.getParent() != null) {
			if (minusNode.getParent().getLeft() == minusNode) {
				minusNode.getParent().setOperand1(minusNode.getResult());
			} else if (minusNode.getParent().getRight() == minusNode) {
				minusNode.getParent().setOperand2(minusNode.getResult());
			}
		}
	}

	/**
	 * Aceasta metoda viziteaza un nod ce contine operatia de inmultire in felul
	 * urmator: se viziteaza copii, acest lucru avand rolul de a oferi cei 2
	 * parametri reprezentati de campurile operand(1 si 2), dupa care se
	 * evalueaza inmultirea, avand ca parametrii cei 2 operanzi, iar aopi se
	 * verifica daca nodul curent are parinte, caz in care se determina ce fel
	 * de fiu este nodul curent si se seteaza valoraea operandului din parinte
	 */
	@Override
	public void visit(MultiplyNode multiplyNode) {
		multiplyNode.getLeft().accept(this);
		multiplyNode.getRight().accept(this);

		multiplyNode.setResult(evaluateMultiplication(multiplyNode.getOperand1(), multiplyNode.getOperand2()));

		if (multiplyNode.getParent() != null) {
			if (multiplyNode.getParent().getLeft() == multiplyNode) {
				multiplyNode.getParent().setOperand1(multiplyNode.getResult());
			} else if (multiplyNode.getParent().getRight() == multiplyNode) {
				multiplyNode.getParent().setOperand2(multiplyNode.getResult());
			}
		}
	}

	/**
	 * Aceasta metoda viziteaza un nod ce contine operatia de impartire in felul
	 * urmator: se viziteaza copii, acest lucru avand rolul de a oferi cei 2
	 * parametri reprezentati de campurile operand(1 si 2), dupa care se
	 * evalueaza inmultirea, avand ca parametrii cei 2 operanzi, iar aopi se
	 * verifica daca nodul curent are parinte, caz in care se determina ce fel
	 * de fiu este nodul curent si se seteaza valoraea operandului din parinte
	 */
	@Override
	public void visit(DivisionNode divisionNode) {
		divisionNode.getLeft().accept(this);
		divisionNode.getRight().accept(this);

		divisionNode.setResult(evaluateDivision(divisionNode.getOperand1(), divisionNode.getOperand2()));

		if (divisionNode.getParent() != null) {
			if (divisionNode.getParent().getLeft() == divisionNode) {
				divisionNode.getParent().setOperand1(divisionNode.getResult());
			} else if (divisionNode.getParent().getRight() == divisionNode) {
				divisionNode.getParent().setOperand2(divisionNode.getResult());
			}
		}
	}

	/**
	 * Aceasta metoda viziteaza un nod ce contine ca informatie un Double, iar
	 * apoi se analizeaza daca nodul are parinte, iar daca are se verifica ce
	 * fel de fiu e, stang sau drept, dupa care se seteaza operandul din
	 * parinte, operand 1 daca e fiu stang sau operand 2 daca e fiu drept
	 *
	 */
	@Override
	public void visit(DoubleNode doubleNode) {
		if (doubleNode.getParent() != null) {
			if (doubleNode.getParent().getLeft() == doubleNode) {
				doubleNode.getParent().setOperand1(doubleNode.getValue());
			} else if (doubleNode.getParent().getRight() == doubleNode) {
				doubleNode.getParent().setOperand2(doubleNode.getValue());
			}
		}
	}

	/**
	 * Aceasta metoda viziteaza un nod ce contine ca informatie un String, iar
	 * apoi se analizeaza daca nodul are parinte, iar daca are se verifica ce
	 * fel de fiu e, stang sau drept, dupa care se seteaza operandul din
	 * parinte, operand 1 daca e fiu stang sau operand 2 daca e fiu drept
	 *
	 */
	@Override
	public void visit(StringNode stringNode) {
		if (stringNode.getParent() != null) {
			if (stringNode.getParent().getLeft() == stringNode) {
				stringNode.getParent().setOperand1(stringNode.getValue());
			} else if (stringNode.getParent().getRight() == stringNode) {
				stringNode.getParent().setOperand2(stringNode.getValue());
			}
		}
	}
}