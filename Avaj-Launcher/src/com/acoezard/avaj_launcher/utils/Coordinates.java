package com.acoezard.avaj_launcher.utils;


public class Coordinates {
    private int longitude;
    private int latitude;
    private int height;

    public Coordinates(int longitude, int latitude, int height) {
        this.longitude = longitude;
        this.latitude = latitude;
        this.height = Math.max(0, Math.min(height, 100));
    }

    public void increaseLongitude(int n) {
        this.longitude += n;
    }

    public void increaseLatitude(int n) {
        this.latitude += n;
    }

    public void increaseHeight(int n) {
        this.height = Math.min(100, this.height + n);
    }

    public void decreaseHeight(int n) {
        this.height = Math.max(0, this.height - n);
    }

    public int getLongitude() {
        return this.longitude;
    }

    public int getLatitude() {
        return this.latitude;
    }

    public int getHeight() {
        return this.height;
    }

    @Override
    public String toString() {
        return this.longitude + "," + this.latitude + "," + this.height;
    }
}
