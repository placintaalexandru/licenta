
/**
 * aceasta clasa contine implementarea celor 4: adunare, scadere, inmultire,
 * impartire pe toate cele 3 tipuri de date: int, double, string
 */
public class Calculator {

	public static Integer add(Integer integer1, Integer integer2) {
		if ((integer1 == Integer.MAX_VALUE) || (integer2 == Integer.MAX_VALUE)) {
			return Integer.MAX_VALUE;
		}

		return integer1 + integer2;
	}

	public static Double add(Integer integer, Double duble) {
		if ((integer == Integer.MAX_VALUE) || (duble == Double.MAX_VALUE)) {
			return Double.MAX_VALUE;
		}

		return new Double(integer + duble);
	}

	public static String add(Integer integer, String string) {
		if (integer == Integer.MAX_VALUE) {
			return "NaN" + string;
		}

		return integer.toString() + string;
	}

	public static Double add(Double duble, Integer integer) {
		return add(integer, duble);
	}

	public static Double add(Double duble1, Double duble2) {
		if ((duble1 == Double.MAX_VALUE) || (duble2 == Double.MAX_VALUE)) {
			return Double.MAX_VALUE;
		}

		return new Double(duble1 + duble2);
	}

	public static String add(Double duble, String string) {
		if (duble == Double.MAX_VALUE) {
			return "NaN" + string;
		}

		return Calculator.twoZecimalRound(duble).toString() + string;
	}

	public static String add(String string, Integer integer) {
		if (integer == Integer.MAX_VALUE) {
			return string + "NaN";
		}

		return string + integer.toString();
	}

	public static String add(String string, Double duble) {
		if (duble == Double.MAX_VALUE) {
			return string + "NaN";
		}

		return string + Calculator.twoZecimalRound(duble).toString();
	}

	public static String add(String string1, String string2) {
		return string1 + string2;
	}

	public static Integer sub(Integer integer1, Integer integer2) {
		if ((integer1 == Integer.MAX_VALUE) || (integer2 == Integer.MAX_VALUE)) {
			return Integer.MAX_VALUE;
		}

		return integer1 - integer2;
	}

	public static Double sub(Integer integer, Double duble) {
		if ((integer == Integer.MAX_VALUE) || (duble == Double.MAX_VALUE)) {
			return Double.MAX_VALUE;
		}

		return new Double(integer - duble);
	}

	public static Integer sub(Integer integer, String string) {
		if (integer == Integer.MAX_VALUE) {
			return Integer.MAX_VALUE;
		}

		return integer - string.length();
	}

	public static Double sub(Double duble, Integer integer) {
		if ((integer == Integer.MAX_VALUE) || (duble == Double.MAX_VALUE)) {
			return Double.MAX_VALUE;
		}

		return new Double(duble - integer);
	}

	public static Double sub(Double duble1, Double duble2) {
		if ((duble1 == Double.MAX_VALUE) || (duble2 == Double.MAX_VALUE)) {
			return Double.MAX_VALUE;
		}

		return new Double(duble1 - duble2);
	}

	public static Double sub(Double duble, String string) {
		if (duble == Double.MAX_VALUE) {
			return Double.MAX_VALUE;
		}

		return new Double(duble - string.length());
	}

	public static String sub(String string, Integer integer) {
		if ((integer > string.length()) && (integer != Integer.MAX_VALUE)) {
			return "";
		} else if (integer < 0) {
			for (int i = integer; i < 0; i++) {
				string += "#";
			}

			return string;
		} else if (integer == Integer.MAX_VALUE) {
			return string;
		}

		return string.substring(0, string.length() - integer);
	}

	public static Double sub(String string, Double duble) {
		if (duble == Double.MAX_VALUE) {
			return Double.MAX_VALUE;
		}

		return new Double(string.length() - duble);
	}

	public static Integer sub(String string1, String string2) {
		return new Integer(string1.length() - string2.length());
	}

