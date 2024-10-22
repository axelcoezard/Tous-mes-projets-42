package com.acoezard.avaj_launcher.aircrafts;

import com.acoezard.avaj_launcher.utils.Coordinates;

public class Aircraft {
    protected long id;
    protected String name;
    protected Coordinates coordinates;

    private static long idCounter;

    protected Aircraft(String name, Coordinates coordinates) {
        this.id = this.nextId();
        this.name = name;
        this.coordinates = coordinates;
    }

    private long nextId() {
        return ++Aircraft.idCounter;
    }

    public long getId() {
        return this.id;
    }

    public String getName() {
        return this.name;
    }

    public Coordinates getCoordinates() {
        return this.coordinates;
    }
}