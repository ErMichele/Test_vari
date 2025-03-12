#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int lua_somma(lua_State *L) {
    double a = lua_tonumber(L, 1); // Primo numero
    double b = lua_tonumber(L, 2); // Secondo numero
    double somma = a + b;

    lua_pushnumber(L, somma);        // Restituisce la somma
    lua_pushboolean(L, ((int)somma % 2 == 0)); // Restituisce true se pari, false se dispari

    return 2; // Due valori restituiti
}

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // Registra la funzione in Lua
    lua_register(L, "calcolaSomma", lua_somma);

    // Carica ed esegui Love2D
    if (luaL_dofile(L, "main.lua")) {
        printf("Errore: %s\n", lua_tostring(L, -1));
    }

    lua_close(L);
    return 0;
}
