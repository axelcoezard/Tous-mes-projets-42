package com.acoezard.avaj_launcher.utils;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import com.acoezard.avaj_launcher.aircrafts.AircraftFactory;
import com.acoezard.avaj_launcher.aircrafts.Flyable;
import com.acoezard.avaj_launcher.exceptions.SimulatorException;

public class Parser {
    private int simulationCount;
    private List<Flyable> aicrafts = new ArrayList<>();
    
    public void parse(String filename) throws IOException, SimulatorException {
		BufferedReader bufferedReader = new BufferedReader(new FileReader(filename));
        
		String firstLine = this.nextLine(bufferedReader);
        if (firstLine == null) {
            throw new SimulatorException("No not-empty line has been found.");
        }
        this.simulationCount = this.shouldBeNumeric(firstLine);
        if (this.simulationCount < 0) {
            throw new SimulatorException("Simulation count should be positive.");
        }

		String aircraftLine;
        Integer line = 0;
        while ((aircraftLine = this.nextLine(bufferedReader)) != null) {
            String[] args = aircraftLine.split("\\s+");
            if (args.length != 5) {
                throw new SimulatorException("Wrong args count for line '" + aircraftLine + "': " + args.length + " != 5");
            }

            int longitude = this.shouldBeNumeric(args[2]);
            int latitude = this.shouldBeNumeric(args[3]);
            int height = this.shouldBeNumeric(args[4]);

            if (longitude < 0 || latitude < 0) {
                throw new SimulatorException("Both longitude and latitude should be positive on line '" + aircraftLine + "'.");
            }

            Flyable flyable = AircraftFactory.newAircraft(args[0], args[1], longitude, latitude, height);
            this.aicrafts.add(flyable);
            line++;
        }
	}

	private String nextLine(BufferedReader bufferedReader) throws IOException {
		String line;
		while ((line = bufferedReader.readLine()) != null) {
			if (!line.isEmpty() && !line.isBlank() && line.length() > 0) {
                return line.trim();
            }
		}
		return null;
	}

    private int shouldBeNumeric(String value) throws SimulatorException {
        try {
            return Integer.parseInt(value);
        } catch (NumberFormatException e) {
            throw new SimulatorException("'" + value + "' should be numeric");
        }
    }

    public int getSimulationCount() {
        return this.simulationCount;
    }

    public List<Flyable> getAircrafts() {
        return this.aicrafts;
    }
}
