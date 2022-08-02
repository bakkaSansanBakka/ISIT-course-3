package Utils;

import java.io.File;

public class FileChooser {
    public String files[];

    public FileChooser(String d) {
        File dir = new File(d);
        if (dir.exists()) {
            files = dir.list();
        }
    }
}
