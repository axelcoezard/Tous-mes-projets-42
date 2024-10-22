def print_header():
	print("""\033[1;32m███████████                         █████  ███            █████     ███
░░███░░░░░███                       ░░███  ░░░            ░░███     ░░░
 ░███    ░███ ████████   ██████   ███████  ████   ██████  ███████   ████   ██████  ████████
 ░██████████ ░░███░░███ ███░░███ ███░░███ ░░███  ███░░███░░░███░   ░░███  ███░░███░░███░░███
 ░███░░░░░░   ░███ ░░░ ░███████ ░███ ░███  ░███ ░███ ░░░   ░███     ░███ ░███ ░███ ░███ ░███
 ░███         ░███     ░███░░░  ░███ ░███  ░███ ░███  ███  ░███ ███ ░███ ░███ ░███ ░███ ░███
 █████        █████    ░░██████ ░░████████ █████░░██████   ░░█████  █████░░██████  ████ █████
░░░░░        ░░░░░      ░░░░░░   ░░░░░░░░ ░░░░░  ░░░░░░     ░░░░░  ░░░░░  ░░░░░░  ░░░░ ░░░░░\033[0m""")

if __name__ == "__main__":
	print_header()
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

	try:
		value = float(input("Nombre de kilometres au compteur de la voiture:\n"))
		print("=> La voiture devrait pouvoir se vendre", round(theta0 * value + theta1, 2), "euros.")
	except ValueError:
		print("=> Erreur: le nombre de kilometres doit être un nombre.")
