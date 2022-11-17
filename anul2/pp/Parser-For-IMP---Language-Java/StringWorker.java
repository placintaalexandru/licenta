/**
 * Created by ALEX on 3/14/2017.
 */
public class StringWorker {

    private String mProgram;

    public StringWorker(String program) {
        this.mProgram = program;
    }

    public String getProgram() {
        return mProgram;
    }

    public String getNodeTypeFrom(int index) {
        String nodeType = "";

        for (int i = index; mProgram.charAt(i) != ' ' && mProgram.charAt(i) != ']'; i++) {
            nodeType += mProgram.charAt(i);
        }

        return nodeType;
    }
}