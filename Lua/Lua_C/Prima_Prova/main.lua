local ffi = require("ffi")

-- Definisci la funzione della DLL
ffi.cdef[[
    int somma(int a, int b);
]]

-- Carica la DLL
local mialibreria = ffi.load("Backend\\mialibreria.dll")

-- Usa la funzione somma
local risultato = mialibreria.somma(5, 10)

function love.draw ()
    love.graphics.print(risultato, 400, 300)
end
