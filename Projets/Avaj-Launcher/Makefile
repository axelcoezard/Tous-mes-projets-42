all:
	find * -name "*.java" > sources.txt
	javac -sourcepath ./src/ -d bin @sources.txt
	cd ./bin && java com.acoezard.avaj_launcher.Simulator ../resources/scenario.txt

logs:
	cat ./bin/simulation.txt

clean:
	rm -r ./bin

re: clean all
