package com.acoezard.avaj_launcher.aircrafts;

import com.acoezard.avaj_launcher.WeatherTower;

public interface Flyable {
    public void updateConditions();
    public void registerTower(WeatherTower weatherTower);
}