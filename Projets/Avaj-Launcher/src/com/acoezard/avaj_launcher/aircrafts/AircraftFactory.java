package com.acoezard.avaj_launcher.aircrafts;

import com.acoezard.avaj_launcher.exceptions.SimulatorException;
import com.acoezard.avaj_launcher.utils.Coordinates;

public class AircraftFactory {

    public static final String TYPE_HELICOPTER = "Helicopter";
    public static final String TYPE_BALOON = "Baloon";
    public static final String TYPE_JETPLANE = "JetPlane";

    public static Flyable newAircraft(String type, String name, int longitude, int latitude, int height) throws SimulatorException {
        // Check coordinates
        if (longitude < 0 || latitude < 0 || height < 0) {
            throw new SimulatorException("Wrong aircraft coordinates");
        }
        // Create Coordinates object
        Coordinates coordinates = new Coordinates(longitude, latitude, height);
        // Check type and create Flyable object
        switch (type) {
            case TYPE_HELICOPTER: return new Helicopter(name, coordinates);
            case TYPE_BALOON: return new Baloon(name, coordinates);
            case TYPE_JETPLANE: return new JetPlane(name, coordinates);
            default: throw new SimulatorException("Wrong aircraft type: '" + type + "'");
        }
    }
}