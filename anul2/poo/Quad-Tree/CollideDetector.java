
import java.util.List;

public class CollideDetector {

	/**
	 * Aceasta metoda cauta in quadtree toate coliziunile cu punctul primit ca
	 * parametru Functia verifica daca celula curenta este frunza, caut in lista
	 * de figuri geoemtrice si verifica daca figurile contin punctul, caz in
	 * care adaug ID-urile in lista La finalul acestei operatii ma opresc Daca
	 * celula nu este frunza apelez functia recursiv pentru fiecare din fii
	 * celulei care contin punctul, geometric verifica doar subplanul in care se
	 * afla punctul
	 * 
	 * @param quadTreeCell
	 *            celula curenta, in program va avea si rol de celula de inceput
	 * @param p
	 *            punctul pentru care se cauta toate figurile care il contin
	 * @param list
	 *            lista in care se adauga ID-urile care contin punctul
	 * @return void
	 */
	public static void collisionsWithPoint(QuadTreeCell quadTreeCell, Point p, List<Integer> list) {
		
		if (quadTreeCell.getmSubPlans().isEmpty()) {
			for (GeometricObject geometricObject : quadTreeCell.getmFigures()) {
				if ((geometricObject.contains(p)) && (!list.contains(geometricObject.getmID()))) {
					list.add(geometricObject.getmID());
				}
			}

			return;
		} else {
			for (QuadTreeCell cell : quadTreeCell.getmSubPlans()) {
				if (cell.getCharacteristicSquare().contains(p)) {
					collisionsWithPoint(cell, p, list);
				}
			}
		}
	}

	/**
	 * Aceasta metoda cauta in quadtree toate coliziunile cu figura geoemtrica
	 * primita ca parametru Functia verifica daca celula curenta este frunza,
	 * caz in care caut prin lista de figuri si verific daca se intersecteaza cu
	 * ceva din lista, caz in care aduaug ID-ul in lista La finalul acestei
	 * operatii ma opresc Daca celula nu este frunza, parcurg lista de fii si
	 * vad daca figura mea atinge patratul caracteristic al fiecarui fiu in
	 * parte, caz in care caut si in acel fiu
	 * 
	 * @param quadTreeCell
	 *            celula curenta din arbore, in program va avea si rol de celula
	 *            de inceput
	 * @param geometricObject
	 *            obiectul geoemtric pentru care se cauta toata figurile care il
	 *            intersecteaza
	 * @param list
	 *            lista in care se adauga ID-urile figurilor care intersecteaza
	 *            obiectul geoemtric
	 */
	public static void collisionsWithObject(QuadTreeCell quadTreeCell, GeometricObject geometricObject,
											List<Integer> list) {
		
		if (quadTreeCell.getmSubPlans().isEmpty()) {
			for (GeometricObject geometricObject1 : quadTreeCell.getmFigures()) {
				if ((geometricObject.collidesWith(geometricObject1)) && ((!list.contains(geometricObject1.getmID())))) {
					list.add(geometricObject1.getmID());
				}
			}

			return;
		}

		for (QuadTreeCell cell : quadTreeCell.getmSubPlans()) {
			if (geometricObject.fitsInSubPlanOf(cell)) {
				collisionsWithObject(cell, geometricObject, list);
			}
		}
	}
}