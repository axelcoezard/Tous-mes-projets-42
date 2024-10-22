package com.acoezard.avaj_launcher.utils;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class Logger {
    private static BufferedWriter bufferedWriter;

    public Logger(String filename) throws IOException {
        File file = new File(filename);
        file.delete();
        if (bufferedWriter == null) {
            bufferedWriter = new BufferedWriter(new FileWriter(file, true));
        }
    }

    public static void log(String log) {
        try {
            if (bufferedWriter != null) {
                bufferedWriter.write(log);
                bufferedWriter.newLine();
                bufferedWriter.flush();
            }
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
    
    public static void close() throws IOException {
        if (bufferedWriter == null) {
            throw new IOException("No logger instance");
        }
        bufferedWriter.close();
        bufferedWriter = null;
    }
}
