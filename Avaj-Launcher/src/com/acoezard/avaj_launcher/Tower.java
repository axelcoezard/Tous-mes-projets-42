package com.acoezard.avaj_launcher;

import java.util.ArrayList;
import java.util.List;

import com.acoezard.avaj_launcher.aircrafts.Flyable;
import com.acoezard.avaj_launcher.utils.Logger;

public class Tower {
    private final List<Flyable> observers = new ArrayList<>();
    
    public void register(Flyable flyable) {
        this.observers.add(flyable);
        Logger.log("Tower says: " + flyable.toString() + " registered to weather tower.");
    }

    public void unregister(Flyable flyable) {
        this.observers.remove(flyable);
        Logger.log("Tower says: " + flyable.toString() + " unregistered from weather tower.");
    }

    protected void conditionsChanged() {
        for (int i = 0; i < observers.size(); i++) {
			observers.get(i).updateConditions();
		}
    }
}