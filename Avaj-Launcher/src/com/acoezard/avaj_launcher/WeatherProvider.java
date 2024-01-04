package com.acoezard.avaj_launcher;

import com.acoezard.avaj_launcher.utils.Coordinates;

public class WeatherProvider {
    public static final String WEATHER_RAIN = "RAIN";
    public static final String WEATHER_FOG = "FOG";
    public static final String WEATHER_SUN = "SUN";
    public static final String WEATHER_SNOW = "SNOW";

    private static final WeatherProvider weatherProvider = new WeatherProvider();
    private static final String[] weather = new String[]{ WEATHER_RAIN, WEATHER_FOG, WEATHER_SUN, WEATHER_SNOW };

    private WeatherProvider() {}

    public static WeatherProvider getProvider() {
        return WeatherProvider.weatherProvider;
    }

    public String getCurrentWeather(Coordinates coordinates) {
        int sum = coordinates.getLongitude() + coordinates.getLatitude() + coordinates.getHeight();
        int mod = WeatherProvider.weather.length;
        return WeatherProvider.weather[sum % mod];
    }
}