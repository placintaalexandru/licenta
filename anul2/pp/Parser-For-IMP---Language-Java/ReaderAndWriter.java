import java.io.*;

/**
 * Created by ALEX on 3/15/2017.
 */
public class ReaderAndWriter {

    private BufferedReader mBufferedReader;
    private BufferedWriter mBufferedWriter;

    public ReaderAndWriter(String inputFile, String outputFile) {
        try {
            this.mBufferedReader = new BufferedReader(new InputStreamReader(new FileInputStream(inputFile)));
            this.mBufferedWriter = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outputFile)));
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
    }

    private String getProgramFromScratch() {
        String program = "";
        String line;
        String[] picesOfProgram;

        try {
            while ((line = mBufferedReader.readLine()) != null) {
            program += line;
            }
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }

        picesOfProgram = program.split("\t");
        program = "";

        for (String pieceOfProgram : picesOfProgram) {
            program += pieceOfProgram + " ";
        }

        return program;
    }

    public void writeResult() {
        InterpretorTree interpretorTree = new InterpretorTree(getProgramFromScratch());
        interpretorTree.evaluateProgram();

        try {
            mBufferedWriter.write(interpretorTree.getResult().toString());
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
    }

    public void close() {
        try {
            if (mBufferedWriter != null) {
                mBufferedWriter.close();
            }

            if (mBufferedWriter != null) {
                mBufferedWriter.close();
            }
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
    }
}