package com.acoezard.avaj_launcher.aircrafts;

import java.util.HashMap;

import com.acoezard.avaj_launcher.WeatherProvider;
import com.acoezard.avaj_launcher.WeatherTower;
import com.acoezard.avaj_launcher.utils.Coordinates;
import com.acoezard.avaj_launcher.utils.Logger;

public class Baloon extends Aircraft implements Flyable {
    private WeatherTower weatherTower;

    private final HashMap<String, String> messages = new HashMap<>() {{
        put(WeatherProvider.WEATHER_SUN, "Let's enjoy the good weather and take some pics.");
        put(WeatherProvider.WEATHER_RAIN, "Damn you rain! You messed up my baloon.");
        put(WeatherProvider.WEATHER_FOG, "Smoke on the water, fire in the sky!");
        put(WeatherProvider.WEATHER_SNOW, " It's snowing. We're gonna crash.");
    }};

    public Baloon(String name, Coordinates coordinates) {
        super(name, coordinates);
    }

    public void updateConditions() {
        String weather = weatherTower.getWeather(coordinates);
        switch(weather) {
            case WeatherProvider.WEATHER_SUN:
                this.coordinates.increaseLongitude(2);
                this.coordinates.increaseHeight(4);
                break;
            case WeatherProvider.WEATHER_RAIN:
                this.coordinates.decreaseHeight(5);
                break;
            case WeatherProvider.WEATHER_FOG:
                this.coordinates.decreaseHeight(3);
                break;
            case WeatherProvider.WEATHER_SNOW:
                this.coordinates.decreaseHeight(15);
                break;
        }
        Logger.log(this + ": " + this.messages.get(weather));
        if (this.coordinates.getHeight() == 0) {
            Logger.log(this + " is landing at " + this.coordinates);
            this.weatherTower.unregister(this);
        }
    }

    public void registerTower(WeatherTower weatherTower) {
        this.weatherTower = weatherTower;
        this.weatherTower.register(this);
    }

    @Override
    public String toString() {
        return "Baloon#" + name + "(" + id + ")";
    }
}