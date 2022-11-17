import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.List;

public class MyWriter {

	/**
	 * Aceasta metoda scrie intr-un fisier toate valorile obiectelor din lista
	 * de rezultate, dupa ce a fost creata lista la citire
	 */
	public void write(List<Object> list, String fileOutPutName) throws IOException {
		FileOutputStream fos = new FileOutputStream(fileOutPutName);
		OutputStreamWriter osw = new OutputStreamWriter(fos);
		BufferedWriter bw = new BufferedWriter(osw);

		for (Object object : list) {
			bw.write(object.toString());
			bw.newLine();
		}

		bw.close();
		osw.close();
		fos.close();
	}
}