	public static Integer multiply(Integer integer1, Integer integer2) {
		if ((integer1 == Integer.MAX_VALUE) || (integer2 == Integer.MAX_VALUE)) {
			return Integer.MAX_VALUE;
		}

		return integer1 * integer2;
	}

	public static Double multiply(Integer integer, Double duble) {
		if ((integer == Integer.MAX_VALUE) || (duble == Double.MAX_VALUE)) {
			return Double.MAX_VALUE;
		}

		return new Double(integer * duble);
	}

	public static String multiply(Integer integer, String string) {
		String result = "";

		if ((integer <= 0) || (integer == Integer.MAX_VALUE)) {
			return result;
		}

		for (int i = 0; i < integer; i++) {
			result += string;
		}

		return result;
	}

	public static Double multiply(Double duble, Integer integer) {
		if ((duble == Double.MAX_VALUE) || (integer == Integer.MAX_VALUE)) {
			return Double.MAX_VALUE;
		}

		return new Double(duble * integer);
	}

	public static Double multiply(Double duble1, Double duble2) {
		if ((duble1 == Double.MAX_VALUE) || (duble2 == Double.MAX_VALUE)) {
			return Double.MAX_VALUE;
		}

		return new Double(duble1 * duble2);
	}

	public static Double multiply(Double duble, String string) {
		if (duble == Double.MAX_VALUE) {
			return Double.MAX_VALUE;
		}

		return new Double(duble * string.length());
	}

	public static String multiply(String string, Integer integer) {
		return multiply(integer, string);
	}

	public static Double multiply(String string, Double duble) {
		return multiply(duble, string);
	}

	public static Integer multiply(String string1, String string2) {
		return new Integer(string1.length() * string2.length());
	}

	public static Integer divide(Integer integer1, Integer integer2) {
		if ((integer1 == Integer.MAX_VALUE) || (integer2 == Integer.MAX_VALUE) || (integer2 == 0)) {
			return Integer.MAX_VALUE;
		}

		return new Integer(integer1 / integer2);
	}

	public static Double divide(Integer integer, Double duble) {
		if ((integer == Integer.MAX_VALUE) || (duble == Double.MAX_VALUE) || (duble == 0)) {
			return Double.MAX_VALUE;
		}

		return new Double(integer / duble);
	}

	public static Integer divide(Integer integer, String string) {
		if ((integer == Integer.MAX_VALUE) || (string.length() == 0)) {
			return Integer.MAX_VALUE;
		}

		return new Integer(integer / string.length());
	}

	public static Double divide(Double duble, Integer integer) {
		if ((duble == Double.MAX_VALUE) || (integer == Integer.MAX_VALUE) || (integer == 0)) {
			return Double.MAX_VALUE;
		}

		return new Double(duble / integer);
	}

	public static Double divide(Double duble1, Double duble2) {
		if ((duble1 == Double.MAX_VALUE) || (duble2 == Double.MAX_VALUE) || (duble2 == 0)) {
			return Double.MAX_VALUE;
		}

		return new Double(duble1 / duble2);
	}

	public static Double divide(Double duble, String string) {
		if ((duble == Double.MAX_VALUE) || (string.length() == 0)) {
			return Double.MAX_VALUE;
		}

		return new Double(duble / string.length());
	}

	public static String divide(String string, Integer integer) {
		if ((integer <= 0) || (integer == Integer.MAX_VALUE)) {
			return string;
		}

		return string.substring(0, string.length() / integer);
	}

	public static Double divide(String string, Double duble) {
		if ((duble == Double.MAX_VALUE) || (duble == 0)) {
			return Double.MAX_VALUE;
		}

		return new Double(string.length() / duble);
	}

	public static Integer divide(String string1, String string2) {
		if (string2.length() == 0) {
			return Integer.MAX_VALUE;
		}

		return new Integer(string1.length() / string2.length());
	}

	public static Double twoZecimalRound(Double duble) {
		return new Double(Math.round(duble * 100)) / 100;
	}
}