class Classe:
    def __init__(self):
        self.Membri = []  # Instance attribute

    class Studente:
        def __init__(self, Nome, Età):
            self.Nome = Nome
            self.Età = Età
            self.Voti = []

        def __lt__(self, other):
            return self.Età < other.Età

        def Nuovo_Voto(self, Classe, Denominativo, Voto):
            for Studente in Classe.Membri:
                if Studente.Nome == Denominativo:
                    Studente.Voti.append(Voto)
                    return
            print(f"Studente {Denominativo} non trovato!")
    
    def Nuovo_Studente(self, Denominativo, Età, Voto):
        Ragazzo = self.Studente(Denominativo, Età)
        Ragazzo.Voti.append(Voto)
        self.Membri.append(Ragazzo)
        self.Membri.sort()

TrED = Classe()
MadeInItaly = Classe()

TrED.Nuovo_Studente("Michele Acciuffi", 15, 8.9)

for Guy in TrED.Membri:
    print(f"{Guy.Nome}, Età: {Guy.Età}, Voti: {Guy.Voti}")

TrED.Studente.Nuovo_Voto(TrED, "Michele Acciuffi", 9.5)

for Guy in TrED.Membri:
    print(f"{Guy.Nome}, Età: {Guy.Età}, Voti: {Guy.Voti}")
