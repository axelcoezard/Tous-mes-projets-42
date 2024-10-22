COLOR_GREEN = "\033[1;32m"
COLOR_RESET = "\033[0m"

def print_header():
	print("""\033[1;32m█████████  █████                        █████
  ███░░░░░███░░███                        ░░███
 ███     ░░░  ░███████    ██████   ██████  ░███ █████  ██████  ████████
░███          ░███░░███  ███░░███ ███░░███ ░███░░███  ███░░███░░███░░███
░███          ░███ ░███ ░███████ ░███ ░░░  ░██████░  ░███████  ░███ ░░░
░░███     ███ ░███ ░███ ░███░░░  ░███  ███ ░███░░███ ░███░░░   ░███
 ░░█████████  ████ █████░░██████ ░░██████  ████ █████░░██████  █████
  ░░░░░░░░░  ░░░░ ░░░░░  ░░░░░░   ░░░░░░  ░░░░ ░░░░░  ░░░░░░  ░░░░░\033[0m""")

def load_thetas():
	theta0 = 0
	theta1 = 0

	try:
		with open("./data/thetas.csv", "r") as f:
			f.readline()
			theta0, theta1 = f.readline().split(",")
			theta0 = float(theta0)
			theta1 = float(theta1)
			f.close()
	except FileNotFoundError:
		print("Pas de fichier thetas.csv!")
		exit(1)

	return theta0, theta1

def load_data():
	X = []
	Y = []
	try:
		with open("./data/data.csv", "r") as f:
			f.readline()
			for line in f:
				x, y = line.split(",")
				X.append(int(x))
				Y.append(int(y))
			f.close()
	except FileNotFoundError:
		print("Pas de fichier data.csv!")
		exit(1)
	return X, Y

if __name__ == "__main__":
	print_header()

	theta0, theta1 = load_thetas()
	X, Y = load_data()

	print(COLOR_GREEN, "\nCalcul des erreurs:".ljust(25), COLOR_RESET, sep="")
	errors = []
	total_error = 0
	error_max = 0
	error_min = 100
	for index, x in enumerate(X):
		y1 = Y[index]
		y2 = theta0 * x + theta1
		error = abs(y1 - y2) * 100 / y1
		print(str(index).ljust(3), "Δ(" + str(x).rjust(6) + ") =", str(round(error, 2)).rjust(5), "%")
		if error > error_max: error_max = error
		if error < error_min: error_min = error
		errors.append(error)
		total_error += error
	avg_error = total_error / len(X)

	print(COLOR_GREEN, "\nErreur minimale:".ljust(25), COLOR_RESET, str(round(error_min, 2)).rjust(5), " %", sep="")
	print(COLOR_GREEN, "Erreur maximale:".ljust(25), COLOR_RESET, str(round(error_max, 2)).rjust(5), " %", sep="")
	print(COLOR_GREEN, "Moyenne de l'erreur:".ljust(25), COLOR_RESET, str(round(avg_error, 2)).rjust(5), " %", sep="")

	ecart_type = 0
	for error in errors:
		ecart_type += (error - avg_error) ** 2
	ecart_type = (ecart_type / len(X)) ** .5
	print(COLOR_GREEN, "Ecart-type de l'erreur:".ljust(25), COLOR_RESET, str(round(ecart_type, 2)).rjust(5), " %", sep="")
	print(COLOR_GREEN, "\nPrecision:".ljust(25), COLOR_RESET, str(100 - round(avg_error, 2)).rjust(5), " %", sep="")
