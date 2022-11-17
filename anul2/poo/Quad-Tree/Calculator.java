
public class Calculator {

	/**
	 * Aceasta metoda calculeaza aria unui triunghi determinat de cele 3 puncte
	 * primite ca parametru Formula data la valoarea de return reprezinta forma
	 * determinantului Aceasta functie o folosesc pentru a verifica daca un
	 * punct este in interiorul unui triunghi sau romb
	 * 
	 * @param p1
	 *            primul varf al triunghiului
	 * @param p2
	 *            al 2 lea varf al triunghiului
	 * @param p3
	 *            al 3 lea varf al triunghiului
	 * @return double valorea determinantului, care in modul reprezinta de 2 ori
	 *         aria triunghiului
	 */
    public static double determinant(Point p1, Point p2, Point p3)
    {
        double x1, x2, x3;
        double y1, y2, y3;

        x1 = p1.getmX();
        y1 = p1.getmY();
        x2 = p2.getmX();
        y2 = p2.getmY();
        x3 = p3.getmX();
        y3 = p3.getmY();

        return  ( x1 * y2 + x2 * y3 + x3 * y1 -
                  x3 * y2 - x1 * y3 - x2 * y1 );
    }
}