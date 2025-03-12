local input1 = ""
local input2 = ""
local messaggio = ""
local coloreSfondo = {0, 0, 0}

function love.textinput(t)
    if #input1 < 10 then
        input1 = input1 .. t
    elseif #input2 < 10 then
        input2 = input2 .. t
    end
end

function love.keypressed(key)
    if key == "backspace" then
        if #input2 > 0 then
            input2 = input2:sub(1, -2)
        elseif #input1 > 0 then
            input1 = input1:sub(1, -2)
        end
    elseif key == "return" then
        -- Converte gli input in numeri
        local num1 = tonumber(input1)
        local num2 = tonumber(input2)

        if num1 and num2 then
            -- Richiama la funzione scritta in C
            local somma, isPari = calcolaSomma(num1, num2)
            messaggio = "Somma: " .. somma
            coloreSfondo = isPari and {1, 0, 0} or {0, 1, 0} -- Rosso se pari, verde se dispari
        else
            messaggio = "Inserisci due numeri validi!"
        end
    end
end

function love.draw()
    -- Sfondo
    love.graphics.clear(coloreSfondo)

    -- Testo di input
    love.graphics.setColor(1, 1, 1)
    love.graphics.print("Numero 1: " .. input1, 10, 10)
    love.graphics.print("Numero 2: " .. input2, 10, 30)

    -- Messaggio risultato
    love.graphics.print(messaggio, 10, 60)
end
