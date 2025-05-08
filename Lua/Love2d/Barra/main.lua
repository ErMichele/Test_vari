-- Definizione della barra di scorrimento
slider = {
    x = 100,         -- Posizione X
    y = 200,         -- Posizione Y
    width = 300,     -- Larghezza della barra
    height = 10,     -- Altezza della barra
    knobX = 100,     -- Posizione X del cursore
    knobWidth = 20,  -- Larghezza del cursore
    value = 0.5,     -- Valore iniziale (0.0 - 1.0)
    dragging = false -- Stato del trascinamento
}

function love.update(dt)
    -- Se il cursore è trascinato, aggiorna la posizione
    if slider.dragging then
        local mouseX = love.mouse.getX()
        slider.knobX = math.max(slider.x, math.min(mouseX, slider.x + slider.width - slider.knobWidth))
        slider.value = (slider.knobX - slider.x) / (slider.width - slider.knobWidth)
    end
end

function love.draw()
    -- Disegna la barra
    love.graphics.setColor(0.5, 0.5, 0.5)
    love.graphics.rectangle("fill", slider.x, slider.y, slider.width, slider.height)

    -- Disegna il cursore
    love.graphics.setColor(1, 1, 1)
    love.graphics.rectangle("fill", slider.knobX, slider.y - 5, slider.knobWidth, slider.height + 10)

    -- Mostra il valore del volume
    love.graphics.setColor(1, 1, 1)
    love.graphics.print("Volume: " .. math.floor(slider.value * 100) .. "%", slider.x, slider.y - 30)
end

function love.mousepressed(x, y, button)
    if button == 1 and x >= slider.knobX and x <= slider.knobX + slider.knobWidth and y >= slider.y - 5 and y <= slider.y + slider.height + 5 then
        slider.dragging = true
    end
end

function love.mousereleased(x, y, button)
    if button == 1 then
        slider.dragging = false
    end
end
