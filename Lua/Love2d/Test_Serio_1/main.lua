local menuOptions = {"Inizia Gioco", "Opzioni", "Esci"}
local selectedOption = 1
local keyPressed = false

function love.load()
    love.window.setTitle("Test serio")
    love.graphics.setFont(love.graphics.newFont(20))
end

function love.update(dt)
    if not keyPressed then
        if love.keyboard.isDown("down") then
            selectedOption = selectedOption + 1
            if selectedOption > #menuOptions then
                selectedOption = 1
            end
            keyPressed = true
        elseif love.keyboard.isDown("up") then
            selectedOption = selectedOption - 1
            if selectedOption < 1 then
                selectedOption = #menuOptions
            end
            keyPressed = true
        elseif love.keyboard.isDown("return") then
            if menuOptions[selectedOption] == "Inizia Gioco" then
                print("Avvio del gioco...")
            elseif menuOptions[selectedOption] == "Opzioni" then
                print("Aprendo il menu delle opzioni...")
            elseif menuOptions[selectedOption] == "Esci" then
                love.event.quit()
            end
            keyPressed = true
        end
    end

    if not love.keyboard.isDown("down") and not love.keyboard.isDown("up") and not love.keyboard.isDown("return") then
        keyPressed = false
    end
end

function love.draw()
    love.graphics.printf("Menu del Gioco", 0, 50, love.graphics.getWidth(), "center")
    
    for i, option in ipairs(menuOptions) do
        if i == selectedOption then
            love.graphics.setColor(1, 0, 0) -- Colore rosso per l'opzione selezionata
        else
            love.graphics.setColor(1, 1, 1) -- Colore bianco per le altre opzioni
        end
        
        love.graphics.printf(option, 0, 100 + i * 30, love.graphics.getWidth(), "center")
    end
    
    love.graphics.setColor(1, 1, 1) -- Reset del colore
end
