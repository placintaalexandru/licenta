import java.io.IOException;
import java.util.Map;

public class Singleton {

	/**
	 * Permit instantierea doar a unui singur obiect de tip Serializer,
	 * repsectiv Deserializer, deoarece crearea mai multor obiecte ar fi
	 * inutile, deoarece ele implicit fac acelasi lucru, serializeaza, respectiv
	 * deserializeaza un graf
	 */
	private static Serializer mSerializer = null;
	private static Deserializer mDeserializer = null;

	public static Serializer getSerializerInstance(String outputFileName) throws IOException {
		if (mSerializer == null) {
			mSerializer = new Serializer(outputFileName);
		} else {
			mSerializer.setNewStreams(outputFileName);
		}

		return mSerializer;
	}

	public static Deserializer getDeserializerInstance(String inputFileName, Map<String, Integer> map)
			throws IOException {
		if (mDeserializer == null) {
			mDeserializer = new Deserializer(inputFileName, map);
		} else {
			mDeserializer.setNewStreams(inputFileName, map);
		}

		return mDeserializer;
	}
}
