package com.acoezard.avaj_launcher.exceptions;

public class SimulatorException extends Exception {
    public SimulatorException(String message) {
        super(message);
    }

    public SimulatorException(String message, Throwable throwable) {
        super(message, throwable);
    }
}
