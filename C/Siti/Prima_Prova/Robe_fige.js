// Funzione che viene chiamata quando l'utente preme il pulsante
function eseguiAzione() {
    // Ottieni il valore dell'input
    var inputUtente = document.getElementById("inputUtente").value;

    // Controlla il valore inserito e fai qualcosa
    if (inputUtente === "Bene") {
        alert("Ne sono felice");
    } else if (inputUtente === "Male") {
        alert("Mi dispiace...");
    } else {
        alert("Hai scritto: " + inputUtente);
    }
}
