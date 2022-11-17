
public class Main {

    public static void main(String[] args) {
	// write your code here

        ReaderAndWriter readerAndWriter = new ReaderAndWriter(args[0], args[1]);
        readerAndWriter.writeResult();
        readerAndWriter.close();
    }
}