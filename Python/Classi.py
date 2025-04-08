class Classe:
    def __init__(self):
        self.membri = []  # Attributo di istanza per contenere gli studenti

    class Studente:
        def __init__(self, nome, eta):
            self.nome = nome
            self.eta = eta
            self.voti = []

        def __lt__(self, other):
            return self.eta < other.eta

        def aggiungi_voto(self, voto):
            if 0 <= voto <= 10:  # Valida il voto prima di aggiungerlo
                self.voti.append(voto)
            else:
                print("Voto non valido! Deve essere compreso tra 0 e 10.")

    def nuovo_studente(self, nome, eta, voto):
        # Controlla se il nome è già presente
        for studente in self.membri:
            if studente.nome == nome:
                print(f"Studente {nome} è già registrato!")
                return
        # Aggiunge un nuovo studente
        nuovo = self.Studente(nome, eta)
        nuovo.aggiungi_voto(voto)
        self.membri.append(nuovo)
        self.membri.sort()  # Ordina automaticamente per età

    def aggiungi_voto_studente(self, nome, voto):
        for studente in self.membri:
            if studente.nome == nome:
                studente.aggiungi_voto(voto)
                return
        print(f"Studente {nome} non trovato!")

    def stampa_membri(self):
        for studente in self.membri:
            print(f"{studente.nome}, Età: {studente.eta}, Voti: {studente.voti}")


# Esempio di utilizzo
trED = Classe()

trED.nuovo_studente("Michele Acciuffi", 15, 8.9)
trED.stampa_membri()

trED.aggiungi_voto_studente("Michele Acciuffi", 9.5)
trED.stampa_membri()
